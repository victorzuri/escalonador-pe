/* ********************************************************************* */
/* Disciplina: Estruturas de Dados 2                                     */
/* Professor:André                                                       */ 
/* Objetivo de Programa: Interface da TAD Fila (de float)                */
/* Tópico da Disciplina: Estrutura de Dados do Tipo Fila                 */
/* ********************************************************************* */

/* Estrutura de Dados que armazena a Fila*/
typedef struct fila Fila;

/* Função que cria a Fila*/
Fila* cria (void);

/* Procedimento Inserir na Fila */
void insere (Fila* f, int v);

/* Função Retirar da Fila */
int retira (Fila* f);

/* Função que verifica se a Fila está vazia*/
int vazia (Fila* f);

/* Procedimento para liberar a área de memória reservada para a Fila*/
void libera (Fila* f);

/* Função que retorna o tamanho da Fila */
int tamanho(Fila* p);

/* Listar elementos da Fila */
void imprime(Fila* p);
