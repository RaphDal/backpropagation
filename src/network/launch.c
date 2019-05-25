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

void network_forward(network_t *network)
{
    for (size_t i = 1; i < network->nb_layers; i++)
        layer_forward(network->layers[i - 1], network->layers[i]);
}

void network_backward(network_t *network)
{
    ssize_t lim = (ssize_t)network->nb_layers - 2;
    for (ssize_t i = lim; i >= 0; i--)
        layer_backward(network->layers[i], network->layers[i + 1]);
}

float *network_predict(network_t *network, float *data)
{
    if (!network || !network->input)
        return (NULL);
    layer_fill(network->input, data);
    network_forward(network);
    return (layer_get(network->output));
}

void network_self_train(network_t *network, float *input, float *output)
{
    if (!network || !network->input || !network->output)
        return;
    layer_fill(network->input, input);
    network_forward(network);
    layer_set_error(network->output, output);
    network_backward(network);
}

void network_train(network_t *network, float **inputs,
float **expecteds, size_t data_size)
{
    for (size_t i = 0; i < network->nb_layers - 1; i++)
        layer_reset_errors(network->layers[i]);
    for (size_t i = 0; i < data_size; i++)
        network_self_train(network, inputs[i], expecteds[i]);
}