
#include "print_game_hash.h"
#include "game_manager_hash.h"



void print_intro(int tab[2][6], player* p_human, player* p_ordi) {
	char choice[100];
	int x = 0;
	printf("\n***************************************************************************");
	printf("\n\nBienvenue dans le jeu d'Awalé ! \n\n");
	
	int unit[2][6] = {{0}};
	int diz [2][6] = {{0}};
	for (int i =0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			unit[i][j] = tab[i][j]%10;
			diz[i][j] = tab[i][j]/10;
		}
	}  
	
	printf("             Nord             \n");
	printf(" ―――――――――――――――――――――――――――――\n");
	printf("| %d%d | %d%d | %d%d | %d%d | %d%d | %d%d |\n", diz[0][0], unit[0][0], diz[0][1], unit[0][1], diz[0][2], unit[0][2], diz[0][3], unit[0][3], diz[0][4], unit[0][4], diz[0][5], unit[0][5]);
	printf("|―――――――――――――――――――――――――――――|\n");
	printf("| %d%d | %d%d | %d%d | %d%d | %d%d | %d%d |\n", diz[1][0], unit[1][0], diz[1][1], unit[1][1], diz[1][2], unit[1][2], diz[1][3], unit[1][3], diz[1][4], unit[1][4], diz[1][5], unit[1][5]);
	printf(" ―――――――――――――――――――――――――――――\n");
	printf("             Sud              \n\n");
	
	while (strcmp(choice, "Sud") != 0 && strcmp(choice, "Nord") != 0) {
		if (x == 1) printf("\nFaute de frappe. Tapez uniquement Nord ou Sud.\n");
		printf("Voulez-vous être joueur Nord ou Sud ? Tapez Nord ou Sud.\n\n");
		lire(choice, 100); 
		x = 1;
	}
	
	if (strcmp(choice, "Sud") == 0) {
		printf("\nVous serez donc joueur Sud et votre adversaire sera joueur Nord.\n");
		p_human->name = 'S'; 
		p_ordi->name = 'N';
	}
	
	else {
		printf("\nVous serez donc joueur Nord et votre adversaire sera joueur Sud.\n");
		p_human->name = 'N'; 
		p_ordi->name = 'S';
	}
	
	printf("\n***************************************************************************");
	printf("\n\nLa partie va commencer ! Le sens du jeu est anti-horaire.\n"); 
	
	print_game(tab, p_human, p_ordi);
	
}


void print_game(int tab[2][6], player *p_1, player *p_2) {
	int score_N;
	int score_S;
	
	if (p_1->name == 'N') {
			score_N = p_1->score;
			score_S = p_2->score;
	}
	
	else {
		score_N = p_2->score;
		score_S = p_1->score;
	}
	
	int unit[2][6] = {{0}};
	int diz [2][6] = {{0}};
	for (int i =0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			unit[i][j] = tab[i][j]%10;
			diz[i][j] = tab[i][j]/10;
		}
	}
	printf("\n   f    e    d    c    b    a \n");
	printf(" ―――――――――――――――――――――――――――――\n");
	printf("| %d%d | %d%d | %d%d | %d%d | %d%d | %d%d |        Score du joueur Nord : %d\n", diz[0][0], unit[0][0], diz[0][1], unit[0][1], diz[0][2], unit[0][2], diz[0][3], unit[0][3], diz[0][4], unit[0][4], diz[0][5], unit[0][5], score_N);
	printf("|―――――――――――――――――――――――――――――|\n");
	printf("| %d%d | %d%d | %d%d | %d%d | %d%d | %d%d |        Score du joueur Sud : %d\n", diz[1][0], unit[1][0], diz[1][1], unit[1][1], diz[1][2], unit[1][2], diz[1][3], unit[1][3], diz[1][4], unit[1][4], diz[1][5], unit[1][5], score_S);
	printf(" ―――――――――――――――――――――――――――――\n");
	printf("   A    B    C    D    E    F \n\n");
	
}



void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
 
int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        }
        else {
            viderBuffer();
        }
        return 1;
    }
    else {
        viderBuffer();
        return 0;
    }
}
