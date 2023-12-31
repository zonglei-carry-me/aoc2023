#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

map<string, pair<string,string>>  xx;

string inst;
int main()
{
    auto lines=readlines();

    inst=lines[0];
    vector<string> currs;
    for(int i=2;i<sz(lines);i++){
        auto a=split_c(lines[i]," =(,)");
        assert(sz(a)==3);
        xx[a[0]]={a[1],a[2]};

        if(a[0].back()=='A') currs.push_back(a[0]);
    }

    map<string,vector<long>> mp;
    for(long i=0;;i++){
        auto c=inst[i%inst.size()];

        if(i%100000==0){
            long step=1;
            for(auto e:mp){
                printf("%s:",e.first.c_str());
                for(auto f:e.second){
                    printf(" %ld", f);
                }
                printf("\n");
                step*= e.second[0];
                if(e.second.size()>=2) assert(e.second[1]==2*e.second[0]);
            }

            for(auto e:mp){
                printf("%ld,",e.second[0]);
            }
            printf("\n-----%ld-----\n",step);
        }
        
        int okay=1;
        for(int j=0;j<sz(currs);j++){
            if(c=='R') {
                currs[j]= xx[currs[j]].second;
            }else{
                currs[j]= xx[currs[j]].first;
            }

            if(currs[j].back()!='Z') okay=0;
            else{
                mp[currs[j]].push_back(i+1);
            }
        }

        if(okay){
            printf("%ld",i+1);
            return 0;
        }
    }

    
    return 0;
}