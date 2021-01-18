#include "StudentInterface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InitializeStudent (char *name, int grade, Student *S) {
	
	strcpy(S->name,name);
	S->grade = grade; 
	
	printf("\nInitializeStudents: %s\n",S->name);
	
}
char *NameOfStudent (Student S) {
	
	static char name[MAXNAMESIZE];
	strcpy(name,S.name);
	
	return name;
}
int GradeOfStudent (Student S) {

    static int grade;
    grade  = S.grade;

	return grade;
}
void FreeStudent (Student *S) {
	
	free(S);
}