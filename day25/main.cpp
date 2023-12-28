#include "mylibs.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

map<int, map<int, bool>> mat;
set<pair<int, int>> edges;
map<string, int> ston;
int g_cnt = 0;

int get_id(string s) {
    if (ston.find(s) == ston.end()) {
        ston[s] = g_cnt++;
    }
    return ston[s];
}

struct flow_t {
    struct edge_t {
        int flow = 0;
        int cap = -1;
        int remain() {
            return cap - flow;
        }
    };
    vector<vector<int>> nbs;
    vector<vector<edge_t>> e;
    vector<bool> visited;
    vector<int> pre;
    int source = -1, target = -1;
    const int inf = 1000 * 1000 * 1000;
    void init(int n) // number of nodes
    {
        nbs = decltype(nbs)(n);
        e = decltype(e)(n, (decltype(e)::value_type)(n));
        visited = decltype(visited)(n);
        pre = decltype(pre)(n);
    }
    void add_edge(int a, int b, int cap) // add direct edge
    {
        if (e[a][b].cap == -1) {
            nbs[a].push_back(b);
            nbs[b].push_back(a);
            e[a][b].cap = 0;
            e[b][a].cap = 0;
        }
        e[a][b].cap += cap;
    }
    bool dfs(int x) {
        if (x == target)
            return true;
        visited[x] = 1;
        for (auto y : nbs[x]) {
            if (visited[y])
                continue;
            if (e[x][y].remain() <= 0)
                continue;
            pre[y] = x;
            if (dfs(y))
                return true;
        }
        return false;
    }
    int bottleneck() {
        int x = target;
        int min_value = inf;
        while (x != source) {
            min_value = min(min_value, e[pre[x]][x].remain());
            x = pre[x];
        }
        return min_value;
    }
    void augment(int delta) {
        int x = target;
        while (x != source) {
            e[pre[x]][x].flow += delta;
            e[x][pre[x]].flow -= delta;
            x = pre[x];
        }
    }
    int max_flow() {
        assert(source != -1 && target != -1);
        int total_flow = 0;
        while (1) {
            fill(visited.begin(), visited.end(), 0);
            if (!dfs(source))
                break;
            int delta = bottleneck();
            total_flow += delta;
            augment(delta);
        }
        return total_flow;
    }
} f;

bool used[2000];
int used_cnt = 0;

void dfs(int a) {
    if (used[a])
        return;
    used[a] = 1;
    used_cnt++;
    for (auto b : mat[a]) {
        dfs(b.first);
    }
}
void solve(int src, int dst) {
    printf("<src=%d dst=%d>", src, dst);
    set<pair<int, int>> remove;
    const int cuts = 3;

    for (int i = 0; i < 3; i++) {
        printf("<%d>", i);
        for (auto b : edges) {
            if (b.second > b.first)
                continue;
            printf("!");
            fflush(stdout);
            flow_t F;
            F.source = src;
            F.target = dst;
            int n = sz(mat);
            F.init(n + 5);

            for (auto e : edges) {
                auto ee = e;
                swap(ee.first, ee.second);
                if (e != b && ee != b && remove.find(e) == remove.end() && remove.find(ee) == remove.end())
                    F.add_edge(e.first, e.second, 1);
            }
            if (F.max_flow() == cuts - sz(remove) - 1) {
                remove.insert(b);
                break;
            }
        }
    }

    for (auto b : remove) {
        printf("[%d,%d]\n", b.first, b.second);
        mat[b.first].erase(b.second);
        mat[b.second].erase(b.first);
    }

    dfs(0);

    printf("%d", (sz(mat) - used_cnt) * used_cnt);
}
int main() {
    auto input = readlines();
    for (auto line : input) {
        auto a = split_c(line, ":")[0];
        auto b = split_c(line, ":")[1];
        auto c = split_c(b, " ");
        int x, y;
        x = get_id(a);
        for (auto d : c) {
            y = get_id(d);
            mat[x][y] = 1;
            mat[y][x] = 1;
        }
    }

    for (auto a : mat) {
        for (auto b : a.second) {
            int x = a.first, y = b.first;
            // edges.insert({y,x});
            edges.insert({x, y});
            // F.add_edge(a.first, b.first, 1);
        }
        // printf("%d %d\n", a.first, sz(a.second));
    }

    while (1) {
        flow_t F;
        int n = sz(mat);
        F.init(n + 5);

        for (auto e : edges)
            F.add_edge(e.first, e.second, 1);

        F.source = 0;
        F.target = rand() % n;
        if (F.max_flow() == 3) {
            solve(F.source, F.target);
            break;
        }
    }

    return 0;
}
