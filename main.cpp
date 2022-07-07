#include <bits/stdc++.h>
using namespace std;

int main(){
    string ara[] = {"haat", "salman", "sallu"};
    string bra[] = {"fahim", "hakim", "lengra", "cg4"};
    for(int i=0; i<3; i++){
        string s = ara[i] + " ";
        for(int j=0; j<4; j++){
            cout<<(s+bra[j])<<endl;
        }
    }
}