#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "ford_fulkerson.h"

/**
 * Main
 * @author Luiz Venturote
 */
int main() {
	
	int run=1, menu_opt=0;
	
	while(run==1) {
		
		// Menu option
		menu_opt = MenuOption();
		
		switch(menu_opt) {
			case 1:
				displayHeader("Ford Fulkerson Algorithm");
				FordFulkersonMF();
				displayFooter();
				break;
			case 0:
				run=0;
				break;
		}
		
	}
	
	exit(0);
}
