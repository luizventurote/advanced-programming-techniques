// Number of vertices in the graph
// Número de vértices do grafo
#define FF_VERTEX_QTY 6

// Maximum value used in the Kruskal algorithm
// Valor máximo utilizado no algoritmo de Kruskal
#define FF_MAX_VALUE 999

// Define the maximum values of the markup table from queue in the BFS algorithm
// Define os valores para gerênciar a tabela de marcação da fila no algoritmo BFS
#define NEUTRAL 0
#define MARKED 1
#define UNMARKED 2

// Variables for the algorithm queue (needed for breadth-first search)
// Variáveis para o algoritmo de fila (Necessário para a busca em largura)
int bfs_markup_table[FF_VERTEX_QTY];  
int beginning_queue=0, end_queue=0;    
int queue[FF_VERTEX_QTY+2];      
int way[FF_VERTEX_QTY];


/**
 * Ford Fulkerson maximum flow
 * @author Luiz Venturote
 */
void FordFulkersonMF() {
	
	int graph[FF_VERTEX_QTY][FF_VERTEX_QTY];
	
	// Init graph
	// Inicializa o grafo
	FF_initGraph(graph);
	
	// Add adges in graph
	// Adiciona arestas no grafo
	FF_addEdge(graph, 0, 1, 16);
	FF_addEdge(graph, 0, 2, 13);
	FF_addEdge(graph, 1, 2, 10);
	FF_addEdge(graph, 1, 3, 12);
	FF_addEdge(graph, 2, 1, 4);
	FF_addEdge(graph, 2, 4, 14);
	FF_addEdge(graph, 3, 2, 9);
	FF_addEdge(graph, 4, 3, 7);
	FF_addEdge(graph, 3, 5, 20);
	FF_addEdge(graph, 4, 5, 4);
	
	// Print graph
	// Exibe o grafo
    FF_printGraph(graph); 
	
    // Print the result
    // Exibe o resultado
    printf(" Maximum flow is: %d \n\n", FordFulkerson(graph, 0, 5));
    
}


/**
 * Init graph
 * Inicia o grafo
 *
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void FF_initGraph(int graph[FF_VERTEX_QTY][FF_VERTEX_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<FF_VERTEX_QTY; i++) {
		for(j=0; j<FF_VERTEX_QTY; j++) {	
		
			// Add maximum value in all edges of the graph
			// Adiciona o valor máximo em todos as arestas do grafo
			graph[i][j] = 0;
		}
	}
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
void FF_addEdge(int graph[FF_VERTEX_QTY][FF_VERTEX_QTY], int src, int dest, int weight) {
	graph[src][dest] = weight;
}


/**
 * Print graph
 * Exibe o grafo
 *
 * @author Luiz Venturote
 */
void FF_printGraph(int graph[FF_VERTEX_QTY][FF_VERTEX_QTY]) {
	
	int i=0, j=0;
	
	printf("\n");
	
	for(i=0; i<FF_VERTEX_QTY; ++i) {
		
		// Graph index
		if(i==0) {
			
			for(j=0; j<FF_VERTEX_QTY; ++j) {
				
				if(j==0)
				printf("   | ");
				
				printf("  %d  ", j);
				
			}
							
			printf("\n");	
			
			for(j=0; j<FF_VERTEX_QTY; ++j)
				printf("------", j);
				
			printf("\n");	
		}
		
		for(j=0; j<FF_VERTEX_QTY; ++j) {
			
			
			if(j==0)
				printf(" %d | ", i);
			
			if(graph[i][j] == 0 || graph[i][j] == FF_MAX_VALUE) {
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
 * Return min value
 * Retorna o menor valor
 *
 * @author Luiz Venturote
 */
int min(int x, int y) {
    return x<y ? x : y;
}


/**
 * Enqueue
 * Enfileirar
 *
 * @author Luiz Venturote
 */
void enqueue(int x) {
    queue[end_queue] = x;
    end_queue++;
    bfs_markup_table[x] = MARKED;
}


/**
 * Dequeue
 * Desenfileirar
 *
 * @author Luiz Venturote
 */
int dequeue() {
    int x = queue[beginning_queue];
    beginning_queue++;
    bfs_markup_table[x] = UNMARKED;
    return x;
}


/**
 * Breadth-First Search algorithm - BFS (https://www.youtube.com/watch?v=QRq6p9s8NVg)
 *
 * @author Luiz Venturote
 * @param  int graph_capacity[][]
 * @param  int flow[][]
 * @param  int start  	Initial vertex
 * @param  int target  	End vertex
 * @return boolean 		If target vertex is UNMARKED return true
 */
int bfs(int graph_capacity[FF_VERTEX_QTY][FF_VERTEX_QTY], int flow[FF_VERTEX_QTY][FF_VERTEX_QTY], int start, int target) {
	
    int i, u,v, n=FF_VERTEX_QTY;
    
    // Initializes the markup table
    // Inicializa a tabela de marcação
    for(i=0; i<n; i++) {
		bfs_markup_table[i] = NEUTRAL;
    }   

	// Adds the first vertex in the equeue
	// Adiciona o primeiro vértice na fila
    enqueue(start);
    
    // The first vertex should have no predecessor
    // O primeiro vértice não deve ter antecessor
    way[start] = -1;
    
    while(beginning_queue!=end_queue) {
    	
    	// Remove a vertex of the equeue
    	// Retira um vértice da fila
		u = dequeue();
		
	    // Search all adjacent NEUTRAL nodes v. If the capacity from u to v in the network is positive, enqueue v.
	    // Procura por todos os vértices adjacentes do vértice v. Se a capacidade de u para v na rede é positiva, enfilere v.
		for(v=0; v<n; v++) {
			
		    if (bfs_markup_table[v]==NEUTRAL && graph_capacity[u][v]-flow[u][v]>0) {
				
				enqueue(v);
				way[v] = u;
				
		    }
		    
		}
    }
    
    // If the markup table of the target node is UNMARKED now, it means that we reached it.
    // Se o vértice alvo estiver como UNMARKED, significa que o algoritmo conseguiu encontra-lo
    return bfs_markup_table[target] == UNMARKED;
}


/**
 * Ford Fulkerson algorithm
 *
 * @author Luiz Venturote
 * @param  int graph_capacity[][]
 * @param  int start  	Initial vertex
 * @param  int target  	End vertex
 */
int FordFulkerson(int graph_capacity[FF_VERTEX_QTY][FF_VERTEX_QTY], int start, int target) {
	
    int i,j,u, max_flow=0, n=FF_VERTEX_QTY, increment=0;
    
    // Flow matrix
    // Matriz de fluxo
    int flow[FF_VERTEX_QTY][FF_VERTEX_QTY];     
    
    // Initialize empty flow
    // Inicializa a matriz de fluxo
    for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
		    flow[i][j] = 0;
		}
    }
    
    // Busca em largura. Enquanto existir um caminho de alcance, incrementa o fluxo ao londo desse caminho
    // BFS breadth first search. While there exists an augmenting path, increment the flow along this path
    while( bfs(graph_capacity, flow, start, target) ) {
    	
		increment = FF_MAX_VALUE;
		
		// Find the shortest path with capacity for flow
		// Encontra o caminho mínimo com capacidade para o fluxo
		for(u=n-1; way[u]>=0; u=way[u]) {
		    increment = min(increment, graph_capacity[way[u]][u]-flow[way[u]][u]);
		}
	    
		// Increment the flow
		// Incrementa o fluxo
		for(u=n-1; way[u]>=0; u=way[u]) {
		    flow[way[u]][u] += increment;
		    flow[u][way[u]] -= increment;
		}
		
		// Increment thw maximum flow
		// Incrementa o fluxo máximo
		max_flow += increment;
		
    }
    
    // When no path is free, the algorithm returns the result of the maximum flow 
    // Quando nenhum caminho estiver livre, o algoritmo retorna o resultado do fluxo máximo
    return max_flow;
}
