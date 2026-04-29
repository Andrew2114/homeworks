#include "utils.h"
#include <ctype.h>
#include <string.h>

void trim(char* str)
{
    if (!str)
        return;

    int i = 0, j = strlen(str) - 1;
    while (isspace((unsigned char)str[i]))
        i++;
    while (j >= i && isspace((unsigned char)str[j]))
        j--;

    int len = j - i + 1;
    for (int k = 0; k < len; k++) {
        str[k] = str[i + k];
    }
    str[len] = '\0';
}

int is_valid_iata_code(const char* code)
{
    if (!code)
        return 0;
    int len = strlen(code);
    if (len != 3)
        return 0;

    for (int i = 0; i < len; i++) {
        if (!isalpha((unsigned char)code[i]) && !isdigit((unsigned char)code[i])) {
            return 0;
        }
    }
    return 1;
}
