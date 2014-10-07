static int tree_size = 31;
static int sqt_sing = 0;

// Node struct
typedef struct node_stc {
	int left_pos;
	struct node_stc * left;
	int value;
	int right_pos;
	struct node_stc * right;
	int level;
	int fb;
} Node_Stc;


/**
 * Initialize a new tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Tree
 * @return void
 */
void Sqt_initTree(Node_Stc *tree) {

	int i=0, j=0, aux=0, next_val=0, level=0;
	
	for(i=0; i<tree_size; i++) {
		
		// Node value
		tree[i].value = -1;	
		
		// Balanced factor
		tree[i].fb = 0;
		
		// Lenf and Right position calc
		tree[i].left_pos = (i*2)+1;
		tree[i].right_pos = (i*2)+2;
		
		// Left position
		if( tree[i].left_pos >= tree_size ) {
			tree[i].left = NULL;
		} else {
			tree[i].left = &tree[ tree[i].left_pos ];	
		}
		
		// Right position
		if( tree[i].right_pos >= tree_size ) {
			tree[i].right = NULL;
		} else {
			tree[i].right = &tree[ tree[i].right_pos ];	
		}
		
		// Level calc
		tree[i].level = level;
		switch(level) {
			case 0:
				level++;
				next_val++;	
				break;
			case 1:
				if(aux == 0) {
					aux = 1;
				} else {
					next_val = 6;	
					aux++;
					level++;
				}
				break;
			default:
				if(i==next_val) {					
					aux++;
					next_val = (int) next_val+pow(2.0, aux);
					level++;	
				}
				break;
		}

	}
	
}


/**
 * Update subtree
 * @author Luiz Venturote
 * @param Node_Stc *tree Tree
 * @return void
 */
void updateSubTree(Node_Stc *sub_tree) {
	
	if(sub_tree != NULL) {
		
		if(sub_tree->left != NULL) {	
			
			if(sub_tree->left->left != NULL) {
				
				sub_tree->left->value = sub_tree->left->left->value;
				
			} else {
				sub_tree->left->value = -1;
			}	
			
			updateSubTree(sub_tree->left);	
			
		}
		
		if(sub_tree->right != NULL) {
			
			if(sub_tree->right->right != NULL) {
				
				sub_tree->right->value 	= sub_tree->right->right->value;

			} else {
				sub_tree->right->value = -1;
			}	
			
			updateSubTree(sub_tree->right);
			
		}
	}
	
}


/**
 * Right rotation
 * @author Luiz Venturote
 * @param Node *A Binary Tree
 * @return Node*
 */
void Sqt_rightRotation(Node_Stc *A) {
	
	Node_Stc *B = A->left; 
          
    // Single Rotation
	if (B->fb == -1) {  
	
		// Node A
		int A_value = A->value;
		int A_left_value = A->left->value;
		int A_right_value = A->right->value;
		
		// Node B
		int B_value = B->value;
		int B_left_value = B->left->value;
		int B_right_value = B->right->value;
		
		// Node C
		Node_Stc *C = B->left;
		int C_value = C->value;
		
		int C_left_value = -1;
		if(C->left != NULL) {
			C_left_value = C->left->value;
		}
			
		int C_right_value = -1;
		if(C->right != NULL) {
			C_right_value = C->right->value;
		}
		
		int C_fb = C->fb;
		
		A->value = B_value;
		A->right->value = A_value;
		A->left->value = C_value;
			
		B->left->value = C_left_value;
		B->right->value = C_right_value;
			
		A->right->left->value = B_right_value;
		A->right->right->value = A_right_value;
   
		A->fb = 0; 
		B->fb = C_fb;
		
		C->fb = 0;
		
		updateSubTree(C);
    	
     } 
	 
	 // Double Rotation
	 else { 
	 
		// Node A
		int A_value = A->value;
		int A_left_value = A->left->value;
		int A_right_value = A->right->value;
		
		// Node B
		int B_value = B->value;
		int B_left_value = B->left->value;
		int B_right_value = B->right->value;
	
		if( B->right->value != -1 ) {
			
			// Node C
			Node_Stc *C = B->right;
			int C_value = C->value;
			
			int C_left_value = -1;
			if(C->left != NULL) {
				C_left_value = C->left->value;
			}
			
			int C_right_value = -1;
			if(C->right != NULL) {
				C_right_value = C->right->value;
			}
			
			A->value = C_value;
			A->right->value = A_value;
			A->left->value = B_value;
			
			B->right->value = C_left_value;
			
			A->left->left->value = C_right_value;
			A->left->right->value = A_right_value;

			if (C->fb == -1){ 
				A->fb = 1; 
			} else {
				A->fb = 0;	
			}
			    
			if (C->fb == 1){ 
				B->fb = -1; 
			} else {
				B->fb = 0;
			} 
			
			updateSubTree(C);
			
		 }
	 }
     
	 A->fb = 0; 
     sqt_sing = 0;
     
}


/**
 * Left rotation
 * @author Luiz Venturote
 * @param Node *A Binary Tree
 * @return Node*
 */ 
void Sqt_leftRotation(Node_Stc *A) {

   Node_Stc *B = A->right; 
   
   // Single Rotation
   if(B->fb == 1) { 
   
		// Node A
		int A_value = A->value;
		int A_left_value = A->left->value;
		int A_right_value = A->right->value;
		
		// Node B
		int B_value = B->value;
		int B_left_value = B->left->value;
		int B_right_value = B->right->value;
		
		// Node C
		Node_Stc *C = B->right;
		int C_value = C->value;
		
		int C_left_value = -1;
		if(C->left != NULL) {
			C_left_value = C->left->value;
		}
			
		int C_right_value = -1;
		if(C->right != NULL) {
			C_right_value = C->right->value;
		}
		
		int C_fb = C->fb;
		
		A->value = B_value;
		A->left->value = A_value;
		A->right->value = C_value;
		
		B->left->value = C_left_value;
		B->right->value = C_right_value;
		
		A->left->left->value = A_left_value;
		A->left->right->value = B_left_value;
   
		A->fb = 0; 
		B->fb = C_fb;
		
		updateSubTree(C);
       
   }
   
	// Double Rotation
	else {
		
		// Node A
		int A_value = A->value;
		int A_left_value = A->left->value;
		int A_right_value = A->right->value;
		
		// Node B
		int B_value = B->value;
		int B_left_value = B->left->value;
		int B_right_value = B->right->value;
		
		if( B->left->value != -1 ) {

			// Node C
			Node_Stc *C = B->left;
			int C_value = C->value;
			
			int C_left_value = -1;
			if(C->left != NULL) {
				C_left_value = C->left->value;
			}
			
			int C_right_value = -1;
			if(C->right != NULL) {
				C_right_value = C->right->value;
			}
			
			A->value = C_value;
			A->left->value = A_value;
			A->right->value = B_value;
			
			B->left->value = C_right_value;
			B->right->value = B_right_value;
			
			A->left->left->value = A_left_value;
			A->left->right->value = C_left_value;
		   
			if (C->fb == 1) {
				A->fb = -1; 
			} else {
				A->fb = 0; 
			}

			if (C->fb == -1) { 
		 		B->fb = 1; 
			} else {
				B->fb = 0;	
			} 
			
			updateSubTree(C);
			
	    }
	    
	}
    
	A->fb = 0; 
	sqt_sing = 0;
	 
}
 

/**
 * Add a new Node
 * @author Luiz Venturote
 * @param Node_Stc *tree Tree
 * @param int value Node value
 * @return void
 */
void Sqt_addNode(Node_Stc *tree, int value) {
		
	// Create a new node
	Node_Stc new_node;
	new_node.value = value;
	
	// Insert the node in the tree
	Sqt_insertNode( tree, new_node);   
	
}


/**
 * Insert node in the tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Tree
 * @param Node_Stc new_node Node
 * @return void
 */
void Sqt_insertNode(Node_Stc *tree, Node_Stc new_node) {

	if( tree != NULL && tree->value != -1) {

		if ( tree->value > new_node.value ) {
			
			// Insert in left
			if(tree->left != NULL) {
				
				Sqt_insertNode( tree->left, new_node); 
				if (sqt_sing == 1) { 
					switch ( tree->fb ) {    
						case 1 : 
							tree->fb = 0; 
							sqt_sing = 0; 
							break; 
						case 0 : 
							tree->fb = -1; 
							break; 
	                    case -1 : 
							Sqt_rightRotation(tree); 
							break; 
	            	}
	            }
            
            }
			
			 
		} else {
			
			// Insert in right
			if( tree->right != NULL) {
				Sqt_insertNode( tree->right, new_node); 
	            if (sqt_sing == 1){ 
					switch (tree->fb)    {   
						case -1 : 
							tree->fb = 0; 
							sqt_sing = 0; 
							break; 
						case 0 : 
							tree->fb = 1; 
							break; 
	                    case 1 : 
							Sqt_leftRotation(tree); 
							break;     
	                }
	            }
        	}
						
		} 
		
	} else {
		tree->value = new_node.value;
		sqt_sing = 1;
	} 
}


/**
 * Node height
 * @author Luiz Venturote
 * @param Node_Stc *tree Tree or node
 * @return int Node height
 */
int Sqt_getNodeHeight(Node_Stc *tree) {

	return Sqt_heightNode(tree) - 1;
		
}

int Sqt_heightNode(Node_Stc *tree) {

	if(tree == NULL || tree->value == -1) 
		return 0;
	else
		return max(Sqt_heightNode(tree->left), Sqt_heightNode(tree->right)) +1;
		
}


/**
 * The tree is balanced?
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return int Yes or No
 */
int Sqt_isBalanced(Node_Stc *tree) {
	
	int lh; // for height of left subtree
	int rh; // for height of right subtree
 
	// If tree is empty then return true
	if(tree == NULL || tree->value == -1)
		return 1; 
 
	// Get the height of left and right sub trees
	lh = Sqt_heightNode(tree->left);
	rh = Sqt_heightNode(tree->right);
   
	//printf("\n Node: %d - lh: %d - rh: %d\n", tree->value, lh, rh);
 
	if( abs(lh-rh) <= 1 && Sqt_isBalanced(tree->left) && Sqt_isBalanced(tree->right))
		return 1;
 
	/* If we reach here then tree is not height-balanced */
	return 0;
}


/**
 * Display the tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return void
 */
void Sqt_displayTree(Node_Stc *tree){
     Sqt_printTree( tree, 2, 40, 40);     
}


/**
 * Print tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @param int line
 * @param int column
 * @param int rate
 * @return void
 */
void Sqt_printTree(Node_Stc *tree, int line, int column, int rate){
     if (tree != NULL){
       if ((line < 25) && (column <= 80) && (column > 0)){    
           Sqt_gotoxy(column,line);
           if( tree->value != -1 )
           printf("<%d>",tree->value, tree->fb);
           else
           printf("<>");
           rate = rate /2;
           Sqt_printTree(tree->left,line+2,column-rate, rate);
           Sqt_printTree(tree->right, line+2,column+rate, rate);      
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
void Sqt_gotoxy(int column, int linha) { 
	COORD point; 
	point.X = column; point.Y = linha; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point); 
}


/**
 * Debug tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return void
 */
void Sqt_debugTree(Node_Stc *tree) {
	
	if( tree != NULL ) {
		printf("\n\n Node: %d - bf: %d - level: %d ", tree->value, tree->fb, tree->level);
		
		if(tree->left != NULL) {
			printf("| Left: %d ", tree->left->value);
		}
		
		if(tree->right != NULL) {
			printf("| Right: %d ", tree->right->value);
		}
	}
	
	if(tree->left != NULL) {
		Sqt_debugTree(tree->left);
	}
	
	if(tree->right != NULL) {
		Sqt_debugTree(tree->right);
	}
	
}


/**
 * Print tree - Preorder
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return void
 */
void Sqt_printPreorder(Node_Stc *tree) {
	
	if( tree != NULL && tree->value != -1 ) {
		printf("  %d  ", tree->value);
	}
	
	if( tree->left != NULL) {
		Sqt_printPreorder(tree->left);
	}
	
	if( tree->right != NULL) {
		Sqt_printPreorder(tree->right);
	}
	
}


/**
 * Print tree - Inorder
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return void
 */
void Sqt_printInorder(Node_Stc *tree) {
	
	if( tree->left != NULL) {
		Sqt_printInorder(tree->left);
	}
	
	if( tree != NULL && tree->value != -1 ) {
		printf("  %d  ", tree->value);
	}
	
	if( tree->right != NULL) {
		Sqt_printInorder(tree->right);
	}
	
}


/**
 * Print tree - Postorder
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return void
 */
void Sqt_printPostorder(Node_Stc *tree) {
	
	if( tree->left != NULL) {
		Sqt_printPostorder(tree->left);
	}
	
	if( tree->right != NULL) {
		Sqt_printPostorder(tree->right);
	}
	
	if( tree != NULL && tree->value != -1 ) {
		printf("  %d  ", tree->value);
	}
	
}


/**
 * Print tree - Descending Order
 * @author Luiz Venturote
 * @param Node *tree Binary Tree
 * @return void
 */
void Sqt_printDescendingOrder(Node_Stc *tree) {
	
	if(tree == NULL) {
		return;
	}
    
    Sqt_printDescendingOrder(tree->right);
    
    if(tree->value != -1) {
   		printf("  %d  ", tree->value);	
    }
    
    Sqt_printDescendingOrder(tree->left);
	
}

/**
 * Search node in the tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @param int value Node value
 * @return Node_Stc
 */
Node_Stc* Sqt_searchNode(Node_Stc *tree, int value) {
   if (tree == NULL) {
       return NULL;      
   } else if (tree->value == value){
       return tree;   
   } else if (tree->value > value){
       return (Sqt_searchNode(tree->left, value));
   } else {
       return (Sqt_searchNode(tree->right, value));       
   } 
}


/**
 * Number of nodes
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return int qty
 */
int Sqt_NodeQty(Node_Stc *tree) {
	
	if(tree == NULL || tree->value == -1) {
		return 0;
	}
	
	int nL = Sqt_NodeQty(tree->left); 
	int nR = Sqt_NodeQty(tree->right); 
	
	return (nL + nR + 1); 
}

int Sqt_getNodeQty(Node_Stc *tree) {
	return Sqt_NodeQty(tree) - 1;
}


/**
 * The tree is perfect balanced?
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return int Yes or No
 */
int Sqt_isPerfectBalanced(Node_Stc *tree) {
	
	int lnq; // for qty of the nodes of left bubtree
	int rnq; // for qty of the nodes of right subtree
 
	// If tree is empty then return true
	if(tree == NULL || tree->value == -1) {
		return 1; 
	} 
		
	// Get the node qty of left and right sub trees
	lnq = Sqt_NodeQty(tree->left);
	rnq = Sqt_NodeQty(tree->right);
 
	if( abs(lnq-rnq) <= 1 && Sqt_isPerfectBalanced(tree->left) && Sqt_isPerfectBalanced(tree->right)) {
		return 1;
	}
 
	return 0;
}


/**
 * strictly binary tree
 * @author Luiz Venturote
 * @param Node_Stc *tree Binary Tree
 * @return int Yes or No
 */
int Sqt_is2Tree(Node_Stc *tree) {

	if(tree) {
		
		if( (tree->right) && (tree->left) ) {
			
			if( ( (tree->right->value == -1)&&(tree->left->value != -1) ) || ( (tree->right->value != -1)&&(tree->left->value == -1) ) ) {
	        	return 0;	
	        } else {
		    	return Sqt_is2Tree(tree->left) && Sqt_is2Tree(tree->right);
			}
			
		}
		
		return 1;
		
    }
    
    return 1;
	
}


/**
 * Swap node values
 * @author Luiz Venturote
 * @param Node_Stc *node_1
 * @param Node_Stc *node_2
 * @return void
 */
void Sqt_swapNodeValues(Node_Stc *node_1, Node_Stc *node_2) {

	// Node buffer
	Node_Stc node_buf;
	
	// Save values
	node_buf.value = node_1->value;
	
	// Swap node values
	node_1->value 	= node_2->value;
	node_2->value	= node_buf.value;
	
}


/**
 * Initialize sequential binary tree representation
 * @author Luiz Venturote
 * @return void
 */
void BinaryTreeSeq() {
	
	// Initializes a new tree
	Node_Stc tree[tree_size];
	Sqt_initTree(tree);
	
	// Adds nodes
	Sqt_addNode(tree, 100);
	Sqt_addNode(tree, 50);
	Sqt_addNode(tree, 150);
	Sqt_addNode(tree, 25);
	Sqt_addNode(tree, 35);
	Sqt_addNode(tree, 15);
	Sqt_addNode(tree, 10);
	Sqt_addNode(tree, 5);
	Sqt_addNode(tree, 3);
	Sqt_addNode(tree, 2);
	
	Sqt_displayTree(tree);
	
	// Search node
	Node_Stc *node_found = Sqt_searchNode(tree, tree->value);
	printf("\n\n\n\n Node: %d\n", node_found->value);
	
	// Node Height
	printf(" Height: %d \n", Sqt_getNodeHeight(node_found) );
	
	// Node Lvel
	printf(" Level: %d \n", node_found->level );
	
	// Node qty
	printf(" Node qty: %d \n\n", Sqt_getNodeQty(node_found) );
	
	// Is perfectly balanced
	printf(" Arvore perfeitamente balanceada: %d \n\n", Sqt_isPerfectBalanced(node_found) );
	
	// Is strictly
	printf(" Arvore Estritamente binaria: %d \n\n", Sqt_is2Tree(node_found) );
	
	// Print tree - Preorder 
	printf(" Preorder:");
	Sqt_printPreorder(tree);
	printf("\n\n");
	
	// Print tree - Inorder 
	printf(" Inorder:");
	Sqt_printInorder(tree);
	printf("\n\n");
	
	// Print tree - Postorder 
	printf(" Postorder:");
	Sqt_printPostorder(tree);
	printf("\n\n");
	
	// Print tree - Descending Order 
	printf(" Descending Order:");
	Sqt_printDescendingOrder(tree);
	printf("\n\n");
	
}
