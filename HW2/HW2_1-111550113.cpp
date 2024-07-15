#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
    vector<vector<string>> req;
    string merge(string &a, string &b) // a is followed by b (ab)
    {
        int n=a.size(), m=b.size(), len=1, idx=0;
        while(len<=min(n, m))
        {   if(a!=""&&b!=""){
                if(a!=b&&b.find(a)!= string::npos)
                {   a="";
                }
                else if(a.substr(n-len)==b.substr(0, len))
                {
                    idx=len;
                }
            }

            len++;
        }
        //cout<<"idx: "<<idx<<"\n";
        string res=b.substr(idx); // idx is the distance to non-overlap and res is the non-overlap string
        return res;
    }

    string solve(vector<string> &words, int prev, int mask, int n, vector<vector<string>> &dp)
    //prev:parent word, mask:track which word has been connected ( i th from right -> i th word )
    {   //dp[prev][mask] = min string to visit {mask} and end with prev
        if(dp[prev][mask]!="") return dp[prev][mask];// check if the dp is empty, when stop
        string res="";
        int minLen=INT_MAX;
        for(int i=0; i<n; i++)
        {
            if(mask&(1<<i)) continue; //check if the i th word has been used
            string temp=req[prev][i]+solve(words, i, mask|(1<<i), n, dp);
            //cout<<prev<<": "<<i<<": "<<temp<<"\n";
            //concatenating the word req[prev][i] (which represents the part of words[i] to append to the previous word) and the result of the recursive call to solve
            int temp_size=temp.size();
            if(temp_size<minLen || (temp_size)==minLen&& temp<res) //replace minLen
            {
                minLen=temp_size;
                res=temp;
            }
        }

        return dp[prev][mask]=res;
    }

public:
    string shortestSuperstring(vector<string>& words)
    {
        int n=words.size();
        sort(words.begin(), words.end());

        req.resize(n, vector<string> (n, ""));
        vector<vector<string>> dp(n, vector<string> ((1<<(n+1)), ""));
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(i==j) continue;
                req[i][j]=merge(words[i], words[j]);
                //cout<<req[i][j]<<",";
            }
            //cout<<"\n*******\n";
        }

        string ans="";
        int minLen=INT_MAX;
        int mask=0;
        for(int i=0; i<n; i++)
        {
            string temp=words[i]+solve(words, i, mask|(1<<i), n, dp);
            //cout<<"temp: "<<temp<<"\n";
//            bool finalcheck=true;
//            for(int i=0;i<n;i++){
//                if(words[i]!="" && temp.find(words[i])== string::npos){
//                    //cout<<words[i]<<"\n";
//                    finalcheck=false;
//                }
//            }

            int temp_size=temp.size();
            if(temp_size<minLen|| (temp_size == minLen && temp < ans)) //find the min length answer
            {
                minLen=temp.size();
                ans=temp;
            }


        }
        return ans;
    }
};
int main(){
    int n;
    cin>>n;
    vector<string> store(n);
    for(int i=0;i<n;i++){
        string str;
        cin>>str;
        store[i]=str;
    }
    vector<string> newstore;
    vector<bool> replicate(n,true);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j&&replicate[i]==true){
                if(store[i].find(store[j])!= string::npos){
                replicate[j]=false;
                }
            }

        }
    }
    for(int i=0;i<n;i++){
        if(replicate[i]==true){
            newstore.push_back(store[i]);
        }
    }
    Solution solution;
    string ans= solution.shortestSuperstring(newstore);
    cout<<ans;
    return 0;
}

