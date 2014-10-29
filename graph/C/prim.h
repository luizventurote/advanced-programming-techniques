// Number of vertices in the graph
#define PRIM_EDGES_QTY 7 
 
 
 /**
 * Init graph
 * @author Luiz Venturote
 * @param  int graph
 */
void PrimMST() {
	
	int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY];
	
	// Init graph
	Prim_initGraph(graph);
   
	// Add adges in graph 1
	Prim_addEdge(graph, 0, 1, 5);
	Prim_addEdge(graph, 0, 2, 3);
	Prim_addEdge(graph, 1, 0, 5);
	Prim_addEdge(graph, 1, 2, 4);
	Prim_addEdge(graph, 1, 3, 1);
	Prim_addEdge(graph, 1, 4, 7);
	Prim_addEdge(graph, 2, 1, 6);
	Prim_addEdge(graph, 2, 3, 5);
	Prim_addEdge(graph, 2, 5, 2);
	Prim_addEdge(graph, 2, 4, 1);
	Prim_addEdge(graph, 3, 4, 9);
	Prim_addEdge(graph, 3, 6, 4);
	Prim_addEdge(graph, 4, 3, 2);
	Prim_addEdge(graph, 4, 5, 5);
	Prim_addEdge(graph, 4, 6, 8);
	Prim_addEdge(graph, 5, 2, 3);
	Prim_addEdge(graph, 5, 4, 7);
	Prim_addEdge(graph, 5, 6, 3);
	Prim_addEdge(graph, 6, 4, 8);
	
	// Print Graph
	Prim_printGraph(graph);
 
    // Print the solution
    Prim(graph);
    
}


/**
 * A utility function to find the vertex with minimum key value, from the set of vertices not yet included in MST
 * @author Luiz Venturote
 * @param  int key[]
 * @param  int mstSet[]
 */
int minKey(int key[], int mstSet[]) {
	
   // Initialize min value
   int min = INT_MAX, min_index;
   
   int v=0;
 
	for (v=0; v<PRIM_EDGES_QTY; v++) {
		
		if (mstSet[v] == 0 && key[v] < min) {
			min = key[v], min_index = v;	
		}
		
	}

   return min_index;
   
}


/**
 * A utility function to print the constructed MST stored in parent[]
 * @author Luiz Venturote
 * @param  int parent[]
 * @param  int n
 * @param  int graph[][]
 */
int printMST(int parent[], int n, int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {

	int i=0;

	printf("Edge   Weight\n");
	
	for (i = 1; i < PRIM_EDGES_QTY; i++) {
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
	}
      
}
 
/**
 * Function to construct and print MST for a graph represented using adjacency matrix representation
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Prim(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {
	
	int parent[PRIM_EDGES_QTY]; 	// Array to store constructed MST
	int key[PRIM_EDGES_QTY];   	// Key values used to pick minimum weight edge in cut
	int mstSet[PRIM_EDGES_QTY];  	// To represent set of vertices not yet included in MST
 
	// Initialize all keys as INFINITE
	int i = 0;
     
	for (i=0; i<PRIM_EDGES_QTY; i++) {
		parent[i] = 0;
		key[i] = INT_MAX;
		mstSet[i] = 0;
	}
	// Always include first 1st vertex in MST.
	key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST 
 
	// The MST will have V vertices
	int count = 0;
	
	for(count=0; count<PRIM_EDGES_QTY-1; count++) {
		
		// Pick thd minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
 
        // Update key value and parent index of the adjacent vertices of the picked vertex. Consider only those vertices which are not yet included in MST
        int v=0;
		for (v=0; v<PRIM_EDGES_QTY; v++) {
			
			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == 0 && graph[u][v]<key[v]) {
				
				parent[v]  = u;
				key[v] = graph[u][v];
			
			}
			
		}
		
     }
 
     // print the constructed MST
     printMST(parent, PRIM_EDGES_QTY, graph);
}


/**
 * Add new adge in the graph
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int src Origin
 * @param  int dest Destination
 * @param  int weight Weight
 */
void Prim_addEdge(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY], int src, int dest, int weight) {
	
	graph[src][dest] = weight;
	graph[dest][src] = weight;
	
}


/**
 * Print graph
 * @author Luiz Venturote
 */
void Prim_printGraph(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {
	
	int edges_qty= PRIM_EDGES_QTY;
	
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


/**
 * Init graph
 * @author Luiz Venturote
 * @param  int graph
 */
void Prim_initGraph(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<PRIM_EDGES_QTY; ++i) {
	
		for(j=0; j<PRIM_EDGES_QTY; ++j) {
			graph[i][j] = 0;	
		}

	}
}
