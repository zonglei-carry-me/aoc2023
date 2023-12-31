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



bool all_empty_c(int cc){
    for(int r=0;r<size_r;r++){
        if (mat[r][cc]!='.'){
            return false;
        }
    }
    return true;
}
void expand_c(int cc){
    for(int r=0;r<size_r;r++){
        for(int c=size_c;c>cc;c--){
            mat[r][c]=mat[r][c-1];
        }
    }
    size_c++;
}

bool all_empty_r(int rr){
    for(int c=0;c<size_c;c++){
        if (mat[rr][c]!='.'){
            return false;
        }
    }
    return true;
}
void expand_r(int rr){
    for(int c=0;c<size_c;c++){
        for(int r=size_r;r>rr;r--){
            mat[r][c]=mat[r-1][c];
        }
    }
    size_r++;
}

void prt(){
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            printf("%c", mat[r][c]);
        }
        printf("\n");
    }
    printf("-------------------\n");

}

vector<pair<int,int>> pnts;

vector<int> c_expands;
vector<int> r_expands;

long age=1000000;
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

    for(int c=0;c<size_c;c++){
        if(all_empty_c(c)) {c_expands.push_back(c);}
    }
    for(int r=0;r<size_r;r++){
        if(all_empty_r(r)) {r_expands.push_back(r);}
    }

    prt();

    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            if(mat[r][c]!='.'){
                int nr=r;
                int nc=c;
                for(auto e:c_expands){
                    if(e<c){
                        nc+=age-1;
                    }
                }
                for(auto e:r_expands){
                    if(e<r){
                        nr+=age-1;
                    }
                }
                pnts.push_back({nr,nc});
            }
        }
    }

    long sum=0;
    for(int i=0;i<pnts.size();i++)
        for(int j=i+1;j<pnts.size();j++){
            //if(i==j) continue;
            sum+= abs(pnts[i].first-pnts[j].first) +abs(pnts[i].second-pnts[j].second);
        }

    printf("\nans=%ld\n",sum);

    return 0;
}