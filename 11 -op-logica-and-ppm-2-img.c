// Adriana a estrturua do codigo eh a mesma para as demais (+, -, *, /)
// o que muda eh o sinal do laco for() em cada pixel
// * (para mutiplicacao)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r,g,b; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *image2;
	FILE *newImage;
    int aux;
	char key[5], _key[5];
	int i,j, larg, alt, max;
	int _i,_j, _larg, _alt, _max;


    //entrada
	image = fopen("A.ppm", "r"); // ----------------------------------------------------------------
	if(image == NULL)
	{
		printf("Erro na abertura do arquivo \n");
		return 0;
	}

    //key
	fscanf(image, "%s", key);
	if(strcmp(key, "P3") != 0){
		printf("Arquivo n ? PPM\n");//checa se esta em P3
		printf("%s\n",key );
		fclose(image);
		return 0;
	}

	//header
	fscanf(image, "%d %d\n%d\n", &alt, &larg, &max);//le o cabe?ario
	printf("Image larg =%d alt=%d key=%s max=%d\n",larg, alt, key,max );//printa na tela os valores lidos

    //alt x largura - [610][480]
	pixel **RGB =(pixel**)malloc(alt*sizeof(pixel*));
	for(i=0;i<alt;i++){
		RGB[i] = (pixel*)malloc(larg*sizeof(pixel));
	}

	//l? as infos da matriz original
	for(i=0; i<alt;i++){
		for(j=0;j<larg;j++){
			fscanf(image, "%d", &RGB[i][j].r );
			fscanf(image, "%d", &RGB[i][j].g );
			fscanf(image, "%d", &RGB[i][j].b );
		}
	}

// fim imagem ---------------

// inicio imagem2 ---------

//entrada
	image2 = fopen("B.ppm", "r"); // ----------------------------------------------------------------
	if(image2 == NULL)
	{
		printf("Erro na abertura do arquivo \n");
		return 0;
	}

    //key
	fscanf(image2, "%s", _key);
	if(strcmp(_key, "P3") != 0){
		printf("Arquivo n eh PPM\n");//checa se esta em P3
		printf("%s\n",_key );
		fclose(image2);
		return 0;
	}

	//header
	fscanf(image2, "%d %d\n%d\n", &_alt, &_larg, &_max);//le o cabe?ario
	printf("Image2 larg =%d alt=%d key=%s max=%d\n",_larg, _alt, _key, _max );//printa na tela os valores lidos

    //saida
	newImage = fopen("arquivo.ppm","w+"); //abre o novo arquivo que vai ser criado
	if(newImage == NULL){
		printf("ERRO AO ABRIR NEWIMAGE");
		return 0;
	}

    //alt x largura - [610][480]
	pixel **RGB2 =(pixel**)malloc(alt*sizeof(pixel*));
	for(i=0;i<alt;i++){
		RGB2[i] = (pixel*)malloc(larg*sizeof(pixel));
	}

	//le as infos da matriz original
	for(i=0; i<alt;i++){
		for(j=0;j<larg;j++){
			fscanf(image2, "%d", &RGB2[i][j].r );
			fscanf(image2, "%d", &RGB2[i][j].g );
			fscanf(image2, "%d", &RGB2[i][j].b );
		}
	}
// fim imagem2

	//grava header / dados
	fprintf(newImage, "P3\n%d %d\n%d\n",alt,larg,max);
	for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){

             if ((RGB[i][j].r == RGB2[i][j].r) && (RGB[i][j].g == RGB2[i][j].g) && (RGB[i][j].b == RGB2[i][j].b))
            {
                  fprintf(newImage, "%d ", RGB[i][j].r );

                  fprintf(newImage, "%d ", RGB[i][j].g);

                  fprintf(newImage, "%d ", RGB[i][j].b);
            }

            else
            {
            aux = 255;
            fprintf(newImage, "%d ", aux );
			fprintf(newImage, "%d ", aux);
			fprintf(newImage, "%d ", aux);

            }
		} //j
		fprintf(newImage, "\n");
	}

	//fim
	fclose(image);
	fclose(image2);
	fclose(newImage);


return 0;
}

