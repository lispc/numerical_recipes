#include<stdio.h>
float f(int n){
	float res = 0;
	int i;
	for(i=1;i<=n;i++){
		res += ((i%2)?1:-1)/(float)i;
	}
	return res;
}
int main(){
	printf("%.9f\n",f(200000));
	printf("%.9f\n",f(2000000));
}

