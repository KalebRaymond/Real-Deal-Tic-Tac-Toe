#include "TTT_Game.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

char TTT_Game::checkWin()
{
    //Check diagonals
    if(( board[0][0] == board[1][1] && board[0][0] == board[2][2] )
        || ( board[2][0] == board[1][1] && board[2][0] == board[0][2] ))
    {
        return board[1][1];
    }

    //Check rows & columns
    for(int i = 0; i < 3; ++i)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    //Check if game is drawn
    //(by checking for a draw after checking 3's in a row, this prevents returning draw if the game is won on the 9th move)
    if(X_moves.size() + O_moves.size() == 9)
    {
        return 'D';
    }

    //Otherwise, the game is still going
    return '-';
}

void TTT_Game::autoPlay()
{
    //Randomize players between [X, O] and [O, X] to simulate games starting with different player
    char players[2];
    available_moves = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int X_turn = rand() % 2;

    players[X_turn] = 'X';
    players[1 - X_turn] = 'O';
    int cur_move = rand() % available_moves.size();

    for(int i = 0; (i <= 8) && (checkWin() == '-'); ++i)
    {
        while(available_moves[cur_move] == -1)
        {
            cur_move = rand() % available_moves.size();
        }

        board[cur_move / 3][cur_move % 3] = players[i % 2];
        //std::cout << cur_move / 3 << " " << cur_move % 3;
        available_moves[cur_move] = -1;
    }

    std::cout << "\n";
}

void TTT_Game::printBoard()
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::cout << board[i][j];
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

TTT_Game::TTT_Game()
{
    static bool seeded = false;
    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }

}


void Opponent::playNewGames(int n)
{
    for(int i = 0; i < n; ++i)
    {
        play_history.push_back(TTT_Game());
        play_history[i].autoPlay();
    }
}

void Opponent::playVsUser()
{
    TTT_Game current_game;
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

            current_game.board[row][column] = 'X';
            current_game.available_moves[(row * 3) + column] = -1;
        }
        else
        {
            int cur_move = rand() % current_game.available_moves.size();
            while(current_game.available_moves[cur_move] == -1)
            {
                cur_move = rand() % current_game.available_moves.size();
            }

            current_game.board[cur_move / 3][cur_move % 3] = 'O';
            current_game.available_moves[cur_move] = -1;
        }

        ++turn_count;
    }

}

Opponent::Opponent(int training_session)
{
    for(double &d : move_probability)
    {
        d = 0.0;
    }

    playNewGames(training_session);
}
