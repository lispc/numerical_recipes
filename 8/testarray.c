#include<stdio.h>
#include<stdlib.h>
int s[2][2] = {1,2,3,4};
int** d;
void dc(void* p){
	printf("%x\n",*((char*)p));
}
void dp(void* p){
	printf("%p\n",p);
}
void dm(void* p,int n){
	int i=0;
	while(i<n){
		printf("%02X ",(unsigned int)(*(((unsigned char*)p)+i)));
		i++;
	}
	printf("\n");
}
int main(){
	/*
	dp(s);
	dc(s);
	dp(s[0]);
	dc(s[0]);
	dp(&s[0][0]);
	dc(&s[0][0]);
	dp(&s[0][1]);
	dp(&s[1][0]);
	dp(&s[1][1]);
	dc(*(s+3));
	*/
	dp(s[1]);
	dp(s);
	dm(s,16);
	d = (int**)malloc(2*sizeof(int*));
	d[0] = (int*)malloc(2*sizeof(int));
	d[1] = (int*)malloc(2*sizeof(int));
	d[0][0]=0;
	d[0][1]=1;
	d[1][0]=2;
	d[1][1]=3;
	dp(d);
	dm(d,16);
	dp(&d[0][0]);
	dp(&d[0][1]);
	dp(&d[1][0]);
	dp(&d[1][1]);
}

