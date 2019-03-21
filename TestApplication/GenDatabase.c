/*
*  Filename: GenDatabase
*  Function: Generate the database file.
*  Author  : DIAO Zhongpu
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXINPUT 256
#define MAXPROBLEM 100

#define EndMarker "-----"

main()
{
	typedef char pfb[MAXINPUT];
	pfb feedback[MAXPROBLEM+1];
									//this "array of string" is to store feedback
	FILE *fp;
	char filename[MAXINPUT],input[MAXINPUT];	
									//strings to store input
	int curqnum=1,maxqnum=0;					
									//record current/maxinum question number
	int ansnum;						//the number of possible answer for certain question
	int tonum;						//the number of next question after certain answer
	int i;
	
	printf("This application is to generate database for modified ");
	printf("teach.c program. Please follow instructions below.\n");
	printf("Please enter the file's name (filename extension should be included): ");
	scanf("%s",filename);
	//strcat(filename,".txt");
	if((fp=fopen(filename,"w"))==NULL){	
						//create database file according to user's assignment
		printf("File open error!\n");
		exit(0);
	}
	
	printf("Please enter the title of this test: ");
	getchar();
	scanf("%[^\n]",input);
	fprintf(fp,"%s\n",input);
	
	
	while(1)
	{

		
		printf("Please enter the %d%s question (enter q to quit):",
			curqnum,(curqnum%10==1)?"st":(curqnum%10==2?"nd":(curqnum%10==3?"rd":"th")));
												// enter the question
		getchar();
		scanf("%[^\n]",input);
		if(strcmp(input,"q")){
			fprintf(fp,"%s%d\n",(curqnum==1)?"":"\n",curqnum);
			if(feedback!=NULL){
				fprintf(fp,"%s\n",feedback[tonum]);
												//record the feedback, if any
			}
			fprintf(fp,EndMarker);
			fprintf(fp,"\n");
			fprintf(fp,"%s\n",input);
			curqnum++;
		} else {
			break;
		}		
		fprintf(fp,EndMarker);
		fprintf(fp,"\n");
				
		printf("How many possible answers are there to this question? ");
		scanf("%d",&ansnum);
		
		for(i=0;i<ansnum;i++){
			printf("Please enter one possible answer to this question:");
			getchar();
			scanf("%[^\n]",input);
			printf("Please enter what number of the question that answer leading to: ");
			scanf("%d",&tonum);
			fprintf(fp,"%s: %d\n",input,tonum);
			printf("What feedback will be displayed? ");
			getchar();
			scanf("%[^\n]",feedback[tonum]);
			
		}

	}
	
	
	
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
	
}
