#include <iostream>
#include <vector>
#include <random>

using namespace std;

void print_XO_Board(vector<char> &boardSymbols);
bool determine_Starter(void);
char Check_XO_Win(vector<char> &boardSymbols);
bool Check_XO_Draw(vector<char> &boardSymbols);
void isValidMove(vector<char> &boardSymbols, bool currentPlayer);
void clearScreen(); // Platform-specific screen clearing function

int main()
{
    bool currentPlayer = determine_Starter();

    vector<char> Symbols = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    while (Check_XO_Win(Symbols) == '0' && !Check_XO_Draw(Symbols))
    {

        print_XO_Board(Symbols);

        isValidMove(Symbols, currentPlayer);
        currentPlayer = !currentPlayer; // Switch player turns
        clearScreen();                  // Clear the screen
    }

    print_XO_Board(Symbols);

    if (Check_XO_Win(Symbols) != '0')
        cout << "Player " << (Check_XO_Win(Symbols) == 'X' ? '1' : '2') << " wins!" << endl;
    else if (Check_XO_Draw(Symbols))
        cout << "It's a draw!" << endl;
}

// Efficiently iterates and formats a 3x3 Tic-Tac-Toe board using symbols stored in a vector.
void print_XO_Board(vector<char> &boardSymbols)
{
    cout << "\n\n\t  " << boardSymbols[0] << " | " << boardSymbols[1] << " | " << boardSymbols[2] << " \n";
    cout << "\t --- --- --- \n";
    cout << "\t  " << boardSymbols[3] << " | " << boardSymbols[4] << " | " << boardSymbols[5] << " \n";
    cout << "\t --- --- --- \n";
    cout << "\t  " << boardSymbols[6] << " | " << boardSymbols[7] << " | " << boardSymbols[8] << " \n";
}

// Simulates a coin toss with user input to determine who goes first in a two-player game.
bool determine_Starter(void)
{
    // Seed the random number generator with better randomness
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(1, 2);

    int randomNumber = distribution(generator);

    char player1Input;
    do
    {
        cout << "Player 1, Heads or Tails? (h/t): ";
        cin >> player1Input;
    } while (player1Input != 'h' && player1Input != 'H' &&
             player1Input != 't' && player1Input != 'T');

    if ((player1Input == 'h' || player1Input == 'H') && randomNumber == 1)
    {
        cout << "Player 1 goes first! and takes \'X\'" << endl;
        return true;
    }
    else if ((player1Input == 't' || player1Input == 'T') && randomNumber == 2)
    {
        cout << "Player 1 goes first! and takes \'X\'" << endl;
        return true;
    }
    else
    {
        cout << "Player 2 goes first! and takes \'O\'" << endl;
        return false;
    }
}

// Checks for a winning player on a Tic-Tac-Toe board (returns 'X', 'O', or '0').
char Check_XO_Win(vector<char> &boardSymbols)
{
    // - Checks both main diagonals.
    if ((boardSymbols[0] == boardSymbols[4] && boardSymbols[4] == boardSymbols[8]) ||
        (boardSymbols[2] == boardSymbols[4] && boardSymbols[4] == boardSymbols[6]))
        return boardSymbols[4];

    // - Checks horizontal and vertical wins.
    for (int i = 0; i < 3; i++)
    {
        if (boardSymbols[i * 3] == boardSymbols[i * 3 + 1] && boardSymbols[i * 3 + 2] == boardSymbols[i])
            return boardSymbols[i * 3];
        else if (boardSymbols[i] == boardSymbols[i + 3] && boardSymbols[i + 6] == boardSymbols[i])
            return boardSymbols[i];
    }

    // - Returns '0' if no winner.
    return '0';
}

// Determines if a Tic-Tac-Toe game is a draw
bool Check_XO_Draw(vector<char> &boardSymbols)
{
    // - Returns false if any space is from the vector
    for (int i = 1; i <= 9; i++)
        if (i + '0' == (boardSymbols[i - 1]))
            return false;
    // - Returns true if all spaces are filled, indicating a draw.
    return true;
}

// Prompts the current player to enter a move (1-9) and validates it.
void isValidMove(vector<char> &boardSymbols, bool currentPlayer)
{
    int position;
    do
    {
        cout << (currentPlayer ? "Player 1" : "Player 2") << "'s turn. Enter position (1-9): ";
        cin >> position;
        if (position < 1 || position > 9)
        {
            cout << "Invalid position. Please enter a number between 1 and 9." << endl;
        }
        else if (boardSymbols[position - 1] != '1' + position - 1)
        {
            cout << "That position is already occupied! Please choose a different one." << endl;
        }
    } // - Repeats until a valid, unoccupied position is chosen.
    while (position < 1 || position > 9 || boardSymbols[position - 1] != '1' + position - 1);

    // - Updates the board with the player's symbol ('X' or 'O').
    boardSymbols[position - 1] = currentPlayer ? 'X' : 'O';
}

void clearScreen()
{
    system("cls");
}
