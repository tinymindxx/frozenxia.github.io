---
layout: post
title: Trapping Rain Water  
tags: java algorithm leetcode
categories: algorithm
---

这道题目之前一直没有独立的做出来，这次自己想出来的，很开心。题目的意思如下图所示，基本思路是首先从左往右进行遍历，从x开始，找到比x大的第一个值，然后计算他们之间能够存储多少水，然后从右往左进行遍历，同样的办法，找到能够存储水的数量，这个地方需要主要一下啊，如果找到了相等的怎么办，比如最左和最有相等，并且都是最高点，所以就需要在两次遍历的任意一次遍历中，取等号的情况就可以了。
![runtime][runtime]

代码如下：
```java
public class Solution {
	public int trap(int[] height) {
		if(height.length < 2) return 0;
		int tmp = height[0];
		int last = 0;
		int sum = 0;
		for(int i = 1;i < height.length;i ++){
			if(height[i] >= tmp){
				sum += cal(last,i,height);
				tmp = height[i];
				last = i;
			}
		}
		tmp = height[height.length-1];
		last = height.length -1;
		for(int i = height.length-2;i >=0;i --){
			if(height[i] > tmp){
				sum += cal(i,last,height);
				last = i;
				tmp = height[i];
			}
		}
		return sum;
	}
	public int cal(int is,int ie,int []height){
		int h = Math.min(height[is],height[ie]);
		int sum = h * (ie-is-1);
		for(int i = is+1 ;i < ie;i ++){
			sum -= height[i];
		}
		return sum;
	}
}

```

[runtime]: {{"/rainwatertrap.png" | prepend: site.imgrepo }}

