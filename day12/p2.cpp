#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
string s;
vector<int> v;
long one_ans=0;
string cl=".#";

int repeat=4;
long S[200][200];

int N;
int M;

int cnt_native=0;
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
    if(idx==size(s)){
        if(verify()) cnt_native++;
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
int solve_naive(string s, vector<int> &v){
    cnt_native=0;
    ::s=s; ::v=v;
    dfs(0);
    return cnt_native;
}

void do_dp(){

    memset(S,0,sizeof(S));
    N=sz(s);
    M=sz(v);

    // init
    {
        int m=1;
        for(int n=1;n<=N;n++){
            int group_size= v[m-1];
            if(group_size >n) continue;
            long cnt=1;
            for(int i=0;i<group_size;i++){
                char c=s[n-1-i];
                if (c=='.'){cnt=0;}
                else if (c=='?'){}
                else if (c=='#'){}
                else assert(false);
            }
            for(int i=0;i<n-group_size;i++){
                if(s[i]=='#') cnt=0;
            }
            S[n][m]+=cnt;
        }
    }

    for(int m=2;m<=M;m++){
        for(int n=1;n<=N;n++){
            int group_size= v[m-1];
            if(group_size >n) continue;
            long cnt=1;
            for(int i=0;i<group_size;i++){
                char c=s[n-1-i];
                if (c=='.'){cnt=0;}
                else if (c=='?'){}
                else if (c=='#'){}
                else assert(false);
            }
            for(int i=n-group_size-1;i>=1 ;i--){
                if(s[i]=='#') break;
                S[n][m]+= cnt* S[i][m-1];
            }
        }
    }

    if(0){
        for(int n=0;n<=N;n++){
            for(int m=0;m<=M;m++){
                printf("<s[%d][%d]=%ld>", n,m, S[n][m]);
            }
            printf("\n");
        }
    }

    long sum=0;

    for(int n=0;n<=N;n++){
        int ok=1;
        for(int i=n;i<N;i++){
            if (s[i]=='#') ok=0;
        }
        if(ok)
        sum+=S[n][M];
    }


    one_ans+=sum;




}
long solve(string s0, vector<int> &v0){
    ::s=s0;
    ::v=v0;
    for(int i=0;i<repeat;i++){
        s+="?";
        s+=s0;
        for(auto e:v0){
            v.push_back(e);
        }
    }
    one_ans=0;
    ::s=s; ::v=v;
    printf("%s\n",s.c_str());
    for(auto e:v) printf("%d,",e);
    printf("\n");

    do_dp();
    printf("------\n");

    /*long ans_naive= solve_naive(::s, ::v);
    if(ans_naive!= one_ans){
        printf("not match !!!!!!!! naive=%ld  me=%ld\n",ans_naive,one_ans);
        assert(false);
    }*/
    return one_ans;
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