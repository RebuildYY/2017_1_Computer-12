#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int WIDTH;
int HEIGHT;
int* wall;
int* pre_wall;
int* cell;
int Id = 0;
FILE* file;

int main() {

	int i, j, k;
	int id;
	int check = 0;
	int pre_id, change;
	file = fopen("mazeGen.maz", "wt");

	printf("Width : ");
	scanf("%d", &WIDTH);
	printf("Hight : ");
	scanf("%d", &HEIGHT);
	wall = (int*)malloc(sizeof(int)*(WIDTH));
	pre_wall = (int*)malloc(sizeof(int)*(WIDTH));
	cell = (int*)malloc(WIDTH*sizeof(int));
	for (i = 0; i < WIDTH; i++) {
		fprintf(file, "+-");
		printf("+-");
		wall[i] = i+1;
	}
	id = i+1;
	fprintf(file, "+\n");
	printf("+\n");
	//맨 위에 있는 필드와 배열을 초기화 해준다.
	srand(time(NULL));

	for (i = 0; i < HEIGHT-1; i++) {
		fprintf(file, "|");
		printf("|");
		for (j = 0; j < WIDTH - 1; j++) {
			if (wall[j] != wall[j+1]) {
				if (rand() % 2 == 0) {//뚫는다.
					pre_id = wall[j + 1];//바꿔야 할 id
					change = wall[j];//change으로 바꾼다.
					for (k = 0; k < WIDTH; k++) {//집합의 포함된 모든 수를 바꾼다.
						if (wall[k] == pre_id) {
							wall[k] = change;
						}
					}
					fprintf(file, "  ");
					printf("  ");
				}
				else{//막는다.
					fprintf(file, " |");
					printf(" |");
				}
			}
			else {
				fprintf(file, " |");
				printf(" |");
			}
		}
		fprintf(file, " |\n");
		printf(" |\n");
		for (j = 0; j < WIDTH; j++) {//방과 방 사이의 층을 그려준다.
			check = 0;//check는 같은 집합 내에서 아래 바닥을 뚫었는지 여부를 구분할 때 사용한다. 뚫은 적이 있으면 1
			if (rand() % 2 == 0) {
				cell[j] = 0;
			}
			else {
				for (k = 0; k < j; k++) {
					if (wall[k] == wall[j] && cell[k] == 0) {
						check = 1;
					}
				}
				if (check == 1) {//이전에 같은 블록에서 뚫어준적이 있을떄
					cell[j] = 1;
				}
				else {//없을 떄
					for (k = j + 1; k < WIDTH; k++) {
						if (wall[k] == wall[j]) {//만약 뒤에 같은 집합이 있는지 확인
							check = 1;
							break;
						}
					}
					if (check == 1) {//뒤에 집합이 있으면 막는다.
						cell[j] = 1;
					}
					else {//없으면 뚫는다.
						cell[j] = 0;
					}
				}
			}
		}
	
		for (j = 0; j < WIDTH; j++) {
			if (cell[j] == 1) {
				fprintf(file, "+-");
				printf("+-");
				pre_wall[j] = id;
				id++;
			}
			else {
				fprintf(file, "+ ");
				printf("+ ");
				pre_wall[j] = wall[j];
			}
		}
		fprintf(file, "+\n");
		printf("+\n");
		//cell 출력

		for (j = 0; j < WIDTH; j++) {
			wall[j] = pre_wall[j];
		}//다음 행을 위한 설정
	}//마지막 전 행까지 출력

	fprintf(file, "|");
	printf("|");
	for (i = 0; i < WIDTH - 1; i++) {
		if (wall[i] != wall[i + 1]) {
			fprintf(file, "  ");
			printf("  ");
			pre_id = wall[i + 1];//바꿔야 할 id
			change = wall[i];//change으로 바꾼다.
			for (k = 0; k < WIDTH; k++) {//집합의 포함된 모든 수를 바꾼다.
				if (wall[k] == pre_id) {
					wall[k] = change;
				}
			}
		}// 옆에 열(칸)과 다를 경우 뚫어준다.
		else {
			fprintf(file, " |");
			printf(" |");
		}
	}
	fprintf(file, " |\n");
	printf(" |\n");
	//마지막행 출력

	for(i = 0; i<WIDTH; i++) {
		fprintf(file, "+-");
		printf("+-");
	}
	fprintf(file, "+\n");
	printf("+\n");
	//맨 아래에 있는 필드를 그려준다.
	return 0;
}