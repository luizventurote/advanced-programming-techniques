// Hash table size
#define HASHTBL_SIZE 511

// Quantity of items of the hash table
#define HASH_ITEN_QTY 200

// Student struct
typedef struct student {
  int 	cod;
  char  name[100];
  int 	phone;
  char 	email[100];
  char 	address[100];
} Student;

// Hashing struct
typedef struct hashing_table {
  Student students[HASHTBL_SIZE];
} HashTable;

/**
 * Get a empty student
 * @author Luiz Venturote
 * @return struct student New student
 */
struct student getEmptyStudent() {
	
	struct student std;
	
	std.cod = 0;
	strcpy(std.name, "");
	std.phone = 0;
	strcpy(std.email, "");
	strcpy(std.address, "");
	
	return std;
}

/**
 * startHashTable - Start a new hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table		 
 * @return int Boolean 
 */
int startHashTable(struct student *hash_table) {
	
	int i=0;
	
	// Reset all positions
	for(i=0; i<HASHTBL_SIZE; i++) {
		hash_table[i] = getEmptyStudent();
	}
	
	return 1;
	
}

/**
 * printHashTable - Print hash table
 * @author Luiz Venturote
 * @param  struct student hash_table Hash table
 */
void printHashTable(struct student *hash_table) {
	
	int i=0;
	
	for(i=0; i<HASHTBL_SIZE; i++) {
		printf(" \n %d | %d - %s \n", i, hash_table[i].cod, hash_table[i].name);
		printf(" --------------------------");
	}
	
	printf("\n\n\n");
	
}

/**
 * Load data from file to struct
 * @author Luiz Venturote
 * @param  char * file_name File name
 * @param  Student **std Struct array
 */
void loadDataFile(char * file_name, Student **std) {
			
	int n = 0, i=0, swap=0;
	
	// File
	FILE* fp;
	
	// Open file
	fp = fopen(file_name,"rt");
	if (fp == NULL) {
		printf("Erro na abertura do arquivo!\n");
		exit(1);
	}
	
	// Line control
	char line[121];

	// Read line by line
	while (fgets(line,121,fp) != NULL) {
		
		// Remove '\n' the end of the line
		strtok(line, "\n");
		
		n++;
		
		// Name
		if(n==1) {
			strcpy(std[i]->name, line);
		}
		
		// Cod
		if(n==2) {
			swap = atoi(line);
			std[i]->cod = swap;
		}
		
		// Phone
		if(n==3) {
			swap = atoi(line);
			std[i]->phone = swap;
		}
		
		// E-mail
		if(n==4) {
			strcpy(std[i]->email, line);
		}
		
		// Address
		if(n==5) {
			strcpy(std[i]->address, line);
		}
		
		// End
		if(n==6) {
			n=0;
			i++;
		}
		
	}
	
	// Close file
	fclose(fp);
	
}


/**
 * Hash Function
 * @author Luiz Venturote
 * @param  int table_size Hash table size
 * @param  int code Code
 * @return int Hash code
 */
int HashFunction(int table_size, int code) {
	
	return code % table_size;
	
}

