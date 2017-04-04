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
