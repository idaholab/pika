#!/usr/bin/python

from sympy import *
init_printing()

T = symbols('T')

R_da = 286.9
R_v = 461.5
P_a = 1.01325e5
K = [-0.5865e4, 0.2224e2, 0.1375e-1, -0.3403e-4, 0.2697e-7, 0.6918]

# Eq. (2)
P_vs = exp(K[0]*T**-1 + K[1]*T**0 + K[2]*T**1 + K[3]*T**2 + K[4]*T**3) + T**K[5]

# Eq. (1)
x_s = R_da / R_v * P_vs / (P_a - P_vs)

print "P_vs = ", P_vs.evalf(subs={T: 262.15})
print "x_s = ", x_s.evalf(subs={T: 262.15})


T_in = [263.21732158353, 263.3856925173, 263.63825334886]

fid = open('test.csv', 'w')
fid.write('time,P_vs,T,x_s\n')

t = 0
dt = 0.1
for u  in T_in:
  s = [str(t), str(P_vs.evalf(subs={T: u})), str(u), str(x_s.evalf(subs={T: u}))]
  fid.write(','.join(s)+'\n')
  t = t + dt
fid.close()
