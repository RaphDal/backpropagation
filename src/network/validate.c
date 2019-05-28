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

#include "network.h"

void max_vector(float *vec, size_t size, size_t *index)
{
    float max = -1;

    for (size_t i = 0; i < size; i++)
        if (vec[i] > max) {
            *index = i;
            max = vec[i];
        }
}

int verify(network_t *network, float *input, float *expected)
{
    float *out = network_predict(network, input);
    size_t index_expected;
    size_t index_output;

    max_vector(out, network->output->neurons, &index_output);
    max_vector(expected, network->output->neurons, &index_expected);
    return (index_expected == index_output);
}

void validate(network_t *network, matrix_t *input,
matrix_t *expected)
{
    float m = input->rows;
    int score = 0;

    for (size_t t = 0; t < input->rows; t++) {
        score += verify(network, input->matrix[t], expected->matrix[t]);
    }
    printf("Result : %d/%lu (%d%)\n", score, input->rows, 100 * score / (int)input->rows);
}
