static int tree_size = 20;
static int tree_nodes = 0;

/**
 * Initialize a new tree
 * @author Luiz Venturote
 * @param int *T Tree
 * @return void
 */
void initTree(int *T) {

	int size = tree_size, i=0;
	
	for(i=0; i<size; i++) {
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
int addNode(int *T, int value) {

	int i=0;
	
	// Increments a node
	tree_nodes++;

	// Check if the tree is empty
	if(T[0] == 0) {
		T[0] = value;
		printf("\nFirst element!\n");
	} else {
		printf("\nelement!\n");
		for(i=0; i<tree_size; i++) {
		
			int left = (i*2)+1;
			int right = (i*2)+2;
			
			printf("\n Left: %d - Right: %d\n", left, right);
		
			// Left
			if( T[left] == 0 && value<T[i] ) {
				T[left] = value;
				printf("\nelement left!\n");
				return 1;	
			} else {
				
				// Right
				if( T[right] == 0 && value>T[i] ) {
					T[right] = value;
					printf("\nelement right!\n");
					return 1;
				}
				
			}
			
		}
	}
	
	return 0;
}

/**
 * Display tree
 * @author Luiz Venturote
 * @param int *T Tree
 * @return void
 */
void printTree(int *T) {
	
	int i=0;
	
	for(i=0; i<tree_size; i++) {
		printf("\\- %d\n", T[i]);
	}
}

/**
 * Initialize sequential binary tree representation
 * @author Luiz Venturote
 * @return void
 */
void BinaryTreeSeq() {
	
	// Initializes a new tree
	int tree[tree_size];
	initTree(tree);
	
	// Print Tree
	printTree(tree);
	
	// Checks if the tree is empty
	printf("\nThe tree is empty? %d\n\n", checkTreeEmpty(tree) );
	
	// Add node
	addNode(tree, 10);
	addNode(tree, 5);
	addNode(tree, 15);
	addNode(tree, 7);
	
	// Print Tree
	printTree(tree);
	
	// Checks if the tree is empty
	printf("\nThe tree is empty? %d\n\n", checkTreeEmpty(tree) );
	
}
