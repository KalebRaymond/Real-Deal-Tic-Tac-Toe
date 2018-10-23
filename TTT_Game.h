#include <vector>

class State;
class Opponent;

//I'm going to keep everything public just for ease of developing

/* Class representing a game of tic tac toe at an aribitrary turn */
class State
{
    public:
        std::vector<char> board;
        double score;

        char checkWin(int turn_count);
        void printBoard();
        State();
};

/* Class representing player O */
class Opponent
{
    public:
        std::vector<State> play_history;
        double move_probability[9];

        void play();
        void playNewGames(int n, int key);
        void playWithData();
        void playVsUser();
        int getIndex(std::vector<char> state_board);
        Opponent(int training_session, int key);

};
