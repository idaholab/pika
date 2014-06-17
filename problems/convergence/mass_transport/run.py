#! /usr/bin/python

import os, subprocess, csv, argparse
import matplotlib.pyplot
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

##
#
def getOptions(args=None):

  # Define command line arguments
  parser = argparse.ArgumentParser(description='Script for performing convergence studies')

  # Add the arguments
  parser.add_argument('input', type=str, help='Input file name')
  parser.add_argument('--refinements', '-r', default=3, type=int, help='Number of uniform refinements')
  parser.add_argument('--execute', '-x', '-e', default=os.path.abspath('../../../pika-oprof'),
                      help='Name of the executable')
  parser.add_argument('--parallel', '-p', '-n', default=1, type=int, help='Run in parallel with the specified number of jobs')

  parser.add_argument('--error', default='L2_error', type=str, help='Name of the L2 error postprocessor')
  parser.add_argument('--hmax', default='h_max', type=str, help='Name of the element size postprocessor')
  parser.add_argument('--disable-execute', '-d', action='store_true', help='Disable the execution of the input files')
  parser.add_argument('--csv', default='out', type=str, help='The name of the csv file output, it will be suffixed with the number of refinements and the extension added (e.g., out_3.csv)')

  return parser.parse_args()

##
#
def runApp(program, input_file, refinements, processors, file_base):

  for i in range(refinements):
    cmd = ['mpiexec', '-n', str(processors), program, '-i', input_file,
         'Mesh/uniform_refine='+str(i), 'Outputs/file_base='+file_base+'_'+str(i)]
    subprocess.call(cmd)

def readCSV(filename):
  with open(filename, 'rb') as f:
    reader = csv.reader(f)
    header = []
    data = []
    for row in reader:
      # Do not include blank rows
      if len(row) == 0:
        continue

      # First row is header
      if reader.line_num == 1:
        header = row
      else:
        data.append(row)

  return header, data

##
#
def getData(file_base, refinements, L2_name, h_name):

  x = []
  y = []

  for i in range(refinements):
    header, data = readCSV(file_base + '_' + str(i) + '.csv')

    x_idx = header.index(h_name)
    y_idx = header.index(L2_name)

    x.append(float(data[-1][x_idx]))
    y.append(float(data[-1][y_idx]))

  return x,y



if __name__ == '__main__':

  # Extract the command line options
  options = getOptions()
  print options

  # Perform the execution of the input files
  if not options.disable_execute:
    runApp(options.execute, options.input, options.refinements, options.parallel, options.csv)

  # Extract the data
  x, y = getData(options.csv, options.refinements, options.error, options.hmax)

  # Create the figure and plot the data
  figure(figsize=(10,6))
  plot(x, y, 'ok-', markersize=12, lw=3)

  # Make the plot a log plot
  gca().set_yscale('log')
  gca().set_xscale('log')

# Create the slope annotation
#plot([100,100], [0.1,0.024], '-k', lw=1)
#plot([50 ,100], [0.1,0.1], '-k', lw=1)
#text(70, 0.11, '1', size=18)
#text(104, 0.045, '2', size=18)

  # Add axis labels
  xlabel('Element Length',{'fontsize':20})
  ylabel('L2 Error',{'fontsize':20})

  # Adjust tick mark fonts
  for xtick in  gca().xaxis.get_major_ticks():
    xtick.label.set_fontsize(18)

  for ytick in gca().yaxis.get_major_ticks():
    ytick.label.set_fontsize(18)

  # Apply grid marks
  grid(True)
  grid(True, which='minor', color='b')

  # Perform fit
  # @\todo{Plot a line, and fit with the data}
  dx = (x[-1]) - log(x[0])
  dy = (y[-1]) - log(y[0])
  print dy/dx

  # Show the file
  #tight_layout()
  savefig('mass_transport.pdf')
  show()
