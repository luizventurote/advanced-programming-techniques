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
Node* searchNode(Node *tree, int value){
   if (tree == NULL) {
       return NULL;      
   } else if (tree->value == value){
       return tree;   
   } else if (tree->value > value){
       return (searchNode(tree->left, value));
   } else {
       return (searchNode(tree->right, value));       
   } 
}

/**
 * Get node max depth
 * @author Luiz Venturote
 * @param Node **node Node
 * @param int depth Depth
 * @return int Depth
 */
int getNodeMaxDepth(Node *node, int depth) {
	int ld, rd;
	if (node==NULL) { return depth-1; }
	ld = getNodeMaxDepth(node->left, depth+1);
	rd = getNodeMaxDepth(node->right, depth+1);
	return (ld<rd) ? rd : ld;
}

int heightNode(Node *tree)
{
	if(!tree)
		return 0;
	else
	{
		int left  = heightNode(tree->left);
		int right = heightNode(tree->right);
		if(left >= right)
			return left + 1;
		else
			return right + 1;
	}
}

/**
 * Display the tree
 * @author Luiz Venturote
 * @param Node **tree Binary Tree
 * @return void
 */
#define pow2(n) (1 << (n))
void Dyn_printTree(Node *root) {
	char fmt[9];
	Node **row1, **row2, **rowTemp;
	int rows, row, col;
	
	if (root==NULL) { return; }

	rows = getNodeMaxDepth(root, 1);
	row1 = malloc(sizeof(Node*) * pow2(rows));
	row2 = malloc(sizeof(Node*) * pow2(rows));
	row1[0] = root;
	for(row=0; row<rows; row++) {
		int col2 = 0, cols = pow2(row);
		sprintf(fmt,"%%%dc", pow2(rows-(row+1)));
		for(col=0; col<cols; col++) {
			Node *node = row1[col];
			if (node!=NULL) {
				printf(" %d ", node->value);
				row2[col2++] = node->left;
				row2[col2++] = node->right;
			} else {
				printf(fmt, ' ');
				row2[col2++] = NULL;
				row2[col2++] = NULL;
			}
			if (col==0) { sprintf(fmt,"%%%dc", pow2(rows-(row+0))); }
		}
		printf("\n");
		rowTemp = row1;
		row1=row2;
		row2=rowTemp;
	}
	free(row1);
	free(row2);
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
	Dyn_addNode(&tree, 9);
	Dyn_addNode(&tree, 12);
	Dyn_addNode(&tree, 16);
	
	// Print the tree
	Dyn_printTree(tree);
	
	// Search node
	Node *node_found = searchNode(tree, 8);
	printf("\n\n Node found: %d\n", node_found->value);
	
	// Node Height
	printf(" Node found height: %d \n\n", heightNode(node_found) );
	
	// Tree Depth
	printf(" Tree max depth: %d \n\n", getNodeMaxDepth( tree, 1) );
	
}
