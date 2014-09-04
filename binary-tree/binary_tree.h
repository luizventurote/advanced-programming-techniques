// Student struct
typedef struct student {
  int 	cod;
  char  name[100];
  int 	phone;
  char 	email[100];
  char 	address[100];
} Student;

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
