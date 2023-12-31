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

long convert(int idx, long input){
    for(auto m:mappings[idx]){
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

    for(auto e: split_c(seeds_line, "sed :")){
        //printf("<%s>",e.c_str());
        seeds.push_back(stol(e));
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
    for(auto seed:seeds){
        vector<long> values;
        values.push_back(seed);
        for(int i=0;i<n_mapppings;i++){
            values.push_back( convert(i, values.back()) );
        }
        minloc=min(minloc,values.back());
    }

    printf("nseeds=%d n_mappings=%d\n",sz(seeds),n_mapppings);

    cout<<minloc<<endl;

    return 0;
}