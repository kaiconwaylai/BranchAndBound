***Instructions***

Requires a C++ compiler with at least C++14 (I think, may be ok with C++11).
I included all the .cpp files in the main file 'BranchAndBound.cpp' because its simpler.
Processing times are hard-coded in and are the maps named _ProcessTimes.

To run:
Compile 'BranchAndBound.cpp' and run the output with argument from 0-4 with each option representing:

 0 - Original algorithm set to time out at 30k and then autocomplete the current best solution.

 1 - Original algorithm with Tardiness/CompletedNodes as the heuristic for jump tracking rather than total tardiness. This stops at first complete solution found.

 2 - Same as above but with not terminating after first solution found, instead finding 1000 (this is hard-coded currently but could potentially be changed) solutions and picking the best from there. This stops when its found 1000 solutions.

 3 - 2 with added pruning so any partial solution with a tardiness equal or above the best solution's so far is pruned. This stops when the queue is empty or 1000 solutions are found. It's always when queue is empty because it cant find any more solutions better than optimal past a point.

 4 - Same as 3 with added stopping heuristic on a number of iterations hard coded right now but would be best as the iterations needed to find first solution.

##### Output
The output shows the best schedule found and the run time of the algorithm to that found it. There is a seperate function to print the current best solution at each iteration that requires an output filestream and the global iterations to print but this can be ignored as its outputs are included.

##### Program

The code works by building a tree of nodes that contains precedences and information about job work time + due date etc.
To find a schedule it keeps track of the currently available, unprocessed nodes and selects one to process. After that the just processed node's children are added to the available pile and this is repeated. A node can't be processed unless all of its parents have been completed.

Code can be improved in quality but it does the job.
