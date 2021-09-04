
Pour lancer le jeu d'awalé il suffit de taper la commande :
- make run_awalé (pour une IA codée en alpha-beta iterative deepening)
- make run_awalé_hash (pour une IA codée en alpha-beta hastable best move iterative deepening)

Pour les deux IA tout fonctionne parfaitement. Aucun coup interdit n'est autorisé, si l'IA bug le programme s'arrête directement !
L'IA donne toujours une réponse entre 5 et 10 secondes, si vous voulez augmenter ou diminuer cette durée il faut modifier la limite de ftime dans la boucle while de la 
fonction choice_IA des fichiers IA_game_manager.c et IA_game_manager_hash.c. 

Si vous voulez juste tester les IA pour voir ce qu'elles renvoient lors du premier tour d'un début de partie commencé par le joueur Nord il faut taper la commande :
- make run_IA (pour l'IA codée en alpha-beta iterative deepening)
- make run_IA_hash (pour l'IA codée en alpha-beta hastable best move iterative deepening)

Pour jouer vous disposez de 3 modes de jeu :
- mode 1 joueur où vous jouez contre l'IA.
- mode 2 joueurs où vous pouvez jouer contre un ami à vous.
- mode spectateur où vous pouvez admirer une partie acharnée de l'IA contre elle-même. 

La fonction d'évaluation se trouve dans les fichiers sources IA_game_manager.c et IA_game_manager_hash.c 
Le code de l'IA codée en alpha-beta iterative deepening se trouve dans le fichier IA_alpha.c
Le code de l'IA codée en alpha-beta hastable best move iterative deepening se trouve dans le fichier IA_hastable_hash.c

Les règles de l'awalé utilisées pour coder ce jeu proviennent du site suivant que vous pouvez consulter si besoin :
http://www.lecomptoirdesjeux.com/l-awale.htm

BON JEU !!!
