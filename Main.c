#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>

//Structure Diet 
struct diet{
	char day[7][15];
	char time[3][15];
	char food[3][100];
};

//Structure For Account
struct account{
	char username[20];
	char password[17];	
};

//Function ProtoTypes
void select();
void calIntakeCalc(int,float,float,char);
void calBurnCalc(int,float,float,char);
float metCalc();
float BMI(float, float);
void healthy(float);
void dietCovid(); 
void dietDengue(); 
void dietDiabetes();
void signup(struct account);
void login(struct account);
void mask(char *);

//Signing Up/Creating an Account:
void signup(struct account acc){
	
	char verify[17];
	int length,i=0; //Length of Password
	int upper=0,lower=0,sym=0,num=0; //Upper:Uppercase Letter; Lower:lowercase letter;Sym:Symbol;Num=Number
	FILE*p;
	
	printf("\nEnter Username:");
	scanf("%s",acc.username);
	
	printf("Enter Password, Such That It Contains 8 to 16 Characters.It Should Include:\n");
	printf(".Uppercase Characters;\n.Lowercase Characters;\n.Numbers &\n.Special Symbols.\nIt Should Not Include:\n");
	printf(".Tabs or\n.Spaces:\n");
	mask(acc.password);
	
	length=strlen(acc.password);
	while(length<8||length>16){   //If Password is Not in Range, Then Input Password Again
		if(length<8){
			printf("\nPassword Too Short!Re-Enter:");
			mask(acc.password);
		}
		else if(length>16){
				printf("\nPassword Too Long!Re-Enter:");
				mask(acc.password);
		}
		length=strlen(acc.password);
	}
	
	while(num==0 || upper==0 || sym==0 || lower==0){    //Checking if Password Satisfies Conditions or Not
		for(i=0;i<length;i++){
			if(acc.password[i]>='a' && acc.password[i]<='z')
				lower=1;
			else if(acc.password[i]>='A' && acc.password[i]<='Z')
					upper=1;
				else if(acc.password[i]>='0' && acc.password[i]<='9')
						num=1;
					else sym=1;
		if(i==length-1){
			if(num==0 || upper==0 || sym==0 || lower==0){
				printf("\nConditions For Password Unsatisfied.");
				if(num==0)
					printf("\nYou Did Not Include Any Numbers.");
				else if(sym==0)
						printf("\nYou Did Not Include Any Symbols.");
					else if(lower==0)
							printf("\nYou Did Not Include Any Lowercase Letters.");
						else if(upper==0)
								printf("\nYou Did Not Include Any Uppercase Letters.");
				printf("\nRe-Enter a Password which Fulfills the Conditions:");
				fflush(stdin);
				mask(acc.password);
				length=strlen(acc.password);
				}
			}
		}
	}
	
	printf("\nKindly Re-Enter Your Password for Confirmation:");
	mask(verify);
	
	if(strcmp(verify,acc.password)!=0){   //If the 2 Passwords are Different
		while(strcmp(verify,acc.password)!=0){
			printf("\nThe 2 Passwords Do Not Match! Kindly Re-Enter Your Password:");
			mask(verify);
		}
	}
	
	if(strcmp(verify,acc.password)==0){  //If They are Equal, Storing It in a File.
		p=fopen("data.txt","a+");
		if(p==NULL){
			printf("\nError! File did not open...");
			exit(1);
		}
		else{
			fwrite(&acc,sizeof(acc),1,p);
			fclose(p);
			printf("\nAccount Created Successfully!");
		}
	}	
	
}

//Login
void login(struct account acc){
	
	int i=0;
	char choice;
	char passwordEnter[17];
	char usernameEnter[20];
	
	printf("\nEnter Your Username:");
	fflush(stdin);
	scanf("%s",usernameEnter);
	printf("\nEnter Your Password:");
	mask(passwordEnter);
	
	
	FILE*p;
	p=fopen("data.txt","r");
	if(p==NULL){
		printf("\nError! File Did Not Open...");
		exit(1);
	}
	else{
		while(fread(&acc,sizeof(acc),1,p) && i<3){
			for(i=0;i<3;i++){
				if(strcmp(passwordEnter,acc.password)==0 && strcmp(usernameEnter,acc.username)==0){
					printf("\nLogged in Successfully!");
					return;
					}
				else {
					//User Has 3 Attempts to Enter Correct Credentials
					if(strcmp(passwordEnter,acc.password)!=0 && strcmp(usernameEnter,acc.username)!=0){
						printf("\nIncorrect Data.You have %d attempts. Re-enter:",3-i);
						printf("\nEnter Your Username:");
						fflush(stdin);
						scanf("%s",usernameEnter);
						printf("\nEnter Your Password:");
						mask(passwordEnter);
						if(strcmp(passwordEnter,acc.password)==0 && strcmp(usernameEnter,acc.username)==0){
						printf("\nLogged in successfully!");
						return;
						}
					}
				}
			}
			if(i==3){
				printf("\nFailed to Login");
				char choose;
				printf("\nDo you Want to Sign-up? Y/N:");
				fflush(stdin);
				scanf(" %c",&choose);
				switch(choose){
					case 'y':
					case 'Y':
						signup(acc);
						break;
					case 'n':
					case 'N':
						printf("\nExiting Program...");
						sleep(1);
						system("cls");
						system("color 0A");
						printf("\n-------------------------------------------------------------------------------------------------------------\n");
						printf("\n\t\t\t\t\t*** Thank You for Using This Application! ***\n");
						printf("\n-------------------------------------------------------------------------------------------------------------\n");
						exit(1);
						break;
					default:
						while(choose!='y'||choose !='Y'||choose!='n'||choose!='N'){
							printf("\nInvalid Choice. Re-enter:");
							scanf(" %c",&choose);
						}
				}
			}
		}
	}
	fclose(p);
}

//For Masking Password
void mask(char *password){
	char ch;
	int i=0;
	while(1){
        ch = getch(); // Getch() Reads a Key From Keyboard Without Displaying it on Screen and Returns it's ASCII Value
        if(ch == 13){ // If Enter Key
            if(i == 0) 
				printf("\nPassword Cannot be Empty");
            break;
            }
		else if(ch == 32 || ch == 9){ // If Space or Tab Key
                continue;
               }
			else if(ch == 8){ // If Backspace
                    if(i > 0){
                        i--;
                        password[i] = '\0';
                        printf("\b \b");
                    }
            	} 
			    else{
                    if(i < 16){
                         password[i] = ch;
                         i++;
                         printf("*");
                    }
                }
        }
    password[i] = '\0';
}

//Menu for Selection
void select(){
	
	int disease,i,age,option;
	char gender,opt;  
	float weight,height,calIntake,index;
	
	printf("\nI- for Calculating BMI(Body Mass Index).\n");
	printf("R- for Calculating BMR(Basal Metabolic Rate).\n");
	printf("D- for Displaying the Disease Diet Plan Chart.\n");
	printf("E-Exit the Program.\n");
	fflush(stdin);
	scanf("%c",&opt);
	
	if(opt=='d' || opt=='D'){    //For Printing Diseases Diet Plans
		printf("We Have Diet Plans of the Following Diseases, Please Enter the Corresponding Number.\n");			
		printf("1.Dengue.\n");
		printf("2.Diabetes.\n");
		printf("3.COVID-19.\n");
		scanf("%d", &disease);
		
        switch(disease){
			case 1:
				printf("\nYour Nutrition Plan for Dengue is Below:");
				dietDengue();
				puts("");
				sleep(3);
				system("cls");
				printf("\nPlease Select from the List Below if you Want to Check Something Else:");
				select(); //RECURSION
				break;
			case 2:
				printf("\nYour Nutrition Plan for Diabetes is Below:");
				dietDiabetes();	
				puts("");
				sleep(3);
				system("cls");
				printf("\nPlease Select from the List Below if you Want to Check Something Else:");
				select(); //RECURSION			 
				break;
			case 3:
				printf("\nYour Nutrition Plan for COVID-19 is Below:");
				dietCovid();
				puts("");
				sleep(3);
				system("cls");
				printf("\nPlease Select from the List Below if you Want to Check Something Else:");
				select(); //RECURSION
				break;
			default:
				printf("Invalid Code For Disease!\n");
				puts("");
				select(); //RECURSION
				break;
			}
		}
		
	else if(opt=='i' || opt=='I' || opt=='r' || opt=='R'){   //Calculating BMI or BMR
	
		do{
			printf("\nEnter Your Weight:");
			scanf("%f", &weight);
		}
		while(weight<=0);      //Weight Should Not be 0 or Less Than 0
		
		do{
			printf("\nEnter Your Height in meters:");
			scanf("%f", &height);
		}
		while(height<=0);       //Height Should Not be 0 or Less Than 0
		
		switch(opt){
			case 'i':
			case 'I':
  				index = BMI(height,weight);
				healthy(index);
				puts("");
				sleep(3);
				system("cls");
				printf("\nPlease Select from the List Below if you Want to Check Something Else:");
				select(); //RECURSION
				break;
			case 'r':
			case 'R':
				
				do{
				printf("\nEnter Your Age:");
				scanf("%d", &age);
			    }
			    while (age<=0 || age>120);      //Restrictions on Age
			    
			    do{
				printf("\nEnter Your Gender.\nm-Male,f-Female:");
				fflush(stdin);
				scanf("%c", &gender);
				}
				while (gender!='f' && gender!='m' && gender!='M'&& gender!='F');   //Invalid Gender Cannot be Entered
				
				printf("\nSelect Your Option:\n1-Calculate Calories Burned  OR  2-Calculate Required Calories Intake:\n");
	            scanf("%d", &option);
				
				if(option == 1){
					calBurnCalc(age,height,weight,gender);
					puts("");
					sleep(3);
					system("cls");
					printf("\nPlease Select from the List Below if you Want to Check Something Else:");
					select(); //RECURSION
				}
				else if(option == 2){
					calIntakeCalc(age,height,weight,gender);
					puts("");
					sleep(3);
					system("cls");
					printf("\nPlease Select from the List Below if you Want to Check Something Else:");
					select(); //RECURSION
				}
				break;
				
			}
	        }
	        
		else if(opt=='e'||opt=='E'){
			printf("\nExiting Program....\n");
			sleep(1);
			system("cls");
			system("color 0A");
			printf("\n-------------------------------------------------------------------------------------------------------------\n");
			printf("\n\t\t\t\t\t*** Thank You for Using This Application! ***\n");
			printf("\n-------------------------------------------------------------------------------------------------------------\n");
			exit(1);
		}
		
		else{
			printf("Invalid Choice!\n");
			printf("Please Re-Enter!\n");
			puts("");
			printf("\nPlease Select from the List Below if you Want to Check Something Else:");
			select(); //RECURSION
	  		}
	}

//BMI Calculator w.r.t. Height & Weight
float BMI(float height, float weight){
	float bmi;
	bmi=(weight/(height*height));

	return bmi;
}

//BMI Checker
void healthy(float bmi){
	if(bmi<18.5){
		printf("\nYour Body Mass Index is %0.2f and you are UnderWeight!",bmi);
    	printf("\nConsider following these Instructions:\n");
    	printf("\n");
    
    	//Reading Text File
    	char ch;
		FILE *pUnder;
    	pUnder=fopen("underweight.txt","r+");
		if(pUnder==NULL){
			printf("\nError!File not found.");
			exit(1);
		}
		else{
			do{
				ch=getc(pUnder);
				printf("%c",ch);
			}while(ch!=EOF);
		}
	
		fclose(pUnder);
    
	}
    
		else if((bmi>18.5)&&(bmi<24.9)){
			printf("\nYour Body Mass Index is %0.2f and you have Normal Weight!",bmi);
			printf("\nYou Have a Perfect BMI! \nExercise Regularly & Continue Taking a Nourishing Diet.");
		}
	 
			else if((bmi>25)&&(bmi<29.9)){
				printf("\nYour Body Mass Index is %0.2f and you are OverWeight!",bmi);
				printf("\nConsider following these Instructions:\n");
				printf("\n");
    
				//Reading Text File
				char ch;
				FILE *pOver;;
				pOver=fopen("overweight.txt","r+");
				if(pOver==NULL){
					printf("\nError!File not found.");
					exit(1);
				}
				else{
					do{
						ch=getc(pOver);
						printf("%c",ch);
					}while(ch!=EOF);
				}
	
				fclose(pOver);
			}
	
				else{
					printf("\nYour Body Mass Index is %0.2f and you are Obese!",bmi);
					printf("\nConsider following these Instructions:\n");
					printf("\n");
    
					//Reading Text File
					char ch;
					FILE *pObese;
					pObese=fopen("obese.txt","r+");
					if(pObese==NULL){
					printf("\nError!File not found.");
					exit(1);
					}
					else{
						do{
							ch=getc(pObese);
							printf("%c",ch);
						}while(ch!=EOF);
					}
	
					fclose(pObese);	
	}	
return;
}

//Calories Intake
void calIntakeCalc(int age,float height,float weight,char gender){
	float calIntake;
	switch(gender){
		//Male Calories Intake
		case 'M':
		case 'm':
			calIntake = ((10 * weight) + (6.25 * height * 100) - (5.00 * age)) + 5.00; 
			break;
		//Female Calories Intake
		case 'F':
		case 'f':
			calIntake = ((10 * weight) + (6.25 * height * 100) - (5 * age)) - 161;
			break;
	}
	printf("\nYou Require  %.2f calories intake.", calIntake);
}

//Calories Burned
void calBurnCalc(int age,float height,float weight,char gender){
	float calBurn;
	float met=metCalc();
	switch(gender){
		//Male Calories Burn
		case 'M':
		case 'm':
			calBurn = ((10 * weight) + (6.25 * height * 100) - (5 * age) + 5) * met / 24;
			break;
		//Female Calories Burn
		case 'F':
		case 'f':
			calBurn = ((10 * weight) + (6.25 * height * 100) - (5 * age) - 161) * met / 24;
	}
	printf("You have burned %.2f calories.", calBurn);
}

//MET
float metCalc(){     //MET Stands for Metabolic Equivalent
	char exercise;
	float met;
	
	printf("\nIn Order to Calculate Calories Burn, We Require met. Please Select the Option of the Exercise That You Have Undergone");
	printf(" So That We May Calculate the MET:");
	printf("\na-Yoga\nb-Weight Training\nc-Cycling\nd-Jogging\ne-Rope Jumping:\n");
	fflush(stdin);
	scanf("%c", &exercise);
	
	switch(exercise){
		case 'a':
		case 'A':
			met=3;    //For Yoga
			break;
		case 'b':
		case 'B':
			met=3.5;  //For Weight Training
			break;
		case 'c':
		case 'C':
			met=4;    //For Cycling
			break;
		case 'd':
		case 'D':
			met=7;   //For Jogging
			break;
		case 'e':
		case 'E':
			met=10;   //For Rope Jumping
			break;
		default:
			met=1;
			break;
		}
		return met;
	}

//COVID Diet Plan Function	
void dietCovid(){
	struct diet covid[7];//Plan For 7 Days

	//Monday
	strcpy(covid[0].day[0],"Mon");
	strcpy(covid[0].time[0],"BreakFast");
	strcpy(covid[0].time[1],"Lunch");
	strcpy(covid[0].time[2],"Dinner");
	strcpy(covid[0].food[0],"Poha with Peanuts");
	strcpy(covid[0].food[1],"Lentils with Rice and Leafy Vegetables");
	strcpy(covid[0].food[2],"Pulka, Palya, and Lentils with Rice");

	//Tuesday
	strcpy(covid[1].day[1],"Tue");
	strcpy(covid[1].time[0],"BreakFast");
	strcpy(covid[1].time[1],"Lunch");
	strcpy(covid[1].time[2],"Dinner");
	strcpy(covid[1].food[0],"Oats Porridge with Nuts");
	strcpy(covid[1].food[1],"Lentils with Rice and Leafy Vegetables");
	strcpy(covid[1].food[2],"Egg Curry");
 
	//Wednesday
	strcpy(covid[2].day[2],"Wed");
	strcpy(covid[2].time[0],"BreakFast");   
	strcpy(covid[2].time[1],"Lunch");
	strcpy(covid[2].time[2],"Dinner");
	strcpy(covid[2].food[0],"Idli Sambhar");
	strcpy(covid[2].food[1],"Ajwain Namak Paratha with Dahi");
	strcpy(covid[2].food[2],"Khichri");
 
	//Thursday
	strcpy(covid[3].day[3],"Thurs");
	strcpy(covid[3].time[0],"BreakFast");
	strcpy(covid[3].time[1],"Lunch");
	strcpy(covid[3].time[2],"Dinner");
	strcpy(covid[3].food[0],"Vegetable Omelete with Whole-Wheat Bread");
	strcpy(covid[3].food[1],"Ajwain Namak Paratha with Dahi");
	strcpy(covid[3].food[2],"Paneer Bhurji");
 
	//Friday
	strcpy(covid[4].day[4],"Fri");
	strcpy(covid[4].time[0],"BreakFast");
	strcpy(covid[4].time[1],"Lunch");
	strcpy(covid[4].time[2],"Dinner");
	strcpy(covid[4].food[0],"Ragi Dosa or Plain Dosa");
	strcpy(covid[4].food[1],"Rajma rice");
	strcpy(covid[4].food[2],"Roti with Green Vegetables");
 
	//Saturday
	strcpy(covid[5].day[5],"Sat");
	strcpy(covid[5].time[0],"BreakFast");
	strcpy(covid[5].time[1],"Lunch");
	strcpy(covid[5].time[2],"Dinner");
	strcpy(covid[5].food[0],"Spinach Gram Flour Cheela");
	strcpy(covid[5].food[1],"Rajma Rice");
	strcpy(covid[5].food[2],"Moong Lentils Cheela");
 
	//Sunday
	strcpy(covid[6].day[6],"Sun");
	strcpy(covid[6].time[0],"BreakFast");
	strcpy(covid[6].time[1],"Lunch");
	strcpy(covid[6].time[2],"Dinner");
	strcpy(covid[6].food[0],"Cashew and Soaked Raisins");
	strcpy(covid[6].food[1],"Sabudana Khichri with Curd");
	strcpy(covid[6].food[2],"Zeera Rice and Sprouts Cooked with Little Tadka");

	//Printing Diet Plan:
	int i,j;
	printf("\n\n\t***7 DAY DIET PLAN FOR COVID PATIENTS***");	
	printf("\n_________________________________________________________________________\n");
	printf("DAY\t|TIME\t\t|FOOD");
	printf("\n_________________________________________________________________________\n");
	for(i=0;i<7;i++){
		printf("%s\t|",covid[i].day[i]);
  		for(j=0;j<3;j++){
  			if(j==0)
    			printf("%s\t",covid[i].time[j]);
 			else 
				printf("\t|%s\t\t",covid[i].time[j]);
   			printf("|%s",covid[i].food[j]);
			printf("\n");
  		}
	printf("_________________________________________________________________________\n");
 	}
}

//Dengue Diet Plan Function
void dietDengue(){
	struct diet dengue[7];//Plan For 7 Days

	//Monday
	strcpy(dengue[0].day[0],"Mon");
	strcpy(dengue[0].time[0],"BreakFast");
	strcpy(dengue[0].time[1],"Lunch");
	strcpy(dengue[0].time[2],"Dinner");
	strcpy(dengue[0].food[0],"Plain Roti Soaked in Milk With Added Sugar");
	strcpy(dengue[0].food[1],"Paraboiled Rice with Fish Stew");
	strcpy(dengue[0].food[2],"Boiled Rice with Carrot & Potato Curry");

	//Tuesday
	strcpy(dengue[1].day[1],"Tue");
	strcpy(dengue[1].time[0],"BreakFast");
	strcpy(dengue[1].time[1],"Lunch");
	strcpy(dengue[1].time[2],"Dinner");
	strcpy(dengue[1].food[0],"Plain Roti and Masoor Lentils Soup");
	strcpy(dengue[1].food[1],"Yellow Peas Lentils Curry with Fresh Lime");
	strcpy(dengue[1].food[2],"Mashed Boiled Rice, Milk, Jaggery");
 
	//Wednesday
	strcpy(dengue[2].day[2],"Wed");
	strcpy(dengue[2].time[0],"BreakFast");   
	strcpy(dengue[2].time[1],"Lunch");
	strcpy(dengue[2].time[2],"Dinner");
	strcpy(dengue[2].food[0],"Rice Flake Pulao With Peas and Carrots");
	strcpy(dengue[2].food[1],"Mashed Potato, Boiled Rice(Ghee on Warm Rice), Boiled Egg");
	strcpy(dengue[2].food[2],"Boiled Rice with Fish Stew");
 
	//Thursday
	strcpy(dengue[3].day[3],"Thurs");
	strcpy(dengue[3].time[0],"BreakFast");
	strcpy(dengue[3].time[1],"Lunch");
	strcpy(dengue[3].time[2],"Dinner");
	strcpy(dengue[3].food[0],"Plain Roti and Moong Lentils Soup");
	strcpy(dengue[3].food[1],"Paraboiled Rice with Chicken Stew");
	strcpy(dengue[3].food[2],"Boiled Rice(Ghee on Warm Rice) and Boiled Eggs");
 
	//Friday
	strcpy(dengue[4].day[4],"Fri");
	strcpy(dengue[4].time[0],"BreakFast");
	strcpy(dengue[4].time[1],"Lunch");
	strcpy(dengue[4].time[2],"Dinner");
	strcpy(dengue[4].food[0],"Custard and Toast");
	strcpy(dengue[4].food[1],"Paraboiled Rice with Fish Stew");
	strcpy(dengue[4].food[2],"Mashed Boiled Rice and Milk");
 
	//Saturday
	strcpy(dengue[5].day[5],"Sat");
	strcpy(dengue[5].time[0],"BreakFast");
	strcpy(dengue[5].time[1],"Lunch");
	strcpy(dengue[5].time[2],"Dinner");
	strcpy(dengue[5].food[0],"Plain Roti and Gram Lentils");
	strcpy(dengue[5].food[1],"Yellow Peas Lentils Curry with Fresh Lime");
	strcpy(dengue[5].food[2],"Boiled Rice with Fish Stew");
 
	//Sunday
	strcpy(dengue[6].day[6],"Sun");
	strcpy(dengue[6].time[0],"BreakFast");
	strcpy(dengue[6].time[1],"Lunch");
	strcpy(dengue[6].time[2],"Dinner");
	strcpy(dengue[6].food[0],"Milk and Cornflakes");
	strcpy(dengue[6].food[1],"Paraoiled Rice with Chicken Stew");
	strcpy(dengue[6].food[2],"Boiled Rice(Ghee on Warm Rice) with Mashed Potatoes");

	//printing diet plan:	
	int i,j;
	printf("\n\n\t***7 DAY DIET PLAN FOR DENGUE PATIENTS***");	
	printf("\n_______________________________________________________________________________________________________________________________\n");
	printf("DAY\t|TIME\t\t|FOOD");
	printf("\n_______________________________________________________________________________________________________________________________\n");
	for(i=0;i<7;i++){
		printf("%s\t|",dengue[i].day[i]);
  		for(j=0;j<3;j++){
  			if(j==0)
    			printf("%s\t",dengue[i].time[j]);
 			else 
				printf("\t|%s\t\t",dengue[i].time[j]);
   			printf("|%s",dengue[i].food[j]);
			printf("\n");
  		}
	printf("________________________________________________________________________________________________\n");
 	}
}

//Diabetes Diet Plan Function
void dietDiabetes(){
	struct diet diabetes[7];//Plan For 7 Days

	//Monday
	strcpy(diabetes[0].day[0],"Mon");
	strcpy(diabetes[0].time[0],"BreakFast");
	strcpy(diabetes[0].time[1],"Lunch");
	strcpy(diabetes[0].time[2],"Dinner");
	strcpy(diabetes[0].food[0],"Low-Fat plain Greek Yogurt, Blueberries, and Chopped Walnuts");
	strcpy(diabetes[0].food[1],"White Beans and Veggie Salad");
	strcpy(diabetes[0].food[2],"Garlic Butter-Roasted Salmon with Potatoes and Asparagus");

	//Tuesday
	strcpy(diabetes[1].day[1],"Tue");
	strcpy(diabetes[1].time[0],"BreakFast");
	strcpy(diabetes[1].time[1],"Lunch");
	strcpy(diabetes[1].time[2],"Dinner");
	strcpy(diabetes[1].food[0],"Muffin-Tin Omelets with Broccoli, Ham and Cheddar");
	strcpy(diabetes[1].food[1],"Spinach and Strawberry Meal-Prep Salad");
	strcpy(diabetes[1].food[2],"Stuffed Potatoes with Salsa & Beans,Citrus Vinaigrette, and Mixed Greens");
 
	//Wednesday
	strcpy(diabetes[2].day[2],"Wed");
	strcpy(diabetes[2].time[0],"BreakFast");   
	strcpy(diabetes[2].time[1],"Lunch");
	strcpy(diabetes[2].time[2],"Dinner");
	strcpy(diabetes[2].food[0],"Muffin-Tin Omelets with Broccoli, Ham and Cheddar");
	strcpy(diabetes[2].food[1],"Spinach and Strawberry Meal-Prep Salad");
	strcpy(diabetes[2].food[2],"Creamy Italian Chicken Skillet and cooked brown rice");
 
	//Thursday
	strcpy(diabetes[3].day[3],"Thurs");
	strcpy(diabetes[3].time[0],"BreakFast");
	strcpy(diabetes[3].time[1],"Lunch");
	strcpy(diabetes[3].time[2],"Dinner");
	strcpy(diabetes[3].food[0],"Low-Fat plain Greek Yogurt, Blueberries, and Chopped Walnuts");
	strcpy(diabetes[3].food[1],"Spinach and Strawberry Meal-Prep Salad");
	strcpy(diabetes[3].food[2],"Baked Eggs in Tomato Sauce with Kale and Whole-Wheat Bread");
 
	//Friday
	strcpy(diabetes[4].day[4],"Fri");
	strcpy(diabetes[4].time[0],"BreakFast");
	strcpy(diabetes[4].time[1],"Lunch");
	strcpy(diabetes[4].time[2],"Dinner");
	strcpy(diabetes[4].food[0],"Low-Fat plain Greek Yogurt, Blueberries, and Chopped Walnuts");
	strcpy(diabetes[4].food[1],"Spinach and Strawberry Meal-Prep Salad");
	strcpy(diabetes[4].food[2],"Slow-Cooker Chicken & White Bean Stew");
 
	//Saturday
	strcpy(diabetes[5].day[5],"Sat");
	strcpy(diabetes[5].time[0],"BreakFast");
	strcpy(diabetes[5].time[1],"Lunch");
	strcpy(diabetes[5].time[2],"Dinner");
	strcpy(diabetes[5].food[0],"Muffin-Tin Omelets with Broccoli, Ham & Cheddar");
	strcpy(diabetes[5].food[1],"Slow-Cooker Chicken & White Bean Stew");
	strcpy(diabetes[5].food[2],"Greek Salad with Edamame, avocado, and sliced");
 
	//Sunday
	strcpy(diabetes[6].day[6],"Sun");
	strcpy(diabetes[6].time[0],"BreakFast");
	strcpy(diabetes[6].time[1],"Lunch");
	strcpy(diabetes[6].time[2],"Dinner");
	strcpy(diabetes[6].food[0],"Low-Fat plain Greek Yogurt, Blueberries, and Chopped Walnuts");
	strcpy(diabetes[6].food[1],"Slow-Cooker Chicken & White Bean Stew");
	strcpy(diabetes[6].food[2],"Spicy Shrimp Tacos");


	int i,j;	
	printf("\n\n\t***7 DAYS DIET PLAN FOR DIABETES***");
	printf("\n________________________________________________________________________________________________________________________\n");
	printf("DAY\t|TIME\t\t|FOOD");
	printf("\n________________________________________________________________________________________________________________________\n");
	for(i=0;i<7;i++){
		printf("%s\t|",diabetes[i].day[i]);
		for(j=0;j<3;j++){
  			if(j==0)
    			printf("%s\t",diabetes[i].time[j]);
 			else printf("\t|%s\t\t",diabetes[i].time[j]);
   			printf("|%s",diabetes[i].food[j]);
			printf("\n");
 		 }
	printf("________________________________________________________________________________________________________________________\n");
 	}
}
	
//Main Function
int main(){	
	struct diet covid[7];
	struct diet dengue[7];
	struct diet diabetes[7];
	struct account acc;
	char choice;
	system("color 0A");
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t\t\t   *** WELCOME TO THE \"HEALTH & FITNESS COMPANION\" ***\n");
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	sleep(1);
	system("cls");
	system("color 0B");
	printf("\nEnter 'S' To Create an Account!\nIf You Already Have an Account, Enter 'L' to Login: \n");
	scanf("%c", &choice);
	fflush(stdin);
	while(choice!='s' && choice!='S' && choice!='l' && choice!='L'){
		printf("\nInvalid Choice. Re-Enter: ");
		scanf(" %c", &choice);
	}
	if(choice=='s' || choice=='S'){
		signup(acc);
		sleep(3);
		system("cls");
	}
	else if(choice=='l' || choice=='L'){
		login(acc);
		sleep(3);
		system("cls");
	}	
	
	system("color 0E");
	printf("\nWhat do you Want to Check?");
	printf("\nEnter your Choice from the Given Options:\n\n");
	select();
	 
	return 0;
}
