// Number of vertices in the graph
// N�mero de v�rtices do grafo
#define PRIM_VERTEX_QTY 5

// Maximum value used in the Prim algorithm
// Valor m�ximo utilizado no algoritmo de Prim
#define PRIM_MAX_VALUE 999
 
 
/**
 * Prim MST
 *
 * @author Luiz Venturote
 */
void PrimMST() {
	
	int graph[PRIM_VERTEX_QTY][PRIM_VERTEX_QTY];
	
	// Init graph
	// Inicializa o grafo
	Prim_initGraph(graph);
   
	// Add adges in graph
	// Adiciona arestas no grafo	
	Prim_addEdge(graph, 0, 1, 2);
	Prim_addEdge(graph, 0, 3, 6);
	Prim_addEdge(graph, 1, 2, 3);
	Prim_addEdge(graph, 1, 3, 8);
	Prim_addEdge(graph, 1, 4, 5);
	Prim_addEdge(graph, 2, 4, 7);
	Prim_addEdge(graph, 3, 4, 9);
	
	// Print graph
	// Exibe o grafo
	Prim_printGraph(graph);
 
    // Print the result
    // Exibe o resultado
    Prim(graph);
    
}


/**
 * A utility function to find the vertex with minimum key value, from the set of vertices not yet included in MST
 * Fun��o utilizada para encontrar o v�rtice com o valor m�nimo que n�o est�o inclu�dos na MST para n�o gerar ciclos
 *
 * @author Luiz Venturote
 * @param  int weight_table[]
 * @param  int markup_table[]
 */
int Prim_minVertexValue(int weight_table[], int markup_table[]) {
	
   int min=PRIM_MAX_VALUE, min_index=0, v=0;
 
	for(v=0; v<PRIM_VERTEX_QTY; v++) {
		
		if(markup_table[v]==0 && weight_table[v]<min) {
			min 	  = weight_table[v];
			min_index = v;	
		}	
	}

   return min_index;
   
}


/**
 * A utility function to print the constructed MST
 * Fun��o utilizada para mostrar na tela a contru��o da MST
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int mst[]
 */
int Prim_printMST(int graph[PRIM_VERTEX_QTY][PRIM_VERTEX_QTY], int mst[]) {

	int i=0;

	printf(" Edge   Weight\n");
	
	for (i=1; i<PRIM_VERTEX_QTY; i++) {
		printf(" %d - %d    %d \n", mst[i], i, graph[i][mst[i]]);
	}   
	
	printf("\n");
}
 
/**
 * Function to construct and print MST for a graph represented using adjacency matrix representation
 * Fun��o para contruir e exibir uma MST de um grafo representado por uma matriz de adjac�ncia
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Prim(int graph[PRIM_VERTEX_QTY][PRIM_VERTEX_QTY]) {
	
	int i=0, n=PRIM_VERTEX_QTY, count=0, u=0, v=0, debug_print=0;
	
	int mst_table[n];
	int weight_table[n];
	int markup_table[n];
 
	// Initialize vectors
	// Inicializa os vetores
	for(i=0; i<n; i++) {
		mst_table[i] 	= 0;		
		markup_table[i] = 0;
		weight_table[i] = PRIM_MAX_VALUE;
	}
	
	// Include first vertex in MST
	// Inclui o primeiro v�rtice na MST
	weight_table[0] = 0;
	mst_table[0] 	= -1;
	
	for(count=0; count<n-1; count++) {
		
		// Pick the minimum key vertex from the set of vertices not yet included in MST
		// Pega os v�rtice de chave min�ma que ainda foram marcados na MST para n�o gerar ciclos
        u = Prim_minVertexValue(weight_table, markup_table);
 
        // Add the picked vertex to the markup table
        // Adiciona o v�rtice escolhido na tabela de marca��o
        markup_table[u] = 1;
 
        // Update edges weight. Consider only those vertices which are not yet included in MST
		// Atualiza os pesos das arestras. Considerando somente os versos que ainda n�o est�o inclu�dos na MST
		for(i=0; i<n; i++) {
				
			if(graph[u][i] && markup_table[i]==0 && graph[u][i]<weight_table[i]) {
				
				mst_table[i] 	= u;
				weight_table[i] = graph[u][i];
				
				debug_print = 1;
			
			} 
			
			printf(" count: %d | u: %d | i: %d | graph[u][i]: %d | mst_table[i]: %d | markup_table[i]: %d | weight_table[i]: %d", count, u, i, graph[u][i], mst_table[i], markup_table[i], weight_table[i]);
			
			if(debug_print == 1) {
				printf(" | Updated");	
				debug_print = 0;
			}	
			
			printf("\n");							
		}
		
		printf("\n");
		
     }
	
	printf(" mst_table[] \n");
	for(i=0; i<n; i++) {
		printf(" [%d]=>%d", i, mst_table[i]);
	}
	printf("\n");
	
	printf("\n markup_table[] \n");
	for(i=0; i<n; i++) {
		printf(" [%d]=>%d", i, markup_table[i]);
	}
	printf("\n");
	
	printf("\n weight_table[] \n");
	for(i=0; i<n; i++) {
		printf(" [%d]=>%d", i, weight_table[i]);
	}
 	printf("\n\n");
 	
     // print the constructed MST
     Prim_printMST(graph, mst_table);
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
void Prim_addEdge(int graph[PRIM_VERTEX_QTY][PRIM_VERTEX_QTY], int src, int dest, int weight) {
	
	graph[src][dest] = weight;
	graph[dest][src] = weight;
	
}


/**
 * Print graph
 * Exibe o grafo
 *
 * @author Luiz Venturote
 */
void Prim_printGraph(int graph[PRIM_VERTEX_QTY][PRIM_VERTEX_QTY]) {
	
	int n=PRIM_VERTEX_QTY, i=0, j=0;
	
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
void Prim_initGraph(int graph[PRIM_VERTEX_QTY][PRIM_VERTEX_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<PRIM_VERTEX_QTY; ++i) {
	
		for(j=0; j<PRIM_VERTEX_QTY; ++j) {
			graph[i][j] = 0;	
		}

	}
}
