#include <stdlib.h>
#include <stdio.h>

char *ft_ftoa(float n, int precision)
{
    char *str;
    int int_part = (int)n;
    float frac_part = n - int_part;
    if (frac_part < 0) frac_part = -frac_part;
    if (int_part < 0) int_part = -int_part;

    // bufor na liczby: maksymalnie 50 znaków
    str = malloc(50);
    if (!str) return NULL;

    char *ptr = str;

    // obsługa znaku
    if (n < 0) *ptr++ = '-';

    // zapis części całkowitej
    sprintf(ptr, "%d", int_part);

    // przesunięcie wskaźnika do końca części całkowitej
    while (*ptr) ptr++;

    if (precision > 0)
    {
        *ptr++ = '.';

        for (int i = 0; i < precision; i++)
        {
            frac_part *= 10;
            int digit = (int)frac_part;
            *ptr++ = '0' + digit;
            frac_part -= digit;
        }
    }

    *ptr = '\0';
    return str;
}

