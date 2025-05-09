#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	FILE *pOver=NULL;
	//inst Stands for Instructions
	char inst2[4][50]={{"1-Proper Exercise\0"},{"2-Consume Weight-Loss Medicines\0"},{"3-Intermittent Fasting\0"},{"4-Consume Whole Grain instead of Fats\0"}};
	 
	//Write
	pOver=fopen("overweight.txt","w");
	int i,j;
	for(i=0;i<4;i++)
		fprintf(pOver,"%s\n",inst2[i]);					
	fclose(pOver);
}