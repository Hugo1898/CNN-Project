
#ifndef PRINT_GAME_H
#define PRINT_GAME_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_manager.h"


void print_intro(int tab[2][6], player* p_human, player* p_ordi);

void print_game(int tab[2][6], player *p_1, player *p_2);

void viderBuffer();

int lire(char *chaine, int longueur);


#endif
