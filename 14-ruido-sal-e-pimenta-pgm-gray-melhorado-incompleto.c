#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct{
	unsigned int gray; //struct dos pixels em RGB;
}pixel;

int main(){

	srand(time(NULL)); // funcao p gerar numero aleatorio
	FILE *image;
	FILE *newImage;

	char key[5];
	int i,j, larg, alt, max;
	int qtd, num;
	qtd = 4;

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


	//grava header / dados
	fprintf(newImage, "P2\n%d %d\n%d\n",alt,larg,max);
	qtd=0;
    for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){

                
                // esse funcionou mais gastou 1 minuto pra concluir
                	num = (rand()%20);
                	if (num == 0)
                	{
                		fprintf(newImage, "0 ");;	
                	}
                	if (num == 1) 
                	{
                		fprintf(newImage, "255 ");	
                	}
                	if (num >= 2) 
                	{
                		fprintf(newImage, "%d ", G[i][j].gray);
                	}
                
                
                
            }
            fprintf(newImage, "\n");
		}

	//fim
	fclose(image);
	fclose(newImage);
return 0;

}
