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

    //opp.playVsUser();
    std::vector<char> tx = {'X','X','X','X','X','X','X','X','X'};
    std::vector<char> to = {'O','O','O','O','O','O','O','O','O'};

    opp.states.push_back(to);
    //std::cout << opp.states[0][2];
    std::cout << opp.seenState(tx);


}
