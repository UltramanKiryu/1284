/*
 Name: Andrew Banks
 NetID: alb1424
 Compiler: online gbd
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
//storeing the game board an 3x3 array of 1,0,-1
//crearte  two semaphroes  one for each player
//same flage the are uses just like in createing read/write files
// to genterate the random numbers inoder of the
//use  binary semaphores in

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
        if(pl==-1)// player 1 turn
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
                arr[2][1]=1;
            }
            //trying to win via the left columne
            else if(arr[0][0]==0)
            {
                arr[0][0]=1;
            }
            else if(arr[0][0]==1)
            {
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
                if(arr[1][0]==0)
                {
                     arr[1][0]=1;
                }
                else if(arr[1][2]==0)
                {
                     printf("hell");
                     arr[1][2]=1;
                }
            }

            // try to win via the right columne
           else if(arr[0][2]==0)
           {
                printf("heell");
                arr[0][2]=1;
           }
            else if(arr[0][2]==1)
            {
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

            else if(arr[1][1]==1)
            {
                printf("hell");
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
            // swtiching to player 2
            pl=-2;
        }
        if(pl==-2)// player 2 turn
        {
            int y=0;
            printf("\n");
            for(i=0;i<3;i++)// dispaling the game board
             {
                 printf("\n");
                 for(j=0;j<3;j++)
                 {
                      printf("%d\t",arr[i][j]);// displaying each place in the board
                 }
             }

            // if right down going to win

            // start of player 2 descion
            if(arr[1][1]==1&&y==0)
            {
                // see if top left is empty
                if(arr[0][0]==0)
                {
                    arr[0][0]=-1;
                }

            }
            // to see if player 1 is about to win via the middle colume
            if(arr[0][1]==1) //middle down
            {
                if(arr[1][1]==1)
                {
                    if(arr[2][1]==0)// see if middle bottome is empty
                    {
                        arr[2][1]=-1;
                    }
                }
                if(arr[2][1]==1)
                {
                    if(arr[1][1]==0)// see if middle midddle is empty
                    {
                        arr[1][1]=-1;
                    }
                }
            }

            // to see if player 1 is about to win via the left colume
            if(arr[0][0]==1) //left top cronor
            {
                if(arr[1][0]==1)// left middle
                {
                    if(arr[2][0]==0) // left bottom
                    {
                        arr[2][0]=-1;
                    }
                }
                if(arr[2][0]==1)
                {
                    if(arr[1][0]==0)
                    {
                       arr[1][0]=-1;
                    }
                }
            }

            // see if player 1 is about of win via right colume
            if(arr[0][2]==1) // right top conor
            {
                if(arr[1][2]==1)// right middle
                {
                    if(arr[2][2]==0) //right bottom is empty
                    {
                        arr[2][2]=-1;
                    }
                }
                if(arr[2][2]==1)// right bottom
                {
                    if(arr[1][2]==0)// right middle is empty
                    {
                        arr[1][2]=-1;

                    }
                }
            }

            // see if the player1 is about to win via top row
            if(arr[0][0]==1)
            {
                if(arr[0][1]==1)
                {
                    if(arr[0][2]==0)
                    {
                        arr[0][2]=-1;
                    }

                }
                if(arr[0][2]==1)
                {
                    if(arr[0][1]==0)
                    {
                        arr[0][1]=-1;
                    }
                }
            }

            // see if the player1 is about to win via middle row
            if(arr[1][0]==1)
            {
                if(arr[1][1]==1)
                {
                    if(arr[1][2]==0)// right middle is empty
                     {
                         arr[1][2]=-1;
                     }
                }
                if(arr[1][2]==1)
                {
                   if( arr[1][1]==0)
                   {
                        arr[1][1]=-1;
                   }
                }
            }

            // see if the player1 is about to win via bottom row
            if(arr[2][0]==1)
            {
                if(arr[2][1]==1)
                {
                    if(arr[2][2]==0)
                    {
                        arr[2][2]=-1;
                    }
                }
                if(arr[2][2]==1)
                {
                    if(arr[2][1]==0)
                    {
                        arr[2][1]=-1;
                    }
                }
            }

            // see if the player1 is about to win via the right diagonal left top cornor to right bottom conor
            if(arr[2][2]==1)
            {
                if(arr[1][1]==1)
                {
                    if(arr[0][0]==0)
                    {
                        arr[0][0]=-1;
                    }
                }
                if(arr[0][0]==1)
                {
                    if(arr[1][1]==0)
                    {
                        arr[1][1]=-1;
                    }
                }
            }

            // see if the player1 is about to win via the left diagonal left top cornor to right bottom conor
            if(arr[0][2]==1)
            {
                if(arr[1][1]==1)
                {
                    if(arr[2][0]==0)
                    {
                        arr[2][0]=-1;
                    }
                }
                if(arr[0][2]==1)
                {
                    if(arr[1][1]==0)
                    {
                        arr[1][1]=-1;
                    }
                }
            }
            // return to player 1
            pl=-1;
        }
    }
    if(tt==9){
    printf("\nits a tie\n");
    }
    return 0;
}
