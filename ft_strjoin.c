#include <stdlib.h>

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

char *ft_strjoin(char const *s1, char const *s2)
{
    if (!s1 || !s2)
        return NULL;

    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *new_str = malloc(len1 + len2 + 1); // +1 na '\0'

    if (!new_str)
        return NULL;

    size_t i = 0;

    // kopiowanie s1
    for (; i < len1; i++)
        new_str[i] = s1[i];

    // kopiowanie s2
    for (size_t j = 0; j < len2; j++, i++)
        new_str[i] = s2[j];

    new_str[i] = '\0';
    return new_str;
}

