#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

vector<pair<int,int> > pnts;

map<char, pair<int,int> > dd;

char mat[2000][2000];

string dstr="UDLR";
void flood(int sr,int sc){
    mat[0][0]='x';
    auto oob=[&sr,&sc](int r,int c){ 
        if(r<0) return 1;
        if(c<0) return 1;
        if(r>=sr) return 1;
        if(c>=sc) return 1;
        return 0;
    };
    while(1){
        int change=0;
        for(int r=0;r<sr;r++)
        {
            for(int c=0;c<sc;c++){
                if(mat[r][c]=='x'){
                    for(int i=0;i<4;i++){
                        auto delta= dd[dstr[i]];
                        int nr=r+delta.first;
                        int nc=c+delta.second;
                        if(!oob(nr,nc) && mat[nr][nc]!='#' && mat[nr][nc]!='x'){
                            change++;
                            mat[nr][nc]='x';
                        }
                    }
                }
            }
        }
        if(!change)break;
    }
}
int main()
{
    dd['U']={-1,0};
    dd['D']={1,0};
    dd['L']={0,-1};
    dd['R']={0,1};
    auto lines=readlines();

    pnts.push_back({0,0});
    for(auto line: lines){
        auto a=split_c(line," ()#");
        auto dir=a[0][0];
        int dist=-1;
        sscanf(a[1].c_str(),"%d",&dist);
        assert(dist!=-1);
        string color= a[2];
        pnts.push_back({pnts.back().first+dd[dir].first*dist, pnts.back().second+dd[dir].second*dist});
    }
    int min_r=999999;
    int min_c=999999;
    for(auto &pnt:pnts){
        min_r=min(min_r,pnt.first);
        min_c=min(min_c,pnt.second);
        printf("<%d,%d>",pnt.first,pnt.second);
    }
    min_r-=2;
    min_c-=2;
    printf("\n");
    int max_r=0;
    int max_c=0;
    for(auto &pnt:pnts){
        pnt.first-=min_r;
        pnt.second-=min_c;

        max_r=max(max_r,pnt.first);
        max_c=max(max_c,pnt.second);
        printf("<%d,%d>",pnt.first,pnt.second);
    }
    max_r+=2;
    max_c+=2;
    for(int r=0;r<max_r;r++){
        for(int c=0;c<max_c;c++){
            mat[r][c]='.';
        }
    }
    printf("\n");

    pnts.clear();
    pnts.push_back({-min_r,-min_c});

    for(auto line: lines){
        auto a=split_c(line," ()#");
        auto dir=a[0][0];
        int dist;
        sscanf(a[1].c_str(),"%d",&dist);
        string color= a[2];

        auto prev=pnts.back();
        for(int i=0;i<=dist;i++){
            int r=prev.first + i * dd[dir].first;
            int c=prev.second+i*dd[dir].second;
            //printf("<<%d,%d>>",r,c);
            mat[r][c]='#';
        }
        pnts.push_back({pnts.back().first+dd[dir].first*dist, pnts.back().second+dd[dir].second*dist});
    }

    for(auto &pnt:pnts){
        printf("<%d,%d>",pnt.first,pnt.second);
    }
    printf("\n");

    flood(max_r,max_c);

    for(int r=0;r<max_r;r++){
        for(int c=0;c<max_c;c++){
           printf("%c",mat[r][c]);
        }
        printf("\n");
    }
    long ans=0;
    for(int r=0;r<max_r;r++){
        for(int c=0;c<max_c;c++){
           char t=mat[r][c];
           if(t=='.'||t=='#') ans++;
        }
        //printf("\n");
    }
    printf("%ld",ans);
    //assert(pnts.back()==pnts[0]);
    return 0;
}