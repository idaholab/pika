#!/usr/bin/python

# Load necessary modules
import math
import sys
from pylab import *
from matplotlib.backends.backend_pdf import PdfPages
import numpy

import csv

def read(filename):

  with open(filename, 'rb') as csvfile:
    reader = csv.reader(csvfile)
    next(reader, None)  # skip the headers
    next(reader, None)  # skip first row
    next(reader, None)  # skip first row
    next(reader, None)  # skip first row
    next(reader, None)  # skip first row
  #  next(reader, None)  # skip first row
    t = []
    ky = []
    ky_initial = 1
    cnt = 0
    for row in reader:
      if cnt == 0:
        ky_initial = float(row[5])
        cnt += 1

      if len(row) > 2:
        t.append(float(row[0])/3600)
        ky.append(100*(float(row[5]) - ky_initial)/ky_initial)

  return t, ky

t0, ky0 = read('yeti_out_micro0.csv')
t1, ky1 = read('yeti_out_micro1.csv')
t2, ky2 = read('yeti_out_micro2.csv')
t3, ky3 = read('yeti_out_micro3.csv')
t4, ky4 = read('yeti_out_micro4.csv')
t5, ky5 = read('yeti_out_micro5.csv')


# Create the figure and plot the data
figure(figsize=(3.25,3))
plot(t0, ky0, '-r', lw=2, label='(a)')
gca().annotate('a,b,f', xy=(20, -1))

plot(t1, ky1, '-r', lw=2, label='(b)')
#gca().annotate('b', xy=(t1[-1]+0.1, ky1[-1]))

plot(t2, ky2, '-b', lw=2, label='(c)')
gca().annotate('c', xy=(t2[-1]+0.1, ky2[-1]))

plot(t3, ky3, '-y', lw=2, label='(d)')
gca().annotate('d', xy=(t3[-1], ky3[-1]-0.6))

plot(t4, ky4, '-g', lw=2, label='(e)')
gca().annotate('e', xy=(t4[-1], ky4[-1]+0.3))

plot(t5, ky5, '-r', lw=2, label='(f)')
#gca().annotate('f', xy=(t5[-1]+0.1, ky5[-1]))

#legend(fontsize=10, loc=8)

# Add axis labels
ylabel('Conductivity Change [%]', fontsize=10)
xlabel('Time [hrs]', fontsize=10)
#xlim([0,8.5])


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
savefig('yeti_keff.pdf')
show()
