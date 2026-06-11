#include <iostream>
using namespace std;

string path;
bool vis[7][7];

int dfs(int i, int r, int c) {
    // reached end
    if (r == 6 && c == 0) {
        return (i == 48);
    }

    if (i == 48) return 0;

    // pruning: trap condition
    if ((r > 0 && r < 6 && !vis[r-1][c] && !vis[r+1][c] &&
         (c == 0 || vis[r][c-1]) && (c == 6 || vis[r][c+1])) ||
        (c > 0 && c < 6 && !vis[r][c-1] && !vis[r][c+1] &&
         (r == 0 || vis[r-1][c]) && (r == 6 || vis[r+1][c]))) {
        return 0;
    }

    vis[r][c] = true;
    int ans = 0;

    // U
    if ((path[i] == '?' || path[i] == 'U') && r > 0 && !vis[r-1][c])
        ans += dfs(i+1, r-1, c);

    // D
    if ((path[i] == '?' || path[i] == 'D') && r < 6 && !vis[r+1][c])
        ans += dfs(i+1, r+1, c);

    // L
    if ((path[i] == '?' || path[i] == 'L') && c > 0 && !vis[r][c-1])
        ans += dfs(i+1, r, c-1);

    // R
    if ((path[i] == '?' || path[i] == 'R') && c < 6 && !vis[r][c+1])
        ans += dfs(i+1, r, c+1);

    vis[r][c] = false;
    return ans;
}

int main() {
    cin >> path;
    cout << dfs(0, 0, 0);
}