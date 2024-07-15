#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;
#define pii pair<int, int>

int main(){
    int q; // query
    cin>>q;
    while(q--){
        int n,m; // vertex, edge
        cin>>n>>m;
        vector<pii> edges;
        for(int i=0;i<m;i++){
            int x,y;
            cin>>x>>y;
            x--,y--;
            edges.push_back({x,y});
        }
        bool ans=false;
        // all possible subsets of edges bitmasking
        for(int i=1;i<(1<<m);i++){
            int x=i;
            vector<bool> include(m,0); // which edges is include
            for(int j=0;j<m;j++){
                include[j]=x%2;
                x>>=1; // move right
                if(!x){break;} // if x==0 discard
            }
            //Skip subsets with fewer than 9 edges
            if(count(include.begin(),include.end(),1)<9){continue;}
            vector<vector<int>> adj(n); // adjacency list for the selected subset of edges
            for(int j=0; j<m; j++){
                if(include[j]){
                    adj[edges[j].first].push_back(edges[j].second);
                    adj[edges[j].second].push_back(edges[j].first);
                }
            }
            // like subdiviosn
            for(int j=0;j<n;j++){
                //int j_size=adj[j].size();
                if(adj[j].size()==2){
                    vector<int> tmp;
                    for(int k:adj[j]){ //remove j from list of k, store k in tmp
                        auto it = remove(adj[k].begin(), adj[k].end(), j);
                        adj[k].erase(it, adj[k].end());
                        tmp.push_back(k);
                    }
                    //check if this two tmp vertex already connected, if not then connect them
                    if(find(adj[tmp[0]].begin(), adj[tmp[0]].end(), tmp[1]) != adj[tmp[0]].end())
                        continue;
                    adj[tmp[0]].push_back(tmp[1]);
                    adj[tmp[1]].push_back(tmp[0]);
                    adj[j].clear();
                }
            }
            //check remain connect component
            int ct=0;
            for(int j=0;j<n;j++){
                if(!adj[j].empty()){
                    ct++;
                }
            }
            bool flag=false;
            if(ct==5){ //check k5
                for(int j=0;j<n;j++){
                    int j_size=adj[j].size();
                    if(j_size!=4 && j_size!=0){
                        flag=true;
                        break;
                    }
                }
                if(!flag){
                    cout <<"No\n";
                    ans = 1;
                    break;
                }
            }
            else if(ct==6){ // check k33
                for(int j=0;j<n;j++){
                    int j_size=adj[j].size();
                    if(j_size!=3 && j_size!=0){
                        flag=true;
                        break;
                    }
                }
                if(flag){
                        continue;
                }
                //check if 6 vertex are two group
                unordered_set<int> s1, s2;
                for(int j=0;j<n;j++){
                    if(adj[j].empty()){continue;}
                    if(s1.empty() && s2.empty()){
                        s1.insert(j);
                        for(int k:adj[j]){
                            s2.insert(k);
                        }
                        continue;
                    }
                    if(s2.find(j)==s2.end()){ // j in s1
                        for(int k:adj[j]){
                            if(s2.find(k)==s2.end()){ // k in s1
                                flag=true;
                                break;
                            }
                        }
                    }
                    else{ // j in s2
                        for(int k:adj[j]){
                            if(s2.find(k)!=s2.end()){ // k in s2
                                flag=true;
                                break;
                            }
                        }
                    }
                }
                if(!flag){
                    cout <<"No\n";
                    ans = true;
                    break;
                }
            }
        }
        if(!ans){cout<<"Yes\n";}
    }
    return 0;
}
