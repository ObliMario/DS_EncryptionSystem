#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define w 1
#define ww w*4
#define N 2
#define MAXCHAR 1000

int g(int c1, int c2, double x[],double epsilon)
	{    
    int iter=0;
    double tmp;
    int x2,x1;
	while(1)
		{
        x1= x[0]<0 ? 0:1;
        x2= x[1]<0 ? 0:1;
		if(x1==c1 && x2==c2)return iter;
		else {
            //Coupled Map
            tmp= (x[0]+x[1])*epsilon;
            x[0]=(1.4-pow(fabs(x[0]),-0.25))+tmp;  
            x[1]=(1.4-pow(fabs(x[1]),-0.25))+tmp;  
			iter++;
			}		
		}   
}

void CodeLine(double epsilon,char input[], int output[], double x[]){
    int i,j;
    j=0;
    for(i=0; i<8; i+=2){
        output[j]=g(input[i]-48,input[i+1]-48,x,epsilon);
        j++;
    } 
}

int readline(FILE *f, char *buffer, size_t len)
{
   char c; 
   int i;

   memset(buffer, 0, len);

   for (i = 0; i < len; i++)
   {   
      int c = fgetc(f); 

      if (!feof(f)) 
      {   
         if (c == '\r')
            buffer[i] = 0;
         else if (c == '\n')
         {   
            buffer[i] = 0;

            return i+1;
         }   
         else
            buffer[i] = c; 
      }   
      else
      {   
         //fprintf(stderr, "read_line(): recv returned %d\n", c);
         return -1; 
      }   
   }   
   return -1; 
}

int main(int argc, char **argv){
    double epsilon=-0.025;
    int i,j;
    int coded[ww];
    double x0[N];
    x0[0]=10.0;
    x0[1]=10.1;
    char binary[9];
    char *filename;
    filename = argv[1];
    FILE *fp;
    char info[MAXCHAR];
    //fp = fopen(filename, "r");
    if ((fp = fopen("uncoded.txt", "r")) == NULL){
        printf("Error! opening file\n");
        exit(1);
    }
    fgets(info,MAXCHAR,fp);
    //fscanf(fp, "%[^\n]", info);
    printf("Data from the file:\n%s\n", info);
    fclose(fp);
    //char info[100000];
    int infolen=strlen(info);
    
    printf("info: %s ; len:%d\n",info,infolen);
    
    char currentChar;
    unsigned char pair;
    
    FILE *fptr;
    fptr = fopen("coded.txt", "w");

    for(i=0; i<infolen; i++){
        currentChar=info[i];
        for (j = 0; j < 8; j++) sprintf((char*)(binary+j),"%d", !!((currentChar << j) & 0x80));
        CodeLine(epsilon,binary,coded,x0);
        if(i==infolen-1) fprintf(fptr, "%d,%d,%d,%d", coded[0],coded[1],coded[2],coded[3]);
        else  fprintf(fptr, "%d,%d,%d,%d,", coded[0],coded[1],coded[2],coded[3]);
    }
    
    fclose(fptr);
    return 0;
}
