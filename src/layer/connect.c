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
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include <math.h>
#include "layer.h"
#include "back_errors.h"

void layer_init_matrix(layer_t *layer, float epsylon)
{
    float **matrix = layer->theta->matrix;
    size_t rows = layer->theta->rows;
    size_t cols = layer->theta->cols;
    float max = 0;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = ((float)(rand()%100))/100 *
            (2 * epsylon) - epsylon;
        }
    }
}

int layer_connect(layer_t *src, layer_t *dst)
{
    matrix_t *matrix;

    if (!src || !dst)
        return (-1);
    matrix = custom(dst->z->rows, src->values->rows, 0);
    src->sum_delta = zeros(dst->z->rows, src->z->rows);
    if (!matrix)
        return (-1);
    src->theta = matrix;
    return (0);
}
