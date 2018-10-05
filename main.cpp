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
    std::vector<TTT_Game> game_history;
    //TTT_Game t;
    for(int i = 0; i < 100; ++i)
    {
        game_history.push_back(TTT_Game());
    }

    for(TTT_Game t : game_history)
    {
       printBoard(t);
    }
}
