---
layout: post
---

  最近在看LSTM的实现,发现有一个Blog写的比较好(http://nicodjimenez.github.io/2014/08/08/lstm.html), 将LSTM的推导原理写的比较清楚,不过也有一些缺点:
- 1.只有推导公式,没有对应的结构图,毕竟LSTM存在多种变形,我在第一次看的时候就有比较大的困惑; 
- 2.blog中我个人觉得有个地方有些问题(这点存疑),经过代码验证之后,发现修正之后的代码能够更快的收敛;

##  LSTM 结构
对于LSTM结构描述比较好的一个blog是(http://colah.github.io/posts/2015-08-Understanding-LSTMs/) ,这里也参照这个结构来进行描述.对于LSTM,主要有三个门对数据进行控制:输入门,遗忘门以及输出门.
![image](https://user-images.githubusercontent.com/5286725/36976610-306ec6a4-20b9-11e8-95b9-ec5b405d0006.png)

根据上面的图形,我们可以得到下面的公式:
![1320729427](https://user-images.githubusercontent.com/5286725/36977849-8d5f9f42-20bd-11e8-8d4a-6864192d5bc4.jpg)


## LSTM  forward propagation

LSTM forward propagation 比较简单,按照上面给的公式进行推导就可以了.详细的代码如下:

``` python
def bottom_data_is(self,input_x,s_prev=None,h_prev=None):

        if s_prev is None:
            s_prev = np.zeros_like(self.state.s)
        if h_prev is None:
            h_prev = np.zeros_like(self.state.h)

        self.s_prev = s_prev
        self.h_prev = h_prev

        xc = np.hstack((input_x,h_prev))

        self.state.i = sigmoid(np.dot(self.params.wi,xc) + self.params.bi)
        self.state.f = sigmoid(np.dot(self.params.wf,xc)+ self.params.bf)
        self.state.o = sigmoid(np.dot(self.params.wo,xc) + self.params.bo)
        self.state.g = np.tanh(np.dot(self.params.wg,xc)+ self.params.bg)

        self.state.s = self.state.g *self.state.i + self.s_prev * self.state.f
        self.state.h = self.state.s * self.state.o

        self.xc  = xc
```

## LSTM back propagation

Back propagation的主要目的是对LSTM 每个节点的参数进行更新,对应的也就是上面的公式里面的w.因此,我们需要求出de/dw的值.其中e表示的是目标函数.下面是主要的推导过程:
![701075651](https://user-images.githubusercontent.com/5286725/36986523-f9768b7a-20d4-11e8-8c9b-23a1a75f667e.jpg)

根据上面的推导,可以得到求导过程:

``` python
# back propagation
    def top_data_is(self,top_diff_h,top_diff_s):
        
        ## ds =  
        # ds = self.state.o*top_diff_h + top_diff_s
        ds = self.state.o*top_diff_h 
        do = self.state.s*top_diff_h

        di = self.state.g*ds
        dg = self.state.i*ds
        df = self.s_prev*ds
        
        di_input = sigmoid_derivative(self.state.i)*di
        df_input = sigmoid_derivative(self.state.f)*df
        do_input = sigmoid_derivative(self.state.o)*do
        dg_input = tanh_derivative(self.state.g)*dg

        ## wi_diff

        self.params.wi_diffs += np.outer(di_input,self.xc)
        self.params.wf_diffs += np.outer(df_input,self.xc)
        self.params.wo_diffs += np.outer(do_input,self.xc)
        self.params.wg_diffs += np.outer(dg_input,self.xc)


        self.params.bi_diffs += di_input
        self.params.bf_diffs += df_input
        self.params.bo_diffs += do_input
        self.params.bg_diffs += dg_input

        dxc  = np.zeros_like(self.xc)

        dxc += np.dot(self.params.wi.T,di_input)
        dxc += np.dot(self.params.wf.T,df_input)
        dxc += np.dot(self.params.wo.T,do_input)
        dxc += np.dot(self.params.wg.T,dg_input)


        self.state.bottom_diff_s = ds*self.state.f
        self.state.bottom_diff_h = dxc[self.params.x_dim:]
```

完整的代码以及对应的测试函数详见:  https://github.com/frozenxia/mini_tensor_flow/tree/master/layers

参考:
- http://colah.github.io/posts/2015-08-Understanding-LSTMs/
- http://www.cnblogs.com/liujshi/p/6159007.html
- http://nicodjimenez.github.io/2014/08/08/lstm.html

