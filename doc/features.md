### 0. [Validation](0_validation.md) primitives

 Basic string validation primitives

 - [is_alpha](0_validation.md#is_alpha-is_num-is_alnum) 
   [is_num](0_validation.md#is_alpha-is_num-is_alnum)
   [is_alnum](0_validation.md#is_alpha-is_num-is_alnum)
 - [is_lowercase](0_validation.md#is_lowercase-is_uppercase)
   [is_uppercase](0_validation.md#is_lowercase-is_uppercase)
 - [is_email](0_validation.md#is_email)
 - [is_html_escaped](0_validation.md#is_html_escaped) 
 - [trim_ws](0_validation.md#trim_ws)
 - [not_blank](0_validation.md#not_blank)

### 1. [Validated Domains](1_domains.md) management

 - [pgvalid_create_registered_domains_table](1_domains.md#pgvalid_create_registered_domains_table) creates `registered_domains` table
 - [pgvalid_drop_registered_domains_table](1_domains.md#pgvalid_drop_registered_domains_table) drops `registered_domains` table
 - [pgvalid_create_validated_domain](1_domains.md#pgvalid_create_validated_domain) creates validated domain using validation primitives above, 
   adds new `registered_domains` table entry, creates `registered_domains` if not exists
 - [pgvalid_drop_validated_domain](1_domains.md#pgvalid_drop_validated_domain) drops validated domain and clears `registered_domains` table entry 
