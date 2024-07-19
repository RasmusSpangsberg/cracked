#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matrix.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t value;
} TiffTag;
#pragma pack(pop)

void write_tiff_header(FILE *fp, uint32_t width, uint32_t height, uint32_t offset_to_ifd, uint32_t offset_to_image_data) {
    // TIFF Header (Little Endian)
    uint8_t header[8] = {
        0x49, 0x49,            // Byte order: Little Endian
        0x2A, 0x00,            // TIFF identifier
        0x08, 0x00, 0x00, 0x00 // Offset to first IFD (8 bytes from start of file)
    };
    fwrite(header, 1, 8, fp);

    // Image File Directory (IFD)
    uint16_t num_entries = 9;
    fwrite(&num_entries, 2, 1, fp);

    // Write IFD entries
    TiffTag tags[9] = {
        { 256, 4, 1, width },                 // ImageWidth
        { 257, 4, 1, height },                // ImageLength
        { 258, 3, 1, 8 },                     // BitsPerSample
        { 259, 3, 1, 1 },                     // Compression (None)
        { 262, 3, 1, 1 },                     // PhotometricInterpretation (BlackIsZero)
        { 273, 4, 1, offset_to_image_data },  // StripOffsets
        { 277, 3, 1, 1 },                     // SamplesPerPixel
        { 278, 4, 1, height },                // RowsPerStrip
        { 279, 4, 1, width * height }         // StripByteCounts
    };

    // Write IFD entries
    for (int i = 0; i < num_entries; ++i) {
        fwrite(&tags[i], 1, sizeof(TiffTag), fp);
    }

    // Offset to next IFD (0 means no more IFDs)
    uint32_t next_ifd = 0;
    fwrite(&next_ifd, 4, 1, fp);
}

int write_tiff(Matrix *m) {
    const size_t image_size = m->cols * m->rows; // 1 byte per pixel (greyscale)

    // Allocate memory for image data
    uint8_t *image_data = (uint8_t*)malloc(image_size);
    if (!image_data) {
        perror("Failed to allocate memory for image data");
        return 1;
    }

    for (int i = 0; i < image_size; i++){
        image_data[i] = m->data[i];
    }

    // Open the file for writing
    FILE *fp = fopen("output.tiff", "wb");
    if (!fp) {
        free(image_data);
        perror("Failed to open file");
        return 1;
    }

    // Calculate offsets
    uint32_t offset_to_ifd = 8; // TIFF header size
    uint32_t offset_to_image_data = offset_to_ifd + 2 + 9 * 12 + 4;

    // Write TIFF header and IFD
    write_tiff_header(fp, m->cols, m->rows, offset_to_ifd, offset_to_image_data);

    // Write image data
    fwrite(image_data, 1, image_size, fp);

    // Clean up
    fclose(fp);
    free(image_data);

    return 0;
}

/*
int main(){
    write_tiff(600, 800);
}*/