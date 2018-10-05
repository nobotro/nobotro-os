#include "../include/stdlib.h"
 #include "../include/string.h"
#include "../include/video.h"
 #include "../include/stdio.h"
#include "../include/keyboard.h"
 

char* whoami=
"  .     .  :     .    .. :. .___---------___.\n"
"       .  .   .    .  :.:. _\".^ .^ ^.  '.. :\"-_. .\n"
"    .  :       .  .  .:../:            . .^  :.:\\.\n"
"        .   . :: +. :.:/: .   .    .        . . .:\\\n"
" .  :    .     . _ :::/:               .  ^ .  . .:\\\n"
"  .. . .   . - : :.:./.                        .  .:\\\n"
"  .      .     . :..|:           nobotro  .  .  ^. .:|\n"
"    .       . : : ..||        .                . . !:|\n"
"  .     . . . ::. ::\\(                           . :)/\n"
" .   .     : . : .:.|. ######              .#######::|\n"
"  :.. .  :-  : .:  ::|.#######           ..########:|\n"
" .  .  .  ..  .  .. :\\ ########          :######## :/\n"
"  .        .+ :: : -.:\\ ########       . ########.:/\n"
"    .  .+   . . . . :.:\\. #######       #######..:/\n"
"      :: . . . . ::.:..:.\\           .   .   ..:/\n"
"   .   .   .  .. :  -::::.\\.       | |     . .:/\n"
"      .  :  .  .  .-:.\":.::.\\             ..:/\n"
" .      -.   . . . .: .:::.:.\\.           .:/\n"
".   .   .  :      : ....::_:..:\\   ___.  :/\n"
"   .   .  .   .:. .. .  .: :.:.:\\       :/\n"
"     +   .   .   : . ::. :.:. .:.|\\  .:/|\n"
"     .         +   .  .  ...:: ..|  --.:|\n";



char* calc=
"+---------------------------+\n"
"| ///////////////////////// |\n"
"+---------------------------+\n"
"| [              1,264.45 ] |\n"
"+---------------------------+\n"
"|                           |\n"
"|                           |\n"
"| [sto] [rcl] [<--] [AC/ON] |\n"
"|                           |\n"
"| [ ( ] [ ) ] [sqr] [  /  ] |\n"
"|                           |\n"
"| [ 7 ] [ 8 ] [ 9 ] [  *  ] |\n"
"|                           |\n"
"| [ 4 ] [ 5 ] [ 6 ] [  -  ] |\n"
"|                           |\n"
"| [ 1 ] [ 2 ] [ 3 ] [  +  ] |\n"
"|                           |\n"
"| [ 0 ] [ . ] [+/-] [  =  ] |\n"
"|                           |\n"
"+---------------------------+\n";
  

void startcalc();

void main() {

	clear_screen();
	while(1)
	{
		char buf[20];
		scan(buf,10);
		if(strcmp(buf,"whoami")==0)
		{
			 printtext(whoami,0x0a,'#');

		}

		else if(strcmp(buf,"calc")==0)
		{

		  startcalc();
		  printtext("quited from calc\n",0x04,0);
		}
		else if(strcmp(buf,"help")==0)
		{
		 printtext("commands: \ncalc-->start calc\nwhoami-->print me :D\nhelp-->print that\nclear-->clear screen\n",0x0a,0);
		}
		else if(strcmp(buf,"clear")==0)
		{
			clear_screen();
		}
		else if (strlen(buf)>0)printtext("unknown command\n",0x04,0);

	}
	 




}
void startcalc()
 {	
	printtext(calc,0x0a,'#');
	next_line();
	printtext("operand a,b.operation +,-,/,* q-quit from calc write ops with numpad\n",0x0a,0);
		  
 	int stat=1;
 	while(stat)
 	{
		 next_line();
		printtext("a:",0x0a,0);

		char ac[10];
		scan(ac,10);

		int a=atoi(ac);

		printtext("b:",0x0a,0);

		char bc[10];
		scan(bc,10);
		int b=atoi(bc);


		printtext("op:",0x0a,0);
		char op[2];
		scan(op,2);

		 
		switch(op[0])
		{	char res[10];
			case '-':
			
				itoa((a-b),res);

				printtext(res,0x0a,0);
				break;

			case '+':

				
				itoa((a+b),res);

				printtext(res,0x0a,0);
				break;

			case '*':
 
				
				itoa((a*b),res);

				printtext(res,0x0a,0);
				break;

			case '/':

				
				itoa((a/b),res);

				printtext(res,0x0a,0);
				break;

			case 'q':
				stat=0;
				break;

		}




	}


 }





