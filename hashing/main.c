#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "hashing.h"
#include "linear_hashing.h"
#include "double_hashing.h"

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
				displayHeader("Linear Hashing");
				linearHashing("students.txt");
				displayFooter();
				break;
			case 2:
				displayHeader("Double Hashing");
				DoubleHashing("students.txt");
				displayFooter();
				break;
			case 0:
				run=0;
				break;
		}
		
	}
	
	exit(0);
}
