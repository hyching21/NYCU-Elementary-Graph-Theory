#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <unordered_map>
using namespace std;

bool bfs(vector<vector<int>>&residual, int s, int t, vector<int>&parent){
    vector<bool>visited(t+1,false);
    queue<int> q;
    q.push(s);
    visited[s]=true;
    parent[s]=-1;
        while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<=t;i++){
            if(visited[i]==false && residual[u][i]>0){
                if(i==t){
                    parent[i]=u;
                    return true;
                }
                q.push(i);
                parent[i]=u;
                visited[i]=true;
            }
        }
    }
    return false;
}

int ford(vector<vector<int>>&mat, int s, int t){
    vector<vector<int>> residual=mat;
    vector<int> parent(t+1,0);
    int max_flow = 0;
    while(bfs(residual,s,t,parent)){
        int path_flow = INT_MAX;
        for(int i=t;i!=s;i=parent[i]){
            int u=parent[i];
            path_flow=min(path_flow,residual[u][i]);
        }
        for(int i=t;i!=s;i=parent[i]){
            int u=parent[i];
            residual[u][i]-=path_flow;
            residual[i][u]+=path_flow;
        }
        max_flow+=path_flow;
    }
    return max_flow;
}
int main(){
    int n,m,k; //hero,monster,potion
    cin>>n>>m>>k;
    int all=n+m+4;
    vector<vector<int>> mat(all,vector<int>(all, 0));
    mat[0][1]=n; //num of hero {1,n}
    mat[0][2]=k; // num of poison {2,k}
    for(int i=0;i<n;i++){
        int t;
        int j=i+3; //hero
        cin>>t; //size of set Mi, monsters that can be killed by ith hero
        mat[1][j]=1; // heros connect {hero,1}
        mat[2][j]=1; // poisons connect {hero,1}
        for(int k=0;k<t;k++){
            int m;
            cin>>m;
            int monster=m+n+2;
            mat[j][monster]=1; // hero connect to monster
            mat[monster][all-1]=1; // monster connect to sink
        }
    }
    cout<<ford(mat,0,all-1);
    return 0;
}
