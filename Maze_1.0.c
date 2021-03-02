//Kindly read the README.txt also to understand the mechanisms and short history behind this project

#include<stdio.h>
#include<windows.h>
#include<time.h>
#define M 100	//Map size M*M

int maze[M + 1][M + 1] = { 0 };//The size for the initial maze
int size;//size for the map
char str[2 * (M + 1)*(M + 1)] = { '\0' };//The array to store symbols for the maze in order print
typedef struct//setting coordinates 
{
	int x;	
	int y;
}Point;

void starting_maze(int size);//function to initialize the map
void print_any();//function to print
void menu();//Menu function
int SidesOK(int pos_x, int pos_y);//function to determine if there are walls on the side
void maze_generator(int pos_x, int pos_y);//Random maze generator function
int visited(int maze[][M+1],Point,Point);//Maze recursion to find path between two "Point"
Point pt(int,int);//function to return coordinates


//The game starts here =w=

Point pt(int x, int y)
{
	Point p={x,y};
	return p;
}

int main(void)
{
	int sign = 0;
	int s[100][100] = { 0 };
	size=0;

	srand(time(NULL));//Random seed generator, to achieve near random
	
	menu();//Calling menu function
	starting_maze(size);//Initializing the maze
	print_any();//Prit the randomly generated maze
	printf("\nYour maze has been successfully generated......\n");
	visited(maze,pt(1,1),pt(size-2,size-2));//Pathfinding at the start and end of the generated maze, i.e. finding the route that connects the start and end points 
	print_any();//Print the maze
	printf("\nYour solution has been successfully generated......\n\n");

	system("pause");
	return 0;
}

int SidesOK(int pos_x, int pos_y)//Determine if a cell with a value of 0 is surrounded by other cells with the same value of 0
{
	int i, j, sign = 0;
	//if exist return 1, else return 0
	if ((pos_x >= 3 && maze[pos_x - 2][pos_y] == 0) || (pos_x < size - 3 && maze[pos_x + 2][pos_y] == 0) || (pos_y >= 3 && maze[pos_x][pos_y - 2] == 0) || (pos_y < size - 3 && maze[pos_x][pos_y + 2] == 0))
	{
			return 1;
	} 
		return 0;
}

int visited(int maze[][M+1],Point start,Point end) 
{
	if(!maze[start.x][start.y])//If coordinates is blank, start looping
	{
		maze[start.x][start.y]=1;// set this coordinate to 1, i.e. it has been travelled
		
		// walk recursively up and down, left and right, looking for a solution before reaching the end; if you hit a dead end, go back the way you came 
		if((!maze[end.x][end.y])&&!(visited(maze,pt(start.x,start.y+1),end)||visited(maze,pt(start.x,start.y-1),end)||visited(maze,pt(start.x+1,start.y),end)||visited(maze,pt(start.x-1,start.y),end)))
		{
			maze[start.x][start.y]=0;// When a dead end is encountered return all back roads to 0 i.e. empty space 
		}
	}
	return maze[end.x][end.y];
}
	
void Maze_generator(int pos_x, int pos_y)
{
	int rand_direction, x, y, sign = 0;
	x = pos_x;//store start point x
	y = pos_y;//store start point y
	
	//dead loop, walk around in all four directions at random, if you hit a dead end, backtrack and find another guide to walk until all of the maze has been visited 
	while (1)
	{
		sign = 0;
		sign = SidesOK(pos_x, pos_y);//Ensuring if there are nearby targets
		if (sign == 0)//return if cant find
		{
			return;
		}
		else
		{
			maze[pos_x][pos_y] = 5;//This is the starting point, all visted blocks are markes as zero
			x = pos_x;//store starting point x
			y = pos_y;//store starting point y
			while (1)
			{
				rand_direction = rand() % 4;//Pick a random direction of travel from 0, 1, 2, 3, i.e. up, down, left, right or left 
				if (rand_direction == 0 && pos_x >= 3 && maze[pos_x - 2][pos_y] == 0)//up
				{
					pos_x = pos_x - 2;
				}
				else if (rand_direction == 1 && pos_x < size - 3 && maze[pos_x + 2][pos_y] == 0)//down
				{
					pos_x = pos_x + 2;
				}
				else if (rand_direction == 2 && pos_y >= 3 && maze[pos_x][pos_y - 2] == 0)//left
				{
					pos_y -= 2;
				}
				else if (rand_direction == 3 && pos_y < size - 3 && maze[pos_x][pos_y + 2] == 0)//right
				{
					pos_y += 2;
				}
				//connect to pts with 1
				maze[(x + pos_x) / 2][(y + pos_y) / 2] = 5;// put the old point between the new point and the old point together with the new point to indicate a walk through 
				maze[pos_x][pos_y] = 5;// will be a new point also means walk through 
				Maze_generator(pos_x, pos_y);// Repeat recursive loop 
				break;
			}
		}
	}
}

void starting_maze(int num) 
{
	int i, j;
	if (num % 2 == 0) // If it is an even number, add one to make it an odd number in order to ensure that the maze can be generated correctly  
	{
		size++;
	} 
	
	for (i = 0;i < size;i++)	// turn all units in the maze area into 2, i.e. walls 
	{ 
		for (j = 0;j < size;j++)
		{
			maze[i][j] = 2;
		}
	}	 
	
	for (i = 0;i < M;i++)// Next to deal with the cells outside the labyrinth range 
	{
		for (j = 0;j < M;j++)
		{
			if (i >= size || j >= size)// reduce all cells outside the maze range to -1, no need to print out 
			{ 
				maze[i][j] = -1;
			} 
			else if (i != 0 && j != 0 && i != size - 1 && j != size - 1)// if not any of the rows at the corners , then inside the maze, spacing is 0 
			{
				if (i % 2 != 0)//if i is a odd number
				{
					if (j % 2 == 1)// if j is also an odd number , make this point 0  
					{
						maze[i][j] = 0; 
					} 
				}	
			}
			
		}
	}
	 
	Maze_generator(1, 1);//Generate maze setting starting point 
	
	for (i = 0;i < size;i++)// reshuffle once to erase all traces of being visited and turn the unit back to empty space 0 
	{
		for (j = 0;j < size;j++)
			if (maze[i][j] == 5)
				maze[i][j] = 0;
	}
	maze[1][1] = 0;// define the starting point as an empty space 
	maze[size - 2][size - 2] = 0;// Define the end point as a null position 
}

void print_any()// function to print a maze 
{
	int i = 0, j = 0;
	str[0] = '\0';
	for (i = 0;i < M;i++)//external loop
	{
		for (j = 0;j < M;j++)//internal loop
		{
			switch(maze[i][j])// Print the symbol for the point 
			{
				case 2:strcat(str, "##");break;//'##' set as wall
				case -1:break;                 //If you encounter any numbers outside of the maze size that do not print 
				case 0:strcat(str, "  ");break;// If 0, it is empty 
				case 1:strcat(str,"o ");break;// If 1, print the path 
			}
		}
		if (maze[i][0] != -1)//change rows
		{
			strcat(str, "\n");
		}	
		//printf("\n");
	}
	printf("%s", str);//print the symbols

}

void menu()// Control menu with control over the size of the maze map
{
	printf("***Hey there, This is a Random Maze Generator***\n\n");
	printf("Please enter the size of the maze you want:");//Enter maze size here'size'
	scanf("%d", &size);
	
}


 


