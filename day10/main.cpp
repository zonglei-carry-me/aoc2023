#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
map<char, pair<int,int> > dir;

char mat[300][300];
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

void prt(){
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            printf("%c", mat[r][c]);
        }
        printf("\n");
    }
    printf("-------------------\n");

}

map<char, string> pipes;


bool in(char c, string s){
    return s.find(c)!=string::npos;
}


// from ...to....
int connected(int r1,int c1, int r2,int c2){
    if(oob(r2,c2)) return false;
    char tile1=mat[r1][c1];
    char tile2=mat[r2][c2];
    if(abs(r1-r2)==1 && abs(c1-c2)==1) assert(false);
    if(r1-r2==0 && c1-c2==0 ) assert(false);
    if( r1-r2==1) {
        return in('^', pipes[tile1]) && in('v', pipes[tile2]);
    }
    else if( r2-r1==1){
        return in('^', pipes[tile2]) && in('v', pipes[tile1]);
    }
    else if( c1-c2==1){
        return in('<', pipes[tile1]) && in('>', pipes[tile2]);
    }
    else if (c2-c1==1){
        return in('<', pipes[tile2]) && in('>', pipes[tile1]);
    }
    assert(false);
}

int visited[300][300];
int found=0;

vector<pair<int,int> > path;
void dfs(int r,int c,int step){
    if(found) return;
    if(mat[r][c]=='S' && visited[r][c] && step>3){
        printf("found!!!\n");
        found=1;
        return;
    }
    if(visited[r][c]) return;

    visited[r][c]=step;
    path.push_back({r,c});

    for(auto d: dstr){
        int nr= dir[d].first+r;
        int nc= dir[d].second+c;
        if(connected(r, c, nr, nc)){
            dfs(nr,nc,step+1);
        }
    }
    if(found) return;

    visited[r][c]=0;
    path.pop_back();
}
long area()
{
    long sum1=0,sum2=0;
    int n=path.size();
    for(int i=0;i<path.size();i++)
    {
        sum1+= path[i].first* path[(i+1)%n].second;
        sum2+= path[i].second* path[(i+1)%n].first;
    }

    return abs(sum1-sum2)/2;
}
void prt2(){
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            if(visited[r][c]){
                printf("%d",visited[r][c]%10);
            }
            else printf("%c", mat[r][c]);
        }
        printf("\n");
    }
    printf("-------------------\n");

}
int main()
{
    dir['^']={-1,0};
    dir['v']={1,0};
    dir['<']={0,-1};
    dir['>']={0,1};

    pipes['|']="^v";
    pipes['-']="<>";
    pipes['L']="^>";
    pipes['J']="<^";
    pipes['7']="<v";
    pipes['F']="v>";

    pipes['S']="^v<>";

    auto lines=readlines();
    for(auto line:lines){
        size_c=sz(line);
        strcpy(mat[size_r], line.c_str());
        size_r++;
    }

    int start_r=-1,start_c=-1;
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            if(mat[r][c]=='S')
            {
                start_r=r;
                start_c=c;
            }
        }
    }

    dfs(start_r,start_c,1);

    prt();

    printf("=======\n");
    prt2();

    vector<int> vec;
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            if(visited[r][c]){
                printf("<%d>",visited[r][c]);
                vec.push_back(visited[r][c]);
            }
        }
    }

    assert(vec.size()%2==0);
    assert(path.size()==vec.size());
    sort(vec.begin(),vec.end());
    printf("\nans=%d\n",vec[vec.size()/2]-1);

    printf("ans2=%ld", area()- sz(path)/2 +1 );

    return 0;
}