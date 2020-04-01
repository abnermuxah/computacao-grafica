#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	unsigned int gray; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i,j, larg, alt, max;
	int maior, menor, id_min, id_max; // valores entre (min e max) vao aparecer, os valores fora dessa escala fica preto!
	int gray;
	
	id_max = 150;
	id_min = 50;
	gray = 0;
	
	


    //entrada
   
	image = fopen("lena.pgm", "r");
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

	// laco p achar a maior e menor intensidade da img
    maior = G[0][0].gray;
    menor = G[0][0].gray;
	for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){
				
					
				if (G[i][j].gray > maior)
				{
					maior = G[i][j].gray;
				}
				if (menor > G[i][j].gray )
				{
					menor = G[i][j].gray;
				}

                // fprintf(newImage, "%d ", G[i][j].gray); // aqui vai ser a manipualão do pixel local

            }
            
		}

		printf("O maior valor da imagem de entrada eh: %d\n", maior );
		printf("O menor valor da imagem de entrada eh: %d\n", menor );
		printf("O ID_MAX digitado pelo usuario foi: %d\n", id_max );
		printf("O ID_MIN digitado pelo usuario foi: %d\n", id_min );
		if ((maior-menor) <= 0)
		{
			printf("Operacao Invalida, Tente de novo com outra imagem\n");
			fclose(image);
			fclose(newImage);
			system("PAUSE");
			exit(0);

		}
	// fim laco


	//grava header / dados
	fprintf(newImage, "P2\n%d %d\n%d\n",alt,larg,max);

    for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){
				
				gray = (G[i][j].gray - menor)*(id_max - id_min)/(maior - menor) + menor;
                fprintf(newImage, "%d ", gray); // aqui vai ser a manipualão do pixel local
                gray =0;

            }
            fprintf(newImage, "\n");
		}

	//fim
	fclose(image);
	fclose(newImage);
return 0;

}
