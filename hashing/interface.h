/**
 * Show menu options
 * @author Luiz Venturote
 * @return int Selected option
 */
int MenuOption() {
	
	// Menu option
	int opt=0;
	
	// Show menu
	system("cls");
	printf(" === Hashing table =========================== \n");
	printf(" 1) Linear Hashing \n");
	printf(" 2) Double Hashing \n");
	printf(" 3) Closed Hashing \n");
	printf(" 4) Open Hashing \n");
	printf(" 0) Exit \n");
	printf("\n Select hashing option: ");
	scanf("%d", &opt);
	
	return opt;
}

/**
 * Display header
 * @author Luiz Venturote
 */
void displayHeader(char * header_text) {
	system("cls");
	printf(" === %s =========================== \n", header_text);	
}

/**
 * Display footer
 * @author Luiz Venturote
 */
void displayFooter() {
	system("pause");
}

