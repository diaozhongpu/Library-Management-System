/*
* list.c 
*
*
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern *booknode;

#define UPPERBOUND 1000

typedef char* string;
/*
typedef struct{
	string title;
	string author[5];
	long long catalongnum;
	string headings[5];
	string publisher;
	int year;
	int ifcirculating;
	struct booknode *next;
} booknode; 
typedef booknode libraryDB[UPPERBOUND];


struct booknode{
	string title;
	string author[5];
	long long catalongnum;
	string headings[5];
	string publisher;
	int year;
	int ifcirculating;
	struct booknode *next;
} ; 

struct booknode;
typedef struct booknode{
	string title;
	string author[5];
	long long catalongnum;
	string headings[5];
	string publisher;
	int year;
	int ifcirculating;
	struct booknode *next;
} booknode; 
*/




/*
struct booknode * CreateDoc()
{
	struct booknode *head, *p;
	string title;
	string author[5];
	long long catalongnum;
	string headings[5];
	string publisher;
	int year;
	int ifcirculating;
	int size;
	
	head=NULL;
	size=sizeof(booknode);
	
	printf("Input title, author, labrary number, headings, publish year, publisher, and 1 for circulating, 0 otherwise:");
	//scanf("%s %s%s%s%s%s %lld %s%s%s%s%s %d %s %d",title,author[0],author[1],
	//	author[2],author[3],author[4],&catalongnum,headings[0],headings[1],
	//	headings[2],headings[3],headings[4],&year,publisher,&ifcirculating);
//	while(catalongnum!=0)
	{
		p=(struct booknode*) malloc(size);
		strcpy(p->title,title);
		p->catalongnum=catalongnum;
		//...
		
		head=InsertDoc(head);
		//scanf("%s %s%s%s%s%s %lld %s%s%s%s%s %d %s %d",title,author[0],author[1],
		//	author[2],author[3],author[4],&catalongnum,headings[0],headings[1],
		//	headings[2],headings[3],headings[4],&year,publisher,&ifcirculating);
		
	}
	
	
	return head;
	
}
*/

//struct booknode * ReadDoc(struct booknode *head, struct booknode *book);

static booknode * InsertDoc(booknode *head)
{
	static booknode *ptr,*ptr1,*ptr2;
	static booknode *book; //=ReadDoc();
	
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
		printf("This book %s circulating\n", ptr->ifcirculating?"is":"is not");
	}

}



void SearchHeadings(booknode *head, string heading)
{
	static booknode *ptr;
	int i;
	for(ptr=head;ptr!=NULL;ptr=ptr->next)
	{
		for(i=0;i<5;i++)
		{
			if(!strcmp(ptr->headings[i],heading))
			{
				printf("%ld\n",ptr->catalongnum);
				break;
			}
		}

	}
}


void SearchBySubject (booknode *libdata,string subject)
{
	int i,j;
	for(i=0;i<UPPERBOUND;i++)
	{
		for(j=0;j<5;j++)
		{
			(libdata[i]).year=0;
			
			
			
		}
		printf("%d",(libdata[i]).year);
	}
	
	
}



