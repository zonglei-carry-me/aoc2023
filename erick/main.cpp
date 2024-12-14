#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;
int arr[1000][1000];
int N=40;
set<int> st;
void solve1() {
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            st.clear();
            for(int k=0;k<i;k++){
                st.insert(arr[k][j]);
            }
            for(int k=0;k<j;k++){
                st.insert(arr[i][k]);
            }
            for(int k=0;;k++){
                if (st.find(k)==st.end()){
                    arr[i][j]=k;
                    break;
                }
            }
        }
    }

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}
int cap(int x){
    int v= 1;
    while(1){
        if(v-1 >=x){
            return v-1;
        }
        v*=2;
    }

}
int rec(int r,int c){
    if(r==0 && c==0) return 0;
    if( c> r) swap(r,c);
    int bound= cap(r);
    int half=(bound+1)/2;
    if(c >= half ) {
        return rec( r-half, c -half);
    }
    return half+ rec(r-half,c); 
}
int main()
{
    solve1();
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            printf("%3d ", rec(i,j));
            if(rec(i,j)!=arr[i][j]){
                printf("<%d,%d; %d %d> ",i,j,rec(i,j),arr[i][j]);
                return 0;
            }
        }
        printf("\n");
    }
    return 0;
}