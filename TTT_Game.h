#include <vector>

class State;
class TTT_Game;
class Opponent;

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
        //std::vector< std::vector< char>> states; //Sometimes I really regret learning C++ as my first language
        double move_probability[9];

    //public:
        void play();
        void playNewGames(int n);
        void playVsUser();
        bool seenState(std::vector<char> state_board);
        Opponent(int training_session);

};
