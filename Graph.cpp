/* Copyright (C) 2020 Marco B. Shafer. All rights reserved.*/


#include "Graph.h"

// Function to fill the empty adjacency matrix 
Graph::Graph(bool d) :
isDirected(d)
{ 

} 

vector<Node*> Graph::getAdjNodes(Node *start) const
{
	vector<Node*> adjNodes;

	for(auto &x : ( *(nodes.find(start) ) )->children)
		adjNodes.push_back(x);
	
	return adjNodes;
}
  
// Function to add an edge to the graph 
void Graph::addEdge(Node *start, Node *end) 
{ 
	//insert start node and end child
    ( *(nodes.insert(start).first) )->children.insert(end);
    
    if(isDirected)
    	nodes.insert(end);
    else
    	( *(nodes.insert(end).first) )->children.insert(start);
} 
  
// Function to perform DFS on the graph 
void Graph::DFS(Node *start) const
{ 
    static unordered_set<Node*> visited;
    // Print the current node 
    cout << start->data << " "; 
  
    // Set current node as visited 
    visited.insert(start);
  
    // For every node of the graph 
    for (auto &n : getAdjNodes(start)) { 
		
        // If some node is adjacent to the current node 
        // and it has not already been visited 
        if(visited.find(n) == visited.end()) { 
            DFS(n); 
        } 
    } 
} 

void Graph::BFS(Node *start)
{ 
	queue<Node*> q;
	resetStates();

    start->setState(VISITING);
	q.push(start);
  	
	while(!q.empty()){
		Node *vis = q.front();
		cout << vis->data << " ";
		
		q.pop();
		
		for (auto &n : getAdjNodes(vis)) { 
		
	        // If some node is adjacent to the current node 
	        // and it has not already been visited 
        	if(n->getState() == UNVISITED) { 
				q.push(n);
				n->setState(VISITING);
			}
		}
		vis->setState(VISITED);
	}
}

//implement BFS search
bool Graph::findPath(Node *start, Node *end)
{ 
	
	if(start == end) return true;
	
	resetStates();
	queue<Node*> q;

        start->setState(VISITING);
	q.push(start);
  	
	while(!q.empty()){
		Node *node = q.front();	
		q.pop();
		
		for (auto &n : getAdjNodes(node)) { 
		
	        // If some node is adjacent to the current node 
	        // and it is unvisited
        	if(n->getState() == UNVISITED) {
				if(n == end) return true; 
				q.push(n);
				n->setState(VISITING);
			}
		}
		node->setState(VISITED);	
	}
	
	return false;
}

bool Graph::thereIsCycle() const
{
	unordered_set<Node*> visited;
	unordered_set<Node*> s;
	
	for(auto &node : nodes){
		if(isDirected ? thereIsCycle(node, visited, s) : thereIsCycle(node, visited))
				return true;
	}
	
	return false;
}

//util function to detect cycles in directed graph
bool Graph::thereIsCycle(Node *start, unordered_set<Node*> &visited, unordered_set<Node*> &s) const
{
	//if node is already visited
	if(visited.find(start) != visited.end())
		return false;
	
	//add in stack
	s.insert(start);
	visited.insert(start);
	
	//for every adjacent node
	for(auto &n : getAdjNodes(start)){
		//if node is present in stack
		if(s.find(n) != s.end())
			return true;
		//else if there's cycle from node
		else if(thereIsCycle(n, visited, s))
			return true;
	}
	
	//if code reaches this point, the DFS didn't find any cycle for that start node
	//erase it from stack
	s.erase(start);
	return false; 
}

//util function to detect cycles in undirected graph
bool Graph::thereIsCycle(Node *start, unordered_set<Node*> &visited, Node* parent) const
{
	//if node is already visited
	if(visited.find(start) != visited.end())
		return false;

	//visit node
	visited.insert(start);
	
	//for every adjacent node
	for(auto &n : getAdjNodes(start)){
		//if node is already visited and it's not parent node
		if(visited.find(n) != visited.end() && n != parent)
			return true;
		//else if there's cycle from node
		else if(thereIsCycle(n, visited, start))
			return true;
	}	
	
	//if code reaches this point, the DFS didn't find any cycle for that start node
	return false; 
}
