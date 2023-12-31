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
    for(auto line: lines){
        int a,b;
        for(int i=0;i<sz(line);i++){
            if(line[i]>='0' &&line[i]<='9'){
                a=line[i]-'0';
                break;
            }
        }
        for(int i=sz(line)-1;i>=0;i--){
            if(line[i]>='0' &&line[i]<='9'){
                b=line[i]-'0';
                break;
            }
        }
        ans+=a*10+b;
    }
    cout<<ans;
    return 0;
}