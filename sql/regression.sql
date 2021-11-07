--
-- Copyright (c) 2008-2021 Yuriy Yarosh
--

CREATE
EXTENSION pg_valid;

SELECT not_blank('abc');
SELECT not_blank('abc ');
SELECT not_blank(' abc');
SELECT not_blank('åbc');
SELECT not_blank('åbc ');
SELECT not_blank(' åbc');
SELECT not_blank('');

SELECT '|' || trim_ws_extra(' a1    ', false) || '|';
SELECT '|' || trim_ws_extra('       ', false) || '|';
SELECT '|' || trim_ws_extra('1       ', false) || '|';
SELECT '|' || trim_ws_extra('       1', false) || '|';
SELECT '|' || trim_ws_extra('       1a', false) || '|';
SELECT '|' || trim_ws_extra(' a1bc   ', false) || '|';

SELECT '|' || trim_ws_extra(' a1    ', true) || '|';
SELECT '|' || trim_ws_extra('       ', true) || '|';
SELECT '|' || trim_ws_extra('a       ', true) || '|';
SELECT '|' || trim_ws_extra('       1', true) || '|';
SELECT '|' || trim_ws_extra('       1a', true) || '|';
SELECT '|' || trim_ws_extra(' a1bc   ', true) || '|';

SELECT '|' || trim_ws_extra(' å1bc   ', true) || '|';
SELECT '|' || trim_ws_extra('å1bc   ', true) || '|';


SELECT is_num('123');
SELECT is_alpha('abc');
SELECT is_alpha('åbc');
SELECT is_alnum('abc1');
SELECT is_alnum('åbc1');
SELECT is_alnum('1abc1');
SELECT is_alnum('1åbc1');

SELECT is_alnum_extra('1åbc1\ ', ' ');
SELECT is_alnum_extra('1åbc1\ ', ' \');
SELECT is_alpha_extra('åbc\ ', ' ');
SELECT is_alpha_extra('åbc\ ', ' \');
SELECT is_num_extra('123\ ', ' ');
SELECT is_num_extra('123\ ', ' \');

SELECT is_email('test@email.com');
SELECT is_email('test@email.com ');
SELECT is_email('test@z.com');

SELECT is_email('test@z.co');

SELECT is_html_escaped('<script>');
SELECT is_html_escaped('&lt;script&gt;');

SELECT pgvalid_create_validated_domain('test_domain');
SELECT *
FROM registered_domains;

SELECT pgvalid_drop_validated_domain('test_domain');
SELECT *
FROM registered_domains;
SELECT *
FROM pg_tables
WHERE tablename = 'registered_domains';

SELECT pgvalid_create_validated_domain('test_domain');
SELECT *
FROM registered_domains;

SELECT pgvalid_create_validated_domain("name" => 'age',
                                       "type" => 'INT',
                                       min => 18,
                                       dump_query => true
           );

SELECT pgvalid_create_validated_domain("name" => 'email',
                                       not_blank => true,
                                       is_email => true,
                                       min_length => 3,
                                       dump_query => true
           );

SELECT pgvalid_create_validated_domain("name" => 'currency',
                                       "type" => 'numeric',
                                       min => 18,
                                       numeric_prec_int => 8,
                                       numeric_prec_frac => 5,
                                       dump_query => true
           );

SELECT pgvalid_create_validated_domain("name" => 'should_fail',
                                       "type" => 'numeric(8, 5)',
                                       dump_query => true
           );

SELECT *
FROM registered_domains;

SELECT pgvalid_drop_registered_domains_table();
SELECT *
FROM pg_tables
WHERE tablename = 'registered_domains';
