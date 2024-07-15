#include <iostream>
#include <queue>
using namespace std;

typedef struct return_2{
    int max_length;
    int far_node;
}R2;

R2 BFS(vector<vector<int>>& graph,int start,int n){
    R2 output;
    output.max_length=0;
    output.far_node=start;
    vector<int> length(n,-1);
    queue<int>q;
    q.push(start);
    length[start]=0;
    //int max_length=0,far_node=start;
    while(!q.empty()){
        int cur=q.front();
        q.pop();

        for(int neighbor:graph[cur]){
            if(length[neighbor]==-1){
                length[neighbor]=length[cur]+1;
                q.push(neighbor);
            }
            if(length[neighbor]>output.max_length){
                output.max_length=length[neighbor];
                output.far_node=neighbor;
            }
        }
    }

    return output;
}

int diameter(vector<vector<int>>& graph,int n){
    //endpoint A and B
    int A=BFS(graph,0,n).far_node;
    R2 B=BFS(graph,A,n);
    return B.max_length;
}

int main(){
    int n;
    cin>>n;
    //create adjacent list
    vector<vector<int>> graph(n);
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        graph[x-1].push_back(y-1);
        graph[y-1].push_back(x-1);
    }

    int d=diameter(graph,n);
    cout<<d<<"\n";
    return 0;
}


