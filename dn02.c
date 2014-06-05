#include <stdio.h>
// NALOGA 2 RESITEV Z ENIM LOOPOM
int input, currentsum, maxlength, currentlength, maxsum, currentindex, maxindex, i, length;

int main(){
	scanf("%d %d", &length, &input);
	maxsum = input;
	maxlength = 1;
	for(i = 0; i < length; i++){
		currentsum = currentsum + input;
		if(currentlength == 0) currentindex = i;
		currentlength = currentlength + 1;
		if(currentsum > maxsum){
			maxsum = currentsum;
			maxindex = currentindex;
			maxlength = currentlength;
		}
		if(currentsum < 0){
			currentlength = 0;
			currentsum = 0;
			currentindex = 0;
		}
		scanf("%d", &input);
	}
	printf("%d %d %d\n", maxindex, maxlength, maxsum);
}
