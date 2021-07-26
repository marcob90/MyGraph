/* Copyright (C) 2020 Marco B. Shafer. All rights reserved.*/

#include <iostream>
#include "Graph.h"

bool thereIsRoute(Graph &g, Node &s, Node &e)
{
	return g.findPath(&s, &e);
}

// Driver code 
int main() 
{ 
	Node n0(0);
	Node n1(1);
	Node n2(2);
	Node n3(3);
	Node n4(4);
	Node n5(5);
	
        // Create the graph 
        Graph G(false); 
        G.addEdge(&n0, &n1); 
        G.addEdge(&n0, &n5); 
        G.addEdge(&n5, &n4); 
        G.addEdge(&n2, &n0); 
        G.addEdge(&n2, &n1); 
        G.addEdge(&n1, &n3); 
  
        // Perform DFS 
        G.BFS(&n0); 
	std::cout << std::endl;
        G.DFS(&n0);
        std::cout << std::endl;
    
        std::cout << thereIsRoute(G, n0, n2);
        std::cout << std::endl;
    
        // cout << G.thereIsCycle();
} 
