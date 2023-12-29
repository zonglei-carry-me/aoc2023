#! /usr/bin/env python3
import sys

lines = sys.stdin.read().split('\n')

ps=[]
vs=[]

def parse(s):
    res=[]
    arr=s.split(',')
    for a in arr:
        #print(a)
        res.append(int(a))
    return res
#print(lines)
for line in lines:
    if line=='':
        continue
    arr= line.split('@')
    p= parse(arr[0])
    v= parse(arr[1])
    ps.append(p)
    vs.append(v)
ANY=123123123123123123123
EPS=0.000001
def solve_one(p1,v1,p2,v2):
    print(p1,v1,p2,v2)
    if (v1-v2)==0:
        if (p1-p2)!=0:
            return None
        else:
            return ANY
    return (p1-p2)/(v2-v1)

def compatible(a,b):
    if a==ANY:
        return True
    if b==ANY:
        return True
    if abs(a-b)> EPS:
        return False
    return True
def solve(i,j):
    ans=[]
    for idx in range (0,3):
        t=solve_one(ps[i][idx],vs[i][idx],ps[j][idx],vs[j][idx])
        ans.append(t)

    print(ans)
    for idx in range (0,3):
        if ans[idx]==None:
            return False
    for idx in range (0,3):
        for idx2 in range (0,3):
            if compatible(ans[idx],ans[idx2]): 
                return False
    a=None
    for idx in range(0,3):
        if ans[idx]!=ANY:
            a=ans[None]
    assert(a!=None)

    if a<0:
        return False
    def in_range(x):
        if x>=200000000000000 and x<=400000000000000:
            return True
        return False
    x= ps[0]+v[0]*a
    y= ps[1]+v[1]*a
    if in_range(x) and in_range(y):
        return True
    return False
    
cnt=0
for i in range(0, len(ps)):
    for j in range (i+1, len(ps)):
        if solve(i,j):
            cnt+=1

print(cnt)