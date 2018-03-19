---
layout: post
---

##  RNN模型

### 状态转移函数
 
![image](https://user-images.githubusercontent.com/5286725/37567159-d4a4b4c4-2afd-11e8-8cc1-d003158ae430.png)

### 输出值

![image](https://user-images.githubusercontent.com/5286725/37567472-7b0b6dae-2b02-11e8-926c-7383d074e2e9.png)



## RNN算法实现(Tensorflow版本)
```python
import tensorflow as tf

class RnnModel():
    def __init__(self,batch_size,num_steps,num_class,state_size,learning_rate):
        self.input_x = tf.placeholder(dtype=tf.int32,shape=(batch_size,num_steps),name='input_x')
        self.input_y = tf.placeholder(dtype=tf.int32,shape=(batch_size,num_steps),name='input_y')
        self.init_state = tf.zeros([batch_size,state_size],tf.float32)
        
        print(self.input_x,self.input_y)

        # 输入的数据类型(batch_size,数据长度)
        x_one_hot = tf.one_hot(self.input_x,num_class)

        # 将数据按照固定长度拆分成(batch_size,num_classes)
        rnn_inputs = tf.unstack(x_one_hot,axis=1)
  
        with tf.variable_scope('rnn_cell'):
            W = tf.get_variable('W',dtype=tf.float32,shape=[num_class+state_size,state_size])
            b = tf.get_variable('b',dtype=tf.float32,shape=[state_size],initializer=tf.constant_initializer(0))

        def rnn_cell(rnn_input,state):
            with tf.variable_scope('rnn_cell', reuse=True):
                W = tf.get_variable('W',dtype=tf.float32,shape=[num_class+state_size,state_size])
                b = tf.get_variable('b',dtype=tf.float32,shape=[state_size],initializer=tf.constant_initializer(0))
            
            return tf.tanh(tf.matmul(tf.concat([rnn_input, state], 1),W)+b) 
        
        state = self.init_state
        rnn_outputs = []
        for rnn_input in rnn_inputs:
            state = rnn_cell(rnn_input,state)
            rnn_outputs.append(state)
        self.final_state = rnn_outputs[-1]


        with tf.variable_scope('softmax'):
            W = tf.get_variable('W',dtype=tf.float32,shape=[state_size,num_class])
            b = tf.get_variable('b',dtype=tf.float32,shape=[num_class],initializer=tf.constant_initializer(0))
            logits = [tf.matmul(rnn_output,W)+b for rnn_output in rnn_outputs]

        self.predictons = [tf.nn.softmax(logit) for logit in logits]
        y_as_lsit = tf.unstack(self.input_y,num=num_steps,axis=1)
 #       print('y_as_list \n\n')
#        print(y_as_lsit)
       # 这个地方采用的是sparse_softmax_cross_entropy_with_logits,因此label不需要进行one-hot编码
        self.losses = [tf.nn.sparse_softmax_cross_entropy_with_logits(labels=label,logits=logit) for label,logit in zip(y_as_lsit,logits)]
        self.total_loss = tf.reduce_mean(self.losses)
        self.train_step = tf.train.AdagradOptimizer(learning_rate).minimize(self.total_loss)
```

### 对应的测试代码:

这里需要说一下测试代码的思路,对于序列长度为T的 _x_ ,对应的输出长度为T的 _y_ ,如果我们测试的时候有500个样本,那么最简单的方式是将500个 _x1_ 与 500个 _y1_ 对应起来,  500个 _x2_  与500个 _y2_ 对应起来,以此类推, _xt_ 与 _yt_ 对应. 这样 _xi_ 的输出与 _yi_ 之间就可以计算delta,从而进行优化.


``` python
import numpy as np
import tensorflow as tf 
from rnn_layer import RnnModel

# import matplotlib.pyplot as plt

import matplotlib.pyplot as plt

num_steps = 5
batch_size = 200
num_class = 2
state_size = 4
learning_rate=0.1

def gen_data(size=10000000):
    X= np.array(np.random.choice(2,size=(size,)))
    # print(X)
    Y= []
    for i in range(size):
        threshold = 0.5
        if X[i-3] == 1:
            threshold += 0.5
        if X[i-8] == 1:
            threshold -= 0.25
        
        if np.random.rand() > threshold:
            Y.append(0)
        else:
            Y.append(1)
    return X,Y

def gen_batch(raw_data,batch_size,num_steps):
    raw_x,raw_y = raw_data
    data_len = len(raw_x)
    # print(data_len)

    batch_partiton_length = int(data_len/batch_size)
    data_x = np.zeros(shape=(batch_size,batch_partiton_length),dtype=np.int32)
    data_y = np.zeros(shape=(batch_size,batch_partiton_length),dtype=np.int32)

    for i in range(batch_size):
        data_x[i] = raw_x[batch_partiton_length*i:batch_partiton_length*(i+1)]
        data_y[i] = raw_y[batch_partiton_length*i:batch_partiton_length*(i+1)]
    
    epoch_size = int(batch_partiton_length/num_steps)
    # print(epoch_size)
    for i in range(epoch_size):
        yield (data_x[:,num_steps*i:num_steps*(i+1)],data_y[:,num_steps*i:num_steps*(i+1)])


def gen_epoches (n,num_steps):
    for i in range(n):
        yield gen_batch(gen_data(),batch_size,num_steps)

def train_network(num_epochs,num_steps,state_size=4,verbos=True):
    rnn_model = RnnModel(batch_size,num_steps,num_class,state_size,learning_rate)
    train_losses=[]
    with  tf.Session() as session:
        session.run(tf.global_variables_initializer())
        
        for idx ,epoch in enumerate(gen_epoches(num_epochs,num_steps)):
            training_loss = 0
            training_state = np.zeros((batch_size,state_size))
            if verbos:
                print('\nEPOCH',idx)
            for step,(X,Y) in enumerate(epoch):
                # print(X.shape)
                # print(step)
                y_as_list,tr_loss,training_loss_,training_state,_=session.run([rnn_model.y_as_lsit,rnn_model.losses,rnn_model.total_loss,rnn_model.final_state,rnn_model.train_step],feed_dict={rnn_model.input_x:X,rnn_model.input_y:Y,rnn_model.init_state:training_state})
                training_loss += training_loss_
                # print(y_as_list,'\n\n')
                if step %100 == 0 and step > 0:
                    if verbos:
                        print('average loss at step ',step ,'  ' ,training_loss_ ,' for last 100 steps ',training_loss/100)
                    train_losses.append(training_loss)
                    training_loss = 0.0
                # break
    return train_losses

        # pass

# print(gen_data(10))
training_loss = train_network(1,num_steps)
plt.plot(training_loss)
plt.show()

```


## RNN算法实现 (Numpy版本)



## 参考
-  https://r2rt.com/recurrent-neural-networks-in-tensorflow-i.html