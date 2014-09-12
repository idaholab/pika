##################################################################################
#                  Pika: Phase field snow micro-structure model                  #
#                                                                                #
#                     (C) 2014 Battelle Energy Alliance, LLC                     #
#                              ALL RIGHTS RESERVED                               #
#                                                                                #
#                   Prepared by Battelle Energy Alliance, LLC                    #
#                      Under Contract No. DE-AC07-05ID14517                      #
#                      With the U. S. Department of Energy                       #
##################################################################################
#! /usr/bin/python

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
parser = argparse.ArgumentParser(description='Execute transient convergence tests for mass transport.')
parser.add_argument('--refinements','-r', default=4, type=int, help='Number of refinements to perform')
parser.add_argument('--first','-f', action='store_true', help='Perform first-order convergence')
parser.add_argument('--second','-s', action='store_true', help='Perform second-order convergence')
parser.add_argument('--disable','-d', action='store_true', help='Disable all calculations')
parser.add_argument('--dphi-dt', action='store_true', help='Execute with version with dphi/dt source term')
parser.add_argument('--parallel', '-p', default=4, help='Number of mpi processes to run')
parser.add_argument('--gold', action='store_true', help='Write gold files')
parser.parse_args('-fsd'.split())
args = parser.parse_args()

# Determine the input file name
if args.first and args.dphi_dt:
  input_name = 'mms_mass_transport_transient_dphi_dt_first.i'
  src = 'mms_mass_transport_transient_dphi_dt_first_out_2.e'
elif args.second and args.dphi_dt:
  input_name = 'mms_mass_transport_transient_dphi_dt_second.i'
  src = 'mms_mass_transport_transient_dphi_dt_second_out_2.e'
elif args.first:
  input_name = 'mms_mass_transport_transient_first.i'
  src = 'mms_mass_transport_transient_first_out_2.e'
elif args.second:
  input_name = 'mms_mass_transport_transient_second.i'
  src = 'mms_mass_transport_transient_second_out_2.e'

# Run the input file and various refinement levels
if not args.disable:
  runApp(input_name, refinements=args.refinements, mpi=args.parallel)

# Extract the data
output_name, ext = os.path.splitext(input_name)
x, y = extractPostprocessorData(output_name + '_out', y='L2_error', x='hmax', refinements=args.refinements)
plt = ConvergencePlot(x, y, xlabel='Element size', ylabel='L2_norm')

if args.first:
  plt.fit(order=2)
elif args.second:
  plt.fit(order=3)

# Update the gold
if args.gold:

  # Copy the output file
  dest = os.path.join(os.getenv('PIKA_DIR'), 'tests', 'mass_transport', 'mms', 'gold', output_name+'_out.e')
  shutil.copyfile(src, dest)

  # Copy the input file
  shutil.copyfile(input_name, os.path.join(os.getenv('PIKA_DIR'), 'tests', 'mass_transport', 'mms', input_name))

show()
