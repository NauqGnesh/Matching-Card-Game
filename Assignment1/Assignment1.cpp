/*	Teoh Ryan Quan Sheng 
	04/OCT/2019
	This program is a simple memory game 
	which asks the user to match pairs of identical cards 
	from a pile of randomized cards
*/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>

// constants 
const int LENGTH = 4;  
using namespace std;

// Function prototypes
void InitializeCards(int cards[][LENGTH]);
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]);
void RevealCards(int cards[][LENGTH], bool faceup [][LENGTH], int, int, int, int);
void SaveFile (string, int, char);

// ======================
//     main function
// ======================
int main()
{	
	// variables 
	string Username ;     
	int x1 , y1 , x2 , y2 ;
	int attempts = 0 ; 
	char again = ' ';
	int winCondition = 0 ; 

	//Welcome the user and ask him to enter his full name
	cout << "Welcome to my game!" << endl ; 
	cout << "Please enter your full name: " ; 
	getline (cin , Username); 
	cout << "Find all the matching pairs on the board!" << endl; 

	//2D array that will hold the number for each card
	int deck[LENGTH][LENGTH];
	//Passing it to InitializeCards function
	InitializeCards(deck);

	//2D array of Booleans that represents whether or not the card is matched
	//All elemements initialized to FALSE representing facedown  
	bool matched[LENGTH][LENGTH] = {0} ; 

	//While the game is not over
	//Displays the current state of the game board
	//Non-matched pairs are "facedown" (*)
	//Matched pairs are "faceup" (number)
	while (again != 'q')
	{
		ShowCards(deck , matched); 

		// Prompt the user to enter the coordinates of two cards
		do 
        {
            cout << "Enter x and y position of the first card: " ;
		    cin >> x1 >> y1 ; 

            if (x1 <0 || x1 >3)
            {
                cout << "Your x-coordinate is invalid. Enter a coordinate from 0-3" << endl ;
            }

            if (y1 <0 || y1 >3)
            {
                cout << "Your y-coordinate is invalid. Enter a coordinate from 0-3" << endl ; 
            }

        }while ( x1<0 || x1>3 || y1<0 || y1>3 );
		
        do 
        {
            cout << "Enter x and y position of the second card: " ;
		    cin >> x2 >> y2 ; 

            if (x2 <0 || x2 >3)
            {
                cout << "Your x-coordinate is invalid. Enter a coordinate from 0-3" << endl ;
            }

            if (y2 <0 || y2 >3)
            {
                cout << "Your y-coordinate is invalid. Enter a coordinate from 0-3" << endl ; 
            }

			if (x2==x1 && y2 == y1 )
			{
				cout << "Pick a different card" << endl ; 
			}

        }while ( x2<0 || x2>3 || y2<0 || y2>3 || (x2==x1 && y2 == y1) );

		//Temporarily reveal cards 
		RevealCards(deck, matched, x1, y1, x2, y2); 

		//If matched 
		if( deck[x1][y1] == deck[x2][y2] )
		{
			matched[x1][y1] = 1;
			matched[x2][y2] = 1;
			cout << "You found a match!" << endl; 
		}

		// If not matched 
		else 
		{
			cout << "No match..." << endl ; 
			cout << "Flipping cards over again" << endl ;
		}

		//update number of attempts made
		attempts++; 

		//Counting number of faceup cards
		for(int i = 0 ; i < 4 ; i++ )      
        {
            for (int j = 0 ; j < 4 ; j++)
            {
				if (matched[i][j]== 1)
				{ 
					winCondition ++;
				}

            }
        }

		//win condition 
        if(winCondition == 16)  
        {
            cout << "Congratulations, you found all the card!" << endl ; 
            ShowCards(deck , matched);
            cout << "Number of attempts: " << attempts << endl ; 
            again = 'q' ;
        }
		
		//win condition not met 
        else 
        {
            winCondition = 0 ; 
		    cout << "Enter 'q' to quit or press any key to continue..." << endl ; 
		    cin.ignore(); //clear the keyboard buffer
			if (cin.get() == 'q') // allow user to go again or quit 
				again = 'q';	
        }

		//clear the keyboard buffer to prevent invalid input in the next loop
		cin.ignore(); 
	}
	
	//Save the user’s name and number of attempts into an output text file
	SaveFile(Username, attempts, again);
	return 0; 
}

// ===================================================
// InitializeCards
// Places pairs of numbers in the 2D array and then
// randomly shuffles them.
// revieves a 2-D array of int and returns nothing 
// ===================================================
void InitializeCards(int cards[][LENGTH]) 
{
	srand(time(NULL)); 
	int x1, y1, x2, y2;
	int i;
	int temp;

	// Place pairs in known locations -   this is how our array looks like after
	cards[0][0] = 1; cards[0][1] = 1;//   1  1  2  2
	cards[0][2] = 2; cards[0][3] = 2;
	cards[1][0] = 3; cards[1][1] = 3;//   3  3  4  4
	cards[1][2] = 4; cards[1][3] = 4;
	cards[2][0] = 5; cards[2][1] = 5;//   5  5  6  6
	cards[2][2] = 6; cards[2][3] = 6;
	cards[3][0] = 7; cards[3][1] = 7;//   7  7  8  8
	cards[3][2] = 8; cards[3][3] = 8;

	//Shuffle 
	for (int i = 0; i < 30; i++) {
		
		y1 = rand() % LENGTH; //Get set of random coordinates and swap
		x1 = rand() % LENGTH; //First random coordinate on our 2d "grid"
		//Sec our 2d "grid"
		y2 = rand() % LENGTH;
		x2 = rand() % LENGTH;

		//Swap value at (x1, y1) with value at(x2, y2)
		temp = cards[x1][y1];
		cards[x1][y1] = cards[x2][y2];
		cards[x2][y2] = temp;
	}
}

// ===============================================================
// ShowCards
// Generates a display on the screen.  If faceup=false,
// an * is output, otherwise the card in that slot is output.
// recieves a 2-D array of ints and a 2-D array of bools 
// returns nothing 
// ===============================================================
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]) 
{
	cout << "  0 1 2 3 " << endl ; 
	cout << "============" << endl ; 
	for ( int i = 0 ; i < LENGTH ; i++)
	{
		cout << i <<"|" ;
		for ( int j = 0 ; j < LENGTH ; j++)
		{
			if (faceup[i][j] == 1 )          // if faceup is true or >=1 
				cout << cards[i][j] << " " ; 
			else                             // if faceup is false or 0 
				cout << "*" << " " ;               
			
		}
		cout << "|"<< endl ; 
	}
	cout << "============" << endl ;
}

// =======================================================================
// RevealCards
// Displays Cards temporarily that was chosen by the user 
// Also displays cards that have already been matched previously
// Recieves a 2-D array of ints and a 2-D array of bools 
// Recieves 4 int variables
// returns nothing 
// =========================================================================
void RevealCards(int cards[][LENGTH], bool faceup[][LENGTH], int x1, int y1, int x2, int y2)
{
	cout << "  0 1 2 3 " << endl ; 
	cout << "============" << endl ; 
	for ( int i = 0 ; i < LENGTH ; i++)
	{
		cout << i <<"|" ;
		for ( int j = 0 ; j < LENGTH ; j++)
		{
			if (faceup [i][j] == 1)
			{
				cout << cards[i][j] << " ";
			}

			else if (i == x1 && j == y1 )          // if faceup is true or >=1 
				cout << cards[x1][y1] << " " ; 

			else if (i == x2 && j == y2 )
			{
				cout << cards[x2][y2] << " " ;
			}

			else if(faceup [i][j] == 0)        // if faceup is false or 0 
				cout << "*" << " " ;               	
		}
		cout << "|"<< endl ; 
	}
	cout << "============" << endl ;
}

// =======================================================================
// SaveFile 
// Saves the username and number of attempts to Save.txt file
// Recieves a string and int variable
// Returns nothing 
// =========================================================================
void SaveFile(string name, int attempts, char status)
    {
        ofstream outfile ; 
        outfile.open ("Save.txt");
        if(!outfile)
        {
            cerr << "File open failure!" << endl ;
            exit(1);
        }
    
		if(status == 'q')
			outfile << "Don't give up!" << endl ; 

		else
		{
			outfile << "Username: "<< name << endl;
        	outfile << "Number of attempts: " << attempts << endl;
		}
		
		
    }



/* 
Test Results :

Welcome to my game!
Please enter your full name: Ryan Teoh
Find all the matching pairs on the board!
  0 1 2 3
============
0|* * * * |
1|* * * * |
2|* * * * |
3|* * * * |
============
Enter x and y position of the first card: 4 4             //INVALID INPUT***
Your x-coordinate is invalid. Enter a coordinate from 0-3
Your y-coordinate is invalid. Enter a coordinate from 0-3
Enter x and y position of the first card: 0 0
Enter x and y position of the second card: 0 1
  0 1 2 3
============
0|2 1 * * |
1|* * * * |
2|* * * * |
3|* * * * |
============
No match...
Flipping cards over again
Enter 'q' to quit or press any key to continue...

  0 1 2 3
============
0|* * * * |
1|* * * * |
2|* * * * |
3|* * * * |
============
Enter x and y position of the first card: 0 0            //VALID INPUT 1***
Enter x and y position of the second card: 0 2
  0 1 2 3
============
0|2 * 3 * |
1|* * * * |
2|* * * * |
3|* * * * |
============
No match...
Flipping cards over again
Enter 'q' to quit or press any key to continue...

  0 1 2 3
============
0|* * * * |
1|* * * * |
2|* * * * |
3|* * * * |
============
Enter x and y position of the first card: 0 0             //VALID INPUT 2***
Enter x and y position of the second card: 0 3
  0 1 2 3
============
0|2 * * 7 |
1|* * * * |
2|* * * * |
3|* * * * |
============
No match...
Flipping cards over again
Enter 'q' to quit or press any key to continue...

  0 1 2 3
============
0|* * * * |
1|* * * * |
2|* * * * |
3|* * * * |
============
Enter x and y position of the first card: 0 0          //VALID INPUT 3***
Enter x and y position of the second card: 1 0
  0 1 2 3
============
0|2 * * * |
1|4 * * * |
2|* * * * |
3|* * * * |
============
No match...
Flipping cards over again
Enter 'q' to quit or press any key to continue...       
q                                                       //QUIT***
Don't give up
*/