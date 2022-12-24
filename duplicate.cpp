#include<iostream>
#include<fstream>
#include<sstream>
#include<bits/stdc++.h>

using namespace std;
vector<vector<int>> input;
void readfile(string filename)
{    
int word;
    string line;    
	ifstream inputFile;    
	inputFile.open(filename); 
    int n=0;
    if(inputFile)
    {
        while(getline(inputFile, line, '\n'))  
        {            
            vector<int> temp;
        istringstream ss(line);
         while(ss >> word)
            {
                temp.push_back(word);
            }   
            input.emplace_back(temp);
            n++;  
        }  
            
    }
    cout<<"total lines: "<<n<<endl; 
}
int main() {
    string filename;
	cout<<"Enter the Input file name: ";
    cin>>filename;
   readfile(filename);
   int no_of_fpga=input[0][0];
   int no_of_conn_channels=input[0][1];
   int capacity_per_fpga=input[0][2];
   int no_of_nodes=input[0][3];
   int no_of_nets=input[0][4];
   int no_of_fixed_nodes=input[0][5];

   cout<<"All the information given: "<<endl;
   cout<<"Number of FPGA: "<<no_of_fpga<<endl;
   cout<<"Number of Connection Channels (Total connections between FPGA): "<<no_of_conn_channels<<endl;
   cout<<"Capacity per FPGA (Max no of nodes handled by each FPGA): "<<capacity_per_fpga<<endl;
   cout<<"Number of Nodes in circuit: "<<no_of_nodes<<endl;
   cout<<"Number of nets(Total connections between nodes): "<<no_of_nets<<endl;
   cout<<"Number of Fixed Nodes: "<<no_of_fixed_nodes<<endl;

   vector<vector<int>> fpga_adj_matrix(no_of_fpga,vector<int>(no_of_fpga,0));
   for(int i=1;i<=no_of_conn_channels;i++)
   {
    fpga_adj_matrix[input[i][0]][input[i][1]]=1;
    fpga_adj_matrix[input[i][1]][input[i][0]]=1;
   }   

    vector<vector<int>> netlist_adj_matrix(no_of_nodes,vector<int>(no_of_nodes,0));
    for(int i=no_of_conn_channels+1;i<=no_of_conn_channels+1+no_of_nets;i++)
    {
        for(int j=1;j<input[i].size();j++)
        {
            netlist_adj_matrix[input[i][0]][input[i][j]]=1;
            netlist_adj_matrix[input[i][j]][input[i][0]]=1;
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > fixed_nodes;    
    for(int i=no_of_conn_channels+no_of_nets+2;i<input.size();i++)
    {
        fixed_nodes.push(make_pair(input[i][0], input[i][1]));
    }
    
   // const int N=1e5+7;
    vector<int> adj[no_of_fpga];
    for(int i=1;i<=no_of_conn_channels;i++)
    {
        adj[input[i][0]].push_back(input[i][1]);
        adj[input[i][1]].push_back(input[i][0]);
    }

    cout<<"Adj list of FPGA Connections: "<<endl;
    
    for(int i=0;i<no_of_fpga;i++)
    {
        cout<<i<<"->";
         vector<int>::iterator it;
        for(it=adj[i].begin();it!=adj[i].end();it++)
        {           
            cout<<*it<<" ";
        }
        cout<<endl;
    }









    cout<<"Adj matrix for connection between FPGA: "<<endl;

    for(int i=0;i<fpga_adj_matrix.size();i++)
    {
        for(int j=0;j<fpga_adj_matrix[i].size();j++)
        {
            cout<<fpga_adj_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Adj matrix for connection between nodes in netlist: "<<endl;

    for(int i=0;i<netlist_adj_matrix.size();i++)
    {
        for(int j=0;j<netlist_adj_matrix[i].size();j++)
        {
            cout<<netlist_adj_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Queue of Fixed nodes: "<<fixed_nodes.size()<<endl;    

    while(!fixed_nodes.empty())
    {
        cout << fixed_nodes.top().first<<" "<<fixed_nodes.top().second << endl;
        fixed_nodes.pop();
    }

    //Printing input vector - Reading input from file to a 2D vector.
     for(int i=0;i<input.size();i++)
    {
        for(int j=0;j<input[i].size();j++)
        {
            cout<<input[i][j]<<" ";
        }
        cout<<endl;
    }
	return 0;
}