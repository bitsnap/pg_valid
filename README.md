# pg_valid

Complex postgres validation extension... 

Just common practices I'm using in day-to-day development - wanted to consolidate everything and get some relevant feedback.

## Status

Mostly **DONE**.
Decided to split this into 7-8 different extensions to simplify further long term support.

## Installation

Install [libicu](https://packages.debian.org/sid/libicu-dev) first for Unicode support; PostgreSQL ICU support is not
required, although ICU usage is advisable.

```bash
make 
sudo make install
sudo make installcheck
```

```postgresql
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