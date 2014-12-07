// Number of vertices in the graph
// Número de vértices do grafo
#define DIJKSTRA_VERTEX_QTY 6

// Maximum value used in the Dijkstra algorithm
// Valor máximo utilizado no algoritmo de Dijkstra
#define DIJKSTRA_MAX_VALUE 999


/**
 * Dijkstra
 *
 * @author Luiz Venturote
 */
void Dijkstra() {
	
	int graph[DIJKSTRA_VERTEX_QTY][DIJKSTRA_VERTEX_QTY];
   
	// Init graph
	Dijkstra_initGraph(graph);
	
	// Add adges in graph 1
    Dijkstra_addEdge(graph, 0, 1, 2);
    Dijkstra_addEdge(graph, 0, 2, 4);
    Dijkstra_addEdge(graph, 1, 2, 1);
    Dijkstra_addEdge(graph, 1, 3, 4);
    Dijkstra_addEdge(graph, 1, 4, 2);
    Dijkstra_addEdge(graph, 2, 3, 3);
    Dijkstra_addEdge(graph, 3, 5, 2);
    Dijkstra_addEdge(graph, 4, 3, 3);
    Dijkstra_addEdge(graph, 4, 5, 2);
	
	// Print graph
	Dijkstra_printGraph(graph);
	
	// Execute Dijkstra
    DijkstraMST(graph, 0);
    
    printf("\n\n");
    
}


/**
 * Function to find the vertex with minimum distance value
 * Função utilizada para encontrar o vértice com distância mínima
 *
 * @author Luiz Venturote
 * @param  int dist_table[]
 * @param  int markup_table[]
 */
int Dijkstra_minDistance(int dist_table[], int markup_table[]) {
	
	int min=DIJKSTRA_MAX_VALUE, min_index=0, v=0;

	for(v=0; v<DIJKSTRA_VERTEX_QTY; v++) {
		if(markup_table[v]==0 && dist_table[v]<=min) {
			min = dist_table[v];
			min_index = v;	
		}
	}
     
   return min_index;
   
}


/**
 * Function to print the constructed distance array
 * Função que exibe a construção da distância do vetor
 *
 * @author Luiz Venturote
 * @param  int dist[]
 * @param  int n
 */
int Dijkstra_printResult(int dist_table[]) {

	int i=0;
	
	printf(" Vertex   Distance from Source\n");

	for(i=0; i<DIJKSTRA_VERTEX_QTY; i++) {
		printf(" %d \t\t %d\n", i, dist_table[i]);	
	}
      
}


/**
 * Funtion that implements Dijkstra algorithm
 * Função que implementa o algoritmo de Dijkstra
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int src Origin point
 */
void DijkstraMST(int graph[DIJKSTRA_VERTEX_QTY][DIJKSTRA_VERTEX_QTY], int src) {
	
	int i=0, count=0, n=DIJKSTRA_VERTEX_QTY, debug_print=0, u=0;
	
	int dist_table[n];    
	int markup_table[n]; 
 
	// Initialize vectors
	// Inicializa os vetores
	for(i=0; i<n; i++) {
		dist_table[i]   = DIJKSTRA_MAX_VALUE;
		markup_table[i] = 0;	
	}
        
 	// Distance of source vertex from itself is always 0
 	// Distância do vértice de origem sempre vai ser 0
	dist_table[src] = 0;
 	
	for(count=0; count<n-1; count++) {
		
		u = Dijkstra_minDistance(dist_table, markup_table);
 
		// Mark the picked vertex as processed
		// Marca o vértice escolhido como processado
		markup_table[u] = 1;
		
		// Update dist value of the adjacent vertices
		// Atualiza as distâncias dos vértices adjacentes
		for(i=0; i<n; i++) {
		
			if(!markup_table[i] && graph[u][i] && dist_table[u]!=DIJKSTRA_MAX_VALUE && dist_table[u]+graph[u][i]<dist_table[i]) {
				
				dist_table[i] = dist_table[u] + graph[u][i];
				
				debug_print = 1;
				
			}
			
			printf(" count: %d | u: %d | i: %d | graph[u][i]: %d | markup_table[i]: %d | dist_table[u]: %d | dist_table[i]: %d", count, u, i, graph[u][i], markup_table[i], dist_table[u], dist_table[i]);
			
			if(debug_print == 1) {
				printf(" | Updated");	
				debug_print = 0;
			}	
			
			printf("\n");
        }
        
        printf("\n");
        
    }
 
 	printf(" markup_table[] \n");
	for(i=0; i<n; i++) {
		printf(" [%d]=>%d", i, markup_table[i]);
	}
	printf("\n");
	
	printf("\n dist_table[] \n");
	for(i=0; i<n; i++) {
		printf(" [%d]=>%d", i, dist_table[i]);
	}
	printf("\n");
 	printf("\n\n");
 
	// Print the constructed distance array
	// Exibe o vetor de distâncias
	Dijkstra_printResult(dist_table);

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
void Dijkstra_addEdge(int graph[DIJKSTRA_VERTEX_QTY][DIJKSTRA_VERTEX_QTY], int src, int dest, int weight) {
	graph[src][dest] = weight;
}


/**
 * Init graph
 * Inicia o grafo
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Dijkstra_initGraph(int graph[DIJKSTRA_VERTEX_QTY][DIJKSTRA_VERTEX_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<DIJKSTRA_VERTEX_QTY; ++i) {
	
		for(j=0; j<DIJKSTRA_VERTEX_QTY; ++j) {
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
void Dijkstra_printGraph(int graph[DIJKSTRA_VERTEX_QTY][DIJKSTRA_VERTEX_QTY]) {
	
	int edges_qty = DIJKSTRA_VERTEX_QTY;
	
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
