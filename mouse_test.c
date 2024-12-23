#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vlib.h"
//Biblioteca de criacao e gerenciamento de threads para Linux
#include <pthread.h>
#include <time.h>
#include "nave_bola.c"

//Biblioteca original de mapeamento da memoria do dispositivo DE1-SoC com Linux embutido
#include "map.c"inim_dir

typedef struct{
  int x;
  int y;
  char dir;
  int offset;
  int reg;
  int ativo;
  int colisao;
} Sprite;

Sprite JogadorMouse;
Sprite E1;

int16_t X_inicial = 0;
int16_t aceleracaoX = 0;
int16_t aceleracaoY = 0;
int16_t aceleracaoZ = 0;

// Função para ler o acelerômetro em uma thread
void* ler_acelerometro(void* arg) {
    int16_t XYZ[3];

    int cont = 0;
    
    while (1) {
      ADXL345_XYZ_Read(XYZ);
      aceleracaoX = XYZ[0];
      aceleracaoY = XYZ[1];
      aceleracaoZ = XYZ[2];
      usleep(100000);

      //Atualiza a medicao do acelerometro ate 10x, para obter um valor inicial de X valido para uso
      if(cont<9) {
        X_inicial = aceleracaoX;
        cont++;
      } 
      DP((aceleracaoX) + 20, 300, 187, 1, 1);
    }
    return NULL;
}

int mod(int num){
    if (num < 0){
      num = num *-1;
    }
    return mod;
}

void move_inim(){
    
    usleep(10000);
    WBR_SPRITE(E1.reg, E1.offset, E1.x, E1.y, E1.ativo);

    if (E1.dir == 'R'){
      E1.x ++;
      if (E1.x == 600){
        E1.dir = 'L';
    }
    }
    else {
      E1.x --;
      if (E1.x == 0){
        E1.dir = 'R';
    }  
    }
}

void move_mouse(){

  int left, middle, right;

  int fd, bytes;
  unsigned char data[3];
  signed char x, y;

    MAP();

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    JogadorMouse.x = 0;
    JogadorMouse.y = 0;
    JogadorMouse.ativo = 1;
    JogadorMouse.offset = 0;
    JogadorMouse.reg = 1;
  while(1){
  bytes = read(fd, data, sizeof(data));

  if(bytes > 0){
  //WBR_SPRITE(1, 0, x, y, 0);
    left = data[0] & 0x1;
    right = data[0] & 0x2;
    middle = data[0] & 0x4;


    x += (int) data[1];
    y -= (int) data[2];
    JogadorMouse.x = ((x*3)+300);
    JogadorMouse.y = ((y*3)+200);
    printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", JogadorMouse.x, JogadorMouse.y, left, middle, right);
    WBR_SPRITE(JogadorMouse.reg, JogadorMouse.offset, JogadorMouse.x, JogadorMouse.y, JogadorMouse.ativo);
    }
  }
}

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

  printf("%d\n", (maxy - miny + 1));
  printf("%d\n", (ylen1 + ylen2));
  printf("%d\n", (maxx - minx + 1));
  printf("%d\n", (xlen1 + xlen2));

  //Verificacao de NAO-sobreposicao no eixo y, ou seja, ver se a distancia entre a ponta de uma hitbox e a ponta oposta da outra e maior ou igual a soma dos comprimentos das hitboxes
  if ((maxy - miny + 1) >= (ylen1 + ylen2)) {
    //Se nao houver sobreposicao no eixo y, nao pode haver colisao alguma, retornando 0
    return 1;
  }

  if ((maxx - minx + 1) >= (xlen1 + xlen2)) {
    return 1;
  }

  //Se nenhum dos teste de NAO-sobreposicao "passou", existe uma colisao
  return 0;
}

int main(int argc, char** argv)
{
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

  //Cria o thread de monitoramento do acelerometro, que constantemente atualiza os valores da medicao das inclinacoes X, Y e Z (medida em g referente a forca de aceleracao sentida em cada eixo)
  pthread_t thread_acelerometro;

  if (pthread_create(&thread_acelerometro, NULL, ler_acelerometro, NULL) != 0) {
      fprintf(stderr, "Erro ao criar a thread do acelerômetro\n");
      return 1;
    }

  //Cria thread para movimento do mouse
  pthread_t thread_mouse;
  if (pthread_create(&thread_mouse, NULL, move_mouse, NULL) != 0){
    fprintf(stderr, "Erro ao criar a thread do mouse\n");
    return 1;  
  }
  JogadorMouse.colisao = 1;

  E1.x = 0;
  E1.y = 100;
  E1.dir = 'R';
  E1.offset = 600;
  E1.ativo = 1;
  E1.reg = 5;
  desenha_sprite();
  while(JogadorMouse.colisao){
    move_inim();
    JogadorMouse.colisao = chk_collision(JogadorMouse.x+1, JogadorMouse.y+1, 
                         JogadorMouse.x-1 + 19, JogadorMouse.y-1 +19, E1.x, E1.y, E1.x+19, E1.y + 19);
    }
    printf("Colisão!");

  return 0; 
}

