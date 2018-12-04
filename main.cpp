#include <iostream>
#include <cctype>      // for toupper()
#include <fstream>   

using namespace std;


// Global variables and constants
// Variables to store the board pieces

//--------------------------------------------------------------------
// Display ID info
void displayIDInfo()
{
    printf("Author: Brian Goldenberg         \n");
    printf(" \n");
}//end displayIDInfo()
//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to the traffic game!                          " << endl
         << "                                                      " << endl
         << "Move the vehicles so that the Red car (RR) can exit   " << endl
         << "the board to the right. Each move should be of the    " << endl
         << "of the form:   CDN   where:                           " << endl
         << "   C  is the vehicle to be moved                      " << endl
         << "   D  is the direction (u=up, d=down, l=left or r=right)" << endl
         << "   N  is the number of squares to move it             " << endl
         << "For example GR2  means move the G vehicle to the right" << endl
         << "2 squares.  Lower-case input such as   gr2  is also   " << endl
         << "accepted.  Enter '-' to reset board, or 'x' to exit.  " << endl;
}//end displayInstructions()

//-------------------------------------------------------------------------------
//function to get piece at certain location


//--------------------------------------------------------------
//Function to find car
void findCar(char car, char board[6][6], int &rowLocation, int &columnLocation)
	{
		for (int r = 0; r < 6; r++)
			{
				for (int c = 0; c < 6; c++)
				{
					if (car == board[r][c])
						{
							rowLocation = r;
							columnLocation = c; 
							return;
						}
				}

			}
			return;
		
			
	}//end FindCar()

//function to find which Allignment cars are (vertical or Horizontal)
char allignmentTest(char car, char board[6][6], int rowLocation, int columnLocation)
	{
		if (board[rowLocation][columnLocation+1]==car)
			{
				return 'H'; //Indicates car allignment is Horizontal
			}
		else if (board[rowLocation+1][columnLocation]==car)
			{
				return 'V'; //Indicates car allignment is Vertical
			}
		else
			{
				return 'N'; //Indicates error in Car alligment
			}

	}

//--------------------------------------------------------
//Function to attain length of each car

int lengthOfCar(char car, char board[6][6], int rowLocation, int columnLocation)
	{
		int numOfCarts = 1;
		int i=1;
		if(allignmentTest(car,board,rowLocation,columnLocation)=='H')
			{
				while(board[rowLocation][columnLocation+i]==car)
					{
						i++;
						numOfCarts++;
					}
			}
		else if(allignmentTest(car,board,rowLocation,columnLocation)=='V')
			{
				while(board[rowLocation+i][columnLocation]==car)
					{
						i++;
						numOfCarts++;
					}
			}
		else
			{
				return -1;
			}
		return numOfCarts;

	}//end LengthofCar()

//---------------------------------------------------------------
//function to have user reset board
/*void resetBoard()
	{
		cout << "You have chosen to reset the board." << endl << "Enter 36 character for the new board:" << endl;
		cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
		cin >> p7 >> p8 >> p9 >> p10 >> p11 >> p12;
		cin >> p13 >> p14 >> p15 >> p16 >> p17 >> p18;
		cin >> p19 >> p20 >> p21 >> p22 >> p23 >> p24;
		cin >> p25 >> p26 >> p27 >> p28 >> p29 >> p30;
		cin >> p31 >> p32 >> p33 >> p34 >> p35 >> p36;
		return;
	}*/
//--------------------------------------------------------------------
// Display the board, using the current values in the global variables.
void inputBoard(char board[6][6], char car, char direction, int xcordinate, int ycordinate, int length)
{
   for(int i=0;i < length; i++)
   {
       if(direction == 'H')
       {
           board[xcordinate][ycordinate+i]=car;
       }
       if(direction == 'V')
       {
           board[xcordinate+i][ycordinate]=car;
       }
   }
}

void displayBoard(char board[6][6])
{
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
			{
				cout << board[r][c] << " ";
			}
		cout << endl;
	}
	
	// Your code should go here, to print out the values in all the
    // p1, p2, ... p36 variables.
    // ...

}//end displayBoard()



//--------------------------------------------------------------------
/*  Board and corresponding global variable values are:
           - - - - - - - -
         1 | G G . . . Y |
         7 | P . . B . Y |
        13 | P R R B . Y >
        19 | P . . B . . |
        25 | O . . . T T |
        31 | O . F F F . |
           - - - - - - - -
 */
// ----------------------------------------------------------------------------------
//Function to move car Right or Left

void MoveRL(char car, char direction, char board[6][6], int &rowLocation, int &columnLocation)
	{
		findCar(car, board, rowLocation, columnLocation); //variable to store location of car
		if (direction == 'R')
		{
			if ((board[rowLocation][columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)]!='.')||columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)>5)//|| (board[rowLocation][columnLocation]!=board[rowLocation][columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)]))) //user input check to make sure there is an open spot in location they wish to move
				{
					cout << endl << car << "*** Move was attempted, but couldn't be completed. ***'" << endl;
					return;
				}
			
			board[rowLocation][columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)]=car;
			board[rowLocation][columnLocation]='.';
		}
		else if(direction == 'L')
		{
		if ((board[rowLocation][columnLocation-1]!='.')||columnLocation-1<0) //user input check to make sure there is an open spot in location they wish to move
			{
				cout<< endl << car << " *** Move was attempted, but couldn't be completed. ***" << endl;;
				return;
			}
			board[rowLocation][columnLocation-1]=car;
			board[rowLocation][columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)-1]='.';
		}
	}//end moveRL
//------------------------------------------------------------------------------
//Function to move piece up or down TODO: REWRITE THE FUNCTION

void MoveUD(char car, char direction, char board[6][6], int &rowLocation, int &columnLocation)
	{
		findCar(car, board, rowLocation, columnLocation); //variable to store location of car
		//int lengthOfCar = LengthOfCar(car); //variable to store the length of the car
		if (direction == 'U') //direction up
		{
				if ((board[rowLocation-1][columnLocation]!='.')||rowLocation-1<0)//||columnLocation+lengthOfCar>5)//|| (board[rowLocation][columnLocation]!=board[rowLocation][columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)]))) //user input check to make sure there is an open spot in location they wish to move
				{
					cout << endl << car << "*** Move was attempted, but couldn't be completed. ***'" << endl;
					return;
				}
			
			board[rowLocation-1][columnLocation]=car;
			board[rowLocation+lengthOfCar(car, board, rowLocation, columnLocation)-1][columnLocation]='.';
		}
	if (direction == 'D') //direction up
		{
				if ((board[rowLocation + lengthOfCar(car, board, rowLocation, columnLocation)][columnLocation]!='.')||rowLocation+lengthOfCar(car, board, rowLocation, columnLocation)>5)//||columnLocation+lengthOfCar>5)//|| (board[rowLocation][columnLocation]!=board[rowLocation][columnLocation+lengthOfCar(car, board, rowLocation, columnLocation)]))) //user input check to make sure there is an open spot in location they wish to move
				{
					cout << endl << car << "*** Move was attempted, but couldn't be completed. ***'" << endl;
					return;
				}
			
			board[rowLocation][columnLocation]='.';
			board[rowLocation+lengthOfCar(car, board, rowLocation, columnLocation)][columnLocation]=car;
		}
}
int main()
{

	int rowLocation = 0;
	int columnLocation = 0;	
	char board[6][6];
	//Variables Declaration
    char car; //Describes which car to move
    char direction; //Decribes direction to move car
    int numSpots; //Describes how many spots to move vehicle

    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions

    // Set the board values
     board[0][0]='G'; board[0][1]='G'; board[0][2]='.'; board[0][3]='.'; board[0][4]='.'; board[0][5]='Y';
     board[1][0]='P'; board[1][1]='.'; board[1][2]='.';board[1][3]='B';board[1][4]='.';board[1][5]='Y';
    board[2][0]='P';board[2][1]='R';board[2][2]='R';board[2][3]='B';board[2][4]='.';board[2][5]='Y';
    board[3][0]='P';board[3][1]='.';board[3][2]='.';board[3][3]='B';board[3][4]='.';board[3][5]='.';
    board[4][0]='O';board[4][1]='.'; board[4][2]='.';board[4][3]='.';board[4][4]='T';board[4][5]='T';
    board[5][0]='O';board[5][1]='.';board[5][2]='F';board[5][3]='F';board[5][4]='F';board[5][5]='.';

   /* displayBoard(board);
    findCar('B',board,rowLocation,columnLocation);
    cout << endl << rowLocation << " " << columnLocation;
    cout << endl << allignmentTest('B',board,rowLocation,columnLocation);
    MoveRL('G', 'R', board, rowLocation, columnLocation);
    cout << endl;
    displayBoard(board);
    MoveRL('G','L',board, rowLocation, columnLocation);
    cout << endl;
    displayBoard(board);
    MoveUD('B','U',board,rowLocation,columnLocation);
    cout << endl;
    displayBoard(board);
    MoveUD('B','D',board,rowLocation,columnLocation);
    cout << endl;
    displayBoard(board);
    */
    displayBoard(board);
    cout << endl;
	int countMoves = 1; //variable to count the moves
 	while (board[2][5]!='R') //condition to check if the user won the game
 		{

			cout << countMoves << ". Your move -> ";
			cin >> car; //attains which car user wishes to move
			  if (car == '-') //condition to check if user wishes to reset the board
				{
					//resetBoard();
					displayBoard(board);
					cout << endl;
					continue;
				}
 			if (car == 'x') //condition to check if user wishes to end the game
 				{
 					break;
				}
 			cin >> direction; //gets direction user wishes to move
 			cin >> numSpots; //gets number of spots to move
 			car = toupper(car);
 			direction = toupper(direction);
 			if(direction ==  'R' || direction == 'L') //if user wants to move Right or Left
 				{
 					for(int i = 0; i < numSpots; i++) //loops number of spots to move
 						{
 							MoveRL(car,direction,board,rowLocation,columnLocation);
						}
 				}
 			else if(direction == 'U' || direction == 'D') //if user wants to move up or down
 				{
 					for(int i = 0; i <numSpots; i++) //loops number of spots to move
 						{
 							MoveUD(car,direction,board,rowLocation,columnLocation);
						}
				}
			displayBoard(board);
			countMoves++;
			cout << endl;

		}
 	if(board[2][5] =='R')
 		{
 			cout << "*** Congratulations, you did it! ***" << endl;
		}
    cout << endl;
    cout << "Thank you for playing.  Exiting..." << endl;

    return 0;
}//end main()
