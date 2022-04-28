#include <iostream>

//Define global variables.
bool use_AI = true;
int P1_wins = 0;
int P2_wins = 0;
int draw = 0;
bool sim = false;
int turn = 0;
int difficulty = 0;
int board[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10 };
//Define functions.
int do_random();
void difficulty_select();
void reset_game();
bool again();
void draw_board();
void help();
int player_turn(int active_player, char XO, int turn);
void ai_turn(int difficulty, int turn);
bool move_invalid(int input);
bool check_win(int active_player);
void do_move(int active_player, int player_input);

int main(void)
{
	std::cout << "Welcome to tic - tac - toe!\n";
	bool input_invalid = true;
	char choice_multiplayer;
	while (input_invalid == true)
	{
		std::cout << "\nWill you be playing (s)olo or (m)ultiplayer?\nYou can also s(i)mulate 10,000 simulated games\n";
		std::cin >> choice_multiplayer;
		choice_multiplayer = toupper(choice_multiplayer);
		if (choice_multiplayer == 'S')
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			use_AI = true;
			input_invalid = false;
      		difficulty_select();
		}
		else if (choice_multiplayer == 'M')
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			input_invalid = false;
			use_AI = false;
		}
		else if (choice_multiplayer == 'I')
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			input_invalid = false;
			sim = true;
			difficulty_select();
		}
		else
		{
			std::cout << "Error: Input Invalid\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}
	// Resets the values of board[] to 10, thus resetting the gamestate.
	reset_game();
	bool game_active = true;
	// Main loop of the game. game_active is only set to false when the player chooses to quit.
	while (game_active == true)
	{
		int active_player;
		char XO;
		turn++;
		draw_board();
		//If no winner by turn 9 the game is adraw.

		// Divide turn by 2. Player 1(X) always plays on odd turns, Player 2(O) on Even turns
		if (turn % 2 != 0)
		{
			active_player = 1;
			XO = 'X';
		}
		else
		{
			active_player = 2;
			XO = 'O';
		}

		//If use_AI is false, alternate between player 1 and player 2.
		if (use_AI == false)
		{
			std::cout << "Turn: "<< turn <<"\nPlayer 1: " << P1_wins << " Player 2 : " << P2_wins << " Draws: " << draw << "\n";
			player_turn(active_player, XO, turn);
		}
		else if (active_player == 1)
		{
			std::cout << "Turn: " << turn << "\nWins: " << P1_wins << " Losses : " << P2_wins << " Draws: " << draw <<  "\n";
			player_turn(active_player, XO, turn);
		}
		else
		{
			std::cout << "Turn: " << turn << "\nWins: " << P1_wins << " Losses : " << P2_wins << " Draws: " << draw << "\n";
			ai_turn(difficulty, turn);
		}

		//The game cannot be won before turn 5. Thus there is no reason to check for a winner before turn 5.
		if (turn >= 5)
		{
			if (check_win(active_player) == true)
			{
				draw_board();
				std::cout << "Player " << active_player << " wins!!!!\n";
				for (int win_print = 0; win_print < 30; win_print++)
				{
					std::cout << XO;
				}
				if (active_player == 1)
				{
					P1_wins++;
				}
				else
				{
					P2_wins++;
				}
				if (again() == true)
				{
					reset_game();
				}
				else
				{
					game_active = false;
				}

			}
		}
		if (turn == 9)
		{	
			draw_board();
			std::cout << "DRAW! There are no winners.\n";
			if (again() == true)
			{
				draw++;
				turn = 0;
				reset_game();
			}
			else
			{
				game_active = false;
			}
		}
	}

	std::cout << "Thank you for playing. \n";

}

void difficulty_select()
{
	bool input_invalid = true;
	do
	{
		std::cout << "Select difficulty. (E)asy, (M)edium, or (H)ard\n";
		char dif_select;
		std::cin >> dif_select;
		dif_select = toupper(dif_select);

		if (dif_select == 'E')
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			input_invalid = false;
		}
		else if (dif_select == 'M')
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			input_invalid = false;
			difficulty = 1;
		}
		else if (dif_select == 'H')
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			input_invalid = false;
			difficulty = 2;
		}
		else
		{
			std::cout << "Error: Input Invalid\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (input_invalid == true);
}

void reset_game()
{
	turn = 0;
	for (int i = 0; i < 9; i++)
	{
		board[i] = 10;
	}

}

bool again()
{
	if (sim == true)
	{
		if (P1_wins + P2_wins + draw == 10000)
		{
			std::cout << "\n10,000 games simulated.\n";
			return false;
		}
		return true;
	}
	else
	{
		bool input_invalid = true;
		do
		{
			std::cout << "\nDo you want to play again? y/n\n";
			char play_again;
			std::cin >> play_again;
			play_again = toupper(play_again);

			if (play_again == 'Y')
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				input_invalid = false;
				return true;
			}
			else if (play_again == 'N')
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				input_invalid = false;
				return false;
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (input_invalid == true);
	}

}

void draw_board()
{
	//Define an string array. ' ' will be replaced with X or O depending on the value of board[]
	std::string board_letters[] = { " ", " ", " ", " ", " ", " ", " ", " ", " "};
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == 2)
		{
			board_letters[i] = "O";
		}
		else if (board[i] == 1)
		{
			board_letters[i] = "X";
		}
		else
		{
			board_letters[i] = " ";
		}
	}
	//Print the board
	std::cout << "\n " << board_letters[0] << " | " + board_letters[1] << " | " << board_letters[2] << " \n";
	std::cout << "___|___|___\n";
	std::cout << " " << board_letters[3] << " | " << board_letters[4] << " | " << board_letters[5] << " \n";
	std::cout << "___|___|___\n";
	std::cout << " " << board_letters[6] << " | " << board_letters[7] << " | " << board_letters[8] << " \n";
	std::cout << "   |   |   \n";
}

void help()
{
	//Draw a simplified board and explain the rules of the game.
	std::cout << "In tic-tac-toe two players take turns marking the spaces in a three-by-three grid with X or O. The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row is the winner.";
	std::cout << "In this program you will enter a number between 1-9 to place your X or O on the grid.\n";
			// Draw a sample grid.
			std::cout << " 1 | 2 | 3 \n";
			std::cout << "___|___|___\n";
			std::cout << " 4 | 5 | 6 \n";
			std::cout << "___|___|___\n";
			std::cout << " 7 | 8 | 9 \n";
			std::cout << "   |   |   \n";
}

bool move_invalid(int input)
{
	if (board[input] != 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int do_random()
{
	int random;
	bool retryroll = true;
	//Random rolls are being placed in a function to reduce redundancy. While rand exists as a function this saves me having to write the move_invalid calls multiple times in different places.
	do
	{
		random = rand() % 9;
		if (move_invalid(random) == false)
		{
			retryroll = false;
		}
	} while (retryroll == true);
	return random;
}

void do_move(int active_player, int player_input)
{
	board[player_input] = active_player;
}

bool check_win(int active_player)
{
	// Horizontal wins
	if (board[0] == active_player && board[1] == active_player && board[2] == active_player)
	{
		return true;
	}
	else if (board[3] == active_player && board[4] == active_player && board[5] == active_player)
	{
		return true;
	}
	else if (board[6] == active_player && board[7] == active_player && board[8] == active_player)
	{
		return true;
	}
	//Vertical Wins
	else if (board[0] == active_player && board[3] == active_player && board[6] == active_player)
	{
		return true;
	}
	else if (board[1] == active_player && board[4] == active_player && board[7] == active_player)
	{
		return true;
	}
	else if (board[2] == active_player && board[5] == active_player && board[8] == active_player)
	{
		return true;
	}
	//Diagonal wins
	else if (board[0] == active_player && board[4] == active_player && board[8] == active_player)
	{
		return true;
	}
	else if (board[2] == active_player && board[4] == active_player && board[6] == active_player)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int player_turn(int active_player, char XO, int turn)
{
	if (sim == true)
	{
		int x = 0;
		int o = 0;
		for (int i = 0; i < 10; i++)
		{
			if (board[i] == 1)
			{
				x++;
			}
			else if (board[i] == 2)
			{
				o++;
			}
		}
		if (turn > 1)
		{
			if (o > x || o > turn / 2)
			{
				std::cout << "HALT! CHEAT!";
				std::cin >> o;
			}
		}
		if (turn < 10)
		{
			do_move(1, do_random());
		}
	}
	else
	{
		bool input_invalid = true;
		while (input_invalid == true)
		{
			int player_input;
			// input_number = std::stoi(player_input);
			std::cout << "Player " << active_player << ": Enter number (1-9) to place your " << XO << "\n";
			std::cin >> player_input;
			if (player_input < 10 && player_input > 0)
			{
				//Computer begins counting at 0 and the playgrid reflects this. Most users would probably prefer 1-9 and thus this subtracts 1 from the input bringing it in line with expectations.
				player_input = player_input - 1;
				if (move_invalid(player_input) == false)
				{
					input_invalid = false;
					do_move(active_player, player_input);
				}
				else
				{
					std::cout << "Error: This space is already occupied.\n";
				}

			}
			else
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				help();
				system("pause");
				draw_board();
			}
		}
	}

	return 0;
	}

void ai_turn(int difficulty, int turn)
{
	//retry bool is used in various places below and serves as a gate. If a move has already been made this turn the AI will not attempt to make another move.
	bool retry = true;
	//Check difficulty and follow appropriate algorithms.
	//Easy difficulty will simply pick a number between 0-8 and attempt to play that square on the grid. It has no strategy and will not attempt to win if possible.
	if (difficulty == 0)
	{
		do_move(2, do_random());
	}
	//Medium Difficulty will actually look to counter the player but can be mislead; It does not actively seize upon victories.
	//Hard difficulty is impossible to beat. It will both counter the players moves and seize upon opportunities for victory.
	if (difficulty >= 1)
	{
		//Define variables and arrays that will be used in the follow checks.
		int top[] = { 0, 1, 2 };
		int center[] = { 3, 4, 5 };
		int bottom[] = { 6, 7, 8 };
		int wincheck[3];
		bool hard_first_pass = false;
		int current_player_check = 1;
		do
		{
			
			//If difficulty == hard then the algorithm will check for optimal turn 2 moves based on the players opening move.
			if (turn == 2 && difficulty == 2)
			{
				if (board[4] == 1 && retry == true || board[3] == 1 && retry == true)
				{
					do_move(2, 0);
					retry = false;
				}
				else if (board[5] == 1 && retry == true)
				{
					do_move(2, 2);
					retry = false;
				}
				else if (board[7] == 1 && retry == true)
				{
					do_move(2, 1);
					retry = false;
				}
				else if (move_invalid(4) == false && retry == true)
				{
					do_move(2, 4);
					retry = false;
				}
			}
			//If difficulty == medium the AI will play a random corner on turn 2 or the center if available.
			else if (turn == 2 && difficulty == 1 && retry == true)
			{
				if (board[4] == 1)
				{
					int corner[4] = { 0, 2, 6, 8 };
					int ai_input = rand() % 4;
					ai_input = corner[ai_input];
					retry = false;
					do_move(2, ai_input);
				}
				else
				{
					do_move(2, 4);
					retry = false;
				}

			}
			//If the difficulty is set the hard the AI will run a seperate pass over the board to actively check to see if it can win.If there are no winning moves it will attemt to play a perfect counter move to the players current input.
			//If there is no winning move or counter move the AI will play in a random square.
			if (turn > 4 && difficulty == 2 && hard_first_pass == false)
			{
				current_player_check = 2;
				hard_first_pass = true;
			}




			// Check horizontal plays for potential wins.
			for (int horizon = 0; horizon < 3; horizon++)
			{
				if (horizon == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						wincheck[i] = top[i];
					}
				}
				else if (horizon == 1)
				{
					for (int i = 0; i < 3; i++)
					{
						wincheck[i] = center[i];
					}
				}
				else if (horizon == 2)
				{
					for (int i = 0; i < 3; i++)
					{
						wincheck[i] = bottom[i];
					}
				}


				if (board[wincheck[0]] == current_player_check && board[wincheck[1]] == current_player_check && move_invalid(wincheck[2]) == false && retry == true)
				{
					retry = false;
					do_move(2, wincheck[2]);
				}
				else if (board[wincheck[1]] == current_player_check && board[wincheck[2]] == current_player_check && move_invalid(wincheck[0]) == false && retry == true)
				{
					retry = false;
					do_move(2, wincheck[0]);
				}
				else if (board[wincheck[0]] == current_player_check && board[wincheck[2]] == current_player_check && move_invalid(wincheck[1]) == false && retry == true)
				{
					retry = false;
					do_move(2, wincheck[1]);
				}
			}
			//Check vertical columns for potential wins.

			for (int vertical = 0; vertical < 3; vertical++)
			{
				if (board[top[vertical]] == current_player_check && board[center[vertical]] == current_player_check && move_invalid(bottom[vertical]) == false && retry == true)
				{
					retry = false;
					do_move(2, bottom[vertical]);
				} 
				else if (board[top[vertical]] == current_player_check && board[bottom[vertical]] == current_player_check && move_invalid(center[vertical]) == false && retry == true)
				{
					retry = false;
					do_move(2, center[vertical]);
				}
				else if (board[center[vertical]] == current_player_check && board[bottom[vertical]] == current_player_check && move_invalid(top[vertical]) == false && retry == true)
				{
					retry = false;
					do_move(2, top[vertical]);
				}
			}
			//Check if taking the center (4) would win the game. Only checks on hard difficulty leaving an intentional exploit in medium.
			if (board[0] == current_player_check && board[8] == current_player_check && move_invalid(4) == false && difficulty == 2 && retry == true || board[6] == current_player_check && board[2] == current_player_check && move_invalid(4) == false && difficulty == 2 && retry == true)
			{
				retry = false;
				do_move(2, 4);
			}
			//Check diagonal plays for potential wins.
			if (board[4] == current_player_check && retry == true)
			{
				if (board[0] == current_player_check && move_invalid(8) == false && retry == true)
				{
					retry = false;
					do_move(2, 8);
				}
				else if (board[8] == current_player_check && move_invalid(0) == false && retry == true)
				{
					retry = false;
					do_move(2, 0);
				}
				else if (board[2] == current_player_check && move_invalid(6) == false && retry == true)
				{
					retry = false;
					do_move(2, 6);
				}
				else if (board[6] == current_player_check && move_invalid(2) == false && retry == true)
				{
					retry = false;
					do_move(2, 2);
				}
			}
				
			//Turn 4 is a critical turn in tic-tac-toe. The following plays ideal counters depending on the players current Xs.
			if (turn == 4 && difficulty == 2 && retry == true)
			{
				if (board[7] == 1 && retry == true)
				{
					if (board[3] == 1 && retry == true || board[5] == 1 && retry == true)
					{
						if (board[0] == 2)
						{
							do_move(2, 2);
							retry = false;
						}
						else if (board[1] == 2 && retry == true)
						{
							do_move(2, 6);
							retry = false;
						}
					}
					else if (board[2] == 1 && retry == true || board[0] == 1 && retry == true)
					{
						do_move(2, 6);
						retry = false;
					}
					else if (board[4] == 1 && retry == true || board[1] == 1 && retry == true)
					{
						do_move(2, 0);
						retry = false;
					}
				}

				if (board[4] == 1 && retry == true)
				{
					if (board[6] == 1 || board[8] == 1)
					{
						do_move(2, 2);
						retry = false;
					}
				}
				//If center still hasn't been taken by turn 4 and more pressing conditions are not met, take the center.
				if (move_invalid(4) == false && retry == true)
				{
					do_move(2, 4);
					retry = false;
				}

				if (board[4] == 2 && retry == true)
				{
					if (board[8] == 1 && board[0] == 1 && retry == true || board[6] == 1 && board[2] == 1 && retry == true)
					{
						do_move(2, 1);
						retry = false;
					}
				}

				if (board[1] == 1 && retry == true)
				{
					if (board[5] == 1 && move_invalid(2) == false && retry == true || board[6] == 1 && move_invalid(2) == false && retry == true)
					{
						do_move(2, 2);
						retry = false;
					}
					else if (board[3] == 1 && move_invalid(0) == false && retry == true || board[8] == 1 && move_invalid(0) == false && retry == true)
					{
						do_move(2, 0);
						retry = false;
					}
				}
				else if (board[7] == 1 && retry == true)
				{
					if (board[5] == 1 && move_invalid(8) == false && retry == true || board[2] == 1 && move_invalid(8) == false && retry == true)
					{
						do_move(2, 8);
						retry = false;
					}
					else if (board[3] == 1 && move_invalid(6) == false && retry == true || board[0] == 1 && move_invalid(6) == false && retry == true)
					{
						do_move(2, 6);
						retry = false;
					}
				}
				else if (board[3] == 1 && retry == true)
				{
					if (board[2] == 1 && move_invalid(0) == false && retry == true)
					{
						do_move(2, 0);
						retry = false;
					}
					else if (board[8] == 1 && move_invalid(6) == false && retry == true)
					{
						do_move(2, 6);
						retry = false;
					}
				}
				else if (board[5] == 1 && retry == true)
				{
					if (board[0] == 1 && move_invalid(2) == false && retry == true)
					{
						do_move(2, 2);
						retry = false;
					}
					else if (board[6] == 1 && move_invalid(8) == false && retry == true)
					{
						do_move(2, 8);
						retry = false;
					}
				}
			}

			//If center square is still not taken by turn 5, attempt to take it.
			if (turn >= 5 && move_invalid(4) == false && retry == true && current_player_check == 1)
			{
				do_move(2, 4);
				retry = false;
			}

			//If playing on medium and no counter move was played above the AI will play a random square; it will not seize upon any chance for victory and will deliberately have a chance to blunder.
			//If running on hard difficulty and the script has made it this far it will change the player check from 2 to 1, switching from seizing upon victory to actively countering the player.
			if (retry == true)
			{
				if (difficulty == 2 && hard_first_pass == true && current_player_check == 1 && retry == true || difficulty == 1 && retry == true)
				{
					if (move_invalid(4) == false && retry == false)
					{
						do_move(2, 4);
						retry == false;
					}
					else if (retry == true)
					{
						do_move(2, do_random());
						retry = false;
					}
				}

				if (difficulty == 2 && hard_first_pass == true)
				{
					current_player_check = 1;
				}
			}

		} while (retry == true);
	}

}