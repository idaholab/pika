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
print t0

t1, ky1 = read('yeti_out_micro1.csv')
t2, ky2 = read('yeti_out_micro2.csv')
t3, ky3 = read('yeti_out_micro3.csv')
t4, ky4 = read('yeti_out_micro4.csv')
t5, ky5 = read('yeti_out_micro5.csv')


# Create the figure and plot the data
figure(figsize=(3.25,2.1))
plot(t1, ky1, '-x', lw=6, label='(a)')
plot(t1, ky1, '-o', lw=2, label='(b)')
plot(t2, ky2, '-s', lw=2, label='(c)')
plot(t3, ky3, '-d', lw=2, label='(d)')
plot(t4, ky4, '--', lw=2, label='(e)')
plot(t5, ky5, '-', lw=2, label='(f)')

legend(fontsize=10, loc=8)

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
#tight_layout()
savefig('pika_keff.pdf')
show()
