#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student {
	int rollno;
	char name[50];
	float marks;
	struct student *next;
};
int c=0,i=0;
struct student *head=NULL;

// Generating roll number value function based and it is taking automatically new roll number
//  Generate next roll number

//ADD
void add_begin(void)
{
	struct student *newnode;
	char name [100];

	newnode = malloc(sizeof(struct student));

	if (newnode == NULL)
	{
		printf("Memory allocation failed!\n");
		return;
	}

	newnode->rollno = ++c;

	printf("Enter name:\n");
	scanf("%s", newnode->name);

	printf("Enter marks:\n");
	scanf("%f", &newnode->marks);

	newnode->next = head;
	head = newnode;

	printf("Record Added Successfully!\n");
}

//add node at end
void add_end()
{
	struct student *newnode,*last;

	newnode=(struct student*)malloc(sizeof(struct student));  // create a node
	//newnode->rollno= getRollno(); //assign the  data

	printf("Enter rollno:\n ");
	scanf("%d", &newnode->rollno);

	printf("Enter name:\n ");
	scanf("%s", newnode->name);

	printf("Enter marks:\n" );
	scanf("%f", &newnode->marks);

	newnode->next=NULL; //important

	if(head == NULL)  //check if list empty

		if (head == NULL)
		{

			head =newnode;   //first node

		}
		else
		{

			last=head;    //traverse to last node
			while(last->next != NULL)
			{
				last = last->next;
			}

			last->next=newnode;  //link new node at end

		}

	printf("Node added at end successfully!\n");
	printf("To show the data! press s/S\n");
}

//SHOW

void show()
{
	struct student *temp;
	struct student *current;
	int roll;

	if(head == NULL)
	{
		printf("No records!\n");
		return;
	}

	printf("\nROLLNO\tNAME\tMARKS\n");

	for(roll = 0; roll < c; roll++)
	{
		temp = head;

		while(temp != NULL)
		{
			if(temp->rollno == roll)
			{
				printf("%d\t%s\t%.2f\n",
						temp->rollno,
						temp->name,
						temp->marks);
				break;
			}

			temp = temp->next;
		}
	}
}

//DELETE
//void del()
void del(void)
{
	struct student *temp = head;
	struct student *prev = NULL;
	struct student *p;
	int rollno;
	int number = 1;

	printf("Enter rollno to delete:\n");
	scanf("%d", &rollno);

	while (temp != NULL && temp->rollno != rollno)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
	{
		printf("Record not found!\n");
		return;
	}

	if (prev == NULL)
		head = temp->next;
	else
		prev->next = temp->next;

	free(temp);

	c--;

	for (p = head; p != NULL; p = p->next)
	{
		p->rollno = number++;
	}

	printf("Deleted successfully!\n");
}

//MODIFY

// Modify record base on: Rollno number Name Marks

void modify() {
	char choice;

	struct student *temp;

	printf("\n Modify Record Based On:\n");
	printf("R/r : Roll No\nN/n : Name\nP/p : Percentage\n");
	printf("Enter choice: ");
	scanf(" %c", &choice);

	// ---- MODIFY BY ROLLNO ----
	if (choice == 'R' || choice == 'r') {
		int rollno;
		printf("Enter rollno number: ");
		scanf("%d", &rollno);

		temp = head;
		while (temp && temp->rollno != rollno)
			temp = temp->next;

		if (!temp) {
			printf("Record not found!\n");
			return;
		}
	}

	//------MODIFY BY NAME--------
	else if (choice =='N' || choice =='n'){
		char name[50];
		printf("enter name:\n");
		scanf ("%s",name);

		temp=head;
		int found =0;

		while(temp){
			if(strcmp(temp->name,name)==0){
				printf("Found->Rollno:%d Name:%s Marks:%.2f\n", temp->rollno,temp->name,temp->marks);

				found = 1;
			}
			temp=temp->next;
		}

		if(!found){
			printf("No record found!\n");
			return;
		}

		int rollno;
		printf("Enter roll number to modify: ");
		scanf("%d", &rollno);

		temp = head;
		while (temp && temp->rollno != rollno)
			temp = temp->next;
	}

	//-------MODIFY BY MARKS-------
	else if(choice =='p' || choice == 'p'){
		float marks;
		printf("Enter marks:\n");
		scanf("%f",&marks);

		temp=head;
		int found =0;
		while (temp){
			if(temp->marks == marks){
				printf("Found -> Rollno:%d Name:%s Marks:%.2f\n", temp->rollno, temp->name, temp->marks);
				found=1;
			}
			temp=temp->next;
		}
		if(!found){
			printf("no record found!\n");
			return;
		}
		int rollno;
		printf("Enter rollno  number to modify: ");
		scanf("%d", &rollno);

		temp = head;
		while (temp && temp->rollno != rollno)
			temp = temp->next;
	}

	else {
		printf("Invalid choice!\n");
		return;
	}

	//------UPDATE DATA------


	if (!temp) {
		printf("Record not found!\n");
		return;
	}

	printf("Enter new name:\n ");
	scanf("%s", temp->name);

	printf("Enter new marks:\n ");
	scanf("%f", &temp->marks);

	printf("Record Updated Successfully!\n");
	printf("To show the data! press s/S\n");
}

// SAVE TO FILE
void save()
{
	FILE *fp= fopen("student.txt","w");
	struct student *temp=head;

	while(temp){
		fprintf(fp, "%d %s %.2f\n", temp->rollno, temp->name, temp->marks);
		temp = temp->next;
	}
	fclose(fp);
	printf("Saved to file!\n");
}

// SORT BY NAME
void sortName() {
	struct student *i, *j;
	for (i = head; i; i = i->next) {
		for (j = i->next; j; j = j->next) {
			if (strcmp(i->name, j->name) > 0) {
				struct student temp = *i;
				*i = *j;
				*j = temp;

				struct student *t = i->next;
				i->next = j->next;
				j->next = t;
			}
		}
	}
	printf("Sorted by name!\n");
	printf("To show the data! press s/S\n");
}

// SORT BY MARKS
void sortMarks(){
	struct student *i, *j;
	for (i = head; i; i = i->next) {
		for (j = i->next; j; j = j->next) {
			if (i->marks > j->marks) {
				struct student temp = *i;
				*i = *j;
				*j = temp;

				struct student *t = i->next;
				i->next = j->next;
				j->next = t;
			}
		}
	}
	printf("Sorted by percentage!\n");
	printf("To show the data! press s/S\n");
}
// REVERSE
void reverse() {
	struct student *prev = NULL, *curr = head, *next;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	head = prev;
	printf("List Reversed!\n");
	printf("To show the data! press s/S\n");
}

// DELETE ALL
void deleteAll() {
	struct student *temp;
	while (head) {
		temp = head;
		head = head->next;
		free(temp);
	}
	c=0;
	printf("All records deleted!\n");
	printf("To show the data! press s/S\n");
}

// MAIN MENU
int main()
{
	char ch;
	int opt;

	while(1){

		printf("\n***** STUDENT RECORD MENU *****\n");
		printf(" a/A: add new record\n d/D: delete a record\n s/S: show the list\n m/M: Modify record based on: Rollnonumber,Name,and Marks\n v/V: save the file\n e/E: exit\n t/T: sorting the lists based on name/Marks\n l/L: delete all the records\n r/R: reverse the list\n");
		scanf(" %c", &ch);

		switch (ch) {
			case 'A':
			case 'a':add_begin(); break;
				 //				printf("1. Add_begin [elements add at first], Press 1 option to Add_begin\n2. Add_end[elements add at end[best method]], Press 2 option to Add_end\n");
				 //				scanf("%d", &opt);
				 //				if (opt == 1) add_begin();
				 //				else add_end();
				 //				break;

			case 'D':
			case 'd': del(); break;
			case 'S':
			case 's': show(); break;
			case 'M':
			case 'm': modify(); break;
			case 'V':
			case 'v': save(); break;
			case 'R':
			case 'r': reverse(); break;
			case 'L':
			case 'l': deleteAll(); break;

			case 'T':
			case 't':

				  printf("1. Sort by Name, Press 1 option to Sort by Name\n 2. Sort by marks, Press 2 option to Sort by Per\n");
				  scanf("%d", &opt);
				  if (opt == 1) sortName();
				  else sortMarks();
				  break;

			case 'E':
			case 'e':{
					 char opt;
					 printf("\nS/s: Save and Exit\nE/e: Exit without Saving\n");
					 printf("Enter choice: ");
					 scanf(" %c", &opt);

					 if (opt == 'S' || opt == 's') {
						 printf("saved the file and exited successfully\n");
						 save();
						 exit(0);
					 } else {
						 printf("Invalid choice!\n");
					 }
					 break;
				 }

			default:
				 printf("Invalid choice! Unkown option please press valid option!\n");
				 break;
		}
	}

}




































































































































































