#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <windows.h>
#include <time.h>
#include <limits.h>
#include "interface.h"
#include "kruskal.h"
#include "prim.h"
#include "dijkstra.h"

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
				displayHeader("Kruskal Algorithm");
				KruskalMST();
				displayFooter();
				break;
			case 2:
				displayHeader("Prim Algorithm");
				PrimMST();
				displayFooter();
				break;
			case 3:
				displayHeader("Dijkstra Algorithm");
				Dijkstra();
				displayFooter();
				break;
			case 0:
				run=0;
				break;
		}
		
	}
	
	exit(0);
}
