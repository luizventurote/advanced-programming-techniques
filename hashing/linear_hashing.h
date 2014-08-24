/**
 * LinearHs_AddHashTable - Add a new item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  struct student std Student struct		 
 * @return int Boolean 
 */
int LinearHs_AddHashTable(struct student *hash_table, struct student std) {
	
	// Signal to control collisions
	int sign=1;
	
	// Get hash code
	int code = HashFunction(HASHTBL_SIZE, std.cod);
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == 0) {
			// Add in hash table
			hash_table[code] = std;
			sign=0;
		} else {
			code++;
		}
		
	}
	
	return 1;
}

/**
 * LinearHs_DeleteHashTable - Delete an item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  struct student std Student struct		 
 * @return int Boolean 
 */
int LinearHs_DeleteHashTable(struct student *hash_table, struct student std) {
	
	// Signal to control
	int sign=1;
	
	// Get hash code
	int code = HashFunction(HASHTBL_SIZE, std.cod);
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == std.cod) {
			hash_table[code] = getEmptyStudent();			
			sign=0;
		} else {
			code++;
		}
		
	}
	
	return 1;
	
}

/**
 * LinearHs_getHashTableItem - Get a item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  int cod Student code		 
 * @return struct student Student found 
 */
Student LinearHs_getHashTableItem(Student *hash_table, int cod) {
	
	// Signal to control
	int sign=1;
	
	// Get hash code
	int code = HashFunction(HASHTBL_SIZE, cod);
	
	// New student
	Student std = hash_table[code];
	
	while(sign == 1) {
		
		// Check empty index
		if(std.cod == cod) {
			return std;
		} else {
			code++;
		}
		
		if(code > HASHTBL_SIZE) {
			sign = 0;
		}
		
	}
	
	std = getEmptyStudent();
	
	return std;
	
}

/**
 * Linear Hashing
 * @author Luiz Venturote
 */
void linearHashing(char * file_name) {
	
	int i = 0;
	
	// Start students matrix
	Student **students = (Student *) malloc(HASH_ITEN_QTY * sizeof(Student *));
	for (i = 0; i != HASH_ITEN_QTY; i++) {
	    students[i] = malloc(sizeof(Student));
	}
	
	// Load data from file
	loadDataFile(file_name, &*students);
	
	// Start hashing table
	HashTable hash_table;
	startHashTable(&hash_table);
	
	// Add
	LinearHs_AddHashTable(&hash_table, *students[5]);
	LinearHs_AddHashTable(&hash_table, *students[1]);
	LinearHs_AddHashTable(&hash_table, *students[8]);
	LinearHs_AddHashTable(&hash_table, *students[10]);
	
	// Remove
	LinearHs_DeleteHashTable(&hash_table, *students[8]);
	
	// Print hash table
	printHashTable(&hash_table);
	
	// Get item from hash table
	Student std = LinearHs_getHashTableItem(&hash_table, 6);
	printf(" Student selected: %s - %d\n\n\n", std.name, std.cod);
	
}

