#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

#define MAX 500

char *int2bin(long long n){
	char *binary;
	binary = (char*)malloc(MAX);
	long long reminder, i=0;
	while (n!=0){
		reminder = n % 2;
		//printf("%lld", reminder);
		n = n / 2;
		binary[i]=reminder;
		i+=1;
	}
	binary[i] = 2;
	return binary;
}

int length(char *arr){
	int i = 0;
	while (arr[i]!=2){
		i++;
	}
	return i;
}

int powermod(int base, long long exp, int mod){
	int result, reminder;
	char *_exp;
	_exp = (char*)malloc(MAX);
	_exp = int2bin(exp);
	reminder = base;
	for (int i=length(_exp)-2;i>=0;i--){
		if(_exp[i] == 1){
			result = ((reminder * reminder) * base);
			result = result % mod;
			reminder = result;
		}
		if (_exp[i] == 0){
			result = (reminder * reminder);
			result = result % mod;
			reminder = result;
		}
	}
	return reminder;
}

bool isprime(int n){
	bool flag = true;
	for (int i=2;i<=n/2;i++){
		if (n%i==0){
			flag=false;
			break;
		}
	}
	return flag;
}

int generate_prime(int min, int max){
	int result=0,low=0,hi=0;
	bool flag = false;
	if(min<max)
	{
		low=min;
        hi=max+1;
    }else{
    	low=max+1;
        hi=min;
    }
    srand(time(NULL));
    result = (rand()%(hi-low))+low;
    while (!flag){
    	if (isprime(result)){
    		flag = true;
    		break;
    	}
    	else{
    		srand(time(NULL));
    		result = (rand()%(hi-low))+low;
    		flag = false;
    	}
    }
    return result;
}

int fin(int p, int q){
	return (p-1)*(q-1);
}

int encrypt_rsa(int msg, long long e, int n){
	return powermod(msg, e, n);
}

int get_decryption_key_odd(int e , int fn, int n){
	for (int i=0;i<=n;i++){
		if (e*i%fn==1){
			return i;
			break;
		}
	}
}

int decrypt_rsa(int c, long long d, int n){
	return powermod(c, d, n);
}

int factorial(int n){
	if (n==0) return 1;
	else return n * factorial(n-1);
}

int gcd(int a, int b){
	a = abs(a);
	b = abs(b);
	int tmp;
	if (a < b){
		tmp = a;
		a = b;
		b = tmp;
	}
	while (b > 0){
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

/* calculates a * *x + b * *y = gcd(a, b) = *d */
void xgcd(int a, int b, int *x, int *y, int *d){ 
  int q, r, x1, x2, y1, y2;
  if (b == 0) {
    *d = a, *x = 1, *y = 0;
    return;
  }
  x2 = 1, x1 = 0, y2 = 0, y1 = 1;
  while (b > 0) {
    q = a / b, r = a - q * b;
    *x = x2 - q * x1, *y = y2 - q * y1;
    a = b, b = r;
    x2 = x1, x1 = *x, y2 = y1, y1 = *y;
  }
  *d = a, *x = x2, *y = y2;
}

bool coPrime(int e, int fn){
	if (gcd(e, fn)!=1){
		return false;
	}
	else {
		return true;
	}
}

int cmod(int a, int b){
	int ret = a % b;
   	if(ret < 0)
    	ret+=b;
   	return ret;
}

int get_decryption_key(int e, int fn){
	int x, y, d, key;
	if (coPrime(e, fn)){
		xgcd(e, fn, &x, &y, &d);
		key = cmod(x, fn);
		return key;
	}
	else return 0;
}

void numberFactorization(int n, int *p, int *q){
	int a;
	for (int i=0;i<=n/2;i++){
		a = 2 ^ factorial(i) % n;
		*q = gcd(a-1, n);
		if (*q > 1){
			*p = n / *q;
			break;
		}
	}
	return ;
}

int ctoi(char *c)
{
    int a;
    a= *c - '0';
    return a;
}

void usage(){
	printf("[*] usage: ./rsa <nr msg>\n");
}

void main(int argc, char *argv[]){
	int n, p, q, e, fn, d, m, c, md, p1, q1;
	if(argc > 1){
	    m = ctoi(argv[1]);
	    e = generate_prime(3, 11);
	    printf("e=%d\n", e);
	    p = generate_prime(11, 21);
	    q = generate_prime(21, 41);
	    printf("p=%d q=%d\n", p, q);
	    fn = fin(p, q);
	    printf("fn=%d\n", fn);
	    n = p * q;
	    while(!coPrime(e, fn)){
	    	e = generate_prime(3, 11);
	    	printf("e=%d\n", e);
	    	p = generate_prime(11, 21);
	    	q = generate_prime(21, 41);
	    	printf("p=%d q=%d\n", p, q);
	    	fn = fin(p, q);
	    	printf("fn=%d\n", fn);
	    	n = p * q;
	    }
	    c = encrypt_rsa(m, e, n);
	    printf("cipher=%d\n", c);
	    numberFactorization(n, &p1, &q1);
	    printf("p1=%d q1=%d\n", p1, q1);
	    fn = fin(p1, q1);
	    printf("fn=%d\n", fn);
	    d = get_decryption_key(e, fn);
	    printf("d=%d\n", d);
	    md = decrypt_rsa(c, d, n);
	    printf("message=%d\n", md);
  	}
  	else{
  		usage();
  	}
}
