// Number of vertices in the graph
#define DIJKSTRA_EDGES_QTY 7
#define DIJKSTRA_MAX_VALUE 999


/**
 * Dijkstra
 * @author Luiz Venturote
 */
void Dijkstra() {
	
	int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY];
	int graph_2[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY];
   
	// Init graph
	Dijkstra_initGraph(graph);
	Dijkstra_initGraph(graph_2);
	
	// Add adges in graph 1
    Dijkstra_addEdge(graph, 0, 1, 5);
	Dijkstra_addEdge(graph, 0, 2, 3);
    Dijkstra_addEdge(graph, 1, 0, 5);
    Dijkstra_addEdge(graph, 1, 2, 4);
    Dijkstra_addEdge(graph, 1, 3, 1);
    Dijkstra_addEdge(graph, 1, 4, 7);
    Dijkstra_addEdge(graph, 2, 1, 6);
    Dijkstra_addEdge(graph, 2, 3, 5);
    Dijkstra_addEdge(graph, 2, 5, 2);
    Dijkstra_addEdge(graph, 2, 4, 1);
    Dijkstra_addEdge(graph, 3, 4, 9);
    Dijkstra_addEdge(graph, 3, 6, 4);
    Dijkstra_addEdge(graph, 4, 3, 2);
    Dijkstra_addEdge(graph, 4, 5, 5);
    Dijkstra_addEdge(graph, 4, 6, 8);
    Dijkstra_addEdge(graph, 5, 2, 3);
    Dijkstra_addEdge(graph, 5, 4, 7);
    Dijkstra_addEdge(graph, 5, 6, 3);
    Dijkstra_addEdge(graph, 6, 4, 8);
    
    // Add adges in graph 2
    Dijkstra_addEdge(graph_2, 0, 1, 5);
	Dijkstra_addEdge(graph_2, 0, 2, 1);
	Dijkstra_addEdge(graph_2, 1, 3, 7);
	Dijkstra_addEdge(graph_2, 1, 4, 1);
	Dijkstra_addEdge(graph_2, 1, 5, 5);
	Dijkstra_addEdge(graph_2, 2, 1, 2);
	Dijkstra_addEdge(graph_2, 2, 3, 6);
	Dijkstra_addEdge(graph_2, 2, 4, 7);
	Dijkstra_addEdge(graph_2, 3, 2, 7);
	Dijkstra_addEdge(graph_2, 3, 5, 4);
	Dijkstra_addEdge(graph_2, 3, 6, 6);
	Dijkstra_addEdge(graph_2, 4, 3, 3);
	Dijkstra_addEdge(graph_2, 4, 5, 5);
	Dijkstra_addEdge(graph_2, 4, 6, 9);
	Dijkstra_addEdge(graph_2, 5, 1, 7);
	Dijkstra_addEdge(graph_2, 5, 6, 2);
	
	// Print graph
	Dijkstra_printGraph(graph);
	
	// Execute Dijkstra
    DijkstraMST(graph, 0);
    
    printf("\n\n\n\n\n");
    
    // Print graph
	Dijkstra_printGraph(graph_2);
	
	// Execute Dijkstra
    DijkstraMST(graph_2, 0);
    
    printf("\n\n");
    
}


/**
 * A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
 * @author Luiz Venturote
 * @param  int dist[]
 * @param  int sptSet[]
 */
int minDistance(int dist[], int sptSet[]) {
	
	// Initialize min value
	int min=DIJKSTRA_MAX_VALUE, min_index=0, v=0;

	for(v=0; v<DIJKSTRA_EDGES_QTY; v++) {
		if(sptSet[v]==0 && dist[v]<=min) {
			min = dist[v];
			min_index = v;	
		}
	}
     
   return min_index;
   
}


/**
 * A utility function to print the constructed distance array
 * @author Luiz Venturote
 * @param  int dist[]
 * @param  int n
 */
int printSolution(int dist[], int n) {

	int i=0;
	
	printf(" Vertex   Distance from Source\n");

	for(i=0; i<DIJKSTRA_EDGES_QTY; i++) {
		printf(" %d \t\t %d\n", i, dist[i]);	
	}
      
}


/**
 * Funtion that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int src
 */
void DijkstraMST(int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY], int src) {
	
	// Indexes
	int i=0, count=0, v=0, n=DIJKSTRA_EDGES_QTY;
	
	// The output array.  dist[i] will hold the shortest - distance from src to i
	int dist[n];    
 
	// sptSet[i] will true if vertex i is included in shortest - path tree or shortest distance from src to i is finalized
	int sptSet[n]; 
 
     // Initialize all distances as INFINITE and stpSet[] as false
	for(i=0; i<n; i++) {
		dist[i]   = DIJKSTRA_MAX_VALUE;
		sptSet[i] = 0;	
	}
        
 	// Distance of source vertex from itself is always 0
	dist[src] = 0;
 	
	// Find shortest path for all vertices
	for(count=0; count<n-1; count++) {
		
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet);
 
		// Mark the picked vertex as processed
		sptSet[u] = 1;
		
		// Update dist value of the adjacent vertices of the picked vertex.
		for(v=0; v<n; v++) {
		
			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if(!sptSet[v] && graph[u][v] && dist[u] != DIJKSTRA_MAX_VALUE && dist[u]+graph[u][v] < dist[v]) {
				dist[v] = dist[u] + graph[u][v];
			}
        }
     }
 
	// print the constructed distance array
	printSolution(dist, n);

}

/**
 * Add new adge in the graph
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int src Origin
 * @param  int dest Destination
 * @param  int weight Weight
 */
void Dijkstra_addEdge(int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY], int src, int dest, int weight) {
	
	graph[src][dest] = weight;
	
}


/**
 * Init graph
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Dijkstra_initGraph(int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<DIJKSTRA_EDGES_QTY; ++i) {
	
		for(j=0; j<DIJKSTRA_EDGES_QTY; ++j) {
			graph[i][j] = 0;	
		}

	}
}

/**
 * Print graph
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Dijkstra_printGraph(int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY]) {
	
	int edges_qty = DIJKSTRA_EDGES_QTY;
	
	int i=0, j=0;
	
	printf("\n");
	
	for(i=0; i<edges_qty; ++i) {
		
		// Graph index
		if(i==0) {
			
			for(j=0; j<edges_qty; ++j) {
				
				if(j==0)
				printf("   | ");
				
				printf("  %d  ", j);
				
			}
							
			printf("\n");	
			
			for(j=0; j<edges_qty; ++j)
				printf("------", j);
				
			printf("\n");	
		}
		
		for(j=0; j<edges_qty; ++j) {
			
			
			if(j==0)
				printf(" %d | ", i);
			
			if(graph[i][j] == 0) {
				printf("  -  ");
			} else {
				printf("  %d  ", graph[i][j]);	
			}
			
		}	
		
		printf("\n\n");
		
	}
	
	printf("\n");
	
}
