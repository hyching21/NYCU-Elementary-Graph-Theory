#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> possible_vertical(vector<vector<int>>& graph,vector<int>& joint,int n){
    int j_size=joint.size();
    vector<vector<int>> vertical_bars(j_size); //the i th vertical_bars means the i th joint's length options
    for(int i=0;i<j_size;i++){
        int start=joint[i];
        vector<int> length(n,-1);
        queue<int> q;
        q.push(start);
        length[start]=0;

        while(!q.empty()){
            int cur=q.front();
            q.pop();
            bool all_visited=true;
            for(int neighbor:graph[cur]){
                if(length[neighbor]==-1){
                     all_visited=false;
                    // check if neighbor is joint then stop -> don't add the length!
                    bool isjoint=false;
                    for(int i=0;i<j_size;i++){
                        if(joint[i]==neighbor){
                            isjoint=true;
                            break;
                        }
                    }
                    if(isjoint){continue;}
                    length[neighbor]=length[cur]+1;
                    q.push(neighbor);

                }
            }
            //if neighbors all visited then add the length to vertical_bars[start]
            if(all_visited){
                vertical_bars[i].push_back(length[cur]);
            }
        }
    }
    return vertical_bars;
}

vector<int> list_joint(vector<vector<int>>& graph,vector<int>& joint,int endjoint[],int n){
    int j_size=joint.size();
    vector<int> jointorder;
    int root=joint[endjoint[0]];
    jointorder.push_back(endjoint[0]);
    vector<int> visited(n,-1);
    queue<int>q;
    q.push(root);
    visited[root]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int neighbor:graph[cur]){
            if(visited[neighbor]==-1){
                visited[neighbor] = visited[cur] + 1;
                q.push(neighbor);
                auto jointIt = find(joint.begin(), joint.end(), neighbor);
                if (jointIt  != joint.end() || neighbor == joint[j_size-1]) {
                    int jointIndex = distance(joint.begin(), jointIt);
                    jointorder.push_back(jointIndex);
                }
            }
        }
    }
    return jointorder;
}

vector<vector<int>> list_combination(vector<vector<int>>& vertical_bars,vector<int>& joint,vector<int>& jointorder){
    int j_size=joint.size();
        vector<vector<int>> c(8,vector<int>(j_size, 0));
    int a_1=vertical_bars[jointorder[0]][0],a_2=vertical_bars[jointorder[0]][1];
    int b_1=vertical_bars[jointorder[j_size-1]][0],b_2=vertical_bars[jointorder[j_size-1]][1];
    c[0][0]=a_1;c[1][0]=a_1;c[4][j_size-1]=a_1;c[5][j_size-1]=a_1;
    c[2][0]=a_2;c[3][0]=a_2;c[6][j_size-1]=a_2;c[7][j_size-1]=a_2;
    c[0][j_size-1]=b_1;c[2][j_size-1]=b_1;c[4][0]=b_1;c[6][0]=b_1;
    c[1][j_size-1]=b_2;c[3][j_size-1]=b_2;c[5][0]=b_2;c[7][0]=b_2;
    for(int i=0;i<4;i++){
        for(int j=1;j<j_size-1;j++){
            int joint_position=jointorder[j];
                c[i][j]=vertical_bars[joint_position][0];
        }
    }
    for(int i=4;i<8;i++){
        for(int j=1;j<j_size-1;j++){
            int joint_position=jointorder[j_size-1-j];
            c[i][j]=vertical_bars[joint_position][0];
        }
    }

    return c;
}

bool check(vector<int>& key,vector<vector<int>>& list_combination){
    int key_size=key.size();
    for(vector<int>& option : list_combination){
        if(key.size()!=option.size()){return false;}
        else{
            bool match=true;
            for(int i=0;i<key_size;i++){
                if(key[i]!=option[i]){match=false;break;}
            }
            if(match){return true;}
        }
    }
    return false;
}

int main(){
    int n; //number of nodes
    cin>>n;
    //adjacent list of drizella
    vector<vector<int>> graph(n);
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int m; //key length of cinderella
    cin>>m;
    vector<int> key(m);
    for(int i=0;i<m;i++){
        cin>>key[i];
    }
    //judge joint
    vector<int> joint;
    for(int i=0;i<n;i++){
        if(graph[i].size()==3){joint.push_back(i);}
    }
    //find vertical
    vector<vector<int>> vertical_bars=possible_vertical(graph,joint,n);
    int j_size=joint.size();
    //judge endjoint
    int endjoint[2],a=0;
    for(int i=0;i<j_size;i++){
        if(vertical_bars[i].size()==2){endjoint[a]=i;a++;}// ith vertical_bars(joint) is corner}
    }
    //check jointorder
    vector<int> jointorder=list_joint(graph,joint,endjoint,n);
    //produce combination
    vector<vector<int>> c = list_combination(vertical_bars,joint,jointorder);

    //check if key matches the blueprint
    bool answer = check(key,c);
    if (answer) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }

    return 0;
}



