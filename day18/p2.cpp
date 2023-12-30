#include "mylibs.h"
#include <cassert>
#include <cstdio>
#include <sstream> 
#include <iostream> 
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

vector<pair<int,int> > pnts;

map<char, pair<int,int> > dd;

char mat[2000][2000];

string dstr="RDLU";
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
int new_format=1;

long labs(long a)
{
    if(a<0) return -a;
    return a;
}
void area()
{
    __int128 sum1=0;
    __int128 sum2=0;
    __int128 sum3=0;
    assert(pnts.back()==pnts[0]);
    pnts.pop_back();
    int n=pnts.size();

    for(int i=0;i<n;i++){
        sum1+= __int128(pnts[i].first)*pnts[(i+1)%n].second;
        sum2+= __int128(pnts[i].second)*pnts[(i+1)%n].first;
        sum3+= labs(pnts[(i+1)%n].first- pnts[i].first) +labs(pnts[(i+1)%n].second- pnts[i].second);
    }

    __int128 ans=labs( long(sum1-sum2))+sum3;
    ans/=2;
    ans+=1;
    cout<<"ans="<< long(ans);
}
int main()
{
    dd['U']={-1,0};
    dd['D']={1,0};
    dd['L']={0,-1};
    dd['R']={0,1};
    auto lines=readlines();
    if(new_format){
        for(auto &line: lines){
            auto a=split_c(line," ()#");
            string color= a[2];
            char dir=dstr[color[5]-'0'];
            color.pop_back();
            long dist;
            sscanf(color.c_str(),"%lx",&dist);

            stringstream ss;
            ss<<dir<<" "<<dist;
            line=ss.str();
            
        }

        for(auto &line: lines){
            printf("%s\n",line.c_str());
        }
    }

    pnts.push_back({0,0});
    for(auto line: lines){
        auto a=split_c(line," ()#");
        auto dir=a[0][0];
        int dist=-1;
        sscanf(a[1].c_str(),"%d",&dist);
        assert(dist!=-1);
        
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
    printf("\n");
    max_r+=2;
    max_c+=2;

    pnts.clear();
    pnts.push_back({-min_r,-min_c});

    if(!new_format){

        for(int r=0;r<max_r;r++){
            for(int c=0;c<max_c;c++){
                mat[r][c]='.';
            }
        }
        printf("\n");
    }

    for(auto line: lines){
        auto a=split_c(line," ()#");
        auto dir=a[0][0];
        int dist;
        sscanf(a[1].c_str(),"%d",&dist);
        //string color= a[2];

        auto prev=pnts.back();
        if(!new_format){
            for(int i=0;i<=dist;i++){
                int r=prev.first + i * dd[dir].first;
                int c=prev.second+i*dd[dir].second;
                //printf("<<%d,%d>>",r,c);
                mat[r][c]='#';
            }
        }
        pnts.push_back({pnts.back().first+dd[dir].first*dist, pnts.back().second+dd[dir].second*dist});
    }

    for(auto &pnt:pnts){
        printf("<%d,%d>",pnt.first,pnt.second);
    }
    printf("\n");




    if(!new_format){
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
    }

    area();

    //assert(pnts.back()==pnts[0]);
    return 0;
}