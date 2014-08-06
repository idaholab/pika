# Load SymPy and enable latex printing
from sympy import *
init_printing()

# Define symbolic variables
T = symbols('T')

# Define constants
D_v = 2.178e-5 # m^2/s
R_da = 286.9
R_v = 461.5
P_a = 1.01325e5
rho_a = 1.341
rho_i = 918.9
K_fit = [-0.58653696e4, 0.2224103300e2, 0.13749042e-1, -0.34031775e-4, 0.26967687e-7, 0.6918651]

# Eq. (2)
P_vs = exp(K_fit[0]*T**(-1) + K_fit[1]*T**0 + K_fit[2]*T**1 + K_fit[3]*T**2 + K_fit[4]*T**3 + K_fit[5]*log(T))

# Eq. (1)
x_s = (R_da / R_v) * P_vs / (P_a - P_vs)

# Eq. (3)
rho_vs = rho_a * x_s

# Concentration equilibrium
u_eq = (rho_vs - rho_vs.subs(T, 263.15)) / rho_i


print (D_v * (rho_vs.subs(T, 266) - rho_vs.subs(T, 270)) / 0.0005).evalf()
print (D_v * (rho_vs.subs(T, 270) - rho_vs.subs(T, 271)) / 0.0005).evalf()
