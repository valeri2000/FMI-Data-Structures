#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include "../QueueLL/Queue.cpp"

void invalidPath() {
    std::cout << "No path exists!\n";
}

int main() {
    std::ifstream in("task3.in");
    int n;
    in >> n;
    std::vector<std::string> grid(n);
    for(int i = 0; i < n; ++i) {
        in >> grid[i];
    }
    int sx, sy, dx, dy;
    in >> sx >> sy >> dx >> dy;
    in.close();

    if(grid[sx][sy] == 'X') {
        invalidPath();
        return 0;
    }

    std::vector<std::vector<bool> > used(
        n,
        std::vector<bool>(n)
    );
    std::vector<std::vector<std::pair<int, int> > > parent(
        n,
        std::vector<std::pair<int, int> >(n, {-1, -1})
    );
    const std::vector<std::pair<int, int> > dirs {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    Queue<std::pair<int, int> > q;

    q.push({sx, sy});
    used[sx][sy] = 1;
    parent[sx][sy] = {sx, sy};
    while(!q.empty()) {
        std::pair<int, int> curr = q.front();
        q.pop();
        for(const std::pair<int, int>& dir : dirs) {
            std::pair<int, int> temp = curr;
            temp.first += dir.first, temp.second += dir.second;
            while(temp.first >= 0 && temp.first < n &&
                  temp.second >= 0 && temp.second < n &&
                  grid[temp.first][temp.second] != 'X') {
                if(!used[temp.first][temp.second]) {
                    used[temp.first][temp.second] = 1;
                    parent[temp.first][temp.second] = curr;
                    q.push({temp.first, temp.second});
                }
                temp.first += dir.first, temp.second += dir.second;
            }
        }
    }

    if(parent[dx][dy] == std::make_pair(-1, -1)) {
        invalidPath();
        return 0;
    }
    std::vector<std::pair<int, int> > path;
    path.push_back({dx, dy});
    if(dx != sx || dy != sy) {
        std::pair<int, int> temp = parent[dx][dy];
        dx = temp.first, dy = temp.second;
        while(parent[dx][dy] != std::make_pair(dx, dy)) {
            path.push_back({dx, dy});
            temp = parent[dx][dy];
            dx = temp.first, dy = temp.second;
        }
        path.push_back({dx, dy});
    }
    std::reverse(path.begin(), path.end());
    std::cout << "Steps: " << (int)path.size() - 1 << std::endl;
    std::cout << "Path:\n";
    for(const std::pair<int, int>& i : path) {
        std::cout << i.first << ' ' << i.second << std::endl;
    }

    return 0;
}
