#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


char end  = ' '; //finalizar o jogo;
int jogadas;
char posicao[3];

int posiX; //coordenada X para percorrer a matriz
int posiY;//coordenada Y para percorrer a matriz
    
int jogador;// 1 => X, 2 => O
    
char game[3][3]; // armazena os caracteres X e O




void clearScreen(); // limpla terminal

void initializeGame(); // inicializa a as variaveis globais;

void printGame(char game[][3]); // da um print do jogo atualizado

void finalizar(); //finaliza o jogo

char verificaVitoria(char game[3][3]);// verifica vitoria

void display();

int main(){
    
    char posicoes[][3] = {"00","01","02","10","11","12","20","21","22"};
    
    
    
    initializeGame();
    
    while(true){
        
        
        
        //solicita e garante que a posição correta seja escolhida pelo usuario;
        while (true)
        {
            clearScreen();
            printGame(game);
            display();
            bool sair = false;
             
            fgets(posicao, 3, stdin);  
            getchar();  

            
            // Verifica se todas as coordenadas são dígitos
            bool coordenadasNumericas = true;
            for (int i = 0; i < 2; i++)
            {
                if (isdigit(posicao[i]) == 0)
                {
                    coordenadasNumericas = false;
                    break;
                }
            }

            if (coordenadasNumericas == false)
            {
                printf("\n\t\t\t\tAs coordenadas devem ser numéricas!");
                getchar(); // Para evitar que a mensagem seja imediatamente sobrescrita
                continue;
            }


            bool posicaoExiste = false;
           

            for(int z = 0; z < 9; z++){
                if(strcmp(posicao,posicoes[z]) == 0){
                    posicaoExiste = true;

                    posiX = posicao[0] - '0';  
                    posiY = posicao[1] - '0'; 
                    break;
                }
            }

            

            if(posicaoExiste == false){
                printf("\n\t\t\t\tDigito Errado! Favor digitar posição correspondente ao diagrama");
            }else{
                if(game[posiX][posiY] != ' '){
                    printf("\n\t\t\t\tA posição já está preenchida! Favor digitar posição correspondente ao diagrama");
                }else{
                    
                    sair = true;
                }    
            }

            if(sair)break;

        }
    
        
        //computa a jogada e preenche o local correspondente ao que o usuário digitou
        if(jogador == 1){
            game[posiX][posiY] = 'X';
        
            jogadas++;
            jogador = 2;
        }else{
            game[posiX][posiY] = 'O';
        
            jogadas++;
            jogador = 1;
        }

        //verifica se houve vitória
        if(jogadas > 4){
            char vitoria = verificaVitoria(game);

            if(vitoria == 'X'){
                clearScreen();
                printf("\n\t\t\t\tParabéns Jogador 1");
                printf("\n\t\t\t\tGanhou com %d Jogadas",jogadas);
                printGame(game);
                
                finalizar();
                if(end != 'S' && end != 's'){
                    initializeGame();
                }else{
                    break;
                }
            }else if(vitoria == 'O'){
                printf("\n\t\t\t\tParabéns Jogador 2");
                printf("\n\t\t\t\tGanhou com %d Jogadas",jogadas);
                printGame(game);
                
                finalizar();
                if(end != 'S' && end != 's'){
                    initializeGame();
                }else{
                    break;
                }
                
                
            }
        }    
        
        if(jogadas == 9){
            clearScreen();
            printf("\n\t\t\t\t\t\tVelha!");
            printGame(game);
            finalizar();
            if(end != 'S' && end != 's'){
                initializeGame();
            }else{
                break;
            }
        }
        
    }

    
    return 0;
}

void display(){
    printf("\n\t\t\t\tDigite a posição (entre 00 e 22) de acordo com o diagrama:");
}

char verificaVitoria(char game[3][3]) {
    int i;
    
    // Verifica linhas
    for (i = 0; i < 3; i++) {
        if (game[i][0] == game[i][1] && game[i][0] == game[i][2] && game[i][0] != ' ') {
            return game[i][0];
        }
    }

    // Verifica colunas
    for (i = 0; i < 3; i++) {
        if (game[0][i] == game[1][i] && game[0][i] == game[2][i] && game[0][i] != ' ') {
            return game[0][i];
        }
    }

    // Verifica diagonais
    if (game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] != ' ') {
        return game[0][0];
    }
    if (game[0][2] == game[1][1] && game[0][2] == game[2][0] && game[0][2] != ' ') {
        return game[0][2];
    }

    // Retorna espaço vazio se não houver vencedor
    return ' ';
}



void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Comando para limpar o terminal no Windows
    #else
        system("clear"); // Comando para limpar o terminal no Linux e macOS
    #endif
}
void printGame(char game[][3]){
    int i = 0;
    
    printf("\n\t\t\t\t\t\tJogador 1 => X");
    printf("\n\t\t\t\t\t\tJogador 2 => O");
    printf("\n\t\t\t\t\t\t  0 1 2");
    printf("\n\t\t\t\t\t\t0 %c|%c|%c",game[0][0],game[0][1],game[0][2]);
    printf("\n\t\t\t\t\t\t  -----");
    printf("\n\t\t\t\t\t\t1 %c|%c|%c",game[1][0],game[1][1],game[1][2]);
    printf("\n\t\t\t\t\t\t  -----");
    printf("\n\t\t\t\t\t\t2 %c|%c|%c",game[2][0],game[2][1],game[2][2]);
    printf("\n\t\t\t\t\t\t  -----\n");
    

}

void initializeGame(){
    int j = 0, i = 0;
    for(i = 0; i<3;i++){
        for(j = 0; j<3; j++){
            game[i][j] = ' ';
        }
    }

    jogadas = 0;
    

    posiX = 0;  //coordenada X para percorrer a matriz
    posiY = 0;  //coordenada Y para percorrer a matriz
    
    jogador = 1;  // 1 => X, 2 => O
    
    

}

void finalizar(){
    printf("\n\t\t\t\t'S' ou 's' para reiniciar e qualquer tecla para finalizar:");
    scanf("%c",&end);
    getchar();
}