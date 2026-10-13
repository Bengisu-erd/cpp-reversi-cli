#include <iostream>
#include <string>
#include <cctype>
using namespace std;
const int MAX_SIZE = 12;

int getBoardSize();
void initBoard(char board[][MAX_SIZE], int size);
void printBoard(const char board[][MAX_SIZE], int size);
bool parseInput(const std::string& input, int size, int& row, int& col);
bool isMoveLegal(const char board[][MAX_SIZE], int size, int row, int col, char player);
int makeMove(char board[][MAX_SIZE], int size, int row, int col, char player);
bool playComputerMove(char board[][MAX_SIZE], int size);
bool hasAnyValidMove(const char board[][MAX_SIZE], int size, char player);
void printScoresAndWinner(const char board[][MAX_SIZE], int size);

int main() {
    int size = getBoardSize();
    char board[MAX_SIZE][MAX_SIZE];

    initBoard(board, size);
    printBoard(board, size);

    while (true) {
        bool userCanMove = hasAnyValidMove(board, size, 'O');
        bool compCanMove = hasAnyValidMove(board, size, 'X');

        if (!userCanMove && !compCanMove) {
            break;
        }

        if (userCanMove) {
            int userRow = -1;
            int userCol = -1;
            std::string inputMove;

            while (true) {
                std::cout << "Enter your move (e.g. 4c): ";
                std::cin >> inputMove;

                if (parseInput(inputMove, size, userRow, userCol)) {
                    if (isMoveLegal(board, size, userRow, userCol, 'O')) {
                        break; // Hamle tamamen geçerli
                    } else {
                        std::cout << "Illegal move! That move does not flip any piece. Try again.\n";
                    }
                } else {
                    std::cout << "Invalid format or position out of bounds! Try again.\n";
                }
            }

            makeMove(board, size, userRow, userCol, 'O');
            printBoard(board, size);
        } else {
            std::cout << "User has no legal moves. Passing turn to computer...\n";
        }

        userCanMove = hasAnyValidMove(board, size, 'O');
        compCanMove = hasAnyValidMove(board, size, 'X');
        if (!userCanMove && !compCanMove) {
            break;
        }

        if (compCanMove) {
            playComputerMove(board, size);
            printBoard(board, size);
        } else {
            std::cout << "Computer has no legal moves. Passing turn to user...\n";
        }
    }

    printScoresAndWinner(board, size);
    return 0;
}



void initBoard(char board[][MAX_SIZE] , int size) {
    int mid1=size/2;
    int mid2=size/2+1;

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            board[i][j]='.';
        }
    }
    board[mid1][mid1]='X';
    board[mid1][mid2]='O';
    board[mid2][mid1]='O';
    board[mid2][mid2]='X';

}

void printBoard(const char board[][MAX_SIZE], int size){
    std::cout << "  "; 
for (int col = 0; col < size; ++col) {
    char letter = 'a' + col;
    std::cout << letter << " ";
}
std::cout << "\n";
for (int row=0; row<size; ++row){
    cout<<(row+1)<<" ";

    for(int col=0; col<size; ++col){
        cout<<board[row][col]<<" ";
    }
    cout<<"\n";
}
}

bool parseInput(const string& input, int size, int& row,int& col){
    if(input.length() <2 || input.length()>3){
        return false;
    }

char letter=input.back();
letter=tolower(letter);
if (letter < 'a' || letter > 'a'+ size ){
    return false;
}
col=letter - 'a';

string numberPart=input.substr(0,input.length()-1);
for(char ch : numberPart){
    if(!isdigit(ch)){
        return false;
    }
}

int rowNum=stoi(numberPart);
if(rowNum<1 || rowNum>size){
    return false;
}
row=rowNum-1;

return true;
}

bool isMoveLegal(const char board[][MAX_SIZE], int size,int row,int col,char player){
    if (board[row][col] != '.' ){
        return false;
    }
      char opponent = (player == 'O') ? 'X' : 'O';

    const int dRow[]={-1,-1,-1,0,0,1,1,1};
    const int dCol[]={-1,0,1,-1,1,-1,0,1};

    for (int dir=0; dir<8; ++dir){
        int r=row+ dRow[dir];
        int c=col+dCol[dir];
        if(r >= 0 && r < size && c >= 0 && c < size && (board[r][c ]== opponent)){
            r+=dRow[dir];
            c+=dCol[dir];

            while(r >= 0 && r < size && c >= 0 && c < size){
                if(board[r][c]=='.'){
                    break;
                }
                if(board[r][c]==player){
                    return true;
                }

                r+=dRow[dir];
                c+=dCol[dir];
            }

        }
    }

    return false;
}

int makeMove(char board[][MAX_SIZE], int size, int row, int col, char player){
    board[row][col]=player;
    int totalFlipped=0;
    
    char opponent = (player == 'O') ? 'X' : 'O';
    const int dRow[]={-1,-1,-1,0,0,1,1,1};
    const int dCol[]={-1,0,1,-1,1,-1,0,1};

    for(int dir=0; dir<8; ++dir){
        int r=row+ dRow[dir];
        int c=col+dCol[dir];
        if(r>=0 && r<size && c>=0 && c<size && board[r][c]==opponent){
            r+=dRow[dir];
            c+=dCol[dir];
            while(r>=0 && r<size && c>=0 && c<size && board[r][c]==opponent){
                  r+=dRow[dir];
                  c+=dCol[dir];
            }
        }
        
        if(r>=0 && r<size && c>=0 && c<size && board[r][c]==player){
    
            int stepR = row + dRow[dir];
            int stepC = col + dCol[dir];
                while (stepR != r || stepC != c) {
                  board[stepR][stepC] = player; // Taşı çevir
                  totalFlipped++;
                  stepR += dRow[dir];
                  stepC += dCol[dir];
                }
                
            }

        }
        return totalFlipped;
    }
    
bool playComputerMove(char board[][MAX_SIZE], int size){
    int maxFlipped=0;
    int bestRow=-1;
    int bestCol=-1;
    for(int r=0; r<size-1; ++r){
        for(int c=0; c<size; ++c){
            if(isMoveLegal(board,size,r,c,'X')){

               char tempBoard[MAX_SIZE][MAX_SIZE];
               for(int i=0; i<size; ++i){
                for(int  j=0; j<size; ++j){
                    tempBoard[i][j]=board[i][j];

                }
               }


               int flipped = makeMove(tempBoard, size, r, c, 'X');
               if(flipped>maxFlipped){
                maxFlipped=flipped;
                bestCol=c;
                bestRow=r;
               }
            }
        }
    }

    if(maxFlipped>0){
        makeMove(board, size, bestRow, bestCol, 'X');
        char colLetter = static_cast<char>('a' + bestCol);
        std::cout << "Computer played: " << (bestRow + 1) << colLetter << "\n";
        return true;
    }
   
    return false;
  
}    

bool hasAnyValidMove(const char board[][MAX_SIZE], int size, char player) {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (isMoveLegal(board, size, r, c, player)) {
                return true;
            }
        }
    }
    return false;
}


void printScoresAndWinner(const char board[][MAX_SIZE], int size) {
    int userScore = 0;
    int compScore = 0;

    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (board[r][c] == 'O') {
                userScore++;
            } else if (board[r][c] == 'X') {
                compScore++;
            }
        }
    }

    std::cout << "\n--- GAME OVER ---\n";
    std::cout << "User (O): " << userScore << "\n";
    std::cout << "Computer (X): " << compScore << "\n";

    if (userScore > compScore) {
        std::cout << "Congratulations! User won!\n";
    } else if (compScore > userScore) {
        std::cout << "Computer won!\n";
    } else {
        std::cout << "It's a tie!\n";
    }
}

int getBoardSize() {
    int size = 0;
    while (true) {
        std::cout << "Enter board size (8, 10, or 12): ";
        if (std::cin >> size) {
            if (size == 8 || size == 10 || size == 12) {
                return size;
            }
            std::cout << "Invalid size! You must enter 8, 10, or 12.\n";
        } else {
            // Sayı yerine harf vb. girilirse akışı temizle
            std::cin.clear();
            std::string dummy;
            std::cin >> dummy;
            std::cout << "Invalid input! Please enter a number.\n";
        }
    }
}





