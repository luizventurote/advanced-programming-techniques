static int dyn_sing = 0;

// Node struct
typedef struct node {
	int value;				// Node content
	struct node *left;		// Feft child
	struct node *right;		// Right child
	int fb; 				// Balanced Factor
} Node;


/**
 * Initialize a new tree
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return void
 */
void Dyn_initTree(Node **tree) {
	*tree = NULL;
}


/**
 * Right rotation
 * @author Luiz Venturote
 * @param Node *A Binary Tree
 * @return Node*
 */
void Dyn_rightRotation(Node **A) {
	
	Node *B = (*A)->left; 
          
    // Single Rotation
	if (B->fb == -1) {   
	              
		(*A)->left = B->right; 
		B->right = (*A); 
		(*A)->fb = 0; 
    	(*A) = B; 
    	
    } 
	 
	 // Double Rotation
	 else { 
	
		if( (B->right != NULL) ){
			
			Node *C = B->right;
			 
			B->right = C->left;
			C->left = B;
			(*A)->left = C;

			(*A)->left = C->right;
			C->right = (*A);
			
			if (C->fb == -1){ 
				(*A)->fb = 1; 
			} else {
				(*A)->fb = 0;	
			}
			    
			if (C->fb == 1){ 
				B->fb = -1; 
			} else {
				B->fb = 0;
			} 
	         
			(*A) = C; 
		 }
	 }
     
	 (*A)->fb = 0; 
     dyn_sing = 0;
     
}


/**
 * Left rotation
 * @author Luiz Venturote
 * @param Node *A Binary Tree
 * @return Node*
 */ 
void Dyn_leftRotation(Node **A) {

   Node *B = (*A)->right; 
   
   // Single Rotation
   if(B->fb == 1) { 
   
	   (*A)->right = B->left; 
	   B->left = (*A); 
	   (*A)->fb = 0; 
       (*A) = B; 
       
   }
   
	// Double Rotation
	else {

		if(B->left != NULL) {

			Node *C = B->left;
			B->left = C->right;
			(*A)->right = C;
			C->right = B;

			(*A)->right = C->left;
			C->left = (*A);
		   
			if (C->fb == 1) {
				(*A)->fb = -1; 
			} else {
				(*A)->fb = 0; 
			}

			if (C->fb == -1) { 
		 		B->fb = 1; 
			} else {
				B->fb = 0;	
			} 
		      
		   (*A) = C; 
	    }
	    
	}
    
	(*A)->fb = 0; 
	dyn_sing = 0;
	 
}
 

/**
 * Insert a new node in the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @param Node *new_node New node
 * @return void
 */
void Dyn_insertNode(Node **tree, Node *new_node){

	if( (*tree) != NULL ) {

		if ( (*tree)->value > new_node->value ) {
			
			// Insert in left
			Dyn_insertNode( &(*tree)->left, new_node); 
			if (dyn_sing == 1) { 
				switch ( (*tree)->fb ) {    
					case 1 : 
						(*tree)->fb = 0; 
						dyn_sing = 0; 
						break; 
					case 0 : 
						(*tree)->fb = -1; 
						break; 
                    case -1 : 
						Dyn_rightRotation( &(*tree) ); 
						break; 
            	}
            }
			 
		} else {
			
			// Insert in right
			Dyn_insertNode( &(*tree)->right, new_node); 
            if (dyn_sing == 1){ 
				switch ((*tree)->fb)    {   
					case -1 : 
						(*tree)->fb = 0; 
						dyn_sing = 0; 
						break; 
					case 0 : 
						(*tree)->fb = 1; 
						break; 
                    case 1 : 
						Dyn_leftRotation(&(*tree)); 
						break;     
                }
            }
			
		}  
		
	} else {
		(*tree) = new_node;
		dyn_sing = 1;
	} 
	
}


/**
 * Add a new node in the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @param int value Node value
 * @return void
 */
void Dyn_addNode(Node **tree, int value){
	
	// Create a new node
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->fb = 0;
	
	// Insert the node in the tree
	Dyn_insertNode(&(*tree), new_node);   
	  
}


/**
 * Add a new node in the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @param int value Node value
 * @return void
 */
Node* Dyn_searchNode(Node *tree, int value) {
   if (tree == NULL) {
       return NULL;      
   } else if (tree->value == value){
       return tree;   
   } else if (tree->value > value){
       return (Dyn_searchNode(tree->left, value));
   } else {
       return (Dyn_searchNode(tree->right, value));       
   } 
}


/**
 * Node height
 * @author Luiz Venturote
 * @param Node **tree Tree or node
 * @return int Node height
 */
int Dyn_getNodeHeight(Node *tree) {

	return Dyn_heightNode(tree) - 1;
		
}

int Dyn_heightNode(Node *tree) {

	if(tree == NULL) 
		return 0;
	else
		return max(Dyn_heightNode(tree->left), Dyn_heightNode(tree->right)) +1;
		
}


/**
 * Lvel height
 * @author Luiz Venturote
 * @param Node **tree Tree or node
 * @param int value Node value
 * @return int Node height
 */
int Dyn_levelNode(Node *tree, int value) {
	
	if(tree == NULL) {
    	return 0;
    	
	} else {
		
		int level = -1;
		
		if(tree->value == value) {
    		return level+1;   
   	
		} else if(tree->value > value) {
	    	level = Dyn_levelNode(tree->left, value);
	   	
		} else {
			level = Dyn_levelNode(tree->right, value);       
	   	} 
	   	
	   	return level +1;   
		
	}
	
	return 0;   
   
}


/**
 * Display the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @return void
 */
void Dyn_displayTree(Node *tree){
     Dyn_printTree(tree,2,40,40);     
}


/**
 * Print tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @return void
 */
void Dyn_printTree(Node *tree, int line, int column, int rate){
     if (tree != NULL){
       if ((line < 25) && (column <= 80) && (column > 0)){    
           Dyn_gotoxy(column,line);
           printf("<%d>",tree->value);
           rate = rate /2;
           Dyn_printTree(tree->left,line+2,column-rate, rate);
           Dyn_printTree(tree->right, line+2,column+rate, rate);      
        }
     }    
}


/**
 * Gotoxy
 * @author Luiz Venturote
 * @param int column
 * @param int line
 * @return void
 */
void Dyn_gotoxy(int column, int linha) { 
	COORD point; 
	point.X = column; point.Y = linha; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point); 
}


/**
 * Print tree - Preorder
 * @author Luiz Venturote
 * @param int column
 * @param int line
 * @return void
 */
void Dyn_printPreorder(Node *tree) {
	
	if( tree != NULL ) {
		printf(" %d", tree->value);
	}
	
	if( tree->left != NULL) {
		Dyn_printPreorder(tree->left);
	}
	
	if( tree->right != NULL) {
		Dyn_printPreorder(tree->right);
	}
	
}


/**
 * Print tree - Inorder
 * @author Luiz Venturote
 * @param int column
 * @param int line
 * @return void
 */
void Dyn_printInorder(Node *tree) {
	
	if( tree->left != NULL) {
		Dyn_printInorder(tree->left);
	}
	
	if( tree != NULL ) {
		printf(" %d", tree->value);
	}
	
	if( tree->right != NULL) {
		Dyn_printInorder(tree->right);
	}
	
}


/**
 * Print tree - Postorder
 * @author Luiz Venturote
 * @param int column
 * @param int line
 * @return void
 */
void Dyn_printPostorder(Node *tree) {
	
	if( tree->left != NULL) {
		Dyn_printPostorder(tree->left);
	}
	
	if( tree->right != NULL) {
		Dyn_printPostorder(tree->right);
	}
	
	if( tree != NULL ) {
		printf(" %d", tree->value);
	}
	
}


/**
 * Print tree - Descending Order
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return void
 */
void Dyn_printDescendingOrder(Node *tree) {
	
	if(tree == NULL) {
		return;
	}
    
    Dyn_printDescendingOrder(tree->right);
    
    printf(" %d", tree->value);
    
    Dyn_printDescendingOrder(tree->left);
	
}


/**
 * Number of nodes
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return int qty
 */
int Dyn_NodeQty(Node *tree) {
	
	if(tree == NULL) {
		return 0;
	}
	
	int nL = Dyn_NodeQty(tree->left); 
	int nR = Dyn_NodeQty(tree->right); 
	
	return (nL + nR + 1); 
}

int Dyn_getNodeQty(Node *tree) {
	return Dyn_NodeQty(tree) - 1;
}


/**
 * The tree is balanced?
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return int Yes or No
 */
int Dyn_isBalanced(Node *tree) {
	
	int lh; // for height of left subtree
	int rh; // for height of right subtree
 
	// If tree is empty then return true
	if(tree == NULL)
		return 1; 
 
	// Get the height of left and right sub trees
	lh = Dyn_heightNode(tree->left);
	rh = Dyn_heightNode(tree->right);
   
	//printf("\n Node: %d - lh: %d - rh: %d\n", tree->value, lh, rh);
 
	if( abs(lh-rh) <= 1 && Dyn_isBalanced(tree->left) && Dyn_isBalanced(tree->right))
		return 1;
 
	/* If we reach here then tree is not height-balanced */
	return 0;
}


/**
 * The tree is perfect balanced?
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return int Yes or No
 */
int Dyn_isPerfectBalanced(Node *tree) {
	
	int lnq; // for qty of the nodes of left bubtree
	int rnq; // for qty of the nodes of right subtree
 
	// If tree is empty then return true
	if(tree == NULL)
		return 1; 
 
	// Get the node qty of left and right sub trees
	lnq = Dyn_NodeQty(tree->left);
	rnq = Dyn_NodeQty(tree->right);
 
	if( abs(lnq-rnq) <= 1 && Dyn_isBalanced(tree->left) && Dyn_isBalanced(tree->right))
		return 1;
 
	return 0;
}


/**
 * strictly binary tree
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return int Yes or No
 */
int Dyn_is2Tree(Node *tree) {

	if(tree) {
		
        if( ( (!tree->right)&&(tree->left) ) || ( (tree->right)&&(!tree->left) ) ) {
        	return 0;	
        } else {
	    	return Dyn_is2Tree(tree->left) && Dyn_is2Tree(tree->right);
		}
		
    }
    
    return 1;
	
}


/**
 * Adds nodes in the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @param int *vector Int Vector
 * @param int qty quantity of nodes in the tree
 * @return void
 */
void Dyn_addNodesInTheTree(Node **tree, int *vector, int qty) {
	
	int i=0;
	
	for(i=0; i<qty; i++) {
		Dyn_addNode(tree, vector[i]);	
	}
	
}
	

/**
 * Print int vector
 * @author Luiz Venturote
 * @param int *vector Int Vector
 * @param int qty quantity of nodes in the tree
 * @return void
 */
void Dyn_printIntVector(int *vector, int qty) {
	
	int i=0;
	
	printf("\n === Values of the int vector ================\n");
	
	for(i=0; i<qty; i++) {
		printf(" %d ", vector[i]);
	}
	
	printf("\n =============================================\n");
		
}


/**
 * Add random values in vector
 * @author Luiz Venturote
 * @param int *vector Int Vector
 * @param int qty quantity of nodes in the tree
 * @return void
 */
void Dyn_addRandValuesInVector(int *vector, int qty) {
	
	int i=0;
	
	for(i=0; i<qty; i++) {
		vector[i] = rand() % qty+qty;	
	}
	
}


/**
 * Print tree inorder
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return void
 */
void Dyn_printTreeInorder(Node *tree) {
	printf("\n === Tree Inorder ============================\n");
	Dyn_printInorder(tree);
	printf("\n =============================================\n");
} 


/**
 * Print results
 * @author Luiz Venturote
 * @param float time_1
 * @param float time_2
 * @return void
 */
void Dyn_printResults(float time_1, float time_2) {
	
	float result=0;
	
	// Results
	printf("\n === Results =================================\n");
	
	printf("\n Tempo decorrido da arvore: %f", time_1);
	printf("\n\n Tempo decorrido do bubble sort: %f", time_2);
	
	if(time_1 < time_2) {
		
		if(time_1 == 0) {
			result = (time_2*100);
			printf("\n\n Arvore binaria e %3.2f%% mais rapida\n\n",  result);	
		} else {
			result = ((time_2/time_1)*100)-100;
			printf("\n\n Arvore binaria e %3.2f%% mais rapida\n\n",  result);		
		}
		
	} else {
		
		if(time_1 == time_2) {
			printf("\n\n Sem diferenca no tempo de execucao\n\n");		
		} else {
			result = ((time_1/time_2)*100)-100;
			printf("\n\n Bubble e %3.2f%% mais rapido\n\n",  result);
		}
		
	}
	
	printf(" =============================================\n\n");
	
}
	
	
/**
 * Initialize dynamic binary tree representation
 * @author Luiz Venturote
 * @return void
 */
void BinaryTreeDyn() {
	
	// Tree
	Node *tree;
	
	// Init
	Dyn_initTree(&tree);
	
	// Adds nodes
	Dyn_addNode(&tree, 100);
	Dyn_addNode(&tree, 50);
	Dyn_addNode(&tree, 150);
	Dyn_addNode(&tree, 25);
	Dyn_addNode(&tree, 35);
	Dyn_addNode(&tree, 15);
	Dyn_addNode(&tree, 10);
	Dyn_addNode(&tree, 5);
	Dyn_addNode(&tree, 3);
	Dyn_addNode(&tree, 2);
	
	Dyn_displayTree(tree);
	
	// Search node
	Node *node_found = Dyn_searchNode(tree, tree->value);
	printf("\n\n\n\n Node: %d\n", node_found->value);
	
	// Node Height
	printf(" Height: %d \n", Dyn_getNodeHeight(node_found) );
	
	// Node Lvel
	printf(" Level: %d \n", Dyn_levelNode(tree, node_found->value) );
	
	// Node qty
	printf(" Node qty: %d \n\n", Dyn_getNodeQty(node_found) );
	
	// Is perfectly balanced
	printf(" Arvore perfeitamente balanceada: %d \n\n", Dyn_isPerfectBalanced(node_found) );
	
	// Is strictly
	printf(" Arvore Estritamente binaria: %d \n\n", Dyn_is2Tree(node_found) );
	
	// Print tree - Preorder 
	printf(" Preorder:");
	Dyn_printPreorder(tree);
	printf("\n\n");
	
	// Print tree - Inorder 
	printf(" Inorder:");
	Dyn_printInorder(tree);
	printf("\n\n");
	
	// Print tree - Postorder 
	printf(" Postorder:");
	Dyn_printPostorder(tree);
	printf("\n\n");
	
	// Print tree - Descending Order 
	printf(" Descending Order:");
	Dyn_printDescendingOrder(tree);
	printf("\n\n");
	
}


/**
 * Initialize dynamic binary tree representation with executing time
 * @author Luiz Venturote
 * @return void
 */
void BinaryTreeDynET() {
	
	int i=0, value=0;
	
	// Tree
	Node *tree;
	
	// Init
	Dyn_initTree(&tree);
	
	// Qty nodes
	int qty_nodes = 100000;
	
	// Vector values
	int values[qty_nodes];
	
	// Add random values in vector
	Dyn_addRandValuesInVector(values, qty_nodes);
	
	// Print Vector
	Dyn_printIntVector(values, qty_nodes);
	
	// Time to print the sorted list of nodes
	time_t seconds = time(NULL);
	
	// Adds nodes in the tree
	Dyn_addNodesInTheTree(&tree, values, qty_nodes);
	
	// Print tree - Inorder 
	Dyn_printTreeInorder(tree);
	
	// End time tree
	float end_time_tree = time(NULL) - seconds;
	
	// Print vector
	//Dyn_printIntVector(values, qty_nodes);
	
	// Time to print the sorted list with bubble sort
	seconds = time(NULL);
	
	// Ording vector
	bubbleSort(values, qty_nodes);
	
	// Print vector
	Dyn_printIntVector(values, qty_nodes);
	
	// End time bubble
	float end_time_bubble = time(NULL) - seconds;
	
	// Print result
	Dyn_printResults(end_time_tree, end_time_bubble);
	
}
