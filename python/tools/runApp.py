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

import os, subprocess

##
# Run an application for purposes of performing convergence study
# @param input_file The input file name
#
# Optional:
#   program=<str> The program to execute (pika-oprof)
#   refinements=<int> The number of successive runs to perform with additional uniform refinement (0)
#   mpi=<int> The number of MPI processes to run (1)
#   output_base=<str> The output file base (<input_file>_out)
def runApp(input_file, **kwargs):

  # Get the default base
  default_base, ext = os.path.splitext(input_file)
  default_base += '_out'

  # Extract the optional agruemnts
  refinements = kwargs.pop('refinements', 0)
  mpi = kwargs.pop('mpi', 1)
  program = kwargs.pop('program', os.path.join(os.getenv('PIKA_DIR'), 'pika-oprof'))
  file_base = kwargs.pop('output_base', default_base )

  for i in range(refinements+1):
    if refinements > 0:
      out_name = file_base + '_' + str(i)
    else:
      out_name = file_base
    cmd = ['mpiexec', '-n', str(mpi), program, '-i', input_file,
           'Mesh/uniform_refine='+str(i), 'Outputs/file_base='+out_name]
    print ' '.join(cmd)
    subprocess.call(cmd)
