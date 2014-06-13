#include<stdio.h>
#define abs(x) ((x)>0?(x):(-(x)))
int debug = 1;
double A[3][3] = {
	1.0, 1.0, 0.5,
	1.0, 1.0, 0.25,
	0.5, 0.25, 2.0
};
double u[4] = {1,1,1,1};
double v[4] = {1,1,1,1};
double uk_last;
int main(){
	int k = 0;
	while(1){
		k++;
		int i;
		int j;
		double sum;
		for(i=0;i<3;i++){
			sum = 0;
			for(j=0;j<3;j++){
				sum += A[i][j]*u[j];
			}
			v[i] = sum;
		}
		double uk = 0;
		for(i=0;i<3;i++){
			if(abs(v[i])>uk){
				uk = abs(v[i]);
			}
		}
		if(debug){
			//printf("v  after %d iter :%.4lf %.4lf %.4lf\n",k,v[0],v[1],v[2]);
		}
		for(i=0;i<3;i++){
			u[i] = v[i]/uk;
		}
		if(debug){
			printf("uk after %d iter : %.7lf\n",k,uk);
		}
		if(debug){
			printf("u  after %d iter : %.4lf %.4lf %.4lf\n",k,u[0],u[1],u[2]);
		}
		if(abs(uk-uk_last)<0.00001)
			break;
		else
			uk_last = uk;
	}
}




