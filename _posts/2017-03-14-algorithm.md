---
layout: post
title: algorithm
tags: algorithm
categories: algorithm
---
### 树
* 红黑树是一个很nice的设计，在先前的学习中，一直很好奇如何想出红黑树这样精妙的实现的，以及红黑树为什么要求保持黑节点平衡。这次从algorithm里面看到了很好的解释，红黑树本质上是一个2-3树的实现，当然也可以是一个2-3-4树的实现。而2-3树在构成的过程中就可以保证所有的空指针到root节点的距离相等。对应到红黑树上面，
