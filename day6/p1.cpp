#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

vector<long> A;
vector<long> B;
int main()
{

    auto lines=readlines();

   
    auto a=split_c(lines[0]," ");
    int cnt=0;
    printf("%d\n",sz(a));
    for(auto e:a) {
            cnt++;
        if(cnt==1) continue;
        printf("<%s>",e.c_str());

        A.push_back(stoi(e));
    }

    auto b=split_c(lines[1]," ");
     printf("%d\n",sz(b));
    cnt=0;
    for(auto e:b){
        cnt++;
        if(cnt==1) continue;
        B.push_back(stoi(e));
     }

    long ans=1;

    for(int i=0;i<A.size();i++){
        printf("%d\n",i);
        auto aa=A[i];
        auto bb=B[i];

        double s1= (aa-sqrt( aa*aa- 4*bb))/2.0 +0.0001;
        double s2=(aa+sqrt( aa*aa- 4*bb))/2.0 -0.0001;

        long a=s1+0.999999;
        long b=s2;

        printf("float: %f %f\n",s1,s2);

        printf("[[%ld]]\n",b-a+1);
        ans*=b-a+1;
    }
    cout<<ans;

    return 0;
}