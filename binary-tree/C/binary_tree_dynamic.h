// Node struct
typedef struct node {
	struct node* left;
	int value;
	struct node* right;
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
			if( (*tree)->left == NULL ){
				(*tree)->left = new_node;                 
			} else {
				Dyn_insertNode( &(*tree)->left, new_node);       
			}
			        
		} else {
			
			// Insert in right
			if ((*tree)->right == NULL){
				(*tree)->right = new_node;               
			} else {
				Dyn_insertNode( &(*tree)->right, new_node);       
			}
			
		}  
		
	} else {
		(*tree) = new_node;   
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
		printf("  %d  ", tree->value);
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
		printf("  %d  ", tree->value);
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
		printf("  %d  ", tree->value);
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
    
    printf("  %d  ", tree->value);
    
    Dyn_printDescendingOrder(tree->left);
	
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
	Dyn_addNode(&tree, 10);
	Dyn_addNode(&tree, 5);
	Dyn_addNode(&tree, 20);
	Dyn_addNode(&tree, 1);
	Dyn_addNode(&tree, 8);
	Dyn_addNode(&tree, 15);
	Dyn_addNode(&tree, 18);
	Dyn_addNode(&tree, 11);
	Dyn_addNode(&tree, 3);
	
	Dyn_displayTree(tree);
	
	// Search node
	Node *node_found = Dyn_searchNode(tree, 20);
	printf("\n\n Node found: %d\n", node_found->value);
	
	// Node Height
	printf(" Node found height: %d \n", Dyn_heightNode(node_found) );
	
	// Node Lvel
	printf(" Node found level: %d \n\n", Dyn_levelNode(tree, node_found->value) );
	
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
