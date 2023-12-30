#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
map<char, pair<int,int> > dir;

char mat[150][150];
int states[150][150][4][11];
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

int max_run=10;
int min_run=4;
void bfs(){
    deque<State> q;

    State init{0,0,0,1,0};
    State init2{0,0,1,1,0};
    q.push_front(init);
    q.push_front(init2);
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
                if(e.cnt==max_run) continue;
                else{
                        State ns{nr,nc,i,e.cnt+1,cost};
                        q.push_back(ns);
                }
            }else if(abs(e.d-i)==2) {
                continue;
            }
            else{
                    if(e.cnt>=min_run){
                        State ns{nr,nc,i,1,cost};
                        q.push_back(ns);
                    }

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

    int ans=999999;
    for(int i=0;i<4;i++)
        for(int j=min_run;j<max_run+1;j++){
    int v=            states[size_r-1][size_c-1][i][j];
        printf("<%d>",v);
        if(v!=-1) ans=min(ans,v);
        }

    printf("\nans=%d\n",ans);

    return 0;
}