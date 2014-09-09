/**
 * Hash Function Double
 * @author Luiz Venturote
 * @param  int table_size Hash table size
 * @param  int code Code
 * @return int Hash code
 */
int HashFunctionDoublue(int table_size, int code) {
	
	return 1 + (code % ( table_size - 1));
	
}

/**
 * re-Hash Function
 * @author Luiz Venturote
 * @param  int table_size Hash table size
 * @param  int code Code
 * @return int New hash code
 */
int reHashing(int table_size, int num1, int num2) {
	
	return (num1 + num2) % table_size;
}

/**
 * DoubleHs_AddHashTable - Add a new item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  struct student std Student struct		 
 * @return int Boolean 
 */
int DoubleHs_AddHashTable(struct student *hash_table, struct student std) {
	
	// Signal to control collisions
	int sign=1, sing_code2=1;
	
	// Get hash code
	int code = HashFunction(HASHTBL_SIZE, std.cod);
	
	// Used for the Double Hash
	int code2=0;
	
	// Start code
	int startCode = code;
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == 0) {
			
			// Add in hash table
			hash_table[code] = std;
			
			// Debug
			printf(" StartHScode=%d - HScode=%d - ItemCod=%d - ItemName=%s\n", startCode, code, std.cod, std.name);
			
			sign=0;
			
		} else {
			if(sing_code2 == 1) {
				code2 = HashFunctionDoublue(HASHTBL_SIZE, std.cod);
				code = reHashing(HASHTBL_SIZE, code, code2);
				sing_code2=0;
			} else {
				code++;
				if(code == (HASHTBL_SIZE-1)) {
					code=0;
				}
			}
		}
		
	}
	
	return 1;
}
 
/**
 * DoubleHs_DeleteHashTable - Delete an item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  struct student std Student struct		 
 * @return int Boolean 
 */
int DoubleHs_DeleteHashTable(struct student *hash_table, struct student std) {
	
	// Signal to control
	int sign=1;
	
	// Get hash code
	int code = HashFunction(HASHTBL_SIZE, std.cod);
	
	// Used for the Double Hash
	int code2=0;
	
	// Start code
	int startCode = code;
	
	while(sign == 1) {
		
		// Check empty index
		if(hash_table[code].cod == std.cod) {
			
			hash_table[code] = getEmptyStudent();
			
			// Debug
			printf(" Deleted: StartHScode=%d - HScode=%d - ItemCod=%d - ItemName=%s\n", startCode, code, std.cod, std.name);
						
			sign=0;
		} else {
			code2 = HashFunctionDoublue(HASHTBL_SIZE, std.cod);
			code = reHashing(HASHTBL_SIZE, code, code2);
		}
		
	}
	
	return 1;
	
}
 
/**
 * DoubleHs_GetHashTableItem - Get a item from the hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 * @param  int cod Student code		 
 * @return struct student Student found 
 */
Student DoubleHs_GetHashTableItem(Student *hash_table, int cod) {
	
	// Signal to control
	int sign=1;
	
	// Get hash code
	int code = HashFunction(HASHTBL_SIZE, cod);
	
	// New student
	Student std = hash_table[code];
	
	// Used for the Double Hash
	int code2=0;
	
	while(sign == 1) {
		
		// Check empty index
		if(std.cod == cod) {	
			return std;
		} else {
			code2 = HashFunctionDoublue(HASHTBL_SIZE, cod);
			code = reHashing(HASHTBL_SIZE, code, code2);
		}
		
		if(code > HASHTBL_SIZE) {
			sign = 0;
		}
		
	}
	
	std = getEmptyStudent();
	
	return std;
	
}

/**
 * Double Hashing
 * @author Luiz Venturote
 */
void DoubleHashing(char * file_name) {
	
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
	
	printf("Hash function: ItemCod mod table_size(%d)\n\n", HASHTBL_SIZE);
	
	// Add
	for (i = 0; i != HASH_ITEN_QTY; i++) {
	    DoubleHs_AddHashTable(&hash_table, *students[i]);
	}
	
	// Colision Test
	Student *colision_student = malloc(sizeof(Student));
	strcpy(colision_student->name, "Ibrahimovic");
	colision_student->cod = 1000;
	DoubleHs_AddHashTable(&hash_table, *colision_student);
	
	Student *colision_student_2 = malloc(sizeof(Student));
	strcpy(colision_student_2->name, "Emanuel");
	colision_student_2->cod = 1000;
	DoubleHs_AddHashTable(&hash_table, *colision_student_2);
	
	// Remove
	DoubleHs_DeleteHashTable(&hash_table, *students[8]);
	
	// Print hash table
	printHashTable(&hash_table);
	
	// Get item from hash table
	Student std = DoubleHs_GetHashTableItem(&hash_table, 1028);
	printf(" Student selected: %s - %d\n\n\n", std.name, std.cod);
	
}

