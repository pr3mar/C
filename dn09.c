#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTENT_SIZE 102

typedef struct _tags {
	char *tag;
	struct _tags *next;
} strTags, *ptrTags;

typedef struct _grades {
	char *gradeID;
	int grade;
	struct _grades *next;
} strGrades, *ptrGrades;

typedef struct _student {
	char *studentID;
	ptrGrades grades;
	struct _student *next;
} strStudent, *ptrStudent;


int size = CONTENT_SIZE;

ptrStudent preberi(FILE *file);
char * enlarge(char *tmp);
/* stack functions */
ptrTags addStack(ptrTags top, char *tag);
ptrTags deleteStack(ptrTags top);
/* student list manipulation */
ptrStudent insertStudent(ptrStudent first, char * studentID, char *gradeID, char *grade);// returns the beginning of the list
void printStudents(ptrStudent student);
/* grade list manipulation */
ptrGrades insertGrade(ptrGrades first, char *gradeID, char *grade); // returns the beginning of the list
void printGrades(ptrGrades grade);

int main(int argc, char ** argv)
{
	FILE *file = NULL;
	if (argc == 1) {
		file = stdin;
	} else {
		file = fopen(argv[1], "r");
		if (file == NULL) {
			printf("napaka 1\n");
			return 0;
		}
	}

	ptrStudent students = NULL;
	students = preberi(file);
	if(students == NULL) {
		printf("\n");
		return 0;
	}

	printStudents(students);

	return 0;
}

ptrStudent preberi(FILE *file) {
	char tmp, buff = -1;
	ptrTags stack = NULL;
	ptrStudent first = NULL;
	char *content = (char*) malloc(sizeof(char) * (size + 1));
	char *tmpVpis = (char*) malloc(sizeof(char) * (size + 1));
	char *tmpnID = (char*) malloc(sizeof(char) * (size + 1));
	char *tmpVred = (char*) malloc(sizeof(char) * (size + 1));
	int stage = -1;
	int i = 0;
	while((tmp = fgetc(file)) != EOF) {
		if(tmp == '<') {
			if(stage == 2 && strcmp(stack->tag, "ocene") != 0 
					&& strcmp(stack->tag, "ocena") != 0) {
				content[i] = '\0';				
				if (strcmp(stack -> tag, "vpisnaStevilka") == 0) {
					strcpy(tmpVpis, content);
				} else if (strcmp(stack -> tag, "nalogaId") == 0) {
					strcpy(tmpnID, content);
				} else if (strcmp(stack -> tag, "vrednost") == 0) {
					strcpy(tmpVred, content);
				} 
			}
			stage = 1;
			buff = tmp;
			i = 0;
			continue;
		}else if(tmp == '/' && buff == '<') {
			stage = 3;
			buff = tmp;
			i = 0;
			continue;
		} else if(tmp == '>') {
			content[i] = '\0';
			if (stage == 1) {
				stack = addStack(stack, content);
			} else if (stage == 3) {
				if(strcmp(stack -> tag, content) == 0) {
					if(strcmp(stack -> tag, "ocena") == 0) {
						if(strlen(tmpVpis) == 0 || strlen(tmpnID) == 0 || strlen(tmpVred) == 0) {
							printf("napaka 2\n");
							exit(0);
						} else {
							first = insertStudent(first, tmpVpis, tmpnID, tmpVred);
							tmpVpis[0] = '\0'; tmpnID[0] = '\0'; tmpVred[0] = '\0';
						}
					}
					stack = deleteStack(stack);
				} else {
					printf("napaka 3\n");
					exit(0);
				}
			}
			buff = tmp;
			stage = 2;
			i = 0;
			continue;
		}
		if(i == (size - 1)) {
			content = enlarge(content);
		}
		
		if( (tmp >= 'A' && tmp <= 'Z') 
				|| (tmp >= 'a' && tmp <= 'z')
					|| (tmp >= '0' && tmp <= '9')) {
			content[i] = tmp;
			buff = tmp;
			i++;
		}
	}

	return first;
}

void printStudents(ptrStudent student) {
	int count = 0, sum = 0;
	while(student != NULL) {
		ptrGrades tmp = student -> grades;
		count = 0; sum = 0;
		while(tmp != NULL) {
			count++;
			sum += tmp -> grade;
			tmp = tmp -> next;
		}
		printf("%s %d %d\n", student -> studentID, count, sum);
		student = student -> next;
	}
}

void printGrades(ptrGrades grade) {
	while(grade != NULL) {
		printf("\t %s %d\t", grade -> gradeID, grade -> grade);
		grade = grade -> next;
	}	
}

ptrGrades insertGrade(ptrGrades first, char *gradeID, char *grade) {
	if(first == NULL) {
		first = (ptrGrades) malloc(sizeof(strGrades));
		char *tmp = (char *) malloc(sizeof(char) * (strlen(gradeID) + 1));
		strcpy(tmp, gradeID);
		first -> gradeID = tmp;
		first -> grade = atoi(grade);
		first -> next = NULL;
		return first;
	} else if (strcmp(first -> gradeID, gradeID) == 0) {
		first -> grade = atoi(grade);
		return first;
	} else {
		first -> next = insertGrade(first -> next, gradeID, grade);
		return first;
	}
}

ptrStudent insertStudent(ptrStudent first, char * studentID, char *gradeID, char *grade) {
	if(first == NULL) {
		first = (ptrStudent) malloc(sizeof(strStudent));
		char *tmpID = (char*) malloc(sizeof(char) * (strlen(studentID) + 1));
		strcpy(tmpID, studentID);
		first -> studentID = tmpID;
		ptrGrades pGrade = (ptrGrades) malloc(sizeof(strGrades));
		pGrade = NULL;
		first -> grades = insertGrade(pGrade, gradeID, grade);
		first -> next = NULL;
		return first;
	} else if(strcmp(first -> studentID, studentID) == 0) {
		// add grade
		first -> grades = insertGrade(first -> grades, gradeID, grade);
		return first;
	} else if(strcmp(first -> studentID, studentID) < 0) { // if '>' -> '<' the order is changed
		// recursively go forward
		first -> next = insertStudent(first -> next, studentID, gradeID, grade);
		return first;
	} else { //if(strcmp(first -> studentID, studentID) < 0) {
		// add to the beginning
		ptrStudent tmp = (ptrStudent) malloc(sizeof(strStudent));
		char *tmpID = (char*) malloc(sizeof(char) * (strlen(studentID) + 1));
		strcpy(tmpID, studentID);
		tmp -> studentID = tmpID;
		ptrGrades pGrade = (ptrGrades) malloc(sizeof(strGrades));
		pGrade = NULL;
		tmp -> grades = insertGrade(pGrade, gradeID, grade);
		tmp -> next = first;
		return tmp;
	}
}

ptrTags addStack(ptrTags top, char *tag) {
	ptrTags newTop = (ptrTags) malloc(sizeof(strTags));
	char *addTag = (char *) malloc(sizeof(char) * (strlen(tag) + 1));
	strcpy(addTag, tag);
	newTop -> tag = addTag;
	newTop -> next = top;
	return newTop;
}

ptrTags deleteStack(ptrTags top) {
	ptrTags tmp = (ptrTags) malloc(sizeof(strTags));
	tmp = top;
	top = top -> next;
	free(tmp -> tag);
	free(tmp);
	tmp = NULL;
	return top;
}

char * enlarge(char *tmp) {
	size += CONTENT_SIZE;
	tmp = (char *) realloc(tmp, sizeof(char*) * (size + 1));
	return tmp;
}
