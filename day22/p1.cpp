#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

struct Pnt{
    int pos[3];
    Pnt(){
    }
    Pnt(string s){
        auto t=split_c(s,",");
        for(int i=0;i<3;i++){
            sscanf(t[i].c_str(),"%d", pos+i);
        }
    }

    string to_string(){
        auto res=string("");
        for (int i=0;i<3;i++){
            if(i) res+=',';
            res+=std::to_string(pos[i]);
        }
        return res;
    }

    int &x(){
        return pos[0];
    }
    int &y(){
        return pos[1];
    }
    int &z(){
        return pos[2];
    }
};

struct Brick{
    Pnt ends[2];
    vector<Pnt> cubes(){
        vector<Pnt> res;
        for(int i=0;i<3;i++){
            if (ends[0].pos[i]!=ends[1].pos[i]){
                int sign=1;
                if (ends[1].pos[i]< ends[0].pos[i]) sign=-1;
                for (int j=ends[0].pos[i];j<=ends[1].pos[i];j+=sign){
                    Pnt pnt;
                    pnt=ends[0];
                    pnt.pos[i]=j;
                    res.push_back(pnt);
                }
                return res;
            }
        
        }
        res.push_back(ends[0]);
        return res;
    }

    int lowest_z(){
        return min(ends[0].z(),ends[1].z());
    }

    vector<int> support_by;
    vector<int> supports;
};

vector<Brick> bricks;

int used[2000];
int inf=9999999;
int main()
{
    auto lines= readlines();
    for(auto line: lines) {
        auto a=split_c(line,"~")[0];
        auto b=split_c(line,"~")[1];

        Brick tmp;
        tmp.ends[0]=Pnt(a);
        tmp.ends[1]=Pnt(b);
        if(tmp.ends[0].z()> tmp.ends[1].z()) swap(tmp.ends[0],tmp.ends[1]);
        bricks.push_back(tmp);

        printf("<%s;%s>\n", tmp.ends[0].to_string().c_str(), tmp.ends[1].to_string().c_str());

        for(auto b: tmp.cubes()){
            printf("[%s]", b.to_string().c_str());
        }
        printf("\n");
    }

    printf("------\n");

    int n=sz(lines);

    for(int iter=0;iter<n;iter++){
        int idx=-1;
        int lowest=inf;
        for (int j=0;j<n;j++){
            if (used[j]) continue;
            if (bricks[j].lowest_z() < lowest){
                idx=j;
                lowest=bricks[j].lowest_z();
            }
        }
        assert(idx!=-1);
        auto & current=bricks[idx];
        int lowest_possible=1;
        for(int i=0;i<n;i++) {
            if(!used[i]) continue;
            for (auto cube: bricks[i].cubes()){
                for(auto cube_cur: current.cubes()){
                    if (cube.x() == cube_cur.x() && cube.y()==cube_cur.y()){
                        lowest_possible= max(lowest_possible, cube.z()+1);
                    }
                }
            }
        }

        used[idx]=1;

        auto dz=current.ends[1].z() - current.ends[0].z();
        current.ends[0].z()= lowest_possible;
        current.ends[1].z()= lowest_possible+dz;

    }

    for(int i=0;i<n;i++){
        printf("<%s;%s>\n", bricks[i].ends[0].to_string().c_str(), bricks[i].ends[1].to_string().c_str());
        for(int j=0;j<n;j++){
            if(j==i)continue;
            int support=0;
            for(auto c1: bricks[i].cubes()){
                for(auto c2:bricks[j].cubes()){
                    if(c1.x()==c2.x() && c1.y()==c2.y() && c1.z()==c2.z()+1) {
                        support=1;
                    }
                }
            }
            if(support) bricks[i].support_by.push_back(j);
            if(support) bricks[j].supports.push_back(i);
        }
    }
    
    for(int i=0;i<n;i++){
        printf(">");
        for(auto b: bricks[i].supports){
            printf("<%d>", b);
        }
       //if(bricks[i].lowest_z()==1 || bricks[i].support_by.size()>1) ans++;
        printf("\n");
    }
    int ans=0;
    for(int i=0;i<n;i++)
    {
        int ok=1;
        for(auto j: bricks[i].supports){
            if(bricks[j].lowest_z()==1) continue;
            if(bricks[j].support_by.size()>1) continue;
            ok=0;
        }
        if(ok) printf("OK\n");
        else printf("NOT\n");
        ans+=ok;
    }
    printf("%d",ans);
    return 0;
}