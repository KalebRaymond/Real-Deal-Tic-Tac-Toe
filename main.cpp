#include <iostream>
#include "TTT_Game.h"


int main()
{
    Opponent opp = Opponent(100);

    for(TTT_Game t : opp.play_history)
    {
        std::cout << t.checkWin() << " wins.\n";
        t.printBoard();
    }

    opp.playVsUser();


}
