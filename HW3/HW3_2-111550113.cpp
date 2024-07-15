#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;

typedef pair<long long int,int>pii; //weight, node index
const long long INF = 0x3f3f3f3f3f3f3f3f;

void dijkstra(vector<vector<pii>>&edges,int n,int source){
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<long long int>dist(n,INF);
    pq.push({0,source});
    dist[source]=0;
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        for(pii x:edges[u]){
            long long int w=x.first;
            int v=x.second;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i=0;i<n;i++){
        if(dist[i]==INF){dist[i]=-1;}
        cout<<dist[i]<<" ";
    }
    cout<<"\n";
}
//k=2
void dijkstra2(vector<vector<pii>>&edges,int n,int s_1,int s_n){
    vector<long long int> dist_1(n,INF),dist_n(n,INF);
    vector<int> parent_1(n,-1),parent_n(n,-1);
    priority_queue<pii, vector<pii>, greater<pii>> pq_1;
    priority_queue<pii, vector<pii>, greater<pii>> pq_n;
    pq_1.push({0,s_1});
    dist_1[s_1]=0;
    while(!pq_1.empty()){
        int u_1=pq_1.top().second;
        pq_1.pop();
        for(pii x_1:edges[u_1]){
            long long int w_1=x_1.first;
            int v_1=x_1.second;
            if(dist_1[u_1]+w_1<dist_1[v_1]||(dist_1[u_1]+w_1==dist_1[v_1]&&parent_1[v_1]>u_1)){
                dist_1[v_1]=dist_1[u_1]+w_1;
                parent_1[v_1]=u_1;
                pq_1.push({dist_1[v_1],v_1});
            }
        }
    }

    pq_n.push({0,s_n});
    dist_n[s_n]=0;
    while(!pq_n.empty()){
        int u_n=pq_n.top().second;
        pq_n.pop();
        for(pii x_n:edges[u_n]){
            long long int w_n=x_n.first;
            int v_n=x_n.second;
            if(dist_n[u_n]+w_n<dist_n[v_n]||(dist_n[u_n]+w_n==dist_n[v_n]&&parent_n[v_n]>u_n)){
                dist_n[v_n]=dist_n[u_n]+w_n;
                parent_n[v_n]=u_n;
                pq_n.push({dist_n[v_n],v_n});
            }
        }
    }
    // find common
    for(int i=0;i<n;i++){
        edges[n].push_back({dist_1[i]+dist_n[i],i});
    }
    //dijkstra again : dijkstra(d_final, edge, parent, source);
    priority_queue<pii, vector<pii>, greater<pii>> pq_final;
    vector<long long int> d_final(n+1,INF);
    vector<int> p_final(n+1,-1);
    edges.push_back(vector<pii>(0));
    pq_final.push({0,n});
    d_final[n]=0;

    while(!pq_final.empty()){
        int u_f=pq_final.top().second;
        pq_final.pop();
        for(pii x_f:edges[u_f]){
            long long int w_f=x_f.first;
            int v_f=x_f.second;
            if(d_final[u_f]+w_f<d_final[v_f]||(d_final[u_f]+w_f==d_final[v_f]&&p_final[v_f]>u_f)){
                d_final[v_f]=d_final[u_f]+w_f;
                p_final[v_f]=u_f;
                pq_final.push({d_final[v_f],v_f});
            }
        }
    }
    //output
    for(int i=0;i<n;i++){
        if(dist_1[i]==INF || dist_n[i]==INF){d_final[i]=-1;}
        cout<<d_final[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    int t,sub;
    cin>>t>>sub;
    while(t!=0){
        int n,m,k; //restaurant,road,choose
        cin>>n>>m>>k;
        vector<vector<pii>> edges(n+1);
        for(int i=0;i<m;i++){
                long long int u,v,w; // road info
                cin>>u>>v>>w;
                edges[v-1].push_back({w,u-1}); //store reversely
        }
        if(k==1){
            //output the min length of i to 1 (total: n numbers)
            dijkstra(edges,n,0);
        }
        else if(k==2){
            //output the min length of i to 1 and to n (! same road counted once)
            dijkstra2(edges,n,0,n-1);
        }
        t--;
    }
    return 0;
}
