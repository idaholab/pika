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

from readCSV import *
import numpy

##
# Reads rows of CSV data
# @param file_base The base name of the *.csv file(s) to read
# @return The x and y postprocessor data as numpy arrays
#
# Optional:
#   x=<str> The name of the postprocessor to extract for x-axis data
#   y=<str> The name of the postprocessor to extract for y-axis data
#   refinements=<int> The number of refinements performed for transient analysis
def extractPostprocessorData(file_base, **kwargs):

  # Extract the option data
  refinements = kwargs.pop('refinements', 0)
  x_name = kwargs.pop('x', 'ndofs')
  y_name = kwargs.pop('y', 'L2_error')

  # Initialize the output
  x = []
  y = []

  # Steady: Read entire .csv file
  if refinements == 0:
    header, data = readCSV(file_base + '.csv')
    x_idx = header.index(x_name)
    y_idx = header.index(y_name)
    for d in data:
      x.append(float(d[x_idx]))
      y.append(float(d[y_idx]))

  # Transient: Read last piece of data for each file
  else:
    for i in range(refinements + 1):
      header, data = readCSV(file_base + '_' + str(i) + '.csv')
      x_idx = header.index(x_name)
      y_idx = header.index(y_name)
      x.append(float(data[-1][x_idx]))
      y.append(float(data[-1][y_idx]))

  return numpy.array(x), numpy.array(y)
