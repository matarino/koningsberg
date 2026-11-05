// C++ program to print Eulerian circuit in given
// directed graph using Hierholzer algorithm
// https://www.geeksforgeeks.org/dsa/hierholzers-algorithm-directed-graph/

#include <bits/stdc++.h>
using namespace std;

// Function to print Eulerian circuit
vector<int> printCircuit(vector<vector<int>> &adj) {
    int n = adj.size();
    
    if (n == 0)
        return {};
    
    // Maintain a stack to keep vertices
    // We can start from any vertex, here we start with 0
    vector<int> currPath;
    currPath.push_back(0);
    
    // list to store final circuit
    vector<int> circuit;
    
    while (currPath.size() > 0) {
        int currNode = currPath[currPath.size() - 1];
        
        // If there's remaining edge in adjacency list
        // of the current vertex
        if (adj[currNode].size() > 0) {
            
            // Find and remove the next vertex that is
            // adjacent to the current vertex
            int nextNode = adj[currNode].back();
            adj[currNode].pop_back();
            
            // Push the new vertex to the stack
            currPath.push_back(nextNode);
        }
        
        // back-track to find remaining circuit
        else {
            // Remove the current vertex and
            // put it in the circuit
            circuit.push_back(currPath.back());
            currPath.pop_back();
        }
    }
    
    // reverse the result vector
    reverse(circuit.begin(), circuit.end());
    
    return circuit;
}

int main() {
    vector<vector<int>> adj = {{2, 3}, {0}, {1}, {4}, {0}};
    vector<int> ans = printCircuit(adj);
    
    for (auto v: ans) cout << v << " ";
    cout << endl;
    return 0;
}
