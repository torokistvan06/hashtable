#include "hashtable.h"
#include "feladat.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	hashtable<int> tabla;
	int n = 0, m = 0, k = 0;
	FILE* fin = fopen("input3.txt", "r");
	FILE* fout = fopen("output3.txt", "w");
	read(fin, n, m, k, tabla);
	simulator(fin,fout,k,tabla);
	interface(tabla);
	return 0;
}