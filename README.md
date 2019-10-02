# 8-Puzzle-Problem
Solving the 4 different puzzles of the 8 Puzzle Problem using DFS, BFS and A* algorithms.

Instructions on how to run the program below.


Compile program: make

Run program: ./puzzlesolver PX algorithm (heuristic)

	Examples: -> DFS on problem 1
			- ./puzzlesolver P1 DFS
	
		  -> BFS on problem 2
			- ./puzzlesolver P2 BFS
		
		  -> A* on problem 3 with misplaced tiles heuristic (H1)
			- ./puzzlesolver P3 AStar H1

		  -> A* on problem 4 with manhattan distance heuristic (H2)
			- ./puzzlesolver P3 AStar H2

Delete executable and object files: make clean
