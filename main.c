	#include <stdio.h>
	#include <math.h>
	#include <windows.h>
	#include <conio.h>
	#include "conio_functions.h" /*substitution of conio.c*/
	#include <stdlib.h>
	#include <locale.h>
	#include <time.h>
	
	#define downArrow 80
	#define upArrow 72
	#define leftArrow 37
	
	#define esc 27
	#define enter 13
	#define f1 59
	
	#define screenColumns 90
	#define horizontalCenter 45
	#define screenRows 40
	#define verticalCenter 20
	
	#define maxSize 10
	
	//function headers 
	int menuSelection(int, int);
	int reprocessing();
	int mainMenu(int matrix[maxSize][maxSize]);
	int isSquare();
	int selectRow(int matrix[maxSize][maxSize]);
	int selectColumn(int matrix[maxSize][maxSize]);
	void printHeader();
	void fillMatrix(int matrix[maxSize][maxSize]);
	void readMatrix(int matrix[maxSize][maxSize]);
	void generateMatrix(int matrix[maxSize][maxSize]);
	void showMatrix(int matrix[maxSize][maxSize]);
	void menuExecute(int matrix[maxSize][maxSize], int);
	void swapRows(int matrix[maxSize][maxSize], int, int);
	void swapColumns(int matrix[maxSize][maxSize], int, int);
	
	//global variables
	int rows, columns;
	
	int main() {
		system("mode con:cols=90 lines=40");
		SetConsoleTitle("Calculadora Trigonometrica");
		setlocale(LC_CTYPE, "Portuguese"); 
		srand(time(NULL));
		cursor(1);
	    
	    int matrix[maxSize][maxSize];
		int out = 0, choice = 0;
	
		do{
		    printHeader();
		    
		    do{
		    	gotoxy(1,5); printf("Número de colunas da matriz:");
		    	gotoxy(30,5); scanf(" %d", &columns);
		    	if(columns <= 0 || columns > maxSize){
		    		gotoxy(1,3);
		    		textcolor(4);
		    		printf("O número de colunas deve ser maior que 0 e menor que 10");
		    		textcolor(0);
		    		gotoxy(30,5);printf("     ");
				}
			}while(columns <= 0 || columns > maxSize);
			gotoxy(1,3);printf("                                                                        ");
			do{
		    	gotoxy(1,6); printf("Número de linhas da Matriz:");
		    	gotoxy(30,6); scanf(" %d", &rows);
		    	if(rows <= 0 || rows > maxSize){
		    		gotoxy(1,3);
		    		textcolor(4);
		    		printf("O número de linhas deve ser maior que 1 e menor que 10");
					textcolor(0);
					gotoxy(30,6);printf("     ");
				}
			}while(rows <= 0 || rows > maxSize);
		    gotoxy(1,3);printf("                                                                        ");
		    
		    fillMatrix(matrix);
		    
		    do{
		    	choice = mainMenu(matrix);
		    	menuExecute(matrix, choice);
			}while(choice >= 0);
		    
			out = reprocessing();	
		}while(out != 2); 
	
	    return 0;
	}
	
	void printHeader(){
		textbackground(15);
		textcolor(0);
		
	    system("cls");
	    int i;
	    for(i=0;i<screenColumns;i++){
		    gotoxy(i,1);
	    	textbackground(14);printf(" ");
	    }
	    
	    gotoxy(horizontalCenter - 13,1); printf("MATRIZES EM C");
	    textbackground(15);
	}
	
	void swapRows(int matrix[maxSize][maxSize], int row1, int row2){
		int i, x, y, aux;
		for(i=0;i<columns;i++){
			x = matrix[row1][i];
			y = matrix[row2][i];
			matrix[row2][i] = x;
			matrix[row1][i] = y;
		}
	}
	
	void menuExecute(int matrix[maxSize][maxSize], int choice){
		int x, y;
		switch(choice){
			case 1:
				x = selectRow(matrix);
				break;
			case 2:
				x = selectColumn(matrix);
				break;
		}	
	}
	
	void showMatrix(int matrix[maxSize][maxSize]){
		printHeader();
		int i, j, x, y;
		gotoxy(1, 3); printf("Matriz obtida: ");
		for(i=0, y=5;i<rows;i++){
			for(j=0,x=horizontalCenter-columns;j<columns;j++){
				gotoxy(x,y);
				printf("%d", matrix[i][j]);
				x+=2;
			}
			y+=2;
		}
	}
	
	int selectRow(int matrix[maxSize][maxSize]){
		showMatrix(matrix);
		int x1=horizontalCenter-columns-2, x2=horizontalCenter+columns;
		int aux = 5, choice = 0, count = 0; char Cursor;
		
		textcolor(4);
		gotoxy(x1, aux);printf(">");
		gotoxy(x2, aux);printf("<");
		textcolor(0);
		
		cursor(0);
		while (!choice) {
	        Cursor = getch();
	        gotoxy(x1,aux); printf("  ");
	        gotoxy(x2,aux); printf("  ");
	        
	        switch(Cursor){
	        	case upArrow:
	        		if(aux == 5) {
	        			aux = 3+rows*2;
						count = rows-1;		
					}
	                else {
	                	aux -=2;
	                	count--;
					}
	                break;
	            case downArrow:
	            	if(aux == 3+rows*2) {
	            		aux = 5;
	            		count = 0;
					}
	                else {
	                	aux+=2;	
	                	count++;
					}
	                break;
	            case enter:
	            	choice = count;
	            	break;
			}
	        
	        textcolor(4);
			gotoxy(x1, aux);printf(">");
			gotoxy(x2, aux);printf("<");
			textcolor(0);
	    }
	    cursor(1);
	    return choice;
	}
	
	int selectColumn(int matrix[maxSize][maxSize]){
		showMatrix(matrix);
		int y1=5, y2=3+columns*2;
		int aux = 5, choice = 0, count = 0; char Cursor;
		
		textcolor(4);
		gotoxy(horizontalCenter-columns, aux-1);printf("v");
		gotoxy(horizontalCenter-columns, aux+rows*2-1);printf("^");
		textcolor(0);
		
		cursor(0);
		while (!choice) {
	        Cursor = getch();
	        textcolor(4);
			gotoxy(horizontalCenter-columns, aux-1);printf("v");
			gotoxy(horizontalCenter-columns, aux+rows*2-1);printf("^");
			textcolor(0);
	        
	        switch(Cursor){
	        	case upArrow:
	        		if(aux == 5) {
	        			aux = 3+columns*2;
						count = columns-1;		
					}
	                else {
	                	aux -=2;
	                	count--;
					}
	                break;
	            case downArrow:
	            	if(aux == 3+columns*2) {
	            		aux = 5;
	            		count = 0;
					}
	                else {
	                	aux+=2;	
	                	count++;
					}
	                break;
	            case enter:
	            	choice = count;
	            	break;
			}
	        
	        textcolor(4);
			gotoxy(horizontalCenter-columns, aux-1);printf("v");
			gotoxy(horizontalCenter-columns, aux+rows*2-1);printf("^");
			textcolor(0);
	    }
	    cursor(1);
	}
	
	void readMatrix(int matrix[maxSize][maxSize]){
		printHeader();
		gotoxy(1,3); printf("Digite a Matriz:");
		int i, j;
		int x=horizontalCenter-columns, y=5; //gotoxy
		
		int digits = 0, num, lastDigit = 0;
		for(i=0, y=5;i<rows;i++){
			for(j=0,x=horizontalCenter-columns;j<columns;j++){
				gotoxy(x,y);
				scanf(" %d", &matrix[i][j]);
				num = matrix[i][j];
	//			while(num > 1) {
	//				num = num / 10;
	//				digits++;
	//			}
				x+=2;
			}
			
			y+=2;
		}
	}
	
	void generateMatrix(int matrix[maxSize][maxSize]){
		int i, j;
		for(i=0;i<rows;i++)
			for(j=0;j<columns;j++)
				matrix[i][j]=rand()%10;
	}
	
	void fillMatrix(int matrix[maxSize][maxSize]){
		printHeader();
		gotoxy(3,3);printf("Modo de preenchimento da matriz: ");
		gotoxy(3,5);printf("Entrada pelo teclado");
	    gotoxy(3,6);printf("Gerada aleatoriamente");
	    switch(menuSelection(5,6)){
	    	case 1:
	    		readMatrix(matrix);
	    		break;
	    	case 2:
	    		generateMatrix(matrix);
	    		break;
		}
	}
	
	int menuSelection(int rowMin, int rowMax){
		cursor(0); textcolor(0);
	    int choice = 0;
	    int aux = rowMin;
	    char Cursor;
	
	    gotoxy(0,aux); printf(" >");
	    while (!choice) {
	        Cursor = getch();
	        gotoxy(0,aux); printf("  ");
	        
	        switch(Cursor){
	        	case upArrow:
	        		if(aux == rowMin) aux = rowMax;
	                    else aux --;
	                    break;
	            case downArrow:
	            	if(aux == rowMax) aux = rowMin;
	                    else aux++;
	                    break;
	            case enter:
	            	choice = aux-rowMin+1;
	            	break;
	            case esc:
	            	choice = -1;
	            	break;
			}
	        
	        gotoxy(0,aux); printf(" >");
	    }
	    
	    cursor(1);
	    return choice;
	}
	
	int isSquare(){
		if(columns == rows)return 1; //yes, is square
		else return 0; //no, isn't square
	}
	
	int mainMenu(int matrix[maxSize][maxSize]){
		printHeader();
		showMatrix(matrix);
		int x = 5 + rows * 2; int y;
		gotoxy(3,++x); printf("Selecione a operação a ser realizada com a matriz (pressione ESC para sair): ");
	    gotoxy(3,++x); printf("Trocar linhas");
	    gotoxy(3,++x); printf("Trocar colunas");
	    gotoxy(3,++x); printf("Verificar se é simétrica");
	    y = x; 
		if(!isSquare())textcolor(8); 
	    gotoxy(3,++x); printf("Trocar diagonais");
	    gotoxy(3,++x); printf("Verificar se é quadrado mágico");
	    gotoxy(3,++x); printf("Verificar se é quadrado latino");
	    gotoxy(3,++x); printf("Verificar se é matriz de permutação");
	    
	    if(!isSquare())
			return menuSelection(rows*2+7, y);
		else 
			return menuSelection(rows*2+7, x);
	}
	
	int reprocessing(){
		printHeader();
		gotoxy(3,3);printf("Deseja recomeçar?");
		gotoxy(3,5);printf("Sim");
	    gotoxy(3,6);printf("Não");
	    return menuSelection(5,6);
	}
