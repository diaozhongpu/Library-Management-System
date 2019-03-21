/*
* storage.c
*
*
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
extern booknode;

#define UPPERBOND 1000
#define EndMarker "-----"
#define BigEndMarker "----------"
#define EndOfFile "=========="

static booknode * ReadDatabase()
{
	static booknode *head, *p;
	int size, i;
	string filename, input;

	head = NULL;
	size = sizeof(booknode);
	filename = (string) malloc(256);
	input = (string) malloc(256);

	printf("Please enter the name of database:");
	scanf("%s", filename);

	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Cannot load the database!");
		return NULL;
	}

	head = (booknode*)malloc(size);
	p = head;

	/*
		#define New(type) ((type) GetBlock(sizeof *((type) NULL)))
		void *GetBlock(size_t nbytes)
		{
		void *result;

		if (_acb == NULL) {
			result = malloc(nbytes);
		} else {
			result = _acb->allocMethod(nbytes);
		}
		if (result == NULL) Error("No memory available");
		return (result);
		}
	*/

	while (1)
	{
		//fgets(p->title,256,fp);
		fscanf(fp, "%[^\n]%*c", p->title);
		for (i = 0; i < 5; i++)
		{
			//fgets(p->author[i],256,fp);
			fscanf(fp, "%[^\n]%*c", p->author[i]);
			if (!strcmp(p->author[i], EndMarker))
			{
				*p->author[i] = NULL;
				break;
			}
		}
		fscanf(fp,"%ld%*c",&p->catalongnum);		
		for (i = 0; i < 5; i++)
		{
			//fgets(p->headings[i],256,fp);
			fscanf(fp, "%[^\n]%*c", p->headings[i]);
			if (!strcmp(p->headings[i], EndMarker))
			{
				*p->headings[i] = NULL;
				break;
			}
		}
		fscanf(fp, "%[^\n]%*c", p->publisher);
		fscanf(fp, "%d%*c", &p->year);
		fscanf(fp, "%d%*c", &p->ifcirculating);
		fscanf(fp, "%[^\n]%*c", input);
		printf("%s",input);
		if (!strcmp(input, EndOfFile))
		{
			p->next = NULL;
			break;
		}
		else
		{
			(p->next) = (booknode*)malloc(size);
			p = p->next;
		}
	}
	return head;

}



/* Section 1 ¨C Functions to read the data file */
/*
* Function: ReadDataBase
* Usage: ReadDataBase ();
* ----------------------------------
* This function asks the user for a file name and reads 
* in the database for the course. The file is formatted 
* as discussed in the section "Designing the external
* structures" in Chapter 16.
*/


void SaveDatabase()
{
	FILE *fp;
	string filename;
	
	
	printf("Please enter the name of database:");
	scanf("%s",filename);

	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Cannot access the storage!");
		return;
	}
	
	
	
	
	
}





