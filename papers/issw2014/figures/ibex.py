#!/usr/bin/python

# Load necessary modules
import math
import sys
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages
import numpy

import csv
with open('ibex.csv', 'rb') as csvfile:
  reader = csv.reader(csvfile)
  next(reader, None)  # skip the headers
  Tm = []
  xm = []
  for row in reader:
    if len(row) > 2:
      Tm.append(float(row[0])-273.15)
      xm.append(40 - float(row[2])*100)

# Morstad Exp. 2 Raw data (4:00)
Te = [-7.55,-4.20,-0.89,-0.04,-0.33,-0.84,-1.13,-1.56,-2.10,-2.69,-3.19,-3.87,-4.50,-5.14,-5.88,-6.47,-8.59,-9.70,-10.16,-9.27,-8.80]
xe = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20, 25, 30, 35, 40]

print Tm

# Create the figure and plot the data
figure(figsize=(3.125,3.125))
plot(Te, xe, 'o-', markersize=5, lw=2, label='Morstad 2007')
plot(Tm, xm, '-k', lw=2, label='Ibex')

legend(fontsize=10, loc=4)

# Add axis labels
xlabel('Temperature [C]', fontsize=10)
ylabel('Depth [cm]', fontsize=10)

ylim(0,30)
gca().invert_yaxis()

# Adjust tick mark fonts
for xtick in  gca().xaxis.get_major_ticks():
    xtick.label.set_fontsize(10)

for ytick in gca().yaxis.get_major_ticks():
    ytick.label.set_fontsize(10)

# Apply grid marks
grid(True)
grid(True, which='minor', color='b')

# Show the file
tight_layout()
savefig('ibex.pdf')
show()
