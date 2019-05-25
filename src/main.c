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

#include "backpropagation.h"
#include <unistd.h>
int main(void)
{
    network_t *network = network_create();

    network_add(network, 6);
    network_add(network, 8);
    network_add(network, 5);

    float **inputs = malloc(sizeof(float *) * 1);
    inputs[0] = malloc(sizeof(float) * 6);
    for (size_t i = 0; i < 6; i++)
        inputs[0][i] = i;
    float **outputs = malloc(sizeof(float *) * 1);
    outputs[0] = malloc(sizeof(float) * 5);
    for (size_t i = 0; i < 5; i++)
        outputs[0][i] = i;

    network_train(network, inputs, outputs, 1);
    
    return (0);
}