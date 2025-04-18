/*
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 10, kernel_size=5)
        self.conv2 = nn.Conv2d(10, 20, kernel_size=5)
        self.conv2_drop = nn.Dropout2d()
        self.fc1 = nn.Linear(320, 50)
        self.fc2 = nn.Linear(50, 10)

    def forward(self, x):
        x = F.relu(F.max_pool2d(self.conv1(x), 2))
        x = F.relu(F.max_pool2d(self.conv2_drop(self.conv2(x)), 2))
        x = x.view(-1, 320)
        x = F.relu(self.fc1(x))
        x = F.dropout(x, training=self.training)
        x = self.fc2(x)
        return F.log_softmax(x)
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

void init_model(){
    // 1. what type of weight initialization? (actually, i'd really like to implement
    // a few different ones and test their performance on MNIST)
    // 2. what is diff between conv2d network and just a 2d convolution?

    // maybe start with a simple feed forward network?
}


// https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
// TODO call sample_from_norm_distr and say using box-muller trans
void box_muller_transform(){
    srand(time(NULL));
    float u1 = (float)rand() / RAND_MAX;
    float u2 = (float)rand() / RAND_MAX;

    float z1 = sqrt(-2 * log(u1)) * cos(2 * 3.14 * u2);
    float z2 = sqrt(-2 * log(u1)) * sin(2 * 3.14 * u2);
}

// TODO how to sample from distribution
void sample_from_normal_distribution(){
    srand(time(NULL));
    
    for (int i = 0; i < 5; i++){
        int r = rand() % 100;
        printf("%i\n", r);
    }

    // TODO sample
}

void zero_init(Matrix *m){
    fill_zero_matrix(m);
}

void lecun_init(Matrix *m){
    // sample each entry independently from a distribution with 0 mean and variance 1/n_{l-1}
}

void xavier_init(Matrix *m){
    // or Glorot initialization

}

void he_init(Matrix *m){
    // or Kaiming initialization
    // this should work better with ReLU activations than xavier initialization
}

void glorot_init(Matrix *m){}

int predict(Matrix *m){
    
}