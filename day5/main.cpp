#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

struct Mapping{
    long dst;
    long src;
    long range;
    Mapping(long aa,long bb,long cc){
        dst=aa;
        src=bb;
        range=cc;
    }
};
int n_mapppings;
vector<Mapping> mappings[10]; 

vector<long>seeds;
vector<long>range_seeds;

long convert(int idx, long input){
    for(auto &m:mappings[idx]){
        if(input>=m.src && input<m.src+m.range) {
            return m.dst+ (input-m.src);
        }
    }
    return input;
}
int main()
{
    auto lines=readlines();
    auto seeds_line= lines[0];
    lines.erase(lines.begin());
    lines.erase(lines.begin());
    lines.push_back("");

    int cnt=0;
    for(auto e: split_c(seeds_line, "sed :")){
        if(cnt%2==0) 
        //printf("<%s>",e.c_str());
        seeds.push_back(stol(e));
        else{
            range_seeds.push_back(stol(e));
        }
        cnt++;
    }

    for(auto line:lines){
        if(line.find("map")!=string::npos ){
            continue;
        }

        if(line=="") {
            n_mapppings++;
            continue;
        }
        auto a=split_c(line," ");
        Mapping mapping{stol(a[0]),stol(a[1]),stol(a[2])};
        mappings[n_mapppings].push_back(mapping);

    }

    long minloc=1000l*1000*1000*1000*1000;
    for(int i=0;i<sz(seeds);i++){
        printf("!!\n");
        auto seed=seeds[i];
        auto rrr=range_seeds[i];
        for(auto j=seed; j<seed+rrr;j++){
            //printf("<%ld>",seed);
            long value=j;
            for(int k=0;k<n_mapppings;k++){
                value=convert(k, value);
            }
            
            minloc=min(minloc,value);
        }
       
    }

    printf("nseeds=%d n_mappings=%d\n",sz(seeds),n_mapppings);

    cout<<minloc<<endl;

    return 0;
}