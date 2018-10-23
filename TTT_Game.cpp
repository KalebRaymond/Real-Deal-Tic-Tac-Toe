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

    //Game cannot be won within first four moves
    if(turn_count < 4)
    {
        return '-';
    }

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
    score = 0.5;
}

/* Opponent members */

//Function to have opponent train by making random moves
void Opponent::play()
{
    //Randomize players between [X, O] and [O, X] to simulate games starting with different player
    char players[2];
    std::vector<int> available_moves = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int X_turn = rand() % 2;

    players[X_turn] = 'X';
    players[1 - X_turn] = 'O';
    int cur_move = rand() % available_moves.size();
    int turn_count = 1;
    int board_index = 0;

    std::vector<char> cur_board = {'-','-','-','-','-','-','-','-','-'};
    std::vector<int> state_indices;

    for(int i = 0; i <= 8; ++i)
    {
        //Get legal move
        while(available_moves[cur_move] == -1)
        {
            cur_move = rand() % available_moves.size();
        }

        //Place X or O in board
        cur_board[available_moves[cur_move]] = players[i % 2];
        ++turn_count;

        //Mark move as taken
        available_moves[cur_move] = -1;

        board_index = this->getIndex(cur_board);

        //Cur_board has not been encountered before
        if(board_index == -1)
        {
            play_history.push_back(State());
            play_history[play_history.size() - 1].board = cur_board;
            state_indices.push_back(this->play_history.size() - 1);

            if(play_history[play_history.size() - 1].checkWin(turn_count) != '-')
            {
                break;
            }
        }
        else
        {
            state_indices.push_back(board_index);
        }
    }

    //If opponent won, give state a score of 1. Otherwise, a score of 0.
    if(this->play_history[state_indices[state_indices.size() - 1]].checkWin(turn_count) == 'O')
        this->play_history[state_indices[state_indices.size() - 1]].score = 1;
    else
        this->play_history[state_indices[state_indices.size() - 1]].score = 0;

    double alpha = 0.5;
    for(int i = state_indices.size() - 2; i >= 0; --i)
    {
        this->play_history[state_indices[i]].score = this->play_history[state_indices[i]].score + alpha * (this->play_history[state_indices[i + 1]].score - this->play_history[state_indices[i]].score);
        alpha = alpha - (alpha / this->play_history.size());
    }
}

//Function to have opponent train using its experience. Conspicuously, opponent performs much worse using this approach.
void Opponent::playWithData()
{
    //Randomize players between [X, O] and [O, X] to simulate games starting with different player
    char players[2];
    std::vector<int> available_moves = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
    int X_turn = rand() % 2;

    players[X_turn] = 'X';
    players[1 - X_turn] = 'O';
    int cur_move = rand() % available_moves.size();
    int turn_count = 1;
    int board_index = 0;

    std::vector<char> cur_board = {'-','-','-','-','-','-','-','-','-'};
    std::vector<int> state_indices;

    for(int i = 0; i <= 8; ++i)
    {
        char player = players[i % 2];
        int board_index = this->getIndex(cur_board);

        //If current state was never encountered, make a random move
        if(board_index == -1)
        {
            int cur_move = rand() % available_moves.size();
            while(available_moves[cur_move] == -1)
            {
                cur_move = rand() % available_moves.size();
            }

            cur_board[cur_move] = player;
            available_moves[cur_move] = -1;
        }
        else
        {
            double prob_of_winning = 0;
            int best_index;

            for(int j = 0; j < 9; ++j)
            {
                if(cur_board[j] == '-')
                {
                    //Assess probability of winning if opponent plays in this space
                    cur_board[j] = player;

                    if(this->play_history[this->getIndex(cur_board)].score > prob_of_winning)
                    {
                          prob_of_winning = this->play_history[this->getIndex(cur_board)].score;
                          best_index = j;
                    }

                    cur_board[j] = '-';
                }
            }

            cur_board[best_index] = player;
            available_moves[best_index] = -1;
        }

        ++turn_count;

        board_index = this->getIndex(cur_board);

        //Cur_board has not been encountered before
        if(board_index == -1)
        {
            play_history.push_back(State());
            play_history[play_history.size() - 1].board = cur_board;
            state_indices.push_back(this->play_history.size() - 1);

            if(play_history[play_history.size() - 1].checkWin(turn_count) != '-')
            {
                break;
            }
        }
        else
        {
            state_indices.push_back(board_index);
        }
    }

    //If opponent won, give state a score of 1. Otherwise, a score of 0.
    if(this->play_history[state_indices[state_indices.size() - 1]].checkWin(turn_count) == 'O')
        this->play_history[state_indices[state_indices.size() - 1]].score = 1;
    else
        this->play_history[state_indices[state_indices.size() - 1]].score = 0;

    double alpha = 0.5;
    for(int i = state_indices.size() - 2; i >= 0; --i)
    {
        this->play_history[state_indices[i]].score = this->play_history[state_indices[i]].score + alpha * (this->play_history[state_indices[i + 1]].score - this->play_history[state_indices[i]].score);
        alpha = alpha - (alpha / this->play_history.size());
    }
}

//If key == 0, train with Opponent::play(). If key == 1, train using Opponent::playWithData()
void Opponent::playNewGames(int n, int key)
{
    if(key == 0)
    {
        for(int i = 0; i < n; ++i)
        {
            play();
        }
    }
    else
    {
        for(int i = 0; i < n; ++i)
        {
            playWithData();
        }
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
            /* X's turn */
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
            /* O's turn */
            std::vector<char> cur_board = current_game.board;
            int board_index = this->getIndex(cur_board);

            //If current state was never encountered, make a random move
            if(board_index == -1)
            {
                int cur_move = rand() % available_moves.size();
                while(available_moves[cur_move] == -1)
                {
                    cur_move = rand() % available_moves.size();
                }

                current_game.board[cur_move] = 'O';
                available_moves[cur_move] = -1;
            }
            else
            {
                double prob_of_winning = 0;
                int best_index;

                for(int i = 0; i < 9; ++i)
                {
                    if(cur_board[i] == '-')
                    {
                        //Assess probability of winning if opponent plays in this space
                        cur_board[i] = 'O';

                        if(this->play_history[this->getIndex(cur_board)].score > prob_of_winning)
                        {
                              prob_of_winning = this->play_history[this->getIndex(cur_board)].score;
                              best_index = i;
                        }

                        cur_board[i] = '-';
                    }
                }

                current_game.board[best_index] = 'O';
                available_moves[best_index] = -1;
            }
        }

        ++turn_count;
    }

    current_game.printBoard();
    std::cout << current_game.checkWin(turn_count) << " wins!\n";

}

//Returns index of the state containing state_board as its board member in Opponent::play_history. If no state is found, returns -1
int Opponent::getIndex(std::vector<char> state_board)
{
    bool found = false;
    //s should be a State object
    for(int i = 0; i < play_history.size(); ++i)
    {
        for(int j = 0; j < 9; j++)
        {
            if(play_history[i].board[j] != state_board[j])
            {
                found = false;
                break;
            }

            found = true;
        }

        if(found)
        {
            return i;
        }
    }

    return -1;
}

Opponent::Opponent(int training_session, int key)
{
    this->play_history.reserve(training_session);

    for(double &d : move_probability)
    {
        d = 0.0;
    }

    playNewGames(training_session, key);
}
