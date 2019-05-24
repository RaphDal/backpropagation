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
    layer->values = zeros(1, neurons + 1);
    return (layer);
}

void layer_destroy(layer_t *layer)
{
    if (!layer)
        return;
    matrix_destroy(layer->values);
    matrix_destroy(layer->theta);
    free(layer);
}
