#include "TTT_Game.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/* State members */

char State::checkWin(int turn_count)
{
    /* 0 1 2  /
    /  3 4 5  /
    /  6 7 8 */
    //Check diagonals
    if(( board[0] == board[4] && board[0] == board[8] )
        || ( board[6] == board[4] && board[6] == board[2] ))
    {
        if(board[4] != '-');
            return board[4];
    }

    //Check rows & columns
    for(int i = 0; i < 3; ++i)
    {
        if(board[i * 3] == board[(i * 3) + 1] && board[i * 3] == board[(i * 3) + 2])
        {
            if(board[i * 3] != '-');
                return board[i * 3];
        }
        if(board[i] == board[3 + i] && board[i] == board[6 + i])
        {
           if(board[i] != '-');
                return board[i];
        }
    }

    //Check if game is drawn
    //(by checking for a draw after checking 3's in a row, this prevents returning draw if the game is won on the 9th move)
    if(turn_count == 9)
    {
        return 'D';
    }

    //Otherwise, the game is still going
    return '-';
}


void State::printBoard()
{
    for(int i = 0; i < 9; ++i)
    {
        std::cout << board[i];

        if(i % 3 == 2)
            std::cout << "\n";
    }

    std::cout << "\n";
}

State::State()
{
    static bool seeded = false;
    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    board = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
}

/* Opponent members */

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
    int turn_count = 1;

    std::vector<char> cur_board = {'-','-','-','-','-','-','-','-','-'};

    std::cout << "New game\n";

    for(int i = 0; i <= 8; ++i)
    {
        if(!this->seenState(cur_board))
        {
            std::cout << "New state:\n";
            play_history.push_back(State());

            for(int j = 0; j < 8; ++j)
            {
                play_history[play_history.size() - 1].board.push_back(cur_board[j]);
            }

            if(play_history[play_history.size() - 1].checkWin(turn_count) != '-')
            {
                break;
            }
        }

        while(available_moves[cur_move] == -1)
        {
            cur_move = rand() % available_moves.size();

        }

        cur_board[available_moves[cur_move]] = players[i % 2];
        ++turn_count;

        //std::cout << cur_move / 3 << " " << cur_move % 3;
        available_moves[cur_move] = -1;

    }

    //std::cout << cur_state.checkWin(turn_count) << "\n";
}


void Opponent::playNewGames(int n)
{
    for(int i = 0; i < n; ++i)
    {
        //play_history.push_back(State());
        play();
    }
}

void Opponent::playVsUser()
{
    State current_game;
    std::vector<int> available_moves = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int turn_count = 0;

    while(current_game.checkWin(turn_count) == '-')
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
            available_moves[(row * 3) + column] = -1;
        }
        else
        {
            int cur_move = rand() % available_moves.size();
            while(available_moves[cur_move] == -1)
            {
                cur_move = rand() % available_moves.size();
            }

            current_game.board[cur_move] = 'O';
            available_moves[cur_move] = -1;
        }

        ++turn_count;
    }

}

//Returns true if parameter state "state" has been encountered in opponent's play experience
bool Opponent::seenState(std::vector<char> state_board)
{
    bool found = false;
    //s should be a State object
    for(auto s: play_history)
    {
        for(int i = 0; i < 9; i++)
        {
            if(s.board[i] != state_board[i])
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
