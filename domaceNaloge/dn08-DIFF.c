#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argumenti, char * argument[]){
	char * diff = malloc((strlen(argument[1]) + strlen(argument[2]) + 20) * sizeof(char));
	sprintf(diff, "diff -0u %s %s", argument[1], argument[2]);
	FILE * result = fopen(argument[3], "w");
	FILE * diff_out = popen(diff, "r");
	char input[110];
	fgets(input, sizeof(input) - 1, diff_out);
	fgets(input, sizeof(input) - 1, diff_out);
	while (fgets(input, 109, diff_out) != NULL) {
		if(input[0] == '+' || input[0] == '-'){
			fprintf(result, "%c", input[1]);
		}
	}
	pclose(diff_out); 
	fprintf(result, "\n");
	fclose(result);
	return 0;
}
