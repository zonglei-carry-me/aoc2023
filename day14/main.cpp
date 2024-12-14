#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
map<char, pair<int,int> > dir;

char mat[150][150];
char mat2[150][150];
int size_r;
int size_c;
bool oob(int r,int c){
    if(r>=size_r) return true;
    if(c>=size_c) return true;
    if(r<0) return true;
    if(c<0) return true;
    return false;
}
string dstr="^<v>";

void run(int d)
{
    int changed=1;
    while(changed){
        //ans=0;
        changed=0;
        for(int r=0;r<size_r;r++){
            for(int c=0;c<size_c;c++){
                int nr=r+dir[dstr[d]].first;
                int nc=c+dir[dstr[d]].second;
                if(mat[r][c]!='O') continue;
                //ans+=(size_r-r);
                if(oob(nr,nc)) continue;
                if(mat[nr][nc]=='.')
                {
                    mat[r][c]='.';
                    mat[nr][nc]='O';
                    changed=1;
                }
            }
        }
    }
}

int count(){
    int ans=0;
        for(int r=0;r<size_r;r++){
            for(int c=0;c<size_c;c++){
                if(mat[r][c]!='O') continue;
                ans+=(size_r-r);
            }
        }
    return ans;
}

string to_string(){
    string s;
            for(int r=0;r<size_r;r++){
            for(int c=0;c<size_c;c++){
                s+=mat[r][c];
            }
        }
        return s;
}
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

    map<string,int> hh;
    //hh[to_string()]= 0;
    int steps=1000000000;
    memcpy(mat2,mat,sizeof(mat));
    int cycle=-1;
    for(int i=1;i<=steps;i++){
        run(0);
        run(1);
        run(2);
        run(3);
        printf("<iter=%d, ans= %d>\n",i+1,count());

        string s=to_string();
        if(hh.find(s)!=hh.end()){
            printf("<cycle=%d>", i-hh[s]);
            cycle=i-hh[s];
            break;
        }
        hh[s]=i;
    }

    memcpy(mat,mat2,sizeof(mat));

    for(int i=1;i<=steps%(cycle*5) ;i++){
        run(0);
        run(1);
        run(2);
        run(3);
        printf("<iter=%d, ans= %d>\n",i+1,count());
    }
    

    

    return 0;
}