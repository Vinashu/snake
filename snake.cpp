#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <locale.h>
#define C 40		//Colunas na tela
#define L 20		//Linhas na tela
#define D 200000000	//Delay

//Definindo a estrutura da fila
struct no {
	int x;
	int y;
	struct no *proximo;
};

typedef no *ptrNo;
ptrNo fila;

//Cobra
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

//Prototipação
void filaInserir(ptrNo fila, int x, int y);
void filaRemover(ptrNo fila);
void filaMostrar(ptrNo fila);

//Jogo
void delay(void);
void clear(void);
void debug(int c);
void iniciaJogo(void);
void desenhaTela(void);
void lerTecla(void);
void moveSnake(void);

int main(void){
  	setlocale(LC_ALL, "Portuguese");    
	iniciaJogo();
	c = 0;
	tecla = ' ';
	while(tecla != 'x'){
		desenhaTela();
		debug(c++);
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

void debug(int c){
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
  	//Criando o primeiro nó da fila
  	fila = (ptrNo) malloc(sizeof(no));
  	fila->x = mySnake.posX;
  	fila->y = mySnake.posY;
  	fila->proximo = NULL;	
}

void desenhaTela(void){
	for (i=0;i<L;i++){
		for (j=0;j<C;j++){
			printf("%c",tela[i][j]);
		}
		printf("\n");		
	}			
	printf("Use os comandos awsd para movimentar a cobra, x para sair!\n");
	filaMostrar(fila);
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
	if (mySnake.speed !=0){
		tela[mySnake.posX][mySnake.posY]='@';        	
		filaInserir(fila,mySnake.posX,mySnake.posY);		
		filaRemover(fila);		
	}
}

//Insere um elemento no final da fila
void filaInserir(ptrNo fila, int x, int y){
  while(fila->proximo != NULL){
  	fila = fila->proximo;  
  }
  fila->proximo = (ptrNo) malloc(sizeof(no));    
  fila = fila->proximo; 
  fila->x = x;
  fila->y = y;
  fila->proximo = NULL;  
}

//Remove um elemento do início da fila
void filaRemover(ptrNo fila){
  ptrNo atual;	
  atual = (ptrNo) malloc(sizeof(no));  
  atual = fila;
  tela[atual->x][atual->y]='X';      
  if (fila->proximo != NULL){
    fila = fila->proximo;
    atual->proximo = fila->proximo;
  }
}

//Desenha o conteúdo da fila na tela
void filaMostrar(ptrNo fila){
  while(fila->proximo != NULL) {
    printf("[%d,%d]", fila->x,fila->y);   	
	fila = fila->proximo;    	
  } 
  printf("[%d,%d]\n", fila->x,fila->y);   	
}
