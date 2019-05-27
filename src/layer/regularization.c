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

float get_regul_cost(layer_t * layer)
{
    matrix_t *theta = layer->theta;
    float res = 0;

    for (size_t i = 0; i < theta->rows; i++)
        for (size_t j = 0; j < theta->cols - 1; j++)
            res += theta->matrix[i][j] * theta->matrix[i][j];
    return (res);
}

void update_grad_by_theta(matrix_t *grad, matrix_t *theta, float lambda, float m)
{
    float imp = lambda / m;

    for (size_t i = 0; i < theta->rows; i++)
        for (size_t j = 0; j < theta->cols - 1; j++)
            grad->matrix[i][j] += imp * theta->matrix[i][j];
}

void apply_gradiant(layer_t *layer, float lambda, float m)
{
    matrix_t *theta = layer->theta;
    matrix_t *grad = layer->gradiant;
    float coef = lambda / m;

    update_grad_by_theta(grad, theta, 1, m);
    for (size_t i = 0; i < grad->rows; i++)
        for (size_t j = 0; j < grad->cols; j++)
            theta->matrix[i][j] -= coef * grad->matrix[i][j];
}
