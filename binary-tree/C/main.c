#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <windows.h>
#include <time.h>
#include "bubble_sort.h"
#include "interface.h"
#include "binary_tree_sequential.h"
#include "binary_tree_dynamic.h"

/**
 * Main
 * @author Luiz Venturote
 */
void main() {
	
	int run=1, menu_opt=0;
	
	while(run==1) {
		
		// Menu option
		menu_opt = MenuOption();
		
		switch(menu_opt) {
			case 1:
				displayHeader("Arvore Binaria com alocacao Sequencial");
				BinaryTreeSeq();
				displayFooter();
				break;
			case 2:
				displayHeader("Arvore Binaria com alocacao Sequencial com verificacao de tempo execucao");
				BinaryTreeSeqET();
				displayFooter();
				break;
			case 3:
				displayHeader("Arvore Binaria com alocacao Dinamica");
				BinaryTreeDyn();
				displayFooter();
				break;
			case 4:
				displayHeader("Arvore Binaria com alocacao Dinamica com verificacao de tempo execucao");
				BinaryTreeDynET();
				displayFooter();
				break;
			case 0:
				run=0;
				break;
		}
		
	}
	
	exit(0);
}
