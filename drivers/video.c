
#define CHAR_PER_LINE80
#define VIDEO_MEMORY 0xb8000
#define VIDEO_CONTROL_PIN 0x3D4
#define VIDEO_DATA_PIN 0x3D5

int cursor_pos=-1;


//read data from pin
unsigned char port_byte_read(unsigned short port ) {

unsigned char result ;
__asm__ ( "in %%dx,%%al":"=a"( result ):"d"( port ));
return result ;

}


//write data to pin
void port_byte_write(unsigned short port ,unsigned char data ) {

__asm__ ("out %%al,%%dx" : : "a"( data ) ,"d"( port ));
}



//return 2 byte.hight 14,low 16
int get_cursor_pos()
{
	if(cursor_pos==-1)
	{
		cursor_pos=0;

		 
		port_byte_write(VIDEO_CONTROL_PIN,14);
	    cursor_pos=port_byte_read ( VIDEO_DATA_PIN)<<8;	
	     


		port_byte_write ( VIDEO_CONTROL_PIN , 15);
		cursor_pos+= port_byte_read ( VIDEO_DATA_PIN);
	}
return cursor_pos;

}




void set_cursor_pos(int x,int y)
{
  
   int pos = y * 80 + x;
   cursor_pos=pos;
   port_byte_write(0x3D4, 14);         
   port_byte_write(0x3D5, pos >> 8);
   port_byte_write(0x3D4, 15);
   port_byte_write(0x3D5, pos);



}



void clear_screen()
{


	char* screen=(char*)VIDEO_MEMORY;
	for (int i = 0; i < 4000; i++)
	   {
	       *screen =0x20;
	       *(screen+1)=0x02;


	       screen+=2;
	   }
	set_cursor_pos(0,0);
	printtext("                           <<NOBOTRO OS v -9.1>>                                \n",0xa0,0);

}

void scroll()
{
	//clear row #2
	char* screen=(char*)VIDEO_MEMORY+320;
	for(int i=0;i<3840;i++)
	{
		*(screen-160)=*screen;

		screen++;

	}



}
void move_next_cursor()
{
	int curpos=get_cursor_pos();


	int y=curpos/80;
	int x=curpos%80;
	x+=1;
	if(x==80)
	{
		y+=1;
		x=0;
		 
	}
	if(y==25)
	{
		scroll();
		x=0;
		y-=1;
	}
	set_cursor_pos(x,y);

}


void printchar(char c,char colors,char toblink)
{
	 
	int curpos=get_cursor_pos()*2;
	char* screen=(char*)curpos+VIDEO_MEMORY;
	if(c=='\n')
		{

			next_line();
			curpos=get_cursor_pos()*2;
			screen=(char*)curpos+VIDEO_MEMORY;
			return;
		}

		 
	*screen=c;

	 
	if(c==toblink)
	{
		*(screen+1)=colors|0b10000000;
	}
	else *(screen+1)=colors;
	screen+=2;
	move_next_cursor();

}
void printtext(char* text,char colors,char toblink)
{

	char c=0;
	int curpos=get_cursor_pos()*2;
	char* screen=(char*)curpos+VIDEO_MEMORY;
	
	while((c=*text++)!='\0')
	{		
		printchar(c,colors,toblink);
	}
}


void next_line()
{
	int curpos=get_cursor_pos();
	int y=curpos/80;
	int x=curpos%80;
	x=0;
	y+=1;
	if(y==25)
	{
		scroll();
		x=0;
		y-=1;
	}

	set_cursor_pos(x,y);
	printtext(">",0x0a,0);


}

void rm_char_in_pos(int pos)
{

	int y=pos/80;
	int x=pos%80;
	int yp=(y*160)+VIDEO_MEMORY;
	*((char*)yp+(x*2))=0x00;
	*((char*)yp+(x*2)+1)=0x02;
	set_cursor_pos(x,y);

}

