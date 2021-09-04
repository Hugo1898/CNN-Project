
#ifndef IA_GAME_MANAGER_H
#define IA_GAME_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "IA_hastable_hash.h"
#include "game_manager_hash.h"

int eval(int tab[2][6], int x, int name, player *p_N, player *p_S);

int choice_IA(int tab[2][6], int base, player *p_ordi, player *p_human, uint64_t hv, hash_type *hash_v, uint64_t hashSC[2][49], uint64_t hashP[2][6][49], uint64_t hashT[2][6][49]);

#endif
