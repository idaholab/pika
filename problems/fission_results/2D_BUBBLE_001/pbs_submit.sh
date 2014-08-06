#!/bin/bash
#PBS -N 2D_BUBBLE_001
#PBS -l select=5:ncpus=20:mpiprocs=20
#PBS -l place=scatter:excl
#PBS -l walltime=3:00:00






source /etc/profile.d/modules.sh
module load moose-dev-gcc

cd $PBS_O_WORKDIR

JOB_NUM=${PBS_JOBID%\.*}


export MV2_ENABLE_AFFINITY=0

mpiexec ~/Projects/pika/pika-opt -i imported_initial_full.i  -log_summary


