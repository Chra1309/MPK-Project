# MPK-Project

## COMPILE 
run following commands to compile the project:
```
sh FirstCompile.sh
make 
```

## RUN SERVER AND CLIENT 
navigate to folder Code and open two terminal windows. One will be client, the other one the server.
first run the server by following command:
```
./autoServer
```
for starting the client you ned to give two arguments: n (number of positions per cubequestion) ms (delay in ms) 
eg.
```
./autoClient 10 0
```

## TEAM 
Auer Christoph		mr19m025

Clauss Katrin		mr19m022

Hörbst Jakob		mr19m012

Litschauer Christoph 	mr19m027

Schweiger Manuel 	mr19m005

Spulak Florian 		mr19m041

Tomasch Julia		mr19m009


## TASK
The project is a combination of the Rubik's cube puzzle and the Mastermind puzzle.
1) At the beginning a "server" will create a solvable Rubik's cube by applying x random (parameter given to the server program e.g.: 100) turns (see here) on all possible cube-sides on a cube that will have 6 different colors (red, green, blue, white, yellow, orange (not necessarily a standard "cube")) and create a client.
2) The "client" will be able to connect to the server and ask the server questions in the form of a "cube"-question (giving colors at positions (max c colors (c<=6) and max n positions (n<<9*6))). "n" will be a given parameter that keeps constant during the whole session. (Every cubequestion will have to ask for n positions)
3) The "client" will also be able to give commands to the server on how to turn the cube or cube sides in a standardized fashion (see here).
4) The "server" will answer the "cube"-question in a "MasterMind" fashion. Black (1) is returned (in an unsorted array) if a color is given at the correct position. White (0) is returned (in an unsorted array) if a color is given at the correct side of the cube. Nothing (2) is returned (in an unsorted array) if a color is neither given at the correct position nor on the correct side. The positions of the 0,1,2 in the array won't give any hint about the positions of the colors nor the sides.
5) The "server" will additionally answer the "client" if the Rubik's cube is solved or not solved - by returning 0 (not solved) or 1 (solved) and then exiting.

The "client" has to solve the Rubik's cube in an efficient way.
Trivial solutions won't be allowed (e.g. first guess the colors (pure MasterMind) and then solve the cube (pure DFS, A* or RBFS-Algorithm)). The solving can and has to already start before all the colors-positions are proven. 
You'll have to find arguments/strategies on "when" to start solving (turning) the cubes-sides.
Due to the structure of this problem you'll have to use heuristic functions to implement the strategies and change of strategies (From a pure Masterproblem to a Rubik's cube problem)

You have to deliver a C/C++ program (gnu C++ in Linux using a makefile in the automake environment), which is able to solve all the given problems (on the given homepage of the specific problem) in a reasonable time.
The project has to be compilable under the linux distribution currently used by the FHTW.
The Makefile has to include a "make test" ability - that calls the executable and tests if the program works like intended.
Any openly available libraries can be used.
You have to analyze your algorithm concerning time and memory usage (gprof and Valgrind) - without this analysis no points will be given!
At the end the group will have to give a presentation (pptx) describing all the used strategies to solve the given problem.



