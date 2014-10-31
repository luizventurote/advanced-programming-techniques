#define KRUSKAL_VERTEX_QTY 7
#define KRUSKAL_MAX_VALUE 999

/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 */
void KruskalMST() {
	
	int graph[KRUSKAL_VERTEX_QTY][KRUSKAL_VERTEX_QTY];
	int graph_2[KRUSKAL_VERTEX_QTY][KRUSKAL_VERTEX_QTY];
	
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
void Kruskal_initGraph(int graph[KRUSKAL_VERTEX_QTY][KRUSKAL_VERTEX_QTY]) {
	
	int i=0, j=0;
	
	for(i=0; i<KRUSKAL_VERTEX_QTY; i++) {
		
		for(j=0; j<KRUSKAL_VERTEX_QTY; j++) {	
			graph[i][j] = KRUSKAL_MAX_VALUE;	
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
void Kruskal_addEdge(int graph[KRUSKAL_VERTEX_QTY][KRUSKAL_VERTEX_QTY], int src, int dest, int weight) {
	graph[src][dest] = weight;
}
 

/**
 * Kruskal’s algorithm - Root
 * @author Luiz Venturote
 * @param  int v
 * @param  int p[]
 */
int Kruskal_Root(int v, int markup_table[]) {
  	
    while(markup_table[v] != v) {
		v = markup_table[v];
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
void Kruskal_Union(int i, int j, int p[]) {
    
	if(j>i) {
		p[j] = i;	
	} else {
		p[i] = j;
	}
        
}


/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Kruskal(int graph[KRUSKAL_VERTEX_QTY][KRUSKAL_VERTEX_QTY]) {
	
	int n = KRUSKAL_VERTEX_QTY;
	
    int count=0, i=0, markup_table[100], min=0, j=0, line=0, column=0, k=0, mst_table[100][100], sum=0;
    
    // Initialize markuop table
    for(i=0; i<n; i++) {
        markup_table[i] = i;
    }
    
    while(count<n) {
    	
        min = KRUSKAL_MAX_VALUE;
        
        // Gets the smallest value of the graph
        for(i=0; i<n; i++) {
        	
            for(j=0; j<n; j++) {
             
                if(graph[i][j] < min) {
                    min = graph[i][j];
                    line = i;
                    column = j;
                }
            }
        }
                
        if(min!=KRUSKAL_MAX_VALUE) {
        	
        	// Checks if vertex has been marked to not generate cycles
            i = Kruskal_Root(line, markup_table);
            j = Kruskal_Root(column, markup_table);
            
            // Checks if it is not equal, to not cause cycles
            if(i!=j) {
            	
            	// Add the edge in to markup table
                mst_table[k][0] = line;
                mst_table[k][1] = column;
                 
                k++;
                 
                sum += min; // Add the cost of the way
                
                Kruskal_Union(i, j, markup_table);
            }
            
        	graph[line][column] = graph[column][line] = KRUSKAL_MAX_VALUE; // Reset vertex value
         
        }
        
		count ++;
		
    }
	 
    if(count!=n) {
        printf(" Spanning tree not exist\n");
    }
    
    if(count==n) {
    	
        printf(" Adges Spanning tree is: ");
        
        for(k=0; k<n-1; k++) {
            printf(" %d->%d |", mst_table[k][0], mst_table[k][1]);
        }
        
    	printf("\n\n Cost: %d \n\n", sum);
    
    }
    
}


/**
 * Print graph
 * @author Luiz Venturote
 * @param  int graph[][]
 */
void Kruskal_printGraph(int graph[KRUSKAL_VERTEX_QTY][KRUSKAL_VERTEX_QTY]) {
	
	int i=0, j=0;
	
	printf("\n");
	
	for(i=0; i<KRUSKAL_VERTEX_QTY; ++i) {
		
		// Graph index
		if(i==0) {
			
			for(j=0; j<KRUSKAL_VERTEX_QTY; ++j) {
				
				if(j==0)
				printf("   | ");
				
				printf("  %d  ", j);
				
			}
							
			printf("\n");	
			
			for(j=0; j<KRUSKAL_VERTEX_QTY; ++j)
				printf("------", j);
				
			printf("\n");	
		}
		
		for(j=0; j<KRUSKAL_VERTEX_QTY; ++j) {
			
			
			if(j==0)
				printf(" %d | ", i);
			
			if(graph[i][j] == 0 || graph[i][j] == KRUSKAL_MAX_VALUE) {
				printf("  -  ");
			} else {
				printf("  %d  ", graph[i][j]);	
			}
			
		}	
		
		printf("\n\n");
		
	}
	
	printf("\n");
	
}
