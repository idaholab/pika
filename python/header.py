#!/usr/bin/python
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

import os, sys




#header = []
#header.append('/****************************************************************/\n')
#header.append('/*       PIKA - Phase field snow micro-structure model          */\n')
#header.append('/*                                                              */\n')
#header.append('/*          Prepared by Battelle Energy Alliance, LLC           */\n')
#header.append('/*            Under Contract No. DE-AC07-05ID14517              */\n')
#header.append('/*            With the U. S. Department of Energy               */\n')
#header.append('/*                                                              */\n')
#header.append('/*            See COPYRIGHT for full restrictions               */\n')
#header.append('/****************************************************************/\n')
#header.append('\n')


# Creates the correct header for python or cpp
def buildHeader(ext):

  width = 80

  header = []
  header.append('Pika: Phase field snow micro-structure model')
  header.append('')
  header.append('(C) 2014 Battelle Energy Alliance, LLC')
  header.append('ALL RIGHTS RESERVED')
  header.append('')
  header.append('Prepared by Battelle Energy Alliance, LLC')
  header.append('Under Contract No. DE-AC07-05ID14517')
  header.append('With the U. S. Department of Energy')

  output = []
  if ext == '.C' or ext == '.h':
    strt = '/*'
    stop = '*/'
    fill = '*'
  elif ext == '.py':
    strt = '#'
    stop = '#'
    fill = '#'

  line  = strt + fill*width + stop + '\n'

  output.append(line)
  for h in header:
    output.append(strt + h.center(width) + stop + '\n')
  output.append(line)

  return output

# Removes old headers
def stripHeader(filename):

  #
  output = []
  in_header = False

  # Locate header start and stop locations
  fid = open(filename, 'r')
  cnt = 0
  for line in fid:
    if line.startswith('#***') or line.startswith('####') or line.startswith('/***') :
      in_header = not in_header
      continue

    if not in_header:
      output.append(line)

  fid.close()

  fid = open(filename, 'w')
  for line in output:
    fid.write(line)
  fid.close()

# Adds new header
def insertHeader(filename):

  name, ext = os.path.splitext(filename)
  header = buildHeader(ext)

  fid = open(filename, 'r+')
  lines = fid.readlines()
  fid.seek(0,0)


  if lines[0].startswith('#!/usr/bin/python'):
    fid.write(lines[0])
    lines.pop(0)

  fid.writelines(header)
  fid.writelines(lines)
  fid.close()

if __name__ == '__main__':

  pika_dir = os.getenv('PIKA_DIR', os.path.abspath('..'))

  for root, dirs, files in os.walk(pika_dir):
    for file in files:
      ext = os.path.splitext(file)[1]
      if ext == '.h' or ext == '.C' or ext == '.py':
        full_file = os.path.join(root,file)
        stripHeader(full_file)
        insertHeader(full_file)
