#include <ctype.h>
#include <stdio.h>

unsigned int ft_atoi_hex(const char *str)
{
    unsigned int result = 0;
    int i = 0;

    // pomijamy prefix "0x" lub "0X"
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        i = 2;

    while (str[i])
    {
        char c = str[i];
        unsigned int value;

        if (c >= '0' && c <= '9')
            value = c - '0';
        else if (c >= 'a' && c <= 'f')
            value = 10 + (c - 'a');
        else if (c >= 'A' && c <= 'F')
            value = 10 + (c - 'A');
        else
            break; // koniec jeśli znak nie jest hex

        result = result * 16 + value;
        i++;
    }

    return result;
}

