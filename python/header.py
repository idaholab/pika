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

import os, sys

pika_dir = os.getenv('PIKA_DIR', os.path.abspath('..'))

header = []
header.append('/****************************************************************/\n')
header.append('/*       PIKA - Phase field snow micro-structure model          */\n')
header.append('/*                                                              */\n')
header.append('/*          Prepared by Battelle Energy Alliance, LLC           */\n')
header.append('/*            Under Contract No. DE-AC07-05ID14517              */\n')
header.append('/*            With the U. S. Department of Energy               */\n')
header.append('/*                                                              */\n')
header.append('/*            See COPYRIGHT for full restrictions               */\n')
header.append('/****************************************************************/\n')
header.append('\n')

for root, dirs, files in os.walk(pika_dir):
  for file in files:
    ext = os.path.splitext(file)[1]
    if ext == '.h' or ext == '.C' or ext == '.py':
      fid = open(os.path.join(root, file), 'r+')
      content = fid.read()
      fid.seek(0,0)
      fid.writelines(header)
      fid.write(content)
      fid.close()
