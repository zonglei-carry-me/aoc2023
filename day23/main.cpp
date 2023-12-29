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

int oob(int r, int c){
    if (r<0) return true;
    if (c<0) return true;
    if (r>=rs) return true;
    if (c>=cs) return true;
    return false;
}
int sr,sc;
int er,ec;
int dr[]={0,1,-1,0};
int dc[]={-1,0,0,1};
int mdr[255];
int mdc[255];

int length=0;
int ans=0;
void dfs(int r, int c ){
//printf("[%d %d]\n",r,c);
    if(oob(r,c)) return;
    if (mat[r][c]=='#') return;
    if(used[r][c]==1){
        //printf("fuck\n");
        return;
    }
    //for(int i=0;i<length;i++) printf(" ");
    //printf("<%d %d>\n",r,c);

    used[r][c]=1; length++;

    if(r==er && c==ec) {
        ans=max(ans,length);
    }

    if (mat[r][c]=='.'|| true) {
        for(int i=0;i<4;i++){
            auto nr=r+dr[i];
            auto nc=c+dc[i];
            dfs(nr,nc);
        }
    }else{
        char a=mat[r][c];
        auto nr=r+mdr[a];
        auto nc=c+mdc[a];
        dfs(nr,nc);
    }
    length--;
    used[r][c]=0;
}
int main()
{
    mdr['^']=-1;
    mdr['v']=1;
    mdc['<']=-1;
    mdc['>']=1;

    auto lines=readlines();
    rs=0;
    for(auto line:lines){
        strcpy(mat[rs++],line.c_str());
        cs=sz(line);
    }
    for(int i=0;i<cs;i++){
        if (mat[0][i]=='.') sr=0,sc=i;
        if( mat[rs-1][i]=='.') er=rs-1, ec=i;
    }

    printf("start= %d %d, end=%d %d, size=%d,%d\n", sr,sc,er,ec,rs,cs);

    dfs(sr,sc);

    printf("ans=%d\n",ans-1);

    return 0;
}