#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

typedef struct{
	 float gray; //struct dos pixels em RGB;
}pixel;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i,j, larg, alt, max;
	int _i, _j, _gray;
	_gray=0;




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
		printf("Arquivo n é PGM\n");//checa se esta em P3
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
			fscanf(image, "%f", &G[i][j].gray );
		}
	}

	//grava header / dados
	fprintf(newImage, "P2\n%d %d\n%d\n",alt,larg,max);
    for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){

              _i = i;
              _j = j;
            // se a matriz for simetrica e tiver no intervalo (0 ... alt) x (0... larg) entao some os vizinhos e divida por 9
            if( (_i-1 >= 0) && (_i-1 < alt) && (_j-1 >= 0) && (_j-1 < larg) &&
                (_i-1 >= 0) && (_i-1 < alt) && (_j   >= 0) && (_j < larg) &&
                (_i-1 >= 0) && (_i-1 < alt) && (_j+1 >= 0) && (_j+1 < larg) &&

                (_i   >= 0) && (_i   < alt) && (_j-1 >= 0) && (_j-1 < larg) &&
                (_i   >= 0) && (_i   < alt) && (_j   >= 0) && (_j < larg) &&
                (_i   >= 0) && (_i   < alt) && (_j+1 >= 0) && (_j+1 < larg) &&

                (_i+1   >= 0) && (_i+1   < alt) && (_j-1 >= 0) && (_j-1 < larg) &&
                (_i+1   >= 0) && (_i+1   < alt) && (_j   >= 0) && (_j < larg) &&
                (_i+1   >= 0) && (_i+1   < alt) && (_j+1 >= 0) && (_j+1 < larg)

               )

            {
                _gray = G[i-1][j-1].gray + G[i-1][j].gray + G[i-1][j+1].gray +
                        G[i][j-1].gray   + G[i][j].gray   + G[i][j+1].gray +
                        G[i+1][j-1].gray + G[i+1][j].gray + G[i+1][j+1].gray;

                        _gray = _gray/9;
                        round(_gray); //trunca o ponto flutuante, arredondando p cima ou p baixo ,
                        fprintf(newImage, "%d ", _gray);


            }
            else {
                        fprintf(newImage, "%d ", G[i][j].gray );
            }
        
           }
            fprintf(newImage, "\n");
		}
	//fim
	fclose(image);
	fclose(newImage);
return 0;

}
