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
#include <string.h>
#include "network.h"
#include "layer.h"
#include "back_errors.h"

network_t *network_create(void)
{
    network_t *network = malloc(sizeof(network_t));

    if (!network)
        return (error_ptr(MALLOC_FAILED));
    network->layers = calloc(limit_layers, sizeof(layer_t *));
    if (!network->layers) {
        free(network);
        return (error_ptr(MALLOC_FAILED));
    }
    network->nb_layers = 0;
    network->input = NULL;
    network->output = NULL;
    return (network);
}

void network_destroy(network_t *network)
{
    if (!network)
        return;
    for (size_t i = 0; i < network->nb_layers; i++)
        layer_destroy(network->layers[i]);
    free(network->layers);
    free(network);
}
