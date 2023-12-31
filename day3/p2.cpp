#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

char mat[150][150];
int states[150][150][4][11];
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

struct Num{
    int r;
    int start_c;
    int end_c;
    int value;

    int is_adj=0;
    Num(int a,int b,int c,int d){
        r=a;start_c=b;end_c=c;value=d;
    }

    bool adj(int rr,int cc){
        if(abs(r -rr) >1) {
            return false;
        }
        if( cc<start_c-1 ) return false;
        if(cc >end_c+1) return false;
        return true;
    }
};

vector<Num> nums;

int main()
{
    memset(states,-1,sizeof(states));
    auto lines=readlines();
    for(auto line:lines){
        size_c=sz(line);
        strcpy(mat[size_r], line.c_str());
        size_r++;
    }

    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            if(mat[r][c]>='0' &&mat[r][c]<='9'){
                int d=-1;
                sscanf(&mat[r][c], "%d",&d);
                char buf[100];
                snprintf(buf,100,"%d",d);
                int len=strlen(buf);
                nums.push_back(Num{r,c,c+len-1, d});
                c+=len;
            }
        }
    }

    long ans=0;
    for(int r=0;r<size_r;r++){
        for(int c=0;c<size_c;c++){
            if(! (mat[r][c]>='0' &&mat[r][c]<='9')  && mat[r][c]!='.'){
                printf("<%c>",mat[r][c]);
                int cnt=0;
                for(auto& num:nums)
                {
                    if (num.adj(r, c)){
                        num.is_adj=1;
                    cnt++;}
                }

                if(cnt==2){
                        long value=1;
                    for(auto& num:nums)
                    {
                        if (num.adj(r, c)){
                            //printf("<%d>",num.value);
                            value*=num.value;
                         }
                    }
                    ans+=value;
                }

            }
        }
    }
    cout<<ans;

    return 0;
}