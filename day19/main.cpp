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
        //printf("[[[[%c %d %d]]]]",cmp,value,param);
        if (cmp=='>'){
            return value>param;
        }else if(cmp=='<'){
            return value<param;
        }else assert(false);
    }

    bool covers(Rule &b){
        if(cmp!=b.cmp) return false;
        if(attr_name!=b.attr_name) return false;
        if(cmp=='>' && param >b.param) {
            return true;
        }
        if(cmp=='<' && param <b.param) {
            return true;
        }

        return false;
    }
};
struct WorkFlow{
    string name;
    vector<Rule> rules;
    string next;

    void add_rules(Rule & rule){
        for(int i=0;i<sz(rules);i++) {
            //if(rules[i].covers(rule)) return;
        }
        rules.push_back(rule);
    }
    void simplify(){
        while(rules.size()>0){
            if(rules.back().next == next){
                rules.pop_back();
            }
            else{
                break;
            }
        }
    }
};
unordered_map<string, WorkFlow> wfs;
vector<Item>items;

bool solve(Item & item){
    //printf("!!\n");
    static string next="in";
    next="in";
    while(1){
        //printf("next=%s ", next.c_str());
        if(next=="A"){
            /*long sum=0;
            for(auto &pr: item.attr){
                sum+=pr.second;
            }*/
            //printf("%d  %ld\n", item.idx,sum);
            //ans+=sum;
            //break;
            return true;
        }
        if(next=="R"){
            //printf("reject %d",item.idx);
            //break;
            return false;
        }
        assert(next!="");
        auto &wf=wfs[next];
        for(auto &rule: wf.rules){
            //printf("[[%c %c %d]]",rule.attr_name, rule.cmp,rule.param);
            if( rule.process(item)== true){
                next=rule.next;
                goto endline;
            }
        }
        next=wf.next;
        endline:;
    }
}
int main()
{
    auto lines= readlines();
    int got_empty=0;
    int n_item=0;

    map<char, set<double> > pivot_values;

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
                    wf.add_rules(rule);
                    //wf.rules.push_back(rule);


                }else{
                    wf.next=c;
                }
            }
            wf.simplify();
            for(auto & rule: wf.rules) {
                    if(rule.cmp=='>') {
                        pivot_values[rule.attr_name].insert(rule.param+0.5);
                    }else{
                        pivot_values[rule.attr_name].insert(rule.param-0.5);
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

                //printf("{{%c %d}}",c,e);
            }
            item.idx=n_item;
            items.push_back(item);
            n_item++;
        }
    }
    auto attr_list="xmas";
    vector<pair<double,double>> intervals[4];
    for(int i=0; i<4 ;i++){

        auto &st=pivot_values[attr_list[i]];

        st.insert(0.5);
        st.insert(4000.5);

        double prev=*st.begin();
        for(auto it2=st.begin();it2!=st.end();it2++){
            //printf("<<%f>>",*it2);
            if(it2==st.begin()) continue;
            printf("<%f %f>\n", prev,*it2);
            assert(*it2 -prev >0.1);
            intervals[i].push_back({prev,*it2});
            prev=*it2;
        }
        printf("\n");
    }

    long cases=1;
    long ans=0;
    
    long cases2=1;
    for(int i=0;i<4;i++){
        cases2*= intervals[i].size();
    }

    cout<<cases2<<endl;
    //return 0;
    Item item;
    for(auto &i0:intervals[0])
    for(auto &i1:intervals[1])
    for(auto &i2:intervals[2])
    for(auto &i3:intervals[3])
    {
       
        long size= long(i0.second-i0.first+0.1)*long(i1.second-i1.first+0.1)*long(i2.second-i2.first+0.1)*long(i3.second-i3.first+0.1);
        assert(size!=0);
        item.attr['x']= i0.first+0.6;
        item.attr['m']= i1.first+0.6;
        item.attr['a']= i2.first+0.6;
        item.attr['s']= i3.first+0.6;
        if(solve(item)) ans+=size;
        cases++;
        if(cases%10000000==0) printf("current=%ld\n",cases);
    }

    printf("cases=%ld\n",cases);




    printf("ans=%ld\n",ans);
    return 0;
}