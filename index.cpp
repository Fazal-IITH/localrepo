#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <climits>  // for INT_MAX, INT_MIN
 
using namespace std;

string generate(int ind, string s, vector<int> v, int n){
    string ans;
    if(ind==s.size()){
        for(int i=1;i<=n;i++){
            int cnt=0;
            for(int j=0;j<v.size();j++){
                if(v[j]==i){
                    ans.push_back('+');
                    cnt+=1;
                    break;
                }
            }
            if(cnt==0){
                ans.push_back('-');
            }
        }
        return ans;
    }
    if(s[ind]=='0'){
        v.erase(v.begin());
        ans=generate(ind+1,s,v,n);
    }
    else if(s[ind]=='1'){
        v.pop_back();
        ans= generate(ind+1,s,v,n);
    }
    else{
        int temp=*(v.end()-1);
        v.pop_back();
        string s1=generate(ind+1,s,v,n);
        v.push_back(temp);
        v.erase(v.begin());
        string s2=generate(ind+1,s,v,n);
        for(int i=0;i<n;i++){
            if(s1[i]==s2[i]){
                ans.push_back(s1[i]);
            }
            else{
                ans.push_back('?');
            }
        }
        return ans;
    }
    return ans;
}
int main(){
    int cases;
    cin >> cases;
    vector<string> ans;
    while(cases--){
        int n,k;
        cin >> n >> k;
        vector<int>v;
        for(int i=0;i<n;i++){
            v.push_back(i+1);
        }
        string s;
        cin>>s;
        
        ans.push_back(temp);
    }
    for(auto it: ans){
        cout << it << endl;
    }
    return 0;
}