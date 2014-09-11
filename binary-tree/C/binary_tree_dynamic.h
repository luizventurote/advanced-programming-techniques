// Node struct
typedef struct node {
	struct node* left;
	Student student;
	struct node* right;
} Node;

/**
 * Initialize a new tree
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return void
 */
void Dyn_initTree(Node *tree) {
	tree = NULL;
}

/**
 * Checks if the tree is empty
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return int empty tree or not
 */
int Dyn_checkEmptyTree(Node *tree) {
	return (tree == NULL);
}

/**
 * Add new Node in the tree
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @param int value Node integer value
 * @return int Yes or no
 */
int Dyn_addNode(Node *tree, int value) {
	return 0;
}

/**
 * Initialize dynamic binary tree representation
 * @author Luiz Venturote
 * @return void
 */
void BinaryTreeDyn() {
	
	printf("Initialize dynamic binary tree representation!\n");
	
	// Tree
	Node *tree = (Node*) malloc( sizeof(Node) );
	
	// Init
	Dyn_initTree(tree);
	
	// Check if the tree is empty
	printf("\n %d", Dyn_checkEmptyTree(tree) );
	
	// Add new node
	Dyn_addNode(tree, 10);
	Dyn_addNode(tree, 5);
	Dyn_addNode(tree, 20);
	
}
