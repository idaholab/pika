#!/usr/bin/python

from sympy import *
init_printing()

T = symbols('T')

R_da = 286.9
R_v = 461.5
P_a = 1.01325e5
K = [-0.5865e4, 0.2224e2, 0.1375e-1, -0.3403e-4, 0.2697e-7, 0.6918]

P_vs = exp(K[1]*T**0 + K[2]*T**1 + K[3]*T**2 + K[4]*T**3 + K[5]*ln(T))
pprint(P_vs)
