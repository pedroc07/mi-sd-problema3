#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "address_map_arm.h"

// ADXL345 Register List
#define ADXL345_ADDRESS 0x53  // Endereço I2C do ADXL345
#define ADXL345_REG_DEVID       	0x00
#define ADXL345_REG_POWER_CTL   	0x2D
#define ADXL345_REG_DATA_FORMAT 	0x31
#define ADXL345_REG_FIFO_CTL    	0x38
#define ADXL345_REG_BW_RATE     	0x2C
#define ADXL345_REG_INT_ENABLE  	0x2E  // default value: 0x00
#define ADXL345_REG_INT_MAP     	0x2F  // default value: 0x00
#define ADXL345_REG_INT_SOURCE  	0x30  // default value: 0x02
#define ADXL345_REG_DATAX0      	0x32  // read only
#define ADXL345_REG_DATAX1      	0x33  // read only
#define ADXL345_REG_DATAY0      	0x34  // read only
#define ADXL345_REG_DATAY1      	0x35  // read only
#define ADXL345_REG_DATAZ0      	0x36  // read only
#define ADXL345_REG_DATAZ1      	0x37  // read only
#define ADXL345_REG_OFSX        	0x1E
#define ADXL345_REG_OFSY        	0x1F
#define ADXL345_REG_OFSZ        	0x20
#define ADXL345_REG_THRESH_ACT		0x24
#define ADXL345_REG_THRESH_INACT	0x25
#define ADXL345_REG_TIME_INACT		0x26
#define ADXL345_REG_ACT_INACT_CTL	0x27

#define XL345_RATE_200        0x0b
#define XL345_FULL_RESOLUTION      0x08
#define XL345_RANGE_16G            0x03
#define XL345_MEASURE              0x08
#define XL345_STANDBY              0x00
#define XL345_INACTIVITY           0x08
#define XL345_ACTIVITY             0x10
#define XL345_RATE_100             0x0a
#define XL345_DATAREADY            0x80


volatile int *I2C0_con, *I2C0_tar, *I2C0_data, *I2C0_readbuffer, *I2C0_enable, *I2C0_enable_sts, *I2C0_fs_hcnt, *I2C0_fs_lcnt;

// Funções para acessar memória física
int open_physical(int fd) {
    if (fd == -1)
        if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
            printf("ERROR: could not open \"/dev/mem\"");
            return (-1);
        }
    return fd;
}

void close_physical(int fd) {
    close(fd);
}

void* map_physical(int fd, unsigned int base, unsigned int span) {
    void *virtual_base;
    virtual_base = mmap(NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, base);
    if (virtual_base == MAP_FAILED) {
        perror("ERROR: mmap() failed");
        close(fd);
        return (NULL);
    }
    return virtual_base;
}

int unmap_physical(void *virtual_base, unsigned int span) {
    if (munmap(virtual_base, span) != 0) {
        perror("ERROR: munmap() failed");
        return (-1);
    }
    return 0;
}


void I2C0_init(){
    //Para qualquer transmissão no I2C0
   *I2C0_enable = 2;
   printf("Desligando I2C0..\n");
   while(*I2C0_enable_sts == 1){}

   //Seta o I2C como mestre e o ADXL345 como escravo
   *I2C0_con = 0x65;
   *I2C0_tar = 0x53;

   //Seta o periodo
   *I2C0_fs_hcnt = 60 + 30;  // 0.6us + 0.3us
   *I2C0_fs_lcnt = 130 + 30; // 1.3us + 0.3us

   //Liga o controlador
   *I2C0_enable = 1;
   printf("Ligando I2C0..\n");
   while(*I2C0_enable_sts == 2){}
}

//Escreve um valor em um registrador
void ADXL345_write(uint8_t address, uint8_t value){
    *I2C0_data = address + 0x400;
    *I2C0_data = value;
}


void ADXL345_read(uint8_t address, uint8_t *value){

    //Envia o endereço + sinal de START
    *I2C0_data = address + 0x400;

    //Envia um sinal de leitura
    *I2C0_data = 0x100;

    // Espera que os dados entrem no buffer e então lê o valor
    while(*I2C0_readbuffer == 0){}
    *value = *I2C0_data;
}

//Realiza a leitura de vários registradores
void multi_read(uint8_t address, uint8_t values[], uint8_t
len){

    int nth_byte=0;
    int i;
    //Envia o endereço + sinal de START
    *I2C0_data = address + 0x400;

    for(i=0; i<len; i++){
        *I2C0_data = 0x100;
    }

    //Lê os bytes
    while(len){
        if ((*I2C0_readbuffer) > 0){
            values[nth_byte] = *I2C0_data;
            nth_byte++;
            len--;
        }
    }
}

void ADXL_345_init(){
    //+-16g range, full resolution
    ADXL345_write(ADXL345_REG_DATA_FORMAT, XL345_RANGE_16G | XL345_FULL_RESOLUTION);

    //taxa de aceleração: 200Hz
    ADXL345_write(ADXL345_REG_BW_RATE, XL345_RATE_200);

    ADXL345_write(ADXL345_REG_THRESH_ACT, 0x04); //atividade
    ADXL345_write(ADXL345_REG_THRESH_INACT, 0x02); //inatividade

    ADXL345_write(ADXL345_REG_TIME_INACT, 0x02); //tempo para inatividade
    ADXL345_write(ADXL345_REG_ACT_INACT_CTL, 0xFF);
    ADXL345_write(ADXL345_REG_INT_ENABLE, XL345_ACTIVITY | XL345_INACTIVITY );

    // para a medição
    ADXL345_write(ADXL345_REG_POWER_CTL, XL345_STANDBY);

    // começa a medição
    ADXL345_write(ADXL345_REG_POWER_CTL, XL345_MEASURE);
}

void ADXL345_XYZ_Read(int16_t szData16[3]){
    int8_t szData8[6];

    
    multi_read(ADXL345_REG_DATAX0, (uint8_t *)&szData8, sizeof(szData8));

    szData16[0] = (szData8[1] << 8) | szData8[0];
    szData16[1] = (szData8[3] << 8) | szData8[2];
    szData16[2] = (szData8[5] << 8) | szData8[4];
}


int ADXL345_WasActivityUpdated(){
    int bReady = 0;
    uint8_t data8;

    ADXL345_read(ADXL345_REG_INT_SOURCE,&data8);
    if (data8 & XL345_ACTIVITY)
        bReady = 1;

    return bReady;
}


int ADXL345_IsDataReady(){
    int bReady = 0;
    uint8_t data8;

    ADXL345_read(ADXL345_REG_INT_SOURCE,&data8);

    if (data8 & XL345_DATAREADY){
        bReady = 1;
    }
    return bReady;
}

int ROUNDED_DIVISION(int n, int d){
    int result;

    if(n >= 0){
        result = (n + (d / 2)) / d;
    }else{
        result = (n - (d / 2)) / d;
    }

    return result;
}


void ADXL345_Calibrate(){
    
    int average_x = 0;
    int average_y = 0;
    int average_z = 0;
    int16_t XYZ[3];
    int8_t offset_x;
    int8_t offset_y;
    int8_t offset_z;
    printf("================================================\n");
    printf("Iniciando a calibragem do ADXL345\n");
    
    // Coloca em estado de STANDBY
    ADXL345_write(ADXL345_REG_POWER_CTL, XL345_STANDBY);
    
    // Obtém os offsets atuais
    ADXL345_read(ADXL345_REG_OFSX, (uint8_t *)&offset_x);
    ADXL345_read(ADXL345_REG_OFSY, (uint8_t *)&offset_y);
    ADXL345_read(ADXL345_REG_OFSZ, (uint8_t *)&offset_z);
    
    // Usa uma taxa de 100 Hz para a aclibração e salva a taxa atual
    uint8_t saved_bw;
    ADXL345_read(ADXL345_REG_BW_RATE, &saved_bw);
    ADXL345_write(ADXL345_REG_BW_RATE, XL345_RATE_100);
    
    // Usa 16g de range (resolução total) e salva o formato atual.
    uint8_t saved_dataformat;
    ADXL345_read(ADXL345_REG_DATA_FORMAT, &saved_dataformat);
    ADXL345_write(ADXL345_REG_DATA_FORMAT, XL345_RANGE_16G | XL345_FULL_RESOLUTION);
    
    // Coloca em estado de MEASURE (medição)
    ADXL345_write(ADXL345_REG_POWER_CTL, XL345_MEASURE);
    
    // Obtém as acelerações médias dos eixos x, y e z por 32 amostras(LSB 3.9 mg)
    int i = 0;
    while (i < 32){
        if (ADXL345_IsDataReady()){
            ADXL345_XYZ_Read(XYZ);
            average_x += XYZ[0];
            average_y += XYZ[1];
            average_z += XYZ[2];
            i++;
        }
    }
    average_x = ROUNDED_DIVISION(average_x, 32);
    average_y = ROUNDED_DIVISION(average_y, 32);
    average_z = ROUNDED_DIVISION(average_z, 32);
    
    // Coloca em estado de STANDBY
    ADXL345_write(ADXL345_REG_POWER_CTL, XL345_STANDBY);

    printf("\nAverage X=%d, Y=%d, Z=%d\n", average_x, average_y, average_z);
    
    // Calcula os offsets (LSB 15.6 mg)
    offset_x += ROUNDED_DIVISION(0-average_x, 4);
    offset_y += ROUNDED_DIVISION(0-average_y, 4);
    offset_z += ROUNDED_DIVISION(256-average_z, 4);

    printf("Calibration: offset_x: %d, offset_y: %d, offset_z: %d (LSB: 15.6 mg)\n",offset_x,offset_y,offset_z);
    
    // "Seta" os registradores dos offsets
    ADXL345_write(ADXL345_REG_OFSX, offset_x);
    ADXL345_write(ADXL345_REG_OFSY, offset_y);
    ADXL345_write(ADXL345_REG_OFSZ, offset_z);
    
    // Volta para a taxa bw original
    ADXL345_write(ADXL345_REG_BW_RATE, saved_bw);
    
    // Volta para o formato de dado original
    ADXL345_write(ADXL345_REG_DATA_FORMAT, saved_dataformat);
    
    // Coloca em estado de MEASURE (medição)
    ADXL345_write(ADXL345_REG_POWER_CTL, XL345_MEASURE);

    printf("\nFinalizando a calibragem do ADXL345\n");
    printf("================================================\n");
}
