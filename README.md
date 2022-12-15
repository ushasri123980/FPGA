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
1. The first part is a single line listing the total number of FPGAs, total number of FPGA connection
channels, capacity per FPGA, total number of nodes, total number of nets, and total number of fixed
nodes. Format:<br />
Total number of FPGAs     Total number of FPGA connection channels         Capacity per FPGA           Total
number of nodes        Total number of nets         Total number of fixed nodes <br />
A sample of the first part is given below.<br />
4 3 3 8 5 2

Note that the FPGA indices are from 0 to < Total number of FPGAs> -1. The node indices are from 0
to <Total number of nodes>-1
  
 2. Each line of the second part lists the two FPGAs connected by each FPGA connection channel. The
number of lines in the second part is equal to the total number of FPGA connection channels.<br />
Format:<FPGA id> <FPGA id><br />
A sample of the second part is given below.<br />
 0 3 <br />
  1 3 <br />
  2 3 <br />
  
  3. The third part provides the information of the nets. The information of each net is given by a
separate line where the first label is the id of its source node and the remaining labels are the ids of
its sink nodes. The number of lines for the third part is equal to the total number of nets.<br />
Format:<source node id> <sink node id><sink node id>…<br />
A sample of the third part is given below.<br />
  0 1 2<br />
1 2 6<br />
2 3 5<br />
3 4<br />
6 7<br />
  4. The final part is the fixed node description. The information of each fixed node is given by a
separate line where the first label is the id of the fixed node and the second label is the id of the
FPGA it is assigned to.<br />
Format:<fixed node id><FPGA id><br />
A sample input of the final part is given below.<br />
  2 3<br />
  4 0<br />
  
### output Format
Output the partitioning result in the order of the node id. For each line, the first label is the id of
node and the second label is the id of FPGA which it is assigned to.<br />
Format: <node id><FPGA id><br />


