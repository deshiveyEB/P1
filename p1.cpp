/*
 *  p1.cpp
 *  
 *
 *  Created by Devin Shively on 1/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <string.h>

fstream file;
int datafile = 0,eos,err,len,nstring=0,ok,out;
char ext[] = {  63, 63, 63, 61, 43, 45, 42, 47, 65, 66,
				67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
				77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
				87, 88, 89, 90, 97, 98, 99,100,101,102,
			   103,104,105,106,107,108,109,110,111,112,
			   113,114,115,116,117,118,119,120,121,122},
			inform[241],rpn[241],str[241],stak[80];

int main( int argc, char **argv )
{
	int atend( void );
	void deleteblanks( void ), drawline( void ), echoprint( void ),
			gencode( void ), getstring( void ), intertnalize( void ),
			makerpn( void ), parse( void );
	
	if( 2 < argc )
	{
		cout << "** use is >p1 [input_file_name] **\n";
		exit( 1 );
	}
	
	if( argc == 2 )
	{
		file.open( *++argv,ios::in );
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
	return ( (len == 3) && (stricmp( str,"end" ) == 0) );
}

void deleteblanks()
{
	char *p,*q;
	
	cout << "String with no blank or tab:\n\n";
	
	p = q = str;
	for( len = 0; *p; p++ )
	{
		if( (*p != ' ' && (*p != '\t') )
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
	t = p =rpn;
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
}

void makerpn()
{
	static char pr[]={0,0,1,2,3,3,4,4};
	char n,*p,*r,s,*t;
}

void parse()
{
}

void reduce( char & s,int & t )
{
}



	
	









