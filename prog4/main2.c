#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
// always check for a win then check for a block
//ipv4 is thr og domain-> ivp6 is the replacement
// UDP-> unvisearl datagram protocal TPC ->transmission control protocol
int main(int argc, char *argv[])
{
    int pl=0;
    int o=0;
    int tt=0;
    int turn=0;
    int arr[3][3],i=0,j=0;
    if (argc > 1)
        {
        pl =atoi(argv[1]);
        }
    for(i=0;i<3;i++)// making the game board
     {
         for(j=0;j<3;j++)
         {
             arr[i][j]=0; // assign each spot as empty
         }
     }
     while (turn > -1)
     {
         for(i=0;i<3;i++)
          {
              for(j=0;j<3;j++)
              {
                  if(arr[i][j]!=0)//checking if the game board is full
                  {
                      tt++;
                  }
              }
          }
         if(tt==9)
         {
             break;
         }
         tt=0;
         if(pl==-1)
         {
             int ti=0;
             printf("\n");
             for(i=0;i<3;i++)// dispaling the game board
              {
                  printf("\n");
                  for(j=0;j<3;j++)
                  {
                       printf("%d\t",arr[i][j]);// displaying each place in the board
                  }
              }
             if(arr[1][1]==0)
             {
                 arr[1][1]=1;
             }
             // if the center is has an x and try to win through the middle colume
             else if(arr[0][1]==0)
             {
                 arr[0][1]=1;

             }
             else if(arr[2][1]==0)
             {
                 printf("heell");
                 arr[2][1]=1;
             }

             //trying to win via the left columne
             else if(arr[0][0]==0)
             { printf("hellqqq");
                 arr[0][0]=1;
             }
             else if(arr[0][0]==1)
             {
                  printf("hellww");
                 if(arr[1][0]==0)
                 {
                     arr[1][0]=1;
                 }
                 else if(arr[2][0]==0)
                 {
                     arr[2][0]=1;
                 }
             }
             // try to win via the middle row
             else if(arr[1][1]==1)
             {
                  printf("hellw");
                 if(arr[1][0]==0)
                 {
                      arr[1][0]=1;
                 }
                 else if(arr[1][2]==0)
                 {

                      arr[1][2]=1;
                 }
             }
             // try to win via the right columne
            else if(arr[0][2]==0)
            {
                 printf("hll");
                 arr[0][2]=1;
            }
             else if(arr[0][2]==1)
             {
                 printf("hll");
                 if(arr[1][2]==0)
                 {
                     arr[1][2]=1;
                 }
                 else if(arr[2][2]==0)
                 {
                     arr[2][2]=1;
                 }
             }
             // try to win via the top row
            else if(arr[0][0]==0)
            {
                 arr[0][0]=1;
            }
             else if (arr[0][1]==1)
             {
                 printf("heell");
                 if(arr[0][1]==0)
                 {
                      arr[0][1]=1;
                 }
                 else if(arr[0][2]==0)
                 {
                      arr[0][2]=1;
                 }
             }
             // trying to win via the bottom row
             else if(arr[2][0]==0)
             {
                 printf("ell");
                  arr[2][0]=1;
             }
             else if(arr[2][0]==1)
             {
                 if(arr[2][1]==0)
                 {
                      arr[2][1]=1;
                 }
                 else if(arr[2][2]==0)
                 {
                      arr[2][2]=1;
                 }
             }
             // trying to win via diagonal from left to right
             else if(arr[0][0]==1)
             {
                 printf("ll");
                 if(arr[1][1]==1)
                 {
                     if(arr[2][2]==0)
                     {
                         arr[2][2]=1;
                     }
                 }
             }
             // trying to win via diagonal form right to left
             else if(arr[0][2]==0)
             {
                 printf("hell");
                 arr[0][2]=1;
             }
             else if(arr[0][2]==1)
             {
                 if(arr[0][2]==1)
                 {
                     if(arr[2][0]==0)
                     {
                         arr[2][0]=1;
                     }
                 }
                 else if(arr[2][0]==1)
                 {
                     if(arr[0][2]==0){
                         arr[0][2]=1;
                     }
                 }
             }
             pl=-2;
         }
         if(pl==-2)
         {
             printf("\n");
             for(i=0;i<3;i++)// dispaling the game board
              {
                  printf("\n");
                  for(j=0;j<3;j++)
                  {
                       printf("%d\t",arr[i][j]);// displaying each place in the board
                  }
              }
             printf("\n where do you want to put an X\n");
             scanf("%d",&o);
             if(o==1)
             {
                 //printf("1\n");
                 if(arr[0][0]==0)
                 {
                     arr[0][0]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==2)
             {
                 //printf("2\n");
                 if(arr[0][1]==0)
                 {
                 arr[0][1]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==3)
             {
              //   printf("3\n");
                 if(arr[0][2]==0)
                 {
                     arr[0][2]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }

             }
             if(o==4)
             {
                // printf("4\n");
                 if(arr[1][0]==0)
                 {
                     arr[1][0]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==5)
             {
                 //printf("5\n");
                 if(arr[1][1]==0)
                 {
                     arr[1][1]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==6)
             {
                 //printf("6\n");
                 if(arr[1][2]==0)
                 {
                     arr[1][2]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==7)
             {
                 //printf("7\n");
                 if(arr[2][0]==0)
                 {
                     arr[2][0]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==8)
             {
                 //printf("8\n");
                 if(arr[2][1]==0)
                 {
                     arr[2][1]=-1;
                 }
                 else
                 {
                     printf("try another spot");
                 }
             }
             if(o==9)
             {
                 //printf("9\n");
                 if(arr[2][2]==0)
                 {
                     arr[2][2]=-1;
                 }
                 else
                 {
                     printf("try another spot\n");
                 }
             }
             // swtiching to player 1
             pl=-1;
         }
     }
    return 0;
}
