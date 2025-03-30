#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "reader.h"

void trim_whitespace(char *str)
{
    if (!str || !*str) return;

    // Trim trailing spaces
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';

    // Trim leading spaces
    char *start = str;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != str) memmove(str, start, strlen(start) + 1);
}

Cfg *parse_config(const char *filename, int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    Cfg *configs = NULL;
    int capacity = 10;
    *count = 0;
    configs = malloc(capacity * sizeof(Cfg));

    char line[256];
    char *current_section = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        trim_whitespace(line);

        if (!line[0] || line[0] == ';' || line[0] == '#') continue;

        if (line[0] == '[') {
            char *end = strchr(line, ']');
            if (!end) continue;

            *end = '\0';
            free(current_section);
            current_section = strdup(line + 1);
            trim_whitespace(current_section);
        } else {
            char *comment = strpbrk(line, ";#");
            if (comment) *comment = '\0';

            char *eq = strchr(line, '=');
            if (!eq) continue;

            *eq = '\0';
            char *key = line, *value = eq + 1;

            trim_whitespace(key);
            trim_whitespace(value);

            // Remove quotes
            if (value[0] == '"' && value[strlen(value)-1] == '"') {
                memmove(value, value+1, strlen(value)-2);
                value[strlen(value)-1] = '\0';
            }

            if (*count >= capacity) {
                capacity *= 2;
                configs = realloc(configs, capacity * sizeof(Cfg));
            }

            configs[*count] = (Cfg){
                .section = current_section ? strdup(current_section) : NULL,
                .key = strdup(key),
                .value = strdup(value)
            };
            (*count)++;
        }
    }

    fclose(file);
    return configs;
}
