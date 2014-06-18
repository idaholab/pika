#! /usr/bin/python
# A simple demonstration of the convergence tools in Pika, the
# executable is slightly modified version of Example 14 of Moose.

# Import necessary packages
import sys, os

# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# Run the problem; this problem is a Steady calculations so adaptivity
# is used in a single run to perform the analysis
runApp('demo.i', mpi=4)

# Extract the data from the Postprocessor CSV output (out.csv)
x, y = extractPostprocessorData('out')

plt = ConvergencePlot(x,y)
plt.fit()
