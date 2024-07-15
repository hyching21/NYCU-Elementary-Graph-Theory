#include <iostream>
#include <queue>
using namespace std;

bool is_bipartite(vector<vector<int>> &graph, int start) {
  vector<int> color(graph.size(), -1); // initially all no color
  color[start] = 0;
  // use BFS
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    // dequeue
    int cur = q.front();
    q.pop();
    // check loop
    // if (graph[cur][cur] == true) {
    //   return false;
    // }
    //check neighbor of cur
    int size=graph[cur].size();
    for (int i = 0; i < size; i++) {
      int neighbor = graph[cur][i];
      if (color[neighbor] == -1) {
        color[neighbor] = 1 - color[cur];
        q.push(neighbor);
      } else if (color[neighbor] == color[cur]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  bool check = is_bipartite(graph, 0);
  if (check) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}