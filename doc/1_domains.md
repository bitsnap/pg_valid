### Domains

```sql

CREATE DOMAIN email AS VARCHAR(64)
    CONSTRAINT email_not_blank CHECK (not_blank(VALUE))
    CONSTRAINT email_too_short CHECK (length(VALUE) < 5) -- trim_ws needs a cast from cstring
    CONSTRAINT email_valid CHECK (is_email(VALUE));

-- same as

SELECT pgvalid_create_validated_domain('email',
                               not_blank => true,
                               is_email => true,
                               min_length => 5,
                               max_length => 64
           -- by default  
           -- "type" => 'VARCHAR', -- TEXT and CHAR's also supported
           -- char_length => 64
           );

-- --

CREATE DOMAIN email AS VARCHAR(64)
    CONSTRAINT email_not_blank CHECK (not_blank(VALUE))
    CONSTRAINT email_too_short CHECK (length(VALUE) < 3) -- trim_ws needs a cast from cstring
    CONSTRAINT email_alnum CHECK (is_alnum(VALUE))
    CONSTRAINT email_is_email CHECK (is_email(VALUE));

-- same as

SELECT pgvalid_create_validated_domain("name" => 'email',
                               not_blank => true,
                               is_email => true,
                               min_length => 3
           );

-- --

CREATE DOMAIN age AS INT CONSTRAINT age_min CHECK (VALUE > 18);

-- same as 

SELECT pgvalid_create_validated_domain("name" => 'age',
                               "type" => 'INT',
                               min => 18
           );

-- -- 

SELECT pgvalid_create_validated_domain("name" => 'currency',
                                       "type" => 'numeric',
                                       min => 18,
                                       numeric_prec_int = 8,
                                       numeric_prec_frac = 5,
           );

-- same as

CREATE DOMAIN currency AS numeric(8, 5)
    CONSTRAINT currency_min CHECK (VALUE > 18)

```

### pgvalid_create_registered_domains_table

`create_validated_domain("schema" TEXT DEFAULT 'public')` proc creates a `registered_domains` table for the target schema.

It's adviceable to use a separate schema for all the domains and respective validation functions, but is not mandatory.
`create_validated_domain` is executed by `pgvalid_create_validated_domain` every time new domain is created.

`registered_domains` table contains basic rules description, for the sake of domain migrations simplicity, and is usually being 
reused by the other postgres extensions.

### pgvalid_drop_registered_domains_table

`pgvalid_drop_registered_domains_table("schema" TEXT DEFAULT 'public')` proc drops `registered_domains` and all the previously created (registered) domains alongside. 

### pgvalid_create_validated_domain

```sql
pgvalid_create_validated_domain("name" TEXT,
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
                                registered_domains_schema TEXT DEFAULT 'public')
```

All in all this should be more or less self-explanatory - creates the domain using common validation checks.

`registered_domains_schema` is a schema where the `registered_domains` table is residing.

`dump_query` - outputs the resulting CREATE DOMAIN SQL query for debug and convenience.

**NOTE:** use `numeric_prec_int`, `numeric_prec_frac`, `char_length` for variadic types, i.e varchars, numerics, chars etc.

This extension provides only the most basic typecheck, which should be sufficient for the most cases.

### pgvalid_drop_validated_domain 

```sql
pgvalid_drop_validated_domain("name" TEXT,
                              "schema" TEXT DEFAULT 'public',
                              registered_domains_schema TEXT DEFAULT 'public') 
```

Drops domain previously created by `pgvalid_create_validated_domain` and stored in `registered_domains` table.

`registered_domains` table may reside in a different schema specified by `registered_domains_schema` param.