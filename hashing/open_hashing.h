// Hash table init size
static int hstable_size = HASHTBL_SIZE;

/**
 * startOpenHashTable - Start a new hash table
 * @author Luiz Venturote
 * @param  Student *hash_table Hash table		 
 * @return int Boolean 
 */
int startOpenHashTable(Student *hash_table) {
	
	int i=0;
	
	// Reset all positions
	for(i=0; i<hstable_size; i++) {
		hash_table[i] = getEmptyStudent();	
	}
	
	return 1;
	
}

/**
 * OpenHs_getHashTable - Get a new hash table
 * @author Luiz Venturote	 
 * @return Student* Hash table 
 */
Student* OpenHs_getHashTable() {
	Student *hash_table = (Student *) malloc(hstable_size * sizeof(Student));	
	startOpenHashTable(hash_table);
	return hash_table;
}

/**
 * OpenHs_expandHashTable - Expand hash table
 * @author Luiz Venturote	 
 * @return void
 */
void OpenHs_expandHashTable(Student *hash_table) {
	
	int i=0;
	
	// Old hash table size
	int old_size = hstable_size;
	
	// Swap Hash
	Student helper_table[hstable_size];
	
	// Save datas
	for(i=0; i<hstable_size; i++) {
		helper_table[i] = hash_table[i];
	}
	
	// Increases the size of the table
	hstable_size *= 2;
	
	// Frees memory
	free(hash_table);
	
	// Allocate a larger memory space
	hash_table = OpenHs_getHashTable();
	
	// Adds data into the new table
	for(i=0; i<old_size; i++) {
		if(helper_table[i].cod != 0) {
			OpenHs_AddHashTable(hash_table, helper_table[i]);
		}			
	}
	
}

/**
 * OpenHs_AddHashTable - Add a new item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  struct student std Student struct		 
 * @return int Boolean 
 */
int OpenHs_AddHashTable(Student *hash_table, struct student std) {
	
	static int load_factor  = 0;
	
	// Signal to control collisions
	int sign=1;
	
	// Get hash code
	int code = HashFunction(hstable_size, std.cod);
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == 0) {
			
			// Check load factor
			if( load_factor > (hstable_size * 0.6)) {
				load_factor = 0;
				OpenHs_expandHashTable(hash_table);
				code = HashFunction(hstable_size, std.cod);
			}
			
			// Add in hash table
				hash_table[code] = std;
				load_factor++;
			
			sign=0;
		} else {
			code++;
		}
		
	}
	
	return 1;
}

/**
 * OpenHs_DeleteHashTable - Delete an item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  struct student std Student struct		 
 * @return int Boolean 
 */
int OpenHs_DeleteHashTable(Student *hash_table, struct student std) {
	
	// Signal to control
	int sign=1;
	
	// Get hash code
	int code = HashFunction(hstable_size, std.cod);
	
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
 * OpenHs_getHashTableItem - Get a item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  int cod Student code		 
 * @return struct student Student found 
 */
Student OpenHs_getHashTableItem(Student *hash_table, int cod) {
	
	// Signal to control
	int sign=1;
	
	// Get hash code
	int code = HashFunction(hstable_size, cod);
	
	// New student
	Student std = hash_table[code];
	
	while(sign == 1) {
		
		// Check empty index
		if(std.cod == cod) {
			return std;
		} else {
			code++;
		}
		
		if(code > hstable_size) {
			sign = 0;
		}
		
	}
	
	std = getEmptyStudent();
	
	return std;
	
}

/**
 * OpenHs_printHashTable - Print hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 */
void OpenHs_printHashTable(Student *hash_table) {
	
	int i=0;
	
	for(i=0; i<hstable_size; i++) {
		printf(" \n %d | %d - %s \n", i, hash_table[i].cod, hash_table[i].name);
		printf(" --------------------------");
	}
	
	printf("\n\n\n");
	
}

/**
 * Open Hashing
 * @author Luiz Venturote
 */
void OpenHashing(char * file_name) {
	
	int i = 0;
	
	// Start students matrix
	Student **students = (Student *) malloc(HASH_ITEN_QTY * sizeof(Student *));
	for (i = 0; i != HASH_ITEN_QTY; i++) {
	    students[i] = malloc(sizeof(Student));
	}
	
	// Load data from file
	loadDataFile(file_name, &*students);
	
	// Start hashing table
	Student *hash_table = OpenHs_getHashTable();
	
	// Add
	OpenHs_AddHashTable(hash_table, *students[5]);
	OpenHs_AddHashTable(hash_table, *students[1]);
	OpenHs_AddHashTable(hash_table, *students[8]);
	OpenHs_AddHashTable(hash_table, *students[10]);
	OpenHs_AddHashTable(hash_table, *students[0]);
	OpenHs_AddHashTable(hash_table, *students[6]);
	OpenHs_AddHashTable(hash_table, *students[9]);
	
	// Remove
	OpenHs_DeleteHashTable(hash_table, *students[6]);
	OpenHs_DeleteHashTable(hash_table, *students[9]);
	
	// Print hash table
	OpenHs_printHashTable(hash_table);
	
	// Get item from hash table
	Student std = LinearHs_getHashTableItem(hash_table, 6);
	printf(" Student selected: %s - %d\n\n\n", std.name, std.cod);
	
}

