#include <math.h>
#include <stdio.h>
#include <stdlib.h>
static void increment(int x){
	x = x+1;
}


int main (void)
{
//	char* x = "abcdefghijk";
//	printf("size is %d", sizeof(x));
/*	int x = 1;
	increment(x);
	printf("x is now %d\n",x);
*/
//   int x = -1;
//   int y = 5;
//   int z = x%y;

//   printf("%d\n",z);

int tarray[5];
int *t;

t = tarray;

t[0] = 3;
t[1] = 1;
t[2] = 2;
t[3] = 5;
t[4] = 4;
int c,d,te;

for (c = 1 ; c <= 5 - 1; c++) {
    d = c;
 
    while ( d > 0 && tarray[d] < tarray[d-1]) {
      te          = tarray[d];
      tarray[d]   = tarray[d-1];
      tarray[d-1] = te;
 
      d--;
    }
  }







int n = 0;

for (n = 0; n < 5; n++){

printf("%d\n",tarray[n]);

}

printf("\n\n");
long long num = 9223371873002223329;
int i = 3;
long long il = 3;
int testnum = num % i;
long long testnuml = num % il;
long long testsqrt = sqrtl(num);
printf("testnum: %d \n",testnum);
printf("testnuml : %lld\n",testnuml);
printf("testsqrt : %lld\n",testsqrt);


	return 0;

}
