/*  p1.cpp
 *  Created by Devin Shively on 1/25/11.
 *  Modified Heavily By Miguel Diaz
 *  Tested by Danny, and Nick
 */     


#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//-Miguel: ended up having to change some of the include files to something
//more recent. Was getting some errors compiling in g++
//so i used fstream, iomanip, iostream. 
fstream file;
int datafile = 0,eos,err,len,nstring=0,ok,out;
char ext[] = {  63, 63, 63, 61, 43, 45, 42, 47, 65, 66,
				67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
				77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
				87, 88, 89, 90, 97, 98, 99,100,101,102,
			   103,104,105,106,107,108,109,110,111,112,
			   113,114,115,116,117,118,119,120,121,122},
			inform[241],rpn[241],str[241],stak[80];

int main(int argc, char *argv[])
{
	int atend( void );
	void deleteblanks( void ), drawline( void ), echoprint( void ),
			gencode( void ), getstring( void ), internalize( void ),
			makerpn( void ), parse( void );
	
	if( 2 < argc )
	{
		cout << "** use is >p1 [input_file_name] **\n";
		exit( 1 );
	}
	
	if( argc == 2 )
	{
		file.open( *++argv,ios::in|ios::out); // had to add ios::out else g++ errored
		if( file.fail() )
		{
			cout << "** can't open \"" << *argv << "\" **\n";
			exit( 1 );
		}
		datafile = 1;
	}
	
	while( 1 )
	{
		getstring();
		echoprint();
		deleteblanks();
		
		if( atend() )
		{
			break;
		}
		else 
		{
			internalize();
			if( !err )
			{
				parse();
				if( !err )
				{
					makerpn();
					gencode();
				}
			}
		}
		drawline();
	}
	
	if( datafile )
	{
		file.close();
	}
	
	return 0;
}

int atend()
{   
	//changed stricmp to strcasecmp because stricmp isnt even in c standard works the same
	return ( (len == 3) && (strcasecmp( str,"end" ) == 0) );
}

void deleteblanks()
{
	char *p,*q;
	
	cout << "String with no blank or tab:\n\n";
	
	
	for( p = q = str, len = 0; *p; p++ )
	{
		if( (*p != ' ') && (*p != '\t') && (*p != '\n') && (*p != '\r') )
		{
			len++;
			*q++ = *p;
		}
	}
		   
	*q = '\0';
	cout << str << "\n\n";	   
}

void drawline()
{
	int i;
	
	for( i = 80; --i; )
	{
		cout << '.';
	}
	
	cout << '\n';
}

void echoprint()
{
	cout << "\nData string " << nstring << ":\n\n" << str << "\n\n";
}

void emit( char a, char n )
{
	static char *op[]={"***","lod","sto","***","add","sub","mul","div"};
	
	cout << setw(5) << ++len << "	" << op[(int)a];
	
	if( n < 60)
	{
		cout << "	" << ext[(int)n];
	}
	
	else
	{
		cout << "	t.";
		
		if( 60 < n )
		{
			cout << '+' << n-60;
		}
	}
	
	cout << '\n';
}

void gencode()
{
	void emit( char,char );
	char a,j,lop,n1,n2,*p,*t;
	
	cout << "Generated symbolic code:\n\n";
	j = len = lop = 0;
	t = p = rpn;
	
	while( 3 < (a = *++p) )
	{
		if( 7 < a )
		{
			*++t = a;
			if( (++lop == 2) && (0 < len) )
			{
				n2 = *t--;
				n1 = *t--;
				*++t = j + 60;
				*++t = n1;
				*++t = n2;
				emit( 2,( j++ ) + 60 ); 
			}
		}
		else
		{ 
			if( lop == 1 )
			{
				emit( a, *t-- );
			}
		    
			else
				{
			 		if( 1 < lop )
					{
						n2 = *t--;
						n1 = *t--;
						emit( 1, n1 );
						emit( a, n2 );
					}
		
					else if( ( a == 4 ) || ( a == 6 )  )
					{
						n1 = *t--;
						emit ( a, n1 );
					}
		
					else
					{
						n1 = *t--;
						emit( 2, j + 60 );
						emit( 1, n1 );
						emit( a, j + 60 );
					}
					if( 59 < n1 )
					{
						--j;
					}
				}
				lop = 0;
		}
		
	}
	
	if( len == 0 )
	{
		emit( 1, rpn[1] );
	}
	emit( 2, *rpn );
}

void getstring()
{
	if( datafile )
	{
		file.getline( str,241 );
	}
	
	else
	{
		cout << "Enter a string, please:\n\n";
		cin.getline( str,241 );
	}
	
	nstring++;
}

void internalize()
{
	int i,j;
	static char inter[]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 4, 0, 5, 0, 7,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
						  0, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,
						 23,24,25,26,27,28,29,30,31,32,33, 0, 0, 0, 0, 0,
						  0,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,
						 49,50,51,52,53,54,55,56,57,58,59, 0, 0, 0, 0, 0};
	char ch,code,k,*p,*q;
	
	cout << "Internal form:\n\n";
	
	k = 0;
	q = inform;
	
	for(p = str; *p; p++)
	{
		*q++ = code = inter[(int)*p];
		
		if( k + code == 0)
		{
			k = p-str + 1;
			ch = *p;
		}
	}
	
	*q = '\0';
	
	for(i = j = 0, p = inform; j < len; p++, j++)
	{
		cout << setw(3) << (int)*p;
		if( ++i == 16 )
		{
			cout << '\n';
			i = 0;
		}
	}
	
	if( i != 0)
	{
		cout << '\n';
	}
	if( (err = (0 < k)) != 0 )
	{
		cout << "\n**" << (int)k << "-th nonblank char < "
			<< (int)ch << " > is illegal. **\n";
	}
} 

//-miguel : implemented the makerpn function please check it to make sure i followed teh logic correctly thanks! 02/12
void makerpn()
{
	static char pr[]={0,0,1,2,3,3,4,4};
	char n,*p,*r,s,*t;
		
	cout << "\nRPN form:\n\n";
	
	t = stak-1;
	r = rpn;                        
	
	// following along the flowchart  
	
	for(p = inform; *p; p++)
	{
		if( 7 < (s = *p) )
		{
			*r++ = s;
		}
		
		else if( s == 1 ) 
		{
			*++t = s;
		}
		
		else
		{
			while(1)
			{
				if( t < stak )
				{                                                                              
					*++t = s;
					break;
				}

				else if( pr[s] <= pr[n = *t--] )
				{
					*r++ = n;
				}
				
				else
				{
					if( 3 < n+s )
					{
						*++t = n;
						*++t = s;
					}						
					break;
				}
		   	} 
	    } 
	}	
	while( stak <= t )
	{
		*r++ = *t--;
	}
	
	*r = '\0';
	
	for( r = rpn; *r; r++ )
	{
		cout << ext[(int)*r]; 
	}
	
	cout << "\n\n";
}

void parse()
{
	void reduce( char &, int & );
	int t;
	static char c1[13][9]={ { 1,11,11,11,11,11,11, 1, 0},
						    {11, 2,11, 2, 2, 2, 2,11, 2},
						    { 1,11,14,10,10,10,10, 1, 0},
						    { 1,11,10,10,10,10,10, 1, 0},
						    { 1,11,10,10,10,10,10, 1, 0},
						    { 1,11,10,10,10,10,10, 1, 0},
						    { 1,11,10,10,10,10,10, 1, 0},
						    {11, 2, 1, 2, 2, 2, 2,12, 2},
						    {11,11,13,13,13,13,13, 1, 0},
						    {11,11, 0, 0, 0, 0, 0, 0, 2},
						    {11, 1, 0, 1, 1, 0, 0, 0, 2},
						    {11, 2, 0, 2, 2, 1, 1, 0, 2},
							{11, 2, 0, 2, 2, 2, 2, 0, 2}},
			   *ermsg[ ] =  {": operators are adjacent",
							": parenthesis is misplaced",
							": operands are adjacent",
							": must begin with letter",
						    ": second equal sign encountered"};
    char a, *p, s;
	if ( len < 3 ){
		cout << "\n** String is too short. **\n";
		err = 1;
		return;
	}
	t = -1;
	err = eos = ok = 0;
	s = 9;
	p = inform;
	do{
		if ( (a = *p++) == '\0'){
			eos = 1;
		}
		else 
		{
			if( 8 < a ){
				a = 8;
			}
			out = 0;
			do{
					switch( c1[s - 1][a - 1] ){
						case 1: stak[++t] = s = a; //shift
								out = 1;
								break;
						case 2: reduce( s, t );
								break;
				   	    default: err = c1[s - 1][a - 1] - 8;
					}
			  }	while ( !err && !out );
		}
	}	while( !eos && !err);
 	
	if( !err )
	{
		do
		{
			reduce( s, t );
		}while ( !ok && !err );
	}
	
	if ( err )
	{
		cout << "\n** Illegal syntax";
		
		if ( 1 < err )
		{
			cout << ermsg[err-2] << " - sigma = " << (int)s << ", alpha = " << (int)a;
		}
		cout << " **\n";
	}
}

void reduce( char & s,int & t )
{
	switch( s ) 
	{
		case 2: if ( t < 2)
				{
					err = 1;
				} 
				else 
				{
					if( (stak[t - 1] != 11) || (stak[t - 2] != 1)) 
					{
						err = 1;
					} 
					else 
					{
						stak[t -= 2] = s = 13;
					}
				}
				break;
		case 8: stak[t] = s = 13;
			    break;
		case 10: err = !( ok = ( eos && (t == 0 )));
				out = 1;
				break;
		case 11: if ( t < 2 )
		{
			err = 1;
		} 
		else 
		{
			if ((stak[t - 1] != 3) || (stak[t - 2] != 8)) 
			{
				err = 1;
			} 
			else
			{
				stak[t -= 2] = s = 10;
			}
		}
				break;
		case 12: if ( t < 2 ) 
				 {
					err = 1;
				 } 
				else 
				{
					s = 11;
					if ( (stak[t - 2] == s) && ( (stak[t - 1] == 4) || (stak[t - 1] == 5) ) ) 
					{
						t -= 2;
					} 
					else 
					{
						stak[t] = s;
					}
				}
				break;
		case 13: if ( t < 2 ) {
							 err = 1;
					} else {
						   s = 12;
						   if ( (stak[t - 2] == s) && ( (stak[t - 1] == 6) || (stak[t - 1] == 7) ) ) {
									 t -= 2;
							} else {
									stak[t] = s;
							}
					}
					break;
			default: err = 1;
	}
}
