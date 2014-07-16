/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

'''***************************************
   * Generating Method of MFG-ed         *
   * Solutions applied to the Heat       *
   * equation (eqn 34) in Kaempfer 2009  *
   *                                     *
   * Compile:                            *
   * python MassTransportMMS.py          *
   *                                     *
   ***************************************'''
#!/usr/bin/python
                                 
from sympy import *
from sympy.utilities.codegen import codegen
init_printing()

x = symbols('x')
y = symbols('y')
t = symbols('t')

phi = t*x*y 
u = t*sin(2.0*pi*x)*cos(2.0*pi*y)
print '\n'
print 'u =\n '
pprint(u)
print '\n'

#Chemical diffusion
D = symbols('D')

#Simplifying Math terms
du_dt = diff(u,t)
grad_u = [diff(u,x), diff(u,y)]
diffuse_D_grad_u =((diff(D*grad_u[0],x) + diff(D*grad_u[1],y)))

dPhi_dt = diff(phi,t)

term1 = du_dt
term2 = diffuse_D_grad_u
term3 =-0.5*(dPhi_dt) #yes it is negative in the original eq.

# Eq. (35) without dPhi_dt 
f = term1-term2

#Print out equation 
print '\n'
print '  F = \n'
pprint(f)
print '\n'
print '\n'
print '  -phi_term = \n'
pprint(-term3)
print '\n'


#Generate the C/C++ version of the code.
print('Equation 35 Code : \n')
[(c_name, c_code), (h_name, c_header)] = codegen(
         ("f", f), "C", "test", header=False, empty=False)
print(c_code)
print('\n')

#Generate C/C++ code for term 4
print('-dPhi_dt term Code : \n')
[(c_name, c_code), (h_name, c_header)] = codegen(
         ("f", -term3), "C", "test", header=False, empty=False)
print(c_code)
print('\n')

