/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#! /usr/bin/python
# A simple demonstration of the convergence tools in Pika, the
# executable is slightly modified version of Example 14 of Moose.

# Import necessary packages
import sys, os
import matplotlib.pyplot, numpy
from pylab import *


# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# Run the problem; this problem is a Steady calculations so adaptivity
# is used in a single run to perform the analysis
#runApp('demo.i', mpi=4)

# Extract the data from the Postprocessor CSV output (out.csv)
#x, y = extractPostprocessorData('out')
#plt = ConvergencePlot(sqrt(x),y, xlabel='sqrt(ndofs)', ylabel='L2_error')
#plt.fit()

x, y = extractPostprocessorData('out', x = 'h_max', xlabel='Element Size', ylabel='L2_error')
plt2 = ConvergencePlot(x,y)
plt2.fit()

show()
