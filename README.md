# Sudoku-Algorithm
This research topic comes from an experiment of algorithm course: 
    using the backtracking method to solve the Sudoku, using the backtracking 
method to try the number of each cell in the initial board of Sudoku, recursively,
until the Sudoku is completed.It can be seen that the implementation efficiency
of the algorithm is not high. Therefore, if the computer can observe the Sudoku
problem and solve it just like human beings, that is, combining the manual method
with the computing speed of the computer, the efficiency of the whole program will
be greatly improved.For manual solution methods, roughly includes 7 kinds, how to 
make these methods to call each other, how to let the computer to realize these 
methods, how to let the computer understand when to use what method......All these 
questions are the key points of this research.
    There is no specific reference and data for the algorithm implementation, so I 
can only rely on personal ideas to write the implementation process of the 
algorithm, and continue to optimize, so as to achieve a higher operational 
efficiency.The specific use of C++ language and data structure knowledge to achieve.
By comparing the running time of solving the same sudoku problem to determine 
the pure backtracking method and the backtracking method combining artificial 
strategy, the comparison of the advantages of the two algorithms to draw a 
conclusion.The Sudoku questions come from a large number of 9*9 Sudoku questions
on the Internet at various levels of difficulty.By comparing the experimental 
results of the program, the efficiency of integrating manual strategy is 41 times 
higher than that of backtracking method. For Sudoku with low difficulty level such as
Easy and Simple, the time of solving manual strategy is about 0.2ms, while the time of
backtracking method is about 122ms, the efficiency is significantly improved.For the
difficult sudoku such as Intermediate and Expert, the average time of manual solving 
strategy is about 2ms, while the backtracking method needs 80ms. Similarly, the improvement 
of efficiency is also very significant.Even if there are some special sudoku, make 
artificial solution strategy algorithm also not very efficient, but it looked like 
sudoku subject collected 10000 online sudoku in the title has not yet found, only 
in sudoku site collected 1 case of extreme series alone, therefore, illustrate the
efficiency of artificial solution strategy algorithm almost entirely over the 
backtracking method.
    Therefore, it can be concluded that for the vast majority of Sudoku, the manual 
method is much more efficient than the backtracking method alone.
