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
	printf(" === Arvore Binaria =========================== \n");
	printf(" 1) Representacao sequencial \n");
//	printf(" 2) Representacao sequencial com verificacao de tempo execucao\n");
	printf(" 2) Representacao dinamica \n");
	printf(" 3) Representacao dinamica com verificacao de tempo execucao \n");
	printf(" 0) Exit \n");
	printf("\n Select option: ");
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

