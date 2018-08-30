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
	//�� ���� �ִ� �ʵ�� �迭�� �ʱ�ȭ ���ش�.
	srand(time(NULL));

	for (i = 0; i < HEIGHT-1; i++) {
		fprintf(file, "|");
		printf("|");
		for (j = 0; j < WIDTH - 1; j++) {
			if (wall[j] != wall[j+1]) {
				if (rand() % 2 == 0) {//�մ´�.
					pre_id = wall[j + 1];//�ٲ�� �� id
					change = wall[j];//change���� �ٲ۴�.
					for (k = 0; k < WIDTH; k++) {//������ ���Ե� ��� ���� �ٲ۴�.
						if (wall[k] == pre_id) {
							wall[k] = change;
						}
					}
					fprintf(file, "  ");
					printf("  ");
				}
				else{//���´�.
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
		for (j = 0; j < WIDTH; j++) {//��� �� ������ ���� �׷��ش�.
			check = 0;//check�� ���� ���� ������ �Ʒ� �ٴ��� �վ����� ���θ� ������ �� ����Ѵ�. ���� ���� ������ 1
			if (rand() % 2 == 0) {
				cell[j] = 0;
			}
			else {
				for (k = 0; k < j; k++) {
					if (wall[k] == wall[j] && cell[k] == 0) {
						check = 1;
					}
				}
				if (check == 1) {//������ ���� ��Ͽ��� �վ������� ������
					cell[j] = 1;
				}
				else {//���� ��
					for (k = j + 1; k < WIDTH; k++) {
						if (wall[k] == wall[j]) {//���� �ڿ� ���� ������ �ִ��� Ȯ��
							check = 1;
							break;
						}
					}
					if (check == 1) {//�ڿ� ������ ������ ���´�.
						cell[j] = 1;
					}
					else {//������ �մ´�.
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
		//cell ���

		for (j = 0; j < WIDTH; j++) {
			wall[j] = pre_wall[j];
		}//���� ���� ���� ����
	}//������ �� ����� ���

	fprintf(file, "|");
	printf("|");
	for (i = 0; i < WIDTH - 1; i++) {
		if (wall[i] != wall[i + 1]) {
			fprintf(file, "  ");
			printf("  ");
			pre_id = wall[i + 1];//�ٲ�� �� id
			change = wall[i];//change���� �ٲ۴�.
			for (k = 0; k < WIDTH; k++) {//������ ���Ե� ��� ���� �ٲ۴�.
				if (wall[k] == pre_id) {
					wall[k] = change;
				}
			}
		}// ���� ��(ĭ)�� �ٸ� ��� �վ��ش�.
		else {
			fprintf(file, " |");
			printf(" |");
		}
	}
	fprintf(file, " |\n");
	printf(" |\n");
	//�������� ���

	for(i = 0; i<WIDTH; i++) {
		fprintf(file, "+-");
		printf("+-");
	}
	fprintf(file, "+\n");
	printf("+\n");
	//�� �Ʒ��� �ִ� �ʵ带 �׷��ش�.
	return 0;
}