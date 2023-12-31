#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
map<char,int> card_value;
vector<pair<string,int>> inputs;

int type(string s){
    map<char,int> stat;
    for(auto e: s) stat[e]++;
    if(sz(stat)==1) return 7;
    if(sz(stat)==2) {
        if(stat.begin()->second ==1 || stat.begin()->second==4){
            return 6;
        }
        if(stat.begin()->second ==2 || stat.begin()->second==3){
            return 5;
        }
        assert(false);
    }
    if(sz(stat)==3) {
        for(auto e: stat) {
            if(e.second==3) return 4;
        }
        for(auto e: stat) {
            if(e.second==2) return 3;
        }
        assert(false);
    }
     if(sz(stat)==4) return 2;
     printf("%s\n",s.c_str());
     assert(sz(stat)==5);
     return 1; 
}
bool cmp2(const string &a, const string &b){
    for(int i=0;i<5;i++){
        //printf("<<%s %s %c>>",a.c_str(),b.c_str(),a[i]);
        assert(card_value.find(a[i])!=card_value.end());
        if(a[i]!=b[i])return card_value[a[i]]< card_value[b[i]];
    }
    printf("<%s %s>\n",a.c_str(),b.c_str());
    //return false;
    assert(false);
}
bool cmp(const pair<string,int>&a, const pair<string,int>&b){
    if(a==b) return false;
    if(type(a.first)!=type(b.first)){
        return type(a.first)<type(b.first);
    }
    else return cmp2(a.first,b.first);
}
int main()
{
    card_value['A']=14;
    card_value['K']=13;
    card_value['Q']=12;
    card_value['J']=11;
    card_value['T']=10;

    for(int i=2;i<=9;i++){
        card_value['0'+i]=i;
    }

    auto lines=readlines();

    for(auto line:lines){
        auto a=split_c(line," ");
        auto b=a[0];
        int c;
        sscanf(a[1].c_str(),"%d",&c);
        inputs.push_back({b,c});
    }

    sort(inputs.begin(),inputs.end(),cmp);

    long ans=0;
    for(int i=0;i<sz(inputs);i++){
        //sort(inputs[i].first.begin(),inputs[i].first.end());
        printf("%s\n",inputs[i].first.c_str());
        ans+=(i+1)* inputs[i].second;
    }
    cout<<ans<<endl;
    
    return 0;
}