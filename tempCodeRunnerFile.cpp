#include <iostream>
#include <vector>
#include <math.h>
#include <set>
using namespace std; 


int main() {
    string s;
    cin >> s;
    int left=0,right=s.size()-1;
    int n=s.size();
    int noofswaps=0;
    while(left<right){
        if(s[left]==s[right]){
            left++;
            right--;
        }
        else{
            int temp=right-1;
            int cnt=0;
            while(temp>=0 && temp>left){
                if(s[left]==s[temp]){
                    swap(s[temp],s[right]);
                    cnt=1;
                    left++;
                    right--;
                    break;
                }
                else{
                    temp--;
                }
            }
            if(cnt==0 && s[right]!=s[left]){
                swap(s[right],s[n/2]);
                noofswaps++;
                if(noofswaps>1){
                    cout<<"NO SOLUTION";
                    return 0;
                }
            }
        }
    }
    for(int i=0;i<n/2;i++){
        if(s[i]!=s[n-1-i]){
            cout<<"NO SOLUTION";
            return 0;
        }
    }
    cout<<s;
    return 0;
}