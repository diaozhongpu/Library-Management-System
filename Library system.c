/*
*  file:Library system.c
*  author: DIAO Zhongpu
*  This file is the solution to Exercise 2, Chapter 16 in book
*  The Art and Science of C.
*  This program uses the linked list to store the information of books
*  when executing, and provide functions for reading & storing bookinfo
*  in database file. While running this program, the user can add new 
*  book to the database, delete existing item by library number, and list
*  all of books in order of library number.
*
*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 256
#define UPPERBOUND 1000
#define EndMarker "-----"
#define BigEndMarker "----------"
#define EndOfFile "=========="

typedef char *string;
typedef struct booknode {
	char title[MAX];
	char author[5][MAX];
	long catalongnum;
	char headings[5][MAX];
	char publisher[MAX];
	int year;
	int ifcirculating;
	struct booknode *next;
} booknode;
							/*
							* the data structure to store bookinfo
							*/
typedef booknode *libraryDB;
							/*
							* libraryDB will store the pointer to the head
							* of linked list
							*/


/*
* Function: static booknode * ReadDatabase()
* Usage: ReadDatabase();
* This function will read book information from database file (whose name
* will provided by user, and store it in a linked list whose head will 
* be returned.
*
*/
static booknode * ReadDatabase(); 

/*
* Function: void SaveDatabase(struct booknode *head);
* Usage: SaveDatabase(libdata);
* This function will store book information in the linked list to
* database file to use later.
*
*/
void SaveDatabase(struct booknode *head);

/*
* Function: static booknode * InsertDoc(struct booknode *head);
* Usage: InsertDoc(libdata);
* This function will add new book information to the linked list.
* In this function, user will be asked to provide the basic information
* of the book, and based on its library number, this book will be inserct
* into the linked list whose head is provided as parameter (libdata).
*
*/
static booknode * InsertDoc(struct booknode *head);

/*
* Function: static booknode * DeleteDoc(struct booknode *head);
* Usage: DeteleDoc(libdata);
* This function will delete exsiting book information by library
* number provided by the user.
*
*/
static booknode * DeleteDoc(struct booknode *head);

/*
* Function: static booknode * ReadDoc(void);
* Usage: ReadDoc();
* This function will incooprate with function InserctDoc().
* This function will ask user to enter basic bookinfo and store
* it in the booknode (an ADT defined above) and return a pointer 
* to this booknode. Therefore pass information from input to 
* abstract data structure.
*
*/
static booknode * ReadDoc(void);

/*
* Function: void PrintDoc(struct booknode *head);
* Usage: PrintDoc(libdata);
* This function will print all the book information stored
* in the linked list whose head is provided.
*
*/
void PrintDoc(struct booknode *head);

/*
* Function: void SearchBySubject (struct booknode *head);
* Usage: SearchBySubject(libdata);
* This function will search for book
*
*/
void SearchBySubject (struct booknode *head);

/*
* The Program STARTS HERE:
*/
int main()
{
	libraryDB libdata;
									/*
									* the head of the linked list to
									* store bookinfo
									*/
	int choice=1;
	
	libdata = ReadDatabase(); 

	
	while(choice)
	{
		printf("\nWhat do you want to do?\n1-search by subject\n2-input new item\n");
		printf("3-delete certain item\n4-print all items\n0-quit\n");
		scanf("%d%*c",&choice);
		switch(choice)
		{
			case 1:SearchBySubject (libdata); break;
			case 2:InsertDoc(libdata); break;
			case 3:libdata=DeleteDoc(libdata); break;
			case 4:PrintDoc(libdata); break;
			default: break;
		}
		
		
	}
	

	SaveDatabase(libdata);
	
	
    return 0;
	
	
}


static booknode * ReadDatabase()
{
	static booknode *head, *p;
	int size, i;
	string filename, input;
	FILE *fp;
	
	head = NULL;
	size = sizeof(booknode);
	filename = (string) malloc(MAX);
	input = (string) malloc(MAX);

	printf("Please enter the name of database:");
	scanf("%s", filename);

	
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Cannot load the database!");
		exit(1);
										/* exit if anything wrong */
	}

	head = (booknode*)malloc(size);
	p = head;

	while (1)
	{
		fscanf(fp, "%[^\n]%*c", p->title);
		for (i = 0; i < 5; i++)
		{
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
	
	fclose(fp);
	
	return head;

}

void SaveDatabase(struct booknode *head)
{
	FILE *fp;
	string filename;
	booknode *ptr;
	int i;
	
	filename=malloc(MAX);
	printf("Please enter the name of database:");
	scanf("%s",filename);

	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Cannot access the storage!");
		exit(1);
	}
	
	for (ptr = head; ptr != NULL; ptr = ptr->next)
	{
		fprintf(fp,"%s\n",ptr->title);
		for(i=0;i<5&&(*ptr->author[i]!=NULL);i++)
		{
			fprintf(fp,"%s\n",ptr->author[i]);
		}
		fprintf(fp,"%s\n",EndMarker);
		fprintf(fp,"%ld\n",ptr->catalongnum);
		for(i=0;i<5&&(*ptr->headings[i]!=NULL);i++)
		{
			fprintf(fp,"%s\n",ptr->headings[i]);		
		}	
		fprintf(fp,"%s\n",EndMarker);
		fprintf(fp,"%s\n",ptr->publisher);
		fprintf(fp,"%d\n",ptr->year);
		fprintf(fp,"%d\n", ptr->ifcirculating);
		
		if(ptr->next!=NULL)
		{
			fprintf(fp,"%s\n",BigEndMarker);
		}
		else
		{
			fprintf(fp,"%s\n",EndOfFile);
			break;
		}
	}

	fclose(fp);
}

static booknode * ReadDoc(void)
{
	static booknode *p;
	int i;
	
	printf("Please enter an new item:");

	p = (booknode*)malloc(sizeof(booknode));


	printf("Please enter the title of this book:");
	scanf("%[^\n]%*c", p->title);
	for (i = 0; i < 5; i++)
	{
		printf("Please enter %s author:(use '-----' to end)"
										,i?"another":"the first");
		scanf("%[^\n]%*c", p->author[i]);
		if (!strcmp(p->author[i], EndMarker))
		{
			*p->author[i] = NULL;
			break;
		}
	}
	printf("Please enter the library number:");
	scanf("%ld%*c",&p->catalongnum);		
	for (i = 0; i < 5; i++)
	{
		printf("Please enter %s heading:(use '-----' to end)",
										i?"another":"the first");
		scanf("%[^\n]%*c", p->headings[i]);
		if (!strcmp(p->headings[i], EndMarker))
		{
			*p->headings[i] = NULL;
			break;
		}
	}
	printf("Please enter the publisher:");
	scanf("%[^\n]%*c", p->publisher);
	printf("Please enter the publish year:");
	scanf("%d%*c", &p->year);
	printf("Whether the book is circulating: 1-yes, 0-no");
	scanf("%d%*c", &p->ifcirculating);
	
	return p;
}

static booknode * InsertDoc(booknode *head)
{
	static booknode *ptr,*ptr1,*ptr2;
	static booknode *book;
	
	book=ReadDoc();	
	ptr2=head;
	ptr=book;
	
	if(head==NULL)
	{
		head=ptr;
		head->next=NULL;
	}
	else 
	{
		while((ptr->catalongnum>ptr2->catalongnum)&&(ptr2->next!=NULL))
		{
			ptr1=ptr2;
			(ptr2)=(ptr2->next);
		}
		if(ptr->catalongnum<=ptr2->catalongnum)
		{
			if(head==ptr2)
			{
				head=ptr;
			}
			else
			{
				ptr1->next=ptr;
			}
			ptr->next=ptr2;
		}
		else
		{
			ptr2->next=ptr;
			ptr->next=NULL;
		}
	}
	
	return head;
}

static booknode * DeleteDoc(booknode *head)
{
	static booknode *ptr1,*ptr2;
	long catalongnum;
	
	printf("Please input the number of item to be deleted: ");
	scanf("%ld",&catalongnum);
	
	while(head!=NULL&&head->catalongnum==catalongnum)
	{
		ptr2=head;
		head=head->next;
		free(ptr2);
	}
	if(head==NULL)
	{
		return NULL;
	}
	ptr1=head;
	ptr2=head->next;
	while(ptr2!=NULL)
	{
		if(ptr2->catalongnum==catalongnum)
		{
			ptr1->next=ptr2->next;
			free(ptr2);
		}
		else
		{
			ptr1=ptr2;
		}
		ptr2=ptr1->next;
	}	
	
	return head;
}

void PrintDoc(booknode *head)
{
	static booknode *ptr;
	int i,num=1;
	
	if (head == NULL)
	{
		printf("\nNo Records\n");
		return;
	}

	printf("\nThe List of Books Are:");
	
	for (ptr = head; ptr != NULL; ptr = ptr->next)
	{
		printf("\nBOOK %d\n",num++);
		printf("Title:%s\nAuthor:\n",ptr->title);
		for(i=0;i<5&&(*ptr->author[i]!=NULL);i++)
		{
			printf("%s\n",ptr->author[i]);
		}
		printf("Library number:%ld\n",ptr->catalongnum);
		printf("Headings:\n");
		for(i=0;i<5&&(*ptr->headings[i]!=NULL);i++)
		{
			printf("%s\n",ptr->headings[i]);		
		}	
		printf("Publisher:%s\n",ptr->publisher);
		printf("Publish year:%d\n",ptr->year);
		printf("This book %s circulating\n",
							ptr->ifcirculating?"is":"is not");
	}

}

void SearchBySubject (struct booknode *head)
{
	string subject;
	booknode *ptr;
	int i,num=1;
	
	subject=malloc(256);
	printf("Please enter the subject you want to search for:");
	scanf("%[^\n]%*c",subject);
	
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		for(i=0;i<5&&*ptr->headings[i]!=NULL;i++)
		{
			if(!strcmp(ptr->headings[i],subject))
			{
				printf("BOOK %d\n",num++);
				printf("Title:%s\n",ptr->title);
				for(i=0;i<5&&(*ptr->author[i]!=NULL);i++)
				{
					printf("Author %d:%s\n",i,ptr->author[i]);
				}
				printf("Library number:%ld\n",ptr->catalongnum);
				break;
			}
		}
	}
	
}
