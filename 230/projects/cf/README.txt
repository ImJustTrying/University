My program works as follows: First we declare a moves array and a board array, which will contain
the moves of each player and the current game state. We pass the board and moves array to game_loop
which contains the main loop for the game. We initialize the arrays and do other setup in init_game
and procede to begin the game. The user is prompted if they would like to go first and they or the
AI will make a move. The AI move is done by prompt_ai_turn and the user is prompted for a turn in
prompt_player_turn. The AI move is the most complicated part, which requires other helper functions
(e.g. check_neighbors, insert_after_series, etc) that help traverse the board and do the reasoning
necessary to have the AI make smarter moves.

Video demonstration: https://youtu.be/dUd7wTj95_U
