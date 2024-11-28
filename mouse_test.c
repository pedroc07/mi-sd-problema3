#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vlib.h"
//Biblioteca de criacao e gerenciamento de threads para Linux
#include <pthread.h>

//Biblioteca original de mapeamento da memoria do dispositivo DE1-SoC com Linux embutido
#include "map.c"

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

int move_inim(){
    int inim_x = 0;
    int inim_y = 200;
    char inim_dir = 'R';
    
    while(1) {
    usleep(10000);
    WBR_SPRITE(5, 600, inim_x, inim_y, 1);

    if (inim_dir == 'R'){
      inim_x ++;
      if (inim_x == 600){
        inim_dir = 'L';
    }
    }
    else {
      inim_x --;
      if (inim_x == 0){
        inim_dir = 'R';
    }
    }    
    }
}

int main(int argc, char** argv)
{
    int fd, bytes;
    unsigned char data[3];

    MAP();

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    int left, middle, right;
    signed char x, y;

    x = 0;
    y = 0;
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

  //Cria thread para movimento do inimigo
  pthread_t thread_inim;
  if (pthread_create(&thread_inim, NULL, move_inim, NULL) != 0){
    fprintf(stderr, "Erro ao criar a thread do acelerômetro\n");
    return 1;  
  }

  while(1){
    // Read Mouse     
    bytes = read(fd, data, sizeof(data));

    if(bytes > 0){
      //WBR_SPRITE(1, 0, x, y, 0);
      left = data[0] & 0x1;
      right = data[0] & 0x2;
      middle = data[0] & 0x4;

      x += data[1];
      y -= data[2];
      printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
      //WBR_SPRITE(1, 0, x, y, 1);
      }

    WBR_SPRITE(1, 0, ((x*3)+300), ((y*3)+200), 1);   

    }

  return 0; 
}