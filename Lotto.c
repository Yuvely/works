// Lotto.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NROWS 45
#define NCOLS 2
#define AROWS 10
#define ACOLS 7

void LottoNumSwap( int LottoNum[][ NCOLS ], int i, int j )
{
	int temp1 = LottoNum[ i ][ 0 ];
	LottoNum[ i ][ 0 ] = LottoNum[ j ][ 0 ];
	LottoNum[ j ][ 0 ] = temp1;

	int temp2 = LottoNum[ i ][ 1 ];
	LottoNum[ i ][ 1 ] = LottoNum[ j ][ 1 ];
	LottoNum[ j ][ 1 ] = temp2;
}

void LottoArraySwap( int LottoArray[][ ACOLS ], int n, int i, int j )
{
	int temp = LottoArray[ n ][ i ];
	LottoArray[ n ][ i ] = LottoArray[ n ][ j ];
	LottoArray[ n ][ j ] = temp;
}

void SelectionLottoNum( int LottoNum[][ NCOLS ] )
{
	int i, j;

	for( i = 0; i < ( NROWS - 1 ); i ++ )
	{
		for( j = ( i + 1 ); j < NROWS; j ++ )
		{
			if( LottoNum[ i ][ 1 ] < LottoNum[ j ][ 1 ] )
			{
				LottoNumSwap( LottoNum, i, j );
			}
		}
	}
}

void SelectionLottoArray( int LottoArray[][ ACOLS ] )
{
	int n, i, j;

	for( n = 0; n < AROWS; n ++ )
	{
		for( i = 0; i < ( ACOLS - 2 ); i ++ )
		{
			for( j = ( i + 1 ); j < ( ACOLS - 1 ); j ++ )
			{
				if( LottoArray[ n ][ i ] > LottoArray[ n ][ j ] )
				{
					LottoArraySwap( LottoArray, n, i, j );
				}
			}
		}
	}
}

int putUpLottoNumber( int LottoNum[][ NCOLS ], int LottoArray[][ ACOLS], int num, int end, int add )
{
	int i;

	if( num >= 45 )
	{
		num = 0;
	}

	for( i = 0; i < end; i ++ )
	{
		LottoArray[ i ][ i + add ] = LottoNum[ num ][ 0 ];
		num ++;
	}

	return num;
}

int putDownLottoNumber( int LottoNum[][ NCOLS ], int LottoArray[][ ACOLS ], int num, int start )
{
	int i;

	if( num >= 45 )
	{
		num = 0;
	}

	for( i = start; i < 10; i ++ )
	{
		LottoArray[ i ][ i - start ] = LottoNum[ num ][ 0 ];
		num ++;
	}

	return num;
}

void putLottoNumber( int LottoNum[][ NCOLS ], int LottoArray[][ ACOLS ] )
{
	int i, j;
	int num = 0;
	int uStart = 6;
	int uEnd = 1;
	int dStart = 4;
	
	for( i = 0; i < 4; i ++ )
	{
		for( j = 0; j < 7; j ++ )
		{
			LottoArray[ i + j ][ j ] = LottoNum[ num ][ 0 ];
			num ++;
		}
	}

	for( i = 0; i < 6; i ++ )
	{
		num = putUpLottoNumber( LottoNum, LottoArray, num, uStart --, uEnd ++ );
		num = putDownLottoNumber( LottoNum, LottoArray, num, dStart ++ );
	}
}

void printLottoArray( int LottoArray[][ ACOLS ] )
{
	int i, j;
	for( i = 0; i < 10; i ++ )
	{
		printf("%d : ", ( i + 1 ));

		for( j = 0; j < 7; j ++ )
		{
			printf("%d ", LottoArray[ i ][ j ]);
		}
		
		printf("\n");
	}
}

int main()
{
	int i;
	int LottoNum[ NROWS ][ NCOLS ] = { 0, };
	int LottoArray[ AROWS ][ ACOLS ] = { 0, };

	for( i = 0; i < NROWS; i ++ )
	{
		LottoNum[ i ][ 0 ] = ( i + 1 );
	}

	FILE* file = fopen( "lotto.csv", "r" );

	if( file != NULL )
	{
		char numStr[ 256 ];
		char* pStr;
		char* token;

		while( !feof( file ) )
		{
			pStr = fgets( numStr, sizeof( numStr ), file );

			token = strtok( numStr, "," );

			while( 1 )
			{
				token = strtok( NULL, "," );

				if( token == NULL )
				{
					break;
				}

				int standard = atoi( token ) - 1;
				LottoNum[ standard ][ 1 ] += 1;
			}
		}
		
		fclose( file );
	}

	SelectionLottoNum( LottoNum );
	putLottoNumber( LottoNum, LottoArray );
	SelectionLottoArray( LottoArray );
	printLottoArray( LottoArray );

	return 0;
}
