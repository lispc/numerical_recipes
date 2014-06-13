#include<stdio.h>
#define abs(x) ((x)>0?(x):(-(x)))
int debug = 1;
double T[3][3] = {
	1.0, 1.0, 0.5,
	1.0, 1.0, 0.25,
	0.5, 0.25, 2.0
};
double A[3][3] = {
	5, 4, 1,
	4, 6, 4,
	1, 4, 7,
};
double B[4][4] = {
	25, 41, 10,  6,
	41, 68, 17, 10,
	10, 17,  5,  3,
	 6, 10,  3,  2
};
double u[4] = {1,1,1,1};
double v[4] = {1,1,1,1};
double uk_last;
void cal(int N,double A[][N]){
	int k = 0;
	while(1){
		k++;
		int i;
		int j;
		double sum;
		for(i=0;i<N;i++){
			sum = 0;
			for(j=0;j<N;j++){
				sum += A[i][j]*u[j];
			}
			v[i] = sum;
		}
		double uk = 0;
		for(i=0;i<N;i++){
			if(abs(v[i])>uk){
				uk = abs(v[i]);
			}
		}
		for(i=0;i<N;i++){
			u[i] = v[i]/uk;
		}
		if(debug){
			printf("%d\t(%.4lf",k,u[0]);
			int i;
			for(i=1;i<N;i++){
				printf(",%.4lf",u[i]);
			}
			printf(")\t%.7lf\n",uk);
		}
		if(abs(uk-uk_last)<0.00001)
			break;
		else
			uk_last = uk;
	}
}
int main(){
	cal(3,A);
	cal(4,B);
}



