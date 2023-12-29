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

void prt(){
    for(auto it=nodes.begin();it!=nodes.end();it++){
        if (it->second.type=='%'){
            printf("(%s %d)", it->second.name.c_str(), it->second.state);
        }else if (it->second.type=='&'){
            printf("{%s ",it->second.name.c_str());
            for(auto it2=it->second.inputs.begin();it2!=it->second.inputs.end();it2++){
                printf("%d,",it2->second);
            }
            printf("}");
        }
    }
    printf("\n");
}
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

    map<string,vector<long>> stat;

    long n_times= 1000l*1000*1000*1000*1000l;
    //n_times=200;
    long LOW_cnt=0;
    long HIGH_cnt=0;
    for(long it=0;it<n_times;it++){
        /*if(random()%10000==0) {
            printf("iter=%ld\n",it);
            prt();
        }*/

        if(random()%100000==0) {
            printf("iter=%ld\n",it);

            for (auto it2=stat.begin();it2!=stat.end();it2++){
                printf("%s: ",it2->first.c_str());
                for(int idx=0;idx< sz(it2->second);idx++){
                    printf(" %ld", it2->second[idx]);
                    if(idx) {
                        printf("(%ld)", it2->second[idx]- it2->second[idx-1]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            //prt();
        }


        //printf("\n");
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

                if(node.name=="kz" && e.signal ==HIGH) {
                    stat[e.from].push_back(it+1);
                    //printf("iter=%ld %s \n",it, e.from.c_str());
                    //prt();
                }
            }
            else {
                if(e.signal==LOW) {
                    printf("ans=%ld",it+1);
                    return 0;
                }
                //printf("<%s %s %d>\n",node.name.c_str(), e.to.c_str(),node.next.size());
                //assert(false);
            }

        }
    }
    printf("<%ld,%ld, %ld>\n",HIGH_cnt,LOW_cnt, HIGH_cnt*LOW_cnt);
    return 0;
}