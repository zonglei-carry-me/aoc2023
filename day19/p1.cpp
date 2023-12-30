#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
struct Item{
    map<char, int> attr;
    int idx;
};
struct Rule{
    char cmp;
    char attr_name;
    int param;
    string next;
    bool process(Item &item){
        auto value=item.attr[attr_name];
        printf("[[[[%c %d %d]]]]",cmp,value,param);
        if (cmp=='>'){
            return value>param;
        }else if(cmp=='<'){
            return value<param;
        }else assert(false);
    }
};
struct WorkFlow{
    string name;
    vector<Rule> rules;
    string next;
};
map<string, WorkFlow> wfs;
vector<Item>items;
int main()
{
    auto lines= readlines();
    int got_empty=0;
    int n_item=0;
    for(auto line: lines) {
        if(line=="") {got_empty=1;continue;}
        //printf("%s\n",line.c_str());
        if (!got_empty){
            WorkFlow wf;
            wf.name=split_c(line,"{}")[0];
            auto a=split_c(line,"{}")[1];
            auto b=split_c(a,",");
            for (auto c:b){
                if (c.find(":")!=string::npos){
                    Rule rule;
                    auto d=split_c(c,":")[0];
                    rule.next=split_c(c,":")[1];
                    rule.attr_name=d[0];
                    rule.cmp=d[1];
                    sscanf(d.c_str()+2,"%d",&rule.param);
                    wf.rules.push_back(rule);
                }else{
                    wf.next=c;
                }
            }
            wfs[wf.name]=wf;

        }
        else{
            auto a=split_c(line,"{},");
            Item item;
            for(auto b:a){
                auto c=split_c(b,"=")[0][0];
                auto d=split_c(b,"=")[1];
                int e;
                sscanf(d.c_str(),"%d", &e);
                item.attr[c]=e;
                printf("{{%c %d}}",c,e);
            }
            item.idx=n_item;
            items.push_back(item);
            n_item++;
        }
    }
    long ans=0;
    for (auto &item:items){
        printf("!!\n");
        string next="in";
        while(1){
            printf("next=%s ", next.c_str());
            if(next=="A"){
                long sum=0;
                for(auto &pr: item.attr){
                    sum+=pr.second;
                }
                printf("%d  %ld\n", item.idx,sum);
                ans+=sum;
                break;
            }
            if(next=="R"){
                printf("reject %d",item.idx);
                break;
            }
            assert(next!="");
            auto &wf=wfs[next];
            for(auto &rule: wf.rules){
                printf("[[%c %c %d]]",rule.attr_name, rule.cmp,rule.param);
                if( rule.process(item)== true){
                    next=rule.next;
                    goto endline;
                }
            }
            next=wf.next;
            endline:;
        }
    }

    printf("ans=%ld\n",ans);
    return 0;
}