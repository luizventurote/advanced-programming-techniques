#define KRUSKAL_EDGES_QTY 7

// Structure to represent a edge
typedef struct edge {
    int src;
    int dest;
    int weight;
} Edge;

// Structure to represent a edge list
typedef struct edgelist {
    Edge data[KRUSKAL_EDGES_QTY*KRUSKAL_EDGES_QTY];
    int n;
} EdgeList;

// Main edge list
EdgeList elist;

// Main graph
int Graph[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY];

// Minimum spanning tree
EdgeList mst;

/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 */
void KruskalMST() {
	
	Kruskal_initGraph();

	// Add adges
	Kruskal_addEdge(0, 1, 5);
	Kruskal_addEdge(0, 2, 3);
	Kruskal_addEdge(1, 0, 5);
	Kruskal_addEdge(1, 2, 4);
	Kruskal_addEdge(1, 3, 1);
	Kruskal_addEdge(1, 4, 7);
	Kruskal_addEdge(2, 1, 6);
	Kruskal_addEdge(2, 3, 5);
	Kruskal_addEdge(2, 5, 2);
	Kruskal_addEdge(2, 4, 1);
	Kruskal_addEdge(3, 4, 9);
	Kruskal_addEdge(3, 6, 4);
	Kruskal_addEdge(4, 3, 2);
	Kruskal_addEdge(4, 5, 5);
	Kruskal_addEdge(4, 6, 8);
	Kruskal_addEdge(5, 2, 3);
	Kruskal_addEdge(5, 4, 7);
	Kruskal_addEdge(5, 6, 3);
	Kruskal_addEdge(6, 4, 8);

	// Print main graph
    Kruskal_printGraph(); 
    
    // Execute Kruskal's algorithm
    Kruskal(Graph, KRUSKAL_EDGES_QTY);
    
    // Print Results
    Kruskal_printResult();
    
}

void Kruskal_initGraph() {
	
	int i=0, j=0;
	
	for(i=0; i<KRUSKAL_EDGES_QTY; i++) {
		
		for(j=0; j<KRUSKAL_EDGES_QTY; j++) {	
			Graph[i][j] = 999;	
		}
	}
}

/**
 * Add new adge in the graph
 * @author Luiz Venturote
 * @param  int src Origin
 * @param  int dest Destination
 * @param  int weight Weight
 */
void Kruskal_addEdge(int src, int dest, int weight) {
	Graph[src][dest] = weight;
}


void AdjacencyMatrix(int a[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY], int n){
	
    int i,j;
    for(i = 0;i < n; i++) {
        for(j = 0;j < n; j++)
        {
//            a[i][j] = a[j][i]= rand()%50;
				a[i][j] = rand()%50;
            if( a[i][j]>40)a[i][j]=a[j][i]=999;
             
        }
    a[i][i] = 999;
    }
    printArray(a,n);
}
 
void printArray(int a[][100],int n){
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
}
 
int root(int v,int p[]){
 
    while(p[v] != v)
        {v = p[v];}
         
return v;
}
 
void union_ij(int i,int j,int p[]){
    if(j > i)
        p[j] = i;
    else
        p[i] = j;
}

/**
 * Kruskal’s algorithm
 * @author Luiz Venturote
 */
void Kruskal(int a[KRUSKAL_EDGES_QTY][KRUSKAL_EDGES_QTY],int n){
	
    int count, i, p[100], min, j, u, v, k, t[100][100], sum;
    
    count = k = sum = 0;
    
    for(i = 0; i < n; i++) {
        p[i] = i;
    }
    
    while(count < n) {
    	
        min = 999;
        
        for(i = 0; i < n; i++) {
        	
            for(j = 0;j < n; j++) {
             
                if(a[i][j] < min) {
                    min = a[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        
        if(min != 999) {
        	
            i = root(u, p);
            j = root(v, p);
            
            if (i != j) {
                t[k][0] = u;
                t[k][1] = v;
                 
                k++;
                 
                sum += min;
                union_ij(i,j,p);
            }
            
        	a[u][v] = a[v][u] = 999;
         
        }
		
		count +=1;
    }   
    if(count != n) {
        printf("spanning tree not exist\n");
    }
    
    if(count == n) {
    	
        printf("Adges Spanning tree is\n");
        
        for(k = 0; k < n-1 ; k++) {
            printf(" %d -> %d ",t[k][0],t[k][1]);
        }
        
    printf("\ncost = %d \n",sum);
    
    }
    
}
 


/**
 * Print result
 * @author Luiz Venturote
 */
void Kruskal_printResult() {
	
 
    
}


/**
 * Print graph
 * @author Luiz Venturote
 */
void Kruskal_printGraph() {
	
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
			
			if(Graph[i][j] == 0 || Graph[i][j] == 999) {
				printf("  -  ");
			} else {
				printf("  %d  ", Graph[i][j]);	
			}
			
		}	
		
		printf("\n\n");
		
	}
	
	printf("\n");
	
}
