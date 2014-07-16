/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

import matplotlib.pyplot, numpy
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

# Under development ...

class ConvergencePlot(object):
  def __init__(self, x, y, **kwargs):

    x_label = kwargs.pop('xlabel', 'x')
    y_label = kwargs.pop('ylabel', 'y')

    self._x = numpy.array(x)
    self._y = numpy.array(y)

    figure(figsize=(10,6))
    plot(self._x, self._y, 'ob', markersize=12)

    self._gcf = gcf()
    self._gca = gca()

    gca().set_yscale('log')
    gca().set_xscale('log')

    # Add axis labels
    xlabel(x_label,{'fontsize':20})
    ylabel(y_label,{'fontsize':20})

    # Adjust tick mark fonts
    for xtick in  gca().xaxis.get_major_ticks():
      xtick.label.set_fontsize(18)

    for ytick in gca().yaxis.get_major_ticks():
      ytick.label.set_fontsize(18)

    # Apply grid marks
    grid(True)
    grid(True, which='minor', color='b')

  def fit(self, **kwargs):
    # Perform fit
    coefficients = numpy.polyfit(log10(self._x),log10(self._y), 1)
    polynomial = numpy.poly1d(coefficients)
    order = kwargs.pop('order', 2)

    print coefficients
    y_ideal = pow(10,coefficients[1])*numpy.power(self._x, sign(coefficients[0])*order)

    plot(self._x, y_ideal, '-k', lw=1)

    text(self._x[0], self._y[-1],'slope: ' + str(coefficients[0]))



  def save(self, filename):
    savefig(filename)
