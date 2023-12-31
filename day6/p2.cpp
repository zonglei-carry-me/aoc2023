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
    auto b=split_c(lines[1]," ");

    string aa;
    for(int i=1;i<a.size();i++){
        aa+=a[i];
    }
    
    string bb;
    for(int i=1;i<b.size();i++){
        bb+=b[i];
    }

    A.push_back(stol(aa));
    B.push_back(stol(bb));

    long ans=1;

    for(int i=0;i<A.size();i++){
        printf("%d\n",i);

 
        auto aa=A[i];
        auto bb=B[i];

        printf("<A %ld  B%ld>",aa, bb);

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