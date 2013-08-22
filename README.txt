The file contains:
1>The source code (KenKenPuzzleSolverSRC.c) for solving an NxN ken ken puzzle.2>The executable (KenKenPuzzleSolver) of the code is also present.
3>The Answers (Programming assignment 1 Problems.pdf) for the questions related to Ken Ken.
4>The input_q3 and its respective output output_q3
5>A trial input and its output.Please note that this is a C code and was executed on MAC platform (using a gcc compiler)The executable needs to be executed on a unix or MAC platform with the following command
niveditamanjunath$ ./KenKenPuzzleSolver <input_file.txt> <output.txt>If the windows machine is unable to recognize the executable then please compile the source code named as KenKenPuzzleSolverSRC.c file using a c compiler and execute >gcc KenKenPuzzleSolverSRC.c>a.exe <input.txt> <output.txt>The output file would be created in the same directory under the name output.txtAssumption:The code has been based on the following assumptionsa>The input file is correct, i.e., no error checks have been placed if the input text has errors in it.b>Output file is expected

The constraints function:
The validate() function, is called every time a child node is created, the child node gets added to the STACK only if it satisfies all the constraints laid out in the valid function.
The STACK's behavior i.e., First in Last Out, ensures DFS(i.e., the most recent child node is expanded) and Backtracking by keeping track of the valid nodes.Trials: The code took about 2 mins and 45 seconds to print a solution for a 9X9 matrix. 

