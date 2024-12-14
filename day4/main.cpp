#include "mylibs.h"
#include <cassert>
#include <cstdio>
#include <string>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

int cnt_cards[1000];
int main()
{
    auto lines=readlines();
    long ans=0;
    int idx=-1;
    for(auto line:lines){
        idx++;
        cnt_cards[idx]++;

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
                else score+=1;
            }

        }
        printf("score=%ld",score);
        for(int i=0;i<score;i++){
            cnt_cards[idx+i+1]+=cnt_cards[idx];
        }
         //ans+=score;
    }
    ans=0;
    printf("idx=%d\n",idx);
    for(int i=0;i<=idx;i++){
        //printf("<%d>",cnt_cards[i]);
        ans+=cnt_cards[i];
    }
    cout<<ans;
    return 0;
}