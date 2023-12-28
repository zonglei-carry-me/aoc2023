#! /usr/bin/env python3
import sys
import sympy

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

def compatible(a,b):
    if a==ANY:
        return True
    if b==ANY:
        return True
    if abs(a-b)> EPS:
        return False
    return True
def solve(i,j):
    print(i,j)
    t1, t2 = sympy.symbols(['t1', 't2'])
    sol = sympy.solve([ ps[i][0] +vs[i][0]*t1  - ps[j][0] -vs[j][0]*t2  , ps[i][1] +vs[i][1]*t1  - ps[j][1] -vs[j][1]*t2  ], [t1, t2])
    assert(len(sol)==0 or len(sol)==2)
    print(sol)
    if len(sol)==0:
        return False
    def in_range(x):
        if x>=200000000000000 and x<=400000000000000:
        #if x>=7 and x<=27:
            return True
        return False
    if(sol[t1]<0 or sol[t2]<0):
        return False
    if not in_range(ps[i][0] +vs[i][0]*sol[t1]):
        return False
    if not in_range(ps[i][1] +vs[i][1]*sol[t1]):
        return False
    return True
    
cnt=0
for i in range(0, len(ps)):
    for j in range (i+1, len(ps)):
        if solve(i,j):
            cnt+=1
            print(cnt)

print(cnt)