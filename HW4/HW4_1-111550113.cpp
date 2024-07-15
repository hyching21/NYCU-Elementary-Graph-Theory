#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void check(vector<vector<int>>&edges,int u,int disc[],int low[],bool visited[],bool is_cut[],int& time,int par){
    int children=0;
    visited[u]=true;
    disc[u]=low[u]=++time;
    for(int v:edges[u]){
        if(!visited[v]){
            children++;
            check(edges,v,disc,low,visited,is_cut,time,u);
            low[u]=min(low[v],low[u]); //check root v's subtree connection to ancestor u or not
            if(par!=-1 && low[v]>=disc[u]){ // if low[v]<disc[u], v can reach to ancestor u without using u
                is_cut[u]=true;
            }
        }
        else if(v!=par){
            low[u]=min(low[u],disc[v]);
        }
    }
    if(par==-1 && children>1){ //Case:u is root and has more than two children
        is_cut[u]=true;
    }
}
void cut(vector<vector<int>>&edges, int n){
    int disc[n]={0};
    int low[n];
    bool visited[n] = {false};
    bool is_cut[n] = {false};
    int time=0,par=-1;
    for(int i=0;i<n;i++){
        if(visited[i]==false){
            check(edges,i,disc,low,visited,is_cut,time,par);
        }
    }
    int count_num=0;
    vector<int>cut_set;
    for(int i=0;i<n;i++){
        if(is_cut[i]==true){
            count_num++;
            cut_set.push_back(i);
        }
    }
    int cut_size=cut_set.size();
    cout<<count_num<<"\n";
    for(int i=0;i<cut_size;i++){
        cout<<cut_set[i]+1<<" ";
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>edges(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        edges[u-1].push_back(v-1);
        edges[v-1].push_back(u-1);
    }
    cut(edges,n);
    return 0;
}
