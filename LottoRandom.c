// LottoRandom.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void FindOverlap( int LottoArray[], int i )
{
	int j;
	LottoArray[ i ] = ( rand() % 45 ) + 1;
	
	for( j = 0; j < i; j ++ )
	{
		while( LottoArray[ i ] == LottoArray[ j ] )
		{
			LottoArray[ i ] = ( rand() % 45 ) + 1;
		}
	}
}

void LottoNumber( int LottoArray[] )
{
	int i;
	int total = 0;

	while( total < 120 || total > 169 )
	{
		total = 0;

		for ( i = 0; i < 6; i ++ )
		{
			FindOverlap( LottoArray, i );

			total += LottoArray[ i ];
		}
	}
}

void LottoBonus( int LottoArray[] )
{
	FindOverlap( LottoArray, 6 );
}

void swap( int LottoArray[], int i, int j )
{
	int temp = LottoArray[ i ];
	LottoArray[ i ] = LottoArray[ j ];
	LottoArray[ j ] = temp;
}

void Selection( int LottoArray[] )
{
	int i, j;

	for( i = 0; i < 5; i ++ )
	{
		for( j = ( i + 1 ); j < 6; j ++ )
		{
			if( LottoArray[ i ] > LottoArray[ j ] )
			{
				swap( LottoArray, i, j );
			}
		}
	}
}

void LottoPrint( int LottoArray[], int num )
{
	int i;

	printf("%d : ", num);

	for( i = 0; i < 7; i ++ )
	{
		printf("%d ", LottoArray[ i ]);
	}

	printf("\n");
}

int main()
{
	int i;
	int LottoArray[ 7 ];

	struct timeval t;
	gettimeofday( &t, NULL );
	srand( t.tv_usec * t.tv_sec );

	for( i = 0; i < 10; i ++ )
	{
		LottoNumber( LottoArray );
		LottoBonus( LottoArray );
		Selection( LottoArray );
		LottoPrint( LottoArray, ( i + 1 ) );
	}

	return 0;
}
