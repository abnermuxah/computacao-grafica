#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int gray; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *image2;
	FILE *newImage;

	char key[5], _key[5];
	int i,j, larg, alt, max;
	int _i,_j, _larg, _alt, _max;


    //entrada
	image = fopen("A.pgm", "r");
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
	newImage = fopen("arquivo.pgm","w+"); //abre o novo arquivo que vai ser criado
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
// fim imagem 1

// inicio imagem 2
// entrada

image2 = fopen("B.pgm", "r");
	if(image2 == NULL)
	{
		printf("Erro na abertura do arquivo \n");
		return 0;
	}

    //key
	fscanf(image2, "%s", _key);
	if(strcmp(key, "P2") != 0){
		printf("Arquivo n e PGM\n");//checa se esta em P3
		printf("%s\n",_key );
		fclose(image2);
		return 0;
	}

	//header
	fscanf(image2, "%d %d\n%d\n", &_alt, &_larg, &_max);//le o cabeçario
	printf("larg =%d alt=%d key=%s max=%d\n",_larg, _alt, _key,_max );//printa na tela os valores lidos


	pixel **G2 =(pixel**)malloc(alt*sizeof(pixel*));
	for(i=0;i<alt;i++){
		G2[i] = (pixel*)malloc(larg*sizeof(pixel));
	}

	//lê as infos da matriz original
	for(i=0; i<alt;i++){
		for(j=0;j<larg;j++){
			fscanf(image2, "%d", &G2[i][j].gray );
		}
	}


	//grava header / dados
	fprintf(newImage, "P2\n%d %d\n%d\n",alt,larg,max);

    for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){

                if (G[i][j].gray && G2[i][j].gray) // ||
                {
                	fprintf(newImage, "%d ", 255);
                }
                else
                {
                	fprintf(newImage, "%d ", 0);
                }

                // fprintf(newImage, "%d ", G[i][j].gray); // aqui vai ser a manipualão do pixel local

            }
            fprintf(newImage, "\n");
		}

	//fim
	fclose(image);
	fclose(newImage);
return 0;

}
