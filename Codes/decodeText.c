#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define w 1
#define ww w*4
#define N 2

int ReadCuat(int a, int b,int c, int d){

    char QUAD[5]={a,b,c,d,'\0'};

    return(int)strtol(QUAD, NULL, 4);

}

int Bin2Int(int aBin[]) {
  if (aBin[0]==0){
      if (aBin[1]==0) return 0;
      else return 1;
  }else
  {
      if (aBin[1]==0) return 2;
      else return 3;
  }
  
}

void CoupledMap(double x[],double epsilon)
	{	
    int i;
	double tmp=0;                       //e
    for(i=0; i<N; i++) tmp=tmp+x[i];    //e
    tmp=tmp*epsilon;                    //e
    for(i=0;i<N;i++) x[i]=(1.4-pow(fabs(x[i]),-0.25))+tmp;  //e
    
	//Para que funcione, debo compilar con -lm al final
}

int Decode(int hexas[],double epsilon,double x0[]){
    int i,k,st_bin[N],quad_linea[ww];
    //for(i=0; i<4; i++)printf("%d ",hexas[i]);
    //printf("\n");
    for(i=0; i<4; i++){
        for(k=0; k<hexas[i]; k++)CoupledMap(x0,epsilon);
        st_bin[0]= x0[0]<0 ? 0:1;
        st_bin[1]= x0[1]<0 ? 0:1;
        quad_linea[i]=(Bin2Int(st_bin))+48; //Le sumamos 48 para que se lea como char en ReadCuat()
    }
    return ReadCuat(quad_linea[0],quad_linea[1],quad_linea[2],quad_linea[3]);

}

int main(int argc, char **argv){
    double epsilon=-0.025;
    int i,j;
    double x0[N];
    int fourints[ww],outIntChar;
    unsigned char Char;

    x0[0]=10.0;
    x0[1]=10.1;

    int inputlen =0;
    char *info = NULL;
    info = argv[1];
    char info2[100000];
    //printf("info: %s\n",info);
    strcpy(info2,info);
    //printf("info2: %s\n",info2);
    
    char *token = strtok(info2, ",");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        inputlen++;
        token = strtok(NULL, ",");
    }
    //***************
    int input[inputlen];
    token = strtok(info, ",");
    // loop through the string to extract all other tokens
    int cont=0;
    while( token != NULL ) {
        input[cont]=atoi(token);
        cont++;
        token = strtok(NULL, ",");
    }
    //int inputlen = sizeof input / sizeof input[0];
    printf("Input len: %d\nInput:",inputlen);
    for(int i=0; i<inputlen;i++) printf("%d,", input[i]);
    printf("\nOut: ");
    FILE *fptr;
    fptr = fopen("decoded.txt", "w");

    for(int i=0; i<inputlen; i+=4){
        for(j=0;j<ww;j++) fourints[j]=input[i+j];
        outIntChar=Decode(fourints,epsilon,x0);
        Char=outIntChar & 0xFF;
        fprintf(fptr, "%c", Char);
        printf("%c",Char);
    }
    printf("\n");
    fclose(fptr);
    return 0;
}
