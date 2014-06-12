#include <stdio.h>
// NALOGA 3 THE NOOBISH WAY
int t[1000][1000];

int main(){
	int sizex, sizey;
	int x, y, c;
	t[0][0] = 1;
	scanf("%d %d", &sizex, &sizey);
	while((c = scanf("%d %d", &x, &y))== 2){
		t[x][y] = -1;
	}
	c = 0;
	//racunanje poti
	while(c < sizex * sizey){
		c += 1;
		for(x = 0; x < sizex; x++){
			for(y = 0; y < sizey; y++){
				if(t[x][y] == c ){
					if(y + 1 != sizey) if(t[x][y + 1] == 0 ) t[x][y + 1] = c + 1;
					if(x + 1 != sizex) if(t[x + 1][y] == 0) t[x + 1][y] = c + 1;
					if(y != 0) if(t[x][y - 1] == 0) t[x][y - 1] = c + 1;
					if(x != 0) if(t[x - 1][y] == 0) t[x - 1][y] = c + 1;
				}
			}
		}
	}
	//izpis rezultata
	if(t[sizex - 1][sizey - 1] == 0 || t[sizex - 1][sizey - 1] == -1) printf("%d\n",-1);
	else printf("%d\n",t[sizex - 1][sizey - 1] - 1);

	return 0;
}
