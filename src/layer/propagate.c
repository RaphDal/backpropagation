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
#include "layer.h"


/*
    Layer layer got values from minus

    o               o
    o               o
    o               o
                    o

    x1 = [1, 3]     x2 = [1, 4]
    theta1 = [3, 4]
*/

void layer_forward(layer_t *minus, layer_t *layer)
{
    if (!minus || !layer)
        return;
    this_matrix_mul(layer->z, minus->theta, minus->values);
    for (size_t i = 0; i < layer->z->rows; i++)
        layer->z->matrix[i][0] += layer->bias[i];
    this_matrix_sigmoid(layer->values, layer->z);
}

void layer_backward(layer_t *layer, layer_t *plus)
{
    matrix_t *transposed_a = matrix_transpose(layer->values);
    matrix_t *time;
    float sig;

    this_matrix_mul_transposed(layer->delta, layer->theta, plus->delta);
    for (size_t i = 0; i < layer->delta->rows; i++) {
        sig = 1 / (1 + expf(-layer->z->matrix[i][0]));
        layer->delta->matrix[i][0] *= sig * (1 - sig);
    }
    time = matrix_mul(plus->delta, transposed_a);
    this_matrix_add(layer->sum_delta, layer->sum_delta, time);
    matrix_destroy(time);
}

void layer_reset_errors(layer_t *layer)
{
    for (size_t i = 0; i < layer->sum_delta->rows; i++)
        for (size_t j = 0; j < layer->sum_delta->cols; j++)
            layer->sum_delta->matrix[i][j] = 0;
}