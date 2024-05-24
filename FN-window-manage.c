#include "FN-window.h"
#include "stdio.h"
#include "stdlib.h"
    static XWindowChanges values;
    static unsigned int valueMask;
  
void configureMenu(FN* global,XEvent* event){
    valueMask=(CWHeight);
    values.height=event->xconfigure.height;
    XConfigureWindow(global->dpy,global->menu.win,valueMask,&values);
    valueMask=(CWY);
    values.y=values.height-MENU_BLOCK_HEIGHT;
    XConfigureWindow(global->dpy,global->menu.drawButton,valueMask,&values);
    valueMask=(CWY | CWX);
    //XUnmapWindow(global->dpy,global->menu.numberInput);
    values.x=event->xconfigure.width/2-MENU_BLOCK_WIDTH/2;
    values.y=event->xconfigure.height/2-MENU_BLOCK_HEIGHT/2;
    XConfigureWindow(global->dpy,global->menu.numberInput,valueMask,&values);
  //  XDrawLine(global->dpy,global->menu.win,global->menu.gc,199,0,199,values.height);

}

void configureFigure(FN* global,XEvent* event){
    valueMask=(CWHeight | CWWidth);
    values.height=MIN(event->xconfigure.height,event->xconfigure.width-MENU_BLOCK_WIDTH);
    values.width=MIN(event->xconfigure.height,event->xconfigure.width-MENU_BLOCK_WIDTH);
    XConfigureWindow(global->dpy,global->figure.win,valueMask,&values);

}

int findWindow(Window win,Window* list,int listsize){
   for(int i=0;i<listsize;i++){
        if(win==list[i]){
        return i;
        }
   }
   return -1;
}
void buttonControl(FN* global,XEvent* event,FNcontrols* controls){
  //if(!controls->inputIsOpened){
  if (!controls->listMenuIsOpened) { 
    if(event->xbutton.window==global->menu.field){
      for(int i=0;i<MENU_LIST_AMMOUNT;i++){
        XMapWindow(global->dpy,global->menu.list[i]);
      }
      controls->listMenuIsOpened=1;
    } else if(event->xbutton.window==global->menu.drawButton){
      fprintf(stderr,"draw the option:%d with n:%d\n",controls->numberOpt,controls->numberN);
      if(controls->numberOpt!=-1 && controls->numberN>0){
        
        assembleFigure(global,controls);
      }
    }
  }
  else {
    if (event->xbutton.window==global->menu.field){
      for(int i=0;i<MENU_LIST_AMMOUNT;i++){
        XUnmapWindow(global->dpy,global->menu.list[i]);
      }
      controls->listMenuIsOpened=0;
    } else {
      controls->numberOpt=findWindow(event->xbutton.window,global->menu.list,MENU_LIST_AMMOUNT);
      if(controls->numberOpt!=-1){
        XMapWindow(global->dpy,global->menu.numberInput);
        controls->inputIsOpened=1;
        fprintf(stderr,"choosed option: %d\n",controls->numberOpt);
      }
    }
  }
  //}else {
    if(event->xbutton.window!=global->menu.numberInput && findWindow(event->xbutton.window,global->menu.list,MENU_LIST_AMMOUNT)==-1){
      
      XUnmapWindow(global->dpy,global->menu.numberInput);
      controls->inputIsOpened=0;
      controls->numericKeyPressedinRow=0;
      controls->tempNumber=0;
      controls->numberN=-1;
    //}
  }

}

int keyControl(FN* global,XEvent* event,FNcontrols* controls){
  const char* c;
  char buf[10];
  if(event->xkey.keycode>=FN_XK_1 && event->xkey.keycode<=FN_XK_9){
if(controls->numericKeyPressedinRow<3){
   // fprintf(stderr,"num:%d %d",controls->tempNumber,controls->numericKeyPressedinRow);
   controls->tempNumber=keycodeToInt(controls->tempNumber,event->xkey.keycode,controls->numericKeyPressedinRow);
   sprintf(buf,"%d",controls->tempNumber);
   const char* c=buf;
   controls->numericKeyPressedinRow++;
   XDrawString(global->dpy,global->menu.numberInput,global->menu.gc[1],55,30,c,controls->numericKeyPressedinRow);
   }
  } else if (event->xkey.keycode==FN_XK_ENTER){
   // fprintf(stderr,"num:%d %d\n",controls->tempNumber,controls->numericKeyPressedinRow);
    if(controls->numericKeyPressedinRow){
  controls->numberN=controls->tempNumber;
    } else {
  controls->numberN=-1;
    }
    controls->numericKeyPressedinRow=0;

    controls->tempNumber=0;
    XUnmapWindow(global->dpy,global->menu.numberInput);
    controls->inputIsOpened=0;
    for(int i=0;i<MENU_LIST_AMMOUNT;i++){
      XUnmapWindow(global->dpy,global->menu.list[i]);
    }
    controls->listMenuIsOpened=0;
    
  } else if (event->xkey.keycode==FN_XK_ESC){
    
    return 0;
  }
  return 1;
}

void drawPlot(FN* global,cps* params){
  XFillRectangle(global->dpy,global->figure.win,global->root.gc,0,0,params->d,params->d);
  for(int i=0;i<params->pointsCount;i++){
  XDrawArc(global->dpy,global->figure.win,global->menu.gc[1],params->points[i].x-params->radius,params->points[i].y-params->radius,params->diameter,params->diameter,0,360*64);
  }
  XDrawPoints(global->dpy,global->figure.win,global->menu.gc[1],params->points,params->pointsCount,CoordModeOrigin);
}

void assembleFigure(FN* global,FNcontrols* controls){
  XWindowAttributes xatr;
  cps params;
  XGetWindowAttributes(global->dpy,global->figure.win,&xatr);
  params.d=xatr.height;
  if(params.d/controls->numberN<12){
  fprintf(stderr,"WARNING : n <%d> number is overcapping the density of the sceen,calculate optimal",controls->numberN);
  controls->numberN=params.d/12;
  }
  params.diameter=10;
  params.radius=params.diameter/2;
  params.goffset=params.d/(controls->numberN+1);
  params.offs=(cot*)malloc(sizeof(cot)*(controls->numberOpt/2+1));
  
  switch(controls->numberOpt){
    case 0:
    params.pointsCount=triangularFormula(controls->numberN);
    assembleTriangularPlot(&params,controls->numberN);
 
    break;
    case 1:
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assembleSquarePlot(&params,controls->numberN);
 
    break;
    case 2:
    params.goffset=params.goffset*8/10;
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assemblePentagonalPlot(&params,controls->numberN);
  
    break;
    case 3:
    params.goffset=params.goffset*8/10;
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assembleHexagonalPlot(&params,controls->numberN);
    
    break;
    case 4:
    params.goffset=params.goffset*6/10;
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assembleHeptagonalPlot(&params,controls->numberN);
    break;
    case 5:
    params.goffset=params.goffset*6/10;
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assembleOctagonalPlot(&params,controls->numberN);
    break;
    case 6:
    params.goffset=params.goffset*6/10;
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assembleNonagonalPlot(&params,controls->numberN);
    break;
    case 7:
    params.goffset=params.goffset*6/10;
    params.pointsCount=uFormula(controls->numberN,controls->numberOpt);
    assembleDecagonalPlot(&params,controls->numberN);
    break;
    }
    drawPlot(global,&params);
    free(params.offs);
    free(params.points);
}
