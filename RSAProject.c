/****************************************************************
*********AUTHOR: ABDUL WAHAB & TALHA ISMAIL**********************
*****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
int num[9999];
int decodednum[9999];
char val[28] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '.' };
char * msg;
char *decodedmsg;
int  size, i, j, parts = 2, start = 0, end, rep, k, p, q, phi, e, n, d, check,check1;
int prod[9999];											/*DECLARING ALL THE VARIABLES GOBALLY, MAKES IT EASY TO USE IN THE USER DEFINED FUNCTION*/
unsigned long long incrypt[9999];
unsigned long long decrypt[9999];
int prime(int a);
int power(int x, unsigned int y, int p);										/*DECLARING THE USERDEFINED FUNCTIONS*/
bool is_coprime(unsigned long long e, unsigned long long phi);	
unsigned long long findd(unsigned long long e, unsigned long long phi);
void main()
{
	/****************************************************!!!!!!!TAKING VALUES OF p q n and e !!!!!!!*********************************************************************/

	printf("AUTHORS: ABDUL WAHAB AND TALHA ISMAIL!\n\n");
	printf("+------------------------------------+\n|    RSA PUBLIC-KEY CRYPTOSYSTEM     |\n+------------------------------------+\n");
q:
	printf("CHOSE BIGGER PRIME NUMBERS FOR CORRECT RESULT! SMALLER PRIME NUMBERS WILL PRODUCE WRONG RESULT!\n");
	printf("Enter a Prime number for value of 'n':");
	scanf("%d", &p);
	check = prime(p);
	if (check == 0)
	{
		printf("Not a prime Number!\n");
		getchar();
		goto q;
	}
w:																			/*TAKING VALUES OF 'p' NAD 'q' TO GENERATE 'n'*/
	printf("Enter another Prime number for value of 'n':");					
	scanf("%d", &q);
	check = prime(q);
	if (check == 0)
	{
		printf("Not a prime Number!\n");
		getchar();
		goto w;
	}
	n = p*q;
	printf("\n the value of n is:%d", n);							/*GENERATING THE VALUE OF PHI*/
	phi = (p - 1)*(q - 1);
r:
	printf("\nChose a prime number (1 - %d) for the value of e that doesnt divide %d:", phi, phi);
	scanf("%d", &e);												/*SELECTING THE VALUE OS 'e'*/
	check = prime(e);
	check1 = is_coprime(e, phi);
	if (check1 == 0)												/*CHECKING WETHER THE VALUE OF 'e' IS CORRECT*/
	{
		printf("NOT CO PRIME!");
		getchar();
		goto r;
	}
	if (check == 0)
	{
		printf("Wrong Choice!");
		getchar();
		goto r;
	}
	if (phi%e == 0)
	{
		printf("Wrong Choice!");
		getchar();
		goto r;
	}
	d = findd(e, phi);												/*GENERATING THE VALUE OF 'd'*/

	printf("+------------------------------------+\n|        I.  KEY GENERATION          |\n+------------------------------------+\n");
	printf("\nPUBLIC KEY (e,n) = (%d,%d)", e, n);
	printf("\nPRIVATE KEY (d,n) = (%d,%d)\n\n", d, n);
	printf("+------------------------------------+\n|        II. CIPHER & DIPHER         |\n+------------------------------------+\n");
	
	/*********************************************************!!!!!!!!GETTING MESSAGE FROM USER!!!!!!!!!****************************************************************/

	printf("\nEnter the size of your message:");					/*USING DYNAMIC MEMORY*/
	scanf("%d", &size);												/*TAKING SIZE FROM THE USER*/
	msg = (char *)malloc(size* sizeof(char));
	decodedmsg = (char *)malloc(size* sizeof(char));
	getchar();
	printf("Your Message:");										/*GETTING THE MESSAGE FROM USER*/
	gets(msg);
	if (strlen(msg) != size)					
	{
		msg[size] = '\0';
	}
	decodedmsg[size] = '\0';
	_strupr(msg);													/*CONVERTING MESSAGE TO UPER CASE*/
	if (strlen(msg) % 2 == 0)										/*INITIALIZING VARIABLE 'rep' FOR CONTROLLING THE REPITITION*/
	{
		rep = strlen(msg) / parts;
		rep--;
	}
	else if (strlen(msg) % 2 == 1)
	{
		rep = strlen(msg) / parts;
	}
	printf("\n\nINPUT.");											/*DSIPLAYING THE MESSAGE*/
	for (i = 0; i < strlen(msg); i++)
	{
		printf("| '%c' | ", msg[i]);
	}
	printf("\n      ");
	for (i = 0; i < strlen(msg); i++)
	{
		for (j = 0; j < 28; j++)
		{
			if (msg[i] == val[j])									/*DISPLAYING THE PARTICULAR VALUE FOR EACH CHARACTER*/
				printf("|  %d  | ", j);
		}
	}

	start = 0;																/*DIVIDING THE MESSAGE IN CHUNKS*/
	end = parts;

	/***********************************************************!!!!!!!DISPLAYING THE CODED NUMBERS AND MESSAGR!!!!!!!***************************************************/
	
	printf("\n\n\nM.    ");
	for (k = 0; k <= rep; k++)
		{
			for (i = start; i < end; i++)
			{
				for (j = 0; j < 28; j++)
				{
					if (msg[i] == val[j])
					{
						num[i] = j;									/*ASSIGNING VALUES TO EVERY CHARACTER IN THE MESSAGE*/
					}
				}
			}
			printf("| %c%c | ", msg[start], msg[start + 1]);		/*DIVIDING AND DESPLAYING MESSAGE IN CHUNKS OF TWO*/
			start = end;
			end = end + parts;
		}
		start = 0;
		end = parts;

		printf("\nP(M). ");
		for (k = 0; k <= rep; k++)
		{
				if (num[i] >= 0 && num[i] < 100)
					prod[k] = (num[start] * 100) + num[start + 1];			/*GENERATING P(M) AND STROING IT IN AN ARRAY*/

			printf("| %d | ", prod[k]);
			start = end;
			end = end + parts;
		}
		if (strlen(msg)  > 1)
		{
			prod[k] = num[i] * 100;
		}
		printf("\nC(P). ");													/*CALCULATING C(P) AND STROING IT IN AN ARRAY AND DISPLAYING IT*/
		for (k = 0; k <= rep; k++)
		{
			incrypt[k] = power(prod[k], e, n);
			printf("| %d | ", incrypt[k]);
		}
		printf("\nD(C). ");													/*DESPLAYING THE D(C) DECRYPTED MESSAGE AND STORING IT IN AN ARRAY*/
		for (k = 0; k <= rep; k++)
		{
			decrypt[k] = power(incrypt[k], d, n);
			printf("| %d | ", decrypt[k]);
		}
		start = 0;
		end = parts;
		for (k = 0; k <= rep; k++)											/*DECODING THE VALUES AND SPLITTING THE CHUNKS*/
		{
			decodednum[start] = decrypt[k] / 100;
			decodednum[start + 1] = decrypt[k] % 100;
			start = end;
			end = end + parts;
		}
		printf("\nM.    ");
		
		
		for (i = 0; i < strlen(msg); i++)
		{
			for (j = 0; j < 28; j++)
			{
				if (decodednum[i] == j)
				{
					decodedmsg[i] = val[j];
				}
			}

		}
		start = 0;
		end = parts;
		for (k = 0; k <= rep; k++)
		{
			printf("| %c%c | ", decodedmsg[start], decodedmsg[start + 1]);
			start = end;
			end = end + parts;
		}

		/************************************************************!!!!!!!!!DISPLAYING THE OUTPUT!!!!!!!!**************************************************************/

		printf("\n\n\nOUTPUT.");										/*DISPLAYING THE DECODED MESSAGE*/
		for (i = 0; i < strlen(msg); i++)
		{
			printf("|  %d  | ", decodednum[i]);
		}
		printf("\n       ");
		for (i = 0; i < strlen(msg); i++)								/*ASSIGNING CHARACTERS TO THE DECODED NUMBERS*/
		{
			printf("| '%c' | ",decodedmsg[i]);
		}
	
	printf("\n\n");
	system("pause");
}

/********************************************************************!!!!!!!USER DEINED FUNCTIONS!!!!!!!!***************************************************************/

int prime(int a)											/*CHECKING IF THE NUMBER IN ARGUEMENT IS PRIME OR NOT*/
{
	int i, j = 0;
	for (i = 1; i < a; i++)
	{
		if (a%i == 0)
			j++;
	}
	if (j == 1)
		return 1;
	else
		return 0;
}
int power(int x, unsigned int y, int p)						/*CALCULATING THE MOD OF EXPONENTIAL STATEMENT*/
{
	int temp = 1;
	for (int i = 0; i < y; i++)
	{
		temp = temp*x;
		temp = temp%p;
	}
	return temp;
}
