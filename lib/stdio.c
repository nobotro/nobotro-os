#include "../include/keyboard.h"

#include "../include/video.h"

void scan(char* buf,int n)
{

char key=0;
int i=0;
char stat=1;
int startpos=get_cursor_pos()%80;
					 
while(stat) // '\n is enter press key code'
	{
		key=get_key();
		if(key==0)continue;
		switch(key)
		{
			case '\n'://if enter press

				printchar('\n',0x0a,0);
				stat=0;
				break;

			case '\b':
				if(i>0)
				{
					int x=get_cursor_pos();
					  
					 
						rm_char_in_pos(x-1);



						i--; 
						buf--;

				

				
				}
				 
				//erase
				break;
			case '<':
				//move left cursor
				break;
			case '>':
				//move right
				break;

			default:
				if(i<n-1)
				{

					*buf++=key;
					printchar(key,0x0a,0);
					i++;
				}
				
				break;






		}
		


	}

*(buf++)='\0';



}
