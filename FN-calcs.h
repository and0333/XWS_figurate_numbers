#ifndef FN_calcs_H_
#define FN_calcs_H_
#include "math.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "stdlib.h"
#define FN_XK_1 10
#define FN_XK_9 19
#define FN_XK_ENTER 36
#define FN_XK_ESC 9
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

struct calcOffset{
    int off1;
    int off2;
};
typedef struct calcOffset cot;
struct calcParams {
    int d;
    cot* offs;
    int goffset;
    int diameter;
    int radius;
    int pointsCount;
    XPoint* points;
};
typedef struct calcParams cps;

unsigned int textSize(const char* text);
int keycodeToInt(int lastnumber,int keycode,int);
unsigned int triangularFormula(int n);
void assembleTriangularPlot(cps* params,int n);
unsigned int uFormula(int n,int option);
void assembleSquarePlot(cps* params,int n);
void assemblePentagonalPlot(cps* params,int n);
void assembleHexagonalPlot(cps* params,int n);
void assembleHeptagonalPlot(cps* params,int n);
void assembleOctagonalPlot(cps* params,int n);
void assembleNonagonalPlot(cps* params,int n);
void assembleDecagonalPlot(cps* params,int n);
#endif //FN_calcs_H_ end definition