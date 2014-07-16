/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#!/usr/bin/python
# Interface thickness convergence in Pika, the

# Import necessary packages
import sys, os
from pylab import*

# Load Pika Python tools
sys.path.append(os.path.join(os.getenv('PIKA_DIR'), 'python'))
from tools import *

# Run the problem 
#runApp('phase_diffusion.i', mpi=12)

# Extract the data from the Postprocessor CSV output (.csv)
time_steps=100

#thickness array
w = []
t = []
for time in range(time_steps):
  str_time=str(time)
  filename = 'out_bubble_line_'+str_time.zfill(4)
  header, data = readCSV(filename + '.csv')
  
#  pos, phi = extractPostprocessorData(filename,x='x', y='phi')
  idx1=0
  idx2=0

  for index in range(len(data)):
    phi=float(data[index][1])
  
    if phi<1.0 and idx1 ==0:
      idx1 = index
    if phi<=-1.0 and idx2==0:
      idx2 = index
  w.append(abs(float(data[idx2][2])-float(data[idx1][2])))
  t.append(int(time))

plt = plot(t,w)
show()
