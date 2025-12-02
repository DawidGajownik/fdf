#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Użycie: %s wejscie.bmp wyjscie.txt tryb(0=wysokosc,1=kolor)\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[3]); // 0 = wysokość, 1 = kolor

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("Nie mogę otworzyć pliku BMP"); return 1; }

    FILE *out = fopen(argv[2], "w");
    if (!out) { perror("Nie mogę otworzyć pliku wyjściowego"); fclose(f); return 1; }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(fileHeader), 1, f);
    fread(&infoHeader, sizeof(infoHeader), 1, f);

    if (fileHeader.bfType != 0x4D42) { fprintf(stderr,"To nie jest BMP!\n"); return 1; }
    if (infoHeader.biBitCount != 24 || infoHeader.biCompression != 0) {
        fprintf(stderr,"Obsługiwane są tylko BMP 24-bit bez kompresji.\n"); return 1;
    }

    int width  = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int rowPadded = (width * 3 + 3) & (~3);

    uint8_t *row = malloc(rowPadded);
    char **lines = malloc(sizeof(char*) * height);

    for (int y = height - 1; y >= 0; y--) {
        fread(row, rowPadded, 1, f);

        lines[y] = malloc(width * 20); // duży bufor na zapis
        int offset = 0;

        for (int x = 0; x < width; x++) {
            uint8_t b = row[x*3 + 0];
            uint8_t g = row[x*3 + 1];
            uint8_t r = row[x*3 + 2];

            if (mode == 0) {
                // tryb wysokości: biały=0, czarny=5000
                double L = 0.2126*r + 0.7152*g + 0.0722*b;
                int height_val = (int)(5000.0 * (1.0 - (L / 255.0)));
                offset += sprintf(lines[y]+offset, "%d", height_val);
            } else {
                // tryb kolor: zapis HEX 0xRRGGBB
                offset += sprintf(lines[y]+offset, "0x%02X%02X%02X", r, g, b);
            }

            if (x < width - 1) offset += sprintf(lines[y]+offset, " ");
        }
    }

    // wypisujemy linie (od góry do dołu)
    for (int i = 0; i < height; i++) {
        fprintf(out, "%s\n", lines[i]);
        free(lines[i]);
    }

    free(lines);
    free(row);
    fclose(f);
    fclose(out);

    return 0;
}

