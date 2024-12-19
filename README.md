# Shooter dos cria
Shooter dos cria é um jogo de batalha espacial no estilo shooter que foi feito utilizando a biblioteca gráfica desenvolvida anteriormente para um processador gráfico embarcado na plataforma DE1-SOC.
Nele, a terra é invadida por seres extraterrestres em naves esféricas. Dois astronautas são encarregados de usar a mais alta tecnologia do planeta para eliminar os invasores através de suas naves lançadoras de mísseis.

## Como Jogar

O jogo foi desenvolvido para uma plataforma DE1-SoC FPGA com sistema operacional Linux, e necessita de compilador GCC devidamente instalado e configurado para execução de comandos diretamente do terminal.
- Copie o diretório `src` e o arquivo `makefile` (branch "release") para uma pasta de sua escolha.
- Com o compilador GCC instalado e configurado, insira o comando `make all` para compilar o programa.
- Caso a aplicação tenha sido compilada com êxito, então insira o comando `sudo ./game` para executar o jogo com as permissões necessárias para SO Linux.

## Jogabilidade

O jogador 1 controla a nave magenta através da rotação da placa DE1-SOC, fazendo uso do acelerômetro do dispositivo. Além disso, o jogador 1 pode tirar mísseis e controlar o estado de jogo por meio dos botões da placa. O jogador 2 controla a nave cinza em formato de pinguim através do movimento do mouse; Pode atirar mísseis através do botão esquerdo do mouse.

Durante a execução do jogo, inimigos são gerados no canto superior da tela e se deslocam de forma autônoma para o canto inferior. O objetivo do jogador deve ser eliminar os inimigos e acumular a maior quantidade possível de pontos evitando esbarrar nos inimigos; Caso isso aconteça, o jogador é eliminado, e caso ambos os jogadores sejam eliminados, o jogo é perdido.

<img src="https://github.com/user-attachments/assets/7485b9bc-31a6-4715-b8c6-df57bbc80b9c" width="700">

<img src="https://github.com/user-attachments/assets/650e2f06-76cf-46f4-a525-4286cc806e8d" width="700">

<img src="https://github.com/user-attachments/assets/2e8c43e8-5384-42a4-9e6c-c72b8634945b" width="700">

<img src="https://github.com/user-attachments/assets/054c1f94-24d7-4fec-bfba-c9cb1d899334" width="700">


## Recursos Utilizados
- **Equipamento:**
  - [Placa DE1-SoC FPGA (Cortex A9 - ARMv7)](https://www.terasic.com.tw/cgi-bin/page/archive.pl?Language=English&No=836)[ (Manual)](https://drive.google.com/file/d/1HzYtd1LwzVC8eDobg0ZXE0eLhyUrIYYE/view)
- **Ferramentas de programação:**
  - [GCC: Coleção de Compiladores GNU - 11.4.0 (2023)](https://gcc.gnu.org/gcc-11/)
  - [VSCode: Visual Studio Code IDE - 1.90.0 (2024)](https://code.visualstudio.com/updates/v1_90)
- **Softwares de edição gráfica:**
  - [Piskel Web App](https://www.piskelapp.com/)
