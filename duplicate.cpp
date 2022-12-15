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