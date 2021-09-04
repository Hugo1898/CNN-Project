
#ifndef IA_HASTABLE_H
#define IA_HASTABLE_H

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>



#define FALSE 0
#define TRUE 1
#define NORD 1
#define SUD -1
#define NB_BITS 28
#define HASH_SIZE (1<<NB_BITS)
#define HASH_MASK (HASH_SIZE-1)
#define WIN 32766
#define BWIN (WIN - 5000)
#define MAXV 32767
#define EXIT_ERROR 126



struct
__attribute__((packed))
hash_type {
	uint64_t sig;
	int16_t v_inf,v_sup;
	uint8_t bmove;
	uint8_t base;
	uint8_t dist;
};

typedef struct hash_type hash_type;

#include "game_manager_hash.h"

int16_t max (int16_t a, int16_t b);

int16_t min (int16_t a, int16_t b);

void make_indx(int *indx);

uint64_t rand_v();

void init_hash(uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]);

int retrieve_v_hash(uint64_t hv, int dist, int *v_inf, int *v_sup, int *bmove, hash_type *hash_v);

void store_v_hash_both(uint64_t hv, int v, int dist, int base, int move, hash_type *hash_v);

void store_v_hash(uint64_t hv, int alpha, int beta, int g, int dist, int base, int move, hash_type *hash_v);

int alpha_beta(int alpha, int beta, int name, int depth, int maxdepth, int base, uint64_t hv, hash_type *hash_v, player *p_N, player *p_S, int tab[2][6], int *best_move, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]);






#endif
