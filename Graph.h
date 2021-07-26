/* Copyright (C) 2020 Marco B. Shafer. All rights reserved.*/

#include <unordered_set> 
#include <vector>

enum State {
	UNVISITED,
	VISITED,
	VISITING
};

class Node {
	friend class Graph;
    
        public:
		Node(int d)
		{
			data = d;
			state = UNVISITED;
		}
		void setState(State s){
			state = s;
		}
		State getState() const{
			return state;
		}
	
	private:
		int data;
		State state;
		std::unordered_set<Node*> children;
};
  
class Graph { 
  
    // Adjacency list
    std::unordered_set<Node*> nodes;
   
    //directed or undirected graph
    bool isDirected;
    
    //util function to get the adj nodes to input node
    std::vector<Node*> getAdjNodes(Node*) const;
    
    //util function to detect cycles in directed graph
    bool thereIsCycle(Node*, std::unordered_set<Node*> &, std::unordered_set<Node*> &) const;
    
    //util function to detect cycles in undirected graph
    bool thereIsCycle(Node*, std::unordered_set<Node*> &, Node* = NULL) const;
    
    //set the state of each node of the graph to UNVISITED
    void resetStates(){
    	for(auto &x : nodes)
    		x->setState(UNVISITED);
	}
  
public: 
    // To create the initial adjacency list 
    Graph(bool); 
  
    // Function to insert a new edge 
    void addEdge(Node*, Node*); 
  
    // Function to display the DFS traversal 
    void DFS(Node*) const; 
    
    // Function to display the BFS traversal 
    void BFS(Node*); 
    
    //Function to find a path between two nodes
    bool findPath(Node*, Node*); 
    
    //Function that detects the presence of a cycle in the graph
    bool thereIsCycle() const;
}; 
