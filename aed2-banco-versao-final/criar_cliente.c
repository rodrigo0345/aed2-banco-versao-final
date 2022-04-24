#include "structs.h"
#include "master.h"

void* Criar_Clientes(Clientes** clts, Contas** cnts, uint* clts_size, uint* cnts_size)
{
	dialogo(2);
	dialogo(3);

	Clientes* novo = LinkedList_New_Clientes();
	novo->saldo_global = 0;

	char string[50] = { 0 };
	scanf_s("%[^\n]%*c", string, 50);
	fflush(stdin);
	if (Security_CheckForDigits_String(string) || strlen(string) <= 1)
	{
		system("cls");
		printf("Nome inv�lido! (Apenas s�o permitidas letras e espa�os)");
		getchar();
		free(novo);
		novo = NULL;
		return  -1;
	}
	novo->nome = (char*)malloc(strlen(string) * sizeof(char));
	if (novo->nome == NULL)
		Security_Error("methods//Clientes//criar_cliente->c//Criar_Clientes//novo->nome");
	strcpy(novo->nome, string);


	dialogo(4);
	scanf_s("%[^\n]%*c", string, 50);
	fflush(stdin);
	if (strlen(string) > 6 || strlen(string) <= 0)
	{
		system("cls");
		printf("C�digo inv�lido! (Apenas s�o permitidos [0 -> 6] carateres)");
		free(novo);
		novo = NULL;
		getchar();
		return -1;
	}
	Security_Encrypt_String(string);
	novo->pin = (char*)malloc(strlen(string) * sizeof(char));
	if (novo->pin == NULL)
		Security_Error("methods//Clientes//criar_cliente.c//Criar_Clientes//novo->pin");
	strcpy(novo->pin, string);


	dialogo(5);
	uint dia, mes, ano;
	printf("\n\n\   -|Dia|- "); Security_Input_Int(string, &dia);
	printf("   -|Mes|- "); Security_Input_Int(string, &mes);
	printf("   -|Ano|- "); Security_Input_Int(string, &ano);
	if (!Time_CheckInputDate_Int(dia, mes, ano))
	{
		system("cls");
		printf("Data inv�lida!");
		free(novo);
		novo = NULL;
		getchar();
		return -1;
	}
	sprintf(string, "%u/%u/%u", dia, mes, ano);
	novo->data = (char*)malloc(strlen(string) * sizeof(char));
	if (novo->data == NULL)
		Security_Error("methods//Clientes//criar_cliente.c//Criar_Clientes//novo->data");
	strcpy(novo->data, string);


	dialogo(6);
	scanf_s("%[^\n]%*c", string, 50);
	novo->morada = (char*)malloc(strlen(string) * sizeof(char));
	if (novo->morada == NULL)
		Security_Error("methods//Clientes//criar_cliente.c//Criar_Clientes//novo->morada");
	strcpy(novo->morada, string);
	fflush(stdin);

	novo->id = (*clts_size)++;

	LinkedList_AppendHead_Clientes(clts, *novo);
	printf("\nConta criada com sucesso!\nGuarde este c�digo, ID -> [%u]\n", novo->id);
	getchar();

	/* liberta o espa�o usado,
		mas n�o conseguimos libertar o
		espa�o usado pelas vari�veis
		dentro de novo				*/

	free(novo);
	novo = NULL;

	return 0;
}
