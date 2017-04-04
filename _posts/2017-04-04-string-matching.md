---
layout: post
title: string matching
tags: algorithm
categories: algorithm
---
## 字符串匹配
&emsp;&emsp;算法一书中讲到了好几种字符串匹配算法，包括暴力匹配算法、kmp算法以及下面要提到的boyer-moore算法和rabin-karp算法。后面这两种算法和KMP算法一样，都能够在线性时间内实现字符串匹配。
<br>

### boyer-moore算法
&emsp;&emsp; boyer-moore算法的主要是思路是从右至左进行匹配。如果匹配失败，那么跳转到下一个位置进行匹配。与KMP算法一样，boyer-moore也需要做预处理，预处理的过程中能够获得下一次跳转的位置。boyer-moore算法思路如下：<br>
![runtime][png1]
<br> 
&emsp;&emsp; 算法实现如下：
<br>
``` c++
#include <iostream>
#include <cstring>
using namespace std;
int *get_skip_table(const char * pat);
int boyer_moore(const char * pat,const char * txt ){
    int * skip_table = get_skip_table(pat);
    int plen = strlen(pat);
    int tlen = strlen(txt);
    int skip = 0;
    for(int i = 0;i <=tlen - plen ; i+= skip){
        skip = 0;
        for(int j = plen-1;j >= 0;j --){
            if(pat[j] != txt[i+j]){
                skip = j-skip_table[txt[i+j]];
                if(skip <1){
                    skip = 1;
                }
                break;
            }
            if(skip == 0 ) return i;
        }
    }
    return -1;
}
int *get_skip_table(const char * pat){
    int len = strlen(pat);
    int R = 256;
    int *skip_table = new int[R];
    for(int i = 0;i < R;i ++ ){
        skip_table[i] = -1;
    }
    for(int i = 0;i < len;i ++){
        skip_table[pat[i]] = i;
    }
    return skip_table;
}

int main(){
    char *pat= "abcdabd";
    char *text = "get_abcdabdskip_tableget_skip_table";
    cout << boyer_moore(pat,text);
}

```
### rabin-karp算法
&emsp;&emsp;rabin-karp算法主要的思路是对字符串做哈希，通过哈希的方式实现字符串的快速匹配，然后依次计算相同长度字符串的哈希值，哈希值匹配的时候，才进行完全的匹配。对字符串进行哈希，利用hoore算法。hoore算法如下:<br>
``` c++
long hash(const char * pat,int M,int R,int Q){
    long h = 0;
    for(int i = 0;i < M;i ++){
        h = (h*R+pat[i])%Q;
    }
    return h;
}

```
&emsp;&emsp;剩下的思路就是如何快速计算与目标字符串等长的字符串的hash值了。计算思路如下：<br>
![runtime][png2]
<br>&emsp;&emsp;通过这种方式，就能快速的计算出字符串的hash值了。代码实现如下：<br>

``` c++
#include <iostream>
#include <cstring>
using namespace std;
long Q= 10231;
int pathash;
int R = 31;
long hash(const char *pat,int len);
long get_rm(const char *pat){
    int len = strlen(pat);
    long rm =  1;
    for(int i = 1;i < len;i ++){
        rm = (R*rm)%Q;
    }
    pathash = hash(pat,len);
    return rm;
}

long hash(const char *pat,int M){
    long h = 0;
    for(int i = 0;i < M;i ++){
        h = (h*R+pat[i])%Q;
    }
    return h;
}
bool check(const char * pat,const char *txt,int index){
    return true;
}
int rabin_karp(const char *pat,const char *txt){
    int tlen = strlen(txt);
    int plen = strlen(pat);
    long rm = get_rm(pat);
    long txthash = hash(txt,plen);
    if(txthash == pathash && check(pat,txt,0)){
        return 0;
    }
    for(int i = plen;i <tlen;i ++ ){
        txthash = (txthash + Q - rm*txt[i-plen]%Q)%Q; 
        txthash = (txthash*R+txt[i])%Q;
        if(txthash == pathash){
            return i-plen+1;
        }
    }
    return -1;
}
int main(){
    char *pat= "abcdabd";
    char *text = "asdfsfsabcdabdr";
    cout << rabin_karp(pat,text);
}


```

<br>&emsp;&emsp;这两天看的字符串匹配算法确实是很精妙的算法，看这些东西确实是意见令人愉悦的事情。

[png1]: {{"/string-matching-1.jpg" | prepend: site.imgrepo }}
[png2]: {{"/string-matching-2.jpg" | prepend: site.imgrepo }}