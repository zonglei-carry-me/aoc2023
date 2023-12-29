#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

const int OFF=0;
const int ON=1;

const int LOW=0;
const int HIGH=1;
struct Node{
    string name;
    char type;
    int state=0;
    vector<string> next;
    map<string,int> inputs;
    int HIGH_cnt=0;
    void prt(){
        printf("name=%s; type=%c; next: ", name.c_str(), type);
        for(auto e:next){
            printf("%s ",e.c_str());
        }
        printf("\n");
    }
};

map<string,Node> nodes;

struct Pulse{
    string from;
    string to;
    int signal;
    Pulse(){
    }
    Pulse(string a,string b, int c){
        from=a;to=b;signal=c;
    }
    void prt(){
        return;
        printf("(%s %s %s)\n",from.c_str(), signal==HIGH?"HIGH":"LOW",to.c_str());
    }
};
int main()
{
    auto lines=readlines();
    for(auto line: lines){
        auto a=split_s(line," -> ")[0];
        auto b=split_s(line," -> ")[1];
        Node node;
        if(a=="broadcaster") {
            node.name=a;
            node.type='b';
        }else if (a[0]=='%') {
            a.erase(a.begin());
            node.type='%';
            node.name=a;
        }else if (a[0]=='&') {
            a.erase(a.begin());
            node.type='&';
            node.name=a;
        }else {
            assert(false);
        }
        auto c= split_c(b,", ");
        for(auto d: c){
            node.next.push_back(d);
        }
        //node.memories= vector<int>(node.next.size(),0);
        node.prt();
        nodes[node.name]=node;
    }

    for(auto& it:nodes){
        for(auto &n:it.second.next){
            nodes[n].inputs[it.first]=LOW;
        }
    }

    int n_times= 1000;

    long LOW_cnt=0;
    long HIGH_cnt=0;
    for(auto it=0;it<n_times;it++){
        printf("\n");
        deque< Pulse> q;
        LOW_cnt+=1;
        for(auto nn: nodes["broadcaster"].next){
            q.push_back({ "broadcaster",nn, LOW});
            q.back().prt();
        }

        while(!q.empty()) {
            auto e=q.front();
            q.pop_front();
            auto &node=nodes[e.to];
            if(e.signal==HIGH) HIGH_cnt++;
            else LOW_cnt++;

            if (node.type=='%') {
                if (e.signal==HIGH) {

                }else{
                    if(node.state==OFF) {
                        node.state=ON;
                        for(auto &nn:node.next){
                            q.push_back({node.name, nn, HIGH});
                            q.back().prt();
                        }
                    }else{
                        node.state=OFF;
                        for(auto &nn:node.next){
                            q.push_back({node.name, nn, LOW});
                            q.back().prt();
                        }
                    }
                }
            }
            else if (node.type=='&'){
                if(node.inputs[e.from]== LOW && e.signal==HIGH) {
                    node.HIGH_cnt++;
                    node.inputs[e.from]=HIGH;
                }else if(node.inputs[e.from]== HIGH && e.signal==LOW){
                    node.HIGH_cnt--;
                    node.inputs[e.from]=LOW;
                }
                if(node.HIGH_cnt ==sz(node.inputs)){
                    for(auto e: node.next){
                        q.push_back({node.name,e,LOW});
                        q.back().prt();
                    }
                }
                else{
                    for(auto e: node.next){
                        q.push_back({node.name,e,HIGH});
                        q.back().prt();
                    }
                }
            }
            else {
                //printf("<%s %s %d>\n",node.name.c_str(), e.to.c_str(),node.next.size());
                //assert(false);
            }

        }
    }
    printf("<%ld,%ld, %ld>\n",HIGH_cnt,LOW_cnt, HIGH_cnt*LOW_cnt);
    return 0;
}