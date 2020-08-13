#include <iostream>
#include <conio.h>
#include <string>


// I HAS CREATED A EXPERIMENTAL ONE CALLED ANOTHA TESTO IN PERSONAL C++ ONCE I GET SOMETHING WORKING THERE IMPLEMENT HERE
// AND PERFECT THIS TINGS
// I WILL FINISH THIS SHIT BY SUNDAY SO I CAN CHILL NEXT WEEK 
// GRIND THIS SHIT OUT FOR DAT SWEET AF BREAK POOFY

using namespace std;

// Matrix that contains all the information of the game board Tic-Tac-Toe
char board[3][3];

// To determine whose turn it is and simplifies which
// letter to draw in the board[][]
char turn = 'X';

// Boolean to store if player has quit
// and if the game is finished
bool playerHasQuit = false;
bool isGameFinished = false;

// will be used to store players names
string players;
string p1, p2;

// implement timer later when done with the ting

// Screen to show Main menu and options for Main Menu
enum Menu {
	MENU = 1,
	PLAY = 2,
	QUIT = 3,
};

// Screen to show Game Mode Sub Menu and its options
// P is player
// C is computer
// V is verses
enum MODE {
	MODE_MENU = 1,
	PVP = 2,
	PVC = 3,
	CVC = 4,
	BACK = 5,
};

// Toggles the symbol for each player
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
void toggleName()
{
	if (turn == 'X') {
		players = p1;
	}
	else {
		players = p2;
	}
}

// need to draw board for pvp
// Clears the previous board when a new input is registered
void drawBoardPVP()
{
	system("cls");
	cout << " PVP Tic-Tac-Toe" << "\n\n";
	cout << p1 << " (X) - " << p2 << " (O) " << "\n\n";
	cout << "\t" << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
	cout << "\t" << "---------" << endl;
	cout << "\t" << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
	cout << "\t" << "---------" << endl;
	cout << "\t" << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
	cout << "\n\n";
	cout << "\t\t\t" << "Enter 'Q' to quit or 'R' to restart" << endl;
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

// need to determine how comp will play

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
	cout << "It's " << players << " turn. " << "Enter the letter of the field: ";
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

// 2 Player mode of Tic-Tac-Toe
void playPVP()
{
	cout << " PVP " << "\n\n";
	cout << "Enter player 1(X) name: " << endl;
	cin >> p1;
	cout << "Enter player 2(O) name: " << endl;
	cin >> p2;
	system("cls");
	// Populates the board
	fill();
	// First time draws the board
	drawBoardPVP();
	while (playerHasQuit == false) {
		// Takes player input
		playerInput();
		// Will continue to redraw the board
		drawBoardPVP();
		// Outcomes of the game
		if (gameOver() == 'X') {
			cout << players << " wins!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		else if (gameOver() == 'O') {
			cout << players << " wins!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		else if (gameOver() == '/') {
			cout << "It's a draw!" << endl;
			isGameFinished = true;
			playerHasQuit = true;
		}
		//Toggles the players to switch turns
		togglePlayer();
	}

	// A message asking if player would like to play again
	// will only appear if the game has finished
	if (isGameFinished == true) {
		cout << "will u like to play again Y or N" << endl;
		char choice;
		cin >> choice;
		// If yes the resets the booleans and recalles playPVP()
		if (choice == 'Y') {
			system("cls");
			playerHasQuit = false;
			isGameFinished = false;
			playPVP();
		}
		else if (choice == 'N') {
			cout << "waiting for keypress to return menu";
			_getch();
			system("cls");
		}
	}
	// Reset playerHasQuit back to false
	playerHasQuit = false;
}

void playPVC()
{
	bool playerHasQuit = false;
	char press;
	do {
		cout << "pvc" << endl;
		cout << "press x to quit" << endl;
		cin >> press;
		if (press == 'x') {
			playerHasQuit = true;
		}
	} while (!playerHasQuit);
	system("cls");	// Clears screen
}

void playCVC()
{
	bool playerHasQuit = false;
	char press;
	do {
		cout << "cvc" << endl;
		cout << "press x to quit" << endl;
		cin >> press;
		if (press == 'x') {
			playerHasQuit = true;
		}
	} while (!playerHasQuit);
	system("cls");	// Clears screen
}

// Shows menu and waits for valid choice. (see enum Menu)
// Input is player's choice.
// Checks if choice is valid.
// Output is choice made by player.
int showMenu()
{
	int choice;
	cout << "menu" << endl;
	cout << "2 to pray" << endl;
	cout << "3 to quit" << endl;
	cin >> choice;
	if (choice == 2) {
		choice = PLAY;
	}
	else if (choice == 3) {
		choice = QUIT;
	}
	else {	// Check to make sure that player is making a valid choice
		cout << " wong choice" << endl;
		cout << "wait for keypress to return to menu" << endl;
		_getch();	// Waits for keypress
		system("cls");	// Clears screen
	}
	system("cls");
	return choice;
}

// Shows the game mode sub menu.
// Determines which version of tic-tac-toe player wants to play.
int showGameModeSubMenu()
{
	int choice;
	cout << " Hello poofy" << endl;
	cout << " 2: pvp" << endl;
	cout << " 3: pvc" << endl;
	cout << " 4: cvc" << endl;
	cout << " 5: go back" << endl;
	cin >> choice;

	if (choice == 2) {
		choice = PVP;
	}
	else if (choice == 3) {
		choice = PVC;
	}
	else if (choice == 4) {
		choice = CVC;
	}
	system("cls");	// Clears screen
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
			playPVP();	// Plays pvp gets winner

			selected = MODE_MENU;	// playPVC() has finished and returns player to showGameModeSubMenu()
		}
		else if (selected == PVC) {
			playPVC();	// Plays pvc gets winner

			selected = MODE_MENU;	// playPVC() has finished and returns player to showGameModeSubMenu()
		}
		else if (selected == CVC) {
			playCVC();	// Plays cvc gets winner

			selected = MODE_MENU;	// playCVC() has finished and returns player to showGameModeSubMenu()
		}

	}

	system("cls");	// Clears screen
	return selected;
}

// put credits here

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
	}

	// Quit was chosen, ending while loop.

	system("cls"); // Clears screen
	cout << "u quite u poofy" << endl;
	// show some quitting ting
	return 0;
}