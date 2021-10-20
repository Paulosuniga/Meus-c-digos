#include <stdio.h>

int soma (int *A, int *B, int *C, int n)
{
    int m = 0 ;
    int i, j, k ;

    for (i = 0; i < n; i++) 		
    {
        for (j = 0; j < n; j++)		
        
			 {
            for (k = 0; k < n; k++) 
            {
                if (A[i]+B[j]+C[k] == 0)
				 m++ ;
            }
        }
    }
    return m ;
}

int main ()
{
    int a[] = {1,2,3} ;
    int b[] = {2,5,6} ;
    int c[] = {-4,-8,-10} ;

    printf ("O valor eh de %i", soma (a, b, c, 3)) ;

    return 0 ;
}
