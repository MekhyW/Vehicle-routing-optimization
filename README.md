# Vehicle Routing Optimization

Felipe Catapano Emrich Melo

## Project Context

The Vehicle Routing Problem (VRP) is a combinatorial optimization and integer programming problem seeking to service a number of customers with a fleet of vehicles. The VRP is an essential problem in the fields of logistics and transportation, with wide-ranging practical applications from courier services to large-scale distribution networks. However it is considered an NP-hard problem, meaning that finding the optimal solution is computationally infeasible for large instances. 

This project presents a C++ application designed to solve the VRP using various solvers, including brute force, heuristic approaches, and parallelization techniques utilizing OpenMP and MPI.

### Restrictions and Requirements

- Vehicle Capacity: Each vehicle in the fleet has a maximum load capacity. This capacity represents the maximum weight or volume of goods that the vehicle can carry at any given time. The solution must ensure that the total load assigned to each vehicle does not exceed its capacity.

- Customer Demand: Each customer has a specific demand, which represents the quantity of goods they require. This demand must be completely met by a single vehicle, meaning no partial deliveries are allowed.

- Route Cost: Each route has an associated cost, which is a comprehensive measure including the distance traveled, delivery time, and fuel consumption. The objective of the VRP is to minimize the total route cost for the entire fleet.

- Maximum Number of Visits per Route: Each route has a constraint on the maximum number of cities (customers) that can be visited. This limitation ensures that routes remain manageable and within practical operational limits.

- Starting and Arriving Point: All vehicles start and end their routes at the company's warehouse. This requirement ensures a practical implementation of the routing solution, where all vehicles return to the base after completing their deliveries.

## File Structure

```
.
├── build/
│   ├── (This directory holds the compiled files generated during the compilation process.)
├── include/
│   ├── (Header files (.h) required for the project. These files define classes, functions, and constants used throughout the project)
│   ├── brute_force_ES_solver.h
│   ├── brute_force_solver.h
│   ├── graph_class.h
│   ├── heuristic_solver.h
│   ├── mpi_solver.h
│   ├── openmp_solver.h
│   └── openmp-mpi_solver.h
├── docs/
│   ├── (Documentation files)
├── input/
│   ├── (This directory contains input text files representing different problem instances for the Vehicle Routing Problem. Each text file is parsed as an instance of the problem)
├── output/
│   ├── (Holds output files containing answers and solver execution times for each problem instance. These files are generated during the execution of the solvers)
├── slurm/
│   ├── (Files designed to facilitate execution in a cluster environment)
├── solvers/
│   ├── (C++ files (.cpp) for each solver implementation. These files contain the actual code for solving the Vehicle Routing Problem using various algorithms and techniques)
├── src/
│   ├── main.cpp
│   └── graph_class.cpp
├── tools/
│   ├── (Python scripts for generating input files, validation, and benchmarking)
├── makefile
├── README.md
└── requirements.txt
```


## Project Features

1. Solver Selection
The project offers a variety of solvers to tackle the Vehicle Routing Problem (VRP).

2. Batch Processing
The project also includes batch processing capabilities. Users can provide a directory containing input files for VRP instances, and the script will automatically iterate through them, solving each instance sequentially.

3. Logging
To enable performance analysis and benchmarking, it incorporates logging functionality. Execution times of each solver are logged to individual output files, providing insights into solver efficiency and performance across different VRP instances.

5. Solution Evaluation
Upon solving each VRP instance, the project evaluates and prints the best route combination found by the selected solver. Additionally, it displays the associated cost of the optimized route, aiding in assessing the quality and effectiveness of the solution approach.

6. Input File Generation
For testing and experimentation purposes, the project provides scripts for generating input files representing VRP instances. These scripts enable users to create custom VRP scenarios, facilitating thorough testing and validation of the solvers.

## Usage Instructions

To use the VRP Solver, follow these steps:

#### 1. Clone the Repository
```bash
git clone https://github.com/MekhyW/Vehicle-routing-optimization.git
```

#### 2. Install Python Requirements: 
```bash
pip install -r requirements.txt
```

#### 3. Check MPI and OpenMP Installation
Make sure that mpic++ is installed on your system with OpenMP support. This is required for compiling and running the parallelized solvers.

#### 4. Compile the Project
```bash
make
```

#### 5. Generate Input Graphs
You can generate input graphs programmatically using the provided Python script or create them manually. To generate input graphs using the provided script, run:
```bash
python tools/graph_gen.py <num_nodes>
```
This will generate a graph with the specified number of nodes and save it to a file named `graph-<num_nodes>.txt`.

#### 6. Run the Program
After generating input graphs or preparing them manually, you can execute the program. Use the following command:
```bash
./main <capacity> <solver>
```
Replace `<capacity>` with the maximum capacity of the vehicles and `<solver>` with the name of the solver you want to use. All files in the `input/` directory will be processed sequentially using the specified solver.

#### 7. Example Input File:
Below is an example input file format that can be used as input for the program. Save it as a text file and place it in the input/ directory.
```
5
1 5
2 6
3 4
4 4
10
0 1 22
1 0 22
0 2 47
2 0 47
0 3 23
3 0 23
0 4 30
4 0 30
1 4 14
2 3 71
```

#### 8. Submitting Jobs to a Cluster
If you are running the program on a cluster environment, you can use the provided SLURM scripts to submit jobs. Modify the scripts as needed and submit them using:
```bash
sbatch slurm/{script_name}.slurm
```