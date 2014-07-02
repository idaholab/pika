'''***************************************
   * Checking the jacobian of the        *
   * phase transition term in eq (33)    *
   * Compile:                            *
   * python DerivativeCheck.py           *
   *                                     *
   ***************************************'''
#!/usr/bin/python
                                 
from sympy import *
from sympy.utilities.codegen import codegen
init_printing()

phi =symbols('phi') 

#constants
lam= symbols('lambda')

u = symbols('u')

u_eq = symbols('u_eq') 

term3 =-lam*(u-u_eq)*((1-phi**2)**2)

#Print out equation 
print '\n'
print '  Term 4 = \n'
pprint(diff(term3,phi))
print '\n'

'''
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
'''
