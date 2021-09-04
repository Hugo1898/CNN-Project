
#ifndef IA_GAME_MANAGER_H
#define IA_GAME_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_manager.h"

int eval(int tab[2][6], int x, int name, player *p_N, player *p_S);

int choice_IA(int tab[2][6], int base, player *p_ordi, player *p_human);

#endif
