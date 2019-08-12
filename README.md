# Real Deal Tic-Tac-Toe
 
Using a min-max algorithm is a whole lot faster, simpler, and should be used in the real world instead of going through the trouble of machine learning, and because Tic Tac Toe is a solved game an AI is totally unnecessary anyway, but machine learning is a lot more fun and interesting.

In contrast to my other Tic Tac Toe project that used min-max, this one's opponent prepares for the game by simulating a given amount of test rounds and applying what it learned against the user. After about 25,000 games of training, it performs as well as the minmax opponent does after zero training 💪. 

I would have added a function to determine whether two tic-tac-toe games were reflections/rotations of eachother, thus reducing the search space for learning from past games, but the complexity of transforming each game eight times and performing a linear search each time outweighed the benefits. There might be some better way of checking such as bijectional mapping or something.

## Works cited
https://www.cs.dartmouth.edu/~lorenzo/teaching/cs134/Archive/Spring2009/final/PengTao/final_report.pdf  
https://users.auth.gr/kehagiat/Research/GameTheory/12CombBiblio/TicTacToe.pdf  
