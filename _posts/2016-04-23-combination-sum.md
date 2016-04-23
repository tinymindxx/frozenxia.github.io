---
layout: post
title: combination sum
tags: java algorithm 
categories: algorithm
---
这道题有几个变形，每个元素是否允许多次使用会导致比较细微的差别。
对于combination-I，其主要思路还是进行递归搜索。代码如下：
```java
public class Solution {
	public List<List<Integer>> combinationSum(int[] candidates, int target) {
		Arrays.sort(candidates);
		List<List<Integer>> retList = new ArrayList<List<Integer>>();
		dfs(candidates,0,target,retList,new ArrayList<Integer>());
		return retList;
	}
	void dfs(int []candidates,int n,int target,List<List<Integer>> total,List<Integer> current){
		if(target == 0){
			total.add(new ArrayList<Integer>(current));
			return;
		}
		for(int i =n;i <candidates.length && candidates[i] <= target;i ++){
			current.add(candidates[i]);
			dfs(candidates,i,target-candidates[i],total,current);
			current.remove(current.size()-1);
		}
	}
}
```

第二个变种，每个元素只能使用一次，因此会出现重复的情况，那么就需要去掉重复的情况，去重有两种解决办法，一种是在进行递归搜索的时候，避免重复情况发送，在递归之前，需要判断 i== n || candidates[i] != candidates[i-1];另一种解决思路就是在递归完成之后，将递归得到的解添加进最终解空间的时候去重，可以使用Set来存储这些解。下面是以Set作为解空间存储区的思路

```java

public class Solution {
	public List<List<Integer>> combinationSum2(int[] candidates, int target) {
		Arrays.sort(candidates);
		Set<List<Integer>> retList = new HashSet<List<Integer>>();
		dfs(candidates,0,target,retList,new ArrayList<Integer>());
		return new ArrayList<List<Integer>>(retList);
	}
	void dfs(int []candidates,int n,int target,Set<List<Integer>> total,List<Integer> current){
		if(target == 0){
			total.add(new ArrayList<Integer>(current));
			return;
		}
		for(int i =n;i <candidates.length && candidates[i] <= target;i ++){
			current.add(candidates[i]);
			dfs(candidates,i+1,target-candidates[i],total,current);
			current.remove(current.size()-1);
		}
	}
}
```
