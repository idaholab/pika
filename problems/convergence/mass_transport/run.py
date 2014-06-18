#! /usr/bin/python

import sys, os, subprocess, csv, argparse
import matplotlib.pyplot, numpy
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
import tools


##
#
def getOptions(args=None):

  # Define command line arguments
  parser = argparse.ArgumentParser(description='Script for performing convergence studies')

  # Add the arguments
  parser.add_argument('input', type=str, help='Input file name')
  parser.add_argument('--refinements', '-r', default=3, type=int, help='Number of uniform refinements')
  parser.add_argument('--execute', '-e', default=os.path.abspath('../../../pika-oprof'),
                      help='Name of the executable')
  parser.add_argument('--parallel', '-p', '-n', default=1, type=int, help='Run in parallel with the specified number of jobs')

  parser.add_argument('--y-axis', '-y', default='L2_error', type=str,
                      help='Name of the postprocessor for plotting on the x-axis')
  parser.add_argument('--x-axis', '-x', default='ndofs', type=str,
                      help='Name of the postprocessor for plotting on the y-axis')
  parser.add_argument('--disable-execute', '-d', action='store_true', help='Disable the execution of the input files')
  parser.add_argument('--csv', default='out', type=str, help='The name of the csv file output, it will be suffixed with the number of refinements and the extension added (e.g., out_3.csv)')

  return parser.parse_args()



if __name__ == '__main__':

  # Extract the command line options
  options = getOptions()
  print options

  # Perform the execution of the input files
  if not options.disable_execute:
    tools.runApp(options.execute, options.input, options.refinements, options.parallel, options.csv)

  # Extract the data
  x, y = getData(options.csv, options.refinements, options.x_axis, options.y_axis)

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
  xlabel('Num. DOFs',{'fontsize':20})
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
  coefficients = numpy.polyfit(log10(x),log10(y), 1)
  polynomial = numpy.poly1d(coefficients)
  #ys = polynomial(x)
  #print coefficients
  print polynomial

  print x,y

  #plot(x, y, 'o')
  #plot(x, ys)
  #ylabel('y')
  #xlabel('x')
  #xlim(-10,10)
  #ylim(-1,1)
  #show()


  # @\todo{Plot a line, and fit with the data}
  dx = log10(x[-1]) - log10(x[0])
  dy = log10(y[-1]) - log10(y[0])
  print dy/dx

  # Show the file
  #tight_layout()
  savefig('mass_transport.pdf')
  show()
