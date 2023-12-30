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
string dstr="^<v>";

bool refl_v(int cc){

    for(int r=0;r<size_r;r++)
    {
        int cl=cc-1;
    int cr=cc;
        for(;cl>=0 && cr<size_c; cl--,cr++){
            if(mat[r][cl]!=mat[r][cr]){
                return false;
            }
        }
    }
    return true;
}
int find_v(){
    for(int c=1;c<size_c;c++)
    {
        if(refl_v(c)) return c;
    }
    return 0;
}

bool refl_h(int rrr){

    for(int c=0;c<size_c;c++)
    {
        int left=rrr-1;
        int right=rrr;
        for(;left>=0 && right<size_r; left--, right++){
            if(mat[left][c]!=mat[right][c]){
                return false;
            }
        }
    }
    return true;
}
int find_h(){
    for(int r=1;r<size_r;r++)
    {
        if(refl_h(r)) return r;
    }
    return 0;
}
long sum;
int solve()
{
    //assert(size_r==size_c);
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
                printf("%c",mat[r][c]);
        }
        printf("\n");
    }

    printf("<%d>\n",find_v());
     printf("<%d>\n",find_h());
    printf("-------\n");
    int v=find_v();
    int h=find_h();
    sum+=v+h*100;

    return 0;
}

int main()
{
    dir['^']={-1,0};
    dir['v']={1,0};
    dir['<']={0,-1};
    dir['>']={0,1};

    auto lines=readlines();
    lines.push_back("");
    for(auto line:lines){
        if(line=="") {
            solve();
            size_r=0;
            continue;
        }
        size_c=sz(line);
        strcpy(mat[size_r], line.c_str());
        size_r++;
    }
    
    printf("<%ld>",sum);

    

    return 0;
}