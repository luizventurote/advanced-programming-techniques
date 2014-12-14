// Number of vertices in the graph
// Número de vértices do grafo
#define DIJKSTRA_VERTEX_QTY 11

// Maximum value used in the Dijkstra algorithm
// Valor máximo utilizado no algoritmo de Dijkstra
#define DIJKSTRA_MAX_VALUE 999

// Quantity of loaded products
// Quantidade de produtos carregados
#define QTD_PRODUCTS 21

// Enable debug
// Ativar debug
#define DEBUG_OPT 0

// Product struct
// Struct Produto
typedef struct product {
	int id;					// ID do produto
	int weight;				// Peso do produto em relação aos produto principal (Indica se o produto combiana ou não com o principal)
	char name[50];			// Nome do produto
	char color[10];			// Cor do produto
	char collection[30];	// Coleção em que o produto pertence
	char product_type[30]	// Tipo de produto (Parte de cima, parte debaixo ou acessório)
} Product;

// Variables that are used to control of product categories
// Variáveis que são utilizadas para o controle das categorias de produtos
int type_under=0, type_accessory=0, type_up=0;						// Variáveis utilizadas para guardar a quantidade de produtos existentes em cada categoria
int type_under_init=-1, type_accessory_init=-1, type_up_init=-1;	// Variáveis utilizadas para guardar a posição inicial de cada categoria na lista de produtos
int product_index=0;												// Índice usado para percorrer a lista de produtos

// Variables that are used to control of minimum way gerated by the algorithm
// Variáveis que são utilizadas para o controle do caminho minimo gerado pelo algoritmo
int way[DIJKSTRA_VERTEX_QTY];	// Caminho
int way_index 	= 0;			// Índice usado para percorrer o caminho
int way_sing 	= 1;			// Sinal usado para o controle de inserções de vértices no caminho


/**
 * Dijkstra Bought Together
 *
 * @author Luiz Venturote
 */
void DijkstraBoughtTogether() {
	
	printf("\n === Dijkstra Bought Together ===================================== \n\n");
	
	int i=0, j=0, product_weight=0;
	
	int graph[DIJKSTRA_VERTEX_QTY][DIJKSTRA_VERTEX_QTY];
   
	// Init graph
	// Inicializa o grafo
	Dijkstra_initGraph(graph);
	
	// Product list
	Product product_list[QTD_PRODUCTS];
	
	// Init product list
	// Inicializa a lista de produtos
	initProductsList(product_list);
	
	// Adds the edges of the bottom part of the products
	// Adiciona as arestas dos produtos da parte de baixo
	for(i=type_under_init; i<type_under_init + type_under; i++) {
		
		product_weight = getProductWeight(product_list[0], product_list[i]);
		
		Dijkstra_addEdge(graph, 0, i, product_weight);
	}
	
	// Add the accessories edges
	// Adiciona as arestas de acessórios
	for(i=type_under_init; i<type_under_init + type_under; i++) {
		for(j=type_accessory_init; j<type_accessory_init + type_accessory; j++) {
			
			product_weight = getProductWeight(product_list[0], product_list[j]) + getProductWeight(product_list[i], product_list[j]);
			
			product_weight = product_weight/3;
			
			if(product_weight < 0) {
				product_weight=0;
			}
			
			Dijkstra_addEdge(graph, i, j, product_weight);
			
		}
	}
	
	// Adds the end edges that are neutral
	// Adiciona as arestas finais que são neutras
	for(i=type_accessory_init; i<type_accessory_init + type_accessory; i++) {
		
		product_weight = getProductWeight(product_list[0], product_list[i]);
		
		Dijkstra_addEdge(graph, i, type_up + type_under + type_accessory, 1);
		
	}
	
	// Print graph
	// Exibe o grafo
	Dijkstra_printGraph(graph);
	
	// Execute Dijkstra
	// Executa o Dijkstra
    DijkstraMST(graph, 0);
    
    // Show products with selected by the algorithm
    // Exibe os produtos selecionados pelo algoritmo  
    for(i=0; i<DIJKSTRA_VERTEX_QTY; i++) {
		if(way[i] != DIJKSTRA_MAX_VALUE) {
			printProduct(product_list, way[i]);
		}
	}
    
    printf("\n\n");
    
}


int getProductWeight(Product p1, Product p2) {
	
	int points = 500;
	
	// Verifica se é da mesma coleção
	if(strcmp(p1.collection, p2.collection) == 0) {
		points -= 253;	
	} else {
		points -= 55;
	}
	
	// Verifica o tipo de produto
	if(strcmp(p1.product_type, "Up") == 0) {
		
		if(strcmp(p2.product_type, "Under") == 0) {
			points -= 52;
		}
		
		if(strcmp(p2.product_type, "Accessory") == 0) {
			points -= 26;
		}
			
	} 
	
	if(strcmp(p1.product_type, "Under") == 0) {
		
		if(strcmp(p2.product_type, "Up") == 0) {
			points -= 54;
		}
		
		if(strcmp(p2.product_type, "Accessory") == 0) {
			points -= 16;
		}
		
	} 
	
	if(strcmp(p1.product_type, "Accessory") == 0) {
		
		if(strcmp(p2.product_type, "Up") == 0) {
			points -= 12;
		}
		
		if(strcmp(p2.product_type, "Under") == 0) {
			points -= 17;
		}
		
	}
	
	// Verifica a coloração
	if(strcmp(p1.color, "Branco") == 0) {
		
		if(strcmp(p2.color, "Preto") == 0) {
			points -= 59;
		}
		
		if(strcmp(p2.color, "Azul") == 0) {
			points -= 84;
		}
		
		if(strcmp(p2.color, "Amarelo") == 0) {
			points -= 23;
		}
		
		if(strcmp(p2.color, "Vermelho") == 0) {
			points -= 16;
		}
		
		if(strcmp(p2.color, "Marrom") == 0) {
			points -= 42;
		}
			
	} 
	
	if(strcmp(p1.color, "Preto") == 0) {
		
		if(strcmp(p2.color, "Branco") == 0) {
			points -= 102;
		}
		
		if(strcmp(p2.color, "Vermelho") == 0) {
			points -= 36;
		}
		
		if(strcmp(p2.color, "Azul") == 0) {
			points -= 36;
		}
		
		if(strcmp(p2.color, "Amarelo") == 0) {
			points -= 20;
		}
		
		if(strcmp(p2.color, "Marrom") == 0) {
			points -= 40;
		}
			
	} 
	
	if(strcmp(p1.color, "Azul") == 0) {
		
		if(strcmp(p2.color, "Branco") == 0) {
			points -= 87;
		}
		
		if(strcmp(p2.color, "Preto") == 0) {
			points -= 102;
		}
		
		if(strcmp(p2.color, "Vermelho") == 0) {
			points -= 10;
		}
		
		if(strcmp(p2.color, "Amarelo") == 0) {
			points -= 20;
		}
		
		if(strcmp(p2.color, "Marrom") == 0) {
			points -= 30;
		}
					
	} 
	
	return points;
}


/**
 * Displays information of a product
 * Exibe informações de um produto
 *
 * @author Luiz Venturote
 */
void printProduct(Product list[], int p_index) {
	printf("\n %d => %s - %s - %s\n", list[p_index].id, list[p_index].name, list[p_index].color, list[p_index].collection);
}


/**
 * Init product list
 * Inicializa a lista de produtos
 *
 * @author Luiz Venturote
 */
void initProductsList(Product list[]) {
	
	// Up
	addProductsInTheList(list, 10, "Camisa gola V", "Branco", "Verao", "Up");
	
	// Under
	addProductsInTheList(list, 20, "Calca sniper", "Azul", "Verao", "Under");
	addProductsInTheList(list, 30, "Calca fit", "Preto", "Inverno", "Under");
	addProductsInTheList(list, 40, "Calca pro", "Vermelho", "Verao", "Under");
	addProductsInTheList(list, 50, "Calca basica skinny", "Preto", "Verao", "Under");
	addProductsInTheList(list, 60, "Bermuda básica", "Azul", "Primavera", "Under");
	addProductsInTheList(list, 70, "Bermuda masculina color", "Amarelo", "Inverno", "Under");
	
	// Accessory
	addProductsInTheList(list, 80, "Tenis", "Branco", "Verao", "Accessory");
	addProductsInTheList(list, 90, "Chinelo", "Amarelo", "Primavera", "Accessory");
	addProductsInTheList(list, 100, "Sapato", "Marrom", "Verao", "Accessory");
		
}


/**
 * Add a product in the list
 * Adiciona um produto na lista
 *
 * @author Luiz Venturote
 */
void addProductsInTheList(Product list[], int id, char name[], char color[], char collection[], char product_type[]) {
	
	list[product_index].id = id;
	strcpy(list[product_index].name, name);
	strcpy(list[product_index].color, color);
	strcpy(list[product_index].collection, collection);
	strcpy(list[product_index].product_type, product_type);
	
	// Contabiliza a quantidade de produtos por tipo
	if(strcmp(product_type, "Under") == 0) {
		type_under++;
		
		if(type_under_init == -1) {
			type_under_init = product_index;
		}
	}
	
	if(strcmp(product_type, "Accessory") == 0) {
		type_accessory++;
		
		if(type_accessory_init == -1) {
			type_accessory_init = product_index;
		}
	}
	
	if(strcmp(product_type, "Up") == 0) {
		type_up++;
		
		if(type_up_init == -1) {
			type_up_init = product_index;
		}
	}
	
	product_index++;
	
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
	
	int i=0, count=0, n=DIJKSTRA_VERTEX_QTY, debug_print=0, u=0, dest_value=DIJKSTRA_MAX_VALUE, u_prior=0, update_index=0, u_min_dist=DIJKSTRA_MAX_VALUE, u_prior_min_dist=DIJKSTRA_MAX_VALUE;
	
	int dist_table[n];    
	int markup_table[n];   
 
	// Initialize vectors
	// Inicializa os vetores
	for(i=0; i<n; i++) {
		dist_table[i]   = DIJKSTRA_MAX_VALUE;
		markup_table[i] = 0;
		way[i] = DIJKSTRA_MAX_VALUE;	
	}
        
 	// Distance of source vertex from itself is always 0
 	// Distância do vértice de origem sempre vai ser 0
	dist_table[src] = 0;
 	
	for(count=0; count<n-1; count++) {
		
		u = Dijkstra_minDistance(dist_table, markup_table);
 
		// Mark the picked vertex as processed
		// Marca o vértice escolhido como processado
		markup_table[u] = 1;
		
		int update_sing = 0; // Variável utilizada para o controle de ações que são realizadas após a atualização de valores do vetor dist_table[] 
		
		// Update dist value of the adjacent vertices
		// Atualiza as distâncias dos vértices adjacentes
		for(i=0; i<n; i++) {
		
			if(!markup_table[i] && graph[u][i] && dist_table[u]!=DIJKSTRA_MAX_VALUE && dist_table[u]+graph[u][i]<dist_table[i]) {
				
				dist_table[i] = dist_table[u] + graph[u][i];
				
				// Guarda o valor da distância mínima
				if(dist_table[i] < u_min_dist) {
					u_min_dist = dist_table[i];
				}
				
				debug_print = 1;
				update_sing = 1;
				update_index = i; // último índice atualizado
				
			}
			
			if(DEBUG_OPT) {
				printf(" count: %d | u: %d | i: %d | graph[u][i]: %d | markup_table[i]: %d | dist_table[u]: %d | dist_table[i]: %d", count, u, i, graph[u][i], markup_table[i], dist_table[u], dist_table[i]);
			}
			
			if(debug_print == 1) {
				if(DEBUG_OPT) {
					printf(" | Updated");
					debug_print = 0;
				}
			}	
			
			if(DEBUG_OPT) {
				printf("\n");
			}
        }
        
        // Adiciona o vértice no caminho principal se houver alguma atualização no vetor dist_table[]
        if(update_sing == 1) {
        	
	        i--;
	        
	        if(DEBUG_OPT) {
	        	printf(" u: %d  |  dest_value: %d  |  dist_table[i]: %d ", u, dest_value, dist_table[i]);
	    	}
	    
	        // Verifica se atualização foi no último elemento do vetor e o valor da última posição
	        if(dist_table[i] < dest_value) {
	        	
	        	if(DEBUG_OPT) {
	        		printf(" |  way_index: %d   |  way[way_index]: %d | ok", way_index, way[way_index]);
	        		printf("\n Vertice %d foi adicionado no caminho!\n", u);
	        	}
	        	
	        	dest_value = dist_table[i];	// Guarda o peso do último vértice adicionado no final do caminho
	        		        	        	
	        	way[way_index] = u;	// Adiciona o vértice no final do caminho
	        	
	        	way_sing = 0; // Trava a inserção de vértices no meio do caminho, com isso, somente o último vértice pode ser alterado
	        	
	        } 
	        
	        if(way_sing == 1) {
	        	
	        	// Verifica se é o primeiro vértice
	        	if(way_index ==  0) {
	        		
	        		if(DEBUG_OPT) {
	        			printf("\n Vertice %d foi adicionado no caminho!\n", u);
	        		}
	        	
	        		way[way_index] = u;
			        way_index++;
	        		
	        	} else {
	        		
	        		if(DEBUG_OPT) {
	        			printf("\n way_index: %d | u_prior: %d | update_index: %d | graph[u_prior][update_index]: %d | graph[u][update_index]: %d | u_min_dist: %d | u_prior_min_dist: %d\n", way_index, u_prior, update_index, graph[u_prior][update_index], graph[u][update_index], u_min_dist, u_prior_min_dist);
					}
					
				    // Verifica se o vértice anterior têm a mesma ligação do que o vértice atual
				    if(graph[u_prior][update_index] == 0) {
				    	
				    	// Adiciona o vértice no caminho
				    	way[way_index] = u;
				       	way_index++;
				       	
				    	if(DEBUG_OPT) {
				    		printf("\n Vertice %d foi adicionado no caminho!\n", u);
				    	}
				       	
				    } else {
				    	
				    	// Verifica se a distância atual é menor do que a distância do vértice anterior
				    	if(u_min_dist < u_prior_min_dist) {
				       		
				       		// Realiza a substituição de posições no caminho
				       		way_index--;
				       		if(DEBUG_OPT) {
				       			printf("\n Vertice %d foi substituido por %d no caminho!\n", way[way_index], u);
				       		}
				    		way[way_index] = u;	
				    		way_index++;
				    	}
				    	
				    }
	        	}
	        }
		}
		
		// Guarda os valores do vértice anterior
		if(update_sing == 1) {
			u_prior = u;
			u_prior_min_dist = u_min_dist;
		}
		
		// Reseta a distância mínima	
		u_min_dist=DIJKSTRA_MAX_VALUE;
		
		if(DEBUG_OPT) {
        	printf("\n\n");
		}
    }
    
    
	printf("\n\n Way \n");
	for(i=0; i<n; i++) {
		if(way[i] != DIJKSTRA_MAX_VALUE) {
			printf(" %d =>", way[i]);
		}
	}
	printf(" %d\n\n", DIJKSTRA_VERTEX_QTY-1);
		
	if(DEBUG_OPT) {
		printf("\n\n");
	 
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
 	}
 
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
