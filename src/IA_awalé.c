
#include <time.h>
#include "IA_game_manager.h"
#include "IA_alpha.h"
#include "print_game.h"
#include "game_manager.h"

int main() {
	player *p_N = calloc(1, sizeof(player));
	p_N->name = 'N';
	player *p_S = calloc(1, sizeof(player));
	p_S->name = 'S';
	int tab[2][6] = {{4, 4, 4, 4, 4, 4}, {4, 4, 4, 4, 4, 4}};

	int best_move;
	int ret, maxdepth;
	clock_t time, otime;
	double ftime;
  
	int base = 0;
	maxdepth = base;
	otime = clock();
	do {
	maxdepth++;
	best_move = -1;
	ret = alpha_beta(- MAXV, MAXV, NORD, base, maxdepth, base, p_N, p_S, tab, &best_move);
	time = clock()- otime;
	ftime = (double)time/(double)CLOCKS_PER_SEC;
	printf("best_move=%d ret=%d base=%d maxdepth=%d time=%f\n", best_move, ret, base, maxdepth, ftime);
	if (best_move == -1) {printf("error -1\n");exit(EXIT_ERROR);}
	if (best_move >= 6) {printf("error SIZE\n");exit(EXIT_ERROR);}
	if (tab[0][best_move] == 0) {printf("error EMPTY\n");exit(EXIT_ERROR);}
	} 
	while ((ftime <= 60.0) && abs(ret) < BWIN);
	
	return 0;
}
