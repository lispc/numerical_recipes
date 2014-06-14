#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double f(double x){
	return 2*x*x*x-x*x+3*x-1;
}
double ff(double x){
	return 6*x*x-2*x+3;
}
double f1(double x){
	return cbrt((1+x)/2);
}
double f2(double x){
	return 2*x*x*x-1;
}
double f3(double x){
	return x*x*x-x-1;
}
double ff3(double x){
	return 3*x*x-1;
}
double iter10(double x,double (*fp)(double)){
	int i = 0;
	while(i<10){
		x = fp(x);
		i++;
		printf("%d %f\n",i,x);
	}
	return x;
}
double nt(double x0,int debug,double p,double (*f)(double),double(*ff)(double)){
	int iter = 0;
	while(1){
		double f0 = f(x0);
		double ff0 = ff(x0);
		double x1 = x0 - f0/ff0;
		double delta = x0-x1;
		double abs_delta = delta>0?delta:-delta;
		if(abs_delta<p){
			return x1;
		}
		x0 = x1;
		iter++;
		if(debug){
			printf("%d %f\n",iter,x0);
		}
	}
}
double bi(int debug,double p){
	int iter = 0;
	double s = -3;
	double e = 3;
	while(1){
		double ys = f(s);
		double ye = f(e);
		if(ys>0&&ye>0||ys<0&&ye<0){
			printf("err: %lf %lf %lf %lf\n",s,e,ys,ye);
			exit(-1);
		}
		double m = (s+e)/2;
		if(e-s<p){
			return m;
		}
		double ym = f(m);
		if(ym>0){
			e = m;
		}else if(ym<0){
			s = m;
		}else{
			return m;
		}
		iter++;
		if(debug){
			printf("%d [%f,%f]\n",iter,s,e);
		}
	}
}
int main(){
	double res_b = bi(1,0.000001);
	double res_n = nt(3,1,0.000001,f,ff);
	printf("%f %f\n",res_b,f(res_b));
	printf("%f %f\n",res_n,f(res_n));
	printf("f1:%f\n",iter10(0,f1));
	printf("f2:%f\n",iter10(0,f2));
	printf("%f\n",nt(1.5,1,0.000001,f3,ff3));
	printf("%f\n",nt(0,1,0.000001,f3,ff3));
}
