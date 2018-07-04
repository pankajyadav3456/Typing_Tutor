#include<iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include<windows.h>
using namespace std;


int score = 0;  //your score.
int missedCounter = 0; //alphabets or number of digits missed.
int levelChoice = 0;  //selection of level.
int wrongKeyCounter = 0; //wrong key counter.
int speedChoice = 0;  //selection of speed.
char startingIntroString[] = "\n\n\t\t\t\tGame Developed by Pankaj Yadav & Amit Pandey  !!  ";
char startNewGameString[] = "\n\t\n\n\t\t\t\tStart New Game  \n\n\nSelect Game Level \n\n(1) Capital Alphabet Mode (A-Z)\n(2) Small Alphabet Mode(a-z)\n(3) Digits Mode (0-9)\n\nYour Choice is -------------->  ";
char selectLevelString[] = "\n\n\nSelect Speed Level\n\n(1) Speed Level One\n(2) Speed Level Two\nYour Choice is -------------->   ";
char authorString[] = "\n\n\t\t\t\tTyping Tutor\n\n\nThis Game is developed by Pankaj Yadav & Amit Pandey\nStudent of Army Institue of Technology ,Pune\n\n\n\n\n\n\nErrors and suggestions will be Appreciated . \n\n\n\n\t\tPress BackSpace to return to Main Menu\n\n\n\t\t\t\tESC to Exit \n\n\n\t\t";
char helpString[] = "\n\t\t\tTyping Tutor\n\n\nThis game helps to improve your typing speed and sharpens your brain. Game has  two modes for the players. First is Beginers mode which is for basic typing,  next one is expert mode which is designed to sharpen your skills at their best\n\nSpeed Level 1 : 1 second time Sleep\nSpeed Level 2 : 500 milisecond time Sleep\n\nGame consits of Capital Alphabets, Small Alphabets, and Numbers (0-9) which varies with different difficulty level\n\nThis game also consist of Score Card which displays your currant Score and also Consists of Missing Alphabets Counter displayed in the game.\n\n\t\t\tBackSpace to return to Main Menu.\n\n\t\t\t\tESC to Exit Game.\n\n\t\t ";
int choice= 0 ;  //for first selection
int t=100 ; //for time
int  SleepTime = 0; //time used for Sleep.
char missedNum[100]; //for numbers  missed.

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct node
{
    int data;
    int x;
    int y;
    node *next;
}*head,*l,*temp;

void InsertNode(int dat);
void deleteNode(int _x);
void author();
void startingScreen();
void levelSelection();
void gameBoard();
void helpScreen();
int  randX();
void printChar();
void capitalAlphabet();
void smallAlphabet();
void digits();
void gameLost();
int searchInLinkList(int data);
void keyPressed();
void winningScreen();
void gotoxy(int x, int y);


int main()
{
	 system("cls");
	 srand ( time(NULL) );
	 startingScreen();
	 getch();
}

void startingScreen()
{
	 choice = 0;
	 system("cls");
	 for (int i=0 ; startingIntroString[i]!='\0' ; i++)
	 {
	  	cout<<startingIntroString[i];
	  	Sleep(100);
	 }

	 Sleep(100);
	 cout<<"\n\n\n\n\t\t\tTyping Tutor Game\n\n\n(1) To Start Game\n(2) To Help\n(3) About Author\n(4) Exit Game\n\nEnter your option -------> ";
	 cin>>choice;

	 if(choice == 1)
	 {
	  	levelSelection();
	 }
	 if(choice == 2)
	 {
	  	helpScreen();
	 }
	 if(choice == 3)
	 {
	  	author();
	 }
	 else if (choice == 4)
	 {
	  	exit(0);
	 }
	 else
	 startingScreen();
}

void levelSelection()
{
	 system("cls");
	 for (int i=0 ; startNewGameString[i]!= '\0' ; i++)
	 {
		  cout<<startNewGameString[i];
		  Sleep(10);
	 }
	 cin>>levelChoice;

	 for (int j=0 ; selectLevelString[j]!='\0' ; j++)
	 {
		  cout<<selectLevelString[j];
		  Sleep(10);
	 }
	 cin>>speedChoice;

	 if (levelChoice>=1 && levelChoice<=3 && speedChoice>=1 && speedChoice<=2)
	 {
		  if (speedChoice == 1)
		  {
		   SleepTime = 1000;
		  }
		  else if (speedChoice == 2)
		  {
		   SleepTime = 500;
		  }
		  keyPressed();
	}
	else
	{
		levelSelection();
	}
}

void keyPressed()
{
	  int key=0;
	  do
	  {
	  		if(kbhit())
			{
	  			char k =getch();
	  			key = k;
	  			if(searchInLinkList(key) == 1)
				{
	   				score++;
	   				deleteNode(key);
	  			}
	 		 	else
				{
	 				 wrongKeyCounter++;
	  			}
	 		}

			if (levelChoice == 1)
			{
	  			capitalAlphabet();
	 		}
	 		else if(levelChoice == 2)
	 		{
	 			smallAlphabet();
			}
	 		else if(levelChoice == 3)
			{
	  			digits();
	 		}
	 		Sleep(SleepTime);
	   }while(key != 27 && missedCounter+wrongKeyCounter<10 && t>0);

	   if(missedCounter+wrongKeyCounter>=10)
	   {
	 	  gameLost();
	   }

	   if (t<=0)
	   {
	 		winningScreen();
	   }
}

int searchInLinkList(int data)
{
	 int search = 0;
	 l = head;
	 while(l)
	 {
	   	if(l->data == data)
		{
	    	search = 1;
	        return search;
	    }
	   l = l->next;
	 }
	 return search;
}

void deleteNode(int _x)
{
	node* temp=head;
	node* temp1=head;

	if(_x==head->data)
	{
		head=temp->next;
		delete temp;
		return;
	}
	while(temp->next->data!=_x )
	{
		temp=temp->next;
	}
    temp1=temp->next;
	temp->next=temp1->next;
	delete temp1;
}

void InsertNode(int data , int x , int y )
{
     l=head;
     if(head == NULL)
	 {
     	head = new node();
     	head->data = data;
     	head->x = x;
     	head->y = y;
  		head->next = NULL;
     }

     else
	 {
   		while(l->next!=NULL)
    	l=l->next;
    	temp = new node();
    	temp->data = data;
    	temp->x = x;
    	temp->y = y;
	    l->next = temp;
    	l = temp;

   	}
}


void capitalAlphabet()
{
	 int randNum = 0;
	 randNum = 65 + (rand() % (int)(90 - 65 + 1));
	 InsertNode(randNum,randX(),0);
	 printChar();
}

void smallAlphabet()
{
	int randNum = 0;
	 randNum = 97 + (rand() % (int)(122 - 97 + 1));
	 InsertNode(randNum,randX(),0);
	 printChar();
}

void digits()
{
	 int randNum = 0;
	 randNum = 48 + (rand() % (int)(57 - 48 + 1)); //random number formula between 48-57 for (0-9)
	 InsertNode(randNum,randX(),0);
	 printChar();
}

int randX()
{
	 int x = 0 ;
	 x = (rand()%80)+1;
	 return x;
}

void printChar()
{
	 system("cls");
	 l = head;
	 while(l->next)
	 {
	 	gotoxy(l->x,l->y++);
	    cout<<(char)l->data;
	    if(l->y<=20)
	      l =  l->next;
	    else
		{
	   		missedNum[missedCounter++] = l->data ;
	     	deleteNode(l->data);
	     	printChar();
	    }
	 }
	 gotoxy(l->x,l->y++);
	 cout<<(char)l->data<<"\n";
	 gotoxy(1,20);
	 cout<<"______________________________________________________________________________";
	 gotoxy(1,22);
	 cout<<"Score : "<<score;
	 gotoxy(27,22);
	 cout<<"Time Left : "<<t--;
	 gotoxy(60,22);
	 cout<<"Digits Missed : "<<missedCounter;
	 gotoxy(1,24);
	 cout<<"Characters Missed : ";
	 for (int i=0 ; i<missedCounter ; i++)
	 {
	  	cout<<missedNum[i];
	 }
	 gotoxy(60,24);
	 cout<<"Wrong Key Hits : "<<wrongKeyCounter;
}

void gameLost()
{
	 system("cls");

	 //Sleep(1000);
	 cout<<"\n\n\t\t\t\tSummary";
	 //Sleep(1000);
	 cout<<"\n\n\t\t\tYou Have Lost the Game";
	 //Sleep(1000);
	 cout<<"\n\n\t\t\tScore : "<<score;
	 //Sleep(1000);
	 cout<<"\n\n\t\t\tNumber of Wrong Keys Hit : "<<wrongKeyCounter;
	 //Sleep(1000);
	 cout<<"\n\n\t\t\tNumber of Character Missed : "<<missedCounter;
	 cout<<"\n\n\t\t\tCharacters Missed : ";

	 for (int i = 0; i<missedCounter ; i++)
	 {
	  	cout<<missedNum[i]<<" ";
	  	//Sleep(1000);
	 }

	 //Sleep(1000);
	 cout<<"\n\n\t\t\tBetter Luck Next Time";
	 //Sleep(1000);
	 cout<<"\n\n\tYou should try again to increase your score.";
	 //Sleep(1000);
	 exit(0);
}

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}

void winningScreen()
{
	 system("cls");
	 Sleep(1000);
	 cout<<"\n\t\t\t\tCongratulations :) ";
	 Sleep(1000);
	 cout<<"\n\n\t\t\tYou Have Won the Game !!!!";
	 Sleep(1000);
	 cout<<"\n\n\n\tNumber of Wrong key Hits : %d ",wrongKeyCounter;
	 Sleep(1000);
	 cout<<"\n\tNumber of Character Missed : %d ",missedCounter;
	 Sleep(1000);
	 cout<<"\n\n\tCharacters Missed : ";

	 for (int i = 0; i< missedCounter ; i++)
	 {
	  	cout<<missedNum[i]<<" ";
	  	Sleep(1000);
	 }

	 Sleep(1000);
	 cout<<"\n\n\n\tTry Again to Increase your Score.";
	 Sleep(1000);
	 cout<<"\n\n\n\t\t\tYou will be redirected to Exit after 2 Seconds.";
	 Sleep(3);
	 exit(0);
}

void helpScreen()
{
	 char k;
	 int key;
	 system("cls");
	 for (int i=0 ; helpString[i] ; i++)
	 {
		cout<<helpString[i];
	  	Sleep(25);
	 }

	 do
	 {
	 	k = getch();
	 	key = k;
	 	if(key == 8)
		{ //backspace key ascii
	 		startingScreen();
	 	}
	 }while(key!=27); //escape key ascii.

}

void author()
{
	 char k;
	 int key;
	 system("cls");
	 for (int i=0 ; authorString[i]!= '\0' ; i++)
	 {
	  	cout<<authorString[i];
	  	Sleep(50);
	 }
	 do
	 {
	 	k = getch();
	 	key = k;
	 	if(key == 8)
		{
	 		startingScreen();
	 	}
	 }while(key!=27); //escape key ascii.
}
