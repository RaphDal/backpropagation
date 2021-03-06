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
    matrix_t *input = matrix_import_mat("inputs.mat");
    matrix_t *expecteds = matrix_import_mat("expecteds.mat");

    network_t *network = network_create();

    network_add(network, 400);
    network_add(network, 25);
    network_add(network, 10);


    /*matrix_t *theta_1 = matrix_import_mat("theta_1");
    network->layers[0]->theta = theta_1;

    matrix_t *theta_2 = matrix_import_mat("theta_2");
    network->layers[1]->theta = theta_2;*/

    validate(network, input, expecteds);
    network_train(network, input, expecteds, 50);
    validate(network, input, expecteds);
    
    return (0);
}