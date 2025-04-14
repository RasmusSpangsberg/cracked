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

#include "matrix.h"


void init_model(){
    // 1. what type of weight initialization? (actually, i'd really like to implement
    // a few different ones and test their performance on MNIST)
    // 2. what is diff between conv2d network and just a 2d convolution?
}


void xavier_init(){}

void he_init(){
    // this should work better with ReLU activations than xavier initialization
}

void lecun_init(){}
void glorot_init(){}

int predict(Matrix *m){
    
}

int main(){

}