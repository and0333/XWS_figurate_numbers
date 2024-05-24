#include "FN-calcs.h"


unsigned int textSize(const char* text){
    unsigned int i=0;
    for(;*text;i++,text++);
    return i;
}
int keycodeToInt(int lastnumber,int keycode,int p){
   return lastnumber*10+((keycode+1)%10);
}

unsigned int triangularFormula(int n){
    return (pow(n,2)+n)/2;
}
void assembleTriangularPlot(cps* params,int n){
  params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset;
  params->offs[0].off2=params->d-params->goffset;
  int r=0;
  for(int i=0,pointsInRow=n;i<n;i++,pointsInRow--,params->offs[0].off2-=params->goffset){
    //points[r].y=yoffset;
    params->offs[0].off1=params->goffset+params->goffset/2*i;
    for(int j=0;j<pointsInRow;j++,params->offs->off1+=params->goffset){
      params->points[r].x=params->offs->off1;
      params->points[r].y=params->offs[0].off2;
      r++;
    }
  }
}
unsigned int uFormula(int n,int option){
    return  ((option+1)*pow(n,2)-(option-1)*n)/2;
}
void assembleSquarePlot(cps* params,int n){
   params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset;
  params->offs[0].off2=params->d-params->goffset;
  int r=0;
  for(int i=0,pointsInRow=n;i<n;i++,pointsInRow--,params->offs[0].off2-=params->goffset){
    params->offs[0].off1=params->goffset;
    for(int j=0;j<n;j++,params->offs[0].off1+=params->goffset){
      params->points[r].x=params->offs[0].off1;
      params->points[r].y=params->offs[0].off2;
      r++;
    }
  }
}
void assemblePentagonalPlot(cps* params,int n){
  params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset*2/3;
  params->offs[0].off2=params->goffset/3;
  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=1;
  params->points[0].x=((params->d-(params->offs[0].off1*(n-1)*2)-params->radius*2)/2)+params->offs[0].off1*(n-1);
  params->points[0].y=params->goffset;
  short po=1;
  for(int j=1;j<n;po=3*j+1,j++){
  params->points[r].x=params->points[r-po].x+params->offs[0].off1;
  params->points[r].y=params->points[r-po].y+params->offs[0].off2;
  r++;
  for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x-params->offs[0].off2;
    params->points[r].y=params->points[r-1].y+params->offs[0].off1;
    r++;
  }
    for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x-params->offs[0].off1;
    params->points[r].y=params->points[r-1].y;
    r++;
  }
    for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x-params->offs[0].off2;
    params->points[r].y=params->points[r-1].y-params->offs[0].off1;
    r++;
  }
  }
}
void assembleHexagonalPlot(cps* params,int n){
   params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset/3;
  params->offs[0].off2=params->goffset/2;
  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=1;
  params->points[0].x=(params->d-(params->offs[0].off1*2+params->offs[0].off2)*(n-1)-params->radius*2)/2+(params->offs[0].off1*2+params->offs[0].off2)*(n-1);
  params->points[0].y=(params->d-params->offs[0].off2*2*(n-1)-params->radius*2)/2+params->offs[0].off2*(n-1);//offset;
  short po=1;
  for(int j=1;j<n;po=4*j+1,j++){
  params->points[r].x=params->points[r-po].x-params->offs[0].off1;
  params->points[r].y=params->points[r-po].y-params->offs[0].off2;
  r++;
    for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x-params->offs[0].off2;
    params->points[r].y=params->points[r-1].y;
    r++;
  }
    for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x-params->offs[0].off1;
    params->points[r].y=params->points[r-1].y+params->offs[0].off2;
    r++;
  }
      for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x+params->offs[0].off1;
    params->points[r].y=params->points[r-1].y+params->offs[0].off2;
    r++;
  }
    for(int i=0;i<j;i++){
    params->points[r].x=params->points[r-1].x+params->offs[0].off2;
    params->points[r].y=params->points[r-1].y;
    r++;
  }


  }
}
void assembleHeptagonalPlot(cps* params,int n){
   params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset*2/3;
  params->offs[0].off2=params->goffset/3;
  params->offs[1].off1=params->goffset/2;

  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=1;
  params->points[0].x=((params->d-((params->offs[0].off1+params->offs[0].off2)*(n-1)*2)-params->radius*2)/2)+(params->offs[0].off1+params->offs[0].off2)*(n-1);
  params->points[0].y=(params->d-(params->offs[1].off1+params->goffset)*(n-1))/2;
  short po=1;
  for(int j=1;j<n;po=5*j+1,j++){
    params->points[r].x=params->points[r-po].x+params->offs[0].off1;
    params->points[r].y=params->points[r-po].y+params->offs[0].off2;
    r++;
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off2;
        params->points[r].y=params->points[r-1].y+params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[1].off1;
        params->points[r].y=params->points[r-1].y+params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->goffset;
        params->points[r].y=params->points[r-1].y;
        r++;

    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[1].off1;
        params->points[r].y=params->points[r-1].y-params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off2;
        params->points[r].y=params->points[r-1].y-params->offs[0].off1;
        r++;
    }
  }
}

void assembleOctagonalPlot(cps* params,int n){
   params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset*2/3;
  params->offs[0].off2=params->goffset/3;

  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=1;
  params->points[0].y=(params->d-(params->offs[0].off1+params->offs[0].off2)*2*(n-1)-params->radius*2)/2;
  params->points[0].x=params->points[0].y+(params->offs[0].off1+params->offs[0].off2)*(n-1);
  short po=1;
  for(int j=1;j<n;po=6*j+1,j++){
    params->points[r].x=params->points[r-po].x+params->offs[0].off1;
    params->points[r].y=params->points[r-po].y+params->offs[0].off2;
    r++;
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off2;
        params->points[r].y=params->points[r-1].y+params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off2;
        params->points[r].y=params->points[r-1].y+params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off1;
        params->points[r].y=params->points[r-1].y+params->offs[0].off2;
        r++;

    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off1;
        params->points[r].y=params->points[r-1].y-params->offs[0].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off2;
        params->points[r].y=params->points[r-1].y-params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off2;
        params->points[r].y=params->points[r-1].y-params->offs[0].off1;
        r++;
    }
  }
}
void assembleNonagonalPlot(cps* params,int n){
   params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset*2/6;
  params->offs[0].off2=params->goffset/6;
  params->offs[1].off1=params->goffset*4/6;
  params->offs[1].off2=params->goffset*5/6;
  params->offs[2].off1=params->goffset*3/6;
  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=1;
  params->points[0].y=(params->d-(params->offs[0].off2+params->offs[1].off1+params->offs[1].off2+params->offs[0].off1)*(n-1)-params->radius*2)/2;
  params->points[0].x=(params->d-(params->offs[1].off1+params->offs[0].off1)*2*(n-1)-params->radius*2)/2+(params->offs[1].off1+params->offs[0].off1)*(n-1);
  short po=1;
  for(int j=1;j<n;po=7*j+1,j++){
    params->points[r].x=params->points[r-po].x+params->offs[1].off1;
    params->points[r].y=params->points[r-po].y+params->offs[0].off2;
    r++;
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off1;
        params->points[r].y=params->points[r-1].y+params->offs[1].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off2;
        params->points[r].y=params->points[r-1].y+params->offs[1].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[2].off1;
        params->points[r].y=params->points[r-1].y+params->offs[0].off1;
        r++;

    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[1].off1;
        params->points[r].y=params->points[r-1].y;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[2].off1;
        params->points[r].y=params->points[r-1].y-params->offs[0].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off2;
        params->points[r].y=params->points[r-1].y-params->offs[1].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off1;
        params->points[r].y=params->points[r-1].y-params->offs[1].off1;
        r++;
    }
  }
}
void assembleDecagonalPlot(cps* params,int n){
   params->points=(XPoint*)malloc(sizeof(XPoint)*(params->pointsCount));
  params->offs[0].off1=params->goffset*2/6;
  params->offs[0].off2=params->goffset/6;
  params->offs[1].off1=params->goffset*4/6;
  params->offs[1].off2=params->goffset*3/6;
  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=1;
  params->points[0].y=(params->d-((params->offs[0].off2+params->offs[1].off2)*2+params->offs[1].off1)*(n-1)-params->radius*2)/2;
  params->points[0].x=(params->d-(params->offs[1].off1+params->offs[0].off1)*2*(n-1)-params->radius*2)/2+(params->offs[1].off1+params->offs[0].off1)*(n-1);
  short po=1;
  for(int j=1;j<n;po=8*j+1,j++){
    params->points[r].x=params->points[r-po].x+params->offs[1].off1;
    params->points[r].y=params->points[r-po].y+params->offs[0].off2;
    r++;
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off1;
        params->points[r].y=params->points[r-1].y+params->offs[1].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x;
        params->points[r].y=params->points[r-1].y+params->offs[1].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off1;
        params->points[r].y=params->points[r-1].y+params->offs[1].off2;
        r++;

    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[1].off1;
        params->points[r].y=params->points[r-1].y+params->offs[0].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[1].off1;
        params->points[r].y=params->points[r-1].y-params->offs[0].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x-params->offs[0].off1;
        params->points[r].y=params->points[r-1].y-params->offs[1].off2;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x;
        params->points[r].y=params->points[r-1].y-params->offs[1].off1;
        r++;
    }
    for(int i=0;i<j;i++){
        params->points[r].x=params->points[r-1].x+params->offs[0].off1;
        params->points[r].y=params->points[r-1].y-params->offs[1].off2;
        r++;
    }
  }
}