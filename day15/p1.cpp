#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

int hhash(string &s){
    int h=0;
    for(auto c:s){
        h+=c;
        h*=17;
        h%=256;
    }
    return h;
}
int main()
{
    auto line=readlines()[0];
    auto strs=split_c(line,",");

    long sum=0;
    for(auto str:strs){
        int h=hhash(str);
        printf("%d\n",h);
        sum+=h;
    }
    printf("<%ld>",sum);


    return 0;
}