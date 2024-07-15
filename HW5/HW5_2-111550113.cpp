#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// find vertex connectivity
struct Edge{
    int to,rev,flow,cap;
};

#define vve vector<vector<Edge>>
int total;
int dist[500],work[500];


void addEdge(vve &adj,int s,int t,int cap){
        Edge e_forward={t,(int)adj[t].size(),0,cap};
        Edge e_backward={s,(int)adj[s].size(),0,0};
        adj[s].push_back(e_forward);
        adj[t].push_back(e_backward);
}
// find augmenting path
bool BFS(vve &adj,int s,int t){
        fill(dist,dist+total,-1);
        dist[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int cur=q.front();
            q.pop();
            for(auto& i:adj[cur]){
                int to=i.to;
                if(dist[to]<0 && i.flow<i.cap){
                    dist[to]=dist[cur]+1;
                    q.push(to);
                }
            }
        }
        return dist[t]>=0;
}
int DFS(vve &adj,int s,int t, int mf){
        //reach to end
        if(s==t){
            return mf;
        }

        for(int &i=work[s];i<(int)adj[s].size();i++){
            Edge&e=adj[s][i];
            int to=e.to,rev=e.rev;

            if(dist[to]==dist[s]+1 && e.cap > e.flow){
                int cur_flow=min(mf,e.cap-e.flow);
                int tmp_flow = DFS(adj,to,t,cur_flow);

                if(tmp_flow>0){
                    e.flow+=tmp_flow;
                    adj[to][rev].flow-=tmp_flow;
                    return tmp_flow;
                }
            }
        }
        return 0;
}

int Ford(vve &adj,int s,int t){
        vve rg = adj;
        int maxflow=0;
        while(BFS(rg,s,t)){ //every times
            for(int i=0;i<200;i++){
                work[i]=0;
            }
            while(true){
                int path_flow = DFS(rg,s,t,INT_MAX);
                if(!path_flow){break;}
                maxflow+=path_flow;
            }

        }
        return maxflow;
}

int main(){
    int n,m; // vertex,edge
    cin>>n>>m;
    //Graph g(2*n+1);
    vector<vector<Edge>> adj(2*n+1);
    total=2*n+1;
    //node i divide into two part: in and out
    for(int i=1;i<=n;i++){
        addEdge(adj,2*i-1,2*i,1);
    }
    //one edge
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        addEdge(adj,2*u,2*v-1,1000);
        addEdge(adj,2*v,2*u-1,1000);
    }
    //if complete
    if(2*m==n*(n-1)){
        cout<<n-1<<"\n";
    }
    else{
        int ans=INT_MAX;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i!=j){
                    ans=min(ans,Ford(adj,2*i,2*j-1));
                }
                if(ans==2){
                    cout<<ans<<"\n";
                    return 0;
                }
            }
        }
        cout<<ans<<"\n";
    }

    return 0;
}


