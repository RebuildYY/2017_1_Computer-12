#include <stdlib.h>
#include "..\ExternDoc.h"
#include "..\UI\Zoom.h"
#include "..\UI\MsgView.h"
#include "..\Graphics\DrawFunc.h"
#include "..\Example\Example.h"

#define ERROR_NUMBER -1

int **wall;
int Width =0, Height=0;
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
void DFS(){

}
void BFS(){

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
	return true; //edit after finish this function
}

/******************************************************************
* function	: bool FreeMemory()
*
* remark	: Save user data to a file
*******************************************************************/
void freeMemory(){
	int i;
	for(i =0; i < Height; i++){
		free(wall[i]);
	}
	Width = 0;
	Height = 0;
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
}