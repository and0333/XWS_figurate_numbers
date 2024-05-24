#ifndef FN_window_H_ 
#define FN_window_H_
#pragma once
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "FN-calcs.h"
/*struct FNlistwins {
    Window field;
    const char* text;
    int size;
    Pixmap pix;
};*/
#define MENU_LIST_AMMOUNT 8
/*typedef struct FNlistwins FNlist;*/

struct FNmenuwin {
    Window win;
    Window field;
    Window drawButton;
    //FNlist list[MENU_LIST_AMMOUNT];
    Window list[MENU_LIST_AMMOUNT];
    Window numberInput;
    GC gc[2];
};
#define MENU_BLOCK_WIDTH 200
#define MENU_BLOCK_HEIGHT 50
typedef struct FNmenuwin FNmenu;


struct FNrootwin {
    Window win;
    GC gc;
};
#define ROOT_MIN_WIDTH 800
#define ROOT_MIN_HEIGHT 600
typedef struct FNrootwin FNroot;

struct FNfigurewin{
    Window win;
    GC gc;
};
typedef struct FNfigurewin FNfigure;

struct FNglobal {
    Display *dpy;
    FNroot root;
    FNmenu menu;
    FNfigure figure;
    unsigned int width;
    unsigned int height;
};
typedef struct FNglobal FN;

struct FNcontrols {
    int numberOpt;
    int numberN;
    int tempNumber;
    unsigned int listMenuIsOpened;
    unsigned int inputIsOpened;
    unsigned int numericKeyPressedinRow;
    int status;
};
typedef struct FNcontrols FNcontrols;


void initDpy(FN* global);
void initScr(FN* global);
void initGraphics(FN* global);
void configureMenu(FN* global,XEvent* event);
void firstStart(FN*,unsigned char*);
void buttonControl(FN* global,XEvent* event,FNcontrols*);
int keyControl(FN* global,XEvent* event,FNcontrols*);
void configureFigure(FN* global,XEvent* event);
void assembleFigure(FN* global,FNcontrols* controls);
void drawPlot(FN* global,cps* params);
void triangularGraph(FN* global,int n,unsigned int pointsCount);
void freeGraphics(FN* global);
void freeAll(FN* global);
#endif //FN_window_H_ end definition