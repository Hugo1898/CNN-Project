
#include "print_game.h"
#include "game_manager.h"
#include "IA_alpha.h"


int main () {
	player *p_ordi = calloc(1, sizeof(player));
	player *p_human = calloc(1, sizeof(player));
	int tab[2][6] = {{4, 4, 4, 4, 4, 4}, {4, 4, 4, 4, 4, 4}};
	
	print_intro(tab, p_human, p_ordi);
	
	int x = 1;
	int end = 1;
	int base = 0;
	
	char c[2];
	int z = -1;
	while ( z < 0) {
		printf ("Voulez-vous jouer en mode 1 joueur, 2 joueurs ou spectateur ? Tapez 1, 2 ou S.\n\n");
		lire(c, 2);
		switch(c[0]) {
		case '1' :
			z = 1;
			break;
		case '2' :
			z = 1;
			break;
		case 'S' :
			z = 1;
			break;
		default :
			printf("\nFaute de frappe. Tapez 1, 2 ou S.\n");
			break;
		}
	}
	
	printf ("\n");
	
	if (c[0] == '2') { 
		while (end) {
			if (x == 1) {
				play_turn_human(p_human, p_ordi, tab);
				x = 2;
			}
			else {
				play_turn_human(p_ordi, p_human, tab);
				x = 1;
			}
			
			end_game(tab, p_human, p_ordi, &end);
		}
	}
	
	else if (c[0] == '1') {
		while (end) {
			if (x == 1) {
				play_turn_human(p_human, p_ordi, tab);
				x = 2;
			}
			else {
				play_turn_ordi(p_ordi, p_human, tab, base);
				x = 1;
			}
			
			end_game(tab, p_human, p_ordi, &end);
			
			base++;
		}
	}
	
	else {
		while (end) {
			if (x == 1) {
				play_turn_ordi(p_human, p_ordi, tab, base);
				x = 2;
			}
			else {
				play_turn_ordi(p_ordi, p_human, tab, base);
				x = 1;
			}
			
			end_game(tab, p_human, p_ordi, &end);
			
			base++;
		}
	
	}
	

	
	return 0;
	
}

