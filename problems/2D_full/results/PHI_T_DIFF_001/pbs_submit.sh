#!/bin/bash
#PBS -N PHI_T_DIFF_001
#PBS -l select=1:ncpus=20:mpiprocs=20
#PBS -l place=scatter:excl
#PBS -l walltime=1:00:00






source /etc/profile.d/modules.sh
module load moose-dev-gcc

cd $PBS_O_WORKDIR

JOB_NUM=${PBS_JOBID%\.*}


export MV2_ENABLE_AFFINITY=0

mpiexec ~/Projects/pika/pika-oprof-opt -i phi_T_initial.i  


