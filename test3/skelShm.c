#include <stdio.h>
#include<stdlib.h>
#include<time.h>
//#include"Semun.h"
//#include<Binary_Sem.h>

int main(int argc, char*argv[])
{
    srand(time(NULL));
    //printf("Amount: %c ", ran);
    int count =0;
    int w=0;
    int block = (rand()%10)+10;// amount of blocks
    int width = rand()%6+10;// width of the Acsii text

    while(count<=block){
        int ran= rand()%25+97;// generate the letter use is the Acsii text
        int length = rand()%10+2;// length of the Acsii text
    for(int i=0;i<=length;i++)
    {
        printf("%c", ran);
        w++;
        if(w==15)
        {
            printf("\n");
            w=0;
        }
    }
    count++;
    }
    printf("\n");

    return 0;
}
