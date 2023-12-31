#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

string numstr[]={"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
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
            for(int j=0;j<9;j++){
                printf("<%s %s>\n", line.c_str()+i,  numstr[j].c_str());
                if(strncmp(line.c_str()+i, numstr[j].c_str(),  numstr[j].size()) ==0 ){
                    a=j+1;
                    printf("<<<<%d>>>>",a);
                    //break;
                    goto line1;
                }
            }
            
        }
        line1:;

        for(int i=sz(line)-1;i>=0;i--){
            if(line[i]>='0' &&line[i]<='9'){
                b=line[i]-'0';
                break;
            }
            for(int j=0;j<9;j++){
                if(strncmp(line.c_str()+i, numstr[j].c_str(),numstr[j].size()) ==0 ){
                    b=j+1;
                    //break;
                    goto line2;
                }
            }
            
        }
        line2:;
        printf("{%d %d}",a,b);
        ans+=a*10+b;
    }
    cout<<ans;
    return 0;
}