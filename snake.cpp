#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#define C 40		//Colunas na tela
#define L 20		//Linhas na tela
#define D 200000000	//delay

char tela[L][C];
char tecla;
int i,j;
long int c,k;

struct snake{
	int posX;
	int posY;
	int size;
	int speed;
};

snake mySnake;

void delay(void);
void clear(void);
void debug(void);
void iniciaJogo(void);
void desenhaTela(void);
void lerTecla(void);
void moveSnake(void);

int main(void){
	iniciaJogo();
	c = 0;
	tecla = ' ';
	while(tecla != 'x'){
		desenhaTela();
		c++;
		debug();
		delay();
		lerTecla();	
		moveSnake();					
		clear();
	}
	return(0);	
}

void delay(void){
	for (k=0; k< D;k++);	
}	

void clear(void){
	system("cls");	
}

void debug(void){
	printf("%d",c);					
}

void iniciaJogo(void){
	for (i=0;i<L;i++){
		for (j=0;j<C;j++){
			tela[i][j] = ' ';
		}
	}	
	for (i=0;i<C;i++){
		tela[0][i] = '#';
		tela[L-1][i] = '#';		
	}
	for (i=0;i<L;i++){
		tela[i][0] = '#';
		tela[i][C-1]= '#';
	}	
	tela[L/2][C/2]='@';
	mySnake.posX = L/2;
	mySnake.posY = C/2;
	mySnake.speed = 0;
}

void desenhaTela(void){
	for (i=0;i<L;i++){
		for (j=0;j<C;j++){
			printf("%c",tela[i][j]);
		}
		printf("\n");		
	}			
	printf("Use os comandos awsd para movimentar a cobra, x para sair!\n");
}

void lerTecla(void){
    if(kbhit()){
        tecla = getch();
        switch (tecla){
 			case 'd':
 				mySnake.speed = 1;
			break;       	
 			case 'a':
 				mySnake.speed = 2; 				
 				mySnake.posY--;
			break;       	
 			case 'w':
 				mySnake.speed = 3; 				
 				mySnake.posX--;
			break;       				
 			case 's':
 				mySnake.speed = 4; 				
 				mySnake.posX++;
			break;       							
        }
    }
}

void moveSnake(void){
    switch (mySnake.speed){	
    	case 1:
 			mySnake.posY++;    		
    	break;
		case 2:
			mySnake.posY--;
		break;       	
		case 3:
			mySnake.posX--;
		break;       				
		case 4:
			mySnake.posX++;
		break;       							  	
	}
	tela[mySnake.posX][mySnake.posY]='@';        	
}
