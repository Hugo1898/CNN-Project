
#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>



typedef struct player player;

struct player {
	char name;
	int score;
};

#include "IA_hastable_hash.h"

void play_turn_human(player *p_turn, player *p_other, int tab[2][6], uint64_t *hv, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]);

void play_turn_ordi(player *p_turn, player *p_other, int tab[2][6], uint64_t *hv, hash_type *hash_v, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49], int base);

void play_case_N (int tab[2][6], int x, int pos[2], int graine);

void play_case_S (int tab[2][6], int x,int pos[2], int graine);

void recolte_N(int tab[2][6], player *p_turn, int pos[2], int rec[6]);

void recolte_S(int tab[2][6], player *p_turn, int pos[2], int rec[6]);

void unrecolte_S(int tab[2][6], player *p_turn, int rec[6]);

void unrecolte_N(int tab[2][6], player *p_turn, int rec[6]);

void unplay_case_S(int tab[2][6], int x, int graine);

void unplay_case_N (int tab[2][6], int x, int graine);

int test_feed_N(int tab[2][6], int only[6], player *p_turn);

int test_feed_S(int tab[2][6], int only[6], player *p_turn);

void end_game(int tab[2][6], player *p_1, player *p_2, int *end);



#endif
