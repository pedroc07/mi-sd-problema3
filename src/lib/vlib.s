.global WBR_SPRITE
.type WBR_SPRITE, %function
.global WBR_BACKGROUND
.type WBR_BACKGROUND, %function
.global WSM
.type WSM, %function
.global WBM
.type WBM, %function
.global DP
.type DP, %function
.global MAP
.type MAP, %function
.global UNMAP
.type UNMAP, %function
.global RDBT
.type RDBT, %function
.global TNLD
.type TNLD, %function

.equ DATA_A,    0x80
.equ DATA_B,    0x70
.equ WRREG,     0xc0
.equ WRFULL,    0xb0
.equ KEYS_BASE, 0x0
.equ HEX0_BASE, 0x60
.equ HEX1_BASE, 0x50
.equ HEX2_BASE, 0x40
.equ HEX3_BASE, 0x30
.equ HEX4_BASE, 0x20
.equ HEX5_BASE, 0x10

@ Argumentos: Nenhum
@ Retorna: void*
MAP:

    REG_ST:
        SUB SP, SP, #36             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R4, [SP, #4]
        STR R5, [SP, #8]
        STR R6, [SP, #12]
        STR R7, [SP, #16]
    
    LDR R0, =pagingfolder           @ Caminho de paginacao
    MOV R1, #2
    MOV R2, #0
    MOV R7, #5                      @ Codigo de chamada do sistema para abertura de arquivo
    SVC 0                           @ Chama o sistema
    
    LDR R1, =FD
    str R0, [R1]

    MOV R10, R0                     @ Copia o endereco virtual base de R0 para 10
    LDR R9, =ALT_LWFPGASLVS_OFST    @ Carrega em R9 o valor contido no endereco de memoria do offset da FPGA bridge

    MOV R0, #0                      @ Volta o registro R0 para 0, ja que este sera usado para avaliar se houve erro
    MOV R1, #4096                   @ Tamanho do pagina
    MOV R2, #3                      @ Leitura e escrita
    MOV R3, #1                      @ Modo MAP_SHARED, automaticamente guarda todas as alteracoes feitas na regiao mapeada na pagina
    MOV R4, R10                     @ Copia o caminho de paginacao para o registro que corresponde ao argumento da chamada de sistema 
    LDR R5, [R9]                    @ Carrega para R5 o valor contido no endereco de memoria referente ao valor de R9
    MOV R7, #192                    @ Codigo da chamada do sistema para mapeamento (mmap2)
    SVC 0                           @ Chama o sistema
    CMP R0, #-1                     @ Verifica se deu erro (codigo -1)
    BEQ END                       @ Vai ao final do codigo imediatamente caso de erro
    @MOV R9, R0                      @ Copia o endereco virtual base para R9

    REG_RS:
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #36             @ Adiciona a quantidade de offset necessaria no registrador SP
    
    END:
        LDR R1, =endereco_mapeado
        STR R0, [R1]
        BX LR                       @ Finaliza funcao

@Dando segmentation fault
@UNMAP:
@
@    REG_ST_:
@        SUB SP, SP, #12             @ Subtrai a quantidade de offset necessaria no registrador SP
@        STR LR, [SP, #0]
@        STR R0, [SP, #4]
@        STR R7, [SP, #8]
@
@    LDR R0, =endereco_mapeado
@    LDR R0, [R0]
@    MOV R1, #4096
@    MOV R7, #91
@    SVC 0
@
@    LDR R0, =FD
@    LDR R0, [R0]
@    MOV R7, #6
@    SVC 0
@
@    REG_RS_:
@        LDR LR, [SP, #0]
@        LDR R0, [SP, #4]
@        LDR R1, [SP, #8]
@        LDR R7, [SP, #12]
@        ADD SP, SP, #16
@
@    END_:
@    BX LR

@Label para verificar se a fila está cheia ou não
@Retorno: void
@OBS.: Não é uma função para passar pra C
VERIFICAR_FILA:

    _REG_ST_:
        SUB SP, SP, #16             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R0, [SP, #4]
        STR R1, [SP, #8]
        STR R7, [SP, #12]

    @Pega o mapeamento feito
    LDR R0, =endereco_mapeado
    LDR R0, [R0]

    VERIFICANDO:
    LDR R1,[R0, #WRFULL]            @Pega o valor do WRFULL e armazena em R1
    CMP R1, #1                      @Compara para ver se é igual a 1 (0 = vazio | 1 = cheio)
    BEQ VERIFICANDO                 @Se for, continua em loop até esvaziar.

    _REG_RS_:
        LDR LR, [SP, #0]
        LDR R0, [SP, #4]
        LDR R1, [SP, #8]
        LDR R7, [SP, #12]
        ADD SP, SP, #16             @Soma a quantidae de offset necessária no registrador SP

    _END_:
        BX LR


@ Argumentos: R0 = Registrador Sprite; R1 = Offset do sprite; R2 = posicao x; R3 = posicao y; R4 = valor sp de ligar/desligar sprite;
@ Retorna: void
WBR_SPRITE:
    @ Salva os valores originais dos registradores utilizados pelo sistema
    REG_ST_0:
        SUB SP, SP, #36             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R4, [SP, #4]
        STR R5, [SP, #8]
        STR R6, [SP, #12]
        STR R7, [SP, #16]
    @ Salva os parametros passados para a funcao por registradores
    PARAM_ST_0:
        STR R0, [SP, #20]
        STR R1, [SP, #24]
        STR R2, [SP, #28]
        STR R3, [SP, #32]

    @Pega o mapeamento feito
    LDR R9, =endereco_mapeado
    LDR R9, [R9]

    @ Restaura os parametros passados para a funcao por registradores
    PARAM_RS_0:
        LDR R0, [SP, #20]
        LDR R1, [SP, #24]
        LDR R2, [SP, #28]
        LDR R3, [SP, #32]
        LDR R4, [SP, #36]           @ Parametro execedente (quarto em diante), carregado sem ter sido guardado pela propria funcao

    DATA_A_SET_0:
        MOV R10, #0b0000            @ Codigo de escrever no banco de registradores (WBR)
        LSL R11, R0, #4             @ Desloca o registrador para seu offset final
        ADD R10, R10, R11           @ Soma o codigo com o endereco do sprite
        STR R10, [R9, #DATA_A]      @ Guarda o valor dos parametros da instrucao WSM que vao em DATA A

    DATA_B_SET_0:
        MOV R10, R1                 @ Offset do sprite
        LSL R11, R3, #9             @ Desloca a posicao y do sprite para seu offset final
        ADD R10, R10, R11           @ Soma para a instrucao
        LSL R11, R2, #19            @ Desloca a posicao x do sprite para seu offset final
        ADD R10, R10, R11           @ Soma para a instrucao
        LSL R11, R4, #29            @ Desloca o valor sp do sprite para seu offset final
        ADD R10, R10, R11           @ Soma para a instrucao
        STR R10, [R9, #DATA_B]      @ Guarda o valor dos parametros da instrucao DP que vao em DATA B

    VERIFY_0:
        BL VERIFICAR_FILA

    DATA_SEND_0:
        MOV R11, #1                 @ Sinal de start
        STR R11, [R9, #WRREG]       @ Manda o sinal
        MOV R11, #0                 @ Sinal de parada
        STR R11, [R9, #WRREG]       @ Manda o sinal

    @ Restaura os valores originais dos registradores utilizados pelo sistema
    REG_RS_0:
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #36             @ Adiciona a quantidade de offset necessaria no registrador SP
    
    END_0:
        BX LR                       @ Finaliza funcao


@ Argumentos: R0 = COR BGR
@ Retorna: void
WBR_BACKGROUND:
    
    @ Salva os valores originais dos registradores utilizados pelo sistema
    REG_ST_1:
        SUB SP, SP, #24             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R4, [SP, #4]
        STR R5, [SP, #8]
        STR R6, [SP, #12]
        STR R7, [SP, #16]
    @ Salva os parametros passados para a funcao por registradores
    PARAM_ST_1:
        STR R0, [SP, #20]

    @ Restaura os parametros passados para a funcao por registradores
    PARAM_RS_1:
        LDR R0, [SP, #20]

    @Pega o mapeamento feito
    LDR R1, =endereco_mapeado
    LDR R1, [R1]

    DATA_A_SET_1:
        MOV R10, #0b0000            @ Codigo de escrever no banco de registradores (WBR)
        STR R10, [R1, #DATA_A]      @ Guarda o valor dos parametros da instrucao WBR que vao em DATA A

    DATA_B_SET_1:
        STR R0, [R1, #DATA_B]       @ Guarda o valor dos parametros da instrucao WBR que vao em DATA B (cor BGR)

    VERIFY_1:
        BL VERIFICAR_FILA

    DATA_SEND_1:
        MOV R11, #1                 @ Sinal de start
        STR R11, [R1, #WRREG]       @ Manda o sinal
        MOV R11, #0                 @ Sinal de parada
        STR R11, [R1, #WRREG]       @ Manda o sinal
    
    @ Restaura os valores originais dos registradores utilizados pelo sistema
    REG_RS_1:
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #24             @ Adiciona a quantidade de offset necessaria no registrador SP

    END_1:
        BX LR                       @ Finaliza funcao


@ Argumentos: R0 = Endereco do sprite (1- 31); R1 = COR BGR;
@ Retorna: void
WSM:

    @ Salva os valores originais dos registradores utilizados pelo sistema
    REG_ST_2:
        SUB SP, SP, #28             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R4, [SP, #4]
        STR R5, [SP, #8]
        STR R6, [SP, #12]
        STR R7, [SP, #16]
    @ Salva os parametros passados para a funcao por registradores
    PARAM_ST_2:
        STR R0, [SP, #20]
        STR R1, [SP, #24]

    @Pega o mapeamento feito
    LDR R2, =endereco_mapeado
    LDR R2, [R2]

    @ Restaura os parametros passados para a funcao por registradores
    PARAM_RS_2:
        LDR R0, [SP, #20]
        LDR R1, [SP, #24]

    DATA_A_SET_2:
        MOV R10, #0b0001            @ Codigo de escrever na memoria de sprintes (WSM)
        LSL R11, R0, #4             @ Desloca o endereco do sprite para seu offset final
        ADD R10, R10, R11           @ Soma o codigo com o endereco do sprite
        STR R10, [R2, #DATA_A]      @ Guarda o valor dos parametros da instrucao WSM que vao em DATA A

    DATA_B_SET_2:
        STR R1, [R2, #DATA_B]       @ Guarda o valor dos parametros da instrucao DP que vao em DATA B (cor BGR)

    VERIFY_2:
        BL VERIFICAR_FILA

    DATA_SEND_2:
        MOV R11, #1                 @ Sinal de start
        STR R11, [R2, #WRREG]       @ Manda o sinal
        MOV R11, #0                 @ Sinal de parada
        STR R11, [R2, #WRREG]       @ Manda o sinal

    @ Restaura os valores originais dos registradores utilizados pelo sistema
    REG_RS_2:
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #28             @ Adiciona a quantidade de offset necessaria no registrador SP
    
    END_2:
        BX LR                       @ Finaliza funcao


@ Argumentos: R0 = indice x do bloco do background (0-79); R1 = indice y do bloco do background (0-59); R2 = COR BGR;
@ Retorna: void
WBM:
    
    @ Salva os valores originais dos registradores utilizados pelo sistema
    REG_ST_3:
        SUB SP, SP, #32             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R4, [SP, #4]
        STR R5, [SP, #8]
        STR R6, [SP, #12]
        STR R7, [SP, #16]
    @ Salva os parametros passados para a funcao por registradores
    PARAM_ST_3:
        STR R0, [SP, #20]
        STR R1, [SP, #24]
        STR R2, [SP, #28]
    
    @Pega o mapeamento feito
    LDR R3, =endereco_mapeado
    LDR R3, [R3]

    @ Restaura os parametros passados para a funcao por registradores
    PARAM_RS_3:
        LDR R0, [SP, #20]
        LDR R1, [SP, #24]
        LDR R2, [SP, #28]

    SQR_INDEX:
        MOV R9, #80                 @ Tamanho da linha (numero de colunas por linha)
        MUL R10, R9, R1             @ Multiplica pelo indice da posicao y
        ADD R11, R10, R0            @ Soma com o indice da posicao x

    DATA_A_SET_3:
        MOV R10, #0b0010            @ Codigo de escrever na memoria de background (WBM)
        LSL R11, R11, #4            @ Desloca o indice do poligono para seu offset final
        ADD R10, R10, R11           @ Soma o codigo com o indice do poligono
        STR R10, [R3, #DATA_A]      @ Guarda o valor dos parametros da instrucao DP que vao em DATA A

    DATA_B_SET_3:
        STR R2, [R3, #DATA_B]            @ Guarda o valor dos parametros da instrucao DP que vao em DATA B (cor BGR)

    VERIFY_3:
        BL VERIFICAR_FILA

    DATA_SEND_3:
        MOV R11, #1                 @ Sinal de start
        STR R11, [R3, #WRREG]       @ Manda o sinal
        MOV R11, #0                 @ Sinal de parada
        STR R11, [R3, #WRREG]       @ Manda o sinal
    
    @ Restaura os valores originais dos registradores utilizados pelo sistema
    REG_RS_3:
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #32             @ Adiciona a quantidade de offset necessaria no registrador SP

    END_3:
        BX LR                       @ Finaliza funcao


@ Argumentos: R0 = posicao x; R1 = posicao y; R2 = COR BGR; R3 = forma; R4 = tamanho
@ Retorna: void
DP:
    @ Salva os valores originais dos registradores utilizados pelo sistema
    REG_ST_4:
        SUB SP, SP, #36             @ Subtrai a quantidade de offset necessaria no registrador SP
        STR LR, [SP, #0]
        STR R4, [SP, #4]
        STR R5, [SP, #8]
        STR R6, [SP, #12]
        STR R7, [SP, #16]
    @ Salva os parametros passados para a funcao por registradores
    PARAM_ST_4:
        STR R0, [SP, #20]
        STR R1, [SP, #24]
        STR R2, [SP, #28]
        STR R3, [SP, #32]

    @Pega o mapeamento feito
    LDR R9, =endereco_mapeado
    LDR R9, [R9]

    @ Restaura os parametros passados para a funcao por registradores
    PARAM_RS_4:
        LDR R0, [SP, #20]
        LDR R1, [SP, #24]
        LDR R2, [SP, #28]
        LDR R3, [SP, #32]
        LDR R4, [SP, #36]           @ Parametro execedente (quarto em diante), carregado sem ter sido guardado pela propria funcao

    DATA_A_SET_4:
        MOV R10, #0b0011            @ Codigo de definir forma (DP)
        LDR R11, =SQR_POL           @ Pega o endereco da variavel
        LSL R11, R11, #4            @ Adapta o o endereco para a soma
        ADD R10, R10, R11           @ Soma com endereco
        STR R10, [R9, #DATA_A]      @ Guarda o valor da instrução na memória de DATA A

    DATA_B_SET_4:
        MOV R10, #0                 @ Valor inicial da soma
        ADD R10, R10, R0            @ Soma com x
        LSL R11, R1, #9             @ Adapta o valor de y para a soma
        ADD R10, R10, R11           @ Soma com y
        LSL R11, R4, #18            @ Adapta o valor do tamanho para a soma
        ADD R10, R10, R11           @ Soma com tamanho
        LSL R11, R2, #22            @ Adapta o valor BRG para a soma
        ADD R10, R10, R11           @ Soma com BRG
        LSL R11, R3, #31            @ Adapta o valor da forma para a soma
        ADD R10, R10, R11           @ Soma com forma
        STR R10, [R9, #DATA_B]      @ Guarda o valor da instrução na memória de DATA B

    VERIFY_4:
        BL VERIFICAR_FILA

    DATA_SEND_4:
        MOV R11, #1                 @ Sinal de start
        STR R11, [R9, #WRREG]       @ Manda o sinal
        MOV R11, #0                 @ Sinal de parada
        STR R11, [R9, #WRREG]       @ Manda o sinal

    REG_RS_4:
        @ Restaura os valores originais dos registradores utilizados pelo sistema
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #36             @ Adiciona a quantidade de offset necessaria no registrador SP

END_4:
    BX LR                           @ Finaliza funcao

RDBT:

    @ Salva os valores originais dos registradores utilizados pelo sistema
    SUB SP, SP, #20
    STR LR, [SP, #0]
    STR R4, [SP, #4]
    STR R5, [SP, #8]
    STR R6, [SP, #12]
    STR R7, [SP, #16]

    @Pega o mapeamento feito
    LDR R9, =endereco_mapeado
    LDR R9, [R9]

    LDR R0, [R9, #KEYS_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)

    MOV R1, #0b1111                 @ 15 utilizado para operacoes logicas (todos os 4 primeiros bits sao 1)
    EOR R0, R0, R1                  @ Inverte os bits dos botoes (4 primeiros), na medida em que todos os 4 primeiros bits de R1 sao 1
    AND R0, R0, R1                  @ Descarta os valores que possam estourar acima de 4 bits

    @ Restaura os valores originais dos registradores utilizados pelo sistema
    LDR LR, [SP, #0]
    LDR R4, [SP, #4]
    LDR R5, [SP, #8]
    LDR R6, [SP, #12]
    LDR R7, [SP, #16]
    ADD SP, SP, #20

    BX LR                           @ Finaliza funcao

TNLD:

    @ Salva os valores originais dos registradores utilizados pelo sistema
    SUB SP, SP, #20
    STR LR, [SP, #0]
    STR R4, [SP, #4]
    STR R5, [SP, #8]
    STR R6, [SP, #12]
    STR R7, [SP, #16]

    @Pega o mapeamento feito
    LDR R9, =endereco_mapeado
    LDR R9, [R9]

    CMP R0, #0
    BEQ STR_HEX_0
    CMP R0, #1
    BEQ STR_HEX_1
    CMP R0, #2
    BEQ STR_HEX_2
    CMP R0, #3
    BEQ STR_HEX_3
    CMP R0, #4
    BEQ STR_HEX_4
    CMP R0, #5
    BEQ STR_HEX_5
    
    STR_HEX_0:
        STR R1, [R9, #HEX0_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)
        B END_LED
    STR_HEX_1:
        STR R1, [R9, #HEX1_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)
        B END_LED
    STR_HEX_2:
        STR R1, [R9, #HEX2_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)
        B END_LED
    STR_HEX_3:
        STR R1, [R9, #HEX3_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)
        B END_LED
    STR_HEX_4:
        STR R1, [R9, #HEX4_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)
        B END_LED
    STR_HEX_5:
        STR R1, [R9, #HEX5_BASE]        @ Carrega o valor dos botoes para R0 (Registro de retorno)

    END_LED:
        @ Restaura os valores originais dos registradores utilizados pelo sistema
        LDR LR, [SP, #0]
        LDR R4, [SP, #4]
        LDR R5, [SP, #8]
        LDR R6, [SP, #12]
        LDR R7, [SP, #16]
        ADD SP, SP, #20

        BX LR                           @ Finaliza funcao


.data
    ALT_LWFPGASLVS_OFST:    .word   0xff200
    pagingfolder:           .asciz  "/dev/mem"
    SQR_POL:                .byte
    endereco_mapeado:       .space 4
    FD:                     .space 4
    
