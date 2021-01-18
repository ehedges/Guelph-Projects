#include "ListInterface.h"
#include <stdlib.h>
#include <stdio.h>
/* some code here (e.g., #include directives, static functions) */

int main (void) {
	/* some code here*/
	
	List * studentList;
	
    Item tempStudent;
    Item * pointStudents;
    
	char * name;

	int grade;
	int type;
	int print;

	studentList = (List*)malloc(sizeof(List));	
	
	pointStudents = (Item*)malloc(sizeof(Item));
	name  = (char*)malloc(sizeof(char)*20);
   /* test = (Student*)malloc(sizeof(Student));
*/
	name = "Bob";
	grade = 42;

	Initialize(studentList);
	
/*	printf("\n StudentList: %s\n", studentList->items[1].name);
*/	
	type = Full(studentList);
	printf("IsFull: %d",type);
	type = Empty(studentList);
	printf("IsEmpty: %d",type);
	type = Size(studentList);
	printf("Size: %d",type);
	
	InitializeStudent (name,grade,&tempStudent);
	
	Insert(tempStudent,1,studentList);
	
/*	printf("\nList;%d\n",studentList->items[1].grade);
	printf("\nList;%s\n",studentList->items[1].name);*/
	type = Full(studentList);
	printf("IsFull: %d\n",type);
	type = Empty(studentList);
	printf("IsEmpty: %d\n",type);
	type = Size(studentList);
	printf("Size: %d\n",type);
	
	Peek(1,studentList,pointStudents);
	printf("AfterPeeking\n");
	type = Empty(studentList);
	printf("IsEmpty: %d\n",type);
/*	printf("\nThis is peekd: %d \n",pointStudents->grade);
	printf("\nThis is peekd: %s \n",pointStudents->name);
*/	
	tempStudent = *pointStudents;
	
	print = GradeOfStudent(tempStudent);
	
	printf("Grade of StudentM: %d",print);
	
	name = NameOfStudent(tempStudent);

	printf("\nThe name: %s\n",name);

    printf("Ending\n");

	Remove(1,studentList);
	
	FreeStudent(pointStudents);
	
	Destroy(studentList);

	
    return EXIT_SUCCESS;
}