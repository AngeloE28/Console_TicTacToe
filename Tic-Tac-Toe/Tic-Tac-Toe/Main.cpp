#include <iostream>
#include <conio.h> // Used for _getch()
#include <string>
#include <Windows.h> // Used for Sleep

using namespace std;

// Matrix that contains all the information of the game board Tic-Tac-Toe
char board[3][3];

// To determine whose turn it is and simplifies which
// letter to draw in the board[][]
// Initially starts with player 1 upon first time loading of the game
// will continually toggle it using togglePlayer() for the duration that
// the game is running
char turn = 'X';

// Boolean to store if player has quit
// If the game has finished and
// if player can input during the game
bool playerHasQuit = false;
bool isGameFinished = false;
bool canPlayerInput = true;

// Boolean for the playPVC() function
// to allow the compiler to display the computer's score
bool isComputerPlaying = false;

// Variables to store players names and
// the title of the game mode
string players;
string player1, player2;
string gameModeTitle;

// Variable to store Computer wins
// Only for the playPVC() game mode
int computerScore = 0;


// Screen to show Main menu and options for Main Menu
enum Menu {
	MENU = 100,
	PLAY = 1,
	INSTRUCTIONS = 2,
	CREDITS = 3,
	QUIT = 4,
};

// Screen to show Game Mode Sub Menu and its options
// P is player
// C is computer
// V is verses
enum MODE {
	MODE_MENU = 100,
	PVP = 1,
	PVC = 2,
	CVC = 3,
	BACK = 4,
};

// Initialise the functions

// The menu functions
int showMenu();
int showGameModeSubMenu();
int GameMode();

// The game modes
void playPVP();
void playPVC();
void playCVC();

// The functions for input and how to end the game
void playerInput();
void computerInput();
void computerWinInput();
bool computerWinning();
char gameOver();

// Utility functions
void togglePlayer();
void toggleName();
void drawBoard();
void fill();

// Screens to show how to play the game and who made it
void showInstructions();
void showCredits();
void showQuitScreen();

// Starts the program
int main()
{
	int screen = MENU; // Set 'screen' to the main menu

	// This loop is controlled by the choices made in 'showMenu()'
	while (screen != QUIT) {
		if (screen == MENU) {

			// Shows the main menu, and stores the player's choice in the 'screen' variable
			screen = showMenu();
		}
		else if (screen == PLAY) {
			screen = GameMode();

			// Returns to the main menu when showGameModeSubMenu() is finished.
			screen = MENU;
		}
		else if (screen == INSTRUCTIONS) {
			showInstructions();	// Shows the instructions screen

			// Returns to the main menu when showInstructions() is finished.
			screen = MENU;
		}
		else if (screen == CREDITS) {
			showCredits();	// Shows the credits screen

			// Returns to the main menu when showCredits() is finished.
			screen = MENU;
		}
	}

	// Quit was chosen, ending while loop.
	// Shows a quit screen
	showQuitScreen();

	return 0;
}

/***********************************************************************/
//					 The Menu Functions for the UI
/***********************************************************************/
// Shows menu and waits for valid choice. (see enum Menu)
// Input is player's choice.
// Checks if choice is valid.
// Output is choice made by player.
int showMenu()
{
	// Initialise to a choice player would likely never make
	int choice = -1;
	cout << "\n\n";
	cout << "\t" << "--------------------------------------" << endl;
	cout << "\t\t" << "Welcome to Toe-Tac-Tic" << endl;
	cout << "\t" << "--------------------------------------" << "\n\n";
	cout << "\t\t" << "   [1] Play" << endl;
	cout << "\t\t" << "   [2] Instructions" << endl;
	cout << "\t\t" << "   [3] Credits" << endl;
	cout << "\t\t" << "   [4] Quit" << "\n\n";
	cout << "\t\t" << "Enter your choice > ";
	cin >> choice;
	if (choice == 1) {
		choice = PLAY;
	}
	else if (choice == 2) {
		choice = INSTRUCTIONS;
	}
	else if (choice == 3) {
		choice = CREDITS;
	}
	else if (choice == 4) {
		choice = QUIT;
	}
	else {	// Check to make sure that player is making a valid choice
		cout << "\n\t" << " ERROR: Invalid choice!" << "\n\n";
		cout << "\t Only enter a number from the menu options available: " <<
			"[1] [2] [3] [4]" << endl;
		Sleep(1500);	// Creates a 1.5 second delay
		choice = MENU;
		system("cls");	// Clears screen
	}
	//system("cls");
	return choice;
}

// Shows the game mode sub menu.
// Determines which version of tic-tac-toe player wants to play.
int showGameModeSubMenu()
{
	system("cls");	// Clears screen
	int choice;
	cout << "\n\n";
	cout << "\t" << "--------------------------------------" << endl;
	cout << "\t\t" << " Choose Your Game Mode" << endl;
	cout << "\t" << "--------------------------------------" << "\n\n";
	cout << "\t\t"<< " [1]: Player Vs Player" << endl;
	cout << "\t\t"<< " [2]: Player Vs Computer" << endl;
	cout << "\t\t" << " [3]: Computer Vs Computer" << endl;
	cout << "\t\t"<< " [4]: Back" << "\n\n";
	cout << "\t" << "Enter your choice > ";
	cin >> choice;

	if (choice == 1) {
		choice = PVP;
	}
	else if (choice == 2) {
		choice = PVC;
	}
	else if (choice == 3) {
		choice = CVC;
	}
	else if (choice == 4) {
		choice = BACK;
	}
	else {	// Check to make sure that player is making a valid choice
		cout << "\n\t" << " ERROR: Invalid choice!" << "\n\n";
		cout << "\t" << " Only enter a number from the menu options available: " <<
			"[1] [2] [3] [4]" << endl;
		Sleep(1500);	// Creates a 1.5 second delay
		choice = MENU;
		system("cls");	// Clears screen
	}
	return choice;
}

// Starts version of tic-tac-toe player wants to play
// based on function showGameModeSubMenu()
int GameMode()
{
	int selected = MODE_MENU;

	while (selected != BACK) {	// Loops while player has not gone back
		if (selected == MODE_MENU) {
			selected = showGameModeSubMenu();
		}
		else if (selected == PVP) {
			gameModeTitle = " PVP Toe-Tac-Tic ";
			playPVP();	// Plays pvp gets winner

			selected = MODE_MENU;	// playPVC() has finished and returns player to showGameModeSubMenu()
		}
		else if (selected == PVC) {
			gameModeTitle = "Player Vs AI Toe-Tac-Tic ";
			playPVC();	// Plays pvc gets winner

			selected = MODE_MENU;	// playPVC() has finished and returns player to showGameModeSubMenu()
		}
		else if (selected == CVC) {
			gameModeTitle = "Taarminatoor Vs RoobooCoop\n\t\t\t     Toe-Tac-Tic";
			playCVC();	// Plays cvc gets winner

			selected = MODE_MENU;	// playCVC() has finished and returns player to showGameModeSubMenu()
		}
	}

	system("cls");	// Clears screen
	return selected;
}



/***********************************************************************/
//				The game modes that the player can play
/***********************************************************************/

// 2 Player mode of Tic-Tac-Toe
void playPVP()
{
	// Can player can input in this game mode
	canPlayerInput = true;
	system("cls");	// Clears screen
	cout << "\t" << "--------------------------------------" << endl;
	cout << "\t\t" << "Player vs Player" << endl;
	cout << "\t" << "--------------------------------------" << "\n\n";
	cout << "\t" << "Enter player 1(X) name: ";
	cin >> player1;
	system("cls");	// Clears screen
	cout << "\t" << "--------------------------------------" << endl;
	cout << "\t\t" << "Player vs Player" << endl;
	cout << "\t" << "--------------------------------------" << "\n\n";
	cout << "\t" << "Enter player 2(O) name: ";
	cin >> player2;
	system("cls");	// Clears screen

	// Populates the board
	fill();
	// First time draws the board
	drawBoard();
	while (playerHasQuit == false) {
		// Takes player input
		playerInput();
		// Will continue to redraw the board
		drawBoard();
		// Outcomes of the game
		// Sets both booleans isGameFinished and playerHasQuit 
		// to true to avoid any compiler misunderstandings
		if (gameOver() == 'X') {
			cout << "\t\t" << players << " wins!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		else if (gameOver() == 'O') {
			cout << "\t\t" << players << " wins!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		else if (gameOver() == '/') {
			cout << "\t\t" << "It's a draw!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		//Toggles the players to switch turns
		togglePlayer();
	}

	// A message asking if player would like to play again
	// will only appear if the game has finished
	if (isGameFinished == true) {
		cout << "\t\t" << "Would you like to play again? [Y] or [N] > ";
		char choice;
		cin >> choice;
		// If yes theN resets the booleans and recalles playPVP()
		if (choice == 'Y') {
			system("cls");
			playerHasQuit = false;
			isGameFinished = false;
			playPVP();
		}
		else if (choice == 'N') {
			cout << "\t\t" << "Loading..." << endl;
			Sleep(500);	// Creates a 0.5 second delay
			system("cls");
		}
	}
	// Reset playerHasQuit back to false
	playerHasQuit = false;
	system("cls");	// Clears the screen
}

// This is the single player game mode
// where the player fights an AI
// AI will either always win or force a draw
void playPVC()
{
	// Player can input in this game mode
	canPlayerInput = true;

	// Computer can input
	isComputerPlaying = true;

	system("cls");	// Clears screen
	cout << "\t" << "--------------------------------------" << endl;
	cout << "\t\t" << "Player vs Computer" << endl;
	cout << "\t" << "--------------------------------------" << "\n\n";
	cout << "\t" << "Enter player 1(X) name: ";
	cin >> player1;
	system("cls");	// Clears screen
	cout << "\n\n\t " << player1 << " is gonna have a bad time... \n\n";
	cout << "\t            ****************\n" <<
		"\t       *****                *****\n" <<
		"\t    ***                          ***\n" <<
		"\t   *                                *\n" <<
		"\t *                                    *\n" <<
		"\t *                                    *\n" <<
		"\t*                                      *\n" <<
		"\t*      *******            *******      *\n" <<
		"\t*    **     ***          **********    *\n" <<
		"\t*   **   *   **          ***********   *\n" <<
		"\t *  ***     **            **********  *\n" <<
		"\t *    *******      ***     *******    *\n" <<
		"\t  *       **      *****     **       *\n" <<
		"\t  *     ***       *****      ***     *\n" <<
		"\t *                *****               *\n" <<
		"\t *                                    *\n" <<
		"\t *     *                        *     *\n" <<
		"\t  *   ** **                  ** **   *\n" <<
		"\t  *    * **** **** **** *** *** *    *\n" <<
		"\t   *     **** **** **** *** ***     *\n" <<
		"\t    **     ** **** **** *** *     **\n" <<
		"\t      ****                    ****\n" <<
		"\t          ********************";
	Sleep(1000);	// 1 second delay
	player2 = "Computaar";	// AI name will be set to Computaar
	system("cls");	// Clears screen

	// Populates the board
	fill();
	// First time draws the board
	drawBoard();
	while (playerHasQuit == false) {
		// Takes player input
		if (turn == 'X') {
			playerInput();
		}
		// Takes the AI input
		else {
			cout <<"\t\t"<< player2 << " is thinking..." << endl;
			Sleep(1000);	// Adds a 1 second delay
			// Condition to make the computer go for the win if presented the chance
			// else will input for the most favourable spot or stop the other player from winning
			if (computerWinning() == true) {
				computerWinInput();
			}
			else {
				computerInput();
			}
		}
		// Will continue to redraw the board
		drawBoard();
		// Outcomes of the game
		// Sets both booleans isGameFinished and playerHasQuit 
		// to true to avoid any compiler misunderstandings
		// If computer wins, adds 1 to score of the computer
		if (gameOver() == 'X') {
			cout << "\t\t" << player1 << " wins!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		else if (gameOver() == 'O') {
			cout << "\t\t" << player2 << " wins!" << endl;
			computerScore += 1;
			isGameFinished = true;
			playerHasQuit = true;
		}
		else if (gameOver() == '/') {
			cout << "\t\t" << "It's a draw!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		//Toggles the players to switch turns
		togglePlayer();
	}

	// A message asking if player would like to play again
	// will only appear if the game has finished
	if (isGameFinished == true) {
		cout << "\t\t" << "Would you like to play again? [Y] or [N] > ";
		char choice;
		cin >> choice;
		// If yes theN resets the booleans and recalles playPVP()
		if (choice == 'Y') {
			system("cls");
			playerHasQuit = false;
			isGameFinished = false;
			playPVC();
		}
		else if (choice == 'N') {
			cout << "\t\t" << "Loading..." << endl;
			Sleep(500);	// Creates a 0.5 second delay
			system("cls");
		}
	}
	// Reset playerHasQuit and isComputerPlaying back to false
	playerHasQuit = false;
	isComputerPlaying = false;
	system("cls");	// Clears the screen
}

// This is the game mode where two
// AIs fight each other
void playCVC()
{
	// Player can't input in this game mode
	canPlayerInput = false;
	system("cls");	// Clears screen
	cout << "\t" << "--------------------------------------" << endl;
	cout << "\t\t" << "Computer vs Computer" << endl;
	cout << "\t" << "--------------------------------------" << "\n\n";
	player1 = "Taarminator";
	player2 = "RoobooCoop";
	cout << "\n\n\t " << player1<<" and "<< player2<<"\n\t will player for your convenience";
	Sleep(1000);	// Creates a 1 second delay
	system("cls");	// Clears screen

	// Populates the board
	fill();
	// First time draws the board
	drawBoard();
	while (isGameFinished == false) {
		// Takes the AI input
		if (turn == 'X') {
			cout << "\t\t" << player1 << " is thinking..." << endl;
			Sleep(1000);	// Adds a 1 second delay
			// Condition to make the computer go for the win if presented the chance
			// else will input for the most favourable spot or stop the other player from winning
			if (computerWinning() == true) {
				computerWinInput();
			}
			else {
				computerInput();
			}
		}
		// Takes the AI input
		else {
			cout << "\t\t" << player2 << " is thinking..." << endl;
			Sleep(1000);	// Adds a 1 second delay
			// Condition to make the computer go for the win if presented the chance
			// else will input for the most favourable spot or stop the other player from winning
			if (computerWinning() == true) {
				computerWinInput();
			}
			else {
				computerInput();
			}
		}
		// Will continue to redraw the board
		drawBoard();
		// Outcomes of the game
		// Sets both booleans isGameFinished and playerHasQuit 
		// to true to avoid any compiler misunderstandings
		if (gameOver() == 'X') {
			cout << "\t\t" << player1 << " wins!" << endl;
			isGameFinished = true;
		}
		else if (gameOver() == 'O') {
			cout << "\t\t" << player2 << " wins!" << endl;
			isGameFinished = true;
		}
		else if (gameOver() == 'N') {
			cout << "\t\t" << "It's a draw!" << endl;
			isGameFinished = true;
		}
		//Toggles the players to switch turns
		togglePlayer();
	}

	// A message asking if player would like to play again
	// will only appear if the game has finished
	if (isGameFinished == true) {
		cout << "\t\t" << "Would you like to play again? [Y] or [N] > ";
		char choice;
		cin >> choice;
		// If yes theN resets the booleans and recalles playPVP()
		if (choice == 'Y') {
			system("cls");
			playerHasQuit = false;
			isGameFinished = false;
			playCVC();
		}
		else if (choice == 'N') {
			cout << "\t\t" << "Loading..." << endl;
			Sleep(500);	// Creates a 0.5 second delay
			system("cls");
		}
		// Resets boolean after game mode is finished
		canPlayerInput = true;
	}
	system("cls");	// Clears the screen
}


/***********************************************************************/
//		 The functions for input and how to end the game
/***********************************************************************/

// Takes a turn input by replacing the letter in the field
// with an 'X' or 'O'
// If turn gives an invalid input, error occurs, console will display error message and
// turn will be given another chance to input a valid input
void playerInput()
{
	toggleName();
	// The variable that stores the player's playerInput
	// and test if its a valid playerInput
	char input;
	cout << "\t" << "It's " << players << " turn. " << "Enter the letter of the field > ";
	cin >> input;

	// Normal playerInputs from A to I
	if (input == 'A') {
		if (board[0][0] == 'A') {
			board[0][0] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'B') {
		if (board[0][1] == 'B') {
			board[0][1] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'C') {
		if (board[0][2] == 'C') {
			board[0][2] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'D') {
		if (board[1][0] == 'D') {
			board[1][0] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'E') {
		if (board[1][1] == 'E') {
			board[1][1] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'F') {
		if (board[1][2] == 'F') {
			board[1][2] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'G') {
		if (board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'H') {
		if (board[2][1] == 'H') {
			board[2][1] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	else if (input == 'I') {
		if (board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else {
			cout << "Spot is already filled. Try again!" << endl;
			playerInput();
		}
	}
	// If playerInput is R, the board will be repopulated
	// effectively restarting the game
	else if (input == 'R') {
		fill();
	}
	// If playerInput is Q, playerHasQuit will equal true
	// which will break the game loop in the void playPVP() function
	else if (input == 'Q') {
		playerHasQuit = true;
	}
	// Makes sure the turn is giving a valid playerInput which is from A to I
	else {
		cout << "Invalid option. Try Again!" << endl;
		playerInput();
	}
}

// Input from computer, makes calculated choices to ensure victory
// or forces a draw
void computerInput()
{
	// turn will always be 'X'
	// If other player takes a corner first
	if (board[0][0] == 'X' || board[0][2] == 'X' ||
		board[2][0] == 'X' || board[2][2] == 'X') {
		// Checks to see if the other player is about to win and stops them
		// Rows
		// First row
		if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'C') {
			board[0][2] = turn;
		}
		else if (board[0][0] == 'A' && board[0][1] == 'X' && board[0][2] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[0][1] == 'B' && board[0][2] == 'X') {
			board[0][1] = turn;
		}
		// Second row
		else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'F') {
			board[1][2] = turn;
		}
		else if (board[1][0] == 'D' && board[1][1] == 'X' && board[1][2] == 'X') {
			board[1][0] = turn;
		}
		else if (board[1][0] == 'X' && board[1][1] == 'E' && board[1][2] == 'X') {
			board[1][1] = turn;
		}
		// Third row
		else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[2][0] == 'G' && board[2][1] == 'X' && board[2][2] == 'X') {
			board[2][0] = turn;
		}
		else if (board[2][0] == 'X' && board[2][1] == 'H' && board[2][2] == 'X') {
			board[2][1] = turn;
		}

		// Columns
		// First column
		else if (board[0][0] == 'A' && board[1][0] == 'X' && board[2][0] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][0] == 'D' && board[2][0] == 'X') {
			board[1][0] = turn;
		}
		// Second column
		else if (board[0][1] == 'B' && board[1][1] == 'X' && board[2][1] == 'X') {
			board[0][1] = turn;
		}
		else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'H') {
			board[2][1] = turn;
		}
		else if (board[0][1] == 'X' && board[1][1] == 'E' && board[2][1] == 'X') {
			board[1][1] = turn;
		}
		// Third column
		else if (board[0][2] == 'C' && board[1][2] == 'X' && board[2][2] == 'X') {
			board[0][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][2] == 'F' && board[2][2] == 'X') {
			board[1][2] = turn;
		}

		// Diagonals
		// '\' diagonal
		else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[0][0] == 'A' && board[1][1] == 'X' && board[2][2] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][1] == 'E' && board[2][2] == 'X') {
			board[1][1] = turn;
		}
		// '/' diagonal
		else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else if (board[0][2] == 'C' && board[1][1] == 'X' && board[2][0] == 'X') {
			board[0][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][1] == 'E' && board[2][0] == 'X') {
			board[1][1] = turn;
		}
		// If the other player is not about to win
		// Takes a spot which is most favourable if a corner is taken by the other player
		// which is to take the middle, then the sides
		else {

			if (board[1][1] == 'E') {
				board[1][1] = turn;
			}
			else if (board[0][1] == 'B') {
				board[0][1] = turn;
			}
			else if (board[1][0] == 'D') {
				board[1][0] = turn;
			}
			else if (board[1][2] == 'F') {
				board[1][2] = turn;
			}
			else if (board[2][1] == 'H') {
				board[2][1] = turn;
			}
			else if (board[1][1] == 'E') {
				board[1][1] = turn;
			}
			else if (board[0][0] == 'A') {
				board[0][0] = turn;
			}
			else if (board[0][2] == 'C') {
				board[0][2] = turn;
			}
			else if (board[2][0] == 'G') {
				board[2][0] = turn;
			}
			else if (board[2][2] == 'I') {
				board[2][2] = turn;
			}
		}
	}
	// If the other player takes the middle first
	else if (board[1][1] == 'X') {
		// Checks to see if the other player is about to win first
		// Rows
		// First row
		if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'C') {
			board[0][2] = turn;
		}
		else if (board[0][0] == 'A' && board[0][1] == 'X' && board[0][2] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[0][1] == 'B' && board[0][2] == 'X') {
			board[0][1] = turn;
		}
		// Second row
		else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'F') {
			board[1][2] = turn;
		}
		else if (board[1][0] == 'D' && board[1][1] == 'X' && board[1][2] == 'X') {
			board[1][0] = turn;
		}
		else if (board[1][0] == 'X' && board[1][1] == 'E' && board[1][2] == 'X') {
			board[1][1] = turn;
		}
		// Third row
		else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[2][0] == 'G' && board[2][1] == 'X' && board[2][2] == 'X') {
			board[2][0] = turn;
		}
		else if (board[2][0] == 'X' && board[2][1] == 'H' && board[2][2] == 'X') {
			board[2][1] = turn;
		}

		// Columns
		// First column
		else if (board[0][0] == 'A' && board[1][0] == 'X' && board[2][0] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][0] == 'D' && board[2][0] == 'X') {
			board[1][0] = turn;
		}
		// Second column
		else if (board[0][1] == 'B' && board[1][1] == 'X' && board[2][1] == 'X') {
			board[0][1] = turn;
		}
		else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'H') {
			board[2][1] = turn;
		}
		else if (board[0][1] == 'X' && board[1][1] == 'E' && board[2][1] == 'X') {
			board[1][1] = turn;
		}
		// Third column
		else if (board[0][2] == 'C' && board[1][2] == 'X' && board[2][2] == 'X') {
			board[0][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][2] == 'F' && board[2][2] == 'X') {
			board[1][2] = turn;
		}

		// Diagonals
		// '\' diagonal
		else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[0][0] == 'A' && board[1][1] == 'X' && board[2][2] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][1] == 'E' && board[2][2] == 'X') {
			board[1][1] = turn;
		}
		// '/' diagonal
		else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else if (board[0][2] == 'C' && board[1][1] == 'X' && board[2][0] == 'X') {
			board[0][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][1] == 'E' && board[2][0] == 'X') {
			board[1][1] = turn;
		}

		// If the other player is not about to win
		// Takes a spot which is most favourable if middle is taken by the other player
		// which is to take a corner first then the sides
		else {
			if (board[0][0] == 'A') {
				board[0][0] = turn;
			}
			else if (board[0][2] == 'C') {
				board[0][2] = turn;
			}
			else if (board[2][0] == 'G') {
				board[2][0] = turn;
			}
			else if (board[2][2] == 'I') {
				board[2][2] = turn;
			}
			else if (board[0][1] == 'B') {
				board[0][1] = turn;
			}
			else if (board[1][0] == 'D') {
				board[1][0] = turn;
			}
			else if (board[1][2] == 'F') {
				board[1][2] = turn;
			}
			else if (board[2][1] == 'H') {
				board[2][1] = turn;
			}
		}
	}
	// If the other player takes a side first
	else {
		// Checks to see if the other player is about to win and stops them
		// Rows
		// First row
		if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'C') {
			board[0][2] = turn;
		}
		else if (board[0][0] == 'A' && board[0][1] == 'X' && board[0][2] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[0][1] == 'B' && board[0][2] == 'X') {
			board[0][1] = turn;
		}
		// Second row
		else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'F') {
			board[1][2] = turn;
		}
		else if (board[1][0] == 'D' && board[1][1] == 'X' && board[1][2] == 'X') {
			board[1][0] = turn;
		}
		else if (board[1][0] == 'X' && board[1][1] == 'E' && board[1][2] == 'X') {
			board[1][1] = turn;
		}
		// Third row
		else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[2][0] == 'G' && board[2][1] == 'X' && board[2][2] == 'X') {
			board[2][0] = turn;
		}
		else if (board[2][0] == 'X' && board[2][1] == 'H' && board[2][2] == 'X') {
			board[2][1] = turn;
		}

		// Columns
		// First column
		else if (board[0][0] == 'A' && board[1][0] == 'X' && board[2][0] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][0] == 'D' && board[2][0] == 'X') {
			board[1][0] = turn;
		}
		// Second column
		else if (board[0][1] == 'B' && board[1][1] == 'X' && board[2][1] == 'X') {
			board[0][1] = turn;
		}
		else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'H') {
			board[2][1] = turn;
		}
		else if (board[0][1] == 'X' && board[1][1] == 'E' && board[2][1] == 'X') {
			board[1][1] = turn;
		}
		// Third column
		else if (board[0][2] == 'C' && board[1][2] == 'X' && board[2][2] == 'X') {
			board[0][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][2] == 'F' && board[2][2] == 'X') {
			board[1][2] = turn;
		}

		// Diagonals
		// '\' diagonal
		else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'I') {
			board[2][2] = turn;
		}
		else if (board[0][0] == 'A' && board[1][1] == 'X' && board[2][2] == 'X') {
			board[0][0] = turn;
		}
		else if (board[0][0] == 'X' && board[1][1] == 'E' && board[2][2] == 'X') {
			board[1][1] = turn;
		}
		// '/' diagonal
		else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'G') {
			board[2][0] = turn;
		}
		else if (board[0][2] == 'C' && board[1][1] == 'X' && board[2][0] == 'X') {
			board[0][2] = turn;
		}
		else if (board[0][2] == 'X' && board[1][1] == 'E' && board[2][0] == 'X') {
			board[1][1] = turn;
		}
		// If the other player is not about to win
		// Takes a spot which is most favourable
		// which is to take then the middle, then the sides
		else {

			if (board[1][1] == 'E') {
				board[1][1] = turn;
			}
			else if (board[0][1] == 'B') {
				board[0][1] = turn;
			}
			else if (board[1][0] == 'D') {
				board[1][0] = turn;
			}
			else if (board[1][2] == 'F') {
				board[1][2] = turn;
			}
			else if (board[2][1] == 'H') {
				board[2][1] = turn;
			}
			else if (board[1][1] == 'E') {
				board[1][1] = turn;
			}
			else if (board[0][0] == 'A') {
				board[0][0] = turn;
			}
			else if (board[0][2] == 'C') {
				board[0][2] = turn;
			}
			else if (board[2][0] == 'G') {
				board[2][0] = turn;
			}
			else if (board[2][2] == 'I') {
				board[2][2] = turn;
			}
		}
	}
}

// Function for computer to input the appropriate spot
// for computer to win
void computerWinInput() {
	// Rows
	// First row
	if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'C') {
		board[0][2] = turn;
	}
	else if (board[0][0] == 'A' && board[0][1] == 'O' && board[0][2] == 'O') {
		board[0][0] = turn;
	}
	else if (board[0][0] == 'O' && board[0][1] == 'B' && board[0][2] == 'O') {
		board[0][1] = turn;
	}
	// Second row
	else if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'F') {
		board[1][2] = turn;
	}
	else if (board[1][0] == 'D' && board[1][1] == 'O' && board[1][2] == 'O') {
		board[1][0] = turn;
	}
	else if (board[1][0] == 'O' && board[1][1] == 'E' && board[1][2] == 'O') {
		board[1][1] = turn;
	}
	// Third row
	else if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'I') {
		board[2][2] = turn;
	}
	else if (board[2][0] == 'G' && board[2][1] == 'O' && board[2][2] == 'O') {
		board[2][0] = turn;
	}
	else if (board[2][0] == 'O' && board[2][1] == 'H' && board[2][2] == 'O') {
		board[2][1] = turn;
	}

	// Columns
	// First column
	else if (board[0][0] == 'A' && board[1][0] == 'O' && board[2][0] == 'O') {
		board[0][0] = turn;
	}
	else if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'G') {
		board[2][0] = turn;
	}
	else if (board[0][0] == 'O' && board[1][0] == 'D' && board[2][0] == 'O') {
		board[1][0] = turn;
	}
	// Second column
	else if (board[0][1] == 'B' && board[1][1] == 'O' && board[2][1] == 'O') {
		board[0][1] = turn;
	}
	else if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'H') {
		board[2][1] = turn;
	}
	else if (board[0][1] == 'O' && board[1][1] == 'E' && board[2][1] == 'O') {
		board[1][1] = turn;
	}
	// Third column
	else if (board[0][2] == 'C' && board[1][2] == 'O' && board[2][2] == 'O') {
		board[0][2] = turn;
	}
	else if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'I') {
		board[2][2] = turn;
	}
	else if (board[0][2] == 'O' && board[1][2] == 'F' && board[2][2] == 'O') {
		board[1][2] = turn;
	}

	// Diagonals
	// '\' diagonal
	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'I') {
		board[2][2] = turn;
	}
	else if (board[0][0] == 'A' && board[1][1] == 'O' && board[2][2] == 'O') {
		board[0][0] = turn;
	}
	else if (board[0][0] == 'O' && board[1][1] == 'E' && board[2][2] == 'O') {
		board[1][1] = turn;
	}
	// '/' diagonal
	else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'G') {
		board[2][0] = turn;
	}
	else if (board[0][2] == 'C' && board[1][1] == 'O' && board[2][0] == 'O') {
		board[0][2] = turn;
	}
	else if (board[0][2] == 'O' && board[1][1] == 'E' && board[2][0] == 'O') {
		board[1][1] = turn;
	}
}

// Function to check if computer currently has a chance to win
// Returns true if the computer has a chance, else returns false
bool computerWinning()
{
	// Rows
	// First row
	if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'C') {
		return true;
	}
	else if (board[0][0] == 'A' && board[0][1] == 'O' && board[0][2] == 'O') {
		return true;
	}
	else if (board[0][0] == 'O' && board[0][1] == 'B' && board[0][2] == 'O') {
		return true;
	}
	// Second row
	else if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'F') {
		return true;
	}
	else if (board[1][0] == 'D' && board[1][1] == 'O' && board[1][2] == 'O') {
		return true;
	}
	else if (board[1][0] == 'O' && board[1][1] == 'E' && board[1][2] == 'O') {
		return true;
	}
	// Third row
	else if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'I') {
		return true;
	}
	else if (board[2][0] == 'G' && board[2][1] == 'O' && board[2][2] == 'O') {
		return true;
	}
	else if (board[2][0] == 'O' && board[2][1] == 'H' && board[2][2] == 'O') {
		return true;
	}

	// Columns
	// First column
	else if (board[0][0] == 'A' && board[1][0] == 'O' && board[2][0] == 'O') {
		return true;
	}
	else if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'G') {
		return true;
	}
	else if (board[0][0] == 'O' && board[1][0] == 'D' && board[2][0] == 'O') {
		return true;
	}
	// Second column
	else if (board[0][1] == 'B' && board[1][1] == 'O' && board[2][1] == 'O') {
		return true;
	}
	else if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'H') {
		return true;
	}
	else if (board[0][1] == 'O' && board[1][1] == 'E' && board[2][1] == 'O') {
		return true;
	}
	// Third column
	else if (board[0][2] == 'C' && board[1][2] == 'O' && board[2][2] == 'O') {
		return true;
	}
	else if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'I') {
		return true;
	}
	else if (board[0][2] == 'O' && board[1][2] == 'F' && board[2][2] == 'O') {
		return true;
	}

	// Diagonals
	// '\' diagonal
	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'I') {
		return true;
	}
	else if (board[0][0] == 'A' && board[1][1] == 'O' && board[2][2] == 'O') {
		return true;
	}
	else if (board[0][0] == 'O' && board[1][1] == 'E' && board[2][2] == 'O') {
		return true;
	}
	// '/' diagonal
	else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'G') {
		return true;
	}
	else if (board[0][2] == 'C' && board[1][1] == 'O' && board[2][0] == 'O') {
		return true;
	}
	else if (board[0][2] == 'O' && board[1][1] == 'E' && board[2][0] == 'O') {
		return true;
	}

	return false;
}

// Conditions to end the game
// A win or a draw
char gameOver()
{
	/*Conditions for the win*/
	// Rows for 'X'
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') {
		return 'X';
	}
	if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X') {
		return 'X';
	}
	if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X') {
		return 'X';
	}

	// Rows for 'O'
	if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') {
		return 'O';
	}
	if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O') {
		return 'O';
	}
	if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O') {
		return 'O';
	}

	// Columns for 'X'
	if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') {
		return 'X';
	}
	if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') {
		return 'X';
	}
	if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X') {
		return 'X';
	}
	// Columns for 'O'
	if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') {
		return 'O';
	}
	if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O') {
		return 'O';
	}
	if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O') {
		return 'O';
	}


	// Diagonal for 'X'
	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
		return 'X';
	}
	if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X') {
		return 'X';
	}
	// Diagonal for 'O'
	if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
		return 'O';
	}
	if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O') {
		return 'O';
	}
	/*End of conditions for the win*/

	// Condition for a draw
	// All spots have been replaced and there is no winner
	// Returns 'N' to indicate that the game is a draw
	if (board[0][0] != 'A' && board[0][1] != 'B' && board[0][1] != 'C' &&
		board[1][0] != 'D' && board[1][1] != 'E' && board[1][2] != 'F' &&
		board[2][0] != 'G' && board[2][1] != 'H' && board[2][2] != 'I') {
		return 'N';
	}
}


/***********************************************************************/
//			 Utility functions which toggles the names, turns
//		 populates the board and draws the board onto the screen
/***********************************************************************/

// Toggles the symbol for each player
// If turn is 'X' switches to 'O' and vice versa
void togglePlayer()
{
	if (turn == 'X') {
		turn = 'O';
	}
	else {
		turn = 'X';
	}
}

// Toggles the name being displayed
// If turn is 'X' shows player1 name else it switches to player2
void toggleName()
{
	if (turn == 'X') {
		players = player1;
	}
	else {
		players = player2;
	}
}

// Draws the title and the board for the game
// Clears the previous board when a new input is registered
void drawBoard()
{
	system("cls");

	cout << "\n\n";
	cout << "\t\t" << "--------------------------------------" << endl;
	// Conditional statements to properly place the titles of the game modes
	// without looking ugly
	if (canPlayerInput == false) {
		cout << "\t\t\t" << gameModeTitle << endl;
	}
	else {
	cout << "\t\t\t" << gameModeTitle << endl;
	}

	cout << "\t\t" << "--------------------------------------" << endl;
	// Displays the score of the computer
	if (isComputerPlaying == true) {
		cout << "\t\t\t" << player2 << " Score: [" << computerScore << "]\n\n";
	}
	// Displays the name of the two AI with a proper position
	if (canPlayerInput == false) {
		cout << "\t\t" << player1 << " (X) " << "\t" << player2 << " (O) " << "\n\n";
	}	// Displays the name of the two players instead
	else {
		cout << "\t\t" << player1 << " (X) " << "\t" << player2 << " (O) " << "\n\n";
	}
	cout << "\t\t\t\t" << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
	cout << "\t\t\t\t" << "---------" << endl;
	cout << "\t\t\t\t" << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
	cout << "\t\t\t\t" << "---------" << endl;
	cout << "\t\t\t\t" << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
	cout << "\n\n";
	// Shows that player can restart the game or quit only if player can input in a game mode
	if (canPlayerInput == true) {
		cout << "\t\t\t" << "Enter 'Q' to quit or 'R' to restart" << "\n\n";
	}
}

// Populates the 2D matrix with the letters A to I
// in alphabetical order going from left to right
// will also be used to reset the board
void fill()
{
	board[0][0] = 'A';
	board[0][1] = 'B';
	board[0][2] = 'C';

	board[1][0] = 'D';
	board[1][1] = 'E';
	board[1][2] = 'F';

	board[2][0] = 'G';
	board[2][1] = 'H';
	board[2][2] = 'I';
}


/***********************************************************************/
// Screens to show how to play the game, who made it and a quit screen
/***********************************************************************/

// Shows the credits screen
// Shows who made the game
void showCredits()
{
	system("cls");	// Clears  screen
	cout << "\n\t\t Created By: Angelo Estoque\n\n";
	cout << "\t\t   Thank you for playing! \n";
	cout << "\n\t---------------------------------------------------\n";
	cout << "\t\tPress any key to return to the menu.           \n";
	cout << "\t---------------------------------------------------\n";
	_getch();       // Waits for keypress
	system("cls");  // Clears screen
	cout << "\n\tLoading...";
	Sleep(250);	// Adds a 0.25 second delay
	system("cls");	// Clears screen
}

// Shows the instructions screen
// Tells player how to play the game
void showInstructions()
{
	system("cls");	// Clears screen
	cout << "\t\t Toe-Tac-Tic\n\n";
	cout << "\t Choose a cell lettered from A to I as below.\n";
	cout << "\t Enter the letter and try to win.\n\n";
	cout << "\t\t  A | B | C\n";
	cout << "\t\t -----------\n";
	cout << "\t\t  D | E | F\n";
	cout << "\t\t -----------\n";
	cout << "\t\t  G | H | I\n\n";

	cout << "\t To win you need to get a three of a kind (shown below with 'X')\n\n";
	cout << "\t\t[ X | X | X ]\n";
	cout << "\t\t -----------\n";
	cout << "\t\t  D | E | F\n";
	cout << "\t\t -----------\n";
	cout << "\t\t  G | H | I\n";
	cout << "\n\t---------------------------------------------------\n";
	cout << "\t\tPress any key to return to the menu.          \n";
	cout << "\t---------------------------------------------------\n";
	_getch();	// Waits for keypress
	system("cls");	// Clears screen
	cout << "\n\tLoading...";
	Sleep(250);	// Adds a 0.25 second delay
	system("cls");	// Clears screen
}

void showQuitScreen()
{
	system("cls"); // Clears screen
	cout << "\n\t\t    See you next time\n\n";

	cout << "\t            ****************\n" <<
		"\t       *****                *****\n" <<
		"\t    ***                          ***\n" <<
		"\t   *                                *\n" <<
		"\t *                                    *\n" <<
		"\t *                                    *\n" <<
		"\t*                                      *\n" <<
		"\t*      ******             **     **    *\n" <<
		"\t*    **     **              **  **     *\n" <<
		"\t*   **       **               **       *\n" <<
		"\t *   **     **              **  **    *\n" <<
		"\t *    *******      ***    **      **  *\n" <<
		"\t  *               *****              *\n" <<
		"\t  *               *****              *\n" <<
		"\t *                *****               *\n" <<
		"\t *                                    *\n" <<
		"\t *     *                        *     *\n" <<
		"\t  *   ** **                  ** **   *\n" <<
		"\t  *    * **** **** **** *** *** *    *\n" <<
		"\t   *     **** **** **** *** ***     *\n" <<
		"\t    **     ** **** **** *** *     **\n" <<
		"\t      ****                    ****\n" <<
		"\t          ********************";
}