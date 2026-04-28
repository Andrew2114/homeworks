#include "utils.h"
#include <ctype.h>
#include <stdlib.h>

int is_number(const char* str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    int i = 0;
    if (str[0] == '-') {
        i++;
        if (str[i] == '\0')
            return 0;
    }

    int has_dot = 0;
    int has_digit = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            if (has_dot || i == 0 || (i == 1 && str[0] == '-')) {
                return 0;
            }
            has_dot = 1;
        } else if (isdigit(str[i])) {
            has_digit = 1;
        } else {
            return 0;
        }
    }

    return has_digit;
}
