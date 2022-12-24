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
    cout<<"total lines: "<<n<<endl; 
}

vector<int> intersetion_of_vectors(vector<int> vector1,vector<int> vector2)
{
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());  
    cout << "First Vector: ";
    for (int i = 0; i < vector1.size(); i++)
        cout << vector1[i] << " ";
    cout << endl;  
    cout << "Second Vector: ";
    for (int i = 0; i < vector2.size(); i++)
        cout << vector2[i] << " ";
    cout << endl;
  
    vector<int> v(vector1.size() + vector2.size());
    vector<int>::iterator it, st;
  
    it = set_intersection(vector1.begin(),vector1.end(),vector2.begin(),vector2.end(),v.begin());    
    for (st = v.begin(); st != it; ++st)
        cout << *st << ", ";
    cout << '\n';
    return v;
}
        int no_of_fpga;
        int no_of_conn_channels;
        int capacity_per_fpga;
        int no_of_nodes;
        int no_of_nets;
        int no_of_fixed_nodes;    
        
/*      Class of graphs and a constructor to initialise no of edges and
        function to addedge and determine length of minimum path:
-------------------------------------------------------------------------------------*/ 
class Graph {
        int V; 
        list<pair<int, int> >* adj;
    
    public:
        Graph(int V); 
        void addEdge(int u, int v, int w);
        vector<int> shortestPath(int s);
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
    
int main()
{    

    string filename;
    cout<<"Enter the input text Filename: "<<endl;
    cin>>filename;
        readfile(filename);
        int no_of_fpga=input[0][0];
        int no_of_conn_channels=input[0][1];
        int capacity_per_fpga=input[0][2];
        int no_of_nodes=input[0][3];
        int no_of_nets=input[0][4];
        int no_of_fixed_nodes=input[0][5];  
        priority_queue<iPair, vector<iPair>, greater<iPair> > fixed_nodes;
        // cout<<"All the information given: "<<endl;
        // cout<<"Number of FPGA: "<<no_of_fpga<<endl;
        // cout<<"Number of Connection Channels (Total connections between FPGA): "<<no_of_conn_channels<<endl;
        // cout<<"Capacity per FPGA (Max no of nodes handled by each FPGA): "<<capacity_per_fpga<<endl;
        // cout<<"Number of Nodes in circuit: "<<no_of_nodes<<endl;
        // cout<<"Number of nets(Total connections between nodes): "<<no_of_nets<<endl;
        // cout<<"Number of Fixed Nodes: "<<no_of_fixed_nodes<<endl;
        Graph fpga_ckt(no_of_fpga);
        Graph nodes_ckt(no_of_nodes);
        set<int> fixed_node_id;
        vector<vector<vector<int>>> vector_of_fpga; //set of FPGAs with dist<=x {1,2,...,maxdist(FPGA)} (4th line in Algorithm)
        vector<pair<pair<int,int>,vector<int>>> vector_of_nodes; //set of nodes with dist<maxdist(FPGA) (7th line Algorithm)
        priority_queue<pair<int,vector<int>>, vector<pair<int,vector<int>>>, greater<pair<int,vector<int>>> > cddt;

    for(int i=1;i<=no_of_conn_channels;i++) fpga_ckt.addEdge(input[i][0],input[i][1],1);                

    for(int i=no_of_conn_channels+1;i<=no_of_conn_channels+no_of_nets;i++)
        for(int j=1;j<input[i].size();j++) nodes_ckt.addEdge(input[i][0],input[i][j],1);                  
    
    for(int i=no_of_conn_channels+no_of_nets+1;i<input.size();i++)  fixed_nodes.push(make_pair(input[i][0], input[i][1]));    
    
    for(int i=no_of_conn_channels+no_of_nets+1;i<input.size();i++)  fixed_node_id.insert(input[i][0]);

   // formed the set of FPGAs for vector_of_fpga. (4th line in Algorithm)
    for(int fpga=0;fpga<no_of_fpga;fpga++)
    {
        vector<vector<int>> set_of_fpga;
        vector<int> temp=fpga_ckt.shortestPath(fpga);
        int max_dist=temp[temp.size()-1];        // I have added max of dist in the dist vector in shortestPth function.
        temp.pop_back();
        // cout<<"Distance from fpga "<<fpga<<" to other fpgas are given by: "<<endl;
        // for(int i=0;i<temp.size();i++)
        // {
        //     cout<<"distance from "<<fpga<<" FPGA to "<<i<<" FPGA is"<<temp[i]<<endl;
        // }
        for(int x=1;x<=max_dist;x++)
        {
            vector<int> v;
            for(int dest_fpga=0;dest_fpga<temp.size();dest_fpga++)
            {
                if(temp[dest_fpga]<=x)
                {
                    v.push_back(dest_fpga);
                }
            }
            set_of_fpga.push_back(v);
        }
        vector_of_fpga.push_back(set_of_fpga);
    }
   //Just printing above to check at runtime
    for(int fpga=0;fpga<vector_of_fpga.size();fpga++)
    {
        cout<<"Vector of FPGAs from "<<fpga<<endl;
        for(int x=0;x<vector_of_fpga[fpga].size();x++)
        {
            cout<<"At a distance less than equal "<<x+1<<endl;
            for(int dest_fpga=0;dest_fpga<vector_of_fpga[fpga][x].size();dest_fpga++)
            {
                cout<<vector_of_fpga[fpga][x][dest_fpga]<<" ";
            }
            cout<<endl;
        }
    }

    priority_queue<iPair, vector<iPair>, greater<iPair> > temp_fixed_nodes=fixed_nodes; //to iterate through fixed nodes queue;

    // formed the set of nodes for all fixed nodes corresponding to fixed FPGAs for vector_of_nodes. (7th line in Algorithm)
    while(!temp_fixed_nodes.empty())
    {
        vector<int> temp=nodes_ckt.shortestPath(temp_fixed_nodes.top().first);
        int max_dist=vector_of_fpga[temp_fixed_nodes.top().second].size();
        temp.pop_back();    
        vector<int> v;    
        for(int i=0;i<temp.size();i++)
        {            
            if(temp[i]<max_dist)
            {
                v.push_back(i);
            }
        }  
        pair<pair<int,int>,vector<int>> p=make_pair(make_pair(temp_fixed_nodes.top().first,max_dist),v);         
        temp_fixed_nodes.pop();
        vector_of_nodes.push_back(p);
    }
    //just printing above to check at runtime.
    for(int node=0;node<vector_of_nodes.size();node++)
    {
        cout<<"Vector of nodes for node : "<<vector_of_nodes[node].first.first<<" at a distance of less than "<<vector_of_nodes[node].first.second<<" is given by"<<endl;
        for(int j=0;j<vector_of_nodes[node].second.size();j++)
        {
            cout<<vector_of_nodes[node].second[j]<<" ";
        }
        cout<<endl;
    }

    // Forming the cddt - set of FPGAs that a node can be placed into. (8th line in Algorithm)    
    temp_fixed_nodes=fixed_nodes;
    while(!temp_fixed_nodes.empty())
    {
        vector<int> temp;
        temp.push_back(temp_fixed_nodes.top().second);
       cddt.push(make_pair(temp_fixed_nodes.top().first,temp));
        temp_fixed_nodes.pop();        
    }
        
   vector<int> original_vector_of_fpgas;
   for(int i=0;i<no_of_fpga;i++) original_vector_of_fpgas.push_back(i);  
   
   for(int i=0;i<no_of_nodes;i++) 
   {
    if(fixed_node_id.find(i)==fixed_node_id.end())
    cddt.push(make_pair(i,original_vector_of_fpgas));  
   } 

   // just priniting the options of FPGAs available for nodes.
   priority_queue<pair<int,vector<int>>, vector<pair<int,vector<int>>>, greater<pair<int,vector<int>>> > temp_cddt=cddt;
   vector<vector<int>> vector_of_cddt;
    while(!temp_cddt.empty())
    {
        vector<int> temp;        
        cout<<"Node "<<temp_cddt.top().first<<" can be placed in: "<<endl;
        for(int fpga=0;fpga<temp_cddt.top().second.size();fpga++) 
        {
            temp.push_back(temp_cddt.top().second[fpga]);
            cout<<"FPGA "<<temp_cddt.top().second[fpga]<<" ";    
        }
        vector_of_cddt.push_back(temp);    
        cout<<endl;
        temp_cddt.pop();
    }
    
    for(int i=0;i<vector_of_cddt.size();i++)
    {
        cout<<"node id: "<<i<<endl;
        for(int j=0;j<vector_of_cddt[i].size();j++)
        {
            cout<<vector_of_cddt[i][j]<<" ";
        }
        cout<<endl;
    }
    int node=0;
    temp_fixed_nodes=fixed_nodes;
    while(temp_fixed_nodes.size()>0)
    {
        int fix_node=vector_of_nodes[node].first.first;
        cout<<"Fixed node id: "<<fix_node<<endl;
        int d=vector_of_nodes[node].first.second;
        int fix_fpga=temp_fixed_nodes.top().second;
        temp_fixed_nodes.pop();
        for(int j=0;j<vector_of_nodes[node].second.size();j++)
        {
            if(fixed_node_id.find(vector_of_nodes[node].second[j])==fixed_node_id.end())
            {
                cout<<"Yes"<<endl;
                int k=nodes_ckt.shortestPath(fix_node)[vector_of_nodes[node].second[j]];
                cout<<"Distance between is given by: "<<k<<endl;
                cout<<"Size of cddt[j] before intersection is: "<<vector_of_cddt[vector_of_nodes[node].second[j]].size()<<endl;
                cout<<"Size of vector_of_fixed fpga at distance: "<<k<<" is given by"<<vector_of_fpga[fix_node][k-1].size()<<endl;
                vector_of_cddt[vector_of_nodes[node].second[j]]=intersetion_of_vectors(vector_of_fpga[fix_node][k-1],vector_of_cddt[vector_of_nodes[node].second[j]]);
                
                cout<<"Size of cddt[j] after intersection is: "<<vector_of_cddt[vector_of_nodes[node].second[j]].size()<<endl;
                // for(int i=0;i<vector_of_cddt.size();i++)
                //     {
                //         cout<<"node id: "<<i<<endl;
                //         for(int j=0;j<vector_of_cddt[i].size();j++)
                //         {
                //             cout<<vector_of_cddt[i][j]<<" ";
                //         }
                //         cout<<endl;
                //     }
            }
            else cout<<"No movable node"<<endl;
        }
        cout<<endl;
        node++;
    }   
   
   
    return 0;
}