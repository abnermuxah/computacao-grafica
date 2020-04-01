// escala versao 1
// este codigo o resultado é apresentado sobreposto na imagem original a partir do primeiro pixel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int gray; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i,j, larg, alt, max, gray;
	int Sx, Sy;
	gray =0;
	Sx = 2; // eixo X
	Sy = 2; // eixo Y
    //entrada
	image = fopen("lena-g.pgm", "r");
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
	printf("Entrada: larg =%d alt=%d key=%s max=%d\n",larg, alt, key,max );//printa na tela os valores lidos

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


	fprintf(newImage, "P2\n%d %d\n%d\n", alt, larg,max);
	printf("Saida: _larg =%d _alt=%d key=%s max=%d\n",larg, alt, key,max );//
    

    for(i=0;i< alt;i++){
		for(j=0;j< larg; j++){
				
			   if ((i*Sy < alt) && (j*Sx < larg) && (i*Sy >= 0) && (j*Sx >= 0))
				 	{
						gray = G[i*Sy][j*Sx].gray;
						fprintf(newImage, "%d ", gray);
					}
				else
				{
				// se preferir voce pode setar pra branco: G[i][j].gray = 255;
				fprintf(newImage, "%d ", G[i][j].gray);
				}
			
				
                //fprintf(newImage, "%d ", G[i][j].gray); // aqui vai ser a manipualão do pixel local

            }
            fprintf(newImage, "\n");
		}

	//fim
	fclose(image);
	fclose(newImage);
return 0;

}
