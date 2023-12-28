#! /usr/bin/env python3
import sys
import z3

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

s=z3.Solver()

x,y,z,t=z3.Reals("x y z t")
vx,vy,vz= z3.Reals("vx vy vz")
s.add(t>0)
for i in range(0, len(ps)):
    t=z3.Real("t"+str(i))
    s.add(x + vx * t == ps[i][0] + vs[i][0]*t)
    s.add(y + vy * t == ps[i][1] + vs[i][1]*t)
    s.add(z + vz * t == ps[i][2] + vs[i][2]*t)

print (s.check())

m = s.model()
print (m)
print(z3.simplify(m[x]+m[y]+m[z]))
