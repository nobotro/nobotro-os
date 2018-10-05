
#include "../include/string.h"

//random number generator
int rand(int start,int end)
{

    extern int krand(int,int);
 
   return krand(start,end);

}

int atoi(char *string)
{



char a=0;
int res=0;
while((a= *string++)!='\0')
    {
         
         res = res*10 + a - '0';
           
          
        
    }

return res;
}



void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }


void sleep(int milisecond)
{
extern void ksleep(int);

 ksleep(milisecond);
 

}