### Validation

### is_alpha is_num is_alnum
```postgresql
SELECT is_num("123");
SELECT is_alpha("FooBared");
SELECT is_alnum("Foobared2021");
```

### is_lowercase is_uppercase
```postgresql
SELECT "yolo" AS str, is_lowercase("yolo") AS lowercase;
SELECT "YOLO" AS str, is_uppercase("YOLO") AS uppercase;
```

### is_email
This validator doesn't support i18n xn-- domains.
```postgresql
SELECT "happy@ne.ko" AS email, is_email("happy@ne.ko");
```

### is_html_escaped
```postgresql
SELECT is_html_escaped("& lt;script& gt;alert(& apos;Oh well& apos;)& lt;script& gt;");
```

### trim_ws
```postgresql
SELECT trim_ws(' abc') = 'abc'  AS trimmed_left,
       trim_ws('abc ') = 'abc'  AS trimmed_right,
       trim_ws(' abc ') = 'abc' AS trimmed_both;
```

### not_blank
```postgresql
SELECT not_blank('abc') = true AS not_blank,
       not_blank('  ') = false AS blank1,
       not_blank('')           AS blank2;
```

We're expecting you to trim your inputs yourself using trim rules.
```
CREATE RULE strings_trim_rule AS ON INSERT TO public.table DO INSTEAD
  INSERT INTO public.table VALUES (
    NEW.id, 
    trim_ws(NEW.varchar_col)
  )
```
