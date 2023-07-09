#include<stdio.h>
int main()
{
    int p;
    printf("Mark in physics: ");
    scanf("%d",&p);
    if(100>p && p>80){
        printf("you got A+");
    }
    else if( p>70 && p<79){
        printf("You got A");
    }
    else if(p>60 && p<69){
        printf("you got A-");
    }
    else {
        printf("you fail");
    }


}
