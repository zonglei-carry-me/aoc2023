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
    printf("%s\n",s.c_str());
    auto ss=split_c(s,".");
    if(ss.size()!=v.size()) return false;
    for(int i=0;i<ss.size();i++){
        if(ss[i].size()!=v[i]) return false;

    }
    return true;
}
string cl=".#";
void dfs(int idx, int group,int running_len){
    //printf("<%d %d %d; %s>\n",idx,group,running_len, s.c_str());
    //auto ss=split_c(s,".");
    //if(ss.size()<v.size()) return;
    //verify();
    if(idx==size(s)){
        if(running_len==0){
            if(group!=v.size()) return;
        }else{
            if(group!=v.size()-1) return;
            if(v.back()!=running_len) return;
        }
        //if(verify()) cnt++;
        cnt++;
        return;
    }
    if(group>=sz(v) && running_len>0) return;
    if(group<sz(v) && running_len > v[group]) return;

    if(s[idx]!='?'){
        if(s[idx]=='#'){
            //running_len++;
            dfs(idx+1,group,running_len+1);
        }
        else{
            if(running_len>0){
                if(v[group]!=running_len) return;
                dfs(idx+1,group+1,0);
            }else{
                dfs(idx+1,group,0);
            }
        }
    }else{
        for(auto c:cl){
            s[idx]=c;
            dfs(idx, group, running_len);
        }
        s[idx]='?';
    }
}

int repeat=4;
int solve(string s0, vector<int> &v0){
    ::s=s0;
    ::v=v0;
    for(int i=0;i<repeat;i++){
        s+="?";
        s+=s0;
        for(auto e:v0){
            v.push_back(e);
        }
    }
    cnt=0;
    ::s=s; ::v=v;
    printf("%s\n",s.c_str());
    for(auto e:v) printf("%d,",e);
    printf("\n");
    //s="???";v={1,1};
    dfs(0, 0,0);
    printf("------\n");
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