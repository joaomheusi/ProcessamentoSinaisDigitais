/* programa para testes com arquivos
-- Lendo arquivo de entrada
-- Processa
-- Gera arquivo de saida
-- walter 1.0 
*/

#include <stdio.h>
#include <string.h>



#define 	FrameSize 1
#define NSAMPLES 1764 

static int frameCount = 1;

extern void proc_file( short *, short *, int);

int main(int argc,char *argv[])
{
    
	FILE *fin,*fout,*fp;


	int i,n,n_amost;
	short entrada,saida;
	short sample[NSAMPLES] ={0x0};
	float y=0;
	
	float fval[1764];
	int coefsN, coefsI;
	
	printf("***************************************************************\n");
	printf("* TESTE COM ARQUIVOS					           		      *\n");
	printf("*                                                             *\n");
	printf("***************************************************************\n");
	printf("\n");

	
	fp = fopen("..\\PassaBaixa200.txt","rb");
    	if ((fp)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo dos coeficientes.\n");
    		return 0;
  	}
  	rewind(fp);
  	coefsN = 0;
  	while (fscanf(fp, "%f", &fval[coefsN++]) != EOF)
    ;
    fclose(fp);
    printf("Leu os coefs\n");
	fin = fopen("..\\sweep0_400.pcm","rb");
    	if ((fin)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo de Entrada\n");
    		return 0;
  	}
    fout = fopen("..\\outPassaBaixa.pcm","wb");
    	if ((fout)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo de Saida\n");
    		return 0;
  	}
	printf("Abriu entrada e sa�da\n");
  
  for (i = 0; i < NSAMPLES; i++)
  {
    sample[i] = 0;
  }
  printf("zerou vetor de amostras\n");
  printf("Processando ... ");

  do{
  		y = 0;

    	n_amost = fread(&entrada, sizeof(short), 1, fin);
    	sample[0] = entrada;
    	
    	for (n = 0; n < NSAMPLES; n++)
		{
		  y += fval[n] * sample[n];
		}
    	
    	for (n = NSAMPLES - 1; n > 0; n--)
	    {
	      sample[n] = sample[n - 1];
	    }
    	
	    saida = (short)y;
	    printf("+1");
	    fwrite(&saida, sizeof(short), 1, fout);
	
  
  } while (n_amost);
  
    printf("terminado!\n");
		
    
	
		fclose(fin);
		fclose(fout);
		
    return 0;
}


