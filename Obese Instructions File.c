#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	FILE *pObese=NULL;
	//inst Stands for Instructions
	char inst3[4][60]={{"1-Reduce Fast Food Consumption\0"},{"2-Cut Down on Sugar\0"},{"3-Try Physical Therapy\0"},{"4-Perform Yoga and Exercise\0"}};
	 
	//Write
	pObese=fopen("obese.txt","w");
	int i,j;
	for(i=0;i<4;i++)
		fprintf(pObese,"%s\n",inst3[i]);					
	fclose(pObese);
}