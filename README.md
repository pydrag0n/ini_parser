# INI_PARSER
- A very simple INI file parser

- Do whatever you want

- Read cfg.ini

## Example
The (parse_config) function returns a structure of the following form:
```c
typedef struct {
    char *section;
    char *key;
    char *value;
} Cfg;
```

```c
int main() {
    int count;
    Cfg *cfg = parse_config("cfg.ini", &count);

	for (int i = 0; i < count; i++) {
		printf("%-15s %-30s = %-30s\n", cfg[i].section, cfg[i].key, cfg[i].value);
	}

	return 0;
}
```

### Output
```
Server          host                 = 203.0.113.42
Server          port                 = 8080
Server          debug_mode           = true
Server          max_connections      = 512
Server          server_name          = FAKE_SERVER_01
Server          ssl_enabled          = false
Database        db_host              = mysql-fake.prod.internal
Database        db_name              = fake_production_db
Database        user                 = admin
Database        password             = s3cretP@ssw0rd!
Database        connection_timeout   = 30
Database        pool_size            = 20
External_API    weather_api_url      = https://api.weatherapp.fake/v3
External_API    currency_api_key     = 5up3rS3cr3tK3y-0000-FFFF-1234
External_API    request_timeout      = 15
External_API    retry_attempts       = 3
Logging         log_level            = DEBUG
Logging         log_path             = /var/log/fake_app/
Logging         max_log_size         = 50MB
Logging         archive_logs         = true
Security        encryption_key       = A1B2-C3D4-E5F6-G7H8
Security        2fa_enabled          = true
Security        password_expiration_days = 90
AppSettings     theme                = dark
AppSettings     default_language     = en_US
AppSettings     enable_analytics     = false
AppSettings     cache_ttl            = 3600
Backup          schedule             = 0 3 * * *
Backup          backup_path          = /mnt/fake_backups/
Backup          max_backups          = 30
Backup          cloud_sync_enabled   = true
```
