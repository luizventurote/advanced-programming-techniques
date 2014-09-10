#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "binary_tree_sequential.h"

/**
 * Main
 * @author Luiz Venturote
 */
void main() {
	
	int run=1, menu_opt=0;
	
	while(run==1) {
		
		// Menu option
		//menu_opt = MenuOption();
		menu_opt = 1;
		
		switch(menu_opt) {
			case 1:
				displayHeader("Arvore Binaria com alocacao Sequencial");
				BinaryTreeSeq();
				displayFooter();
				break;
			case 2:
				displayHeader("Arvore Binaria com alocacao Sequencial");
				//BinaryTreeDin("students.txt");
				displayFooter();
				break;
			case 0:
				run=0;
				break;
		}
		
	}
	
	exit(0);
}
