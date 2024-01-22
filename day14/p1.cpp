#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
map<char, pair<int,int> > dir;

char mat[150][150];
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

int main()
{
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

    int changed=1;
    int ans;
    while(changed){
        ans=0;
        changed=0;
        for(int r=0;r<size_r;r++){
            for(int c=0;c<size_c;c++){
                int nr=r-1;
                if(mat[r][c]!='O') continue;
                ans+=(size_r-r);
                if(nr<0) continue;
                if(mat[nr][c]=='.')
                {
                    mat[r][c]='.';
                    mat[nr][c]='O';
                    changed=1;
                }
            }
        }
    }
    printf("<%d>",ans);

    return 0;
}