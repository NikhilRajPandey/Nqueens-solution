#include <iostream>
#include <string>
#include <vector>
#include <array>

class Solution {
    public:
        int boardSize;
        int **board;
        /* Board[i][j] value meanings.
        1 mean queen place
        0 mean a place where queen can't attack
        -n means 'n' queens can attack on this place
        */
        std::vector<int **> solutions;
        int **curr_solution;
        // solution vector will be like [[x1,y1],[x2,y2]....],[x1,y1],[x2,y2]....]...]
        // solution[n] will be the array of cordinates[i and j] where queen can placed
        
    
    int ** giveBoard(){ // Allocate memory for board
        int **Board = (int**)calloc(this->boardSize,sizeof(int*));
        for (int i = 0; i < this->boardSize; i++){
            Board[i] = (int*)calloc(this->boardSize,sizeof(int));
        }
        return Board;
    }
    // Gives the array of pair
    int ** giveArrPair(){
        int **ArrPair = (int **)calloc(this->boardSize,sizeof(int*));
        for (int i = 0; i < this->boardSize; i++){
            ArrPair[i] = (int*)calloc(2,sizeof(int));
        }
        return ArrPair;
    }

    void resetCurSolution(){ // Reset curr solution
        this->curr_solution = giveArrPair();
        for (int i = 0; i < this->boardSize; i++){
            this->curr_solution[i][0] = this->solutions[this->solutions.size()-1][i][0];
            this->curr_solution[i][1] = this->solutions[this->solutions.size()-1][i][1];
        }
    }
    // Accesing the board can be done using Board[y][x]
    inline bool isOutOfscreen(int y,int x){
        if(x < 0 || y < 0 || x >= this->boardSize || y >= this->boardSize){
            return true;
        }
        return false;
    }
    /* Mark or Unmark All the moves where queen can attack
    If val is -1 means Mark and if 1 then means unmark */
    void markAllQMoves(int y,int x,int val){ // accesing using Board[y][x]

        // Marking Horizontally
        for (int i = 0; i < this->boardSize; i++){
            if(i == x)continue;
            this->board[y][i] += val;
        }
        // Marking Vertically
        for (int i = 0; i < this->boardSize; i++){
            if(i == y)continue;
            this->board[i][x] += val;
        }
        // Marking Diagonally[Camel]

        /*These i and j will generate this combination [+1+1],[+1,-1],[-1,+1],[-1,-1]*/
        for (int i = -1; i < 2; i+=2){
            for (int j = -1; j < 2; j+=2){
                for (int k = 1; !this->isOutOfscreen(y+i*k,x+j*k); k++){
                    this->board[y+i*k][x+j*k] += val;
                }
            }
        }
    }
    

    void solveNQueensUtil(int noOfqSet=0,int i=0,int j=0){ // noOfqSet is no of queens set on their places
        if(noOfqSet == this->boardSize){
            this->solutions.push_back(this->curr_solution);
            this->resetCurSolution();
            return;
        }

        while (i < this->boardSize){
            while (j < this->boardSize){
                if(this->board[i][j] == 0){ // Desirable location
                    this->board[i][j] = 1;
                    this->markAllQMoves(i,j,-1);
                    this->curr_solution[noOfqSet][0] = i;
                    this->curr_solution[noOfqSet][1] = j;

                    this->solveNQueensUtil(noOfqSet+1,i,j);
                    this->board[i][j] = 0;
                    this->markAllQMoves(i,j,1);
                }
                j++;
            }
            i++;
            j = 0;
        }

    }
    std::vector<int **> solveNQueens(int n) {
        this->boardSize = n;
        this->board = giveBoard();
        this->curr_solution = this->giveArrPair();
        this->solveNQueensUtil();
        return this->solutions;
    }
};

int main(){
    Solution s;
    int nOfq;
    printf("No of queens. You want: ");
    scanf("%d",&nOfq);

    std::vector<int **> test = s.solveNQueens(nOfq);
    std::cout<<"\nNo Of Solution "<<s.solutions.size()<<std::endl;

    /*Please Ignore this Place. This is just printing the board */
    for (int n = 0; n < s.solutions.size(); n++){
        int nofQprinted = 0; // Nof of queens printed
        for (int i = 0; i < s.boardSize; i++){
            for (int j = 0; j < s.boardSize; j++){
                printf("|");
                if(nofQprinted < s.boardSize){
                    if(s.solutions[n][nofQprinted][0] == i && s.solutions[n][nofQprinted][1] == j){
                        printf("Q");
                        nofQprinted++;
                        continue;
                    }
                }
                printf(" ");
            }
            printf("|\n");
        }
        printf("\n");
    }
    
    
    return 0;
}
