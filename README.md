# Real Deal Tic-Tac-Toe
 
Using a min-max algorithm is a whole lot faster, simpler, and should be used in the real world instead of this machine learning bs,  and because Tic Tac Toe is a solved game an AI is totally unnecessary anyway, but machine learning bs is a lot more fun and interesting.

In contrast to my other Tic Tac Toe project that used min-max, this one's opponent prepares for the game by simulating a given amount of test rounds and applying what it learned against the user.

I would have added a function to determine whether two tic-tac-toe games were reflections/rotations of eachother, thus reducing the search space for learning from past games, but the complexity of transforming each game eight times and performing a linear search each time outweighed the benefits. There might be some better way of checking such as bijectional mapping or something, but there are bigger fish to fry.

The bulk of this program was spent trying to decipher what `V(s) <- V(s) + α[ V(s') - V(s) ]` meant in terms of code (with procrastinating in the README coming in close second.) It took me like three days to figure out that `<-` just meant the asignment operator `=`. All the articles on temporal difference reinforcement learning are written in highly theoretical language - perhaps it is my duty to spoonfeed others who shall follow in my path.



https://www.cs.dartmouth.edu/~lorenzo/teaching/cs134/Archive/Spring2009/final/PengTao/final_report.pdf  
https://users.auth.gr/kehagiat/Research/GameTheory/12CombBiblio/TicTacToe.pdf  
