
#include "IA_game_manager.h"
#include "game_manager.h"
#include "IA_alpha.h"


int eval(int tab[2][6], int x, int name, player *p_N, player *p_S) {
	int pos[2];
	int rec[6] = {0};
	int only[6] = {0};
	int scoreN;
	int scoreS;
	int v, test, graine;
	int comp = 0;
	
	if (name == NORD) {
		graine = tab[0][x];
		play_case_N (tab, x, pos, graine);
		recolte_N(tab, p_N, pos, rec);
		scoreN = p_N->score;
		scoreS = p_S->score;
		if (scoreN > 24) {
			unrecolte_N(tab, p_N, rec);
			unplay_case_N (tab, x, graine);
			return WIN;
		}
		
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 6; j++) {
				comp += tab[i][j];
			}
		}
		if (comp <= 3) {
			unrecolte_N(tab, p_N, rec);
			unplay_case_N (tab, x, graine);
			
			if (scoreN > scoreS) {
				return WIN;
			}
			else if (scoreN < scoreS) {
				return - WIN;
			}
			else return 0;
		}
		
		test = test_feed_S(tab, only, p_S); 
		if (test == 0) {
			v = p_S->score;
			for (int i = 0; i < 2; i++){
				for (int j = 0; j < 6; j++) {
					v += tab[i][j];
				}
			}
			unrecolte_N(tab, p_N, rec);
			unplay_case_N (tab, x, graine);
			if (v > 24) {
				return - WIN; 
			}
			else return 0;	
		}
		
		unrecolte_N(tab, p_N, rec);
		unplay_case_N (tab, x, graine);
		return (scoreN + 1);
	}
	else {
		int graine = tab[1][x];
		play_case_S (tab, x, pos, graine);
		recolte_S(tab, p_S, pos, rec);
		scoreN = p_N->score;
		scoreS = p_S->score;
		if (scoreS > 24) {
			unrecolte_S(tab, p_S, rec);
			unplay_case_S (tab, x, graine);
			return - WIN;
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 6; j++) {
				comp += tab[i][j];
			}
		}
		if (comp <= 3) {
			unrecolte_S(tab, p_S, rec);
			unplay_case_S (tab, x, graine);
			
			if (scoreN > scoreS) {
				return WIN;
			}
			else if (scoreN < scoreS) {
				return - WIN;
			}
			else return 0;
		}
		
		test = test_feed_N(tab, only, p_N); 
		if (test == 0) {
			v = p_N->score;
			for (int i = 0; i < 2; i++){
				for ( int j = 0; j < 6; j++) {
					v += tab[i][j];
				}
			}
			unrecolte_S(tab, p_S, rec);
			unplay_case_S(tab, x, graine);
			if (v > 24) {
				return WIN; 
			}
			else return 0;	
		}
		
		unrecolte_S(tab, p_S, rec);
		unplay_case_S (tab, x, graine);
		return -(scoreS + 1);
	}
	
}

int choice_IA(int tab[2][6], int base, player *p_ordi, player *p_human) {
	int best_move;
	int ret, maxdepth;
	clock_t time, otime;
	double ftime = 0.0;
	int name;
	
	if (p_ordi->name == 'N') {
		name = NORD;
	}
	else name = SUD;
	
	maxdepth = base;
	otime = clock();
	do {
	maxdepth++;
	best_move = -1;
	if (name == NORD) {
		ret = alpha_beta(- MAXV, MAXV, name, base, maxdepth, base, p_ordi, p_human, tab, &best_move);
	}
	else {
		ret = alpha_beta(- MAXV, MAXV, name, base, maxdepth, base, p_human, p_ordi, tab, &best_move);
	}
	time = clock()- otime;
	ftime += (double)time/(double)CLOCKS_PER_SEC;
	if (best_move == -1) {printf("error -1\n");exit(EXIT_ERROR);}
	if (best_move >= 6) {printf("error SIZE\n");exit(EXIT_ERROR);}
	if (name == NORD) {
		if (tab[0][best_move] == 0) {printf("error EMPTY\n");exit(EXIT_ERROR);}
	}
	else {
		if (tab[1][best_move] == 0) {printf("error EMPTY\n");exit(EXIT_ERROR);}
	}
	// printf("best_move=%d ret=%d base=%d maxdepth=%d time=%f\n", best_move, ret, base, maxdepth, ftime);
	} 
	while ((ftime <= 5.0) && abs(ret) < BWIN);
	
	/*
	int comp = 0;
	for (int i =0; i < 2; i++) {
				for (int j = 0; j < 6; j++) {
					comp +=  tab[i][j];
				}
			}
	printf ("\n%d\n", comp);
	*/
	
	
	return best_move;

} 
