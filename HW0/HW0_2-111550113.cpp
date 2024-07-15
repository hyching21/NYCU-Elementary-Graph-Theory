#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> frequency;

    int max_count = 0;
    int mode = -1;

    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        frequency[num]++;
        if (frequency[num] > max_count) {
            max_count = frequency[num];
            mode = num;
        }
    }

    cout << mode << " " << max_count;
    return 0;
}
