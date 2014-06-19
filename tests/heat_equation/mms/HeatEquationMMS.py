'''***************************************
   * Generating Method of MFG-able       *
   * Solutions applied to the Heat       *
   * equation (eqn 34) in Kaempfer 2009  *
   *                                     *
   * Compile:                            *
   * python HeatEquationMMS.py          *
   *                                     *
   ***************************************'''
#!/usr/bin/python
                                 
from sympy import *
from sympy.utilities.codegen import codegen
init_printing()

x = symbols('x')
y = symbols('y')
t = symbols('t')

phi =-t*(x*y)**2.0 
T = t*sin(2.0*pi*x)*sin(2.0*pi*y)

print '\n'
print 'T =\n '
pprint(T)
print '\n'

#Heat Conductivities and Capacities
k = symbols('k')

c = symbols('c')

L_sg = symbols('L_sg') 

#Simplifying Math terms
dT_dt = diff(T,t)
grad_T = [diff(T,x), diff(T,y)]
diffuse_k_grad_T =((diff(k*grad_T[0],x) + diff(k*grad_T[1],y)))

dPhi_dt = diff(phi,t)

term1 = c * (dT_dt)
term2 = diffuse_k_grad_T
term3 =0.5 * L_sg  * (dPhi_dt)

# Eq. (34) without dPhi_dt 
hx =term1-term2

#Print out equation 
print '\n'
print '  F = \n'
pprint(hx)
print '\n'
print '\n'
print '  -phi_term = \n'
pprint(-term3)
print '\n'


#Generate the C/C++ version of the code.
print('Equation 34 Code : \n')
[(c_name, c_code), (h_name, c_header)] = codegen(
         ("f", hx), "C", "test", header=False, empty=False)
print(c_code)
print('\n')


#Generate C/C++ code for term 4
print('-dPhi_dt term Code : \n')
[(c_name, c_code), (h_name, c_header)] = codegen(
         ("f", -term3), "C", "test", header=False, empty=False)
print(c_code)
print('\n')

