#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;


char mat[200][200];
char used[200][200];

int d[200][200];
int rs,cs;

int oob(int r, int c){
    if (r<0) return true;
    if (c<0) return true;
    if (r>=rs) return true;
    if (c>=cs) return true;
    return false;
}
int dr[]={0,1,-1,0};
int dc[]={-1,0,0,1};
int src_r,src_c;

int inf=1000*1000*1000;
int norm(int x,int s){
    return (x%s+s)%s;
}

long solve(int src_r,int src_c, int step){
    
    set<pair<int,int>> st[5000+5];
    st[0].insert({src_r,src_c});
    //const int step=300;
    for(int iter=1;iter<=step;iter++){
        for(auto e:st[iter-1]){
            for(int i=0;i<4;i++){
                int nr= e.first+dr[i];
                int nc= e.second+dc[i];
                if(oob(nr,nc)) continue;
                if(mat[nr][nc]=='#') continue;
                st[iter].insert({nr,nc});
            }
        }
    }
    return sz(st[step]);
}

int div2(int a, int b){
    if(a<0 && a%b!=0) return -((-a)/b +1);
    return a/b;
}
int main()
{
    memset(d,-1,sizeof(d));
    auto lines=readlines();
    rs=0;
    for(auto line:lines){
        strcpy(mat[rs++],line.c_str());
        cs=sz(line);
    }

    int cnt=0;
    for(int r=0;r<rs;r++)
        for(int c=0;c<cs;c++){
            if (mat[r][c]=='S'){
                src_r=r;src_c=c;
            } 
            if (mat[r][c]=='#'){     
                cnt++;
            }
        }
    
    printf("<%d %d %d>\n",rs,cs,cnt);

    int n_step=26501365;
    //int n_step=401;
    map<pair<int,int>, pair<int,int>> mat_st;
    pair<int,int> dd[4]={{1,1},{1,-1},{-1,1},{-1,-1}};
    for(int i=0;i<4;i++){
        for(int delta=0;delta<=n_step;delta++){
            auto r= src_r+delta * dd[i].first;
            auto c= src_c+(n_step-delta) *dd[i].second;

            int rr=(r%rs+rs)%rs;
            int cc=(c%cs+cs)%cs;
            int gr=div2(r,rs);
            int gc=div2(c,cs);
            //printf("<<<%d,%d----%d %d-- %d %d>>>\n",r,c,gr,gc,rr,cc);
            if(gr==0 && gc==0) {
                if(rr==0 && cc==0  ) continue;
                if(rr==rs-1 && cc==rs-1 ) continue;
                if(rr==rs-1 && cc==0 ) continue;
                if(rr==0 && cc==rs-1 ) continue;
            }
            mat_st[{gr,gc}]= {rr,cc};
        }
        printf("\n");
    }

    printf("sz=%d\n",sz(mat_st));

    map< tuple<int,int,int>, int> stat;

    for(auto m: mat_st ){
        //printf("{%d %d}\n",m.first.first,m.first.second);
        int off_r= m.first.first*rs;
        int off_c= m.first.second*cs;
        //printf("[%d %d]\n",m.first.first, m.first.second);
        int dist=inf;
        int nsrc_r;
        int nsrc_c;
        for(int r=0;r<rs;r++){
            for(int c=0;c<cs;c++){
                if( abs(r+off_r-src_r) +abs(c+off_c-src_c) <= dist ){
                    dist= abs(r+off_r-src_r) +abs(c+off_c-src_c);
                    nsrc_r=r;
                    nsrc_c=c;
                }
            }
        }
        int dist2= abs( m.second.first - nsrc_r) + abs( m.second.second - nsrc_c);
        //if (dist2)
        stat[ {nsrc_r,nsrc_c,  dist2 }]++;
    }

    long sum1=0;
    for(auto s: stat) {
        printf("<%d %d, %d; %d>\n",get<0>(s.first),get<1>(s.first),get<2>(s.first), s.second);
        long tmp=solve(get<0>(s.first), get<1>(s.first), get<2>(s.first));
        sum1+=  tmp*s.second;
        printf("%ld\n",tmp);
    }

    //long radius=n_step+1;
    long r2 = (n_step+1)/rs;
    
    long full_cnt1=  r2*r2 ;
    long full_cnt2= (r2-1)*(r2-1);
    if(r2<1) full_cnt2=0;

    printf("full_cnt1=%ld  full_cnt2=%ld\n", full_cnt1,full_cnt2);

    long sum2= solve(src_r, src_c, 2*rs + r2%2 +n_step%2+1) *full_cnt1;
    long sum3= solve(src_r, src_c, 2*rs + (r2+1)%2 +n_step%2+1) *full_cnt2;

    printf("%ld %ld %ld %ld\n",sum1,sum2,sum3,sum1+sum2+sum3);
    
    return 0;

}
