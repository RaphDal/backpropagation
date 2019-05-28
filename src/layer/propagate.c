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

void layer_forward(layer_t *minus, layer_t *layer)
{
    float tot = 0;

    this_matrix_mul_nt(layer->z, minus->a, minus->theta);
    layer->a->cols--;
    for (size_t i = 0; i < layer->a->rows; i++)
        layer->a->matrix[i]++;
    this_matrix_sigmoid(layer->a, layer->z);
    layer->a->cols++;
    for (size_t i = 0; i < layer->a->rows; i++)
        layer->a->matrix[i]--;
    for (size_t i = 0; i < layer->a->cols - 1; i++)
        tot += layer->a->matrix[0][i];
}

void layer_backward(layer_t *layer, layer_t *plus)
{
    layer->delta->matrix--;
    layer->delta->rows++;

    this_matrix_mul_transposed(layer->delta, layer->theta, plus->delta);
    
    layer->delta->matrix++;
    layer->delta->rows--;


    sigmoid_gradiant(layer->delta, layer->z);

    this_matrix_add_mul(layer->gradiant, plus->delta, layer->a);
}

void layer_reset_errors(layer_t *layer)
{
    for (size_t i = 0; i < layer->gradiant->rows; i++)
        for (size_t j = 0; j < layer->gradiant->cols; j++)
            layer->gradiant->matrix[i][j] = 0;
}