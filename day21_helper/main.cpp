#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;


char mat[200][200];
char used[200][200];

int d[200][200];
int rs,cs;

int oob(int r, int c){
    if (r<0) return true;
    if (c<0) return true;
    if (r>=rs) return true;
    if (c>=cs) return true;
    return false;
}
int dr[]={0,1,-1,0};
int dc[]={-1,0,0,1};
int src_r,src_c;
set<pair<int,int>> st[5000+5];
int main()
{
    memset(d,-1,sizeof(d));
    auto lines=readlines();
    rs=0;
    for(auto line:lines){
        strcpy(mat[rs++],line.c_str());
        cs=sz(line);
    }

    int cnt=0;
    for(int r=0;r<rs;r++)
        for(int c=0;c<cs;c++){
            if (mat[r][c]=='S'){
                src_r=r;src_c=c;
            } 
            if (mat[r][c]=='#'){     
                cnt++;
            }
        }

    
    printf("<%d %d %d>\n",rs,cs,cnt);

    //src_r=5; src_c=5;
    st[0].insert({src_r,src_c});
    d[src_r][src_c]=0;
    const int step=500;
    for(int iter=1;iter<=step;iter++){
        for(auto e:st[iter-1]){
            for(int i=0;i<4;i++){
                int nr= e.first+dr[i];
                int nc= e.second+dc[i];
                //if(oob(nr,nc)) continue;
                int nnr=(nr%rs+rs)%rs;
                int nnc=(nc%cs+cs)%cs;
                //printf("<%d %d %d %d %d %d>\n",nnr,nnc,nr,nc,sr,sc);
                //printf("<%d %d %d %d>\n",nnr,nnc,sr,sc);
                if(mat[nnr][nnc]=='#') continue;
                if (d[nnr][nnc]==-1 && !oob(e.first,e.second)) {
                    d[nnr][nnc]=d[e.first][e.second]+1;
                }
                st[iter].insert({nr,nc});
            }
        }
        if(iter<20|| iter<100 && iter%10==0 || iter%100==0||iter%100==1) {
            printf("<iter=%d, %d, delta=%d>\n",iter,sz(st[iter]), sz(st[iter])-sz(st[iter-1]) );
        }
    }
    printf("<ans=%d>\n",sz(st[step]));


    int ill_cnt=0;
    for(int r=0;r<rs;r++)
    {
        for(int c=0;c<cs;c++){
            if(mat[r][c]=='#') printf("#");
            else if(d[r][c]==-1) printf("x");
            else {
                
                if(d[r][c] != abs(r-src_r)+abs(c-src_c)){
                    printf("!");
                    ill_cnt++;
                    //printf("\n%d %d\n",r,c);
                    //assert(0);
                    //printf("<%d %d %d>", r,c,d[r][c]);
                }
                else {
                    printf("%d",d[r][c]%10);
                }
            }
        }
        printf("\n");
    }
    printf("i=%d",ill_cnt);
    return 0;
}
