--
--
--

-- \echo
-- Use "CREATE EXTENSION pg_valid" to load this file.
-- \quit

CREATE FUNCTION is_alpha_extra("in" VARCHAR, chars VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_alpha("in" VARCHAR)
    RETURNS BOOLEAN
AS
$$
DECLARE
    result VARCHAR;
BEGIN
    EXECUTE format('SELECT %I.is_alpha_extra(%L, '''')::VARCHAR', current_schema, "in") INTO result;
    RETURN result;
END;
$$
    LANGUAGE plpgsql
    STRICT
    STABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_alnum_extra("in" VARCHAR, chars VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_alnum("in" VARCHAR)
    RETURNS BOOLEAN
AS
$$
DECLARE
    result VARCHAR;
BEGIN
    EXECUTE format('SELECT %I.is_alnum_extra(%L, '''')::VARCHAR', current_schema, "in") INTO result;
    RETURN result;
END;
$$
    LANGUAGE plpgsql
    STRICT
    STABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_num_extra("in" VARCHAR, chars VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_num("in" VARCHAR)
    RETURNS BOOLEAN
AS
$$
DECLARE
    result VARCHAR;
BEGIN
    EXECUTE format('SELECT %I.is_num_extra(%L, '''')::VARCHAR', current_schema, "in") INTO result;
    RETURN result;
END;
$$
    LANGUAGE plpgsql
    STRICT
    STABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_lowercase("in" VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_uppercase("in" VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_email("in" VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION is_html_escaped("in" VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION not_blank("in" VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION trim_ws_extra("in" VARCHAR, trim_extra BOOLEAN)
    RETURNS CSTRING
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION trim_ws("in" VARCHAR)
    RETURNS VARCHAR
AS
$$
DECLARE
    result VARCHAR;
BEGIN
    EXECUTE format('SELECT %I.trim_ws_extra(%L, true)::VARCHAR', current_schema, "in") INTO result;
    RETURN result;
END;
$$
    LANGUAGE plpgsql
    STRICT
    STABLE
    SECURITY INVOKER
    PARALLEL SAFE;

CREATE FUNCTION p_mkdir("dir" VARCHAR)
    RETURNS BOOLEAN
AS
'MODULE_PATHNAME'
    LANGUAGE C
    STRICT
    IMMUTABLE
    SECURITY INVOKER
    PARALLEL SAFE;