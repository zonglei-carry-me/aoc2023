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

vector<pair<string,int> > boxes[256];
int main()
{
    auto line=readlines()[0];
    auto strs=split_c(line,",");

    long sum=0;
    for(auto str:strs){
        //int h=hhash(str);
        //printf("%d\n",h);
        //sum+=h;
        string label=split_c(str,"-=")[0];
        int fl=-1;char c;
        
        if (str.find('-') ==string::npos){
            fl= str.back()-'0';
            c = str[str.size()-2];
        }
        else{
            c=str.back();
        }

        printf("<%s %c %d; %d>", label.c_str(), c,fl, hhash(label));
        auto h=hhash(label);
        if(c=='-'){
            auto &box=boxes[h];
            for(int i=0;i<box.size();i++){
                if(box[i].first==label){
                    box.erase(box.begin()+i);
                    break;
                }
            }
        }else{
            auto &box=boxes[h];
            int found=0;
            for(int i=0;i<box.size();i++){
                if(box[i].first==label){
                    box[i].second=fl;
                    found=1;
                    break;
                }
            }
            if(!found){
                box.push_back({label,fl});
            }
        }
    }
    sum=0;
    for(int i=0;i<256;i++){
        auto box=boxes[i];
        for(int j=0;j<box.size();j++){
            sum+=(i+1)*(j+1)*box[j].second;
        }
    }
    printf("<%ld>",sum);


    return 0;
}