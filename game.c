#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vlib.h"
//Biblioteca de criacao e gerenciamento de threads para Linux
#include <pthread.h>
#include <time.h>

//Biblioteca original de mapeamento da memoria do dispositivo DE1-SoC com Linux embutido
#include "map.c"

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
    Sprite spriteList[4];     //Lista de sprites que compoem o objeto
    Polygon polygonList[4];   //Lista de poligonos que compoem o objeto
} Object;

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

  printf("Mousexi: %d, Mouseyi:%d, Mousexf: %d, Mouseyf:%d, Inimxi: %d, Inimyi:%d, Inimxf: %d, Inimyf:%d\n", xi1, yi1, xf1, yf1, xi2, yi2, xf2, yf2);

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

// Função para ler o acelerômetro em uma thread e atualizar a posicao do jogador 1
void* ler_acelerometro(void* arg) {
    int16_t aceleracaoX;
    int16_t aceleracaoY;
    int16_t aceleracaoZ;
    int16_t XYZ[3];
    
    while (1) {
      ADXL345_XYZ_Read(XYZ);
      aceleracaoX = XYZ[0];
      aceleracaoY = XYZ[1];
      aceleracaoZ = XYZ[2];

      int wasPosChanged = 0;

        if (player2.xpos != (aceleracaoX + 20)) {
            player2.xpos = (aceleracaoX + 20);
            wasPosChanged = 1;
        }

        if (player2.ypos != (aceleracaoY + 20)) {
            player2.ypos = (aceleracaoY + 20);
            wasPosChanged = 1;
        }

        if (wasPosChanged == 1) {
            printList[0] = 1;

            for (int objCount = 0; objCount < 4; objCount++) {
                Object actualEnemy = enemyList[objCount];

                if (chk_collision((player2.xpos + player2.xStart), (player2.ypos + player2.yStart),
                (player2.xpos + player2.xEnd), (player2.ypos + player2.yEnd),
                (actualEnemy.xpos + actualEnemy.xStart), (actualEnemy.ypos + actualEnemy.yStart),
                (actualEnemy.xpos + actualEnemy.xEnd), (actualEnemy.ypos + actualEnemy.yEnd)) == 0) {
                    player1.status = 1;
                }
            }
        }

        usleep(100000);
    }
    return NULL;
}

// Função para ler o mouse em uma thread e atualizar a posicao do jogador 2
void* ler_mouse(void* arg){

    int left, middle, right;

    int fd, bytes;
    unsigned char data[3];
    signed char x, y;

    MAP();

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    
    if(fd == -1) {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
    
    while(1) {
        bytes = read(fd, data, sizeof(data));
        int wasPosChanged = 0;

        if(bytes > 0){
            
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;


            x += (int) data[1];
            y -= (int) data[2];

            if (player2.xpos != ((x*3)+300)) {
                player2.xpos = ((x*3)+300);
                wasPosChanged = 1;
            }

            if (player2.ypos != ((y*3)+200)) {
                player2.ypos = ((y*3)+200);
                wasPosChanged = 1;
            }

            if (wasPosChanged == 1) {
                printList[1] = 1;

                for (int objCount = 0; objCount < 4; objCount++) {
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

// Função para exibir os objetos do jogo
void* printar_Objetos(void* arg) {

    for(int printCount = 0; printCount< 12; printCount++) {
        int printVar = printList[printCount];

        if (printVar == 1) {

            for (int elementCount = 0; elementCount < 4; elementCount++) {
                Sprite actualSprite;
                Polygon actualPolygon;
                int xbase;
                int ybase;

                if(printCount == 0) {
                    actualSprite = (player1.spriteList)[elementCount];
                    actualPolygon = (player1.polygonList)[elementCount];
                    xbase = player1.xpos;
                    ybase = player1.ypos;
                }
                else if(printCount == 1) {
                    actualSprite = (player2.spriteList)[elementCount];
                    actualPolygon = (player2.polygonList)[elementCount];
                    xbase = player2.xpos;
                    ybase = player2.ypos;
                }
                else if((printCount >= 2) && (printCount <= 5)) {
                    actualSprite = ((enemyList[(printCount - 2)]).spriteList)[elementCount];
                    actualPolygon = ((enemyList[(printCount - 2)]).polygonList)[elementCount];
                    xbase = (enemyList[(printCount - 2)]).xpos;
                    ybase = (enemyList[(printCount - 2)]).ypos;
                }

                if(actualSprite.reg >= 1) {
                    WBR_SPRITE(actualSprite.reg, actualSprite.spriteoffset, (xbase + actualSprite.xoffset), (ybase + actualSprite.yoffset), 1);
                }

                if(actualPolygon.size >= 1) {
                    DP((xbase + actualPolygon.xoffset), (ybase + actualPolygon.yoffset), actualPolygon.color, actualPolygon.shape, actualPolygon.size);
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    int fd1 = -1;
    int fd2 = -1;
    void *I2C0_virtual;
    int16_t XYZ[3];

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

    //Inicializa o controlador I2C e configura a conexao entre o controlador I2C e o acelerometro ADXL345
    I2C0_init();

    //Inicializa e configura o acelerometro
    ADXL_345_init();

    //Calibra o acelerometro
    ADXL345_Calibrate();

    //Cria thread para monitoramento do acelerometro e controle do jogador 1
    pthread_t thread_acelerometro;

    if (pthread_create(&thread_acelerometro, NULL, ler_acelerometro, NULL) != 0) {
        fprintf(stderr, "Erro ao criar a thread do acelerômetro\n");
        return 1;
    }
    
    //Valores iniciais do jogador 2
    player2.xpos = 0;
    player2.ypos = 0;
    player2.xStart = 0;
    player2.yStart = 0;
    player2.xEnd = 19;
    player2.yEnd = 19;
    player2.status = 0;
    player2.spriteList[0]

    //Cria thread para monitoramento do mouse e controle do jogador 2
    pthread_t thread_mouse;

    if (pthread_create(&thread_mouse, NULL, ler_mouse, NULL) != 0){
        fprintf(stderr, "Erro ao criar a thread do mouse\n");
        return 1;
    }
}