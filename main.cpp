#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Board frame
void printHorizontal(int size, int r, int l, int w, int k){ //Print horizontal line
	for(int i = 0; i < size; i++){
		if (i == w && (r == l || r == l + 1)){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout << " -------";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
		}
		else cout << " -------";
	}
	cout << "\n";
}

void printVertical(int size, int r, int l, int w, int k){ //Print vertical line
	for(int i = 0; i < size; i++){
		if (r == l && (i == w || i == w - 1)){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout << "       |";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
		}
		else cout << "       |";
	}
	cout << "\n";
}

//Print board
void printBoard(int size, int cursor, int board[][7], char player[][7], int k){
	double len_name;
	int y;
	int len = cursor / size, wid = cursor % size;
	int i;
	for(i = 0; i < size; i++){
		
		printHorizontal(size, i, len, wid, k);
		
		if (i == len && wid == 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout<< "|";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
		}	
		else cout<< "|";
		
		printVertical(size, i, len, wid, k);
		
		if (i == len && wid == 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout<< "|";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
		}	
		else cout<< "|";
		
		for (int j = 0; j < size; j++){
			
			if (board[i][j] != 0){
				len_name = strlen(player[board[i][j] - 1]);
				y = (7 - len_name)/2;
				for (int r = 0; r < y; r++ )
					cout<< " ";
				cout<< player[board[i][j] - 1];
				for (int r = 0; r < y; r++ )
					cout<< " ";
				if (i == len && (j == wid || j == wid - 1)){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << "|";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
				}
				else cout << "|";	
			}
			else {
				if (i == len && (j == wid || j == wid - 1)){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << "       |";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
				}
				else cout << "       |";
			}
		}
		cout<< "\n";
		
		if (i == len && wid == 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout<< "|";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
		}	
		else cout<< "|";
		
		printVertical(size, i, len, wid, k);
	}
	printHorizontal(size, i, len, wid, k);
}

//Winning conditions
bool equals3(int a, int b, int c) {
  return a == b && b == c && a != 0;
}

char checkWinner3(int size, int board[][7]) {

  	// horizontal
  	for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++){
    		if (equals3(board[j][i], board[j][i+1], board[j][i+2]))
      			return 'w';
      	}
  	}

  	// Vertical
  	for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++){
    		if (equals3(board[i][j], board[i+1][j], board[i+2][j]))
      			return 'w';
      	}
  	}

  	// Diagonal
  	for (int i = 0; i < size; i++){
  		for (int j = 0; j < size; j++){
  			if (i == j){
  				if (equals3(board[i][j], board[i + 1][j + 1], board[i + 2][j + 2]))
    				return 'w';
    		}
    	}
  	}
  	
  	for (int i = 0; i < size; i++){
  		for (int j = size - 1; j >= 0; j--){
  			if (i + j ==  size - 1){
  				if (equals3(board[i][j], board[i + 1][j - 1], board[i + 2][j - 2]))
    				return 'w';
  			}
		}
  	}

  	int openSpots = 0;
  	for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size; j++) {
      		if (board[i][j] == 0) {
        	openSpots++;
      		}
    	}
  	}

  	if (openSpots == 0)
    	return 't';
	else 
    	return 'n';
}

bool equals5(int a, int b, int c, int d, int e) {
  return a == b && b == c && c == d && d == e && a != 0;
}

char checkWinner5(int size, int board[][7]) {

  	// horizontal
  	for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++){
    		if (equals5(board[j][i], board[j][i+1], board[j][i+2], board[j][i+3], board[j][i+4]) )
      			return 'w';
      	}
  	}

  	// Vertical
  	for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++){
    		if (equals5(board[i][j], board[i+1][j], board[i+2][j], board[i+3][j], board[i+4][j]))
      			return 'w';
      	}
  	}

  	// Diagonal
  	for (int i = 0; i < size; i++){
  		for (int j = 0; j < size; j++){
  			if (i == j){
  				if (equals5(board[i][j], board[i + 1][j + 1], board[i + 2][j + 2], board[i + 3][j + 3], board[i + 4][j + 4]))
    				return 'w';
    		}
    	}
  	}
  	
  	for (int i = 0; i < size; i++){
  		for (int j = size - 1; j >= 0; j--){
  			if (i + j ==  size - 1){
  				if (equals5(board[i][j], board[i + 1][j - 1], board[i + 2][j - 2], board[i + 3][j - 3], board[i + 4][j - 4]))
    				return 'w';
  			}
		}
  	}

  	int openSpots = 0;
  	for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size; j++) {
      		if (board[i][j] == 0) {
        	openSpots++;
      		}
    	}
  	}

  	if (openSpots == 0)
    	return 't';
	else 
    	return 'n';
}

bool equals7(int a, int b, int c, int d, int e, int f, int g) {
  return a == b && b == c && c == d && d == e && e == f && f == g && a != 0;
}

char checkWinner7(int size, int board[][7]) {

  	// horizontal
  	for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++){
    		if (equals7(board[j][i], board[j][i+1], board[j][i+2], board[j][i+3], board[j][i+4], board[j][i+5], board[j][i+6] ) )
      			return 'w';
      	}
  	}

  	// Vertical
  	for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++){
    		if (equals7(board[i][j], board[i+1][j], board[i+2][j], board[i+3][j], board[i+4][j], board[i+5][j], board[i+6][j]))
      			return 'w';
      	}
  	}

  	// Diagonal
  	for (int i = 0; i < size; i++){
  		for (int j = 0; j < size; j++){
  			if (i == j){
  				if (equals7(board[i][j], board[i + 1][j + 1], board[i + 2][j + 2], board[i + 3][j + 3], board[i + 4][j + 4], board[i + 5][j + 5], board[i + 6][j + 6]))
    				return 'w';
    		}
    	}
  	}
  	
  	for (int i = 0; i < size; i++){
  		for (int j = size - 1; j >= 0; j--){
  			if (i + j ==  size - 1){
  				if (equals7(board[i][j], board[i + 1][j - 1], board[i + 2][j - 2], board[i + 3][j - 3], board[i + 4][j - 4], board[i + 5][j - 5], board[i + 6][j - 6]))
    				return 'w';
  			}
		}
  	}

  	int openSpots = 0;
  	for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size; j++) {
      		if (board[i][j] == 0) {
        	openSpots++;
      		}
    	}
  	}

  	if (openSpots == 0)
    	return 't';
	else 
    	return 'n';
}

//Update
void setMove(int size, int cursor, int board[][7], char player[][7], int k, int win_match[2], char name[][7], int &tie){
	char c ;
	int mover;
	int last_moveX;
	int last_moveY;
	cursor = 0;
	char result; 
	if (size == 3) result = checkWinner3(size, board);
	if (size == 5) result = checkWinner5(size, board);
	if (size == 7) result = checkWinner7(size, board);
	for (mover = 0; result != 'w' && result != 't'; mover = (mover + 1) % 2){
		system("cls");
		SetConsoleTextAttribute(hConsole, k);
		printBoard(size, cursor, board, player, k);
		c = _getch();
		switch (c){
			case 72:{
				if(cursor >= size)
					cursor -= size;
				break;
			}
			case 80: {
				if (cursor <= size * (size - 1) - 1)
					cursor += size;
				break;
			}
			case 75:{
				if (cursor > 0)
					cursor -= 1;
				break;
			}
			case 77: {
				if (cursor < size * size - 1)
					cursor += 1;
				break;
			}
			case 13:{
				if (board[cursor / size][cursor % size] == 0)
					board[cursor / size][cursor % size] = mover + 1;
				else
					mover = (mover + 1) % 2;
				last_moveX = cursor / size;
				last_moveY = cursor % size;
				if (size == 3) result = checkWinner3(size, board);
				if (size == 5) result = checkWinner5(size, board);
				if (size == 7) result = checkWinner7(size, board);	
				break;
			}
			case 'z':{
				if (board[last_moveX][last_moveY] != (mover + 1) % 2 ){
					board[last_moveX][last_moveY] = 0;
					break;
				}
				else 
					mover = (mover + 1) % 2;
				break;
			}
		}
		if (size == 3) result = checkWinner3(size, board);
		if (size == 5) result = checkWinner5(size, board);
		if (size == 7) result = checkWinner7(size, board);	
	}
	system("cls");
	printBoard(size, cursor, board, player, k);
	if (result == 'w'){
	mover = (mover + 1) % 2;
	cout << name[mover] << " win! \n";
	win_match[mover]++;}
	if (result == 't'){
		cout << "Tie!\n";
		tie ++;
	}
}

//Input players' icon designs
void Icon(int &icon1, int &icon2, char player[][7], char icon[][7] ){
	cout<< "Choose player 1 icon: ";
	cin>> icon1;
	if (icon1 == 32) memcpy(player[0], "x" , 7);
	else if (icon1 == 33) memcpy(player[0], "o" , 7);
	else {
		while (icon1 < 1 || icon1 > 33){
			cout<< "Invalid number. Try again: ";
			cin>> icon1;
		}
		icon[0][0] = (char)icon1;
		icon[0][1] = '\0';
		memcpy(player[0], icon[0] , 7);
	}
	
	cout<< "Choose player 2 icon (this icon must be different from player 1 icon): ";
	cin>> icon2;
	if (icon2 == 32) memcpy(player[1],"x" , 7);
	else if (icon2 == 33) memcpy(player[1], "o" , 7);
	else {
		while ((icon2 < 1 || icon2 > 33) || icon2 == icon1){
			cout<< "Invalid number. Try again: ";
			cin>> icon2;
		}
		icon[1][0] = (char)icon2;
		icon[1][1] = '\0';
		memcpy(player[1], icon[1] , 7);
	}
}

int main(){
	
	int size;
	int cursor;
	int match = 0;
	int tie = 0;
	int k;
	int icon1, icon2;
	char replay = 'e';
	char name[2][7];
	char changecolor;
	char player[2][7];
	char icon[2][7];
	char changeicon;
	char symbol;
	char stop_music;
	
	int win_match[2];
	for (int i = 0; i < 2; i++)
		win_match[i] = 0;
	
	//Play sound
	PlaySound(TEXT("music2.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	cout<< "Enter 's' to turn off music and another keys to play music ";
	cin>> stop_music;
		if (stop_music == 's')
			PlaySound(NULL, 0, 0);
	//Source: https://www.youtube.com/watch?v=34d4iGHvm1g&ab_channel=Tajammal
	
	//Change game theme
  	for(k = 1; k < 255; k++)
  	{
    	SetConsoleTextAttribute(hConsole, k);
    	cout << k << " Choose me!" << endl;
  	}
  	SetConsoleTextAttribute(hConsole, 7);
  	cout<< "Do you want to change theme color of this game?\n";
	cout<< "Enter 'y' for Yes and another character for 'No': ";
	cin>> changecolor;
	if (changecolor == 'y'){
  		cout<< "Enter color number you want to apply: ";
  		cin>> k;
  		SetConsoleTextAttribute(hConsole, k);
	}
	else k = 15;
	system("cls");
	
	//Name of player 1
	cout<< "Name of player 1: ";
	cin>> name[0];
	
	//Name of player 2
	cout<< "Name of player 2: ";
	cin>> name[1];
	
	//Icons design players can choose
	cout<< "Player icons design:\n";
	for (int i = 1; i < 32; i++){
		if (i < 7 || i > 10 && i != 13 && i != 27){
			if (i == 28){
				symbol = i;
				cout<< "\t" << i << "  " << symbol << endl;
			}
			else {
				symbol = i;
				cout<< "\t" << i << " " << symbol << endl;
			}
		}
	}
	cout<< "\t" << "32 x" << endl;	
	cout<< "\t" << "33 o" << endl;	
	
	Icon(icon1, icon2, player, icon);
		
	do{ 
		//Ask players if they want to turn on music when replay
		if (replay != 'e'){
			cout<< "Enter 's' to turn off music\n";
			cout<< "Enter 'p' to play music if your music is being turned off\n";
			cout<< "Press another keys to remain everything....";
			cin>> stop_music;
			if (stop_music == 's')
				PlaySound(NULL, 0, 0);
			if (stop_music == 'p') PlaySound(TEXT("music2.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
		} 
		
		//Ask players if they want to change color when replay
		if (replay != 'e'){
			for(k = 1; k < 255; k++){
    			SetConsoleTextAttribute(hConsole, k);
    			cout << k << " Choose me!" << endl;
  			}
  			SetConsoleTextAttribute(hConsole, 7);
  			cout<< "Do you want to change theme color of this game?\n";
			cout<< "Enter 'y' for Yes and another character for 'No': ";
			cin>> changecolor;
			if (changecolor == 'y'){
  				cout<< "Enter color number you want to apply: ";
  				cin>> k;
  				SetConsoleTextAttribute(hConsole, k);
			}
			else k = 15;

			system("cls");
			
			//Ask players if they want to change their icons design
			cout<< "Player icons design:\n";
			for (int i = 1; i < 32; i++){
				if (i < 7 || i > 10 && i != 13 && i != 27){
					if (i == 28){
						symbol = i;
						cout<< "\t" << i << "  " << symbol << endl;
					}
					else {
						symbol = i;
						cout<< "\t" << i << " " << symbol << endl;
					}
				}
			}
			cout<< "\t" << "32 x" << endl;	
			cout<< "\t" << "33 o" << endl;
			cout<< "Do you want to change your icons design?\n";
			cout<< "Enter 'y' for Yes and another character for 'No': ";
			cin>> changeicon;
			if (changeicon == 'y'){
				Icon(icon1, icon2, player, icon);
			}
		}
		
		//Choose board size
		cout<< "Enter the size of your board\n";
		cout<< "Enter 3 for 3x3 board\n";
		cout<< "Enter 5 for 5x5 board\n";
		cout<< "Enter 7 for 7x7 board\n";
		cin>> size;
		while (size != 3 && size != 5 && size != 7){
			cout<< "Invalid board size. Enter again!\n";
			cout<< "Enter the size of your board\n";
			cin>> size;
		}
	
		int board[size][7];
		
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++)
				board[i][j] = 0;
		}
		match ++;
		setMove(size, cursor, board, player, k, win_match, name, tie);
		cout<< "Replay? Enter 'e' to exit and another keys to replay: ";
		cin>> replay;
	}
	while (replay != 'e');
	
	//Statistical outcomes
	cout<< "Number of matches: " << match << endl;
	cout << "Number of winning matches: \n";
	for (int x = 0; x < 2; x++)
		cout << name[x] << ": " << win_match[x] << endl;
	cout<< "Number of tie matches: " << tie << endl;
	
	return 0;
}
	
