import matplotlib.pyplot, numpy
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages

# Under development ...

class ConvergencePlot(object):
  def __init__(self, x, y):
    self._x = numpy.array(x)
    self._y = numpy.array(y)

    figure(figsize=(10,6))
    plot(sqrt(self._x), self._y, 'ob', markersize=12)

    self._gcf = gcf()
    self._gca = gca()

    gca().set_yscale('log')
    gca().set_xscale('log')

# Create the slope annotation
#plot([100,100], [0.1,0.024], '-k', lw=1)
#plot([50 ,100], [0.1,0.1], '-k', lw=1)
#text(70, 0.11, '1', size=18)
#text(104, 0.045, '2', size=18)

    # Add axis labels
    xlabel('sqrt(Num. DOFs)',{'fontsize':20})
    ylabel('L2 Error',{'fontsize':20})

    # Adjust tick mark fonts
    for xtick in  gca().xaxis.get_major_ticks():
      xtick.label.set_fontsize(18)

    for ytick in gca().yaxis.get_major_ticks():
      ytick.label.set_fontsize(18)

    # Apply grid marks
    grid(True)
    grid(True, which='minor', color='b')

  def fit(self):
    # Perform fit
    coefficients = numpy.polyfit(log10(sqrt(self._x)),log10(self._y), 1)
    polynomial = numpy.poly1d(coefficients)

    y_ideal = pow(10,coefficients[1])*numpy.power(sqrt(self._x),-2)

    plot(sqrt(self._x), y_ideal, '-k', lw=1)

    text(sqrt(self._x[0]),self._y[-1],'slope: ' + str(coefficients[0]))


    show()


  def save(self, filename):
    savefig(filename)
