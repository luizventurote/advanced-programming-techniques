#define KRUSKAL_EDGES_QTY 7

/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 */
void KruskalMST() {
	
	int graph[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY];
	int graph_2[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY];
	
	// Init graph
	Kruskal_initGraph(graph);
	Kruskal_initGraph(graph_2);

	// Add adges
	Kruskal_addEdge(graph, 0, 1, 5);
	Kruskal_addEdge(graph, 0, 2, 3);
	Kruskal_addEdge(graph, 1, 0, 5);
	Kruskal_addEdge(graph, 1, 2, 4);
	Kruskal_addEdge(graph, 1, 3, 1);
	Kruskal_addEdge(graph, 1, 4, 7);
	Kruskal_addEdge(graph, 2, 1, 6);
	Kruskal_addEdge(graph, 2, 3, 5);
	Kruskal_addEdge(graph, 2, 5, 2);
	Kruskal_addEdge(graph, 2, 4, 1);
	Kruskal_addEdge(graph, 3, 4, 9);
	Kruskal_addEdge(graph, 3, 6, 4);
	Kruskal_addEdge(graph, 4, 3, 2);
	Kruskal_addEdge(graph, 4, 5, 5);
	Kruskal_addEdge(graph, 4, 6, 8);
	Kruskal_addEdge(graph, 5, 2, 3);
	Kruskal_addEdge(graph, 5, 4, 7);
	Kruskal_addEdge(graph, 5, 6, 3);
	Kruskal_addEdge(graph, 6, 4, 8);

	// Print main graph
    Kruskal_printGraph(graph); 
    
    // Execute Kruskal's algorithm
    Kruskal(graph);
    
    printf("\n\n -------------------- \n\n");
    
    // Add adges
	Kruskal_addEdge(graph_2, 0, 1, 5);
	Kruskal_addEdge(graph_2, 0, 2, 1);
	Kruskal_addEdge(graph_2, 1, 5, 1);
	Kruskal_addEdge(graph_2, 1, 4, 1);
	Kruskal_addEdge(graph_2, 1, 3, 7);
	Kruskal_addEdge(graph_2, 2, 1, 2);
	Kruskal_addEdge(graph_2, 2, 3, 6);
	Kruskal_addEdge(graph_2, 2, 4, 7);
	Kruskal_addEdge(graph_2, 3, 2, 7);
	Kruskal_addEdge(graph_2, 3, 5, 4);
	Kruskal_addEdge(graph_2, 3, 6, 6);
	Kruskal_addEdge(graph_2, 4, 3, 3);
	Kruskal_addEdge(graph_2, 4, 5, 5);
	Kruskal_addEdge(graph_2, 4, 6, 9);
	Kruskal_addEdge(graph_2, 5, 1, 7);
	Kruskal_addEdge(graph_2, 5, 6, 2);
	
	// Print main graph
    Kruskal_printGraph(graph_2); 
    
    // Execute Kruskal's algorithm
    Kruskal(graph_2);
    
}


/**
 * Init graph
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Kruskal_initGraph(int graph[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<KRUSKAL_EDGES_QTY; i++) {
		
		for(j=0; j<KRUSKAL_EDGES_QTY; j++) {	
			graph[i][j] = 999;	
		}
	}
}


/**
 * Add new adge in the graph
 * @author Luiz Venturote
 * @param  int graph[][]
 * @param  int src Origin
 * @param  int dest Destination
 * @param  int weight Weight
 */
void Kruskal_addEdge(int graph[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY], int src, int dest, int weight) {
	graph[src][dest] = weight;
}
 

/**
 * Kruskal’s algorithm - Root
 * @author Luiz Venturote
 * @param  int 
 * @param  int p[]
 */
int Kruskal_Root(int v,int p[]){
 
    while(p[v] != v) {
		v = p[v];
	}
         
	return v;
	
}


/**
 * Kruskal’s algorithm - Union
 * @author Luiz Venturote
 * @param  int i
 * @param  int j
 * @param  int p[]
 */
void Kruskal_Union(int i,int j,int p[]){
    if(j > i)
        p[j] = i;
    else
        p[i] = j;
}


/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Kruskal(int graph[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY]){
	
	int n = KRUSKAL_EDGES_QTY;
	
    int count=0, i=0, p[100], min=0, j=0, u=0, v=0, k=0, t[100][100], sum=0;
    
    count = k = sum = 0;
    
    for(i=0; i<n; i++) {
        p[i] = i;
    }
    
    while(count < n) {
    	
        min = 999;
        
        for(i=0; i<n; i++) {
        	
            for(j=0; j<n; j++) {
             
                if(graph[i][j] < min) {
                    min = graph[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        
        if(min != 999) {
        	
            i = Kruskal_Root(u, p);
            j = Kruskal_Root(v, p);
            
            if (i != j) {
                t[k][0] = u;
                t[k][1] = v;
                 
                k++;
                 
                sum += min;
                Kruskal_Union(i,j,p);
            }
            
        	graph[u][v] = graph[v][u] = 999;
         
        }
		
		count +=1;
    }
	 
    if(count != n) {
        printf(" Spanning tree not exist\n");
    }
    
    if(count == n) {
    	
        printf(" Adges Spanning tree is: ");
        
        for(k=0; k<n-1; k++) {
            printf(" %d -> %d ",t[k][0],t[k][1]);
        }
        
    printf("\n\n Cost: %d \n\n",sum);
    
    }
    
}


/**
 * Print graph
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Kruskal_printGraph(int graph[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY]) {
	
	int i=0, j=0;
	
	printf("\n");
	
	for(i=0; i<KRUSKAL_EDGES_QTY; ++i) {
		
		// Graph index
		if(i==0) {
			
			for(j=0; j<KRUSKAL_EDGES_QTY; ++j) {
				
				if(j==0)
				printf("   | ");
				
				printf("  %d  ", j);
				
			}
							
			printf("\n");	
			
			for(j=0; j<KRUSKAL_EDGES_QTY; ++j)
				printf("------", j);
				
			printf("\n");	
		}
		
		for(j=0; j<KRUSKAL_EDGES_QTY; ++j) {
			
			
			if(j==0)
				printf(" %d | ", i);
			
			if(graph[i][j] == 0 || graph[i][j] == 999) {
				printf("  -  ");
			} else {
				printf("  %d  ", graph[i][j]);	
			}
			
		}	
		
		printf("\n\n");
		
	}
	
	printf("\n");
	
}
