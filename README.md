# pg_valid

Complex postgres validation extension.

## Motivation

There's too much validation going on, usually on the backend and frontend side, but sometimes even in the database schema itself.
This extension was created to standardize domain validation and introduce basic reflection capabilities,
which makes the database schema the single source of truth. Posix regular expressions are far from anything I'd call fast, 
so porting the most common checks to C had improved performance a lot.

```sql

SELECT pgvalid_create_validated_domain("name" => 'email',
                                       not_blank => true,
                                       html_escaped => true,
                                       is_email => true,
                                       min_length => 3
);

SELECT pgvalid_create_validated_domain("name" => 'cleartext_password',
                                       not_blank => true,
                                       html_escaped => true,
                                       min_length => 5,

);

SELECT pgvalid_create_validated_domain("name" => 'full_name',
                                       not_blank => true,
                                       html_escaped => true,
                                       min_length => 5,
                                       is_alnum => true
);

CREATE TABLE public.users (
  id SERIAL NOT NULL,
  email email NOT NULL,
  password cleartext_password NOT NULL,
  full_name full_name NOT NULL
);

SELECT * FROM registered_domains WHERE "name" = 'full_name';
    name     | schema | not_blank | html_escaped | is_num | is_alpha | is_alnum | ...
-------------+--------+-----------+--------------+--------+----------+----------+
 full_name   | public | t         | t            | f      | f        | f        |

```

## Installation

Install [libicu](https://packages.debian.org/sid/libicu-dev) first for Unicode support; PostgreSQL ICU support is not
required, although ICU usage is advisable.

```bash
make 
sudo make install
sudo make installcheck
```

```sql
CREATE EXTENSION pg_valid;
```

## pg_valid [features](doc/features.md)

### 0. [Validation](doc/0_validation.md) primitives
To replace common SQL and regex based validation with a set of simple and efficient C functions.

### 1. [Validated Domains](doc/1_domains.md) management
A set of convenience functions to seamlessly create and manage validation domains.

## Testing

C Functions, without the extension binding

```bash
mkdir build
cd build
cmake ..
make
./pg_valid_test
```

Postgres extension

```bash
make
sudo make install
sudo systemctl restart postgresql
sudo PGUSER=postgres make installcheck
```

CTest is omitted for simplicity.

## License

Licensed under the terms of [MIT License](LICENSE).