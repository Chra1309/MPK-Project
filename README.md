# MPK-Project

Für alle die ein kleines Tutorial brauchen!
https://www.youtube.com/watch?v=0fKg7e37bQE


ToDo: 


-[x] starten

-[x] server sendet würfel an client - client löst am client

-[ ] client gibt dem server anweisungen zum lösen des würfels

-[ ] Rubiks Würfel

-[x] faces random erzeugen 

-[ ] 

-[ ] Mastermind

-[ ] zusammensetzten

-[ ] Projekt fertig 

_____________________________________________________________________________

## PROGRESS:

Spuli:

-Fragen für beliebige "n" können jetzt zu 2er fragen heruntergebrochen werden. Diese 2er fragen werden sogar als geordnetes array beantwortet. Die funktion "aksTwo" im client ist dafür zuständig.

-Der server erstellt jetzt nur noch beim starten einen random cube und dieser lebt dann weiter über die ganze progreammlaufzeit.

jakob + kathi:
FILLCUBE:
Auffüllen eines Würfels aus der Liste:
#include "masterheader.hpp"
#include "fillcube.hpp"
    fillrandomcube(MiddleCode, MiddleColor, EdgeCodes, CornerCodes);
es wird ein cube[6][3][3] befüllt und kann an den Solver übergeben werden. 
(ind fillrandomcube wird auch ein solvability-test ausgeführt - ist in solvability.hpp)




The faces are displayed as if you are facing them in this order
	
	Top
	Left
	Front
	Right
	Back
	Bottom

	0   y   yellow
	1   o   orange
	2   b   blue    
	3   r   red // falsch es ist green //richtig es ist red
	4   g   green // falsch es ist red // richtig es rst green
	5   w   white
	6       black


_____________________________________________________________________________

WICHTIGSTE git-commands
    
    git clone
    git status
    git add
    git commit -m "deintextstehthier"
    git push
    git pull


_____________________________________________________________________________
rubikssolver - Link von Mehnen 
A text-based rubik's cube solver. 

Authors: Eric Kuecks <ekuecks@ucla.edu>
	 http:/github.com/ekuecks
	 
	 Chandler Brown <chanbrown007@yahoo.com>
	 http:/github.com/chanbrown007

It will give you a scramble from the solved state then
all necessary rotations to solve it.

This project assumes you have basic familiarity with 
rubik's cube rotation notation.
for more information, visit:
http://www.speedsolving.com/wiki/index.php/3x3x3_notation
NOTE: we used i instead of ' to indicate CCW (ri instead of r')

USE:
Type make to compile.
Then type ./cube to run the program.

Color Representation:
We will use a standard cube held with white on the bottom, blue
in front, and red on the right for the examples






