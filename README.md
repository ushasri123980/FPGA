# FPGA

# TopoPart: a Multi-level Topology-Driven Partitioning Framework for Multi-FPGA Systems

### Dan Zheng
dzheng@cse.cuhk.edu.hk
### Xinshi Zang
xszang@cse.cuhk.edu.hk
### Martin D.F. Wong
mdfwong@cuhk.edu.hk

### Problem Statement:
This design project is completely open in terms of how you solve the problem. (You may propose your
own approach or follow previously proposed approaches in the literature.)
You may work individually or in a team of two persons, you will receive an additional bonus if you
finish this project on your own.
Given a circuit netlist (V, E) where V represents the set of circuit nodes and E represents the set of
nets (each net is a directed hyperedge), and a system graph (V’,E’) where V’ represents the set of
FPGAs and E’ represents the set of connection channels connecting specific pairs of FPGAs. Each net
has a unique source plus one or more sinks. We want to assign the circuit nodes to the given FPGAs
to minimize the sum of external degrees of all FPGAs subject to the following constraints. (The
external degree of a FPGA Fi is defined as the number of hyperedges incident with Fi but not fully
inside Fi.)
1. Fixed node constraints: There are some circuit nodes which are already assigned to specific FPGAs
and cannot be moved to other FPGAs.
2. Partition size constraints: The total number of circuit nodes assigned to each FPGA must not
exceed the capacity of a FPGA (we assume all FPGAs have the same capacity).
3. Topology constraints: If node u is the source node of a net and node v is a sink node of the same
net, then nodes u and v are either assigned to the same FPGA (i.e., FPGA(u) = FPGA(v)) or assigned
to two neighboring FPGAs (i.e., (FPGA(u), FPGA(v)) ∈ E’).

### Input Format
There are mainly four parts in the input file.
The first part is a single line listing the total number of FPGAs, total number of FPGA connection
channels, capacity per FPGA, total number of nodes, total number of nets, and total number of fixed
nodes. Format:<br />
Total number of FPGAs  "\t"  Total number of FPGA connection channels      Capacity per FPGA       Total
number of nodes     Total number of nets      Total number of fixed nodes <br />
A sample of the first part is given below.
Note that the FPGA indices are from 0 to < Total number of FPGAs> -1. The node indices are from 0
to <Total number of nodes>-1
