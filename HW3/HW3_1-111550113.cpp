#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
using namespace std;

typedef pair<long long int,int> pii;

void prim(vector<long long int>&b_cost,vector<vector<pii>>&special,int n,int min_index){
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    long long int min_cost=0;
    vector<bool> visited(n,false);
    for(int i=0;i<n;i++){
        if(i!=min_index){
            pq.push({b_cost[min_index]+b_cost[i],i});
        }
    }
    //push special weight of min_index
    for(pii edge:special[min_index]){
        pq.push({edge.first,edge.second});
    }
    visited[min_index]=true;
    //while pq!=empty() push the new special weight
    while(!pq.empty()){
        pii p=pq.top();
        int u=p.second;
        long long int w=p.first;
        pq.pop();
        if(visited[u]==true){continue;}
        min_cost+=w;
        visited[u]=true;
        for(pii edge_new:special[u]){
            pq.push({edge_new.first,edge_new.second});
        }
    }
    cout<< min_cost <<"\n";
}
int main(){
    int q; //plans
    cin>>q;
    for(int k=0;k<q;k++){
        int n,m; //number of city, special offers
        cin>>n>>m;
        vector<long long int> b_cost(n);
        vector<vector<pii>> special(n);
        long long int min_value=LLONG_MAX;
        int min_index=0;
        for(int i=0;i<n;i++){
            long long int a;
            cin>>a;
            b_cost[i]=a;
            if(a<min_value){
                min_value=a;
                min_index=i;
            }
        }
        for(int i=0;i<m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            special[u-1].push_back({w,v-1});
            special[v-1].push_back({w,u-1});
        }
        prim(b_cost,special,n,min_index);
    }
    return 0;
}
