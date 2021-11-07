--
--
--

\echo Use "CREATE EXTENSION pg_valid" to load this file. \quit

CREATE FUNCTION pgvalid_create_registered_domains_table("schema" TEXT DEFAULT 'public') RETURNS VOID AS
$$
BEGIN
    EXECUTE format('CREATE TABLE IF NOT EXISTS %I.registered_domains (' ||
                   '"name" VARCHAR(64) NOT NULL,' ||
                   '"schema" VARCHAR(64) NOT NULL,' ||
                   'not_blank BOOLEAN DEFAULT true,' ||
                   'html_escaped BOOLEAN DEFAULT true,' ||
                   'is_num BOOLEAN DEFAULT false,' ||
                   'is_alpha BOOLEAN DEFAULT false,' ||
                   'is_alnum BOOLEAN DEFAULT false,' ||
                   'is_email BOOLEAN DEFAULT false,' ||
                   'regex TEXT NOT NULL DEFAULT '''',' ||
                   'min_length INT NOT NULL DEFAULT -1,' ||
                   'max_length INT NOT NULL DEFAULT -1,' ||
                   'min NUMERIC NOT NULL DEFAULT -1, ' ||
                   'max NUMERIC NOT NULL DEFAULT -1, ' ||
                   '"type" TEXT NOT NULL DEFAULT ''VARCHAR'',' ||
                   'numeric_prec_int INT DEFAULT -1,' ||
                   'numeric_prec_frac INT DEFAULT -1,' ||
                   'char_length INT DEFAULT 64,' ||
                   'CONSTRAINT registered_domains_pk PRIMARY KEY ("schema","name"),' ||
                   'CONSTRAINT registered_domains_validated_check CHECK ' ||
                   '((is_num = true AND is_alpha = false AND is_alnum = false) OR' || -- one of should be true
                   '(is_num = false AND is_alpha = true AND is_alnum = false) OR' ||
                   '(is_num = false AND is_alpha = false AND is_alnum = true) OR' ||
                   '(is_num = false AND is_alpha = false AND is_alnum = false))' || -- no validators were applied
                   ');', "schema");
END;
$$
    LANGUAGE plpgsql
    VOLATILE
    PARALLEL UNSAFE
    SECURITY INVOKER
    STRICT;

CREATE FUNCTION pgvalid_drop_registered_domains_table("schema" TEXT DEFAULT 'public') RETURNS VOID AS
$$
DECLARE
    dom RECORD;
BEGIN
    FOR dom IN
        EXECUTE format('SELECT "name", "schema" FROM %I.registered_domains', "schema")
        LOOP
            PERFORM pgvalid_drop_validated_domain(dom."name", dom."schema", "schema");
        END LOOP;

    EXECUTE format('DROP TABLE IF EXISTS %I.registered_domains', "schema");
END;
$$
    LANGUAGE plpgsql
    VOLATILE
    PARALLEL UNSAFE
    SECURITY INVOKER
    STRICT;

CREATE FUNCTION pgvalid_create_validated_domain("name" TEXT,
                                                "schema" TEXT DEFAULT 'public',
                                                not_blank BOOLEAN DEFAULT true,
                                                html_escaped BOOLEAN DEFAULT true,
                                                is_num BOOLEAN DEFAULT false,
                                                is_alpha BOOLEAN DEFAULT false,
                                                is_alnum BOOLEAN DEFAULT false,
                                                is_email BOOLEAN DEFAULT false,
                                                regex TEXT DEFAULT '',
                                                min_length INT DEFAULT 3,
                                                max_length INT DEFAULT 64,
                                                min NUMERIC DEFAULT -1,
                                                max NUMERIC DEFAULT -1,
                                                "type" TEXT DEFAULT 'VARCHAR',
                                                numeric_prec_int INT DEFAULT -1,
                                                numeric_prec_frac INT DEFAULT -1,
                                                char_length INT DEFAULT 64,
                                                dump_query BOOLEAN DEFAULT false,
                                                registered_domains_schema TEXT DEFAULT 'public') RETURNS VOID AS
$$
DECLARE
    result_query TEXT := format('CREATE DOMAIN %I.%I AS %s', "schema", "name", upper("type"));
    insert_query TEXT := '';
BEGIN

    IF (position('(' in lower("type")) > 0 OR position(')' in lower("type")) > 0) THEN
        RAISE EXCEPTION 'Unexpected brackets, please use char_length, numeric_prec_int, numeric_prec_frac parameters instead';
    END IF;

    PERFORM pgvalid_create_registered_domains_table(registered_domains_schema);

    IF (lower("type") = ANY (string_to_array('varchar,char,text', ','))) THEN
        IF (max_length > 0 AND min_length > 0 AND max_length < min_length) THEN
            RAISE EXCEPTION 'Expected max_length % to be greater than min_length %', max_length, min_length;
        END IF;

        IF (NOT max_length > 0 AND char_length <= max_length) THEN
            RAISE EXCEPTION 'Expected char_length % to be greater or equal max_length %', char_length, max_length;
        END IF;

        IF (lower("type") <> 'text') THEN
            IF char_length <= 0 THEN
                RAISE EXCEPTION 'Expected char_length % to be positive', char_length;
            END IF;

            result_query := format('%s(%s) ', result_query, char_length);
        ELSE
            result_query := format('%s ', result_query);
        END IF;

        IF (not_blank) THEN
            result_query :=
                    format('%s CONSTRAINT %s_not_blank CHECK (length(trim_ws(VALUE)) > 0) ', result_query, "name");
        END IF;

        IF (html_escaped) THEN
            result_query :=
                    format('%s CONSTRAINT %s_html_escaped CHECK (is_html_escaped(trim_ws(VALUE))) ', result_query,
                           "name");
        END IF;

        IF (is_num) THEN
            result_query :=
                    format('%s CONSTRAINT %s_is_num CHECK (is_num(trim_ws(VALUE))) ', result_query, "name");
        END IF;

        IF (is_alpha) THEN
            result_query :=
                    format('%s CONSTRAINT %s_is_alpha CHECK (is_alpha(trim_ws(VALUE))) ', result_query, "name");
        END IF;

        IF (is_alnum) THEN
            result_query :=
                    format('%s CONSTRAINT %s_is_alnum CHECK (is_alnum(trim_ws(VALUE))) ', result_query, "name");
        END IF;

        IF (is_email) THEN
            result_query :=
                    format('%s CONSTRAINT %s_is_enum CHECK (is_email(trim_ws(VALUE))) ', result_query, "name");
        END IF;

        IF min_length = max_length AND max_length > 0 THEN
            result_query :=
                    format('%s CONSTRAINT %s_length_eq CHECK (trim_ws(VALUE) = %s) ', result_query, "name", max_length);
        ELSE
            IF (min_length > 0) THEN
                result_query :=
                        format('%s CONSTRAINT %s_too_short CHECK (char_length(trim_ws(VALUE)) > %s) ', result_query,
                               "name",
                               min_length);
            END IF;

            IF (max_length > 0) THEN
                result_query :=
                        format('%s CONSTRAINT %s_too_long CHECK (char_length(trim_ws(VALUE)) < %s) ', result_query,
                               "name",
                               max_length);
            END IF;
        END IF;

        IF regex <> '' THEN
            result_query := format('%s CONSTRAINT %s_regex CHECK (VALUE ~ %L) ', result_query, "name", regex);
        END IF;
    ELSE
        IF (lower("type") = ANY (string_to_array(
                'int,int2,int4,int8,numeric,byte,smallint,integer,bigint,decimal,real,double precision,serial,bigserial',
                ',')) OR
            starts_with(lower("type"), 'numeric')
            ) THEN

            min_length := -1;
            max_length := -1;

            IF (starts_with(lower("type"), 'numeric')) THEN

                IF numeric_prec_int <= 0 THEN
                    RAISE EXCEPTION 'Expected numeric_prec_int % to be positive', char_length;
                END IF;

                IF numeric_prec_frac <= 0 THEN
                    RAISE EXCEPTION 'Expected numeric_prec_frac % to be positive', char_length;
                END IF;

                result_query := format('%s(%s, %s) ', result_query, numeric_prec_int, numeric_prec_frac);
            ELSE
                result_query := format('%s ', result_query);
            END IF;

            IF "min" = "max" AND "max" > 0 THEN
                result_query :=
                        format('%s CONSTRAINT %s_eq CHECK (VALUE = %s) ', result_query, "name", "max");
            ELSE
                IF ("min" > 0) THEN
                    result_query :=
                            format('%s CONSTRAINT %s_min CHECK (VALUE > %s) ', result_query, "name",
                                   "min");
                END IF;

                IF ("max" > 0) THEN
                    result_query :=
                            format('%s CONSTRAINT %s_max CHECK (VALUE < %s) ', result_query, "name",
                                   "max");
                END IF;
            END IF;
        ELSE
            RAISE EXCEPTION 'Expected % to be one of VARCHAR, CHAR or TEXT or any numeric type', "type";
        END IF;
    END IF;

    result_query := format('%s;', result_query);

    insert_query := format('INSERT INTO %I.registered_domains VALUES (' ||
                   '%L, ' || -- name
                   '%L, ' || -- schema
                   '%L, ' || -- not blank
                   '%L, ' || -- html escaped
                   '%L, ' || -- is num
                   '%L, ' || -- is alpha
                   '%L, ' || -- is alnum
                   '%L, ' || -- is email
                   '%L, ' || -- regex
                   '%s, ' || -- min length
                   '%s, ' || -- max length
                   '%s, ' || -- min
                   '%s, ' || -- max
                   '%L, ' || -- type
                   '%s, ' || -- numeric_prec_int
                   '%s, ' || -- numeric_prec_frac
                   '%s' || -- char length
                   ');',
                   registered_domains_schema,
                   "name",
                   "schema",
                   not_blank,
                   html_escaped,
                   is_num,
                   is_alpha,
                   is_alnum,
                   is_email,
                   regex,
                   min_length,
                   max_length,
                   "min",
                   "max",
                   upper("type"),
                   numeric_prec_int,
                   numeric_prec_frac,
                   char_length);


    EXECUTE result_query;
    EXECUTE insert_query;

    if dump_query THEN
        RAISE INFO 'RESULT QUERY:\n%', result_query;
        RAISE INFO 'RESULT INSERT QUERY:\n%', insert_query;
    END IF;
END;
$$
    LANGUAGE plpgsql
    VOLATILE
    PARALLEL UNSAFE
    SECURITY INVOKER
    STRICT;

CREATE FUNCTION pgvalid_drop_validated_domain("name" TEXT,
                                              "schema" TEXT DEFAULT 'public',
                                              registered_domains_schema TEXT DEFAULT 'public') RETURNS VOID AS
$$
BEGIN
    EXECUTE format('DROP DOMAIN %I.%I;', "schema", "name");

    EXECUTE format('DELETE FROM %I.registered_domains WHERE "schema" = %L AND "name" = %L;',
                   registered_domains_schema, "schema", "name");
END;
$$
    LANGUAGE plpgsql
    VOLATILE
    PARALLEL UNSAFE
    SECURITY INVOKER
    STRICT;
