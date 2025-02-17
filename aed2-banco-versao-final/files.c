#include "master.h"
#include "structs.h"

/* Carrega as listas ligadas usadas ao longo do programa recorrendo a ficheiros .csv */
void Files_LoadMemory(Clientes** clts, Contas** cnts, uint* clts_size, uint* cnts_size)
{
	/* abrir o ficheiro */
	FILE* ficheiro = fopen("clientes.csv", "r");
	if (ficheiro == NULL)
		Security_Error(__FILE__, __LINE__);

	char line[215] = "";
	int i = 0;
	char* key;
	Clientes* tmp = LinkedList_New_Clientes();

	/* recolher o cabecalho do ficheiro .csv */
	fgets(line, 215, ficheiro);

	/* guardar as informacoes do ficheiro clientes.csv na struct "tmp" */
	while (fgets(line, 215, ficheiro) != NULL && strcmp(line, "\n"))
	{
		key = strtok(line, ";");
		tmp->id = atoi(key);

		key = strtok(NULL, ";");
		tmp->pin = malloc(sizeof(char) * 8);
		if (tmp->pin == NULL)
			Security_Error(__FILE__, __LINE__);
		strcat(key, "\0");
		strcpy(tmp->pin, key);

		key = strtok(NULL, ";");
		tmp->nome = malloc(sizeof(char) * 50);
		if (tmp->nome == NULL)
			Security_Error(__FILE__, __LINE__);
		strcat(key, "\0");
		strcpy(tmp->nome, key);

		key = strtok(NULL, ";");
		tmp->data = malloc(sizeof(char) * 15);
		if (tmp->data == NULL)
			Security_Error(__FILE__, __LINE__);
		strcat(key, "\0");
		strcpy(tmp->data, key);

		key = strtok(NULL, ";");
		tmp->morada = malloc(sizeof(char) *50);
		if (tmp->morada == NULL)
			Security_Error(__FILE__, __LINE__);
		strcat(key, "\0");
		strcpy(tmp->morada, key);

		key = strtok(NULL, ";");
		Security_Replace_Char(key, ',', '.');
		tmp->saldo_global = atof(key);

		key = strtok(NULL, ";");
		tmp->contas_associadas = malloc(sizeof(char) * 70);
		if (tmp->contas_associadas == NULL)
			Security_Error(__FILE__, __LINE__);
		if (atoi(key) == 0)
		{
			free(tmp->contas_associadas);
			tmp->contas_associadas = NULL;
		}
		else
		{
			key[strlen(key) - 1] = '\0';  /* retira o \n do final da string para facilitar a manipula��o de dados */
			strcpy(tmp->contas_associadas, key);
		}
			

		(*clts_size)++;
		LinkedList_AppendHead_Clientes(clts, *tmp);
	}

	free(tmp);
	fclose(ficheiro);

	/* abrir o ficheiro contas.csv */
	FILE* ficheiro2 = fopen("contas.csv", "r");
	if (ficheiro2 == NULL)
		Security_Error(__FILE__, __LINE__);

	Contas* tmp2 = LinkedList_New_Contas();
	uint prev_id = 0;

	fgets(line, 215, ficheiro2);

	/* guardar as informacoes do ficheiro contas.csv na struct "tmp" */
	while (fgets(line, 215, ficheiro2) != NULL && strcmp(line, "\n"))
	{
		key = strtok(line, ";");

		tmp2->movimentos = NULL;
		tmp2->id = atoi(key);

		key = strtok(NULL, ";");
		tmp2->id_owner = atoi(key);

		key = strtok(NULL, ";");
		tmp2->tipo = atoi(key);

		key = strtok(NULL, ";");

		/* troca a virgula por um ponto de forma a conseguir fazer a conversa~o de string para float */
		Security_Replace_Char(key, ',', '.');
		tmp2->saldo = atof(key);

		(*cnts_size)++;
		LinkedList_AppendHead_Contas(cnts, *tmp2);
	}

	free(tmp2);
	fclose(ficheiro2);

	/* abrir o ficheiro movimentos.csv */
	FILE* ficheiro3 = fopen("movimentos.csv", "r");
	if (ficheiro2 == NULL)
		Security_Error(__FILE__, __LINE__);

	/* recolher o cabecalho do movimentos.csv */
	fgets(line, 215, ficheiro3);

	/* guardar as informacoes do ficheiro movimentos.csv na struct das contas recorrendo � stack movimentos */
	/* sem duvida, o metodo mais lento do programa */
	while (fgets(line, 215, ficheiro3) != NULL && strcmp(line, "\n"))
	{
		/* id (pesquisa pela conta com o id fornecido)*/
		key = strtok(line, ";");
		uint id = atoi(key);

		Contas* aux = LinkedList_BinarySearch_Contas(*cnts, id);

		if (aux == NULL)
		{
			continue;
		}

		Movimentos* tmp3 = Stack_Create_Movimentos(id);
	
		/* tipo de movimento (credito ou debito)*/
		key = strtok(NULL, ";");
		tmp3->tipo = (char*)malloc(sizeof(char) * 60);
		if (tmp3->tipo == NULL)
			Security_Error(__FILE__, __LINE__);
		strcat(key, "\0");
		strcpy(tmp3->tipo, key);

		/* montante */
		key = strtok(NULL, ";");
		Security_Replace_Char(key, ',', '.');
		tmp3->montante = atof(key);

		/* data */
		key = strtok(NULL, ";");
		tmp3->data = (char*)malloc(sizeof(char) * 30);

		if (tmp3->data == NULL)
			Security_Error(__FILE__, __LINE__);

		if(key[strlen(key) - 1] == '\n')
			key[strlen(key) - 1] = '\0';

		strcpy(tmp3->data, key);

		Stack_Push_Movimentos(&(aux->movimentos), tmp3);
	}

	fclose(ficheiro3);
}

void Files_SaveMemory(Clientes** clts, Contas** cnts)
{
	/* temos de trocar a ordem das listas ligadas antes de as guardar */
	LinkedList_Reverse_Cliente(clts);
	LinkedList_Reverse_Conta(cnts);

	FILE* clientes = fopen("clientes.csv", "w");
	if(clientes==NULL)
		Security_Error(__FILE__, __LINE__);

	//id,palavra-passe,nome,data de nascimento,morada,saldo global,contas
	Clientes* curr;

	fprintf(clientes, "%s\n", "id;palavra-passe;nome;data de nascimento;morada;saldo global;contas");

	for (curr = *clts; curr != NULL; curr = curr->next)
	{
		fprintf(clientes, "%d;%s;%s;%s;%s;%.2lf;%s\n", curr->id, curr->pin, curr->nome, 
												curr->data, curr->morada, curr->saldo_global, 
												curr->contas_associadas);
	}
	fclose(clientes);

	FILE* as_contas = fopen("contas.csv", "w");
	FILE* os_movimentos = fopen("movimentos.csv", "w");

	fprintf(as_contas, "%s\n", "ID;Id do propriet�rio;ordem ou prazo;saldo");
	fprintf(os_movimentos, "%s\n", "id conta;tipo;montante;data");

	Contas* tmp;
	for (tmp = *cnts; tmp != NULL; tmp = tmp->next)
	{
		/* O(n^2), sabemos n�o ser o mais adequado por�m j� n�o tivemos tempo para arranjar um mecanismo mais eficiente */
		Movimentos* aux = tmp->movimentos;
		while (aux != NULL)
		{
			fprintf(os_movimentos, "%d;%s;%.2lf�;%s\n",	aux->id_conta, aux->tipo, aux->montante, aux->data);							
			aux = aux->next;
		}

		fprintf(as_contas, "%d;%d;%d;%.2lf�\n", tmp->id, tmp->id_owner, tmp->tipo, tmp->saldo);
	}
	fclose(as_contas);
	fclose(os_movimentos);
}

