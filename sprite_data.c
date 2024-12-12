#include <stdint.h>

#define NEW_PISKEL_FRAME_COUNT 1
#define NEW_PISKEL_FRAME_WIDTH 20
#define NEW_PISKEL_FRAME_HEIGHT 20

/* Piskel data for "New Piskel" */

void desenha_sprite(){
  int cont0, cont1, cont3;

  unsigned int nave_bola_data[500] = {
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 
510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 
510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 510, 510, 510, 
510, 510, 510, 510, 510, 511, 0, 511, 0, 511, 0, 511, 0, 511, 0, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 510, 510, 510, 
510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 
510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 
510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
};

unsigned int nave_pinguim_data[500] = {
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 292, 292, 292, 292, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 292, 39, 39, 292, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 292, 292, 292, 39, 292, 292, 292, 292, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 292, 292, 292, 292, 292, 292, 292, 292, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 292, 292, 292, 292, 511, 511, 292, 292, 292, 292, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 292, 292, 292, 292, 511, 511, 511, 511, 292, 292, 292, 292, 510, 510, 510, 510, 
510, 510, 510, 510, 292, 292, 292, 292, 511, 511, 511, 511, 292, 292, 292, 292, 510, 510, 510, 510, 
510, 510, 510, 292, 292, 292, 292, 511, 511, 511, 511, 511, 511, 292, 292, 292, 292, 510, 510, 510, 
510, 510, 510, 292, 292, 292, 292, 511, 511, 511, 511, 511, 511, 292, 292, 292, 292, 510, 510, 510, 
510, 510, 292, 292, 292, 292, 511, 511, 511, 511, 511, 511, 511, 511, 292, 292, 292, 292, 510, 510, 
510, 510, 292, 292, 292, 292, 511, 511, 511, 511, 511, 511, 511, 511, 292, 292, 292, 292, 510, 510, 
510, 510, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 292, 510, 510, 
510, 510, 292, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 292, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
};

unsigned int projetil_data[500] = {
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 7, 7, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 7, 7, 7, 7, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
};

  cont3 = 0;

  for(cont0 = 0; cont0 < 21; cont0++) {
            
    for(cont1 = 0; cont1 < 20; cont1++) {
                
      WSM(((cont0 * 20) + cont1), nave_bola_data[((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 800, nave_pinguim_data[((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 400, projetil_data[((cont0 * 20) + cont1)]);
      }
    }
    
};
