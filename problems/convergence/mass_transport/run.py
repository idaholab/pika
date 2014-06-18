#! /usr/bin/python

import sys, os, subprocess, csv, argparse
import matplotlib.pyplot, numpy
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# The number of uniform refinements to perform
refine = 4

# Run the input file and various refinement levels
#runApp('mms_mass_transport.i', refinements=refine, mpi=4)

# Extract the data
x, y = extractPostprocessorData('out', refinements=refine)

# Build plot (sqrt(dofs))
plt = ConvergencePlot(sqrt(x), y, xlabel='sqrt(ndofs)', ylabel='L2_error')
plt.fit()

# Extract the data
x, y = extractPostprocessorData('out', refinements=refine, x = 'hmax')
plt2 = ConvergencePlot(x, y, xlabel='Element size', ylabel='L2_error')
plt2.fit()

show()
