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

#include <stdlib.h>
#include <unistd.h>
#include "layer.h"
#include "back_errors.h"
#include "matrix.h"

layer_t *layer_create(size_t neurons)
{
    layer_t *layer;

    if (!neurons)
        return (error_ptr(NEGATIVE_NEURONS));
    if (neurons >= limit_neurons)
        return (error_ptr(TOO_MUCH_NEURONS));
    layer = malloc(sizeof(layer_t));
    if (!layer)
        return (error_ptr(MALLOC_FAILED));
    layer->theta = NULL;
    layer->gradiant = NULL;
    layer->delta = zeros(neurons + 1, 1);
    layer->delta->rows--;
    layer->z = zeros(1, neurons);
    layer->a = custom(1, neurons + 1, 1);
    layer->neurons = neurons;
    return (layer);
}

void layer_destroy(layer_t *layer)
{
    if (!layer)
        return;
    matrix_destroy(layer->delta);
    matrix_destroy(layer->theta);
    matrix_destroy(layer->a);
    matrix_destroy(layer->z);
    matrix_destroy(layer->gradiant);
    free(layer);
}

void layer_fill(layer_t *layer, float *data)
{
    for (size_t i = 0; i < layer->neurons; i++)
        layer->a->matrix[0][i] = data[i];
}

float *layer_get(layer_t *layer)
{
    float *res;

    if (!layer)
        return (NULL);
    if (!(res = malloc(sizeof(float) * (layer->neurons))))
        return (NULL);
    for (size_t i = 0; i < layer->neurons; i++)
        res[i] = layer->a->matrix[0][i];
    return (res);
}

void layer_set_error(layer_t *layer, float *expected)
{
    for (size_t i = 0; i < layer->neurons; i++)
        layer->delta->matrix[i][0] = layer->a->matrix[0][i] - expected[i];
}