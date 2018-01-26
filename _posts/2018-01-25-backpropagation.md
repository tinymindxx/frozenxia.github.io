---
layout: post
title : Neural network - training INS using the back propagation algorithm
---

# Neural network - introduction

## The principle of learning a multilayer neural network using the back propagation algorithm
Consider the learning process of a neural network using the backpropagation algorithm . 
To illustrate this process, we use a neural network consisting of three layers and having two inputs and one output:
here, the author considers the layers differently and does not take into account the "2 neurons" of the input layer

![sample post]({{site.baseurl}}/images/2018-01-25-bp/img01.gif)
Each neuron consists of two elements. 
The first element - dendrites - adds weighting factors to the input signals. 
The second element - the body - realizes a non-linear function, the so-called. function of activation of a neuron. 
The signal e is the weighted sum of the input signals

``` c 
у = f (е)
```

Output signal of the neuron. 
![sample post]({{site.baseurl}}/images/2018-01-25-bp/img01b.gif)
To train a neural network, we must prepare training data (examples). 
In our case, the training data consists of the input signals (x1 and x2) and the desired result z. 
Training is a sequence of iterations (repetitions). 
In each iteration, the weights of the neurons are adjusted using the new data from the training examples. 
The change in the weight coefficients is the essence of the algorithm described below. 

Each step of training begins with the impact of input signals from the training examples. After that, we can determine the values ​​of the output signals for all neurons in each layer of the network. 
The illustrations below show how the signal propagates through the network. 
SymbolsW (Xm) n represent the connection weight between the network input Xm and the neuron n in the input layer. 
The symbols y (n) represent the output signal of the neuron n . 




Propagation of a signal through a hidden layer. 
The symbols Wmn represent the weight factors of the links between the output of the neuron m and the input of the neuron n in the next layer. 


Propagation of the signal through the output layer 

In the next step of the algorithm, the output signal of the network y is compared with the desired output signal z , which is stored in the training data.
The difference between these two signals is called the error d of the output layer of the network. 


It is impossible to directly calculate the error signal for internal neurons, because the output values ​​of these neurons are unknown. 
For many years, an effective method for learning a multi-layer network was unknown. 
Only in the middle of the eighties the algorithm for back propagation of the error was developed. 
The idea is to propagate the error signal d (computed in the learning step) back to all the neurons whose output signals were incoming for the last neuron. 


The weighting coefficients Wmn, used for back propagation of the error, are equal to the same coefficients that were used during the calculation of the output signal. Only the direction of the data flow changes (signals are transmitted from the output to the input). 
This process is repeated for all layers of the network. If the error has come from several neurons, it is summarized: 



When the magnitude of the signal error is calculated for each neuron, you can adjust the weights of each neuron input (dendrite) node. 
In the formulas below df (e) / de - is a derivative of the neuron activation function (whose weighting factors are adjusted).
as remember, for the activation function of the sigmoid type 

           1
S(x) = -----------
       1 + exp(-x)
the derivative is expressed in terms of the function itself:
S'(x) = S(x)*(1 - S(x))
, which significantly reduces the computational complexity of the method of back propagation of the error. 

The computation of the derivative is necessary, because to correct the weights in the learning of the ANN using the back propagation algorithm, we use the methodgradient descent.








The coefficient h affects the speed of learning the network. 
There are several methods for selecting this parameter. 
The first way is to start the learning process with a large value of the parameter h. During correction of weight coefficients, the parameter is gradually reduced. 
The second is a more complex method of training, begins with a small value of the parameter h. In the learning process, the parameter increases, and then decreases again at the final stage of training. 
Beginning of the educational process with a low value of the parameter h makes it possible to determine the sign of the weighting coefficients. 