#include <iostream>
#include <ctime>
#include <cstdlib>

const int SIZE = 3;
// tracks the status of all fields
bool boardStatus[SIZE][SIZE];
int score[2] = {};
void printMenu();

void drawBoard (bool m1[][SIZE], bool m2[][SIZE]){
    for (int i = 0; i < SIZE; i++){
        std::cout << "-------------\n" << "| ";
        for (int j = 0; j < SIZE; j++)
            if (m1[i][j]) std::cout << "X" << " | ";
            else if (m2[i][j]) std::cout << "O" << " | ";
            else std::cout << "  | ";
        std::cout << "\n";
    }
    std::cout << "-------------\n";
}
bool draw(){
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
                if (!boardStatus[i][j]) return false;
    return true;
}
bool win(bool m[][SIZE]){
    int counter1 = 0, counter2 = 0;
    // checks row by row and column by column for
    // three X's or O's
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (m[i][j]) counter1++;
            if (m[j][i]) counter2++;
        }
        if (counter1 == 3 || counter2 == 3) return true;
        counter1 = 0; counter2 = 0;
    }
    // checks left diagonal
    for (int i = 0; i < SIZE; i++)
        if (m[i][i]) counter1++;
    if (counter1 == 3) return true;
    // checks right diagonal
    for (int i = 0, j = 2; i < SIZE; i++, j--)
        if (m[i][j]) counter2++;
    if (counter2 == 3) return true;

    return false;
}
void printWinOrDraw (bool m[][SIZE], char ch){
    if (win(m)) {
        std::cout << ch << " player won!\n\n";
        if (ch == 'X') score[0]++;
        else score[1]++;
    }
    else if (draw()) std::cout << "It's a draw!\n\n";
    return;
}
// randomly generates field for player O
void computerChoice(int &rowComputer, int &columnComputer){
    srand(time(0));
    do{
           rowComputer = rand() % 3;
           columnComputer = rand() % 3;
           if (!boardStatus[rowComputer][columnComputer])break;
        } while (boardStatus[rowComputer][columnComputer]);
}
// takes valid input for player X from the user
void playerInput (int &rowPlayer, int &columnPlayer){
    do {
        do {
            std::cout << "Enter a row (0, 1 or 2) for player X: ";
            std::cin >> rowPlayer;
            if (rowPlayer < 0 || rowPlayer > 2)
            std::cout << "Invalid input! Try again\n";
        } while (rowPlayer < 0 || rowPlayer > 2);
        do {
            std::cout << "Enter a column (0, 1 or 2) for player X: ";
            std::cin >> columnPlayer;
            if (columnPlayer < 0 || columnPlayer > 2)
                std::cout << "Invalid input! Try again\n";
        } while (columnPlayer < 0 || columnPlayer > 2);
        if (!boardStatus[rowPlayer][columnPlayer]) break;
        else std::cout << "That field is already taken. Use another field.\n";
    } while (boardStatus[rowPlayer][columnPlayer]);
}
void startGame(bool player[][SIZE], bool computer[][SIZE]){
    int rowPlayer, columnPlayer, rowComputer, columnComputer;
    do {
        playerInput(rowPlayer, columnPlayer);
        // marks player X field choice as taken
        boardStatus[rowPlayer][columnPlayer] = true;
        player[rowPlayer][columnPlayer] = true;
        drawBoard(player, computer);
        if (win(player) || draw()){
        printWinOrDraw(player, 'X');
        break;
        }
        computerChoice(rowComputer, columnComputer);
        std::cout << "O player chooses field (" << rowComputer << "," << columnComputer << "): \n";
        // marks player O field choice as taken
        boardStatus[rowComputer][columnComputer] = true;
        computer[rowComputer][columnComputer] = true;
        drawBoard(player, computer);
        if (win(computer) || draw()){
        printWinOrDraw(computer, 'O');
        break;
        }
    } while (!win(player) || !win(computer) || !draw());
    printMenu();
}
void setGame(){
    bool player[SIZE][SIZE], computer[SIZE][SIZE];
    // all fields on the board are initially marked
    // as empty (false)
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            boardStatus[i][j] = false;
            player[i][j] = false;
            computer[i][j] = false;
            }
    drawBoard(player, computer);
    startGame(player, computer);
}
void printMenu(){
    std::cout << "Choose one of following options by entering 1 or 2: "
         << "\n1. Reset the game "
         << "\n2. Exit\n";
    int option;
    std::cin >> option;
    switch(option){
        case 1: setGame(); break;
        case 2: std::cout << "\nSCORE:\nX | O\n" << score[0] << " : " << score[1] << "\n"; return;
        default: std::cout << "Invalid input. Game ends\n"; return;
    }
}
int main(){
    std::cout << "WELCOME TO THE GAME!\nYou are player X and the computer is player O.\nLet's start the game: \n";
    setGame();
    return 0;
}

