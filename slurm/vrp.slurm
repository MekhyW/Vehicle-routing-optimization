#!/bin/bash
#SBATCH --job-name=vehicle-routing-optimization
#SBATCH --output=vehicle-routing-optimization_job.out
#SBATCH --error=vehicle-routing-optimization_job.err
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=8
#SBATCH --nodes=4
#SBATCH --time=02:00:00
#SBATCH --partition=espec
#SBATCH --mem=2G

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

make

mpirun -np $SLURM_NTASKS ./main $VEHICLE_CAPACITY $MAX_STOPS $SOLVER
