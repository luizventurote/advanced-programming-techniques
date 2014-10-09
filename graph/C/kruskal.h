// Structure to represent a weighted edge in graph
struct graph_edge {
	int value;
	int weight;
} typedef Edge;

// Structure to represent a connected, undirected and weighted graph
//struct graph {
//    int V, E;
//    Edge* edge;
//} typedef Graph;

/**
 * Creates a graph
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 */
Edge ** createGraph(int lines, int columns) {
	
	int i=0, j=0;
	
	Edge ** graph = malloc( lines * sizeof(Edge*) );
	
	for(i=0; i<lines; ++i) {
		graph[i] = malloc( columns * sizeof(Edge) );
		
		// Add neutral values in edge
		for(j=0; j<columns; ++j) {
			graph[i][j].value = 0;
			graph[i][j].weight = 0;
		}
	}
		
    return graph;
    
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
//    return a1.weight > b1.weight;
}
 


// The main function to construct MST using Kruskal's algorithm
int ** KruskalMST(Edge **graph, int lines, int columns) {

	
//	int ** graph_mst = malloc( lines * sizeof(int*) );
	
//    int V = graph->V;
//    
//    Edge result[V];  // Tnis will store the resultant MST
//    
//    int e = 0;  // An index variable, used for result[]
//    int i = 0;  // An index variable, used for sorted edges
//    int v=0;
// 

    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
//    qsort(graph[0][0], lines*columns, sizeof(graph[0][0]), myComp);
 
    // Allocate memory for creating V ssubsets
//    struct subset *subsets =
//        (struct subset*) malloc( V * sizeof(struct subset) );
// 
//    // Create V subsets with single elements
//    for (v = 0; v < V; ++v)
//    {
//        subsets[v].parent = v;
//        subsets[v].rank = 0;
//    }
// 
//    // Number of edges to be taken is equal to V-1
//    while (e < V - 1)
//    {
//        // Step 2: Pick the smallest edge. And increment the index
//        // for next iteration
//        Edge next_edge = graph->edge[i++];
// 
//        int x = find(subsets, next_edge.src);
//        int y = find(subsets, next_edge.dest);
// 
//        // If including this edge does't cause cycle, include it
//        // in result and increment the index of result for next edge
//        if (x != y)
//        {
//            result[e++] = next_edge;
//            Union(subsets, x, y);
//        }
//        // Else discard the next_edge
//    }
// 
//    // print the contents of result[] to display the built MST
//    printf("Following are the edges in the constructed MST\n");
//    for (i = 0; i < e; ++i)
//        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
//                                                   result[i].weight);
//    return;
    
    return NULL;
    
}

void printGraph(Edge *graph [], int lines, int columns) {
	
	int i=0, j=0;
	
	Edge *graph_edge;
	
	printf("\n");
	
	for(i=0; i<lines; ++i) {
		
		// Graph index
		if(i==0) {
			
			for(j=0; j<columns; ++j) {
				
				if(j==0)
				printf("   | ");
				
				printf("  %d  ", j);
				
			}
							
			printf("\n");	
			
			for(j=0; j<columns; ++j)
				printf("------", j);
				
			printf("\n");	
		}
		
		for(j=0; j<columns; ++j) {
			
			if(j==0)
				printf(" %d | ", i);
			
			if(graph[i][j].value == 0) {
				printf("  -  ");
			} else {
				printf("  %d  ", graph[i][j].value);	
			}
			
		}	
		
		printf("\n\n");
		
	}
	
	printf("\n");
	
}


void addEdge(Edge ** graph, int src, int dest, int weight) {
	
	graph[src][dest].value = 1;
	graph[dest][src].value = 1;
	graph[src][dest].weight = weight;
	
}


void Kruskal() {

	// Qty of vertices in graph
    int vertices_qty = 6; 
    
    // Create graph
    Edge **graph = createGraph(vertices_qty, vertices_qty);
 
    // add edge
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 0, 4, 1);
    addEdge(graph, 0, 5, 2);
    
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 1, 4, 2);
    
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 2, 5, 2);
    
    addEdge(graph, 3, 4, 2);
    
    // Print Graph
 	printGraph(graph, vertices_qty, vertices_qty);
 	
 	// Kruskal algorithm to get minimum spanning tree
    int **graph_mst = KruskalMST(graph, vertices_qty, vertices_qty);
		
}
