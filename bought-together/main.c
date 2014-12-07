#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <windows.h>
#include <time.h>

#define PACK_QTD 3		// Capacidade m�xima de produtos de um pacote

// Product struct
typedef struct product {
	int id;					// ID do produto
	int weight;				// Peso do produto em rela��o aos produto principal (Indica se o produto combiana ou n�o com o principal)
	char name[50];			// Nome do produto
	char color[10];			// Cor do produto
	char collection[30];	// Cole��o em que o produto pertence
	char product_type[20]	// Tipo de produto (Parte de cima, parte debaixo ou acess�rio)
} Product;

// Node struct
typedef struct node {
	Product product;		// Produto do n�
	struct node *prim; 		// Ponteiro para eventual primeiro filho
	struct node *prox; 		// Ponteiro para eventual irm�o
} Node;

// Sinal para cntrolar o c�culo de pesos dos produtos
int sing = 0;

/**
 * Main - Bought Together
 * @author Luiz Venturote
 */
int main() {
	
	// �rvore principal
	Node *tree;

	// N� de sele��o
	Node *node_selected;

	// Inicializa �rvore principal
	initTree(&tree);
	
	// Aponta para o primeiro produto
	node_selected = tree;
	
	// Inicializa i pacote de produtos
	Product *package = (Product *)malloc(sizeof(Product)*3);
	
	// Adiciona o produto principal no pacote
	package[0] = node_selected->product;
	
	// Adiciona os produtos do primeiro tipo ( Parte debaixo )
	addNode(&node_selected, 100, "Calca sniper", "Azul", "Verao 2015", "Under");
	addNode(&node_selected, 90, "Calca fit", "Preto", "Inverno 2014", "Under");
	addNode(&node_selected, 80, "Calca pro", "Vermelho", "Primavera 2012", "Under");
	addNode(&node_selected, 88, "Calca basica skinny", "Preto", "Inverno 2012", "Under");
	addNode(&node_selected, 85, "Bermuda b�sica", "Azul", "Primavera 2012", "Under");
	addNode(&node_selected, 83, "Bermuda masculina color", "Amarela", "Inverno 2014", "Under");
	printTree(*node_selected);				// Exibe a sub �rvore
	RelatedProduct(node_selected); 			// Seleciona o produto com amior similaridade
	package[1] = node_selected->product;	// Adiciona o produto no pacote de produtos
	
	// Adiciona os produtos do primeiro tipo ( Acess�rios )
	addNode(&node_selected, 100, "Tenis", "Branco", "Verao 2015", "Accessory");
	addNode(&node_selected, 100, "Chinelo", "Amarelo", "Primavera 2012", "Accessory");
	addNode(&node_selected, 100, "Sapato", "Marrom", "Verao 2015", "Accessory");
	printTree(node_selected);				// Exibe a sub �rvore	
	RelatedProduct(node_selected);			// Seleciona o produto com amior similaridade	
	package[2] = node_selected->product;	// Adiciona o produto no pacote de produtos
	
	// Exibe os produtos que combinam com a pe�a principal
	showPackageItems(package);
	
	exit(0);
}


/**
 * Show items of the package (Exibe os itens do pacote)
 * @author Luiz Venturote
 */
void showPackageItems(Product * pack) {
	
	int i=0;
	
	printf("\n Package:");
	
	for(i=0; i<PACK_QTD; i++) {
		printf("\n - %d - %s - %s - %s - %s (%d)", pack[i].id, pack[i].name, pack[i].color, pack[i].collection, pack[i].product_type, pack[i].weight);
	}
	
}

/**
 * Select the related produtos (Seleciona o produto relacionado)
 * @author Luiz Venturote
 */
void RelatedProduct(Node* node) {
	
	int max=-2;
	
	Node *node_selected = (Node *)malloc(sizeof(Node));
	
	getRelatedProduct(node, &max, node_selected);
	
	*node = *node_selected;
}


/**
 * Get the related produtos (Seleciona o produto relacionado)
 * @author Luiz Venturote
 */
void getRelatedProduct(Node* node, int * max, Node* node_selected) {
	
	Node* p;
	
	if(*max <= node->product.weight) {
		
		// N�o conta o valor da raiz
		if(*max < 0) {
			*max = 0;
		} else {
			*max = node->product.weight;
			*node_selected = *node;	
		}
	}
	
	for (p=node->prim; p!=NULL; p=p->prox) {
		getRelatedProduct(p, max, node_selected);
	}

}

/**
 * Initialize a new tree
 * @author Luiz Venturote
 * @param Node *tree
 * @return void
 */
void initTree(Node **tree) {
	
	*tree = NULL;
	
	// Adiciona o primeiro n�
	addNode(&(*tree), 10, "Camisa gola V", "Branco", "Verao 2015", "Up");
	
}


/**
 * Add a new node in the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @param int value Node value
 * @return void
 */
void addNode(Node **tree, int id, char name[], char color[], char collection[], char product_type[]) {
	
	// Create a new node
	Node *new_node = (Node *) malloc(sizeof(Node));
	new_node->product.id = id;
	new_node->product.weight = 0;
	strcpy(new_node->product.name, name);
	strcpy(new_node->product.color, color);
	strcpy(new_node->product.collection, collection);
	strcpy(new_node->product.product_type, product_type);
	new_node->prim = NULL;
	new_node->prox = NULL;
	
	// Verifica se n�o � o produto principal
	if(sing == 1) {
		// Faz a pontua��o do produto
		rateProduct(&(*tree), &new_node);
	} else {
		sing = 1;
	}
	
	// Insert the node in the tree
	insertNode(&(*tree), new_node);   
	  
}

void rateProduct(Node ** tree, Node **new_node) {
	
	int points = 0;
	
	// Verifica se � da mesma cole��o
	if(strcmp((*tree)->product.collection, (*new_node)->product.collection) == 0) {
		points++;	
	}
	
	// Verifica o tipo de produto
	if(strcmp((*tree)->product.product_type, "Up") == 0) {
		
		if(strcmp((*new_node)->product.product_type, "Under") == 0) {
			points += 5;
		}
		
		if(strcmp((*new_node)->product.product_type, "Accessory") == 0) {
			points += 10;
		}
			
	} 
	
	if(strcmp((*tree)->product.product_type, "Under") == 0) {
		
		if(strcmp((*new_node)->product.product_type, "Up") == 0) {
			points += 5;
		}
		
		if(strcmp((*new_node)->product.product_type, "Accessory") == 0) {
			points += 10;
		}
		
	} 
	
	if(strcmp((*tree)->product.product_type, "Accessory") == 0) {
		
		if(strcmp((*new_node)->product.product_type, "Up") == 0) {
			points += 10;
		}
		
		if(strcmp((*new_node)->product.product_type, "Under") == 0) {
			points += 10;
		}
		
	}
	
	// Verifica a colora��o
	if(strcmp((*tree)->product.color, "Branco") == 0) {
		
		if(strcmp((*new_node)->product.color, "Preto") == 0) {
			points += 5;
		}
		
		if(strcmp((*new_node)->product.color, "Azul") == 0) {
			points += 8;
		}
			
	} 
	
	if(strcmp((*tree)->product.color, "Preto") == 0) {
		
		if(strcmp((*new_node)->product.color, "Branco") == 0) {
			points += 10;
		}
		
		if(strcmp((*new_node)->product.color, "Vermelho") == 0) {
			points += 3;
		}
			
	} 
	
	if(strcmp((*tree)->product.color, "Azul") == 0) {
		
		if(strcmp((*new_node)->product.color, "Branco") == 0) {
			points += 8;
		}
					
	} 
	
	
	(*new_node)->product.weight = points;
	
}


/**
 * Insert a new node in the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @param Node *new_node New node
 * @return void
 */
void insertNode(Node **tree, Node *new_node){

	if( (*tree) != NULL ) {

		new_node->prox = (*tree)->prim;
		(*tree)->prim = new_node;
				
	} else {
		(*tree) = new_node;
	} 	
}


/**
 * Print tree (Exibe a �rvore)
 * @author Luiz Venturote
 */
void printTree(Node* a) {
	
	printf(" %d )", a->product.weight);
	printSubTree(a);
	printf("\n");	
}


/**
 * Print a sub tree (Exibe uma sub �rvore)
 * @author Luiz Venturote
 */
void printSubTree(Node* a) {
	
	Node* p;
	
	for (p=a->prim; p!=NULL; p=p->prox) {
		
		printf(" %d ",p->product.weight);
		
		if(p->prox != NULL) {
			printf("->");
		}
		
		printSubTree(p); // Imprime filhos	
	}
}

