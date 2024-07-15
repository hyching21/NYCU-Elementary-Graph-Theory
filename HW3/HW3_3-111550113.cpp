#include <iostream>
#include <vector>
using namespace std;

void DFS(int node,int p,vector<vector<int>>&mat,vector<int>&height,vector<int>&parent){
    parent[node]=p;
    int s=mat[node].size();
    if(s==1&&node!=1){
        height[node]=0;
        return;
    }

    for(int v:mat[node]){
        if(v!=p){
            DFS(v,node,mat,height,parent);
            height[node]=max(height[node], 1 + height[v]);
        }
    }
}
int main(){
    int n; //number of vertex
    cin>>n;
    vector<vector<int>> mat(n+1);
    vector<int>height(n+1,0);
    vector<int>parent(n+1,-1);
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        mat[x].push_back(y);
        mat[y].push_back(x);
    }
    DFS(1,-1,mat,height,parent);
    for(int i=1;i<=n;i++){
        cout<<height[i]<<" "<<parent[i]<<"\n";
    }
    return 0;
}




