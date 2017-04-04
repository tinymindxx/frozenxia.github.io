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