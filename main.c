#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <poll.h> 
#include <fcntl.h> 
#include <errno.h>
#include <string.h>
#define tam 10
typedef struct
{
  char palavra[20];
} palavras [tam]; 
//Assinatura das funções
int getch(void);
void perder();
void ganhar();
void creditos();
void arquivo(int *score_jogo, char nome[30]);
void ler (palavras *pergunta);
void ler2 (palavras *pergunta2, int *timer);
void comparar (palavras *pergunta, palavras *pergunta2, int *timer);
void printar (palavras pergunta);
void mapa(int linha, int coluna);
void escolhaf(int correta, int *escolha, int *contvida);
void pergunta(int contperg, int *dadonumero, int *controle_dado );
void menu(char *escolha);
void instruções();
void jogar(int *dadonum);
void jogo();

int main(void) {
  char escolha,resp,start,nome[20],Linha[100],*result, retornar;
  int controle = 0, controlearq = 0;
  system("clear");
  menu(&escolha);
  while(controle != 1){
  switch(escolha){
	  case 'p': //jogo
      system("clear");
      jogo();
      controle = 1;
    break;
    case 'i': //instruções
      instruções();
      getch();
			printf("Pressione qualquer tecla para voltar ao menu: \n");
   
      start = getch();
      system("clear");
      printf("Voltando ao menu...\n");
      sleep(1);
      system("clear");
      menu(&escolha);
    break;
    case 's': //sair
      system("clear");
      printf("\nSentimos muito :/\n");
      printf("\n:( esperamos que você volte!");
      printf("\nObrigado, até uma próxima vez!\n\n\n");
      sleep(3);
      creditos(); 
      controle = 1;
		break;
		case 'h': //histórico de partidas anteriores
			system("clear");
      controlearq = 0; //variável para resolver o problema do criterio de parada do while
      FILE *arq; 
			arq = fopen("score.txt","rt");
      while (!feof(arq) && controlearq == 0){
        result = (fgets(Linha, 100, arq));
      //  if(result){   
	        printf(" %s\n",Linha);
     /*   }
        else if(result == (NULL)) {
          controlearq = 3;
        }*/
      }
      fclose(arq);
      printf("\n==========================================");
      printf("\nPressione qualquer tecla para voltar ao menu: ");
      getch();
      retornar = getch();
      system("clear");
      printf("Voltando ao menu...\n\n\n\n");
      sleep(1);
      system("clear");
      menu(&escolha);
    break;
    //caso tecla inválida
    default:
      system("clear");
      printf("Pressione alguma tecla válida!\n\n");
      sleep(2);
      system("clear");
      menu(&escolha);
    break;
  }
  }
  return 0;
}
//Menu do jogo
void menu(char *escolha){ 
  printf("======================= University Run =======================\n\n");
  printf("Pressione a tecla correspondente para realizar a ação desejada\n\n");
  printf("[p] Iniciar o jogo\n");
  printf("[i] Instruções\n");
	printf("[h] Histórico\n");
  printf("[s] Sair do jogo\n");
  printf("\n==============================================================\n");
  scanf(" %c", escolha);
}
//////////////////// Instruções do jogo
void instruções(){ 
      system("clear");
      printf("============================= COMANDOS ============================\n\n");
      printf("• [d] para jogar o dado\n\n");
      printf("============================ INSTRUÇÕES ===========================\n\n");
      printf("• O jogador lançará um dado e percorrerá um número de casas no tabuleiro correspondente ao número sorteado no dado; \n");
			printf("• O jogador começará com três vidas e a cada resposta incorreta, uma vida será perdida. Caso sejam esgotadas, será fim de jogo;\n");
			printf("• Cada desafio é único! \n");
      printf("• O jogo terminará quando o jogador concluir os desafios e chegar ao fim do tabuleiro. \n\n");
      printf("===================================================================\n\n");}

/////////////////////// Função para ler sem apertar enter
int getch(void) 
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
/////////////////////// O jogo em si
void jogo(){
  int score;
  time_t time_ini,time_fim;
  char nome[30];
  int contdado=0,dadonum=0,controle_dado = 0;
  printf("==================================================");
  printf("\n\n          Olá jogador, qual o seu nome?\n ");
  printf("\n==================================================\n");
  scanf(" %[^\n]",nome);
  system("clear");
  printf("==================================================");
  printf("\n\n        Bem vindo %s\n\n",nome);
  printf("==================================================\n\n");
  sleep(2);
  system("clear");
  time_ini = time(NULL);
  mapa(29,2);
  while (contdado<16){
  printf("Dado: %d",dadonum);
  jogar(&dadonum);
  srand(time(NULL));
  dadonum = rand()%(6)+1;
  contdado += dadonum;
  controle_dado++;
  pergunta(contdado,&dadonum,&controle_dado);
	}
  time_fim = time(NULL);
  score = difftime(time_fim, time_ini);
  arquivo(&score,nome);
  }
//////////////////// Função para jogar o dado
	void jogar(int *dadonum){
	char jogar_dado;
		printf("\nPressione [d] para jogar o dado ---> ");
    getch();
    jogar_dado = getch();
		while(jogar_dado != 'd'){
      system("clear");
			printf("Pressione [d] para jogar o dado");
			scanf( " %c",&jogar_dado);
		}    
}
////////////////// Função para as perguntas e desafios do jogo
void pergunta(int contperg, int *dadonumero, int *controle_dado ){
int escolha,cont_vida, controle,escolhafinal=0,controlevalidf;
if (*controle_dado == 1){
  cont_vida = 3;}
switch (contperg){
  case 1:
    system("clear");
    mapa(24,2);
		printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
		printf("\nSão eventos que marcam o Segundo Reinado no Brasil (1840 – 1889):\n");
		printf("\n1) Golpe da Maioridade e Noite das Garrafadas.");
		printf("\n2) Guerra da Cisplatina, movimento tornou a região do Uruguai independente do Brasil.");
		printf("\n3) Início do Brasil monárquico e mudança do nome oficial do país que muda de Brasil para Império do Brasil.");
		printf("\n4) Dom Pedro II foi coroado imperador do Brasil e início da imigração no Brasil\n");
		scanf(" %d",&escolha);
		escolhaf(4,&escolha,&cont_vida);
    system("clear");
    mapa(24,2);
	break;
	case 2:
    system("clear");
		mapa(24,6);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
		system("clear");
		printf("\nO que é um cartógrafo?\n");
		printf("\n1) Pessoa que elabora mapas ou cartas geográficas");
		printf("\n2) Aparelho utilizado para confecção de mapas com precisão");
		printf("\n3) Instrumento que define a razão entre o tamanho do mapa e o que se tem na realidade");
		printf("\n4) Funcionário do IBGE responsável por coletar estatísticas\n");
		scanf(" %d",&escolha);
		escolhaf(1,&escolha,&cont_vida);
    system("clear");
    mapa(24,6);
	break;
  case 3:
    system("clear");
    mapa(24,10);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
		printf("\nComo podemos definir um Algoritmo?\n");
		printf("\n1) Sequência de comandos ordenados, infinitos e ambíguos que são empregados para executar uma tarefa.");
		printf("\n2) Sequência de instruções ordenadas, infinitas e não-ambíguas que são empregadas para executar uma tarefa.");
		printf("\n3) Sequência de instruções ordenadas, finitas e não-ambíguas que são empregadas para executar uma tarefa.");
		printf("\n4) Sequência de comandos ordenados, infinitos e não-ambíguos que são empregados para executar uma tarefa\n");
		scanf(" %d",&escolha);
		escolhaf(3,&escolha,&cont_vida);
    system("clear");
    mapa(24,10);
	break;
  case 4:
    system("clear");
    mapa(24,14);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
		system("clear");
		printf("\nAna tem 12 anos e flavia tem o dobro da idade da ana, e jorge tem o dobro da idade de flavia. Qual a idade de jorge?\n");
		printf("\n1) 48");
		printf("\n2) 98");
		printf("\n3) 22");
		printf("\n4) 38\n");
		scanf(" %d",&escolha);
		escolhaf(1,&escolha,&cont_vida);
    system("clear");
    mapa(24,14);
	break;
  case 5: 
    system("clear");
		mapa(26,20);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
		system("clear");
		printf("\nUm país da Europa Ocidental se envolveu em discussões internas sobre separatismo entre as suas duas principais regiões: Flandres, ao norte, e Valônia, ao Sul. Qual é esse país?\n");
		printf("\n1) Ucrânia");
		printf("\n2) Suíça");
		printf("\n3) Bélgica");
		printf("\n4) Espanha\n");
		scanf(" %d",&escolha);
		escolhaf(3,&escolha,&cont_vida);
    system("clear\n");
    mapa(26,20);
	break;
  case 6:
    system("clear");
		mapa(25,25);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
		system("clear");
		printf("\nO que representa a função a seguir: x^2+2x+5 = 0\n");
		printf("\n1) Parábola");
		printf("\n2) Elipse");
		printf("\n3) Quadrado perfeito");
		printf("\n4) Reta\n");
		scanf(" %d",&escolha);
		escolhaf(1,&escolha,&cont_vida);
    system("clear");
    mapa(25,25);
	break;
  case 7:
    system("clear");
		mapa(22,25);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
  	printf("\nQuem descobriu o Brasil?\n");
  	printf("\n1) John Lennon");
  	printf("\n2) Manuel Bandeira");
  	printf("\n3) Pedro Álvares Cabral");
  	printf("\n4) Mano Brown\n");
		scanf(" %d",&escolha);
		escolhaf(3,&escolha,&cont_vida);
    system("clear");
    mapa(22,25);
  break;
  case 8:
    system("clear");
		mapa(18,25);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
  	printf("\nQuantas casas decimais tem o número pi?\n");
  	printf("\n1) Duas");
  	printf("\n2) Centenas");
  	printf("\n3) Infinitas");
  	printf("\n4) milhões\n");
		scanf(" %d",&escolha);
		escolhaf(3,&escolha,&cont_vida);
    system("clear");
    mapa(18,25);
  break;
  case 9:
    system("clear");
		mapa(14,25);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
    printf("\nQual personagem folclórico costuma ser agradado pelos caçadores com a oferta de fumo?\n");
    printf("\n1) Caipora");
    printf("\n2) Saci");
    printf("\n3) Lobisomem");
    printf("\n4) Boitatá\n");
		scanf(" %d",&escolha);
		escolhaf(1 ,&escolha,&cont_vida);
    system("clear");
    mapa(14,25);
  break;
  case 10:
    system("clear");
		mapa(10,21);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
    printf("\nSegundo a Mitologia Grega, quem é o Rei dos Deuses?\n");
    printf("\n1)Poseidon");
    printf("\n2)Apolo");
    printf("\n3)Cronos");
    printf("\n4)Zeus\n");
		scanf(" %d",&escolha);
		escolhaf(4,&escolha,&cont_vida);
    system("clear");
    mapa(10,21);
  break;
  case 11:
    system("clear");
		mapa(16,20);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d",cont_vida);
    sleep(3);
    system("clear");
    printf("\nQual o menor país do mundo?\n");
    printf("\n1) Vaticano");
    printf("\n2) Itália");
    printf("\n3) Russia ");
    printf("\n4) Peru\n");
		scanf(" %d",&escolha);
		escolhaf(1,&escolha,&cont_vida);
    system("clear");
    mapa(16,20);
  break;
  case 12:
    system("clear");
		mapa(17,16);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d", cont_vida);
    sleep(3);
    system("clear");
    printf("\nQual foi a corrente de pensamento que influenciou a revolução francesa?\n");
    printf("\n1) Racionalismo");
    printf("\n2) Niilismo");
    printf("\n3) Iluminismo");
    printf("\n4) Existencialismo\n");
		scanf(" %d",&escolha);
		escolhaf(3,&escolha,&cont_vida);
    system("clear");
    mapa(17,16);
  break;
  case 13:
    system("clear");
		mapa(17,10);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d", cont_vida);
    sleep(3);
    system("clear");
    printf("\nQual o quadrado de 2, somado ao cubo de 2, subtraído do quadrado de 3?\n");
    printf("\n1) 2");
    printf("\n2) 3");
    printf("\n3) -1");
    printf("\n4) -2\n");
		scanf(" %d",&escolha);
		escolhaf(2,&escolha,&cont_vida);
    system("clear");
    mapa(17,10);
  break;
  case 14:
    system("clear");
		mapa(16,5);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d", cont_vida);
    sleep(3);
    system("clear");
    printf("\nEm que século o continente europeu foi devastado pela peste bubônica?\n");
    printf("\n1) No século X");
    printf("\n2) No século XI");
    printf("\n3) No século XIII");
    printf("\n4) No século XIV\n");
		scanf(" %d",&escolha);
		escolhaf(4,&escolha,&cont_vida);
    system("clear");
    mapa(16,5);
  break;
  case 15:
		system("clear");
		mapa(11,3);
    printf("Dado: %d",*dadonumero);
    printf("  Vidas: %d", cont_vida);
    sleep(3);
    system("clear");
		printf("\nO que é cariótipo?");
		printf("\n1) Pigmento amarelo existente nas plantas");
		printf("\n2) Coleção de genes que formam um indivíduo");
		printf("\n3) Tipos de cáries que aparecem nos dentes");
		printf("\n4) Um tipo de vitamina C\n");
		scanf(" %d",&escolha);
		escolhaf(2,&escolha,&cont_vida);
    system("clear");
    mapa(11,3);
  break;
  default:{
	system("clear");
	mapa(6,9);
  sleep(3);
  system("clear");
  printf("Você chegou ao final do jogo!!!\n\n");
  while (controlevalidf != 3){    
  printf("Escolha seu desafio final com sabedoria:\n[1]\n[2]\n");
  scanf(" %d", &escolhafinal);  
  if (escolhafinal == 1){   
  //////////////////////JOKENPO/////////////////////
  int sorteio,jogada=0,i;
  srand(time(NULL));
  sorteio = rand()%3;
  system("clear");
  printf("==========================DESAFIO FINAL==========================\n\n");
  printf("Você encontrou com Minoru na porta da faculdade e foi desafiado para jogar um jokenpo, se perder, você será cruelmente reprovado!! Boa sorte!!\n\n");
  printf(" [1] para Pedra\n [2] para Papel\n [3] para Tesoura: ");
  printf("\n\nSua escolha ----> ");
  scanf(" %d",&jogada);
  switch (sorteio){
    case 0:
      printf("Minoru ----> Pedra\n\n");
    break;
    case 1:
      printf("Minoru ----> Papel\n\n");
    break;
    case 2:
      printf("Minoru ----> Tesoura\n\n");
    break;
    }
    //////////////caso de empate//////////////
    while((sorteio == 0 && jogada == 1) || (sorteio == 1 && jogada == 2) || (sorteio == 2 && jogada == 3)){
      printf("Empate\n");
      sorteio = rand()%3;
      printf("Jogue novamente----> ");
      scanf(" %d", &escolha);
			switch (sorteio){
    		case 0:
      		printf("Minoru ----> Pedra\n\n");
   			break;
    		case 1:
      		printf("Minoru ----> Papel\n\n");
    		break;
        case 2:
          printf("Minoru ----> Tesoura\n\n");
        break;
    }}
    /////////////caso de vitória//////////////////
    if((sorteio == 0 && jogada == 2) || (sorteio == 1 && jogada == 3) || (sorteio == 2 && jogada == 1)){
      printf("Você passou para o próximo semestre!!\n\n\nParabéns jovem padawan\n\n");
      controlevalidf = 3;
      sleep(3);
      ganhar();
      creditos();}
    //////////////caso de derrota//////////////////
    else{
    controlevalidf = 3;
    printf("Você não passou no semestre!!\n\n\n");
    sleep(3);
    perder();
    creditos();
    }
  }
  else if (escolhafinal==2){
  //////////////// Desafio de digitação
    system("clear");
    printf("==================================================================\n");
    printf("=       Você caiu no teste de digitação ultra, mega, power!!     =\n");
    printf("==================================================================\n");
    printf("Digite 10 palavras aleatorias!!!\n");
    sleep(4);
    system("clear");
    int timertempos;
    palavras pergunta, pergunta2; // definindo 2 variaveis para ler as palavras 2 vezes
    ler (&pergunta); // lê a 1 vez para armazenar
    printar(pergunta);// printa na tela para o jogador digitar elas novamente
    ler2 (&pergunta2,&timertempos);// lê as palavras novamente e compara com as lidas na 1 vez
    comparar(&pergunta,&pergunta2, &timertempos);//função para comparar as palavras digitadas
    controlevalidf = 3;
  }
  else {
    controlevalidf = 0;
  }
  }
    }
    }
}
//função para validar se a resposta da função está correta e descontar as vidas
void escolhaf(int correta, int *escolha, int *contvida){
  int cont_vida = *contvida;
	while(correta != *escolha && contvida>0){
			cont_vida--;
      if(cont_vida==0){
        perder();
        creditos();
        exit(0);
      }
     *contvida = cont_vida;
      printf("Você perdeu uma vida, restam %d", cont_vida);
			printf("\nTente novamente: \n");
      scanf(" %d",&*escolha);
  }
}
//////////////////////// lê as palavras da 1 vez
void ler (palavras *pergunta)
{
    int i;
    for (i=0; i<tam; i++)
    {
    
        printf("Digite a %d palavra: ", i+1);
        scanf(" %s", *&(*pergunta)[i].palavra); 
    }    
}
////////////////////// printa as palavras digitadas na tela
void printar (palavras pergunta)
{
    int i;
    system("clear");
    for (i=0; i<tam; i++)
    {
        printf (" %dº Palavra: %s \n", i+1 ,pergunta[i].palavra);
    }
}
///////////////////////// Lê as palavras novamente digitadas para comparalas com a 1 leva
void ler2 (palavras *pergunta2, int *timer)
{
    int i;
    int tempo;
    time_t t_ini, t_fim;
    t_ini = time(NULL);
    for (i=0; i<tam; i++)
    {

        printf("Digite a %dº palavra acima: ", i+1);
        scanf(" %s", *&(*pergunta2)[i].palavra); 
    }    
    t_fim = time(NULL);
    tempo = difftime(t_fim,t_ini);
    *timer = tempo;
}
///////////////////////// compara as palavras digitadas da 1 com as da 2 vez
void comparar (palavras *pergunta, palavras *pergunta2, int *timer){
  int i,cont_erro = 0;

  for (i=0; i<tam; i++){
  if (strcmp ((*pergunta)[i].palavra, (*pergunta2)[i].palavra) == 0){   
    printf("\nVocê acertou a %d palavra!\n", i+1);
  }
  else if (strcmp ((*pergunta)[i].palavra, (*pergunta2)[i].palavra) != 0){
    cont_erro ++;
  }
  }
  if (cont_erro == 0) {  
    system("clear");
    printf("\nVocê acertou as %d palavras! e seu tempo foi de %d segundos\n", tam, *timer);
    sleep(4);
    ganhar();
    creditos();
  }

  else{
    system("clear");
    printf("\nVocê errou %d palavras! e seu tempo foi de %d segundos\n", cont_erro, *timer);
    sleep(4);
    perder();
    creditos();
  }
  }
//////////////////////////////// Função para quando ganhar o jogo
	void ganhar(){
  system("clear");
  printf("======================= University Run =======================\n");
  printf("========================VOCÊ GANHOU!!!======================== \n");
  printf("==============Parabéns por concluir com êxito ==================\n");
  printf("=========================Nosso jogo!!!!=======================\n");
  sleep(4);
}
//////////////////////////// Função para quando perder o jogo
void perder(){
  system("clear");
  printf("======================= University Run =======================\n");
  printf("========================VOCÊ PERDEU!!!======================== \n");
  printf("=============Se prepare melhor da próxima vez=================\n");
  printf("==============================================================\n");
  sleep(4);
}
////////////////////// Créditos para a equipe de desenvolvimento
void creditos(){
  system("clear");
  printf("=====================DESENVOLVIDO POR:========================\n");
  printf("==============PEDRO HENRIQUE GONÇALVES MACHADO================\n");
  printf("==============================================================\n\n\n");
  sleep(2);
  system("clear");
  printf("=====================DESENVOLVIDO POR:========================\n");
  printf("============GUILHERME HENRIQUE PEREIRA SERAFINI===============\n");
  printf("==============================================================\n\n\n");
  sleep(2);
  system("clear");
  printf("=====================DESENVOLVIDO POR:========================\n");
  printf("===================FELIPE FERREIRA ALVES======================\n");
  printf("==============================================================\n\n\n");
  sleep(2);
  system("clear");
  printf("=====================DESENVOLVIDO POR:========================\n");
  printf("==============JOÃO PEDRO MENDONÇA DOS SANTOS==================\n");
  printf("==============================================================\n\n\n");
  sleep(2);
  system("clear");
}
//// Arquivo que salva o score do jogador (tempo para finalizar)
void arquivo(int *score_jogo, char nome[30]){
  FILE *arq;
  arq = fopen("score.txt","a+");
  fprintf(arq,"\nNome: %s | Score: %d segundos",nome,*score_jogo);
  fclose(arq);
  }
//////////////////////// mapa do jogo
void mapa(int linha, int coluna){
   char mapa[30][30] = {
		//      A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   x   z AA  AB   AC  AD  
    /*L1*/{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    /*L2*/{' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L3*/{' ',' ',' ',' ','x',' ',' ','x','x','x','x','x',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L4*/{' ',' ',' ',' ','x',' ',' ','x','x','x','x','x',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L5*/{' ',' ',' ',' ','x',' ',' ','x','x','x','x','x',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L6*/{' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L7*/{' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L8*/{' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		/*L9*/{' ','x',' ',' ',' ','x','x','x','x','x','x','x','x','x','x',' ',' ','x','x','x','x','x','x','x',' ',' ',' ',' ',' '},
		/*L10*/{' ','x','x','x','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' '},
		/*L11*/{' ','x',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' '},
		/*L12*/{' ','x',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x',' ',' ',' ',' ',' ',' ','x','x',' ',' '},
		/*L13*/{' ','x',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ','x',' ',' ',' ',' ','x',' ',' ','x',' '},
		/*L14*/{' ','x',' ',' ','x','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ','x','x','x','x',' ',' ',' ','x',' '},
		/*L15*/{' ','x',' ','x',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ','x',' ','x',' ',' ',' ','x',' '},
		/*L16*/{' ','x','x',' ',' ',' ',' ','x','x','x','x','x','x','x','x','x','x','x',' ',' ',' ','x',' ','x',' ',' ',' ','x',' '},
		/*L17*/{' ','x',' ',' ',' ',' ','x',' ',' ',' ',' ',' ','x',' ',' ',' ',' ','x',' ',' ',' ','x',' ','x','x','x','x','x',' '},
		/*L18*/{' ',' ','x',' ',' ','x',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ','x',' ',' ',' ','x',' ','x',' ',' ',' ','x',' '},
		/*L19*/{' ',' ',' ','x','x',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ','x',' ',' ',' ','x',' ','x',' ',' ',' ','x',' '},
		/*L20*/{' ',' ',' ',' ','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x',' ','x',' ',' ',' ','x',' '},
		/*L21*/{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x','x','x','x',' '},
		/*L22*/{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ','x',' '},
		/*L23*/{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x',' ',' ',' ',' ',' ','x',' ',' ',' ','x',' '},
		/*L24*/{'x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ',' ','x','x',' ',' ',' ',' ','x',' ',' ',' ','x',' '},
		/*L25*/{'x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ',' ','x',' ','x','x','x','x','x','x','x','x','x',' '},
		/*L26*/{'x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ',' ','x',' ',' ',' ',' ',' ','x',' ',' ',' ','x',' '},
		/*L27*/{'x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ','x',' ',' ',' ',' ','x',' ',' ',' ',' ',' ','x',' ',' ',' ','x',' '},
		/*L28*/{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x',' ',' ',' ',' ',' ','x',' ',' ',' ','x',' '},
		/*L29*/{'x',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x','x','x','x','x','x','x','x','x','x',' '},
		/*L30*/{'x',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					};
  for (int i=0;i<30;i++){
    for(int j=0;j<30;j++){
      if (i == linha && j == coluna){
				mapa[linha][coluna]='I';
				printf(" %c",mapa[linha][coluna]);	
      }
      else{  
      printf(" %c",mapa[i][j]);
      }
  }printf("\n");}
  }