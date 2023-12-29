#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;


char mat[200][200];
char used[200][200];
int rs,cs;

/*
int oob(int r, int c){
    if (r<0) return true;
    if (c<0) return true;
    if (r>=rs) return true;
    if (c>=cs) return true;
    return false;
}*/
int dr[]={0,1,-1,0};
int dc[]={-1,0,0,1};
int sr,sc;
set<pair<int,int>> st[5000+5];
int main()
{
    auto lines=readlines();
    rs=0;
    for(auto line:lines){
        strcpy(mat[rs++],line.c_str());
        cs=sz(line);
    }

    for(int r=0;r<rs;r++)
        for(int c=0;c<cs;c++){
            if (mat[r][c]=='S'){
                sr=r;sc=c;
            }        
        }
    st[0].insert({sr,sc});
    const int step=5000;
    for(int iter=1;iter<=step;iter++){
        for(auto e:st[iter-1]){
            for(int i=0;i<4;i++){
                int nr= e.first+dr[i];nr%=sr;
                int nc= e.second+dc[i];nc%=sc;
                //if(oob(nr,nc)) continue;
                if(mat[nr][nc]=='#') continue;
                st[iter].insert({nr,nc});
            }
        }
        printf("<%d>\n",sz(st[iter]));
    }
    printf("<ans=%d>\n",sz(st[step]));
    return 0;
}