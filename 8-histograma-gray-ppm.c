#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int gray, r,g,b; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i,j, larg, alt, max;
	int hist[255], k;

   //entrada
	image = fopen("lena-original.pgm", "r");
	if(image == NULL)
	{
		printf("Erro na abertura do arquivo \n");
		return 0;
	}

     //key
	fscanf(image, "%s", key);
	if(strcmp(key, "P2") != 0){
		printf("Arquivo n e PGM\n");//checa se esta em P3
		printf("%s\n",key );
		fclose(image);
		return 0;
	}

	//header
	fscanf(image, "%d %d\n%d\n", &alt, &larg, &max);//le o cabeçario
	printf("larg =%d alt=%d key=%s max=%d\n",larg, alt, key,max );//printa na tela os valores lidos

    //saida
	newImage = fopen("arquivo.ppm","w+"); //abre o novo arquivo que vai ser criado
	if(newImage == NULL){
		printf("ERRO AO ABRIR NEWIMAGE");
		return 0;
	}
    
	pixel **G =(pixel**)malloc(alt*sizeof(pixel*));
	for(i=0;i<alt;i++){
		G[i] = (pixel*)malloc(larg*sizeof(pixel));
	}

	//lê as infos da matriz original
	for(i=0; i<alt;i++){
		for(j=0;j<larg;j++){
			fscanf(image, "%d", &G[i][j].gray );
		}
	}
	// setar para zero todos os valores do vetor vetor hist[255]
	for (k=0 ; k<255 ; k++)
	{
		hist[k]=0;
	}
 	//grava header / dados
	fprintf(newImage, "P3\n%d %d\n%d\n",alt,larg,max);
	for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){
            for (k=0; k<=255 ; k++)
            {
                if (G[i][j].gray == k) // CONTADOR PRO R
                {
                    hist[k]++;
                }
            }
    
		}
	}
	// laco p mostrar a qtd dos valores de 0 a 255
	fprintf(newImage, "\nResultado Histograma \n\n");
	 for (k=0; k<=255 ; k++)
      {
       fprintf(newImage, "GRAY[%d]  = %d \n", k, hist[k]);
       // fprintf(newImage, "%d\n", hist[k]);
      }
 
	//fim
	fclose(image);
	fclose(newImage);
return 0;
}
