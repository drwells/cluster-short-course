# Scheduling jobs on a cluster

## Preliminaries
* Suppose you want to run the same program with 100 different parameter sets.
  What's the best way to keep everything organized?
* The program you want to run has billions of degrees of freedom and is too slow
  to run on a single processor, or even whatever number of processors your
  computer has - how can we run programs on hundreds or thousands of processors
  concurrently?

In both cases, the answer is to use *batch computing*. Rather than starting a
program manually, we will write a script containing what we want to do and then
a *scheduler* will run it for us at some point in the future. In this course we
will look at the most popular scheduler - slurm, the Simple Linux Utility for
Resource Management (that acronym is made up - its just named after the drink
from Futurama). Lots of other such utilities exist: for example, AWS (Amazon Web
Services) uses its own management software but its still built on the same
concepts.

To use slurm, we will write shell scripts and *submit* them to slurm. At some
point in the future (e.g., when all previously scheduled jobs have been run)
slurm will execute our program for us. Hence - good shell scripting skills are
the right place to start when it comes to using slurm!

For historical reasons, these scripts are commonly called "batch scripts"
because they specify a list of commands to be run in a single batch.

## Basic Slurm Usage
### Jargon
* *batch script*: same as a shell script. Since slurm executes all the commands
  in this script they commands are 'batched' (hence the name).
* *job*: the name of the batch script.
* *node*: Clusters are (as the name implies) created by networking together lots
  of computers together. The individual unit here, which functions somewhat like
  a PC, is a node.
* *partition*: clusters tend to be broken up into separate groups of computers.
  For example, all of the nodes containing GPUs tend to be grouped together into
  a GPU partition.

### Commonly used executables
* `sbatch` This command submits a batch script to slurm - each submitted script
  corresponds to one new job.
* `srun` This is like sbatch but it sits around until the job is done - this is
  rarely what we want to do. The main reason to use `srun` is that Slurm is
  (typically!) compiled in a way that it understands MPI, so you can do
 ```
srun big_application
 ``` 
   instead of typing out
 ```
mpirun -np 128 big_application
 ``` 
  though again (this is complex) some versions of `mpirun` will detect that they
  are running in slurm and use that to figure out their own parallelization.
      
* `squeue` Jobs are queued: jobs submitted earlier tend to be executed earlier.
  The scheduling rules are actually fairer than that and therefore much more
  complicated.
* `sinfo` Print information about the machine: e.g., basic information on the
  partitions present on the machine.

### Dealing with output
A few words of advice:
1. The amount of space in your home directory is very limited and accessing it
   is relatively slow.
2. The amount of space on the scratch drive is quite large and accessing it is
   relatively fast: however, (at UNC) this drive is cleaned out every 90 days.
   
Hence: on UNC machines we should always put our output in the 90 day scratch
drive (especially if we have a lot of it) and then copy and paste or postprocess
it later.

## A Slurm template
Here's an example taken straight from our group (one of Marshall's scripts):
```shell
#!/bin/bash

#SBATCH --job-name=42contraction
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=16
#SBATCH --partition=skylake
#SBATCH --error=contraction42_err
#SBATCH --output=contraction42_out
#SBATCH --mem=10GB
#SBATCH --time=7-0:0:0

# note that we don't specify anything else to mpirun - slurm will tell mpirun 
# what to do.
mpirun ./main3d contraction_tests/input.contraction42 -stokes_ksp_monitor -velocity_ksp_type cg -velocity_pc_type none -velocity_ksp_norm_type none -pressure_ksp_norm_type none -stokes_ksp_rtol 1.0e-6 -stokes_ksp_converged_reason
```

As you know - its just a shell script. Slurm is able to interpret the lines
starting with `#SBATCH` in a special way. In order:
1. The name of the job. This lets us check on it with `squeue` easily.
2. The number of nodes to use.
3. Ask for sixteen processors per node. Another option here is `--exclusive`
   which will request all of the processors (and memory!) on each node.
4. The partition.
5. Where to write the standard error.
6. Where to write the standard output.
7. The amount of memory we want to use per node.
8. The expected length of the job. If the job is still going at this point then
   slurm will stop it.
   
In this example, the executable `./main3d` knows how to save its state to disk:
this is called a *restart file*. With a restart file we can start a new job to
resume the computation if it needs more than a week to finish.

Some more flags you might want to use are:
* `--mail-user=` the email address slurm will use to inform you of updates.
* `--mail-type=BEGIN,END` ask slurm to email you when the job starts and finishes.
* `--dependency` lets you specify that one job depends on another job. If you
  are clever you can specify lots of work all at once with this flag, like in a
  acyclic graph.
  
## Example 0: log in to longleaf or dogwood and see what people are up to
Try using `squeue` in conjunction with `wc` and `grep` to see who is running
what. I recommend also using the `finger` and `pinky` utilities to look around.

## Example 1: hello, slurm
Make a new hello world script which prints 'hello, slurm to the standard
output. Submit the job to slurm under VCL.

## Example 2: array jobs, done manually
Write a second slurm script which runs the hello world script ten times (i.e.,
sequential execution).

## Example 3: array jobs, done with slurm's arrays
Here we'll use
```
#SBATCH --array=1-10
```
to set up ten jobs. We can get the number of the job with
```
TASK_ID=$SLURM_ARRAY_TASK_ID
```
which slurm sets as an environment variable for us.

Make each job print "hello slurm from process X" in which "X" is the array job
number.

To set up the output files: try
```
#SBATCH --output=%A_%a.out
#SBATCH --error=%A_%a.error
``` 
here slurm will substitute in the master job id for `%A` and the task id (one
through ten) for `%a`, respectively.
