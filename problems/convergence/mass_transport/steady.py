#! /usr/bin/python
#**************************************************************#
#       PIKA - Phase field snow micro-structure model          #
#                                                              #
#          Prepared by Battelle Energy Alliance, LLC           #
#            Under Contract No. DE-AC07-05ID14517              #
#            With the U. S. Department of Energy               #
#                                                              #
#            See COPYRIGHT for full restrictions               #
#**************************************************************#

import sys, os, subprocess, csv, argparse, shutil
import matplotlib.pyplot, numpy
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

# Load Pika Python tools
if 'PIKA_DIR' not in os.environ:
  os.environ['PIKA_DIR'] = os.path.abspath(os.path.join('..', '..', '..'))
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# Parse command-line options
parser = argparse.ArgumentParser(description='Execute steady convergence test for mass transport.')
parser.add_argument('--gold', action='store_true', help='Write gold files')
parser.add_argument('--parallel', '-p', default=4, help='Number of mpi processes to run')
args = parser.parse_args()

# Run the input file and various refinement levels
runApp('mms_mass_transport_steady.i', mpi=args.parallel)

# Extract the data
x, y = extractPostprocessorData('mms_mass_transport_steady_out', x = 'hmax')
plt = ConvergencePlot(x, y, xlabel='Element size', ylabel='L2_error')
plt.fit()

# Update the gold
if args.gold:
  dest = os.path.join(os.getenv('PIKA_DIR'), 'tests', 'mass_transport', 'mms')

  for i in range(3,4):
    src = 'mms_mass_transport_steady_out.e-s00' + str(i)
    shutil.copyfile(src, os.path.join(dest, 'gold', src))

  src = 'mms_mass_transport_steady_out.csv'
  shutil.copyfile(src, os.path.join(dest, 'gold', src))

  src = 'mms_mass_transport_steady.i'
  shutil.copyfile(src, os.path.join(dest, src))

show()
