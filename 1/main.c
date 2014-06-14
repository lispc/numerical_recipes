#include<stdio.h>
#define LN2 0.693147190546
float ln2_f = 0.693147190546;
int debug = 1;
int debug_iter = 1;
float f(int n){
	float res = 0;
	int i;
	for(i=1;i<=n;i++){
		res += ((i%2)?1:-1)/(float)i;
		if(debug&&(i%5000==0||i%5000==1)){
			printf("%d %.9f\n",i,res-ln2_f);
		}
	}
	return res;
}
double d(int n){
	double res = 0;
	int i;
	for(i=1;i<=n;i++){
		res += ((i%2)?1:-1)/(double)i;
	}
	return res;
}
/*
int iter(float delta){
	float res = 0;
	int i;
	for(i=1;;i++){
		res += ((i%2)?1:-1)/(float)i;
		float d = res - ln2_f;
		if(d<delta&&d>-delta){
			printf("%d %.9f\n",i,d);
		}
	}
}
*/
int main(){
	printf("%.9f\n",f(200000));
	printf("%.9lf\n",d(200000));
	printf("%.9f\n",f(2000000));
	printf("%.9lf\n",d(2000000));
}

