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
    for(int i=2;i<sz(lines);i++){
        auto a=split_c(lines[i]," =(,)");
        assert(sz(a)==3);
        xx[a[0]]={a[1],a[2]};
    }

    string curr="AAA";
    for(int i=0;;i++){
        auto c=inst[i%inst.size()];

        if(c=='R') {
            curr= xx[curr].second;
        }else{
            curr= xx[curr].first;
        }

        if(curr=="ZZZ"){
            printf("%d",i+1);
            return 0;
        }
    }

    
    return 0;
}