// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.



//At first we set n
(Infinite)


@KBD
D = M
@BLACK
D; JGT // if D > 0 then turns black

//TURNS WHITE
@i
M = 0
@SCREEN
D = A
@KBD
D = A - D
@n
M = D


@SCREEN       //gets the add of the Screen
D = A
@index
M = D


(LOOP1)       //Fills the screen: 8192
@i
M = M + 1
D = M
@n
D = D - M
@END
D; JGT
@index
A = M
M = 0
@1
D = A
@index
M = D + M
@LOOP1
0; JMP



// TURNS BLACK
(BLACK)
@i
M = 0
@SCREEN
D = A
@KBD
D = A - D
@n
M = D


@SCREEN       //gets the add of the Screen
D = A
@index
M = D


(LOOP2)       //Fills the screen: 8096
@i
M = M + 1
D = M
@n
D = D - M
@END
D; JGT
@index
A = M
M = -1
@1
D = A
@index
M = D + M
@LOOP2
0; JMP


//runs an infinite loop
(END)
@Infinite
0; JMP
