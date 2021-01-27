#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
    cin >> s;
    int flag = 1;
    int ans = 1;
    for(int i = 0; i < s.size(); i++){
        if(flag == 1){
            if(s[i] == '!'){
                if(i != 0) flag++;
                else{
                    ans = 0;
                    break;
                }
            }
            else if(s[i] == 'A');
            else{
                ans = 0;
                break; 
            }
        }
        else if(flag == 2){
            if(s[i] == '!');
            else{
                ans = 0;
                break;
            }
        }
    }
    if(ans && flag == 2) printf("Panic!\n");
    else printf("No Panic\n");
}