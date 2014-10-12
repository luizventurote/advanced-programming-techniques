#define MAX 20

// Structure to represent a edge in graph
typedef struct edge {
    int src;
    int dest;
    int weight;
} Edge;

// Structure to represent a edge list
typedef struct edgelist {
    Edge data[MAX];
    int n;
} EdgeList;

// Main edge list
EdgeList elist;

// Main graph
int Graph[MAX][MAX],n;

// Minimum spanning tree
EdgeList mst;

/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 */
void KruskalMST() {
	
	// Indexes
    int i,j;
    
    // Amount of vertices
    n = 8;

	// Add adges
	addEdge(0, 1, 3);
	addEdge(0, 2, 1);
	addEdge(1, 2, 7);
	addEdge(1, 3, 2);
	addEdge(1, 4, 6);
	addEdge(2, 6, 3);
	addEdge(2, 7, 2);
	addEdge(3, 5, 7);
	addEdge(3, 6, 5);
	addEdge(4, 5, 2);
	addEdge(5, 6, 1);
	addEdge(6, 7, 9);

	// Print main graph
    printGraph(); 
    
    // Execute Kruskal's algorithm
    Kruskal();
    
    // Print Results
    printResult();
    
}


/**
 * Add new adge in the graph
 * @author Luiz Venturote
 * @param  int src Origin
 * @param  int dest Destination
 * @param  int weight Weight
 */
void addEdge(int src, int dest, int weight) {
	
	Graph[src][dest] = weight;
	Graph[dest][src] = weight;
	
}


/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 */
void Kruskal() {
	
	int markup_table[MAX];
	
	// Indexes
    int i,j, b;
    
    int cno1,cno2;
    
    // Amount edges of the main edge list
    elist.n=0;
    
    for(i=1;i<n;i++) {
    
        for(j=0;j<i;j++) {
        	
            if(Graph[i][j]!=0) {
            	
            	// Add values in main edge list
                elist.data[elist.n].src	 	= 	i;
                elist.data[elist.n].dest 	= 	j;
                elist.data[elist.n].weight	=	Graph[i][j];
                
                elist.n++;
                
            }
        }
        
    }

	// Sort edge list
    sort();            

    mst.n=0;
    
    for(i=0;i<elist.n;i++) {
    	
    	// Search inside markup table
        cno1 = search(markup_table, elist.data[i].src);
        cno2 = search(markup_table, elist.data[i].dest);
        
//        printf("\n src: %d \t dest: %d \t cno1: %d \t cno2: %d\n", elist.data[i].src, elist.data[i].dest, cno1, cno2);
        
        if(cno1!=cno2) {
        	
            mst.data[mst.n] = elist.data[i];
            
            mst.n = mst.n+1;
            
            union1(markup_table,cno1,cno2);
            
        }
        
    }
    
    
}


/**
 * Search inside markup table
 * @author Luiz Venturote
 * @param  int markup_table
 * @param  int vertex
 */
int search(int markup_table[],int vertex) {
	
    return(markup_table[vertex]);
    
}


/**
 * Union
 * @author Luiz Venturote
 */
void union1(int markup_table[],int c1,int c2) {
    int i;
    for(i=0;i<n;i++) {
    	if(markup_table[i]==c2)
    		markup_table[i]=c1;
    }
        
}


/**
 * Sort
 * @author Luiz Venturote
 */
void sort() {
	
    int i,j;
    Edge temp;
    
    for(i=1;i<elist.n;i++) {
    	
    	for(j=0;j<elist.n-1;j++) {
    		
    		if(elist.data[j].weight>elist.data[j+1].weight) {
                temp=elist.data[j];
                elist.data[j]=elist.data[j+1];
                elist.data[j+1]=temp;
            }
            
    	}
            
    }
        
}


/**
 * Print result
 * @author Luiz Venturote
 */
void printResult() {
	
    int i,cost=0;
    
    for(i=0;i<mst.n;i++) {
    	
        printf("\n src: %d\t dest: %d\t weight: %d",mst.data[i].src,mst.data[i].dest,mst.data[i].weight);
        
		cost=cost+mst.data[i].weight;
        
    }

    printf("\n\nCost of the spanning tree=%d\n\n",cost);
    
}


/**
 * Print graph
 * @author Luiz Venturote
 */
void printGraph() {
	
	int i=0, j=0;
	
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
			
			if(Graph[i][j] == 0) {
				printf("  -  ");
			} else {
				printf("  %d  ", Graph[i][j]);	
			}
			
		}	
		
		printf("\n\n");
		
	}
	
	printf("\n");
	
}
