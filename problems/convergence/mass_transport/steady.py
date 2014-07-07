#! /usr/bin/python

import sys, os, subprocess, csv, argparse
import matplotlib.pyplot, numpy
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# Run the input file and various refinement levels
runApp('mms_mass_transport_steady.i', mpi=4)

# Extract the data
x, y = extractPostprocessorData('out')

# Extract the data
x, y = extractPostprocessorData('out', x = 'hmax')
plt = ConvergencePlot(x, y, xlabel='Element size', ylabel='L2_error')
plt.fit()

show()
