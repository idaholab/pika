#!/usr/bin/python

# Load necessary modules
import math
import sys
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages
import numpy

import csv
with open('micro_keff_out.csv', 'rb') as csvfile:
  reader = csv.reader(csvfile)
  next(reader, None)  # skip the headers
  next(reader, None)  # skip initial data

  t = []
  kx = []
  ky = []
  diff = []
  kx_initial = 1
  ky_initial = 1
  cnt = 0
  for row in reader:
    if cnt == 0:
      kx_initial = float(row[4])
      ky_initial = float(row[5])
      cnt += 1

    if len(row) > 2:
      t.append(float(row[0])/3600)
      print kx_initial
      kx.append(100*(float(row[4]) - kx_initial)/kx_initial)
      ky.append(100*(float(row[5]) - ky_initial)/ky_initial)
      diff.append(ky[-1] - kx[-1])

# Create the figure and plot the data
figure(figsize=(3.25,2.1))
plot(t, kx, '-', lw=2, label='x', color='0.5')
plot(t, ky, '-k', lw=2, label='y')
#plot(t, diff, '-k', lw=2, label='diff')

legend(fontsize=10, loc=8)

# Add axis labels
ylabel('Conductivity Change [%]', fontsize=10)
xlabel('Time [hrs]', fontsize=10)
xlim([0,8.5])


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
savefig('pika_keff.pdf')
show()
