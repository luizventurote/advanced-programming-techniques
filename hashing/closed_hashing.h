// Hash table init size
static int closed_hstable_size = 10;

// Node struct
typedef struct NodeType {
	struct student student;
	struct NodeType *prox;  
} Node;

/**
 * initList - Initializing the linked list
 * @author Luiz Venturote	 
 * @return Node * NULL 
 */
Node * initList() {
	return NULL;
}

/**
 * insertNode - Insert a new node in the linked list
 * @author Luiz Venturote
 * @param  Node *list Linked list
 * @param  Student std Node value 
 * @return Node* New node
 */
Node * insertNode(Node *list, Student std) {
	
	Node *new = (Node*) malloc(sizeof(Node));
	new->student = std;
	new->prox = NULL;
		
	if(list == NULL) {
		list = new;
	} else {
		Node *p;
		for(p=list; p->prox != NULL; p=p->prox);
		p->prox = new;
	}
	
	return list;
	
}

/**
 * removeNode - Remove node in the linked list
 * @author Luiz Venturote
 * @param  Node *list Linked list
 * @param  Student std Node value 
 * @return Node* Node removed
 */
Node * removeNode(Node *list, Student std) {
	
	Node *before = NULL;
	Node *plist = list;
	
	while(plist!=NULL && plist->student.cod != std.cod) {
		before = plist;
		plist = plist->prox;		
	}
	
	if(plist == NULL) {
		return NULL;
	}
	
	if(before == NULL) {
		Node *save_list = plist;
		plist = plist->prox;
		free(save_list);
		return plist;
	} else {
		before->prox = plist->prox;
		free(plist);
		return list;
	}
	
	return NULL;
}

/**
 * getNode - Get a node in the linked list
 * @author Luiz Venturote
 * @param  Node *list Linked list
 * @param  int cod Node code
 * @return Node* Node
 */
Node * getNode(Node *list, int cod) {
	
	if(list == NULL) {
		return NULL;
	} else {
		Node *plist;
		for(plist=list; plist!=NULL && plist->student.cod!=cod; plist=plist->prox);
		
		if(plist == NULL) {
			return NULL;
		} else {
			return plist;
		}
	}
}

/**
 * startClosedHashTable - Start a new hash table with linked list
 * @author Luiz Venturote
 * @param  Node **hash_table Hash table		 
 * @return int Boolean 
 */
int startClosedHashTable(Node **hash_table) {
	
	int i=0;
	
	// Reset all positions
	for(i=0; i<closed_hstable_size; i++) {
	    hash_table[i] = initList();
	}
	
	return 1;
	
}

/**
 * ClosedHs_AddHashTable - Add a new item from the hash table
 * @author Luiz Venturote
 * @param  Node **hash_table Hash table
 * @param  Student std Student struct		 
 * @return int Boolean 
 */
int ClosedHs_AddHashTable(Node **hash_table, Student std) {
	
	// Get hash code
	int code = HashFunction(closed_hstable_size, std.cod);
	
	// Adds the element in the list
	hash_table[code] = insertNode(hash_table[code], std);
	
	printf(" HScode=%d - ItemCod=%d - ItemName=%s\n", code, std.cod, std.name);

	return 1;
}
 
/**
 * ClosedHs_DeleteHashTable - Delete an item from the hash table
 * @author Luiz Venturote
 * @param  Node **hash_table Hash table
 * @param  Student std Student struct		 
 * @return int Boolean 
 */
int ClosedHs_DeleteHashTable(Node **hash_table, Student std) {
	
	// Get hash code
	int code = HashFunction(closed_hstable_size, std.cod);
	
	hash_table[code] = removeNode(hash_table[code], std);
	
	// Debug
	printf(" Deleted: HScode=%d - ItemCod=%d - ItemName=%s\n", code, std.cod, std.name);
	
	return 1;
	
}
 
/**
 * ClosedHs_GetHashTableItem - Get a item from the hash table
 * @author Luiz Venturote
 * @param  Node **hash_table Hash table
 * @param  int cod Student code		 
 * @return struct student Student found 
 */
Student ClosedHs_GetHashTableItem(Node **hash_table, int cod) {
	
	// Get hash code
	int code = HashFunction(closed_hstable_size, cod);
	
	// New student
	Student std = hash_table[code]->student;
	
	if(std.cod != cod) {
		Node *std_node;
		std_node = getNode(hash_table[code], cod);
		return std_node->student;
	}
	
	return std;
	
}

/**
 * ClosedHs_printHashTable - Print hash table with linked list
 * @author Luiz Venturote
 * @param  Node **hash_table Hash table
 */
void ClosedHs_printHashTable(Node **hash_table) {
	
	int i=0;
	
	Node *sub_node;
	
	for(i=0; i<closed_hstable_size; i++) {
		if(hash_table[i] != NULL) {
			printf(" \n %d | %d - %s \n", i, hash_table[i]->student.cod, hash_table[i]->student.name);
			printf(" --------------------------------------------------");
			if(hash_table[i]->prox != NULL) {				
				for(sub_node=hash_table[i]->prox; sub_node != NULL; sub_node=sub_node->prox) {
					printf(" \n   | %d - %s \n", sub_node->student.cod, sub_node->student.name);
					printf(" --------------------------------------------------");
				}
			}
		}
	}
	
	printf("\n\n\n");
	
}

/**
 * Closed Hashing
 * @author Luiz Venturote
 */
void ClosedHashing(char * file_name) {
	
	int i = 0;
	
	// Start students matrix
	Student **students = (Student *) malloc(HASH_ITEN_QTY * sizeof(Student *));
	for (i = 0; i != HASH_ITEN_QTY; i++) {
	    students[i] = malloc(sizeof(Student));
	}
	
	// Load data from file
	loadDataFile(file_name, &*students);
	
	// Start hashing table
	Node **hash_table = (Node *) malloc(closed_hstable_size * sizeof(Node *));
	startClosedHashTable(&*hash_table);
	
	// Add
	for (i = 0; i != HASH_ITEN_QTY; i++) {	    
		ClosedHs_AddHashTable(&*hash_table, *students[i]);
	}
	
	// Remove
	ClosedHs_DeleteHashTable(&*hash_table, *students[0]);
	ClosedHs_DeleteHashTable(&*hash_table, *students[10]);
	
	// Print hash table
	ClosedHs_printHashTable(&*hash_table);
	
	// Get item from hash table
	Student std = ClosedHs_GetHashTableItem(&*hash_table, 1028);
	printf(" Student selected: %s - %d\n\n\n", std.name, std.cod);
	
}

