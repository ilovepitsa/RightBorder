#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<malloc.h>
#include<string.h>
const int n = 20;
struct VozratDoN
{
	int k;
	char* newstring;
};
struct VozratDoN DovodDoN(char string[], int k, char * newstring, FILE*file);
void PoObzac(char string[],FILE* file);
void viravnivanie(char string[], FILE* out, int key);
int main()
{
	setlocale(LC_ALL, "Russian");
	printf("Вас приветсвует программа по разбиению текста на абзацы + выравнивания по правому краю!\n");
	FILE* in, *out;
	FILE* filetemp1, *filetemp2, *filetemp3;
	in = fopen("in.txt", "r+");
	out = fopen("out.txt", "r+");
	filetemp1 = fopen("filetemp1.txt", "r+" );
	filetemp2 = fopen("filetemp2.txt", "r+");
	filetemp3 = fopen("filetemp3.txt", "r+");

	if (in == NULL || out == NULL || filetemp1 == NULL || filetemp2 == NULL || filetemp3 == NULL )
	{
		printf("Не удалось открыть файл"); return -5;
	}

	char string[270] = { 0 }; int i;
	char* newstring;
	newstring = (char*)malloc(n * sizeof(char));
	memset(newstring, '\0', n);
	while (fgets(string, 256, in))
	{
		for (i = 0; i < (int)strlen(string); i++)
		{
			if (string[i] == '\n')string[i] = ' ';
		}
		for (i = 0; i < (int)strlen(string)-1; i++)
		{
			if(string[i]==" " && string[i+1]==" ")
				for (int j = i; j < (int)strlen(string)-1; j++)
				{
					string[j] = string[j + 1];
				}
		}
		fputs(string, filetemp1);
		for (i = 0; i < (int)strlen(string); i++) string[i] = '\0';

	}
	rewind(filetemp1);
	char* temp_mass; int k = 0; struct VozratDoN vozvrat;	struct VozratDoN poObz;
	while (fgets(string, n,filetemp1))
	{
		if (strchr(string, '^') != 0)
		{
		 PoObzac(string, filetemp2);
		}
		else
		{
			fputs(string, filetemp2);
		}
		for (i = 0; i < (int)strlen(string); i++) string[i] = '\0';
	}
	
	rewind(filetemp2); k = 0;
	memset(newstring, '\0', n); 
	while (fgets(string,n-k,filetemp2))
	{
		vozvrat = DovodDoN(string, k, newstring, filetemp3);
		k = vozvrat.k; newstring = vozvrat.newstring;
		for (i = 0; i < (int)strlen(string); i++) string[i] = '\0';
	}
	if (newstring != NULL)
		fputs(newstring, filetemp3);
	rewind(filetemp3);
	printf("Вывод результата на экран(1) или в выходной файл(2)?\n");
	int key;
	scanf("%d", &key);
	if (key > 2 || key < 1)
	{
		printf("Неправильный выбор вывода"); return 0;
	}
	while (fgets(string, n, filetemp3))
	{
	//	printf("%s", string);
		viravnivanie(string,out,key);
	
		for (i = 0; i < (int)strlen(string); i++) string[i] = '\0';
	}

	fclose(in); fclose(out); fclose(filetemp1);fclose(filetemp2);fclose(filetemp3);
	printf("Программа завершила свою работу");
}

struct VozratDoN DovodDoN(char string[], int k, char*newstring, FILE* file)
{
	int i; char* temp_mass = (char*)malloc(n * sizeof(char));
	i = strlen(string);
	struct VozratDoN vozvrat;
	memset(temp_mass, '\0', n);
	if (string[i] != ' ' && (int)strlen(string) > n / 2)
	{
		while (string[i] != ' ')
			i--;
		k = strlen(string) - i;
		for (int j = 0; j < k; j++)
		{
			temp_mass[j] = string[i + j];
		}
	}
	else k = 0;
	strncat(newstring, string, i+1);
	if ((int)strlen(newstring) + (int)strlen(temp_mass) < n)
	{
		strcat(newstring, temp_mass); k = 0;
	}
	if (strchr(newstring, '\n') == 0)
	{
		strcat(newstring, "\n");
	}
	fputs(newstring, file);
	memset(newstring, '\0', n);
	
	if (k != 0)
	{
		strncat(newstring, temp_mass, k);
	}
	vozvrat.k = k;
	vozvrat.newstring = newstring;
	
	free(temp_mass);
	return vozvrat;
}
void PoObzac(char string[], FILE* file)
{
	int i; char* newstring = (char*)malloc(n * sizeof(char));
	char* temp_mass = (char*)malloc(n * sizeof(char));
	memset(newstring, '\0', n); memset(temp_mass, '\0', n);
	if (strchr(string, '^') != 0)
	{
		i = 0;
		while (string[i] != '^')
			i++;
		string[i] = '\n';
		strncat(newstring, string, i+1);
		fputs(newstring, file);
		memset(newstring, '\0', n);
		strcat(temp_mass, "   ");
		for (int j = i+1; j < (int)strlen(string); j++)
			temp_mass[j - i +2] = string[j+1];
			PoObzac(temp_mass, file);
	}
	else
		fputs(string, file);

}
void viravnivanie(char string[], FILE*out,int key)
{
	char* temp_mass = (char*)malloc(n * sizeof(char));
	int i = 0, k, s=0;
	k = (int)strlen(string);
	memset(temp_mass, '\0', n);
	if (k < n)
	{
		for (i = 0; i < n - k-1; i++)
			strcat(temp_mass, " ");
	}
	
	strcat(temp_mass, string);
	while (temp_mass[n - 1] == ' ')
		for (i = n - 1; i != 2; i--)
			temp_mass[i] = temp_mass[i - 1];
	if(key==2)
	fputs(temp_mass, out);
	else
	{
		printf("%s", temp_mass);
	}
	free(temp_mass);
}

