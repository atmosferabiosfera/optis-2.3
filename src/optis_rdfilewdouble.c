# include <stdlib.h>

# include "optis_global.h"

double** rd_filewdouble(char *name, int nline, int ncol, int exline)
{
	FILE *file;
	double **data;
	int i, j, r;

	file = fopen(name, "r");
	if(file == NULL)
	{
		return NULL;
	}

	if(exline > 0)
	{
		for(i=0;i<exline;i++)
		{
			// Descarta uma linha
			fscanf(file, "%*[^\n]\n", NULL);
		}
	}

	data = (double**)malloc(nline*sizeof(double*));
	for(i=0;i<nline;i++)
	{
		data[i] = (double*)malloc(ncol*sizeof(double));

		for(j=0;j<ncol;j++)
		{
			r = fscanf(file, "%lf", &data[i][j]);
			
			// Avisa sobre um possivel erro
			if (r != 1)
			{
				printf("\nERRO: A leitura dos dados observados ou a saida do modelo nao esta correta.\n"\
				       "Conferir as configuracoes de linhas e/ou colunas no arquivo conf.h\n");
				exit(EXIT_FAILURE);
			}
		}
		// Descarta o resto da linha apos ler as colunas iniciais
		fscanf(file, "%*[^\n]\n", NULL);
	}

	fclose(file);

	return data;

}
