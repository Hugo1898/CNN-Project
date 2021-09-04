
#ifndef IA_HASTABLE_H
#define IA_HASTABLE_H


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "game_manager.h"


#define NORD 1
#define SUD -1
#define WIN 32766
#define BWIN (WIN - 5000)
#define MAXV 32767
#define EXIT_ERROR 126



int max (int a, int b);

int min (int a, int b);

void make_indx(int *indx);

int alpha_beta(int alpha, int beta, int name, int depth, int maxdepth, int base, player *p_N, player *p_S, int tab[2][6], int *best_move);






#endif
