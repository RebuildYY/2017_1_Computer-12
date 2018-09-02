#include <stdlib.h>
#include "..\ExternDoc.h"
#include "..\UI\Zoom.h"
#include "..\UI\MsgView.h"
#include "..\Graphics\DrawFunc.h"
#include "..\Example\Example.h"

#define ERROR_NUMBER -1

typedef struct _node *nodePointer;
typedef struct _node {
	int vertex;
	nodePointer link;
}Node;
typedef struct linked *linkedPointer;
typedef struct linked {
	int data;
	linkedPointer link;
}Linked;
typedef struct result *resultPointer;
typedef struct result {
	int start;
	int finish;
	resultPointer link;
}Result;

nodePointer *adjlist;
int *visited;
linkedPointer S;
linkedPointer Q;
linkedPointer Qu;
resultPointer result;
int **wall;
int Width =0, Height=0;
int finishflag = 0;
int dfsflag = 0;
int bfsflag = 0;
//function prototype

static void drawDirect(CDC *pDC);
static void drawBuffered();

//Start of user code
#include <float.h>

/*****************************************************************
* function	: bool readFile(const char* filename)
* argument	: cons char* filename - filename to be opened
* return	: true if success, otherwise flase
* remark	: After read data file, phisycal view must be set;
*			  otherwise drawing will not be executed correctly.
*			  The window will be invalidated after readFile()
*			  returns true.
******************************************************************/
void DFS(void){
	nodePointer w;
	linkedPointer temp;
	linkedPointer del;
	resultPointer rtemp;
	w = (nodePointer)malloc(sizeof(Node));
	int target = Width*Height - 1, i;
	int check = 0,v = 0;
	visited = (int*)malloc((Height*Width)*sizeof(int));
	for (i = 0; i < Height*Width; i++) {
		visited[i] = FALSE;
	}
	visited[v] = TRUE;
	temp = (linkedPointer)malloc(sizeof(Linked));
	temp->data = v;
	temp->link = NULL;
	S = temp;
	while (S != NULL) {
		if (S->data == target){ 
			break;
		}
		w = adjlist[S->data]->link;
		check = 0;
		while (1) {
			if (visited[w->vertex] == FALSE) {
				rtemp = (resultPointer)malloc(sizeof(Result));
				rtemp->start = S->data;
				rtemp->finish = w->vertex;
				rtemp->link = NULL;	
				temp = (linkedPointer)malloc(sizeof(Linked));
				temp->data = w->vertex;
				temp->link = S;
				S = temp;
				if(result == NULL){
					result = rtemp;
				}
				else{
					rtemp->link = result;
					result = rtemp;
				}
				visited[w->vertex] = TRUE;
				check = 1;
				break;
			}
			if (w->link == NULL) {
				break;
			}
			w = w->link;
		}
		if (check == 0) {//방문할게 없는 경우 pop
			del = S;
			S = S->link;
			free(del);
		}
	}
	dfsflag = 1;
	finishflag = 1;
}
void BFS(void){
	nodePointer w;
	resultPointer rtemp;
	linkedPointer temp;
	linkedPointer del;
	linkedPointer rear;
	int target = Width*Height - 1;
	int i, v=0, key;
	int prevertex;
	visited = (int*)malloc((Height*Width)*sizeof(int));
	for (i = 0; i < Height*Width; i++) {
		visited[i] = FALSE;
	}
	visited[v] = TRUE;
	temp = (linkedPointer)malloc(sizeof(Linked));
	temp->data = v;
	temp->link = NULL;
	Q = temp;
	rear = Q;
	while (Q != NULL) {
		if (Q->data == target) break;
		w = adjlist[Q->data]->link;
		prevertex = Q->data;
		Q = Q->link;
		while (1) {
			if (w == NULL)break;
			if (visited[w->vertex] == FALSE) {
				temp = (linkedPointer)malloc(sizeof(Linked));
				temp->data = w->vertex;
				temp->link = NULL;
				if (Q == NULL) {
					Q = temp;
					rear = Q;
				}
				else {
					rear->link = temp;
					rear = temp;
				}
				visited[w->vertex] = TRUE;
				rtemp = (resultPointer)malloc(sizeof(Result));
				rtemp->start = prevertex;
				rtemp->finish = w->vertex;
				rtemp->link = NULL;
				if(result == NULL){
					result = rtemp;
				}
				else{
					rtemp->link = result;
					result = rtemp;
				}
				if (w->vertex == target)break;
			}
			if (w->link == NULL) {
				break;
			}
			w = w->link;
		}
		if (w->vertex == target)break;
	}
	/*
	key = stack->data;
	stack = stack->link;
	temp = (linkedPointer)malloc(sizeof(linked));
	temp->data = stack->data;
	temp->link = NULL;
	Qu = temp;
	for(;stack;){
		w = adjlist[stack->data]->link;
		while(1){
			if(w->vertex == key){
				key = stack->data;
				temp = (linkedPointer)malloc(sizeof(linked));
				temp->data = stack->data;
				temp->link = Q;
				Q = temp;
				break;
			}
			if(w->link == NULL){
				break;
			}
		}
		del = stack;
		stack = stack->link;
		free(del);
	}
	*/
	bfsflag = 1;
	finishflag = 1;
}

void Makeadjlist(int size) {
	int num, i, j;
	nodePointer temp;
	nodePointer next;
	adjlist = (nodePointer*)malloc(size * sizeof(nodePointer));

	for (i = 0; i < size; i++) {
		adjlist[i] = (nodePointer)malloc(sizeof(Node));
	}
	num = 0;
	for (i = 0; i < Height; i++) {
		for (j = 0; j < Width; j++) {
			next = adjlist[num];
			next->link = NULL;
			if (i > 0) {
				if (wall[i - 1][j] == 0 || wall[i - 1][j] == 1) {
					temp = (nodePointer)malloc(sizeof(Node));
					temp->vertex = num - Width;
					temp->link = NULL;
					next->link = temp;
					next = temp;
				}
			}
			if (j > 0) {
				if (wall[i][j - 1] == 0 || wall[i][j - 1] == 2) {
					temp = (nodePointer)malloc(sizeof(Node));
					temp->vertex = num - 1;
					temp->link = NULL;
					next->link = temp;
					next = temp;
				}
			}
			if (wall[i][j] == 0) {
				temp = (nodePointer)malloc(sizeof(Node));
				temp->vertex = num + Width;
				temp->link = NULL;
				next->link = temp;
				next = temp;
				temp = (nodePointer)malloc(sizeof(Node));
				temp->vertex = num + 1;
				temp->link = NULL;
				next->link = temp;
				next = temp;
			}
			else if (wall[i][j] == 1) {
				temp = (nodePointer)malloc(sizeof(Node));
				temp->vertex = num + Width;
				temp->link = NULL;
				next->link = temp;
				next = temp;
			}
			else if (wall[i][j] == 2) {
				temp = (nodePointer)malloc(sizeof(Node));
				temp->vertex = num + 1;
				temp->link = NULL;
				next->link = temp;
				next = temp;
			}
			num++;
		}
	}
}
bool readFile(const char* filename){
	FILE *fp;
	char c, room, wl;
	int i;
	fp = fopen(filename, "r");
	while (1) {
		fscanf(fp, "%c", &c);
		if (c == '\n')break;
		Width++;
	}
	Height++;
	Width /= 2;
	while (1) {
		fscanf(fp, "%c", &c);
		wall = (int**)realloc(wall, Height * sizeof(int*));
		wall[Height - 1] = (int*)calloc(Width, sizeof(int));
		for (i = 0; i < Width; i++) {
			fscanf(fp, "%c%c", &room, &wl);
			if (wl == '|') {
				wall[Height - 1][i] = 1;
			}
			else {
				wall[Height - 1][i] = 0;
			}
		}
		fscanf(fp, "%c", &c);
		fscanf(fp, "%c", &c);
		for (i = 0; i < Width; i++) {
			fscanf(fp, "%c%c", &room, &wl);
			if (room == '-') {
				wall[Height - 1][i] = wall[Height - 1][i] + 2;
			}
			else {
				wall[Height - 1][i] = wall[Height - 1][i] + 0;
			}
		}

		if (fscanf(fp, "%c", &c) == EOF)break;
		Height++;
	}
	fclose(fp);
	Makeadjlist(Height*Width);
	return true; //edit after finish this function
}

/******************************************************************
* function	: bool FreeMemory()
*
* remark	: Save user data to a file
*******************************************************************/
void freeMemory(){
	int i;
	resultPointer del;
	for(i =0; i < Height; i++){
		free(wall[i]);
	}
	free(visited);
	for(; result; ){
		del = result;
		result = result->link;
		free(result);
	}
	Width = 0;
	Height = 0;
	finishflag = 0;
	dfsflag = 0;
	bfsflag = 0;
}

/**************************************************************
* function	: bool writeFile(const char* filename)
*
* argument	: const char* filename - filename to be written
* return	: true if success, otherwise false
* remark	: Save user data to a file
****************************************************************/
bool writeFile(const char* filename){
	//start of the user code
	bool flag;
	flag = 0;

	return flag;
	//end of usercode
}

/************************************************************************
* fucntion	: void drawMain(CDC* pDC)
*
* argument	: CDC* pDC - device context object pointer
* remark	: Main drawing function. Called by CMFC_MainView::OnDraw()
*************************************************************************/
void drawMain(CDC *pDC){
	//if direct drawing is defined
#if defined(GRAPHICS_DIRECT)
	drawDirect(pDC);
	//if buffered drawing is defined
#elif defined(GRAPHICS_BUFFERED)
	drawBuffered();
#endif
}

/************************************************************************
* function	: static void drawDirect(CDC *pDC
*
* argument	: CDC* pDC - device context object pointer
* remark	: Direct drawing routines here.
*************************************************************************/
static void drawDirect(CDC *pDC){
	//begin of user code
	//Nothing to write currently.
	//end of user code
}

/***********************************************************************
* function	: static void drawBuffered()
*
* argument	: CDC* pDC -0 device object pointer
* remark	: Buffered drawing routines here.
************************************************************************/
static void drawBuffered(){
	
	int i, j, row=0,col=0;
	double temx, temy;
	
	setWindow(0, 0, 100, 100, 1);
	DrawBox_I(0, 0, 100, 100, 2, RGB(10,10,10));
	temx = 100 / (double)Width;
	temy = 100 / (double)Height;

	for(row = 0; row < Height; row++){
		for(col = 0; col < Width; col++){
			if (wall[row][col] == 1) {
				DrawLine_I(temx*(col + 1), temy*(row), temx*(col + 1), temy*(row + 1), 1, RGB(10, 10, 10));
			}
			else if (wall[row][col] == 2) {
				DrawLine_I(temx*(col), temy*(row + 1), temx*(col + 1), temy*(row + 1), 1, RGB(10, 10, 10));
			}
			else if (wall[row][col] == 3){
				DrawLine_I(temx*(col + 1), temy*(row), temx*(col + 1), temy*(row + 1), 1, RGB(10, 10, 10));
				DrawLine_I(temx*(col), temy*(row + 1), temx*(col + 1), temy*(row + 1), 1, RGB(10, 10, 10));
			}
		}
	}
	if(finishflag == 1){
		for(; result; result = result->link){
			if(result->start == result->finish+Width){
				DrawSolidBox_I(temx*(result->start%Width)+temx/3, temy*(result->start/Width)+2*temy/3, temx*(result->start%Width)+2*temx/3, temy*(result->finish/Width)+temy/3, 1, RGB(0, 255, 0), RGB(0 , 255, 0));
			}
			else if(result->start == result->finish-Width){
				DrawSolidBox_I(temx*(result->start%Width)+temx/3, temy*(result->start/Width)+temy/3, temx*(result->start%Width)+2*temx/3, temy*(result->finish/Width)+2*temy/3, 1, RGB(0, 255, 0), RGB(0 , 255, 0));
			}
			else if(result->start == result->finish-1){
				DrawSolidBox_I(temx*(result->start%Width)+temx/3, temy*(result->start/Width)+temy/3, temx*(result->finish%Width)+2*temx/3, temy*(result->finish/Width)+2*temy/3, 1, RGB(0, 255, 0), RGB(0 , 255, 0));
			}
			else if(result->start == result->finish+1){
				DrawSolidBox_I(temx*(result->start%Width)+2*temx/3, temy*(result->start/Width)+temy/3, temx*(result->finish%Width)+temx/3, temy*(result->finish/Width)+2*temy/3, 1, RGB(0, 255, 0), RGB(0 , 255, 0));
			}
		}
		if(dfsflag == 1){
			DrawSolidBox_I(temx*(S->data%Width)+temx/3, temy*(S->data/Width)+temy/3, temx*(S->data%Width)+2*temx/3, temy*(S->data/Width)+2*temy/3, 1, RGB(0, 0, 255), RGB(0 , 0, 255));
			for(; S->link; S = S->link){
				if(S->data == S->link->data+Width){//아래로 내려온 경우
					DrawSolidBox_I(temx*(S->data%Width)+temx/3, temy*(S->data/Width)+temy/3, temx*(S->data%Width)+2*temx/3, temy*(S->link->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				else if(S->data == S->link->data-Width){//위로 올가가는 경우
					DrawSolidBox_I(temx*(S->data%Width)+temx/3, temy*(S->data/Width)+2*temy/3, temx*(S->data%Width)+2*temx/3, temy*(S->link->data/Width)+temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				else if(S->data == S->link->data-1){//왼쪽으로 가는 경우
					DrawSolidBox_I(temx*(S->data%Width)+2*temx/3, temy*(S->data/Width)+temy/3, temx*(S->link->data%Width)+temx/3, temy*(S->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				else if(S->data == S->link->data+1){//오른쪽으로 가는 경우
					DrawSolidBox_I(temx*(S->data%Width)+temx/3, temy*(S->data/Width)+temy/3, temx*(S->link->data%Width)+2*temx/3, temy*(S->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				DrawSolidBox_I(temx*(S->data%Width)+temx/3, temy*(S->data/Width)+temy/3, temx*(S->data%Width)+2*temx/3, temy*(S->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
			}
			DrawSolidBox_I(temx*(S->data%Width)+temx/3, temy*(S->data/Width)+temy/3, temx*(S->data%Width)+2*temx/3, temy*(S->data/Width)+2*temy/3, 1, RGB(0, 0, 255), RGB(0 , 0, 255));
		}
		if(bfsflag == 1){
			/*
			DrawSolidBox_I(temx*(Qu->data%Width)+temx/3, temy*(Qu->data/Width)+temy/3, temx*(Qu->data%Width)+2*temx/3, temy*(Qu->data/Width)+2*temy/3, 1, RGB(0, 0, 255), RGB(0 , 0, 255));
			for(; Qu->link; Qu = Qu->link){
				if(S->data == S->link->data+Width){//아래로 내려온 경우
					DrawSolidBox_I(temx*(Qu->data%Width)+temx/3, temy*(Qu->data/Width)+temy/3, temx*(Qu->data%Width)+2*temx/3, temy*(Qu->link->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				else if(Qu->data == Qu->link->data-Width){//위로 올가가는 경우
					DrawSolidBox_I(temx*(Qu->data%Width)+temx/3, temy*(Qu->data/Width)+2*temy/3, temx*(Qu->data%Width)+2*temx/3, temy*(Qu->link->data/Width)+temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				else if(Qu->data == Qu->link->data-1){//왼쪽으로 가는 경우
					DrawSolidBox_I(temx*(Qu->data%Width)+2*temx/3, temy*(Qu->data/Width)+temy/3, temx*(Qu->link->data%Width)+temx/3, temy*(Qu->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				else if(Qu->data == Qu->link->data+1){//오른쪽으로 가는 경우
					DrawSolidBox_I(temx*(Qu->data%Width)+temx/3, temy*(Qu->data/Width)+temy/3, temx*(Qu->link->data%Width)+2*temx/3, temy*(Qu->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
				}
				DrawSolidBox_I(temx*(Qu->data%Width)+temx/3, temy*(Qu->data/Width)+temy/3, temx*(Qu->data%Width)+2*temx/3, temy*(Qu->data/Width)+2*temy/3, 1, RGB(255, 0, 0), RGB(255 , 0, 0));
			}
			DrawSolidBox_I(temx*(Qu->data%Width)+temx/3, temy*(Qu->data/Width)+temy/3, temx*(Qu->data%Width)+2*temx/3, temy*(Qu->data/Width)+2*temy/3, 1, RGB(0, 0, 255), RGB(0 , 0, 255));
		*/
		}
	}
}