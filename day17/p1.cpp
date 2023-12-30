#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
map<char, pair<int,int> > dir;

char mat[150][150];
int states[150][150][4][3];
int size_r;
int size_c;
bool oob(int r,int c){
    if(r>=size_r) return true;
    if(c>=size_c) return true;
    if(r<0) return true;
    if(c<0) return true;
    return false;
}
string dstr=">v<^";
void dfs(int r,int c, int d, int cnt, int cost0){
    if(oob(r,c)) return;
    //printf("(%d %d,%d %d,%d)\n",r,c,d,cnt,cost0);

    int cost=cost0+mat[r][c]-'0';
    auto &v= states[r][c][d][cnt];
    if (v==-1 || cost <v){
        v=cost;
    }else{
        return;
    }
    for(int i=0;i<4;i++){
        int nr=r+dir[dstr[i]].first;
        int nc=c+dir[dstr[i]].second;
        if(d==i) {
            if(cnt==3) continue;
            else{
                dfs(nr,nc, i, cnt+1, cost);
            }
        }else if(abs(d-i)==2) {
            continue;
        }
        else{
            dfs(nr,nc, i, 1, cost);

        } 
    }
}
struct State{
    int r;
    int c;
    int d;
    int cnt;
    int cost;
    State(int rr, int cc, int dd, int ccnt,int ccost){
        r=rr;
        c=cc;
        d=dd;
        cnt=ccnt;
        cost=ccost;
    }
};
void bfs(){
    deque<State> q;

    State init{0,0,0,0,0};
    q.push_front(init);
    while(!q.empty()){
        //printf("!");
        auto e=q.front();
         //printf("(%d %d,%d %d,%d)\n",e.r,e.c,e.d,e.cnt,e.cost);
        q.pop_front();
        int cost=e.cost+mat[e.r][e.c]-'0';
        auto &v= states[e.r][e.c][e.d][e.cnt];
        if (v==-1 || cost <v){
            v=cost;
        }else{
            continue;
        }
        for(int i=0;i<4;i++){
            int nr=e.r+dir[dstr[i]].first;
            int nc=e.c+dir[dstr[i]].second;
            if(oob (nr,nc)) continue;
            if(e.d==i) {
                if(e.cnt==3) continue;
                else{
                        State ns{nr,nc,i,e.cnt+1,cost};
                        q.push_back(ns);
                }
            }else if(abs(e.d-i)==2) {
                continue;
            }
            else{
                    State ns{nr,nc,i,1,cost};
                    q.push_back(ns);

            } 
        }
    }
}
int main()
{
    memset(states,-1,sizeof(states));
    dir['^']={-1,0};
    dir['v']={1,0};
    dir['<']={0,-1};
    dir['>']={0,1};

    auto lines=readlines();
    for(auto line:lines){
        size_c=sz(line);
        strcpy(mat[size_r], line.c_str());
        size_r++;
    }

    mat[0][0]='0';

    //dfs(0,0,0,0,0);
    bfs();

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
    int v=            states[size_r-1][size_c-1][i][j];
        printf("<%d>",v);
        }

    return 0;
}