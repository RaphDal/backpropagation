// The MIT License (MIT)

// Copyright (c) 2019 Raphael DALMON

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include <math.h>
#include <fcntl.h>
#include "layer.h"

static float vec_min(float *vec, size_t n)
{
    float min = 1000;

    for (size_t i = 0; i < n; i++)
        if (vec[i] < min)
            min = vec[i];
    return (min);
}

static float vec_max(float *vec, size_t n)
{
    float max = -1000;

    for (size_t i = 0; i < n; i++)
        if (vec[i] > max)
            max = vec[i];
    return (max);
}

static void row_draw(char const *filepath, float *row, size_t len)
{
    FILE *file = fopen(filepath, "w+");
    int rows = (int)sqrtf((float)len);
    int cols = len / rows;
    float max = vec_max(row, len);
    float min = vec_min(row, len);
    float diff = fabs(max - min);

    if (!file) {
        printf("Fail to open %s\n", filepath);
        return;
    }
    fprintf(file, "P2\n%d %d\n255\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", (int)(255 * (row[i * cols + j] - min) / diff));
            if (j < cols - 1)
                fprintf(file, " ");
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void layer_draw(layer_t *layer, char const *filepath)
{
    char buff[1024];

    for (size_t i = 0; i < layer->theta->rows; i++) {
        snprintf(buff, 1024, "%s_%lu.pgm", filepath, i + 1);
        printf("Open %s\n", buff); 
        row_draw(buff, layer->theta->matrix[i] + 1, layer->theta->cols - 1);
    }

}
