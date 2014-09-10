#define TREE_SIZE 20

/**
 * Initialize a new tree
 * @author Luiz Venturote
 * @param int *T Tree
 * @return void
 */
void initTree(int *T) {

	int tree_size = TREE_SIZE, i=0;
	
	for(i=0; i<tree_size; i++) {
		T[i] = 0;	
	}
	
}

/**
 * Checks if the tree is empty
 * @author Luiz Venturote
 * @param int *T Tree
 * @return int Yes or No
 */
int checkTreeEmpty(int *T) {
	return (*T == 0);
}

/**
 * Add a new Node
 * @author Luiz Venturote
 * @param int *T Tree
 * @param int value Node value
 * @return int Yes or No
 */
int addNode(int *T, int value) {}

/**
 * Initialize sequential binary tree representation
 * @author Luiz Venturote
 * @return void
 */
void BinaryTreeSeq() {
	
	int i=0;
	
	// Initializes a new tree
	int tree[TREE_SIZE];
	initTree(tree);
	
	for(i=0; i<TREE_SIZE; i++) {
		printf("- %d\n", tree[i]);
	}
	
	// Checks if the tree is empty
	printf("%d\n", checkTreeEmpty(tree) );
	
}
