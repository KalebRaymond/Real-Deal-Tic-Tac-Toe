#include <vector>
/* A class representing a game of tic tac toe */

class TTT_Game
{
    private:
        std::vector<int> X_moves, O_moves;
        char board[3][3];
    public:
        char checkWin();
        TTT_Game();
};
