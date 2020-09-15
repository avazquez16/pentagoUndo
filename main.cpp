/* -----------------------------------------------------------
   Program 6: Pentago Undo

   Class: CS 141, Spring 2020.  Tues 11am lab
   System: Visual Studio Code
   Author: Arturo Vazquez
   -----------------------------------------------------------
 */

#include <iostream> // cout ...
#include <cstring> // toupper....

using namespace std;
class Board{

private:
    char** board;

public:
    Board();
    void displayBoard();
    bool piecePlacement(char userRow, char userColumn, char userRotationDirection, char userQuadrant, char &tempPlayerXorO);
    void createGameBoardTemp(char gameBoardTemp[6][6]);
    void rotateQuadrantLeft(char userQuadrant);
    void rotateQuadrantRight(char userQuadrant);
    bool validMove(char userRow, char userColumn, char userRotationDirection, char userQuadrant);
    bool horizontalAndVerticalGameWinnerCheck(char player);
    bool diagonalGameWinnerCheck(char player);
    bool gameWinnerCheck(char playerX, char playerO);
    char** getBoard();
    Board(const Board& oldBoard);
};

// Constructor used for board set to '.'
Board::Board(){
    this -> board = new char*[6]; // 6 pointers
    for(int row = 0; row < 6; row++){
        board[row] = new char[6];
        for(int col = 0; col < 6; col++){
            board[row][col] = '.';
        }
    }
}

// Return board(2d array)
char** Board::getBoard(){ return board;}

// Copy constructor
Board::Board(const Board& object) {

    this -> board = new char*[6]; // 6 pointers
    for(int row = 0; row < 6; row++){
        board[row] = new char[6];
    }
    for (int row = 0; row <6; row++){
        for (int col = 0; col < 6; col++){
            board[row][col] = object.board[row][col];
        }
    }
}


// Function displays board.
void Board::displayBoard() {
    char rowLetter = 'A';
    int middleDesign = 0;

    cout << "\n    1   2   3   4   5   6   \n"
            "  1-----------------------2 \n";
    for(int rows = 0; rows < 6; rows++){
        cout << rowLetter << " | ";
        for(int cols = 0; cols < 6; cols++){
            if (cols != 5  && cols != 2)
                cout << board[rows][cols] << "   ";
            if (cols ==5)
                cout << board[rows][cols];
            if (cols==2)
                cout << board[rows][cols] << " | ";
        }
        cout << " | "  << rowLetter << endl;
        if (middleDesign != 2 && rows != 5)
            cout << "  |           |           | \n";
        if (middleDesign == 2)
            cout << "  |-----------+-----------| \n";
        middleDesign++;
        rowLetter ++;
    }
    cout << "  3-----------------------4  \n"
            "    1   2   3   4   5   6    \n";
}

// Function determines if the users input is valid/within range
bool Board::validMove(char userRow, char userColumn, char userRotationDirection, char userQuadrant){
    if (!(userRow >= 'A' && userRow <= 'F')) {
        cout << "    *** Invalid move row.  Please retry.\n";
        return false;
    }

    if (!(userColumn >= '1' && userColumn <= '6')){
        cout << "    *** Invalid move column.  Please retry.\n";
        return false;
    }

    if (!(userQuadrant >= '1' && userQuadrant <= '4')){
        cout << "    *** Selected quadrant is invalid.  Please retry. \n";
        return false;
    }

    if (!(userRotationDirection == 'L' || userRotationDirection == 'R')){
        cout << "    *** Quadrant rotation direction is invalid.  Please retry. \n";
        return false;
    }

    if ((board[userRow - 'A'][userColumn - '1']!= '.')){
        cout << "    *** That board location is already taken.  Please retry.\n";
        return false;
    }
    return true;
}

// Function updates the board if the user entered valid input
bool  Board::piecePlacement(char userRow, char userColumn, char userRotationDirection, char userQuadrant, char &tempPlayerXorO) {
    if (validMove(userRow, userColumn, userRotationDirection, userQuadrant)){
        board[userRow - 'A'][userColumn - '1'] = tempPlayerXorO;
        if (userRotationDirection == 'R')
            rotateQuadrantRight(userQuadrant);
        else
            rotateQuadrantLeft(userQuadrant);

        return true;
    }
    return false;

}

// Function stores values from the board into a temp 2d array used for quadrant rotation
void Board::createGameBoardTemp(char gameBoardTemp[6][6]){
    for (int row = 0; row < 6; row++){
        for(int col = 0; col < 6; col++){
            gameBoardTemp[row][col] = board[row][col];
        }
    }
}

// Function rotates quadrants 1-4 to the left
void Board::rotateQuadrantLeft(char userQuadrant){
    char gameBoardTemp[6][6]; // Board array elements will be stored here.
    createGameBoardTemp(gameBoardTemp); // Store elements from the board 2d array into a temp 2d array.

    switch(userQuadrant){
        case '1':
            board[0][0] = gameBoardTemp[0][2];board[0][1] = gameBoardTemp[1][2];board[0][2] = gameBoardTemp[2][2];
            board[1][0] = gameBoardTemp[0][1];board[1][1] = gameBoardTemp[1][1];board[1][2] = gameBoardTemp[2][1];
            board[2][0] = gameBoardTemp[0][0];board[2][1] = gameBoardTemp[1][0];board[2][2] = gameBoardTemp[2][0];
            break;
        case '2':
            board[0][3] = gameBoardTemp[0][5];board[0][4] = gameBoardTemp[1][5];board[0][5] = gameBoardTemp[2][5];
            board[1][3] = gameBoardTemp[0][4];board[1][4] = gameBoardTemp[1][4];board[1][5] = gameBoardTemp[2][4];
            board[2][3] = gameBoardTemp[0][3];board[2][4] = gameBoardTemp[1][3];board[2][5] = gameBoardTemp[2][3];
            break;
        case '3':
            board[3][0] = gameBoardTemp[3][2];board[3][1] = gameBoardTemp[4][2];board[3][2] = gameBoardTemp[5][2];
            board[4][0] = gameBoardTemp[3][1];board[4][1] = gameBoardTemp[4][1];board[4][2] = gameBoardTemp[5][1];
            board[5][0] = gameBoardTemp[3][0];board[5][1] = gameBoardTemp[4][0];board[5][2] = gameBoardTemp[5][0];
            break;
        case '4':
            board[3][3] = gameBoardTemp[3][5];board[3][4] = gameBoardTemp[4][5];board[3][5] = gameBoardTemp[5][5];
            board[4][3] = gameBoardTemp[3][4];board[4][4] = gameBoardTemp[4][4];board[4][5] = gameBoardTemp[5][4];
            board[5][3] = gameBoardTemp[3][3];board[5][4] = gameBoardTemp[4][3];board[5][5] = gameBoardTemp[5][3];
            break;
    }
}

// Function rotates quadrants 1-4 to the right
void Board::rotateQuadrantRight(char userQuadrant){
    char gameBoardTemp[6][6]; // Board array elements will be stored here.
    createGameBoardTemp(gameBoardTemp); // Store elements from the board 2d array into a temp 2d array.

    switch(userQuadrant){
        case '1':
            board[0][0] = gameBoardTemp[2][0];board[0][1] = gameBoardTemp[1][0];board[0][2] = gameBoardTemp[0][0];
            board[1][0] = gameBoardTemp[2][1];board[1][1] = gameBoardTemp[1][1];board[1][2] = gameBoardTemp[0][1];
            board[2][0] = gameBoardTemp[2][2];board[2][1] = gameBoardTemp[1][2];board[2][2] = gameBoardTemp[0][2];
            break;
        case '2':
            board[0][3] = gameBoardTemp[2][3];board[0][4] = gameBoardTemp[1][3];board[0][5] = gameBoardTemp[0][3];
            board[1][3] = gameBoardTemp[2][4];board[1][4] = gameBoardTemp[1][4];board[1][5] = gameBoardTemp[0][4];
            board[2][3] = gameBoardTemp[2][5];board[2][4] = gameBoardTemp[1][5];board[2][5] = gameBoardTemp[0][5];
            break;
        case '3':
            board[3][0] = gameBoardTemp[5][0];board[3][1] = gameBoardTemp[4][0];board[3][2] = gameBoardTemp[3][0];
            board[4][0] = gameBoardTemp[5][1];board[4][1] = gameBoardTemp[4][1];board[4][2] = gameBoardTemp[3][1];
            board[5][0] = gameBoardTemp[5][2];board[5][1] = gameBoardTemp[4][2];board[4][2] = gameBoardTemp[3][2];
            break;
        case '4':
            board[3][3] = gameBoardTemp[5][3];board[3][4] = gameBoardTemp[4][3];board[3][5] = gameBoardTemp[3][3];
            board[4][3] = gameBoardTemp[5][4];board[4][4] = gameBoardTemp[4][4];board[4][5] = gameBoardTemp[3][4];
            board[5][3] = gameBoardTemp[5][5];board[5][4] = gameBoardTemp[4][5];board[5][5] = gameBoardTemp[3][5];
            break;
    }
}

// Function checks for any 5 consecutive player pieces horizontal or vertical.
bool Board::horizontalAndVerticalGameWinnerCheck(char player) {
    int lookFiveInARowHorizontal = 0;
    int lookFiveInARowHorizontalIndexPlusOne = 0;
    int lookFiveInARowVertical = 0;
    int lookFiveInARowVerticalIndexPlusOne = 0;

    for(int row = 0; row < 6 ; row++){
        for(int col = 0; col < 5 ; col++){
            if (board[row][col] == player)
                lookFiveInARowHorizontal ++;
            if (board[row][col+1] == player)
                lookFiveInARowHorizontalIndexPlusOne++;
            if (board[col][row] == player)
                lookFiveInARowVertical++;
            if (board[col+1][row] == player)
                lookFiveInARowVerticalIndexPlusOne++;
            if (lookFiveInARowHorizontal == 5  || lookFiveInARowHorizontalIndexPlusOne == 5 ||
                lookFiveInARowVertical == 5 || lookFiveInARowVerticalIndexPlusOne == 5)
                return true;
        }
        lookFiveInARowHorizontal = 0;
        lookFiveInARowHorizontalIndexPlusOne = 0;
        lookFiveInARowVertical = 0;
        lookFiveInARowVerticalIndexPlusOne = 0;

    }

    return false;
}

// 6 Possible diagonal win conditions. function broke 6 possibilities into 3 loops that check 2 possibilities
bool Board::diagonalGameWinnerCheck(char player){
    int lookFiveInARowDiagonal = 0;
    int lookFiveInARowDiagonalTwo = 0;
    int tempRow = 5;
    int tempRowTwo = 1;

    /*Center diagonal possibilities board[5,0],[4,1],[3,2],[2,3],[1,4],[0,5]
    and                             board[0,0],[1,1],[2,2],[3,3],[4,4],[5,5]  (both have same columns)*/
    for (int row = 0; row < 6; row++){
        if(board[row][row] == player)
            lookFiveInARowDiagonal++;
        if(board[tempRow--][row] == player)
            lookFiveInARowDiagonalTwo++;
        if(lookFiveInARowDiagonal == 5 || lookFiveInARowDiagonalTwo == 5 )
            return true;
    }

    /*Other 2 possibilities        board[5,1],[4,2],[3,3],[2,4],[1,5]
    and                            board[0,1],[1,2],[2,3],[3,4],[4,5]  (both have same columns)*/
    tempRow = 4;
    lookFiveInARowDiagonal = 0;
    lookFiveInARowDiagonalTwo = 0;
    for (int row = 0; row < 5; row++){
        if(board[tempRow--][row] == player)
            lookFiveInARowDiagonal++;
        if(board[tempRowTwo++][row] == player)
            lookFiveInARowDiagonalTwo++;
        if(lookFiveInARowDiagonal == 5 || lookFiveInARowDiagonalTwo == 5 )
            return true;
    }

    /*Final 2 possibilities board[4,0],[3,1],[2,2],[1,3],[0,4]
    and                    board[1,0],[2,1],[3,2],[4,3],[5,4] (both have same columns)*/
    tempRow = 5;
    tempRowTwo =0;
    lookFiveInARowDiagonal = 0;
    lookFiveInARowDiagonalTwo = 0;
    for (int row = 1; row < 6; row++){
        if(board[tempRow--][row] == player)
            lookFiveInARowDiagonal++;
        if(board[tempRowTwo++][row] == player)
            lookFiveInARowDiagonalTwo++;
        if(lookFiveInARowDiagonal == 5 || lookFiveInARowDiagonalTwo == 5 )
            return true;
    }
    return false;
}

// Function puts all the functions that detect winner into one single function
bool Board::gameWinnerCheck(char playerX, char playerO) {

    // IF BOTH PLAYERS WON
    if ((horizontalAndVerticalGameWinnerCheck(playerX) || diagonalGameWinnerCheck(playerX)) && (horizontalAndVerticalGameWinnerCheck(playerO) || diagonalGameWinnerCheck(playerO) )){
        cout <<"    *** Both X and O have won.  Game is a tie.\n";
        displayBoard();
        return false;
    }

    // CHECK IF PLAYER X WINS
    if(horizontalAndVerticalGameWinnerCheck(playerX) || diagonalGameWinnerCheck(playerX) ){
        cout <<"    *** X has won the game! \n";
        displayBoard();
        return false;
    }

    // CHECK IF PLAYER O WINS
    if(horizontalAndVerticalGameWinnerCheck(playerO) || diagonalGameWinnerCheck(playerO) ){
        cout <<"    *** O has won the game! \n";
        displayBoard();
        return false;
    }
    return true;
}

class Node {
public:
    Node *next;
    int MovementNumber;
    char player;
    Board oldBoard;
};

// Display the move numbers on the linked list
void displayList( Node *pTemp) {

    cout << "   List of moveNumber:playerToMove is ";
    while (pTemp != nullptr) {
        if (pTemp->MovementNumber != 1)
            cout << pTemp->MovementNumber << ":" << pTemp->player << "->";
        else
            cout << pTemp->MovementNumber << ":" << pTemp->player;
        pTemp = pTemp->next;
    }
    cout << endl;
}

// Function deletes node from the list
void deleteNodeFromList(Node *&head){
    Node *temp = head;
    head = head -> next;
    delete temp;
}


// function adds a new list to the linked list
void addNodeToList(Node *&head, int movementNumber, char playerXorO,  Board theBoard){
    Node *pTemp = new Node();
    pTemp->MovementNumber = movementNumber;
    pTemp->player = playerXorO;
    pTemp->oldBoard = theBoard;
    pTemp->next = nullptr;
    if (head != nullptr)
        pTemp->next = head;
    head = pTemp;
}

// Function determines which player's turn it is.
void playerTurn(int moveNumber, char playerO, char playerX, char &tempPlayerXorO) {
    if (moveNumber % 2 == 0)
        tempPlayerXorO = playerO;
    else
        tempPlayerXorO = playerX;
}

// Function displays instructions
void displayInstructions()
{
    cout << "\n"
         << "Play the two-player game of Pentago. Be the first to get 5 in a row. \n"
         << "                                                                 \n"
         << "Pentago is played on a 6 by 6 board, divided into four 3 by 3    \n"
         << "quadrants.  There are two players, X and O, who alternate turns. \n"
         << "The goal of each player is to get five of their pieces in a row, \n"
         << "either horizontally, vertically, or diagonally.                  \n"
         << "                                                                 \n"
         << "Players take turns placing one of their pieces into an empty     \n"
         << "space anywhere on the board, then choosing one of the four       \n"
         << "board quadrants to rotate 90 degrees left or right.              \n"
         << "                                                                 \n"
         << "If both players get five in a row at the same time, or the       \n"
         << "last move is played with no five in a row, the game is a tie.    \n"
         << "If a player makes five a row by placing a piece, there is no need\n"
         << "to rotate a quadrant and the player wins immediately.            \n"
         << "                                                                 \n"
         << "     Play online at:  https://perfect-pentago.net                \n"
         << "     Purchase at:     www.mindtwisterusa.com                     \n"
         << "                                                                 \n"
         << "For each move provide four inputs:                               \n"
         << "   row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R) \n"
         << "For instance input of B32R places the next piece at B3 and then  \n"
         << "would rotate quadrant 2 (upper-right) to the right (clockwise).  \n"
         << "                                                                 \n"
         << "At any point enter 'x' to exit the program or 'i' to display instructions.\n";
}

// Function exits the program or displays instructions or undos player move
bool exitInstructionUndo(char userRow, int &moveNumber,char &tempPlayerXorO, Node *&head, Board &theBoard, Board initialBoard ){

    // User enters X to exit
    if (userRow == 'X'){
        cout << "Exiting program...\n\n";
        exit(0);
    }

        // User enters I instructions get displayed
    else if (userRow == 'I'){
        displayInstructions();
        return true;
    }

        // User enters U node gets deleted and board gets updated
    else if (userRow == 'U') {
        if (head->next == nullptr) {
            cout << "*** You cannot undo past the beginning of the game.  Please retry. ***\n";
            theBoard = initialBoard;
            return true;
        }
        deleteNodeFromList(head);
        theBoard = head->oldBoard;
            moveNumber = head -> MovementNumber;
            tempPlayerXorO =  head -> player;


        cout << "* Undoing move *";
        return true;
    }

    return false;
}

int main(){
    char userRow;
    char userColumn;
    char userQuadrant;
    char userRotationDirection;
    int moveNumber = 1;
    char tempPlayerXorO = 'X';
    char playerX = 'X';
    char playerO = 'O';

    Board theBoard;  // Create the board as an instance of the Board class
    Board initialBoard = theBoard;
    Node * head; // Create head of the node
    head =  nullptr; // Set head pointer to null

    playerTurn(moveNumber, playerO, playerX, tempPlayerXorO);
    addNodeToList(head, moveNumber,  tempPlayerXorO, theBoard);

    cout<< "Welcome to Pentago, where you try to get 5 of your pieces in a line.\n"
           "At any point enter 'x' to exit, 'i' for instructions, or 'u' to undo.\n";

    while(true){
        theBoard.displayBoard();
        displayList(head);
        cout << moveNumber <<  ". Enter row, column, quadrant, direction for " << tempPlayerXorO << ":" ;

        // If user input x(exit) or i(instructions) or U(undo)
        cin >> userRow;
        userRow = toupper(userRow);
        if (exitInstructionUndo(userRow, moveNumber, tempPlayerXorO, head, theBoard, initialBoard))
            continue;

        // Get user input and make toupper
        cin >> userColumn; cin >> userQuadrant; cin >> userRotationDirection;
        userQuadrant = toupper(userQuadrant); userRotationDirection = toupper(userRotationDirection);

        // Updates the board if the user entered valid input and adds node
        if (theBoard.piecePlacement( userRow, userColumn, userRotationDirection, userQuadrant, tempPlayerXorO)){
            moveNumber++;
            playerTurn(moveNumber, playerO, playerX, tempPlayerXorO);
            addNodeToList(head, moveNumber,  tempPlayerXorO, theBoard);

            // Winner is detected
            if (!theBoard.gameWinnerCheck(playerX,  playerO))
                break;

            // Board is full/no one wins
            if (moveNumber > 36){
                cout << "    *** No one has won.  Game is a tie.\n";
                theBoard.displayBoard();
                cout << "Thanks for playing.  Exiting... \n";
                exit(0);
            }
        }
    }
    // Out of the loop player won or tied
    cout << "Thanks for playing.  Exiting... \n";
}
