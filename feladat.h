#ifndef FELADAT_H_INCLUDED
#define FELADAT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include "hashtable.h"

#pragma warning(disable:4996)
#pragma warning(disable:6031)	

const char* szoveg = "1 - Termek hozzaadasa a raktarhoz\n2 - Termek rendelese\n3 - Hibas termektipus megadasa\n4 - Raktar ujrameretezese\n5 - Termek keresese\n6 - Raktar maximalis telitettsegenek az allitasa\n0 - Kilepes\nKerem valasszon opciot!\n";


void read(FILE* fin, int& n, int& m, int& k, hashtable<int>& tabla)
{
	int s;
	float maxLoad;
	fscanf(fin, "%d %d %d %f", &n, &m, &k, &maxLoad);
	tabla.setMaxLoad(maxLoad);
	tabla.resize(n);
	for (int i = 0; i < m; i++)
	{
		fscanf(fin, "%d", &s);
		tabla.insert(s);
	}
}

void hozzaad(FILE* fin, FILE* fout, hashtable<int>& tabla, int signal)
{
	switch (signal)
	{
	case 1:
	{
		int n, s, errValue = 1;
		fscanf(fin, "%d", &n);
		for (int i = 0; i < n; i++)
		{
			fscanf(fin, "%d", &s);
			errValue = tabla.insert(s);
			fprintf(fout, "%d ", errValue);
		}
		fprintf(fout, "\n");
		break;
	};
	case 2:
	{
		int s, errValue;
		printf("Kerem adjon meg termekkodot : ");
		scanf("%d", &s);
		errValue = tabla.insert(s);	
		if (errValue == 1)
			printf("Sikeresen hozzaadtuk a raktarhoz!\n");
		else
			printf("A termek mar a raktarban van!\n");
		printf("Nyomj le egy gombot a folytatashoz...");
		int foo = _getch();
		break;
	};
	default:
	{
		printf("Error: bad signal\n");
		exit(0);
	};
	}
}

void rendel(FILE* fin, FILE* fout, hashtable<int>& tabla, int signal)
{
	switch (signal)
	{
	case 1:
	{
		int n, s, errValue;
		fscanf(fin, "%d", &n);
		for (int i = 0; i < n; i++)
		{
			fscanf(fin, "%d", &s);
			errValue = tabla.remove(s);
			fprintf(fout, "%d ", errValue);
		}
		fprintf(fout, "\n");
		break;
	};
	case 2:
	{
		int s, errValue;
		printf("Kerem adjon meg termekkodot : ");
		scanf("%d", &s);
		errValue = tabla.remove(s);
		if (errValue == 1)
			printf("Sikeresen elkuldtuk a termeket!\n");
		else
			printf("A termék nincs a raktárban!\n");
		printf("Nyomj le egy gombot a folytatashoz...");
		int foo = _getch();
		break;
	};
	default:
	{
		printf("Error: bad signal\n");
		exit(0);
	};
	}
}


void hibas(FILE* fin, FILE* fout, hashtable<int>& tabla, int signal)
{
	switch (signal)
	{
	case 1:
	{
		int n, errValue;
		fscanf(fin, "%d", &n);
		errValue = tabla.removeList(n);
		fprintf(fout, "%d\n",errValue);
		break;
	};
	case 2:
	{
		int n, errValue;
		printf("Kerem adja meg a hibas termek tipusat : ");
		scanf("%d", &n);
		errValue = tabla.removeList(n);
		if (errValue == 1)
			printf("Sikeresen toroltunk minden %d tipusu termeket!\n",n);
		else
			printf("Nincs a raktarban %d tipusu termek!\n",n);
		printf("Nyomj le egy gombot a folytatashoz...");
		int foo = _getch();
		break;
	};
	default:
	{
		printf("Error: bad signal\n");
		exit(0);
	};
	}
}

void ujrameretez(FILE* fin, FILE* fout, hashtable<int>& tabla, int signal)
{
	switch (signal)
	{
	case 1:
	{
		int n;
		fscanf(fin, "%d", &n);
		tabla.resize(n);
		fprintf(fout, "1\n");
		break;
	}
	case 2:
	{
		int n;
		printf("Kerem adja meg a raktar uj meretet : ");
		scanf("%d", &n);
		tabla.resize(n);
		printf("A raktar ujrameretezese s termek ujraosztasa megtortent!\n");
		printf("Nyomj le egy gombot a folytatashoz...");
		int foo = _getch();
		break;
	}
	default:
	{
		printf("Error: bad signal\n");
		exit(0);
	};
	}
}

void keres(FILE* fin, FILE* fout, hashtable<int>& tabla, int signal)
{
	switch (signal)
	{
	case 1:
	{
		int s, errValue;
		fscanf(fin, "%d", &s);
		errValue = tabla.findInTable(s);
		if (errValue > 0)
			errValue = 1;
		else
			errValue = 0;
		fprintf(fout, "%d\n", errValue);
		break;
	};
	case 2:
	{
		int s, errValue;
		printf("Kerem addja meg a termek kodjat : ");
		scanf("%d", &s);
		errValue = tabla.findInTable(s);
		if (errValue > 0)
			printf("A %d termek a %d tipusoknal van!\n", s, errValue);
		else
			printf("A termek nem talalhato a raktarban!\n");
		printf("Nyomj le egy gombot a folytatashoz...");
		int foo = _getch();
		break;
	};
	default:
	{
		printf("Error: bad signal\n");
		exit(0);
	};
	}
}

void ujtelitettseg(FILE* fin, FILE* fout, hashtable<int>& tabla, int signal)
{
	switch (signal)
	{
	case 1:
	{
		float n;
		fscanf(fin, "%f", &n);
		tabla.setMaxLoad(n);
		fprintf(fout, "1\n");
		break;
	}
	case 2:
	{
		float n;
		printf("Kerem adja meg a raktar maximalis telitettsegi aranyat : ");
		scanf("%f", &n);
		tabla.setMaxLoad(n);
		printf("Sikeres atallitas!\n");
		printf("Nyomj le egy gombot a folytatashoz...");
		int foo = _getch();
		break;
	}
	default:
	{
		printf("Error: bad signal\n");
		exit(0);
	};
	}
}

void simulator(FILE* fin, FILE* fout, int k, hashtable<int>& tabla)
{
	char utasitas[50];
	for (int i = 0; i < k; i++)
	{
		fscanf(fin, "%s", utasitas);
		utasitas[strlen(utasitas)] = '\0';

		if (!strcmp(utasitas, "Hozzaad"))
		{
			hozzaad(fin, fout, tabla,1);
			continue;
		}

		if (!strcmp(utasitas, "Rendel"))
		{
			rendel(fin, fout, tabla, 1);
			continue;
		}

		if (!strcmp(utasitas, "Hibas"))
		{
			hibas(fin, fout, tabla, 1);
			continue;
		}

		if (!strcmp(utasitas, "Ujrameretez"))
		{
			ujrameretez(fin, fout, tabla, 1);
			continue;
		}

		if (!strcmp(utasitas, "Keres"))
		{
			keres(fin, fout, tabla, 1);
			continue;
		}

		if (!strcmp(utasitas, "UjTelitettseg"))
		{
			ujtelitettseg(fin, fout, tabla, 1);
			continue;
		}
	}
}

void interface(hashtable<int>& tabla)
{
	char kod;
	FILE* dum = fopen("input.txt", "r");
	while (1)
	{
		system("CLS");
		printf("A raktar aktualis allapota:\n");
		tabla.print();
		printf("\n%s", szoveg);
		kod = _getch();
		printf("\n");
		switch (kod)
		{
		case 48: 
		{
			printf("Shutdown");
			exit(0);
		}
		case 49:
		{
			hozzaad(dum, dum, tabla, 2);
			break;
		};
		
		case 50:
		{
			rendel(dum, dum, tabla, 2);
			break;
		};

		case 51:
		{
			hibas(dum, dum, tabla, 2);
			break;
		};

		case 52:
		{
			ujrameretez(dum, dum, tabla, 2);
			break;
		};

		case 53:
		{
			keres(dum, dum, tabla, 2);
			break;
		};

		case 54:
		{
			ujtelitettseg(dum, dum, tabla, 2);
			break;
		};
		default:
		{
			printf("Hibas opcio!\n");
			break;
		};
		}
	}
}

#endif