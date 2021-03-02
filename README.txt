#Name
Random maze generator and solver


#Description
This is a project I made in 2020 May when I was learning recursion(you could try this yourself too!). 
Recently I start sorting my codes and decide to post some of them on Github. 
This C programming currently have some flaws dealing with ranndom maze generation when it tries to generate a even number maze.
Maybe if I have time in the future, I will solve this out.


#Ideas and mechanisms
-Random maze generator
Website:https://zhuanlan.zhihu.com/p/27381213

I first understand the ideas for maze generator from this site. 
Although it is in chinese(you could use google to translate it to english), it is very detailed and well written, my maze's idea is based on it.
Since I was learning recursion, I decided to use recursion as the main method to generate my maze.

-Maze solver
This is solve using recursion also. Move on random direction and continuously trying to find a way connecting start point and end point##.


#Mechanisms
Initially, you use array to have a fixed size of the maze which here is called M, and set them all to -1.
When the function to initialize the maze "starting_maze" is runned, it reads the size of the maze that you want and then turn those to 0;
so would be something like.

 0  0  0  0  0 -1 -1 -1 
 0  0  0  0  0 -1 -1 -1
 0  0  0  0  0 -1 -1 -1
 0  0  0  0  0 -1 -1 -1
 0  0  0  0  0 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 
-1 -1 -1 -1 -1 -1 -1 -1 
-1 -1 -1 -1 -1 -1 -1 -1 
( this is a maze where initial maze size 'M' is 8 and the user define maze size is 5)

You can change M to control the maximum size for the maze

Recursion is used to generate paths and then set the rest of it as walls which is '2' and a maze is generated. 
Hence, solver uses the same method. 
More details can be viewed in the comments I put in the code.


#Installations
You can run it in a C/C++ IDE. Y
You could try to install DEV C++(not ideal, but very easy to use and install) if you find installing Visual Studio Code complicated.
I use DEV C++ for 6 months++ to learn before moving to Visual Studio Code.


Any feedbacks or suggestions are welcomed~~~


