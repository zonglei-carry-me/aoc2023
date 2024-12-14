#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
string s;
vector<int> v;
int cnt=0;
bool verify(){
    //printf("%s\n",s.c_str());
    auto ss=split_c(s,".");
    if(ss.size()!=v.size()) return false;
    for(int i=0;i<ss.size();i++){
        if(ss[i].size()!=v[i]) return false;

    }
    return true;
}
void dfs(int idx){
    if(idx==sz(s)){
        if(verify()) cnt++;
        return;
    }
    if(s[idx]!='?'){
        dfs(idx+1);
    }else{
        s[idx]='.';
        dfs(idx+1);
        s[idx]='#';
        dfs(idx+1);
        s[idx]='?';
    }
}
int solve(string s, vector<int> &v){
    cnt=0;
    ::s=s; ::v=v;
    dfs(0);
    return cnt;
}
int main()
{
    auto lines=readlines();
    long ans=0;
    for(auto line:lines){
        auto a=split_c(line," ")[0];
        auto b=split_c(line," ")[1];

        vector<int> v;
        auto c=split_c(b,",");
        for(auto d: c){
            int x=-1;
            sscanf(d.c_str(),"%d",&x);
            assert(x!=-1);
            v.push_back(x);
        }
        ans+=solve(a,v);
    }
    printf("%ld",ans);
    return 0;
}
