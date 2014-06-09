'''***************************************
   * Generating Method of MFG-able       *
   * Solutions applied to the Heat       *
   * equation (eqn 34) in Kaempfer 2009  *
   *                                     *
   * Compile:                            *
   * python HeatEquationMMS.py          *
   *                                     *
   ***************************************'''
'''
*******************************************
             NOMENCLATURE

*******************************************
'''

#!/usr/bin/python
                                 
from sympy import *
from numpy import linspace
init_printing()

#Problem Parameters
x_dim = 1.0
y_dim = 1.0 
end_time = 1.0

nx = 10 
dt = 1

x = symbols('x')
y = symbols('y')
t = symbols('t')

phi =-t*pow(y*x,3.0) 
T = t*sin(2.0*pi*x)*sin(2.0*pi*y)

print '\n'
print 'Phi =\n '
pprint(phi)
print '\n'

print '\n'
print 'T =\n '
pprint(T)
print '\n'

#Heat Conductivities and Capacities
ki = symbols('ki')
ka = symbols('ka')

ci = symbols('ci')
ca = symbols('ca')

L_sg = symbols('L_sg') 

#Phase Field Quantities
k = ki*0.5*(1.0+phi)+ka*0.5*(1.0-phi)
c = ci*0.5*(1.0+phi)+ca*0.5*(1.0-phi)

#k=symbols('k')

#c=symbols('c')

#Simplifying Math terms
grad_T = [diff(T,x), diff(T,y)]
print 'grad_T =\n '
pprint(grad_T)
print '\n'


dPhi_dt = diff(phi,t)

dT_dt = diff(T,t)

# Eq. (34) 
#hx = c*( dT_dt ) - ((diff(k*grad_T[0],x) + diff(k*grad_T[1],y))) - 0.5*L_sg*( dPhi_dt) 
hx = c*( dT_dt ) - ((diff(k*grad_T[0],x) + diff(k*grad_T[1],y)))
#hx = - ((diff(k*grad_T[0],x) + diff(k*grad_T[1],y)))

print '\n'
print '  F = \n'
print(hx)
print '\n'
print '\n'
print '  F = \n'
pprint(hx)
print '\n'
hx.evalf( subs={x:1, y:1})
rawEval=(hx.evalf( subs={x:0.75, y:0.75 , t:1 ,ki:2.29, ka:0.02, L_sg:2.60e9, ci:1.8e6, ca:1.4e3}))
xy3=x*y*x*y*x*y
inputEq=8.0*pi*pi*t*(0.5*ka*(t*(xy3) + 1.0) + 0.5*ki*(-t*(xy3) + 1.0))*sin(2.0*pi*x)*sin(2.0*pi*y)-2.0*pi*t*((1.5*ka*t*(xy3))/x - (1.5*ki*t*(xy3))/x)*sin(2.0*pi*y)*cos(2.0*pi*x)-2.0*pi*t*((1.5*ka*t*(xy3))/y - (1.5*ki*t*(xy3))/y)*sin(2.0*pi*x)*cos(2.0*pi*y)+(0.5*ca*(t*(xy3) + 1.0) + 0.5*ci*(-t*(xy3) + 1.0))*sin(2.0*pi*x)*sin(2.0*pi*y)
evalInput=(inputEq.evalf( subs={x:0.75, y:0.75 , t:1 ,ki:2.29, ka:0.02, L_sg:2.60e9, ci:1.8e6, ca:1.4e3}))

print(rawEval)
print(evalInput)
differ= rawEval-evalInput
print(differ) 
'''
X=linspace(0,x_dim,nx)
Y=linspace(0,y_dim,nx)
time=1
fid = open('test.csv', 'w')
fid.write('X,Y,T,hx\n')

for u  in X:
  for v  in Y:
    s = [str(u),str(v), str(T.evalf(subs={x: u, y: v, t: time}))]
    fid.write(','.join(s)+'\n')
fid.close()
'''

