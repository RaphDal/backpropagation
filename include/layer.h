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

#ifndef LAYER_H_
#define LAYER_H_

#include <unistd.h>
#include "matrix.h"

static const size_t limit_neurons = 65536;

typedef struct layer
{
    matrix_t *theta;

    matrix_t *z;
    matrix_t *a;

    matrix_t *delta;
    matrix_t *gradiant;

    size_t neurons;
} layer_t;


/*
** layer.c
*/

layer_t *layer_create(size_t neurons);
void layer_destroy(layer_t *layer);
void layer_fill(layer_t *layer, float *data);
float *layer_get(layer_t *layer);
void layer_set_error(layer_t *layer, float *expected);


/*
** connect.c
*/

int layer_connect(layer_t *src, layer_t *dst);
void layer_init_matrix(layer_t *layer, float epsylon);


/*
** propagate.c
*/

void layer_forward(layer_t *minus, layer_t *layer);
void layer_backward(layer_t *layer, layer_t *plus);
void layer_reset_errors(layer_t *layer);


/*
** sigmoid.c
*/

void sigmoid(matrix_t *res, matrix_t *matrix);
void sigmoid_gradiant(matrix_t *res, matrix_t *matrix);


/*
** regularization.c
*/

float get_regul_cost(layer_t * layer);
void apply_gradiant(layer_t *layer, float lambda, float m);


/*
** draw.c
*/

void layer_draw(layer_t *layer, char const *filepath);


#endif /* !LAYER_H_ */
