#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

int main()
{
    auto lines=readlines();
    long ans=0;
    for(int i=0;i<sz(lines);i++){

        map<string,int> stat;
        auto a=split_c(lines[i],":")[1];
        auto b=split_c(a,";");
        for(auto c: b){
            auto d=split_c(c,",");
            for(auto e:d){
                auto f=split_c(e," ")[0];
                auto g=split_c(e," ")[1];

                cout<<f<<g<<endl;
                if(stat[g]<stoi(f)){
                    stat[g]=stoi(f);
                }
            }
        }
        /*if(stat["red"]<=12 && stat["green"]<=13 && stat["blue"]<=14){
            ans+=(i+1);
        }*/
        ans+=stat["red"]*stat["green"]* stat["blue"];

    }
    cout<<ans;
    return 0;
}