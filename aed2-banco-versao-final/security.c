#include "master.h"

/* Caso seja ativado ir� dar output a uma msg e ir� encerrar o programa */
void Security_Error(char* msg)
{
	perror(msg);
	exit(1);
}

/* Apaga todo o conte�do dentro das listas ligadas clts e cnts */
void Security_ProgramExit_Global(Clientes* clts, Contas* cnts)
{
	LinkedList_Delete_Clientes(&clts);
	LinkedList_Delete_Contas(&cnts);
	exit(0);
}

/* M�todo alternativo ao scanf, apenas funciona para numeros */
void Security_Input_Int(char variable[], int* store)
{
	fgets(variable, sizeof(variable) + 1, stdin);
	(*store) = atoi(variable);
	fflush(stdin);
}

/* Valida o n�mero introduzido pelo utilizador [0,Max] */
int Security_Validation_UInt(uint Input, uint Max)
{
	if (1 > Input || Max < Input)
	{
		return 0;
	}
	return 1;
}

/* encripta��o muito muito b�sica s� para parecer fixe :) */
void Security_Encrypt_String(char frase[])
{
	int i = 0;
	while (frase[i] != '\0')
	{
		if (frase[i] == 0) continue;
		else
			frase[i] += 3 * i;
		i++;
	}
}

/* verifica se a string do argumento tem ou n�o numeros e carateres especiais */
uint Security_CheckForDigits_String(char* string)
{
	int i = 0;
	for (i = 0; i < strlen(string); i++)
	{
		if (isdigit(string[i]))
		{
			return 1;
		}
		else if (string[i] == '!' || string[i] == '@' || string[i] == '#' || string[i] == '$'
			|| string[i] == '%' || string[i] == '^' || string[i] == '&' || string[i] == '*'
			|| string[i] == '(' || string[i] == ')' || string[i] == '-' || string[i] == '{'
			|| string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == ':'
			|| string[i] == ';' || string[i] == '"' || string[i] == '\'' || string[i] == '<'
			|| string[i] == '>' || string[i] == '.' || string[i] == '/' || string[i] == '?'
			|| string[i] == '~' || string[i] == '`')
		{
			return 1;
		}
	}
	return 0;
}

/* pede automaticamente ao utilizador as credenciais de login e retorna um numero para indicar se foi bem sucedido ou n�o */
uint Security_Login(Clientes** clts, Clientes** result, char* guess, uint* id)
{
	char str[14];
	printf("Indique o ID do Cliente: ");
	Security_Input_Int(str, id);

	printf("Indique o PIN: ");
	scanf_s("%[^\n]%*c", guess, 20);
	fflush(stdin);

	if (strlen(guess) > 6 || strlen(guess) <= 0)
	{
		system("cls");
		printf("C�digo inv�lido! (Apenas s�o permitidos [0 -> 6] carateres)");
		getchar();
		return 0;
	}
	Security_Encrypt_String(guess);

	*result = LinkedList_BinarySearch_Clientes(*clts, *id);

	if (*result == NULL)
	{
		printf("Cliente n�o encontrado!");
		getchar();
		return 0;
	}

	/* ainda existe aqui um problema, ainda n�o sei porque */
	if (strcmp(guess, (*result)->pin))
	{
		printf("PIN incorreto!");
		getchar();
		free(*result);
		*result = NULL;
		return 0;
	}
	return 1;
}

/* trata dos argumentos do cmd sendo o mais importante o comando --dev */
void Security_Flags(char* argv[])
{
	if (argv[1] == NULL) return;
	if (!strcmp(argv[1],"--dev"))
	{
		DevTools_Options();
	}
}

/* Cria um ficheiro .txt para guardar o livro-raz�o de uma conta */
void Security_FileLivroRazao(Contas* curr)
{
	char filename[20];

	/* armazenamos o nome do ficheiro a ser criado em "filename" */
	sprintf(filename, "%s[%d].txt", "Livro-Razao", curr->id);
	printf("Localiza��o do ficheiro: %s", filename);

	FILE* open = fopen(filename, "w");
	if (open == NULL)
		Security_Error("security.c//Security_FileLivroRazao//open (n�o foi possivel abrir o ficheiro)");

	char* key = strtok(curr->livro_razao, ";");
	while (key != NULL)
	{
		fprintf(open, "%s\n", key);
		key = strtok(NULL, ";");
	}

	fclose(open);

	printf("\nFicheiro criado com sucesso!");
	getchar();
}