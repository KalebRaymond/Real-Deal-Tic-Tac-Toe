#include <iostream>
#include "TTT_Game.h"

void printBoard(TTT_Game t)
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::cout << t.board[i][j];
        }

        std::cout << "\n";
    }

    std::cout << "\n\n";
}

int main()
{
    Opponent opp = Opponent(100);

    for(TTT_Game t : opp.play_history)
    {
        std::cout << t.checkWin() << " wins.\n";
        printBoard(t);
    }


}
