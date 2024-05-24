#include "FN-window.h"
#include "./materials/colours.h"
void initDpy(FN* global){
 global->dpy = XOpenDisplay(NULL);
}

void initScr(FN* global){
    int scr = DefaultScreen(global->dpy);
    int depth = DefaultDepth(global->dpy, scr);
    global->height=DisplayHeight(global->dpy, scr);
    global->width=DisplayWidth(global->dpy, scr);
    XSetWindowAttributes attr;
    XSizeHints hint;
    Pixmap pix;
    long mask;
    /*--------------------------global------------------------------*/
    hint.min_width=ROOT_MIN_WIDTH;
    hint.min_height=ROOT_MIN_HEIGHT;
    attr.override_redirect = False;
    attr.background_pixel = WhitePixel(global->dpy, scr);
    
    global->root.win =
      XCreateWindow(global->dpy, DefaultRootWindow(global->dpy), 0, 0,
                    ROOT_MIN_WIDTH,ROOT_MIN_HEIGHT, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel), &attr);
    
    hint.flags = (PMinSize);
    XSetNormalHints(global->dpy, global->root.win, &hint);

    mask=(ExposureMask | ButtonPressMask | KeyPressMask | StructureNotifyMask);
    XSelectInput(global->dpy,global->root.win,mask);
    XMapWindow(global->dpy,global->root.win);
    /*------------------------menu-----------------------------*/
    /**------------------------mainblock----------------------------**/
    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),MENU_BLOCK_WIDTH,1,depth);
    XDrawLine(global->dpy,pix,global->menu.gc[0],0,0,MENU_BLOCK_WIDTH-2,0);
    XDrawPoint(global->dpy,pix,global->menu.gc[1],MENU_BLOCK_WIDTH-1,0);
    attr.background_pixmap=pix;
    global->menu.win=
          XCreateWindow(global->dpy, global->root.win , 0, 0,
                    MENU_BLOCK_WIDTH,ROOT_MIN_HEIGHT, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);
    XMapWindow(global->dpy,global->menu.win);
    /*------------------------figure----------------------------*/
    attr.background_pixel=0xffffff;
    attr.bit_gravity=CenterGravity;
    attr.backing_store=WhenMapped;
    global->figure.win=
            XCreateWindow(global->dpy, global->root.win , MENU_BLOCK_WIDTH,0,
                    ROOT_MIN_WIDTH-MENU_BLOCK_WIDTH,ROOT_MIN_HEIGHT, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixel | CWBitGravity | CWBackingStore), &attr);
    XMapWindow(global->dpy,global->figure.win);
    /**------------------------upperfield----------------------------**/
    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT,depth);
    XFillRectangle(global->dpy,pix,global->menu.gc[0],0,0,MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT);
    XDrawLine(global->dpy,pix,global->menu.gc[1],0,MENU_BLOCK_HEIGHT-1,MENU_BLOCK_WIDTH-1,MENU_BLOCK_HEIGHT-1);
    XDrawLine(global->dpy,pix,global->menu.gc[1],MENU_BLOCK_WIDTH-1,0,MENU_BLOCK_WIDTH-1,MENU_BLOCK_HEIGHT-1);
    XDrawString(global->dpy,pix,global->menu.gc[1],10,10,"choose type",11);
    attr.background_pixmap=pix;
    global->menu.field=
            XCreateWindow(global->dpy, global->menu.win , 0, 0,
                    MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);
    mask=(ButtonPressMask);
    XSelectInput(global->dpy,global->menu.field,mask);
    XMapWindow(global->dpy,global->menu.field);
    /**------------------------listfieldsarray----------------------------**/
    const char* textFields[MENU_LIST_AMMOUNT]={"triangular","square","pentagonal","hexagonal","heptagonal","octagonal","nonagonal","decagonal"};
    
    for(int i=0;i<MENU_LIST_AMMOUNT;i++){
        pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT,depth);
        XFillRectangle(global->dpy,pix,global->menu.gc[1],0,0,MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT);
        XDrawString(global->dpy,pix,global->menu.gc[0],10,10,textFields[i],textSize(textFields[i]));
        attr.background_pixmap=pix;
        global->menu.list[i]=
            XCreateWindow(global->dpy, global->menu.win , 0, MENU_BLOCK_HEIGHT+MENU_BLOCK_HEIGHT*i,
                    MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT, 0,
                    depth, InputOutput, 0,
                    (CWBackPixmap), &attr);
    mask=(ButtonPressMask);
    XSelectInput(global->dpy,global->menu.list[i],mask);

    }
    /**------------------------inputfield----------------------------**/
    
    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT,depth);
    XFillRectangle(global->dpy,pix,global->menu.gc[0],0,0,MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT);
    XFillRectangle(global->dpy,pix,global->root.gc,MENU_BLOCK_WIDTH/4,MENU_BLOCK_HEIGHT/4,MENU_BLOCK_WIDTH-MENU_BLOCK_WIDTH/4-MENU_BLOCK_HEIGHT/4,MENU_BLOCK_HEIGHT-2*MENU_BLOCK_HEIGHT/4+2);
    XDrawRectangle(global->dpy,pix,global->menu.gc[1],0,0,MENU_BLOCK_WIDTH-1,MENU_BLOCK_HEIGHT-1);
    XDrawRectangle(global->dpy,pix,global->menu.gc[1],MENU_BLOCK_WIDTH/4,MENU_BLOCK_HEIGHT/4,MENU_BLOCK_WIDTH-MENU_BLOCK_WIDTH/4-MENU_BLOCK_HEIGHT/4-1,MENU_BLOCK_HEIGHT-2*MENU_BLOCK_HEIGHT/4+2-1);
    XDrawString(global->dpy,pix,global->menu.gc[1],30,30,"n:",2);
    attr.background_pixmap=pix;
    global->menu.numberInput=
            XCreateWindow(global->dpy, global->root.win , ROOT_MIN_WIDTH/2-MENU_BLOCK_WIDTH/2,ROOT_MIN_HEIGHT/2-MENU_BLOCK_HEIGHT/2,
                    MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);
    mask=(KeyPressMask | ButtonPressMask);
    XSelectInput(global->dpy,global->menu.numberInput,mask);
   
    /**------------------------drawfield----------------------------**/
    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT,depth);
    XFillRectangle(global->dpy,pix,global->menu.gc[0],0,0,MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT);
    XDrawLine(global->dpy,pix,global->menu.gc[1],0,0,MENU_BLOCK_WIDTH-1,0);
    XDrawLine(global->dpy,pix,global->menu.gc[1],MENU_BLOCK_WIDTH-1,0,MENU_BLOCK_WIDTH-1,MENU_BLOCK_HEIGHT-1);
    XDrawString(global->dpy,pix,global->menu.gc[1],10,10,"draw",4);
    attr.background_pixmap=pix;
    global->menu.drawButton=
            XCreateWindow(global->dpy, global->menu.win , 0,ROOT_MIN_HEIGHT-MENU_BLOCK_HEIGHT,
                    MENU_BLOCK_WIDTH,MENU_BLOCK_HEIGHT, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);
    mask=(ButtonPressMask);
    XSelectInput(global->dpy,global->menu.drawButton,mask);
    XMapWindow(global->dpy,global->menu.drawButton);

}

void initGraphics(FN* global){
    
    XFontStruct *fn; /* Font parameters structure */
    char *fontname = "9x15";
    /*--------------------------global------------------------------*/
    global->root.gc=XCreateGC(global->dpy,DefaultRootWindow(global->dpy),0,0);
    XSetForeground(global->dpy, global->root.gc, 0xFFFFFF);
    /*------------------------menu-----------------------------*/
   

    global->menu.gc[0]=XDefaultGC(global->dpy,0);
    global->menu.gc[1]=XCreateGC(global->dpy,DefaultRootWindow(global->dpy),0,0);
    XSetForeground(global->dpy, global->menu.gc[0], MENU_BACKGROUND);
    XSetForeground(global->dpy, global->menu.gc[1], MENU_BORDER);
    if ((fn = XLoadQueryFont(global->dpy, fontname)) != NULL){
        XSetFont(global->dpy,global->menu.gc[0], fn->fid);
        XSetFont(global->dpy,global->menu.gc[1], fn->fid);
    }

        XFreeFont(global->dpy,fn);
}
void freeAll(FN* global){
  XFreeGC(global->dpy,global->root.gc);
  XFreeGC(global->dpy,global->menu.gc[1]);
  XCloseDisplay(global->dpy);
}