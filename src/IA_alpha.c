
#include "IA_game_manager.h"
#include "IA_alpha.h"
#include "game_manager.h"


int max (int a, int b) {
	if (a >= b) return a;
	else return b;
} 

int min (int a, int b) {
	if (a <= b) return a;
	else return b;
} 

void make_indx(int *indx) {
	for (int i = 0; i < 6; i++) {
		indx[i] = i;
	}
}



int alpha_beta(int alpha, int beta, int name, int depth, int maxdepth, int base, player *p_N, player *p_S, int tab[2][6], int *best_move) {
	int a, b, g, x, v;
	int ev = 0;
	int only[6] = {0};
	int indx[6];
	
	make_indx(indx);
	
	if (name == NORD) { 
		test_feed_N(tab, only, p_N);
	}
	else {
		test_feed_S(tab, only, p_S);
	}
	

	for (int j = 0; j < 6; j++) {	
		x = indx[j];
		
		if (only[x] == 1) {
			v = eval(tab, x, name, p_N, p_S);
			
			ev += v;
			
			if (abs(v) == WIN) {
				if (v > 0) {
					v = v - depth;
				}
				else v = v + depth;
			
				if (depth == base) {
					*best_move = x;
				}
				
				return v;
			
			}	
		}
	}
	
	
	if (ev == 0) {
		for (int j = 0; j < 6; j++) {	
			x = indx[j];
		
			if (only[x] == 1) {
				
				if (depth == base) {
					*best_move = x;
				}
				
				return 0;
			}
		}
	}	

	/* Leaf but not end of game. Return evaluation of the position. */
	if (depth == maxdepth) return ev;
	
	a = alpha; b = beta;
	
	if (name == NORD) { 
		g = - MAXV;
	}
	else g = MAXV;
	

	for (int j = 0; j < 6; j++) {
		
		x = indx[j];
		
		if (only[x] == 1) {
			int pos[2];
			int rec[6] = {0};
			if (name == NORD) {
				int graine = tab[0][x];
				play_case_N (tab, x, pos, graine);
				recolte_N(tab, p_N, pos, rec);
				v = alpha_beta(a, beta, - name, depth + 1, maxdepth, base, p_N, p_S, tab, best_move);
				unrecolte_N(tab, p_N, rec);
				unplay_case_N (tab, x, graine);
			}
			else {
				int graine = tab[1][x];
				play_case_S (tab, x, pos, graine);
				recolte_S(tab, p_S, pos, rec);
				v = alpha_beta(alpha, b, - name, depth + 1, maxdepth, base, p_N, p_S, tab, best_move);
				unrecolte_S(tab, p_S, rec);
				unplay_case_S (tab, x, graine);
			}
			
			if (name == NORD) {
				if (v > g) {
					if (base == depth) *best_move = x;
				}
				
				g = max(g,v);
				a = max(a,g);
				if (g >= beta) break; /* Beta cut */
			}
			
			else {
				if (v < g) {
					if (base == depth) *best_move = x;
				}
					
				g = min(g,v);
				b = min(b,g);
				if (g <= alpha) break; /* Alpha cut */
			}		
		}
	}

	return g;
}
	
		
		
		
		
