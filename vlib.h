#ifndef vlib.h
#define vlib.h

extern void MAP();

extern void UNMAP();

extern void WBR_SPRITE(unsigned int registrador, unsigned int offset, unsigned int x, unsigned int y, unsigned int sp);

extern void WBR_BACKGROUND(unsigned int rgb);

extern void WSM(unsigned int endereco, unsigned int cor);

extern void WBM(unsigned int x, unsigned int y, unsigned int rgb);

extern void DP(unsigned int x, unsigned int y, unsigned int cor, unsigned int forma, unsigned int tamanho);

extern int RDBT();

extern void TNLD(unsigned int indice_led, unsigned int valor_bit);

#endif
