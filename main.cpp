#include <iostream>
#include "TTT_Game.h"


int main()
{
    Opponent opp = Opponent(100);

    for(int i = 0; i < opp.play_history.size(); ++i)
    {
        opp.play_history[i].printBoard();
    }
    /*for(State s : opp.play_history)
    {
        std::cout << s.checkWin(9)<< " wins.\n";
        s.printBoard();
    }*/

    //opp.playVsUser();
    State tx;
    tx.board = {'X','X','X','X','X','X','X','X','X'};
    State to;
    to.board = {'O','O','O','O','O','O','O','O','O'};
    State tt;
    tt.board = {'X','-','-','-','-','-','-','O','-'};

    opp.play_history.push_back(to);
    opp.play_history.push_back(tx);
    //std::cout << opp.states[0][2];
    std::cout << opp.seenState(tt.board);


}
