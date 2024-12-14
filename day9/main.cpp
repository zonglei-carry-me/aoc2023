#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

vector<long> vec[1000];
long ans=0;
void solve(){
    int n=vec[0].size();
    int deep; int i;
    for(i=1;;i++){
        int all_zero=true;
        vec[i].clear();
        for(int j=0;j<n-i;j++){
            vec[i].push_back(vec[i-1][j+1]-vec[i-1][j]);
            if(vec[i][j]) all_zero=false;
        }
        if(all_zero) break;
    }
    deep=i;

    for(int i=deep;i>=1;i--){
        vec[i-1].push_back(    vec[i-1].back()  +vec[i].back());
    }

    for(int i=0;i<=deep;i++)
    {
        for(int j=0;j<vec[i].size();j++){
            printf("[%ld]", vec[i][j]);
        }
        printf("\n");
    }

    ans+=vec[0].back();

    printf("-------\n");

}
int main()
{
    auto lines=readlines();
    for(auto line:lines){
        auto a=split_c(line," ");
        vector<long> v;
        for(auto b:a){
            long d;
            sscanf(b.c_str(), "%ld",&d);
            v.push_back(d);
        }
        reverse(v.begin(),v.end());
        vec[0]=v;
        solve();
    }

    printf("%ld",ans);
    return 0;
}