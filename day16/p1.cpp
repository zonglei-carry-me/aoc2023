#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;


map<int, pair<int,int> > dir;

char mat[150][150];
int states[150][150][4];
int size_r;
int size_c;
bool oob(int r,int c){
    if(r>=size_r) return true;
    if(c>=size_c) return true;
    if(r<0) return true;
    if(c<0) return true;
    return false;
}

const int UP=0;
const int RIGHT=1;
const int DOWN=2;
const int LEFT=3;

void dfs(int r,int c,int d);
void helper(int r,int c, int d){
     dfs(r+dir[d].first,c+dir[d].second, d);
}
void dfs(int r,int c,int d){
    if(oob(r,c)) return;
    if(states[r][c][d]) return;
    printf("<%d %d %d>",r,c,d);
    states[r][c][d]=1;
    if (mat[r][c]=='.'){
        dfs(r+dir[d].first,c+dir[d].second, d);
    }else if(mat[r][c]=='|' ){
        if(d==UP || d==DOWN){
            dfs(r+dir[d].first,c+dir[d].second, d);
        }else{
            helper(r,c,(d+1)%4);
            helper(r,c,(d+3)%4);
        }
    }
    else if(mat[r][c]=='-' ){
        if(d==LEFT || d==RIGHT){
            dfs(r+dir[d].first,c+dir[d].second, d);
        }else{
            helper(r,c,(d+1)%4);
            helper(r,c,(d+3)%4);
        }
    }
    else if(mat[r][c]=='/'  ) {
        if(d==RIGHT) helper(r,c,UP);
        if(d==LEFT)  helper(r,c,DOWN);
        if(d==UP)  helper(r,c,RIGHT);
        if(d==DOWN)  helper(r,c,LEFT);
    }   else if(mat[r][c]== '\\') {
        if(d==RIGHT) helper(r,c,DOWN);
        if(d==LEFT) helper(r,c,UP);
        if(d==UP)  helper(r,c,LEFT);
        if(d==DOWN)  helper(r,c,RIGHT);
    } else assert(false);
}


int main()
{
    memset(states,0,sizeof(states));
    dir[UP]={-1,0};
    dir[DOWN]={1,0};
    dir[LEFT]={0,-1};
    dir[RIGHT]={0,1};

    auto lines=readlines();
    for(auto line:lines){
        size_c=sz(line);
        strcpy(mat[size_r], line.c_str());
        size_r++;
    }


    dfs(0,0,RIGHT);

    printf("\n");
    int ans=0;
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            int eng=0;
            for(int i=0;i<4;i++){
                if (states[r][c][i]) eng=1;
            }
            if(eng) printf("#");
            else printf("%c",mat[r][c]);
            ans+=eng;
        }
        printf("\n");
    }
    printf("%d",ans);
    return 0;
}