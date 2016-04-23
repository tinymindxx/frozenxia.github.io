---
layout: post
title: Sudoku Solver 
tags: java algorithm 
categories: algorithm
---
sudoku solver的思路很直接，但是一开始没有处理好递归如何进行下去的。要解决这个问题，就需要有一种方法可以有效的遍历完整个数组，可以采用将二维数组转换成一维数组的方式，这样就可以进行深度递归了，深度递归的时候，着眼于解决当前cell的value选择。这个思路的代码如下所示.

``` java
public class Solution {
	public void solveSudoku(char[][] board) {
		helper(board,0);
	}

	public boolean  helper(char [][]board,int m){
		if(m > 80) return true;
		int i = m/9;
		int j = m%9;
		if(board[i][j] == '.'){
			Set<Character> seti = new HashSet<Character>();
			for(char c = '1' ;c <= '9';c ++){
				if(isvalid(board,i,j,c)){
					seti.add(c);
				}
			}
			for(char c : seti){
				board[i][j] = c;
				if(helper(board,m+1)) return true;
				board[i][j] = '.';
			}
			return false;
		}else{
			return helper(board,m+1);
		}

	}
	boolean isvalid(char[][]board,int p,int q,char c){
		int k = p/3*3+q/3;
		for(int i =0;i < 9;i ++){
			if(board[p][i] == c || board[i][q] == c||board[p/3*3+i/3][q/3*3+i%3] == c) return false;
		}
		return true;
	}

}

```
除了这种思路意外，从discuss上面还看到了另外一种思路，就是直接每次都遍历整个二维数组，进行深度递归。深度递归着眼于解决整个sudoku。具体代码如下


``` java
public class Solution {
	public void solveSudoku(char[][] board) {
		if(board == null || board.length == 0)
			return;
		solve(board);
	}

	public boolean solve(char[][] board){
		for(int i = 0; i < board.length; i++){
			for(int j = 0; j < board[0].length; j++){
				if(board[i][j] == '.'){
					for(char c = '1'; c <= '9'; c++){//trial. Try 1 through 9 for each cell
						if(isValid(board, i, j, c)){
							board[i][j] = c; //Put c for this cell

							if(solve(board))
								return true; //If it's the solution return true
							else
								board[i][j] = '.'; //Otherwise go back
						}
					}
					return false;
				}
			}
		}
		return true;
	}

	public boolean isValid(char[][] board, int i, int j, char c){
		//Check colum
		for(int row = 0; row < 9; row++)
			if(board[row][j] == c)
				return false;

		//Check row
		for(int col = 0; col < 9; col++)
			if(board[i][col] == c)
				return false;

		//Check 3 x 3 block
		for(int row = (i / 3) * 3; row < (i / 3) * 3 + 3; row++)
			for(int col = (j / 3) * 3; col < (j / 3) * 3 + 3; col++)
				if(board[row][col] == c)
					return false;
		return true;
	}
}

```

这是两种不同的思路，总体而言，第一种的计算量是要小一些，但是为了解决问题所产生的递归子函数应该是相同的。
