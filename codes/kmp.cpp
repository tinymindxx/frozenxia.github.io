#include<iostream>
#include <cstring>
using namespace std;
int *gen_next(char *pat);
int kmp(char *text,char *pattern){
    int plen = strlen(pattern);
    int tlen = strlen(text);
    int *next = gen_next(pattern);
    int i = 0;
    int j = 0;
    for( i = 0,j = 0;i < tlen;i ++){
        while (j &&text[i] != pattern[j]){
            j = next[j];
        }
        if(text[i]== pattern[j]) j ++;
        if(j == plen) return i-plen+1;
    }
    cout << endl <<i << '\t' <<j << endl;
    if( j == plen ) return i-plen+1;
    return -1;
}
int *gen_next(char *pat){
    int plen = strlen(pat);
    int *next = new int[strlen(pat)+1];
    for(int i = 0;i < plen;i ++){
        next[i] = 0;
    }
    int j = 0;
    next[0] = 0;
    for(int i = 1;i < plen;i ++){
        j = next[i];
        while(j &&pat[j] != pat[i]){
            j = next[j];
        }
        next[i+1] =(pat[j] == pat[i])?j+1:0;
    }
    for(int i = 0;i < plen;i ++){
        cout << next[i] << '\t';
    }
    cout << endl;
    return next;
 }

int main(){
    char *pat = "aacabcda";
    gen_next(pat);
    char *text = "abaacabcdacabcda";
   cout << "index " <<kmp(text,pat);

}

