// Number of vertices in the graph
// Número de vértices do grafo
#define PRIM_EDGES_QTY 7 

// Maximum value used in the Prim algorithm
// Valor máximo utilizado no algoritmo de Prim
#define PRIM_MAX_VALUE 999
 
 
/**
 * Prim MST
 *
 * @author Luiz Venturote
 */
void PrimMST() {
	
	int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY];
	
	// Init graph
	// Inicializa o grafo
	Prim_initGraph(graph);
   
	// Add adges in graph
	// Adiciona arestas no grafo
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
	
	// Print graph
	// Exibe o grafo
	Prim_printGraph(graph);
 
    // Print the result
    // Exibe o resultado
    Prim(graph);
    
}


/**
 * A utility function to find the vertex with minimum key value, from the set of vertices not yet included in MST
 * Função utilizada para encontrar o vértice com o valor mínimo que não estão incluídos na MST 
 *
 * @author Luiz Venturote
 * @param  int key[]
 * @param  int mstSet[]
 */
int Prim_minKey(int key[], int mstSet[]) {
	
   int min=PRIM_MAX_VALUE, min_index=0, v=0;
 
	for(v=0; v<PRIM_EDGES_QTY; v++) {
		
		if (mstSet[v]==0 && key[v]<min) {
			min 	  = key[v];
			min_index = v;	
		}	
	}

   return min_index;
   
}


/**
 * A utility function to print the constructed MST stored in parent[]
 * Função utilizada para mostrar na tela a contrução da MST amazenada no parent[]
 *
 * @author Luiz Venturote
 * @param  int parent[]
 * @param  int n
 * @param  int graph[][]
 */
int Prim_printMST(int parent[], int n, int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {

	int i=0;

	printf("Edge   Weight\n");
	
	for (i=1; i<PRIM_EDGES_QTY; i++) {
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
	}   
}
 
/**
 * Function to construct and print MST for a graph represented using adjacency matrix representation
 * Função para contruir e exibir uma MST de um grafo representado por uma matriz de adjacência
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Prim(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {
	
	int i=0, n=PRIM_EDGES_QTY, count = 0, u=0, v=0;
	
	int parent[n]; 	// Array to store constructed MST
	int key[n];   	// Key values used to pick minimum weight edge in cut
	int mstSet[n];  // To represent set of vertices not yet included in MST
 
	// Initialize all keys as INFINITE
	for (i=0; i<n; i++) {
		parent[i] = 0;		
		mstSet[i] = 0;
		key[i] 	  = PRIM_MAX_VALUE;
	}
	
	// Include first vertex in MST
	key[0] 	  = 0;
	parent[0] = -1;
	
	for(count=0; count<n-1; count++) {
		
		// Pick the minimum key vertex from the set of vertices not yet included in MST
        u = Prim_minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
 
        // Update key value and parent index of the adjacent vertices of the picked vertex. Consider only those vertices which are not yet included in MST
		for(v=0; v<n; v++) {
			
			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if(graph[u][v] && mstSet[v]==0 && graph[u][v]<key[v]) {
				
				parent[v] = u;
				key[v] 	  = graph[u][v];
			
			}
		}
     }
 
     // print the constructed MST
     Prim_printMST(parent, n, graph);
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
void Prim_addEdge(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY], int src, int dest, int weight) {
	
	graph[src][dest] = weight;
	graph[dest][src] = weight;
	
}


/**
 * Print graph
 * Exibe o grafo
 *
 * @author Luiz Venturote
 */
void Prim_printGraph(int graph[PRIM_EDGES_QTY][PRIM_EDGES_QTY]) {
	
	int n=PRIM_EDGES_QTY, i=0, j=0;
	
	printf("\n");
	
	for(i=0; i<n; ++i) {
		
		// Graph index
		if(i==0) {
			
			for(j=0; j<n; ++j) {
				
				if(j==0)
				printf("   | ");
				
				printf("  %d  ", j);
				
			}
							
			printf("\n");	
			
			for(j=0; j<n; ++j)
				printf("------", j);
				
			printf("\n");	
		}
		
		for(j=0; j<n; ++j) {
			
			
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
 * Inicia o grafo
 *
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
