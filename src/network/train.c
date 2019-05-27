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
#include "network.h"

void network_forward(network_t *network, float *input);

void network_backward(network_t *network, float *expected)
{
    ssize_t lim = (ssize_t)network->nb_layers - 2;

    layer_set_error(network->output, expected);
    for (ssize_t i = lim; i >= 0; i--)
        layer_backward(network->layers[i], network->layers[i + 1]);
}

float network_self_train(network_t *network, float *input, float *output,
size_t training_size)
{
    float cost = 0;

    network_forward(network, input);
    network_backward(network, output);
    for (size_t j = 0; j < network->output->a->cols - 1; j++)
        cost += -output[j] * log(network->output->a->matrix[0][j]) - (1 - output[j]) * log(1 - network->output->a->matrix[0][j]);
    cost /= training_size;
    if (isinf(cost))
        return (0);
    if (isnan(cost))
        return (0);
    return (cost);
}

void network_epoch(network_t *network, matrix_t *input,
matrix_t *expected, size_t step)
{
    float j = 0;
    float regul = 0;
    float m = input->rows;
    char buff[101] = {0};

    setbuf(stdout, NULL);
    for (size_t i = 0; i < network->nb_layers - 1; i++)
        layer_reset_errors(network->layers[i]);
    for (size_t i = 0; i < m; i++) {
        if ((i+1)%((int)(m / 100)) == 0) {
            buff[(int)(((i+1) * 100) / m) - 1] = '|';
            printf("[%-100s] %lu/%lu (%f)\r", buff, i+1, input->rows, j);
        }
        j += network_self_train(network, input->matrix[i],
        expected->matrix[i], input->rows);
    }
    for (size_t i = 0; i < network->nb_layers - 1; i++) {
        regul += get_regul_cost(network->layers[i]);
        apply_gradiant(network->layers[i], 1, input->rows);
    }
    j += regul * (1 / (2 * m));
    printf("\nFinal cost : %f\n", j);
}

void network_train(network_t *network, matrix_t *input,
matrix_t *expected, size_t epochs)
{
    for (size_t step = 0; step < epochs; step++)
        network_epoch(network, input, expected, step);
}
