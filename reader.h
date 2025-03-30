typedef struct {
    char *section;
    char *key;
    char *value;
} Cfg;

void trim_whitespace(char *str);
Cfg *parse_config(const char *filename, int *count);
