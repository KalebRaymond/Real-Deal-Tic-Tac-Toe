#include "TTT_Game.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/* State members */

char State::checkWin()
{
    /* 0 1 2  /
    /  3 4 5  /
    /  6 7 8 */
    //Check diagonals
    if(( board[0] == board[4] && board[0] == board[8] )
        || ( board[6] == board[4] && board[6] == board[2] ))
    {
        return board[4];
    }

    int move_count = 0;
    //Check rows & columns
    for(int i = 0; i < 3; ++i)
    {
        if(board[i * 3] == board[(i * 3) + 1] && board[i * 3] == board[(i * 3) + 2])
        {
            return board[i * 3];
        }
        if(board[i] == board[3 + i] && board[i] == board[6 + i])
        {
            return board[i];
        }
    }

    //Check if game is drawn
    //(by checking for a draw after checking 3's in a row, this prevents returning draw if the game is won on the 9th move)
    /*if(X_moveboard.size() + O_moveboard.size() == 9)
    {
        return 'D';
    }*/

    //Otherwise, the game is still going
    return '-';
}

State::State()
{
    board = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
}

void Opponent::play()
{
    //So I'm thinking the configuration of board[3][3] is s. Thus V(s) somehow determiens the value of that state s.
    //I suppose s' is a state that has already been encountered, which can be accessed from a database of states.
    /*   a. In each episode of the learning phase                                                                                   /
    /    1) Observe a current board state s;                                                                                        /
    /    2) Make a next move based on the distribution of all available V(s') of next moves;                                        /
    /    3) Record s' in a sequence;                                                                                                /
    /    4)  If  the  game  finishes,  it  updates  the  values  of  the  visited  states  in  the  sequence  and  starts  over     /
    /    again; otherwise, go to 1).                                                                                               */


    //Randomize players between [X, O] and [O, X] to simulate games starting with different player
    char players[2];
    std::vector<int> available_moves = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int X_turn = rand() % 2;

    players[X_turn] = 'X';
    players[1 - X_turn] = 'O';
    int cur_move = rand() % available_moves.size();

    State cur_state;

    for(int i = 0; (i <= 8) && (cur_state.checkWin() == '-'); ++i)
    {
        if(!this.seenState(cur_state))
        {
            play_history.push_back(cur_state);
        }

        while(available_moves[cur_move] == -1)
        {
            cur_move = rand() % available_moves.size();
        }

        cur_state.board[i] = cur_move;

        //std::cout << cur_move / 3 << " " << cur_move % 3;
        available_moves[cur_move] = -1;
    }
}

/*void TTT_Game::printBoard()
{
    for(int i = 0; i < 9; ++i)
    {
        std::cout << board[i];

        if(i % 3 == 2)
            std::cout << "\n";
    }

    std::cout << "\n";
}

TTT_Game::TTT_Game(Opponent* opponent)
{
    static bool seeded = false;
    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    board = {'-', '-','-','-','-','-','-','-','-'};

    this->opponent = opponent;

}*/

/* Opponent members */

void Opponent::playNewGames(int n)
{
    for(int i = 0; i < n; ++i)
    {
        play_history.push_back(State);
    }
}

void Opponent::playVsUser()
{
    TTT_Game current_game(this);
    current_game.available_moves = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int turn_count = 0;

    while(current_game.checkWin() == '-')
    {
        current_game.printBoard();

        if(turn_count % 2 == 0)
        {
            int row = 0, column = 0;
            std::cout << "Enter row: ";
            std::cin >> row;
            std::cout << "Enter column: ";
            std::cin >> column;

            current_game.board[(row * 3) + column] = 'X';
            current_game.available_moves[(row * 3) + column] = -1;
        }
        else
        {
            int cur_move = rand() % current_game.available_moves.size();
            while(current_game.available_moves[cur_move] == -1)
            {
                cur_move = rand() % current_game.available_moves.size();
            }

            current_game.board[cur_move] = 'O';
            current_game.available_moves[cur_move] = -1;
        }

        ++turn_count;
    }

}

//Returns true if parameter state "state" has been encountered in opponent's play experience
bool Opponent::seenState(std::vector<char> state)
{
    bool found = false;
    for(auto s: states)
    {
        for(int i = 0; i < 9; i++)
        {
            if(s[i] != state[i])
            {
                break;
            }

            found = true;
        }

        if(found)
        {
            return true;
        }
    }

    return false;
}

Opponent::Opponent(int training_session)
{
    for(double &d : move_probability)
    {
        d = 0.0;
    }

    playNewGames(training_session);
}
