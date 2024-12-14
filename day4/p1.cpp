#include "mylibs.h"
#include <cassert>
#include <cstdio>
#include <string>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

int main()
{
    auto lines=readlines();
    long ans=0;
    for(auto line:lines){
        auto a=split_c(line,":")[1];
        auto b=split_c(a,"|")[0];
        auto c=split_c(a,"|")[1];

        auto d=split_c(b," ");
        auto e=split_c(c," ");

        set<int> st;
        for(auto f: e){
            int a=stoi(f);
            st.insert(a);
        }
        long score=0;
        for(auto g:d){
            int a=stoi(g);
            if(st.find(a)!=st.end()){
                if(score==0) score=1;
                else score*=2;
            }

        }
         ans+=score;
    }
    cout<<ans;
    return 0;
}