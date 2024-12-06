#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vlib.h"
//Biblioteca de criacao e gerenciamento de threads para Linux
#include <pthread.h>
#include <time.h>

//Biblioteca original de mapeamento da memoria do dispositivo DE1-SoC com Linux embutido
#include "map.c"

#include "nave_bola.c"
#include "nave_pinguim.c"

typedef struct {
    int reg;                //Numero do registrador, valores abaixo de 1 resultam no nao-desenho do sprite
    int spriteoffset;       //Offset do sprite
    int xoffset;            //Offset do sprite em relacao a posicao x do objeto do qual faz parte
    int yoffset;            //Offset do sprite em relacao a posicao y do objeto do qual faz parte
} Sprite;

typedef struct {
    int xoffset;            //Offset do poligono em relacao a posicao x do objeto do qual faz parte
    int yoffset;            //Offset do poligono em relacao a posicao y do objeto do qual faz parte
    int color;              //Numero da cor (0-511) do poligono
    int shape;              //Numero da forma do poligono
    int size;               //Numero do tamanho do poligono, valores abaixo de 1 resultam no nao-desenho do poligono
} Polygon;

typedef struct {
    int xpos;               //Posicao x do objeto
    int ypos;               //Posicao y do objeto
    int xStart;             //Offset do comeco da hitbox no eixo x
    int yStart;             //Offset do comeco da hitbox no eixo y
    int xEnd;               //Offset do fim da hitbox no eixo x
    int yEnd;               //Offset do fim da hitbox no eixo y
    int status;             //Estado do objeto
    Sprite spriteList[4];   //Lista de sprites que compoem o objeto
    Polygon polygonList[4]; //Lista de poligonos que compoem o objeto
} Object;

int appState = 1;                                           //Variavel de estado do jogo
int btnValue = 0;
int printList[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   //Lista de objetos a serem exibidos
Object player1;                                             //Objeto global do jogador 1
Object player2;                                             //Objeto global do jogador 2
Object enemyList[4];                                        //Lista global de ate 4 objetos referentes aos inimigos

/*Funcao para verificar colisao
Argumentos:
xi1 = menor posicao x da hitbox 1
yi1 = menor posicao y da hitbox 1
xf1 = maior posicao x da hitbox 1
yf1 = maior posicao y da hitbox 1
xi2 = menor posicao x da hitbox 2
yi2 = menor posicao y da hitbox 2
xf2 = maior posicao x da hitbox 2
yf2 = maior posicao y da hitbox 2
*/
int chk_collision(int xi1, int yi1, int xf1, int yf1, int xi2, int yi2, int xf2, int yf2) {
    //Primeiro fazemos a checagem no eixo y, visto que por se tratar de um top-down shooter, as colisoes tem chance maior de ocorrer enquanto movendo no eixo y
    int miny;
    int maxy;
    //Calcular o comprimento y de cada hitbox
    int ylen1 = (yf1 - yi1 + 1);
    int ylen2 = (yf2 - yi2 + 1);

    //Achar o valor minimo de y entre ambas as hitboxes
    if (yi2 < yi1) {
        miny = yi2;
    }
    else {
        miny = yi1;
    }

    //Achar o valor maximo de y entre ambas as hitboxes
    if (yf2 > yf1) {
        maxy = yf2;
    }
    else {
        maxy = yf1;
    }

    //Verificacao de NAO-sobreposicao no eixo y, ou seja, ver se a distancia entre a ponta de uma hitbox e a ponta oposta da outra e maior ou igual a soma dos comprimentos das hitboxes
    if ((maxy - miny + 1) >= (ylen1 + ylen2)) {
        //Se nao houver sobreposicao no eixo y, nao pode haver colisao alguma, retornando 0
        return 1;
    }

    //Repete o processo para o eixo x
    int minx;
    int maxx;
    int xlen1 = (xf1 - xi1 + 1);
    int xlen2 = (xf2 - xi2 + 1);

    if (xi2 < xi1) {
        minx = xi2;
    }
    else {
        minx = xi1;
    }

    if (xf2 > xf1) {
        maxx = xf2;
    }
    else {
        maxx = xf1;
    }

    if ((maxx - minx + 1) >= (xlen1 + xlen2)) {
        return 1;
    }

    //Se nenhum dos teste de NAO-sobreposicao "passou", existe uma colisao
    return 0;
}

//Funcao modulo para achar o valor absoluto de um numero
int mod(int num){
    if (num < 0){
      num = num *-1;
    }
    return num;
}

//Funcao para achar o indice do intervalo de tamanho 10 ao qual um valor igual ou maior que 0 pertence
int intervalsOfTen(int value) {

    if (value < 10) {
        return 0;
    }
    else if (value < 20) {
        return 1;
    }
    else if (value < 30) {
        return 2;
    }
    else if (value < 40) {
        return 3;
    }
    else if (value < 50) {
        return 4;
    }
    else if (value < 60) {
        return 5;
    }
    else if (value < 70) {
        return 6;
    }
    else if (value < 80) {
        return 7;
    }
    else {
        return 8;
    }
}


// Função para ler o acelerômetro em uma thread e atualizar a posicao do jogador 1
void* ler_acelerometro(void* arg) {
    int16_t XYZ[3];
    int16_t aceleracaoX;
    int16_t aceleracaoY;
    //int16_t aceleracaoZ;

    //Contador de movimento nos eixos X e Y
    int movCountX = 0;
    int movCountY = 0;

    //Contador das medicoes iniciais do acelerometro e somas dos valores iniciais
    int initialCount;
    int sum16X = 0;
    int sum16Y = 0;

    //Jogar os 8 valores de medicao iniciais fora
    for(initialCount = 0; initialCount < 8; initialCount++) {
        usleep(25000);
        ADXL345_XYZ_Read(XYZ);
    }

    //Somar os proximos 16 valores de medicao
    for(initialCount = 0; initialCount < 16; initialCount++) {
        usleep(25000);
        ADXL345_XYZ_Read(XYZ);
        sum16X += XYZ[0];
        sum16Y += XYZ[1];
    }

    //Achar a media dos valores de medicao para definir como parametros iniciais
    int initialX = (sum16X / 16);
    int initialY = (sum16Y / 16);

    printf("INX: %d, INY: %d\n", initialX, initialY);

    while (1) {

        if(appState == 0) {

            //Le o acelerometro
            ADXL345_XYZ_Read(XYZ);
            aceleracaoX = (XYZ[0] - initialX);
            aceleracaoY = (XYZ[1] - initialY);
            //aceleracaoZ = XYZ[2];

            //Variavel para determinar se houve movimento
            int wasPosChanged = 0;

            //Contador de movimento sobe a cada ciclo de medicao de acordo com a inclinacao do acelerometro nos eixos X e Y
            movCountX += intervalsOfTen(mod(aceleracaoX));
            movCountY += intervalsOfTen(mod(aceleracaoY));
            //Contador de movimento no eixo X chega a 8
            if (movCountX >= 8) {
                int newxpos = (player1.xpos + (aceleracaoX / mod(aceleracaoX)));
                
                //Se estiver no intervalo de movimento X, faz o movimento
                if((newxpos >= 170) && (newxpos < 450)) {
                    player1.xpos = newxpos;
                    wasPosChanged = 1;
                }
                
                movCountX -= 8;
            }

            //Contador de movimento no eixo Y chega a 8
            if (movCountY >= 8) {
                int newypos = (player1.ypos - (aceleracaoY / mod(aceleracaoY)));
                
                //Se estiver no intervalo de movimento Y, faz o movimento
                if((newypos >= 40) && (newypos < 420)) {
                    player1.ypos = newypos;
                    wasPosChanged = 1;
                }
                
                movCountY -= 8;
            }

            //Se mudou a posicao
            if (wasPosChanged == 1) {
                //Pede para exibir o objeto na nova posicao ao registrar na lista
                printList[0] = 1;
                int objCount;

                //Verifica se houve colisao com objeto "inimigo"
                for (objCount = 0; objCount < 4; objCount++) {
                    Object actualEnemy = enemyList[objCount];

                    if (chk_collision((player1.xpos + player1.xStart), (player1.ypos + player1.yStart),
                    (player1.xpos + player1.xEnd), (player1.ypos + player1.yEnd),
                    (actualEnemy.xpos + actualEnemy.xStart), (actualEnemy.ypos + actualEnemy.yStart),
                    (actualEnemy.xpos + actualEnemy.xEnd), (actualEnemy.ypos + actualEnemy.yEnd)) == 0) {
                        player1.status = 1;
                    }
                }
            }

            //Tempo para o proximo ciclo de leitura (1.5 milissegundos)
            usleep(1500);
        }
    }
}

// Função para ler o mouse em uma thread e atualizar a posicao do jogador 2
void* ler_mouse(void* arg){

    int fd, bytes;
    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);

    if(fd == -1) {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
    //Dados do mouse
    unsigned char data[3];
    signed char x, y;
    int left, middle, right;

    while(1) {

        if (appState == 0) {

            //Le o mouse
            bytes = read(fd, data, sizeof(data));
            int wasPosChanged = 0;
            if(bytes > 0){
                
                //Dados dos botoes
                left = data[0] & 0x1;
                right = data[0] & 0x2;
                middle = data[0] & 0x4;
                //Separa nos vetores
                int xvector = ((int) data[1]);
                int yvector = ((int) data[2]);
                //Valores unsigned acima de 127 sao negativos (ate 255)
                if(xvector >= 128) {
                    xvector = (-255 + xvector);
                }

                //Valores unsigned acima de 127 sao negativos (ate 255)
                if(yvector >= 128) {
                    yvector = (-255 + yvector);
                }

                //Acha as novas posicoes apos o movimento
                int newxpos = (player2.xpos + xvector);
                int newypos = (player2.ypos - yvector);
                //Tenta fazer o movimento no eixo X
                if (player2.xpos != newxpos) {
                    
                    //Se estiver no intervalo de movimento X, faz o movimento
                    if((newxpos >= 170) && (newxpos < 450)) {
                        player2.xpos = newxpos;
                        wasPosChanged = 1;
                    }
                }

                //Tenta fazer o movimento no eixo Y
                if (player2.ypos != (y*3)) {
                    
                    //Se estiver no intervalo de movimento Y, faz o movimento
                    if((newypos >= 40) && (newypos < 420)) {
                        player2.ypos = newypos;
                        wasPosChanged = 1;
                    }
                }
                
                 //Se mudou a posicao
                if (wasPosChanged == 1) {
                    //Pede para exibir o objeto na nova posicao ao registrar na lista
                    printList[1] = 1;
                    int objCount;
                    //Verifica se houve colisao com objeto "inimigo"
                    for (objCount = 0; objCount < 4; objCount++) {
                        Object actualEnemy = enemyList[objCount];
                        if (chk_collision((player2.xpos + player2.xStart), (player2.ypos + player2.yStart),
                        (player2.xpos + player2.xEnd), (player2.ypos + player2.yEnd),
                        (actualEnemy.xpos + actualEnemy.xStart), (actualEnemy.ypos + actualEnemy.yStart),
                        (actualEnemy.xpos + actualEnemy.xEnd), (actualEnemy.ypos + actualEnemy.yEnd)) == 0) {
                            player2.status = 1;
                        }
                    }
                }
            }
        }
    }
}

// Função para exibir os objetos do jogo
void* printar_objetos(void* arg) {

    while(1) {

        int printCount;

        for(printCount = 0; printCount< 12; printCount++) {

            //Se o objeto esta marcado na lista para "imprimir"
            if (printList[printCount] == 1) {
                int elementCount;

                //Varre a lista de 4 sprites e 4 poligonos que PODEM fazer parte de cada objeto
                for (elementCount = 0; elementCount < 4; elementCount++) {
                    Sprite actualSprite;
                    Polygon actualPolygon;
                    int xbase;
                    int ybase;

                    //Indice 0 pertence ao jogador 1
                    if(printCount == 0) {
                        actualSprite = (player1.spriteList)[elementCount];
                        actualPolygon = (player1.polygonList)[elementCount];
                        xbase = player1.xpos;
                        ybase = player1.ypos;
                    }
                    //Indice 1 pertence ao jogador 2
                    else if(printCount == 1) {
                        actualSprite = (player2.spriteList)[elementCount];
                        actualPolygon = (player2.polygonList)[elementCount];
                        xbase = player2.xpos;
                        ybase = player2.ypos;
                    }
                    //Indices de 2 a 5 pertencem aos "inimigos"
                    else if((printCount >= 2) && (printCount < 6)) {
                        actualSprite = ((enemyList[(printCount - 2)]).spriteList)[elementCount];
                        actualPolygon = ((enemyList[(printCount - 2)]).polygonList)[elementCount];
                        xbase = (enemyList[(printCount - 2)]).xpos;
                        ybase = (enemyList[(printCount - 2)]).ypos;
                    }

                    //Se o registro tem numero valido, sabe-se que tem sprite ali
                    if(actualSprite.reg >= 1) {
                        //Numero sp do sprite inicialmente 0, que desativa
                        int spriteSp = 0;
                        //Porem, caso o jogo esteja em execucao, muda para 1, ativando
                        if(appState == 0) {
                            spriteSp = 1;
                        }
                        //Envia comando de "escrever" sprite
                        WBR_SPRITE(actualSprite.reg, actualSprite.spriteoffset, (xbase + actualSprite.xoffset), (ybase + actualSprite.yoffset), spriteSp);
                    }

                    if(actualPolygon.size >= 1) {
                        //Tamanho do poligono inicalmente 0, que desativa
                        int polSize = 0;
                        
                        //Porem, caso o jogo esteja em execucao, muda para 1, ativando
                        if(appState == 0) {
                            polSize = actualPolygon.size;
                        }
                        
                        //Envia comando de desenhar poligono
                        DP((xbase + actualPolygon.xoffset), (ybase + actualPolygon.yoffset), actualPolygon.color, actualPolygon.shape, polSize);
                    }
                }

                printList[printCount] = 0;
            }
        }
    }
}

// Função para monitorar o fluxo do jogo
void* monitorar_jogo(void* arg) {
    
    while(1) {
        //printf("AS: %d\n", appState);

        //Se o valor do botao e 1, encerramos o jogo
        if (btnValue == 1) {
            appState = 4;

            printList[0] = 1;
            printList[1] = 1;
        }
        //Se o valor do botao e 2, reiniciamos o jogo
        else if (btnValue == 2) {
            appState = 3;

            printList[0] = 1;
            printList[1] = 1;

            //Espera 400 milissegundos antes de continuar a thread (debouncing e "cooldown")
            usleep(400000);
            
            //Apos isso, segura tambem enquanto o botao nao for solto (nao permite ativacao seguida por manter pressionado)
            while (btnValue != 0) { }
            //Espera 100 milissegundos antes de continuar a thread (debouncing)
            usleep(100000);
        }
        //Se o valor do botao e 4 e o estado e 0, pausamos o jogo
        else if ((btnValue == 4) && (appState == 0)) {
            appState = 1;

            printList[0] = 1;
            printList[1] = 1;

            //Espera 400 milissegundos antes de continuar a thread (debouncing e "cooldown")
            usleep(400000);
            
            //Apos isso, segura tambem enquanto o botao nao for solto (nao permite ativacao seguida por manter pressionado)
            while (btnValue != 0) { }
            //Espera 100 milissegundos antes de continuar a thread (debouncing)
            usleep(100000);
        }
        //Se o valor do botao e 4 e o estado e 0, pausamos o jogo
        else if ((btnValue == 4) && (appState == 1)) {
            appState = 0;

            printList[0] = 1;
            printList[1] = 1;

            //Espera 400 milissegundos antes de continuar a thread (debouncing e "cooldown")
            usleep(400000);
            
            //Apos isso, segura tambem enquanto o botao nao for solto (nao permite ativacao seguida por manter pressionado)
            while (btnValue != 0) { }
            //Espera 100 milissegundos antes de continuar a thread (debouncing)
            usleep(100000);
        }
    }
}

void move_inim(){

    char dir = 'R';
    
    while(1){
    usleep(10000);
    if (dir == 'R'){
      enemyList[0].xpos ++;
      printList[2] = 1;
      if (enemyList[0].xpos == 450){
        dir = 'L';
    }
    }
    else {
      enemyList[0].xpos --;
      printList[2] = 1;
      if (enemyList[0].xpos == 170){
        dir = 'R';
    }  
    }
    }
}

int main(int argc, char** argv) {
    int fd1 = -1;
    int fd2 = -1;
    void *I2C0_virtual;
    int16_t XYZ[3];

    int isFirstRun = 1;
    // Abrir /dev/mem e mapear a área de memória do I2C e do SYSMGR
    if ((fd1 = open_physical(fd1)) == -1)
        return (-1);
    if (!(I2C0_virtual = map_physical(fd1, I2C0_BASE, I2C0_SPAN)))
        return (-1);
    close_physical(fd1);


    //Mapeamento de memória do I2C0
    I2C0_con = (int *) (I2C0_virtual + I2C0_CON);
    I2C0_tar = (int *) (I2C0_virtual + 0x4);
    I2C0_data = (int *) (I2C0_virtual + 0x10);
    I2C0_readbuffer = (int *) (I2C0_virtual + 0x78);
    I2C0_enable = (int *) (I2C0_virtual + 0x6C);
    I2C0_enable_sts = (int *) (I2C0_virtual + 0x9C);
    I2C0_fs_hcnt = (int *) (I2C0_virtual + 0x1C);
    I2C0_fs_lcnt = (int *) (I2C0_virtual + 0x20);

    //Mapear memória assembly
    MAP();

    //Carrega os sprites para a memoria
    desenha_sprite();
    desenha_sprite_ps2();

    //Inicializa o controlador I2C e configura a conexao entre o controlador I2C e o acelerometro ADXL345
    I2C0_init();

    //Inicializa e configura o acelerometro
    ADXL_345_init();

    //Calibra o acelerometro
    ADXL345_Calibrate();

    //Valores fixos de objeto do jogador 1
    player1.xStart = 0;
    player1.yStart = 0;
    player1.xEnd = 19;
    player1.yEnd = 19;
    
    player1.spriteList[0].reg = 1;
    player1.spriteList[0].spriteoffset = 0;
    player1.spriteList[0].xoffset = 0;
    player1.spriteList[0].yoffset = 0;

    player1.spriteList[1].reg = -1;

    player1.spriteList[2].reg = -1;

    player1.spriteList[3].reg = -1;

    player1.polygonList[0].size = -1;

    player1.polygonList[1].size = -1;

    player1.polygonList[2].size = -1;

    player1.polygonList[3].size = -1;

    //Valores fixos de objeto do jogador 2
    player2.xStart = 0;
    player2.yStart = 0;
    player2.xEnd = 19;
    player2.yEnd = 19;

    player2.spriteList[0].reg = 3;
    player2.spriteList[0].spriteoffset = 1;
    player2.spriteList[0].xoffset = 0;
    player2.spriteList[0].yoffset = 0;

    player2.spriteList[1].reg = -1;

    player2.spriteList[2].reg = -1;

    player2.spriteList[3].reg = -1;

    player2.polygonList[0].size = -1;

    player2.polygonList[1].size = -1;

    player2.polygonList[2].size = -1;

    player2.polygonList[3].size = -1;

    //Valores do inimigo
    enemyList[0].xpos = 200;
    enemyList[0].ypos = 200;
    enemyList[0].xStart = 0;
    enemyList[0].yStart = 0;
    enemyList[0].xEnd = 19;
    enemyList[0].yEnd = 19;
    enemyList[0].status = 0;

    enemyList[0].spriteList[0].reg = 5;
    enemyList[0].spriteList[0].spriteoffset = 2;
    enemyList[0].spriteList[0].xoffset = 0;
    enemyList[0].spriteList[0].yoffset = 0;

    enemyList[0].spriteList[1].reg = -1;
    enemyList[0].spriteList[2].reg = -1;
    enemyList[0].spriteList[3].reg = -1;

    enemyList[0].polygonList[0].size = -1;
    enemyList[0].polygonList[1].size = -1;
    enemyList[0].polygonList[2].size = -1;
    enemyList[0].polygonList[3].size = -1;

    printList[2] = 1;
    
    while(appState != 4) {
        
        //Valores iniciais de sessao de jogo do jogador 1
        printList[0] = 1;

        player1.xpos = 260;
        player1.ypos = 260;
        player1.status = 0;
        
        //Valores iniciais de sessao de jogo do jogador 2
        printList[1] = 1;
        
        player2.xpos = 320;
        player2.ypos = 260;
        player2.status = 0;

        if (isFirstRun == 1) {
            
            pthread_t thread_mov_inimigo;

            if(pthread_create(&thread_mov_inimigo, NULL, move_inim, NULL) != 0){
                fprintf(stderr ,"Erro ao criar thread de moimento do inimigo");
                return 1;
            }

            //Cria a thread de monitoracao do estado do jogo
            pthread_t thread_monitorar;

            if(pthread_create(&thread_monitorar, NULL, monitorar_jogo, NULL) != 0){
                fprintf(stderr ,"Erro ao criar thread de monitoracao");
                return 1;
            }

            //Cria thread para monitoramento do acelerometro e controle do jogador 1
            pthread_t thread_acelerometro;
            if (pthread_create(&thread_acelerometro, NULL, ler_acelerometro, NULL) != 0) {
                fprintf(stderr, "Erro ao criar a thread do acelerômetro\n");
                return 1;
            }
            //Cria thread para monitoramento do mouse e controle do jogador 2
            pthread_t thread_mouse;
            if (pthread_create(&thread_mouse, NULL, ler_mouse, NULL) != 0){
                fprintf(stderr, "Erro ao criar a thread do mouse\n");
                return 1;
            }
            //Cria a thread de renderizacao
            pthread_t thread_renderizar;

            if(pthread_create(&thread_renderizar, NULL, printar_objetos, NULL) != 0){
                fprintf(stderr ,"Erro ao criar thread de renderização");
                return 1;
            }
        }
        //Loop principal que le os botoes para controle do jogo
        while(appState != 3 && appState != 4) {
            btnValue = RDBT();
        }

        if (appState != 4) {
            //Volta o estado para "pausa"
            appState = 1;
        }
        else {
            appState = 1;

            appState = 4;
        }

        //Atualiza variavel de primeira execucao
        isFirstRun = 0;
    }
}