#include<stdio.h>
#include<math.h>
double t[] = {20, 25, 30, 35, 40, 45, 50, 55, 60};
double y[] = {805,985,1170,1365,1570,1790,2030,2300,2610};
double g[4][4];
double d[4];
int debug = 1;
void solve(){
	int i;
	int j;
	int m;
	int k;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			for(m=0;m<sizeof(t)/sizeof(t[0]);m++){
				g[i][j]+=pow(t[m],i)*pow(t[m],j);
			}
		}
	}
	for(i=0;i<4;i++){
		for(m=0;m<sizeof(t)/sizeof(t[0]);m++){
			d[i]+=y[m]*pow(t[m],i);
		}
	}
	if(debug){
		printf("d:\n");
		for(i=0;i<4;i++){
			printf("%f ",d[i]);
		}
		printf("\ng:\n");
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				printf("%f ",g[i][j]);
			}
			printf("\n");
		}
	}
	for(i=0;i<3;i++){
		for(j=i+1;j<4;j++){
			double ratio = -g[j][i]/g[i][i];
			for(k=i;k<4;k++){
				g[j][k]+=ratio*g[i][k];
			}
			d[j]+=ratio*d[i];
		}
	}
	for(i=3;i>=0;i--){
		for(j=i+1;j<4;j++){
			d[i]-=g[i][j]*d[j];
		}
		d[i]/=g[i][i];
	}
	printf("final exp: y = %f + %f*x + %f*x^2 + %f*x^3\n",d[0],d[1],d[2],d[3]);
	printf("t\ty\tybar\terr\n");
	for(i=0;i<sizeof(t)/sizeof(t[0]);i++){
		double xx = t[i];
		double res = d[0]+d[1]*xx+d[2]*xx*xx+d[3]*xx*xx*xx;
		printf("%6.1f %6.1f %6.1f %6.1f\n",t[i],y[i],res,res-y[i]);
	}
}
int main(){
	solve();
}



