#include <stdio.h>
#include "erro.h"
#include <string.h>

#define MAX_SIZE 1024

int sequencia_nao_contem_so_As_e_Bs ();
int nao_tem_so_um_argumento ();
int cmd_seq ();
int ja_existe_sequencia ();

struct {
  int tamanho;
  char seq[MAX_SIZE];
} estado;

void guarda_sequencia(char *arg) {
	strcpy(estado.seq, arg);
	estado.tamanho = strlen(arg);
}

char *obtem_sequencia() {
	return estado.seq;
}

int interpretar(char *linha) {
    char comando[MAX_SIZE];
    char args[MAX_SIZE];
    int nargs;
    nargs = sscanf(linha, "%s %[^\n]", comando, args);

    /* Comando seq com argumentos */
    if(strcmp(comando, "seq") == 0 && nargs == 2)
        return cmd_seq(args);
    /* Comando seq sem argumentos */
    else if(strcmp(comando, "seq") == 0 && nargs == 1)
        return cmd_seq(NULL);
    /* Comando sair */
    else if(strcmp(comando, "sair") == 0) {
        return 0;
    } else {
        /* Como não é nenhum dos comandos anteriores, devolve o erro correspondente */
        return mensagem_de_erro(E_COMMAND);
    }
}

void interpretador() {
    int resultado = 0;
    char buffer[MAX_SIZE];
    int ciclo = 1;
    while(ciclo &&
      fgets(buffer, MAX_SIZE, stdin) != NULL){
        resultado = interpretar(buffer);
        if(resultado == 0)
            ciclo = 0;
    }
}

int main() {
	estado.tamanho = -1;

    interpretador();
    return 0;
}

int cmd_seq(char *args) {
    if(args != NULL) {
        if(nao_tem_so_um_argumento(args))
             return mensagem_de_erro(E_ARGS);
        else if(sequencia_nao_contem_so_As_e_Bs(args))
             return mensagem_de_erro(E_SEQ_INV);
        else
             guarda_sequencia(args);
             return 1;
    } else {
        if(ja_existe_sequencia()) {
             printf("%s\n", obtem_sequencia());
             return 1;
        } else {
             return mensagem_de_erro(E_NO_SEQ);
         }
    }
}

int ja_existe_sequencia (){
   if (estado.seq == NULL) return 1;
   else return 0;
}



int nao_tem_so_um_argumento (char *args){
    int i;
    i=0;
    while (args[i]!='\0'){
         if (args[i]==' ') return 1;
         else i++;
         }
    return 0;
}

int sequencia_nao_contem_so_As_e_Bs (char *args){
 int i;
 for (i=0;args[i]!='\0';i++){
     if (args[i]!='A' && args[i]!='B') return 1; 
     }
 return 0;
}
