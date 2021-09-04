
#define _XOPEN_SOURCE 500

#include "IA_game_manager_hash.h"
#include "IA_hastable_hash.h"
#include "game_manager_hash.h"


int16_t max (int16_t a, int16_t b) {
	if (a >= b) return a;
	else return b;
} 

int16_t min (int16_t a, int16_t b) {
	if (a <= b) return a;
	else return b;
} 

void make_indx(int *indx) {
	for (int i = 0; i < 6; i++) {
		indx[i] = i;
	}
}

uint64_t rand_v() {
	return
	(((uint64_t)lrand48())<<62) ^
	(((uint64_t)lrand48())<<31) ^
	((uint64_t)lrand48());
}

void init_hash(uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 49; j++) {
			hashSC[i][j] = rand_v();
		}
	}
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) { 
			for (int k = 0; k < 49; k++) {
				hashP[i][j][k] = rand_v();
				hashT[i][j][k] = rand_v();
			}
		}
	}
}

int retrieve_v_hash(uint64_t hv, int dist, int *v_inf, int *v_sup, int *bmove, hash_type *hash_v) {
	int ind=hv&HASH_MASK;

	if (hash_v[ind].sig == hv) {
		if ((hash_v[ind].dist == dist) || ((hash_v[ind].v_inf == hash_v[ind].v_sup) && (abs(hash_v[ind].v_inf) >= BWIN))){
			*v_inf = hash_v[ind].v_inf;
			*v_sup = hash_v[ind].v_sup;
			*bmove = hash_v[ind].bmove;
			return TRUE;
		}
		
		*bmove = hash_v[ind].bmove;
		return FALSE;
	}
	
	return FALSE;
}

void store_v_hash_both(uint64_t hv, int v, int dist, int base, int move, hash_type *hash_v) {
	int ind = hv&HASH_MASK;

	if ((hash_v[ind].base != base) || (hash_v[ind].dist <= dist)) {
		hash_v[ind].v_inf = (int16_t)v;
		hash_v[ind].v_sup = (int16_t)v;
		hash_v[ind].sig = hv;
		hash_v[ind].base = (uint8_t)base;
		hash_v[ind].bmove = (uint8_t)move;
		hash_v[ind].dist = (uint8_t)dist;
	}
}

void store_v_hash(uint64_t hv, int alpha, int beta, int g, int dist, int base, int move, hash_type *hash_v) {
	int ind = hv&HASH_MASK;

	if ((hash_v[ind].base != base) || (hash_v[ind].dist <= dist)) {
		if ((hash_v[ind].sig != hv) || (hash_v[ind].dist != dist)) {
			/* Not an update. Have to initialize/reset everything */
			hash_v[ind].v_inf = - MAXV;
			hash_v[ind].v_sup = MAXV;
			hash_v[ind].dist = (uint8_t)dist;
			hash_v[ind].sig = hv;
		}
		
		hash_v[ind].base = (uint8_t)base;
		hash_v[ind].bmove = (uint8_t)move;
		
		if ( (g > alpha) && (g < beta)) {
			hash_v[ind].v_inf = (int16_t)g;
			hash_v[ind].v_sup = (int16_t)g;
		}
		else if (g <= alpha) hash_v[ind].v_sup = (int16_t)g;
		else if (g >= beta) hash_v[ind].v_inf = (int16_t)g;
	}
}



int alpha_beta(int alpha, int beta, int name, int depth, int maxdepth, int base, uint64_t hv, hash_type *hash_v, player *p_N, player *p_S, int tab[2][6], int *best_move, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]) {
	int a, b, g, x, v;
	int ev = 0;
	int v_inf, v_sup, bmove = -1, lmove = -1;
	int do_bmove;
	int only[6] = {0};
	int indx[6];
	uint64_t hv_r = hv; 
	
	make_indx(indx);
	
	if (name == NORD) { 
		test_feed_N(tab, only, p_N);
	}
	else {
		test_feed_S(tab, only, p_S);
	}

	/* If position has already been evaluated, return evaluation 
	 or update bounds */
	if (retrieve_v_hash(hv, maxdepth - depth, &v_inf, &v_sup, &bmove, hash_v)) {
		if (depth == base) *best_move = bmove;
		if (v_inf == v_sup) return v_inf; /* Exact evaluation */
		if (v_inf >= beta) return v_inf; /* Beta cut */
		if (v_sup <= alpha)  return v_sup; /* Alpha cut */
		alpha = max(alpha, v_inf);
		beta = min(beta, v_sup);
	}
	
	
	
	/* Test first if there is a winning move; 
	 if there is one, store evaluation and return 
	 else compute simultaneously the evaluation of the position
	*/		
			
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
				
				store_v_hash_both(hv, v, maxdepth-depth, base, x, hash_v);
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
				
				store_v_hash_both(hv, 0, maxdepth-depth, base, x, hash_v);
				return 0;
			}
		}
	}	

	/* Leaf but not end of game. Return evaluation of the position. */
	if (depth == maxdepth) return ev;

	/* Classical alpha-beta */
	if ((bmove != -1) && only[bmove] == 1) {
		do_bmove = TRUE;
	}
	else do_bmove = FALSE;
	
	a = alpha; b = beta;
	
	if (name == NORD) { 
		g = - MAXV;
	}
	else g = MAXV;
	

	for (int j = 0; j < 6; j++) {
		if (do_bmove) {
			if (j == 0) {
				x = bmove;
			}
			else {
				x = indx[j-1];
				if (bmove == x) {
					x = indx[j];
					do_bmove = FALSE;
				}
			}
		}
			
		else x = indx[j];
		
		if (only[x] == 1) {
			int pos[2];
			int rec[6] = {0};
			if (name == NORD) {
				int graine = tab[0][x];
				play_case_N (tab, x, pos, graine);
				recolte_N(tab, p_N, pos, rec);
				hv ^= hashSC[0][p_N->score] ^ hashSC[1][p_S->score] ^ hashP[0][x][graine];
				for (int i =0; i < 2; i++) {
					for (int j = 0; j < 6; j++) {
						hv ^= hashT[i][j][tab[i][j]];
					}
				}
				v = alpha_beta(a, beta, - name, depth + 1, maxdepth, base, hv, hash_v, p_N, p_S, tab, best_move, hashSC, hashP, hashT);
				unrecolte_N(tab, p_N, rec);
				unplay_case_N (tab, x, graine);
				hv = hv_r;
			}
			else {
				int graine = tab[1][x];
				play_case_S (tab, x, pos, graine);
				recolte_S(tab, p_S, pos, rec);
				hv ^= hashSC[0][p_N->score] ^ hashSC[1][p_S->score] ^ hashP[1][x][graine];
				for (int i =0; i < 2; i++) {
					for (int j = 0; j < 6; j++) {
						hv ^= hashT[i][j][tab[i][j]];
					}
				}
				v = alpha_beta(alpha, b, - name, depth + 1, maxdepth, base, hv, hash_v, p_N, p_S, tab, best_move, hashSC, hashP, hashT);
				unrecolte_S(tab, p_S, rec);
				unplay_case_S (tab, x, graine);
				hv = hv_r;
			}
			
			if (name == NORD) {
				if (v > g) {
					lmove = x;
					if (base == depth) *best_move = x;
				}
				
				g = max(g,v);
				a = max(a,g);
				if (g >= beta) break; /* Beta cut */
			}
			
			else {
				if (v < g) {
					lmove = x;
					if (base == depth) *best_move = x;
				}
					
				g = min(g,v);
				b = min(b,g);
				if (g <= alpha) break; /* Alpha cut */
			}		
		}
	}


	store_v_hash(hv, alpha, beta, g, maxdepth-depth, base, lmove, hash_v);
	return g;
}
	
		
		
		
		
