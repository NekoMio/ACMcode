#include<iostream>
#include<cstring>
#include<cstdio>
#include<set>
using namespace std;
char S[2000];
unsigned long long bkdr_hash(const char* key){
    char* str=const_cast<char*>(key);
    unsigned long long seed=31;
    unsigned long long hash=0;
    while(*str) hash=hash*seed+(*str++);
    return hash;
}
int main()
{
    set<unsigned long long> T;
    int n;
    unsigned long long H=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",S);
        H=bkdr_hash(S);
        if(!T.count(H))T.insert(H);
    }
    printf("%d",T.size());
    //while(1);
}