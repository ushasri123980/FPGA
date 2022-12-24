//Header files
#include<iostream>
#include<fstream>
#include<sstream>
#include<bits/stdc++.h>

using namespace std;
typedef pair<int, int> iPair;
#define INF 0x3f3f3f3f
vector<vector<int>> input;

/*Function to read file into a 2D input Vector*/
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
    //cout<<"total lines: "<<n<<endl; 
}

/*updating a set to intersection with other set */
//Update a set with intersection with other?
set<int> intersection(set<int> set_1, set<int> set_2)
{
std::set<int>::iterator it1 = set_1.begin();
std::set<int>::iterator it2 = set_2.begin();
// cout<<"cddt is given by: ";
// for(auto it:set_1)
// {
//     cout<<it<<" ";
// }
// cout<<endl;
// cout<<"set of nodes<d is given by: ";
// for(auto it:set_2)
// {
//     cout<<it<<" ";
// }
// cout<<endl;
    while ( (it1 != set_1.end()) && (it2 != set_2.end()) )
        {
            if (*it1 < *it2) {
                set_1.erase(it1++);
            } else if (*it2 < *it1) {
                ++it2;
            } else { // *it1 == *it2
                    ++it1;
                    ++it2;
            }
        }
    set_1.erase(it1, set_1.end());
// cout<<"cddt after intersection is given by: ";
// for(auto it:set_1)
// {
//     cout<<it<<" ";
// }
// cout<<endl;
return set_1;
}


// Global Variables
    int no_of_fpga;
    int no_of_conn_channels;
    int capacity_per_fpga;
    int no_of_nodes;
    int no_of_nets;
    int no_of_fixed_nodes;   


/* Class of graphs and a constructor to initialise no of edges and
        function to addedge and determine length of minimum path:
-------------------------------------------------------------------------------------*/

class Graph {
        int V; 
        list<pair<int, int> >* adj;
    
    public:
        Graph(int V); 
        void addEdge(int u, int v, int w);
        vector<int> shortestPath(int s);
        int minimum_distance(int s,int d);
        int max_min_dist(int s);
};
    Graph::Graph(int V)
    {
        this->V = V;
        adj = new list<iPair>[V];
    }
    
    void Graph::addEdge(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    vector<int> Graph::shortestPath(int src)
    {
        int maxi=0;
        priority_queue<iPair, vector<iPair>, greater<iPair> >
            pq;
        vector<int> dist(V, INF);
        pq.push(make_pair(0, src));
        dist[src] = 0;
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            list<pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = (*i).first;
                int weight = (*i).second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        //cout<<"Vertex Distance from "<<src<<" is given by"<<endl;        
        for (int i = 0; i < V; ++i)
        {
            //printf("%d \t\t %d\n", i, dist[i]);
            maxi=max(maxi,dist[i]);
        }              
        dist.push_back(maxi);
        return dist;
}

    int Graph::minimum_distance(int src,int des)
    {
        int maxi=0;
        priority_queue<iPair, vector<iPair>, greater<iPair> >
            pq;
        vector<int> dist(V, INF);
        pq.push(make_pair(0, src));
        dist[src] = 0;
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            list<pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = (*i).first;
                int weight = (*i).second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }        
        return dist[des];
}

    int Graph::max_min_dist(int src)
    {
        int maxi=0;
        priority_queue<iPair, vector<iPair>, greater<iPair> >
            pq;
        vector<int> dist(V, INF);
        pq.push(make_pair(0, src));
        dist[src] = 0;
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            list<pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = (*i).first;
                int weight = (*i).second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }     
        for (int i = 0; i < V; ++i)  maxi=max(maxi,dist[i]);             
        return maxi;
    }

void global_input()
{
    string filename;
    cout<<"Enter the input text Filename: "<<endl;
    cin>>filename;
        readfile(filename);
         no_of_fpga=input[0][0];
         no_of_conn_channels=input[0][1];
         capacity_per_fpga=input[0][2];
         no_of_nodes=input[0][3];
         no_of_nets=input[0][4];
         no_of_fixed_nodes=input[0][5];  
}
        

int main()
{ 
    // string filename;
    // cout<<"Enter the input text Filename: "<<endl;
    // cin>>filename;
    //     readfile(filename);
    //     int no_of_fpga=input[0][0];
    //     int no_of_conn_channels=input[0][1];
    //     int capacity_per_fpga=input[0][2];
    //     int no_of_nodes=input[0][3];
    //     int no_of_nets=input[0][4];
    //     int no_of_fixed_nodes=input[0][5];  
        
        global_input();  

        cout<<"All the information given: "<<endl;
        cout<<"Number of FPGA: "<<no_of_fpga<<endl;
        cout<<"Number of Connection Channels (Total connections between FPGA): "<<no_of_conn_channels<<endl;
        cout<<"Capacity per FPGA (Max no of nodes handled by each FPGA): "<<capacity_per_fpga<<endl;
        cout<<"Number of Nodes in circuit: "<<no_of_nodes<<endl;
        cout<<"Number of nets(Total connections between nodes): "<<no_of_nets<<endl;
        cout<<"Number of Fixed Nodes: "<<no_of_fixed_nodes<<endl;
        
        Graph fpga_ckt(no_of_fpga);
        Graph nodes_ckt(no_of_nodes);
        queue<pair<int,int>> q;
        set<int> set_of_fpga;
        set<int> fixed_circuit_nodes;
        set<int> movable_circuit_nodes;
        map<iPair,set<int>> fpga_map;
        map<iPair,set<int>> nodes_map;
        map<int,set<int>> cddt;

    //Formation of graph of connection between Fpga's - FPGA graph Gˆ(Eˆ, Vˆ )
    for(int i=1;i<=no_of_conn_channels;i++) fpga_ckt.addEdge(input[i][0],input[i][1],1);                
    // for(int i=0;i<no_of_fpga;i++)
    // {
    //     vector<int> dist=fpga_ckt.shortestPath(i);
    //     cout<<"Shortest distance from: "<<i<<" to:"<<endl;
    //     for(int j=0;j<dist.size();j++)
    //     {
    //         cout<<"destination "<<j<<" is "<<dist[j]<<endl;
    //     }
    //     cout<<endl;
    // }

    //Formation of graph of connection between Node's - Netlist Circuit graph G(E, V)
    for(int i=no_of_conn_channels+1;i<=no_of_conn_channels+no_of_nets;i++)
        for(int j=1;j<input[i].size();j++) nodes_ckt.addEdge(input[i][0],input[i][j],1);                  
    
    //Formation of Fixed node-FPGA pair queue Q and set of fixed nodes.
    for(int i=no_of_conn_channels+no_of_nets+1;i<input.size();i++)  
    {
        q.push(make_pair(input[i][0], input[i][1])); 
        fixed_circuit_nodes.insert(input[i][0]);
    }

    //Formation of set of movable nodes.
    for(int i=0;i<no_of_nodes;i++) if(fixed_circuit_nodes.find(i)==fixed_circuit_nodes.end()) movable_circuit_nodes.insert(i);
    
    //Formation of map of Fpga Sˆ(ˆvi,x) 
    for(int i=0;i<no_of_fpga;i++)
    {
        set_of_fpga.insert(i);
        for(int x=1;x<=fpga_ckt.max_min_dist(i);x++)
        {            
            set<int> set_of_fpga;
            for(int j=0;j<no_of_fpga;j++) 
            {
                if(fpga_ckt.minimum_distance(i,j)<=x) 
                {
                set_of_fpga.insert(j); 
                }
            }  
            fpga_map[make_pair(i,x)]=set_of_fpga;         
        }
    }
   
   //Formation of map of nodes S(vi,d)
    queue<pair<int,int>> temp=q;
    while(!temp.empty())
    {
        set<int> set_of_nodes;
        int d=fpga_ckt.max_min_dist(temp.front().second);
        for(int j=0;j<no_of_nodes;j++)  if(nodes_ckt.minimum_distance(temp.front().first,j)<d) set_of_nodes.insert(j);
        nodes_map[make_pair(temp.front().first,d)]=set_of_nodes;
        temp.pop();
    }

    // for(auto it=nodes_map.begin();it!=nodes_map.end();it++)
    // {
    //     cout<<it->first.first<<" "<<it->first.second<<endl;
    //     for(auto i:it->second)
    //     {
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    // }

    //Assigning initial values for cddt - line 8 and line 9 in Algorithm.
    temp=q;
    while(!temp.empty())
    {
        cddt[temp.front().first]={temp.front().second};
        temp.pop();
    }
    for(auto i:movable_circuit_nodes) cddt[i]=set_of_fpga;

    cout<<"cddt Before line 10 in Algorithm: [Initial Assumption]"<<endl;
    for(auto& it:cddt)
    {
        cout<<"Node id: "<<it.first<<" and its corresponding set of cddt: ";
        for(auto i:it.second)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }
    
    temp=q;
    while(!temp.empty())
    {
        //cout<<"Game Begins"<<endl;
        int i=temp.front().first;
        int fix_fpga=temp.front().second;
        int d=fpga_ckt.max_min_dist(fix_fpga);
        temp.pop();     
        // cout<<"cddt before checking node "<<i<<" is given by: "<<endl;
        // for(auto& it:cddt)
        // {
        //     cout<<"Node id: "<<it.first<<" and its corresponding set of cddt: ";
        //     for(auto i:it.second)
        //     {
        //         cout<<i<<" ";
        //     }
        //     cout<<endl;
        // }   
        for(auto j:nodes_map[make_pair(i,d)])
        {
           if( movable_circuit_nodes.find(j)!=movable_circuit_nodes.end())
           {
            int k=nodes_ckt.minimum_distance(i,j);            
           cddt[j]= intersection(cddt[j],fpga_map[make_pair(fix_fpga,k)]);            
            if(cddt[j].size()==1) temp.push(make_pair(j,*cddt[j].begin()));
            if(cddt[j].size()==0) return 0;
           }
        }
        // cout<<"cddt after checking node "<<i<<" is given by: "<<endl;
        // for(auto& it:cddt)
        // {
        //     cout<<"Node id: "<<it.first<<" and its corresponding set of cddt: ";
        //     for(auto i:it.second)
        //     {
        //         cout<<i<<" ";
        //     }
        //     cout<<endl;
        // }   
    }  
    
    cout<<"Final cddt"<<endl;
    for(auto& it:cddt)
    {
        cout<<"Node id: "<<it.first<<" and its corresponding set of cddt: ";
        for(auto i:it.second)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }

return 0;
}