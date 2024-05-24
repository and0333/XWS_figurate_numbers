#include "stdio.h"
#include "FN-window.h"
#include "FN-calcs.h"


void dispatch(FN*);


int main(){
    FN global;
    initDpy(&global);
    initGraphics(&global);
    initScr(&global);
    dispatch(&global);
    
    freeAll(&global);

    return 0;

}




void dispatch(FN* global){
    XEvent event;
    FNcontrols controls;
    controls.numberOpt=-1;
    controls.numberN=-1;
    controls.tempNumber=0;
    controls.listMenuIsOpened=0;
    controls.inputIsOpened=0;
    controls.numericKeyPressedinRow=0;
    controls.status=1;
    while (controls.status){
     XNextEvent(global->dpy, &event);
     switch (event.type) {
        case ConfigureNotify:
        configureMenu(global,&event);
        configureFigure(global,&event);
        break;
        case Expose:
        break;
        case ButtonPress:
        buttonControl(global,&event,&controls);
        break;
        case KeyPress:
        controls.status=keyControl(global,&event,&controls);
        break;
        default:
        break;
     }
    }
}