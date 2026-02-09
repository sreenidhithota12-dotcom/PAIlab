#include <iostream>
#include <vector>
#include <string>
using namespace std;
void nextvalue(int k, int n, int m,vector<int> &x,vector<vector<int>> &adj) {
    while (true) {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0) return;
        bool safe = true;
        for (int v : adj[k]) {
            if (x[v] == x[k]) {
                safe = false;
                break;
            }
        }
        if (safe) return;
    }
}
bool coloring(int k, int n, int m,vector<int> &x,vector<vector<int>>&adj) {
    while (true) {
        nextvalue(k, n, m, x, adj);
        if (x[k] == 0) return false;
        if (k == n - 1)
            return true;
        else if (coloring(k + 1, n, m, x, adj))
            return true;
    }
}
int main() {
    int n;
    cout << "Enter number of names: ";
    cin >> n;
    vector<string> names(n);
    cout << "Enter names:\n";
    for (int i = 0; i < n; i++)
        cin >> names[i];
    cout << "\nNames list:\n";
    for (int i = 0; i < n; i++)
        cout << i + 1 << ". " << names[i] << endl;
    int m;
    cout << "Enter number of colors: ";
    cin >> m;
    int c;
    cout << "Enter number of constraints: ";
    cin >> c;
    vector<vector<int>> adj(n);
    cout << "Enter constraint pairs (numbers):\n";
    for (int i = 0; i < c; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> x(n, 0);
    if (coloring(0, n, m, x, adj)) {
        cout << "One possible solution:\n";
        for (int i = 0; i < n; i++)
            cout << names[i] << " -> Color " << x[i] << endl;
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}
