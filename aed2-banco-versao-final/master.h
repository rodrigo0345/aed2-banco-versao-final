#pragma once
#pragma warning(disable:4996)
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

/* usado para detetar memory leaks no visual studio 2022 */
#include <crtdbg.h> 

#include "master.h"
#include "structs.h"

#define LOG_WARNING(msg) printf("\nAviso: %s\n", msg);

/* menu principal do programa */
void Menu_MainLoop(Clientes** clts, Contas** cnts, uint* clts_size, uint* cnts_size);

/* --- Clientes --- */

/* Retorna um novo cliente com as variaveis iniciadas corretamente */
Clientes* LinkedList_New_Clientes();

/* Adiciona uma nova "node" ao inicio da lista ligada */
void LinkedList_AppendHead_Clientes(Clientes** lista, Clientes elemento);

/* Elimina uma "node" da lista ligada que � referenciada tendo em conta o id do cliente */
uint LinkedList_RemoveNode_Clientes(Clientes** lista, Contas** cnts, uint id);

/* Encontra uma "node" da lista ligada tendo em conta o id do cliente e usando a t�cnica de pesquisa bin�ria */
Clientes* LinkedList_BinarySearch_Clientes(Clientes* listHead, uint id);

/* Liberta a memoria usada pela lista ligada */
void LinkedList_Delete_Clientes(Clientes** head_ref);

/* Metodo usado com alguma frequencia que serve para mostrar ao utilizador todas as contas associadas ao cliente */
uint LinkedList_ShowContas_Clientes(Clientes* cliente, Contas** cnts);

/* (RemCAC = Remove Contas Associadas ao Cliente) Responsavel por eliminar todas as contas que pertencam a um dado cliente */
void LinkedList_RemCAC_Clientes(Clientes* cliente_removido, Contas** cnts);

void LinkedList_Reverse_Cliente(Clientes** head_ref);

/* --- Contas --- */

/* Retorna uma nova conta com as variaveis iniciadas corretamente */
Contas* LinkedList_New_Contas();

/* Adiciona uma nova "node" ao inicio da lista ligada */
void LinkedList_AppendHead_Contas(Contas** lista, Contas elemento);

/* Elimina uma "node" da lista ligada que � referenciada tendo em conta o id da conta */
uint LinkedList_RemoveNode_Contas(Contas** lista, uint id);

/* Encontra uma "node" da lista ligada tendo em conta o id da conta e usando a t�cnica de pesquisa bin�ria */
Contas* LinkedList_BinarySearch_Contas(Contas* listHead, uint id);

/* Liberta a memoria usada pela lista ligada */
void LinkedList_Delete_Contas(Contas** head_ref);

/* Metodo usado quando ja temos uma variavel a apontar para a "node" que desejamos remover */
uint LinkedList_RemoveAlreadyKnownNode_Contas(Contas** lista, Contas** known_node);

void LinkedList_Reverse_Conta(Contas** head_ref);

/* Caso seja ativado o modo debug, ir� dar output ao ficheiro e � linha onde ocorreu o problema e ir� encerrar o programa */
void Security_Error(const char* file, const long line);

/* Liberta a memoria usada pelas linked lists mais importantes do programa "clts" e "cnts" */
void Security_ProgramExit_Global(Clientes* clts, Contas* cnts);

/* scanf personalizado usado para ser mais eficaz perante inputs inesperados do utilizador */
void Security_Input_Int(char variable[], int* store);

/* Garante que o valor da variavel e maior que zero e menor ou igual que o "Max" */
int Security_Validation_UInt(uint Input, uint Max);

/* Garante que a string nao possui carateres especiais nem numeros */
uint Security_CheckForDigits_String(char* string);

/* Encripta a string passada como argumento, porem, nao e muito eficaz */
void Security_Encrypt_String(char frase[]);

/* Permite ao utilizador efetuar login no seu cliente */
uint Security_Login(Clientes** clts, Clientes** result, char* guess, uint* id);

/* Ferramenta de debugging acessada pelo terminal */
void Security_Flags(char* argv[]);

/* Move os dados dos utilizadores dos ficheiros .csv para as listas ligadas */
void Files_LoadMemory(Clientes** clts, Contas** cnts, uint* clts_size, uint* cnts_size);

/* Mostra ao utilizador algumas informco~es iniciais sobre a nossa aplicaca~o */
void introducao();

/* Garante que a data introduzida pelo utilizador e� maior que o ano 1800 e que de facto e� valida */
unsigned short Time_CheckInputDate_Int(int Day, int Month, int Year);

/* Retorna a data atual em formato string */
char* time_str();

/* tem como input uma string e troca um carater dessa string por outra string */
void Security_Replace_Char(char* s, char ch, char repl);

void DevTools_Options();

void Files_LoadMemory(Clientes** clts, Contas** cnts, uint* clts_size, uint* cnts_size);
void Files_SaveMemory(Clientes** clts, Contas** cnts);


/* --- dialogo --- */

enum dialogos { /* organiza as falas com os utilizadores*/
	MenuInicial = 1, 
	CriarNovoUtilizador,
	IntroduzirNome, 
	CodigoDeAcesso,
	DataDeNascimento,
	Localidade,
	EditarClientes,
	Selecao,
	ConsultarCliente,
	Dev,
	ClienteSemContas, 
	IndiqueLocalidade,
	ConsultarConta, 
	TiposDeContas,
	LocalidadeInvalida, 
	SemClientes,
	SemContasComSNegativo, 
	SelecioneIDConta,
	OpcaoInvalida = 20,
	CodigoInvalido,
	DataInvalida,
	ContaCriadaSucesso,
	NomeInvalido,
	OperacaoConcluida,
	IDInvalido,
	SelecioneOpcao,
	SemContas,
	RemoverCliente,
	ClienteRemovidoSucesso,
	Montante,
	MontanteInvalido,
	SemMovimentos,
};

/* Comandos disponiveis:
	- MenuInicial
	- CriarNovoUtilizador
	- IntroduzirNome
	- CodigoDeAcesso
	- DataDeNascimento
	- Localidade
	- EditarClientes
	- Selecao
	- ConsultarCliente
	- Dev
	- ClienteSemContas
	- IndiqueLocalidade
	- ConsultarConta 
	- TiposDeContas
	- LocalidadeInvalida
	- SemClientes
	- SemContasComSNegativo
	- SelecioneIDConta
	- OpcaoInvalida
	- CodigoInvalido
	- DataInvalida 
	- ContaCriadaSucesso
	- NomeInvalido
	- OperacaoConcluida
	- IDInvalido 
	- SelecioneOpcao
	- SemContas
	- RemoverCliente
	- ClienteRemovidoSucesso
	- Montante
	- MontanteInvalido
	- SemMovimentos
*/
void dialogo(int id);

/* Stack dos movimentos */
Movimentos* Stack_Create_Movimentos(uint id_conta);
void Stack_Push_Movimentos(Movimentos** s, Movimentos* d);
void Stack_Show_Movimentos(Movimentos* s);