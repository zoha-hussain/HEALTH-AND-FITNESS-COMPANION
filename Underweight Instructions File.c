#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	FILE *pUnder=NULL;
	//inst Stands for Instructions
	char inst1[4][50]={{"1-Eating Dry Fruits\0"},{"2-Eat a variety of Fruits and Vegetables\0"},{"3-Consume Nutrient-Rich Foods\0"},{"4-Drinking Dairy Products and Fresh Juices\0"}};
	 
	//Write
	pUnder=fopen("underweight.txt","w");
	int i,j;
	for(i=0;i<4;i++)
		fprintf(pUnder,"%s\n",inst1[i]);					
	fclose(pUnder);
}