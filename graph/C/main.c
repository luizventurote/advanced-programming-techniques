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
				displayHeader("Algoritmo de Kruskal");
				KruskalMST();
				displayFooter();
				break;
			case 2:
				displayHeader("Algoritmo Prim");
				Prim();
				displayFooter();
				break;
			case 3:
				displayHeader("Algoritmo de Dijkstra");
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
