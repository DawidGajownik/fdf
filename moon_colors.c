//
// Created by dawid-gajownik on 22.11.2025.
//

void	set_moon_color(unsigned char *pixel, int map_height)
{
        int shade;

        // normalizacja: przyjmijmy wysokość w zakresie -8000 .. 8000
        // i przeskalujmy do 0..255
        if (map_height < -8000)
                map_height = -8000;
        if (map_height > 8000)
                map_height = 8000;

        shade = (map_height + 8000) * 255 / 16000;

        // kolor w formacie 0xFFRRGGBB (pełna alfa)
        *(unsigned int *)pixel = (0xFF << 24)
                | (shade << 16)
                | (shade << 8)
                | (shade);
}
