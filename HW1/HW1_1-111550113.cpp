#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, m; // vertex, edge
  cin >> n >> m;
  vector<int> u(m), v(m), w(m);

  for (int i = 0; i < m; i++) {
    cin >> u[i] >> v[i] >> w[i]; // value of w[i] is from u[i] to v[i]
  }

  vector<vector<int>> mat(n, vector<int>(n, 0));
  vector<int> in_deg(n, 0);
  vector<int> out_deg(n, 0);
  for (int i = 0; i < m; i++) {
    mat[u[i] - 1][v[i] - 1] = w[i];
    in_deg[v[i] - 1]++;
    out_deg[u[i] - 1]++;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
  for (int i = 0; i < n; i++) {
    cout << in_deg[i] << " " << out_deg[i] << endl;
  }
  return 0;
}