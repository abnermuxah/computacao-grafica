#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r,g,b; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i,j, larg, alt, max;


    //entrada
	image = fopen("lenap3.ppm", "r");
	if(image == NULL)
	{
		printf("Erro na abertura do arquivo \n");
		return 0;
	}

    //key
	fscanf(image, "%s", key);
	if(strcmp(key, "P3") != 0){
		printf("Arquivo n é PPM\n");//checa se esta em P3
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

	pixel **RGB =(pixel**)malloc(alt*sizeof(pixel*));
	for(i=0;i<alt;i++){
		RGB[i] = (pixel*)malloc(larg*sizeof(pixel));
	}

	//lê as infos da matriz original
	for(i=0; i<alt;i++){
		for(j=0;j<larg;j++){
			fscanf(image, "%d", &RGB[i][j].r );
			fscanf(image, "%d", &RGB[i][j].g );
			fscanf(image, "%d", &RGB[i][j].b );
		}
	}


	//grava header / dados
	fprintf(newImage, "P3\n%d %d\n%d\n",alt,larg,max);
	for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){
			fprintf(newImage, "%d ", 255 - RGB[i][j].r );
			fprintf(newImage, "%d ", 255 - RGB[i][j].g);
			fprintf(newImage, "%d ", 255 - RGB[i][j].b);
		}
		fprintf(newImage, "\n" );
	}

	//fim
	fclose(image);
	fclose(newImage);
return 0;
}
