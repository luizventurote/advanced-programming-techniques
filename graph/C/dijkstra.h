// Number of vertices in the graph
// Número de vértices do grafo
#define DIJKSTRA_EDGES_QTY 7

// Maximum value used in the Dijkstra algorithm
// Valor máximo utilizado no algoritmo de Dijkstra
#define DIJKSTRA_MAX_VALUE 999


/**
 * Dijkstra
 *
 * @author Luiz Venturote
 */
void Dijkstra() {
	
	int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY];
   
	// Init graph
	Dijkstra_initGraph(graph);
	
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
	
	// Print graph
	Dijkstra_printGraph(graph);
	
	// Execute Dijkstra
    DijkstraMST(graph, 0);
    
    printf("\n\n");
    
}


/**
 * A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
 * Função utilizada para encontrar o vértice com distância mínima
 *
 * @author Luiz Venturote
 * @param  int dist[]
 * @param  int sptSet[]
 */
int Dijkstra_minDistance(int dist[], int sptSet[]) {
	
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
 *
 * @author Luiz Venturote
 * @param  int dist[]
 * @param  int n
 */
int Dijkstra_printResult(int dist[]) {

	int i=0;
	
	printf(" Vertex   Distance from Source\n");

	for(i=0; i<DIJKSTRA_EDGES_QTY; i++) {
		printf(" %d \t\t %d\n", i, dist[i]);	
	}
      
}


/**
 * Funtion that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int src Origin point
 */
void DijkstraMST(int graph[DIJKSTRA_EDGES_QTY][DIJKSTRA_EDGES_QTY], int src) {
	
	int i=0, count=0, n=DIJKSTRA_EDGES_QTY, debug_print=0;
	
	// The output array.  dist[i] will hold the shortest - distance from src to i
	int dist[n];    
 
	// markup_table[i] will true if vertex i is included in shortest - path tree or shortest distance from src to i is finalized
	int markup_table[n]; 
 
	// Initialize all distances as INFINITE and stpSet[] as false
	for(i=0; i<n; i++) {
		dist[i]   = DIJKSTRA_MAX_VALUE;
		markup_table[i] = 0;	
	}
        
 	// Distance of source vertex from itself is always 0
	dist[src] = 0;
 	
	// Find shortest path for all vertices
	for(count=0; count<n-1; count++) {
		
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = Dijkstra_minDistance(dist, markup_table);
 
		// Mark the picked vertex as processed
		// Marca o vértice escolhido como processado
		markup_table[u] = 1;
		
		// Update dist value of the adjacent vertices of the picked vertex.
		for(i=0; i<n; i++) {
		
			// Update dist[i] only if is not in markup_table, there is an edge from 
			// u to i, and total weight of path from src to i through u is 
			// smaller than current value of dist[i]
			if(!markup_table[i] && graph[u][i] && dist[u]!=DIJKSTRA_MAX_VALUE && dist[u]+graph[u][i]<dist[i]) {
				
				dist[i] = dist[u] + graph[u][i];
				
				debug_print = 1;
				
			}
			
			printf(" count: %d | u: %d | i: %d | graph[u][i]: %d | markup_table[i]: %d | dist[u]: %d | dist[i]: %d", count, u, i, graph[u][i], markup_table[i], dist[u], dist[i]);
			
			if(debug_print == 1) {
				printf(" | Add");	
				debug_print = 0;
			}	
			
			printf("\n");
        }
        
        printf("\n");
        
     }
 
	// print the constructed distance array
	Dijkstra_printResult(dist);

}


 /**
 * Add new adge in the graph
 * Adiciona uma nova aresta no grafo
 *
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
 * Inicia o grafo
 *
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
 * Exibe o grafo
 *
 * @author Luiz Venturote
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
