#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define w 1
#define ww w*4
#define N 2

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}
void CoupledMap(double x[],double epsilon)
	{	
    int i;
	double tmp=0;                       //e
    for(i=0; i<N; i++) tmp=tmp+x[i];    //e
    tmp=tmp*epsilon;                    //e
    for(i=0;i<N;i++) x[i]=(1.4-pow(fabs(x[i]),-0.25))+tmp;  //e
	//compile with -lm 
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
int ReadCuat(int a, int b,int c, int d){
    char QUAD[5]={a,b,c,d,'\0'};
    return(int)strtol(QUAD, NULL, 4);
}

int Decode(int hexas[],double epsilon,double x0[]){
    int i,k,st_bin[N],quad_linea[ww];
    for(i=0; i<4; i++){
        for(k=0; k<hexas[i]; k++)CoupledMap(x0,epsilon);
        st_bin[0]= x0[0]<0 ? 0:1;
        st_bin[1]= x0[1]<0 ? 0:1;
        quad_linea[i]=(Bin2Int(st_bin))+48; //sum 48 to read as char on ReadCuat()
    }
    return ReadCuat(quad_linea[0],quad_linea[1],quad_linea[2],quad_linea[3]);
}

int main(int argc, char **argv){
    clock_t start = clock();
    double epsilon=-0.025;
    int i,j,read;
    //DECLARATIONS
    FILE *pInput, *pOutput;
    unsigned char buffer1[1],buffer4[4];
    char buf[4];
    double x0[N];
    for(i=0; i<N; i++) x0[i]=10.0+(0.1*i); //Reiniciamos x0
    x0[0]=10.0;
    x0[1]=10.1;
    //FILE DATA
    const char* filename=argv[1];
    int size = fsize(filename);
    pInput=fopen(filename,"rb");
    int h=size/w;
    int res= size-(w*h);
    char hexa[4];
    int hexas[4],outH;
    //GET LEN OF EXT AND EXT
    read=fread(buffer1,sizeof(buffer1),1,pInput);
    sprintf(buf,"%d",buffer1[0]);
    int lenExt=atoi(buf);
    printf("lenExt: %d\n",lenExt);
    unsigned char bufferH[lenExt+1];
    read=fread(bufferH,lenExt,1,pInput);
    bufferH[lenExt]='\0';
    printf("Ext: %s\n",bufferH);
    //OUTPUT
    int lenName= strlen(filename);
    char out[lenName+lenExt];
    char filenameChar[lenName+1];
    for(i=0; i<lenName+1; i++) filenameChar[i]=filename[i];
    char *token=strtok(filenameChar,".");
    sprintf(out,"%s.%s", token,bufferH);
    pOutput=fopen(out,"wb");
    //READ AND WRITE FROM FILE TO DS
    int percentage= h/10;
    printf("size: %d\n",size);
    for(i=0; i<size-(lenExt+1); i+=4){
        if(i%percentage==0)printf("Progress: %.0f/100\n", ((float)i/h)*100);
        for (j = 0; j < 4; j++)
        {
            read=fread(buffer1,sizeof(buffer1),1,pInput);
            sprintf(hexa,"%d",buffer1[0]);
            hexas[j]=atoi(hexa);
        }
        //DECODE
        outH=Decode(hexas,epsilon,x0);
        buffer1[0]=outH & 0xFF;
        fwrite(buffer1, 1, sizeof(buffer1), pOutput);
    }
    //CLOSE FILES
    fclose(pInput);
    fclose(pOutput);
}
