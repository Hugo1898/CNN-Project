CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror -O3 -I ./include 
LDFLAGS = -flto

	
run_awalé : awalé
	./$^
	
run_IA : IA_awalé
	./$^

run_awalé_hash : awalé_hash
	./$^
	
run_IA_hash : IA_awalé_hash
	./$^
	
	
awalé: awalé.o print_game.o game_manager.o IA_alpha.o IA_game_manager.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
IA_awalé : IA_awalé.o IA_alpha.o IA_game_manager.o game_manager.o print_game.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
awalé_hash: awalé_hash.o print_game_hash.o game_manager_hash.o IA_hastable_hash.o IA_game_manager_hash.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
IA_awalé_hash : IA_awalé_hash.o IA_hastable_hash.o IA_game_manager_hash.o game_manager_hash.o print_game_hash.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $^

clean:
	find . -type f -executable -delete
	rm -Rf *.o 


