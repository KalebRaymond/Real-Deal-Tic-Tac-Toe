#include <vector>

class State;
class TTT_Game;
class Opponent;

/* Class representing a game of tic tac toe at an aribitrary turn */
class State
{
    std::vector<char> board;
    double score;
    char checkWin();
};

/* A class representing a game of tic tac toe */
/*class TTT_Game
{
    public:
        Opponent* opponent;
        std::vector<State> states;
        std::vector<int> X_moves,
                         O_moves;
        std::vector<int> available_moves;

        char checkWin(State s);
        void autoPlay();
        void printBoard();
        TTT_Game(Opponent* opponent);

};*/

/* Class representing player O */
class Opponent
{
    public:
        std::vector<State> play_history;
        //std::vector< std::vector< char>> states; //Sometimes I really regret learning C++ as my first language
        double move_probability[9];

    //public:

        void playNewGames(int n);
        void playVsUser();
        bool seenState(std::vector<char> state);
        Opponent(int training_session);

};
