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
	printf(" 1) Algoritmo de Kruskal \n");
	printf(" 2) Algoritmo Prim\n");
	printf(" 3) Algoritmo de Dijkstra\n");
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

