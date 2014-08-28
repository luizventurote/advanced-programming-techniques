// Hash table init size
static int open_hstable_size = 100;

/**
 * startOpenHashTable - Start a new hash table
 * @author Luiz Venturote
 * @param  Student *hash_table Hash table		 
 * @return int Boolean 
 */
int startOpenHashTable(Student *hash_table) {
	
	int i=0;
	
	// Reset all positions
	for(i=0; i<open_hstable_size; i++) {
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
	Student *hash_table = (Student *) malloc(open_hstable_size * sizeof(Student));	
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
	int old_size = open_hstable_size;
	
	// Swap Hash
	Student helper_table[open_hstable_size];
	
	// Save datas
	for(i=0; i<open_hstable_size; i++) {
		helper_table[i] = hash_table[i];
	}
	
	// Increases the size of the table
	open_hstable_size *= 2;
	
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
	
	static int load_factor = 0;
	
	static int index = 0;
	
	// Signal to control collisions
	int sign=1;
	
	// Get hash code
	int code = HashFunction(open_hstable_size, std.cod);
	
	// Start code
	int startCode = code;
	
	// Hash table old size
	int open_hstable_size_old = open_hstable_size;
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == 0) {
			
			// Check load factor
			if( load_factor > (open_hstable_size * 0.6)) {
				printf("\n========================================\n");
				printf(" Exampd table active (open_hstable_size_old: %d - open_hstable_size: %d - load_factor: %d)", open_hstable_size_old, open_hstable_size*2, load_factor);
				printf("\n========================================\n");
				load_factor = 0;
				index=0;
				OpenHs_expandHashTable(hash_table);
				code = HashFunction(open_hstable_size, std.cod);
			}
			
			// Add in hash table
				hash_table[code] = std;
				load_factor++;
				
			// Debug
			printf(" %d - StartHScode=%d - HScode=%d - ItemCod=%d - ItemName=%s\n", index, startCode, code, std.cod, std.name);
			index++;
			
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
	int code = HashFunction(open_hstable_size, std.cod);
	
	// Start code
	int startCode = code;
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == std.cod) {
			hash_table[code] = getEmptyStudent();
			printf(" Deleted: StartHScode=%d - HScode=%d - ItemCod=%d - ItemName=%s\n", startCode, code, std.cod, std.name);			
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
	int code = HashFunction(open_hstable_size, cod);
	
	// New student
	Student std = hash_table[code];
	
	while(sign == 1) {
		
		// Check empty index
		if(std.cod == cod) {
			return std;
		} else {
			code++;
		}
		
		if(code > open_hstable_size) {
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
	
	// Debug
	printf("\n========================================\n");
	printf(" Print table (open_hstable_size: %d)", open_hstable_size);
	printf("\n========================================\n");
	
	int i=0;
	
	for(i=0; i<open_hstable_size; i++) {
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
	for (i = 0; i != HASH_ITEN_QTY; i++) {
	    OpenHs_AddHashTable(hash_table, *students[i]);
	}
	
	// Colision Test
	Student *colision_student = malloc(sizeof(Student));
	strcpy(colision_student->name, "Ibrahimovic");
	colision_student->cod = 1000;
	OpenHs_AddHashTable(hash_table, *colision_student);
	
	Student *colision_student_2 = malloc(sizeof(Student));
	strcpy(colision_student_2->name, "Emanuel");
	colision_student_2->cod = 1000;
	OpenHs_AddHashTable(hash_table, *colision_student_2);
	
	// Remove
	OpenHs_DeleteHashTable(hash_table, *students[6]);
	OpenHs_DeleteHashTable(hash_table, *students[9]);
	
	// Print hash table
	OpenHs_printHashTable(hash_table);
	
	// Get item from hash table
	Student std = OpenHs_getHashTableItem(hash_table, 1197);
	printf(" Student selected: %s - %d\n\n\n", std.name, std.cod);
	
}

