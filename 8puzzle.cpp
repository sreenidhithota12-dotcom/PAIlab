#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <string>
using namespace std;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
bool isSolvable(string s) {
    int inv = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (s[i] && s[j] && s[i] > s[j])
                inv++;
        }
    }
    return (inv % 2 == 0);
}
int solve(string start,string goal) {
    if (!isSolvable(start)) {
        cout << "Not Solvable\n";
        return -1;
    }
    queue<pair<string, int>> q;
    set<string> visited;
    q.push({start, 0});
    visited.insert(start);
    while (!q.empty()) {
        string curr = q.front().first;
        int level = q.front().second;
        q.pop();
        if (curr == goal)
            return level;
        int pos = curr.find('0');
        int x = pos / 3;
        int y = pos % 3;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                string next = curr;
                swap(next[x * 3 + y], next[nx * 3 + ny]);

                if (!visited.count(next)) {
                    visited.insert(next);
                    q.push({next, level + 1});
                }
            }
        }
    }
    return -1;
}
int main() {
    string start,goal;
    cout << "Enter puzzle (9 digits, use 0 for blank):\n";
    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        start += c;
    }
    cout<<"enter goal: ";
    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        goal += c;
    }
    int moves = solve(start,goal);
    if (moves != -1)
        cout << "Minimum moves = " << moves << endl;
    return 0;
}
