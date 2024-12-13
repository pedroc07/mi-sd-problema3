#include <stdint.h>

//#define NEW_PISKEL_FRAME_COUNT 1
//#define NEW_PISKEL_FRAME_WIDTH 20
//#define NEW_PISKEL_FRAME_HEIGHT 20

/* Piskel data for "New Piskel" */

void desenha_sprite(){
  int cont0, cont1, cont3;

  /*unsigned int nave_bola_data_0[500] = {
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 
  510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 327, 327, 327, 327, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 511, 511, 510, 327, 511, 511, 327, 510, 511, 511, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 327, 327, 327, 327, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 
  510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 39, 39, 39, 39, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  };*/

unsigned int sphere_spaceship_animated_data[6][500] = {
  {
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 39, 111, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 39, 111, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 111, 183, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 255, 255, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 183, 255, 183, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 510, 111, 3, 448, 183, 448, 448, 111, 3, 510, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 510, 111, 3, 455, 183, 455, 455, 111, 3, 510, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 510, 39, 3, 7, 111, 7, 7, 39, 3, 510, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 21, 39, 39, 111, 111, 111, 39, 39, 39, 21, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 3, 21, 21, 21, 21, 21, 21, 3, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 3, 3, 3, 3, 3, 3, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 39, 111, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 39, 111, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 111, 183, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 255, 255, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 183, 255, 183, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 510, 3, 183, 455, 455, 183, 455, 3, 111, 510, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 510, 3, 111, 7, 7, 111, 7, 3, 39, 510, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 510, 3, 111, 63, 63, 111, 63, 3, 39, 510, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 21, 39, 39, 111, 111, 111, 39, 39, 39, 21, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 3, 21, 21, 21, 21, 21, 21, 3, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 3, 3, 3, 3, 3, 3, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 39, 111, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 39, 111, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 111, 183, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 255, 255, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 183, 255, 183, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 111, 510, 510, 183, 7, 7, 111, 510, 510, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 510, 510, 183, 63, 63, 111, 510, 510, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 510, 510, 111, 56, 56, 111, 510, 510, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 21, 39, 39, 111, 111, 111, 39, 39, 39, 21, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 3, 21, 21, 21, 21, 21, 21, 3, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 3, 3, 3, 3, 3, 3, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 39, 111, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 39, 111, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 111, 183, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 255, 255, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 183, 255, 183, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 510, 111, 3, 63, 183, 63, 63, 111, 3, 510, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 510, 111, 3, 56, 183, 56, 56, 111, 3, 510, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 510, 39, 3, 504, 111, 504, 504, 39, 3, 510, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 21, 39, 39, 111, 111, 111, 39, 39, 39, 21, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 3, 21, 21, 21, 21, 21, 21, 3, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 3, 3, 3, 3, 3, 3, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 39, 111, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 39, 111, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 111, 183, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 255, 255, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 183, 255, 183, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 510, 3, 183, 56, 56, 183, 56, 3, 111, 510, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 510, 3, 111, 504, 504, 111, 504, 3, 39, 510, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 510, 3, 111, 448, 448, 111, 448, 3, 39, 510, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 21, 39, 39, 111, 111, 111, 39, 39, 39, 21, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 3, 21, 21, 21, 21, 21, 21, 3, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 3, 3, 3, 3, 3, 3, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 39, 111, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 39, 111, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 111, 183, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 255, 255, 255, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 39, 111, 183, 183, 255, 183, 183, 183, 111, 111, 39, 39, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 111, 510, 510, 183, 504, 504, 111, 510, 510, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 510, 510, 183, 448, 448, 111, 510, 510, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 39, 510, 510, 111, 455, 455, 111, 510, 510, 39, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 21, 21, 39, 39, 111, 111, 111, 39, 39, 39, 21, 21, 510, 510, 510, 510, 
    510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 3, 21, 21, 39, 39, 39, 39, 21, 21, 3, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 3, 21, 21, 21, 21, 21, 21, 3, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 3, 3, 3, 3, 3, 3, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  }
};

unsigned int rocket_thruster_animated_data[5][500] = {
  {
    510, 510, 510, 510, 510, 510, 510, 510, 438, 511, 511, 438, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 438, 511, 511, 438, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 292, 438, 438, 292, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 438, 511, 511, 438, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 438, 511, 511, 438, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 438, 438, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 510, 292, 292, 510, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 438, 511, 511, 438, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 438, 511, 511, 438, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 438, 438, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 438, 511, 511, 438, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 438, 511, 511, 438, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 438, 438, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  },
  {
    510, 510, 510, 510, 510, 510, 510, 510, 438, 511, 511, 438, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 511, 511, 511, 511, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 438, 511, 511, 438, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 438, 438, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 292, 510, 510, 292, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 292, 292, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 
    510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
  }
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
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510,
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
  510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510
};

unsigned int pause_data[500] = {
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 
510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510, 510, 510, 511, 511, 511, 510, 510, 510, 510,
510, 510, 510, 510, 511, 511, 511, 292, 510, 510, 510, 510, 292, 511, 511, 511, 510, 510, 510, 510,
510, 510, 510, 510, 511, 511, 511, 292, 510, 510, 510, 510, 292, 511, 511, 511, 510, 510, 510, 510 
};

  cont3 = 0;

  for(cont0 = 0; cont0 < 21; cont0++) {
            
    for(cont1 = 0; cont1 < 20; cont1++) {
                
      
      WSM(((cont0 * 20) + cont1), nave_pinguim_data[((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 400, projetil_data[((cont0 * 20) + cont1)]);

      
      WSM(((cont0 * 20) + cont1) + 1200, sphere_spaceship_animated_data[0][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 1600, sphere_spaceship_animated_data[1][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 2000, sphere_spaceship_animated_data[2][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 2400, sphere_spaceship_animated_data[3][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 2800, sphere_spaceship_animated_data[4][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 3200, sphere_spaceship_animated_data[5][((cont0 * 20) + cont1)]);

      WSM(((cont0 * 20) + cont1) + 4000, rocket_thruster_animated_data[0][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 4400, rocket_thruster_animated_data[1][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 4800, rocket_thruster_animated_data[2][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 5200, rocket_thruster_animated_data[3][((cont0 * 20) + cont1)]);
      WSM(((cont0 * 20) + cont1) + 5600, rocket_thruster_animated_data[4][((cont0 * 20) + cont1)]);

      WSM(((cont0 * 20) + cont1) + 6000, pause_data[((cont0 * 20) + cont1)]);
    }
  }
};