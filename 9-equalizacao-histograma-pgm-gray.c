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
	int k;
	double prob[255], prob_acum[255], hist[255], total_pixels, new_gray, contador;


	total_pixels = 0; 
	new_gray = 0;
	contador =0;
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
	// setar para zero todos os valores do vetor vetor hist[k], prob[k] e prob_acum[k];
	for (k=0 ; k<255 ; k++)
	{
		hist[k]=0;  prob[k]=0; //prob_acum[k]=0;
	}
 	//grava header / dados
	fprintf(newImage, "P2\n%d %d\n%d\n",alt,larg,max);
	// laco p acumular no hist[k] a qtd de ocorrencias de cada pixel
	for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){
            for (k=0; k<=255 ; k++)  // contador p acumular hist[k]
            {
                if (G[i][j].gray == k) 
                {
                    hist[k]++;
                }
            }
    
		}
	}
	// laco que apresenta os valores do hist[k]
	for (k=0; k < 10 ; k++)
	{
		printf("Hist[%d] = %.0lf\n", k, hist[k]);
	}
	printf("\n\n");
	// laco p calcular o valor acumulado hist[k]
	for (k=0; k < 255 ; k++)
	{
		total_pixels = total_pixels + hist[k];
	}
	// laco p calcular a probabilidade  do hist[k]
	printf("total de pixels da img: %.lf \n\n", total_pixels);
	// laco p calcular a probabilidade do pixel
	for (k=0; k < 255 ; k++)
	{
		prob[k] = (hist[k] / total_pixels);
		//hist_pixel = 0 ;
	}
	// faco p exibir os valores da porbabilidade
	for (k=0; k < 10 ; k++)
	{
		printf("ProbabilidadePixel[%d]=%.21lf\n", k, prob[k] );
		//hist_pixel = 0 ;
	}
	

	// zerar a probabilidade acumulativa

	for (k=0 ; k<255 ; k++)
	{
		prob_acum[k]=0;
	}
	// laco p calcular a probabilidade acumulativa prob_ac[k] // ta so copiando o vetor, tem que acumular aki ta o erro
	for (k=0; k < 255 ; k++)
	{

		contador = contador + prob[k];
		prob_acum[k] = contador;

	}
	// laco que apresenta a prob acumulativa
	for (k=250; k < 255 ; k++)
	{
		printf("Resultado: Prob_acum[%d] = %.21lf --- \n",k, prob_acum[k] );
	}
	

	
	printf("\n\n ProbAcum[%d] =  %lf\n",k , prob_acum[254]);
	// laco p gravar na matriz o produto prob_ac[k] * hist[k]  // me enrolei aki
	
	for(i=0;i<alt;i++){
		for(j=0;j<larg; j++){

			for (k=0; k<=255 ; k++)  // contador p acumular hist[k]
            {
                if (G[i][j].gray == k) 
                {
                   new_gray = (prob_acum[k] * 255); // neste caso estou mutiplicando pela maxima intensidade
                   fprintf(newImage, "%.0lf ", new_gray); // aqui vai ser a manipualão do pixel local
                	new_gray = 0 ;
                }
            }
                
            }
            fprintf(newImage, "\n");
		}
	
 
	//fim
	fclose(image);
	fclose(newImage);
return 0;
}
