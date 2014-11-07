// Number of vertices in the graph
// Número de vértices do grafo
#define FF_VERTEX_QTY 6

// Maximum value used in the Kruskal algorithm
// Valor máximo utilizado no algoritmo de Kruskal
#define FF_MAX_VALUE 999

#define WHITE 0
#define GRAY 1
#define BLACK 2

int capacity[FF_VERTEX_QTY][FF_VERTEX_QTY]; // capacity matrix
int color[FF_VERTEX_QTY]; // needed for breadth-first search               
int pred[FF_VERTEX_QTY];  // array to store augmenting path
int head,tail;
int q[FF_VERTEX_QTY+2];


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
    printf(" %d \n\n", FordFulkerson(graph, 0, 5));
    
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
			graph[i][j] = FF_MAX_VALUE;
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
	capacity[src][dest] = weight;
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

void enqueue(int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}


int bfs(int flow[FF_VERTEX_QTY][FF_VERTEX_QTY], int start, int target) {
	
    int u,v, n=FF_VERTEX_QTY;
    
    for (u=0; u<n; u++) {
		color[u] = WHITE;
    }   
    
    head = tail = 0;
    
    enqueue(start);
    
    pred[start] = -1;
    
    while (head!=tail) {
    	
		u = dequeue();
		
	    // Search all adjacent white nodes v. If the capacity
	    // from u to v in the residual network is positive,
	    // enqueue v.
		for (v=0; v<n; v++) {
		    if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0) {
				enqueue(v);
				pred[v] = u;
		    }
		}
		
    }
    
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}


/**
 * Ford Fulkerson algorithm
 * @author Luiz Venturote
 */
int FordFulkerson(int graph[FF_VERTEX_QTY][FF_VERTEX_QTY], int source, int sink) {
	
    int i,j,u, max_flow=0, n=FF_VERTEX_QTY, increment=0;
    
    // flow matrix
    int flow[FF_VERTEX_QTY][FF_VERTEX_QTY];     
    
    // Initialize empty flow
    for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
		    flow[i][j] = 0;
		}
    }
    
    // While there exists an augmenting path, increment the flow along this path
    while( bfs(flow, source, sink) ) {
    	
        // Determine the amount by which we can increment the flow.
		increment = FF_MAX_VALUE;
		
		for (u=n-1; pred[u]>=0; u=pred[u]) {
			
		    increment = min(increment, capacity[pred[u]][u]-flow[pred[u]][u]);
		    
		}
	    
		// Now increment the flow.
		for(u=n-1; pred[u]>=0; u=pred[u]) {
			
		    flow[pred[u]][u] += increment;
		    flow[u][pred[u]] -= increment;
		    
		}
		
		max_flow += increment;
		
    }
    
    // No augmenting path anymore. We are done.
    return max_flow;
    
}


