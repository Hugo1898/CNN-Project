
#include "game_manager_hash.h"
#include "print_game_hash.h"
#include "IA_game_manager_hash.h"
#include "IA_hastable_hash.h"

void play_turn_human(player *p_turn, player *p_other, int tab[2][6], uint64_t *hv, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]) {
	int x = -1;
	char c[2];
	int only[6] = {0};
	if (p_turn->name == 'N') {
		if (test_feed_N(tab, only, p_turn) != 0) {
			printf("***********************************\n");
			printf ("\nC'est au tour du joueur Nord de jouer.\n"); 
			while ( x < 0) {
				printf ("Choisissez quelle case vous voulez semer ? Tapez a, b, c, d, e, ou f.\n\n");
				lire(c, 2);
				switch(c[0]) {
				case 'a' :
					x = 5;
					break;
				case 'b' :
					x = 4;
					break;
				case 'c' :
					x = 3;
					break;
				case 'd' :
					x = 2;
					break;
				case 'e' :
					x = 1;
					break;
				case 'f' :
					x = 0;
					break;
				default :
					printf("\nFaute de frappe. Aucune de vos cases n'a cette lettre.\n");
					break;
				}
					
				if (tab[0][x] == 0) {
					printf("\nChoisissez une autre case car celle-ci est vide.\n");
					x = -1;
				}
				
				else if (only[x] == 0) {
					printf("\nChoisissez une autre case car il faut nourir l'adversaire.\n");
					x = -1;
				}
				
			} 
			int pos[2];
			int graine = tab[0][x];
			int rec[6] = {0};
			int score = p_turn->score;
			play_case_N (tab, x, pos, graine);
			printf("\nSemage de la case %c effectué :\n", c[0]); 
			print_game(tab, p_turn, p_other);
			recolte_N(tab, p_turn, pos, rec);
			*hv ^= hashSC[0][p_turn->score] ^ hashSC[1][p_other->score] ^ hashP[0][x][graine];
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 6; j++) {
					*hv ^= hashT[i][j][tab[i][j]];
				}
			}
			int sem = p_turn->score - score; 
			printf("Récolte des graines semés par le joueur Nord : %d graines ont été récoltées. \n", sem);
			print_game(tab, p_turn, p_other);
		}
		else {
			printf("***********************************\n");
			printf("Le joueur Nord ne peut pas nourrir le joueur Sud.\n");
			for (int i = 0; i < 2; i++) {
				for ( int j = 0; j < 6; j++) {
					p_turn->score += tab[i][j];
					tab[i][j] = 0;
				}
			}
			print_game(tab, p_turn, p_other);
		}
		
	}
	
	else {
		if (test_feed_S(tab, only, p_turn) != 0) {
			printf("***********************************\n");
			printf ("\nC'est au tour du joueur Sud de jouer.\n"); 
			while ( x < 0) { 
				printf ("Choisissez quelle case vous voulez semer ? Tapez A, B, C, D, E, ou F.\n\n");
				lire(c, 2);
				switch(c[0]) {
				case 'A' :
					x = 0;
					break;
				case 'B' :
					x = 1;
					break;
				case 'C' :
					x = 2;
					break;
				case 'D' :
					x = 3;
					break;
				case 'E' :
					x = 4;
					break;
				case 'F' :
					x = 5;
					break;
				default :
					printf("\nFaute de frappe. Aucune de vos cases n'a cette lettre.\n");
					break;
				}
				
				if (tab[1][x] == 0) {
					printf("\nChoisissez une autre case car celle-ci est vide.\n");
					x = -1;
				} 
				
				else if (only[x] == 0) {
					printf("\nChoisissez une autre case car il faut nourir l'adversaire.\n");
					x = -1;
				}
			}
			int pos[2];
			int rec[6] = {0};
			int graine = tab[1][x];
			int score = p_turn->score;
			play_case_S (tab, x, pos, graine);
			printf("\nSemage de la case %c effectué :\n", c[0]); 
			print_game(tab, p_turn, p_other);
			recolte_S(tab, p_turn, pos, rec);
			*hv ^= hashSC[0][p_other->score] ^ hashSC[1][p_turn->score] ^ hashP[1][x][graine];
			for (int i =0; i < 2; i++) {
				for (int j = 0; j < 6; j++) {
					*hv ^= hashT[i][j][tab[i][j]];
				}
			}
			int sem = p_turn->score - score;
			printf("Récolte des graines semés par le joueur Sud : %d graines ont été récoltées. \n", sem);
			print_game(tab, p_turn, p_other);
		}
		else {
			printf("***********************************\n");
			printf("Le joueur Sud ne peut pas nourrir le joueur Nord.\n");
			for (int i = 0; i < 2; i++) {
				for ( int j = 0; j < 6; j++) {
					p_turn->score += tab[i][j];
					tab[i][j] = 0;
				}
			}
			print_game(tab, p_turn, p_other);
		}
	}
	 
}


void play_turn_ordi(player *p_turn, player *p_other, int tab[2][6], uint64_t *hv, hash_type *hash_v, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49], int base) {
	int x;
	char c = 0;
	int only[6] = {0};
	if (p_turn->name == 'N') {
		if (test_feed_N(tab, only, p_turn) != 0) {
			printf("***********************************\n");
			printf("\nC'est au tour du joueur Nord (ordi) de jouer.\n"); 
			x = choice_IA(tab, base, p_turn, p_other, *hv, hash_v, hashSC, hashP, hashT);	
			switch(x) {
				case 5 :
					c = 'a';
					break;
				case 4 :
					c = 'b';
					break;
				case 3 :
					c = 'c';
					break;
				case 2 :
					c = 'd';
					break;
				case 1 :
					c = 'e';
					break;
				case 0 :
					c = 'f';
					break;
				
			}
			
			printf("L'ordi a choisi de semer la case %c.\n", c);
			
			if (only[x] == 0) {
				printf("\n Erreur de feed.\n");
				exit(EXIT_ERROR);
			}
			
			int pos[2];
			int graine = tab[0][x];
			int rec[6]={0};
			int score = p_turn->score;
			play_case_N (tab, x, pos, graine);
			printf("\nSemage de la case %c effectué :\n", c); 
			print_game(tab, p_turn, p_other);
			recolte_N(tab, p_turn, pos, rec);
			*hv ^= hashSC[0][p_turn->score] ^ hashSC[1][p_other->score] ^ hashP[0][x][graine];
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 6; j++) {
					*hv ^= hashT[i][j][tab[i][j]];
				}
			}
			int sem = p_turn->score - score; 
			printf("Récolte des graines semés par le joueur Nord (ordi) : %d graines ont été récoltées. \n", sem);
			print_game(tab, p_turn, p_other);
		}
		
		else {
			printf("***********************************\n");
			printf("Le joueur Nord (ordi) ne peut pas nourrir le joueur Sud.\n");
			for (int i = 0; i < 2; i++) {
				for ( int j = 0; j < 6; j++) {
					p_turn->score += tab[i][j];
					tab[i][j] = 0;
				}
			}
			print_game(tab, p_turn, p_other);
		}
		

	}
	
	else {
		if (test_feed_S(tab, only, p_turn) != 0) {
			printf("***********************************\n");
			printf("\nC'est au tour du joueur Sud (ordi) de jouer.\n"); 
			x = choice_IA(tab, base, p_turn, p_other, *hv, hash_v, hashSC, hashP, hashT);	
			switch(x) {
				case 5 :
					c = 'F';
					break;
				case 4 :
					c = 'E';
					break;
				case 3 :
					c = 'D';
					break;
				case 2 :
					c = 'C';
					break;
				case 1 :
					c = 'B';
					break;
				case 0 :
					c = 'A';
					break;
				
			}
			
			printf("L'ordi a choisi de semer la case %c.\n", c);
			
			if (only[x] == 0) {
				printf("\n Erreur de feed.\n");
				exit(EXIT_ERROR);
			}
		
			int pos[2];
			int graine = tab[1][x];
			int rec[6] = {0};
			int score = p_turn->score;
			play_case_S (tab, x, pos, graine);
			printf("\nSemage de la case %c effectué :\n", c); 
			print_game(tab, p_turn, p_other);
			recolte_S(tab, p_turn, pos, rec);
			*hv ^= hashSC[0][p_other->score] ^ hashSC[1][p_turn->score] ^ hashP[1][x][graine];
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 6; j++) {
					*hv ^= hashT[i][j][tab[i][j]];
				}
			}
			int sem = p_turn->score - score; 
			printf("Récolte des graines semés par le joueur Sud (ordi) : %d graines ont été récoltées. \n", sem);
			print_game(tab, p_turn, p_other);
		}
		
		else {
			printf("***********************************\n");
			printf("Le joueur Sud (ordi) ne peut pas nourrir le joueur Nord.\n");
			for (int i = 0; i < 2; i++) {
				for ( int j = 0; j < 6; j++) {
					p_turn->score += tab[i][j];
					tab[i][j] = 0;
				}
			}
			print_game(tab, p_turn, p_other);
		}	
	}
}


void play_case_N (int tab[2][6], int x, int pos[2], int graine) {
	tab[0][x] = 0;
	for (int j = x-1; j >= 0; j--) {
		if (graine > 0) {
			tab[0][j]++;
			graine--;
			pos[0] = 0;
			pos[1] = j;
		}
		else break;	
	}
	
	while (graine > 0) {
		for (int j = 0; j < 6; j++) {
			if (graine > 0) {
			tab[1][j]++;
			graine--;
			pos[0] = 1;
			pos[1] = j;
			}
			else break;
		}
		
		for (int j = 5; j >= 0; j--) {
			if (j == x) j--;
			if (j < 0) break;
			if (graine > 0) {
			tab[0][j]++;
			graine--;
			pos[0] = 0;
			pos[1] = j;
			}
			else break;	
			
		}
	}
}

void play_case_S (int tab[2][6], int x, int pos[2], int graine) {
	tab[1][x] = 0;
	for (int j = x+1; j < 6; j++) {
		if (graine > 0) {
			tab[1][j]++;
			graine--;
			pos[0] = 1;
			pos[1] = j;
		}
		else break;	
	}
	
	while (graine > 0) {
		for (int j = 5; j >= 0; j--) {
			if (graine > 0) {
			tab[0][j]++;
			graine--;
			pos[0] = 0;
			pos[1] = j;
			}
			else break;		
		}
		
		for (int j = 0; j < 6; j++) {
			if (j == x) j++;
			if (j > 5) break;
			if (graine > 0) {
			tab[1][j]++;
			graine--;
			pos[0] = 1;
			pos[1] = j;
			}
			else break;
		}
		
	}
}

void recolte_S(int tab[2][6], player *p_turn, int pos[2], int rec[6]) {	
	if (pos[0] == 0) {
		int i = 0;
		for (int j = pos[1]; j < 6; j++) {
			if (tab[i][j] == 3 || tab[i][j] == 2) {
				p_turn->score += tab[i][j];
				rec[j] = tab[i][j];
				tab[i][j] = 0;
			}
			else break;
		}
	}
}
	

void recolte_N(int tab[2][6], player *p_turn, int pos[2], int rec[6]) {
	if (pos[0] == 1) {
		int i = 1;
		for (int j = pos[1]; j >= 0; j--) {
			if (tab[i][j] == 3 || tab[i][j] == 2) {
				p_turn->score += tab[i][j];
				rec[j] = tab[i][j];
				tab[i][j] = 0;
			}
			else break;
		}
	}
}

void unrecolte_S(int tab[2][6], player *p_turn, int rec[6]) {	
	for (int j = 0; j < 6; j++) {
		p_turn->score -= rec[j];
		tab[0][j] += rec[j];
	}
}


void unrecolte_N(int tab[2][6], player *p_turn, int rec[6]) {	
	for (int j = 0; j < 6; j++) {
		p_turn->score -= rec[j];
		tab[1][j] += rec[j];
	}
}

void unplay_case_S(int tab[2][6], int x, int graine) {
	tab[1][x] = graine;
	for (int j = x+1; j < 6; j++) {
		if (graine > 0) {
			tab[1][j]--;
			graine--;
		}
		else break;	
	}
	
	while (graine > 0) {
		for (int j = 5; j >= 0; j--) {
			if (graine > 0) {
			tab[0][j]--;
			graine--;
			}
			else break;		
		}
		
		for (int j = 0; j < 6; j++) {
			if (j == x) j++;
			if (j > 5) break;
			if (graine > 0) {
			tab[1][j]--;
			graine--;
			}
			else break;
		}
		
	}
}

void unplay_case_N (int tab[2][6], int x, int graine) {
	tab[0][x] = graine;
	for (int j = x-1; j >= 0; j--) {
		if (graine > 0) {
			tab[0][j]--;
			graine--;
		}
		else break;	
	}
	
	while (graine > 0) {
		for (int j = 0; j < 6; j++) {
			if (graine > 0) {
			tab[1][j]--;
			graine--;
			}
			else break;
		}
		
		for (int j = 5; j >= 0; j--) {
			if (j == x) j--;
			if (j < 0) break;
			if (graine > 0) {
			tab[0][j]--;
			graine--;
			}
			else break;	
			
		}
	}
}


int test_feed_N(int tab[2][6], int only[6], player *p_turn) {
	int x = 0;
	for (int j = 0; j <6; j++) {
		int pos[2] = {0};
		int graine = tab[0][j];
		int rec[6]={0};
		int comp = 0;
		if (graine != 0) {
			play_case_N (tab, j, pos, graine);
			recolte_N(tab, p_turn, pos, rec);
			for (int z = 0; z < 6; z++) {
					comp += tab[1][z];
				} 
			if (comp != 0) {
				only[j] = 1;
				x +=1;
			}
			
			unrecolte_N(tab, p_turn, rec);
			unplay_case_N(tab, j, graine);  
		}
	}
	return x;	
}


int test_feed_S(int tab[2][6], int only[6], player *p_turn) {
	int x = 0;
	for (int j = 0; j < 6; j++) {
		int pos[2] = {0};
		int graine = tab[1][j];
		int rec[6]={0};
		int comp = 0;
		if (graine != 0) {
			play_case_S (tab, j, pos, graine);
			recolte_S(tab, p_turn, pos, rec);
			for (int z = 0; z < 6; z++) {
					comp += tab[0][z];
				} 
			if (comp != 0) {
				only[j] = 1;
				x += 1;
			}
				
			unrecolte_S(tab, p_turn, rec);
			unplay_case_S(tab, j, graine); 
		} 
		
	}
	return x;	
}

	
void end_game(int tab[2][6], player *p_1, player *p_2, int *end) {
	if ( p_1->score > 24) {
		if (p_1->name == 'N') printf("Victoire du joueur Nord !\n\n");
		else printf("Victoire du joueur Sud !\n\n");
		*end = 0;
	}
	
	if ( p_2->score > 24) {
		if (p_2->name == 'N') printf("Victoire du joueur Nord !\n\n");
		else printf("Victoire du joueur Sud !\n\n");
		*end = 0;
	}
	
	int comp = 0;
	 	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			comp += tab[i][j];
		}
	}
		
	if (comp <= 3) {
		if (comp != 0) printf("Plus aucune prise n'est possible.\n\n");
		if (p_1->score > p_2->score) {
			if (p_1->name == 'N') printf("Victoire du joueur Nord !\n\n");
			else printf("Victoire du joueur Sud !\n\n");
			*end = 0;
		}
		else if (p_2->score > p_1->score) {
			if (p_2->name == 'N') printf("Victoire du joueur Nord !\n\n");
			else printf("Victoire du joueur Sud !\n\n");
			*end = 0;
		}
		
		else printf("Egalité parfaite !\n\n");
	
	}
	
}

