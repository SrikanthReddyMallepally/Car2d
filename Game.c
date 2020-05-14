#include<stdio.h>
#include<dos.h>
#include<graphics.h>
# define UNCLICKED 0
# define CLICKED 1
//////////////////////////////////
//constants
//////////////////////////////////
union REGS i,o;
int X=0, Y=0;
int color=1,BodyColor=15;
int a=150,score=0;
char s[20];
int k=20 ,f=0,v=0;
//////////////////////////////////
//user defined functions
/////////////////////////////////
void CarColorModule();
void SelectEnvi();
void button(int,int,int,int,int,char*,int,int);
void dispScore(int);
void car(int,int);
void city();
void forest();
void village();
void is_keyhitvillage();
void is_keyhit();
void mini_forest();
void mini_city();
void mini_village();
void mainScreen();
void lines(int,int);
void tree(int,int);
void lines1(int,int);
void tree1(int,int);
void lines2(int,int);
void tree2(int,int);
void hills(int,int);

////////////////////////////////////////
// MOUSE RELATED FUNCTIONS
///////////////////////////////////////
void init_mouse()
{
  union REGS iregs, oregs;
  iregs.x.ax = 0;
  int86(0x33, &iregs, &oregs);
  if(oregs.x.ax == 0)
   {
    cleardevice();
    printf("mouse not installed\n");
    getch();
    exit(1);
   }
   iregs.x.ax = 1;
   int86(0x33, &iregs ,&oregs);
}
void mouse()
{
 int button,x1,y1;
 union REGS iregs, oregs;
 iregs.x.ax = 3;
 int86(0x33, &iregs ,&oregs);
 button = oregs.x.bx & 3;
 x1 = oregs.x.cx;
 y1 = oregs.x.dx;
 if(oregs.x.bx & 1)
  {
   X = x1 ; Y = y1;
  }
 if(button == 3)
   exit(0);
}
void hide_mouse()
{
 union REGS ioRegs;
 ioRegs.x.ax=2;
 int86(0x33,&ioRegs,&ioRegs);
}
void show_mouse()
{
 union REGS ioRegs;
 ioRegs.x.ax=1;
 int86(0x33,&ioRegs,&ioRegs);
}
void remove_mouse()
{
 union REGS ioRegs;
 ioRegs.x.ax=0;
 int86(0x33,&ioRegs,&ioRegs);
}
///////////////////////////////////
// 3d button
//////////////////////////////////
void button(int x1,int y1,int x2,int y2,int check,char* text,int btncolor,int color)
{
 int up,low;
 setfillstyle(1,btncolor);
 bar(x1,y1,x2,y2);
 if(check==0)    //Unclicked
 up=15,low=8;
 else
 up=8,low=15;     //Clicked
 setcolor(low);
 line(x2,y1,x2,y2);
 line(x2-1,y1,x2-1,y2);
 line(x1,y2,x2,y2);
 line(x1+1,y2-1,x2,y2-1);

 setcolor(up);
 line(x1,y1,x2,y1);
 line(x1+1,y1+1,x2-1,y1+1);
 line(x1,y1,x1,y2);
 line(x1+1,y1+1,x1+1,y2-1);
 setcolor(color);

 settextjustify(CENTER_TEXT,CENTER_TEXT);
 outtextxy(x1+4+(x2 - x1)/2,(y1+(y2 - y1)/2)-4, text);
}
void dispScore(int color)
{
 sprintf(s,"SCORE:-%d",score);
 setcolor(color);
 outtextxy(545,445,s);
}
//////////////////////////////////
// CAR
/////////////////////////////////
void car(int c,int x)
{
 setcolor(c);

 setfillstyle(1,c);
 line(10+a,365,38+a,370);
 line(103+a,370,218+a,370);
 line(282+a,370,290+a,370);
 arc(70+a,365,350,190,32);
 arc(250+a,365,350,190,32);
 //wheels
 setcolor(c);
 setfillstyle(1,0);
 circle(70+a,364,24);
 circle(70+a,364,15);
 circle(250+a,364,24);
 circle(250+a,364,15);
 floodfill(49+a,366,c);
 floodfill(229+a,366,c);
 floodfill(88+a,366,c);
 floodfill(268+a,366,c);
 setcolor(c);
 setfillstyle(1,7);
 pieslice(70+a,364,20,60,15);
 pieslice(70+a,364,80,120,15);
 pieslice(70+a,364,140,180,15);
 pieslice(70+a,364,200,240,15);
 pieslice(70+a,364,260,300,15);
 pieslice(70+a,364,320,360,15);

 pieslice(250+a,364,20,60,15);
 pieslice(250+a,364,80,120,15);
 pieslice(250+a,364,140,180,15);
 pieslice(250+a,364,200,240,15);
 pieslice(250+a,364,260,300,15);
 pieslice(250+a,364,320,360,15);
 setcolor(c);
 setfillstyle(1,c);
 //front
 arc(290+a,358,270,360,12);      ///1
 line(301+a,357,296+a,349);       //2
 line(296+a,349,301+a,338);    ///3
 arc(292+a,333,320,34,11);     ///front light dwn curve          //4
 if(c==0)
 setfillstyle(1,0);                  //////////change
 else
 setfillstyle(1,14);
 line(301+a,327,271+a,309); //lighttop  //5
 arc(298+a,297,202,275,30);      //6
 floodfill(280+a,317,c);
 setcolor(c);
 arc(290+a,343,279,90,5);       //7
 if(c==0)
 setfillstyle(1,0);
 else
 setfillstyle(1,14);
 line(285+a,337,302+a,337); //8           //3-302
 line(285+a,337,290+a,347);    //9
 line(290+a,347,296+a,348);  //10 ///3-296
 floodfill(292+a,343,c);
 line(271+a,309,240+a,305);//engine top 1
 line(240+a,305,200+a,304); //engine top 2
 //mirror
 setcolor(c);
 if(c==0)
 setcolor(0);
 line(186+a,285,210+a,304); //mirror botm
 line(186+a,285,168+a,276);//mirrortop
 line(182+a,290,200+a,304);//mirrorlayer 2 btm
 line(182+a,290,165+a,280);//mirror layer 2 tp
 line(165+a,280,168+a,276);
 if(c==0)
 setfillstyle(1,0);
 else
 setfillstyle(1,color);              ///////////change done
 if(c==0)
 floodfill(187+a,290,0);
 else
 floodfill(187+a,290,c);

 //top1
 line(34+a,307,80+a,285);
 line(80+a,285,110+a,278);
 line(110+a,278,140+a,275);
 line(140+a,275,158+a,275);
 line(158+a,275,168+a,276);//joint to mirror top           158 275
 //top2
 line(165+a,280,150+a,280);
 line(150+a,280,130+a,282);
 line(130+a,282,110+a,285);
 line(110+a,285,90+a,291);
 line(90+a,291,68+a,300);
 //windows
 line(68+a,300,72+a,302);
 line(72+a,302,79+a,303);
 line(79+a,303,89+a,304);
 line(89+a,304,115+a,306);
 line(115+a,306,177+a,307);
 line(95+a,305,100+a,289); ////window divider
 //door
 //sidemirrior
 line(200+a,304,180+a,311);
 arc(182+a,306,90,270,5);
 line(180+a,302,185+a,300);
 line(185+a,300,192+a,299);
 if(c==0)
 setcolor(0);
 else
 setcolor(c);
 ///back
 line(10+a,365,16+a,359);
 line(16+a,359,10+a,340);
 line(10+a,340,18+a,325);
 //backlight
 if(c==0)
 setcolor(0);
 else
 setcolor(c);
 line(18+a,325,14+a,315);
 line(14+a,315,39+a,315);
 line(39+a,315,46+a,322);
 line(46+a,322,25+a,322);
 line(25+a,322,18+a,325);
 //from light to mirror
 if(c==0)
 setfillstyle(1,0);
 else
 setfillstyle(1,6);     //9,4
 floodfill(20+a,320,c);
 setcolor(c);
 line(14+a,315,36+a,307);
 ///////////car full body color
 setcolor(c);
 setfillstyle(1,x);
 floodfill(250+a,320,c);
 setcolor(c);
 arc(150+a,305,180,279,55);
 line(200+a,307,203+a,312);
 line(203+a,312,203+a,348);
 line(203+a,348,200+a,360);
 line(200+a,360,157+a,360);
 ellipse(220+a,325,0,360,5,2);
 ellipse(109+a,318,0,360,10,1);
 delay(13);
}

void lines2(int x,int y)
{
setcolor(6);
setfillstyle(1,6);
line(270+x,272+y,270+x,232+y);
line(280+x,272+y,280+x,232+y);
line(270+x,272+y,280+x,272+y);
line(270+x,232+y,280+x,232+y);
floodfill(272+x,265+y,6);
}
void tree2(int x,int y)
{
setcolor(2);
setfillstyle(1,2);
arc(265+x,222+y,270,340,15);
arc(265+x,222+y,145,270,15);
arc(265+x,212+y,110,260,15);
arc(270+x,202+y,70,185,13);
arc(280+x,207+y,0,130,17);
arc(280+x,218+y,240,20,18);

arc(288+x,210+y,280,16,10);
arc(280+x,207+y,0,100,10);
arc(280+x,207+y,70,150,10);
arc(270+x,207+y,140,190,10);
arc(270+x,215+y,190,250,10);
arc(280+x,207+y,0,100,10);
arc(280+x,207+y,180,250,10);
floodfill(272+x,222+y,2);
}
void lines1(int x,int y)
{
setcolor(6);
setfillstyle(1,6);
line(300+x,272+y,300+x,252+y);
line(310+x,272+y,310+x,252+y);
line(300+x,272+y,310+x,272+y);
line(300+x,252+y,310+x,252+y);
floodfill(302+x,270+y,6);
}
void tree1(int x,int y)
{
setcolor(10);
setfillstyle(1,10);
arc(300+x,242+y,90,300,12);
arc(310+x,242+y,230,90,12);
arc(305+x,232+y,340,200,10);
floodfill(305+x,232+y,10);
}
void lines(int x,int y)
{
setcolor(6);
setfillstyle(1,6);
line(230+x,272+y,230+x,262+y);
line(240+x,272+y,240+x,262+y);
line(230+x,272+y,240+x,272+y);
line(230+x,262+y,240+x,262+y);
floodfill(232+x,270+y,6);
}
void tree(int x,int y)
{
setcolor(2);
setfillstyle(1,2);
arc(230+x,252+y,90,300,12);
arc(240+x,252+y,230,90,12);
arc(235+x,242+y,340,200,12);
floodfill(235+x,242+y,2);

}
/////////////////////////////////////////
//MAIN FOREST,MAIN CITY,MAIN VILLAGE
/////////////////////////////////////////
void city()
{
 int i=0,j=0;
// cleardevice();
 hide_mouse();
 remove_mouse();
 setcolor(15);
 setfillstyle(1,15);
 circle(37,40,20);
 floodfill(39,43,15);
 ///building 1
 setcolor(6);
 setfillstyle(1,6);
 rectangle(0,280-117,80,390-117);
 floodfill(2,282-117,6);
 for(i=0;i<=80;i=i+20)
 {
  for(j=0;j<=60;j=j+20)
  {
   setcolor(0);
   setfillstyle(1,7);
   rectangle(6+j,286+i-117,16+j,296+i-117);
   floodfill(7+j,287+i-117,0);
  }
 }
 //building 2
 setcolor(15);
 setfillstyle(1,4);
 rectangle(98,230-117,170,389-117);
 floodfill(100,232-117,15);
 setcolor(7);
 for(i=0;i<=60;i=i+10)
 {
 rectangle(100+i,230-117,108+i,388-117);     //388
 }
 for(i=0;i<=150;i=i+10)  //150
 {
 rectangle(98,230+i-117,170,239+i-117);
 }
//big building 3
 setcolor(7);
 line(235,15,235,28);
 rectangle(232,28,238,35);
 setfillstyle(8,7);
 floodfill(234,32,7);
 rectangle(230,35,240,45);
 floodfill(235,39,7);
 rectangle(225,45,245,60);
 floodfill(232,57,7);
 rectangle(220,60,250,80);
 floodfill(227,72,7);
 rectangle(215,80,255,100);
 floodfill(219,85,7);
 rectangle(205,100,265,140);
 floodfill(209,105,7);
 rectangle(195,140,275,272);
 floodfill(200,145,7);
 //building4
 setcolor(9);
 setfillstyle(7,9);
 rectangle(303,260-117,367,389-117);
 floodfill(305,262-117,9);
 //building5
 setcolor(5);
 setfillstyle(1,5);
 pieslice(410,220-117,0,180,30);
 setcolor(2);
 setfillstyle(7,2);
 rectangle(380,220-117,440,389-117);
 floodfill(382,222-117,2);
 for(i=0;i<=140;i=i+20)
 {
  for(j=0;j<=40;j=j+20)
  {
   setcolor(7);
   setfillstyle(1,7);
   rectangle(385+j,225+i-117,395+j,235+i-117);
   floodfill(386+j,226+i-117,7);
  }
 }
 //building6
 setcolor(11);
 setfillstyle(2,11);
 rectangle(460,259-117,520,389-117);
 floodfill(462,261-117,11);
 //building7 last
 setcolor(14);
 setfillstyle(1,14);                 //////7,14
 rectangle(540,180-117,639,389-117);
 floodfill(542,183-117,14);
 for(i=0;i<=180;i=i+20)
 {
  for(j=0;j<=80;j=j+20)
  {
   setcolor(0);
   setfillstyle(1,7);
   rectangle(545+j,190+i-117,553+j,198+i-117);
   floodfill(546+j,191+i-117,0);
  }
 }
 setcolor(7);
 line(0,272,639,272);
 line(0,273,639,273);
 /////////grounds///
 setcolor(2);
 setfillstyle(1,2);
 rectangle(0,390,639,410);
 floodfill(5,392,2);
 setcolor(6);
 setfillstyle(1,6);
 rectangle(0,411,639,479);
 floodfill(5,435,6);
 setcolor(7);
 line(0,390,639,390);
 line(0,390,639,390);
 car(15,color);
}

void forest()
{

 hide_mouse();
 remove_mouse();

 if(f==0)
 {
 setcolor(2);
 rectangle(0,390,639,410);
 setfillstyle(1,2);
 floodfill(5,392,2);

 setcolor(6);
 rectangle(0,411,639,479);
 setfillstyle(1,6);
 floodfill(5,435,6);

 setcolor(3);
 rectangle(0,0,639,110);
 setfillstyle(1,3);
 floodfill(7,20,3);

 setcolor(8);
 rectangle(0,111,639,273);
 setfillstyle(1,8);
 floodfill(8,117,8);

//3rd tree

setcolor(2);
setfillstyle(1,2);
line(180,272,180,212);
line(200,272,200,212);
line(180,212,150,212);
line(200,212,230,212);
line(150,212,180,192);
line(230,212,200,192);
line(180,192,150,192);
line(200,192,230,192);
line(180,272,200,272);
line(150,192,180,172);//left
line(230,192,200,172);//right
line(180,172,150,172);
line(200,172,230,172);
line(150,172,180,152);//l
line(230,172,200,152);//r
line(180,152,150,152);
line(200,152,230,152);
line(150,152,190,120);//l
line(230,152,190,120);//r
floodfill(182,265,2);
//4th tree
setcolor(2);
setfillstyle(1,2);
line(270,272,270,232);
line(280,272,280,232);
line(270,272,280,272);
line(270,232,280,232);
floodfill(272,265,2);
setcolor(2);
setfillstyle(1,2);
arc(265,222,270,340,15);
arc(265,222,145,270,15);
arc(265,212,110,260,15);
arc(270,202,70,185,13);
arc(280,207,0,130,17);
arc(280,218,240,20,18);
arc(288,210,280,16,10);
arc(280,207,0,100,10);
arc(280,207,70,150,10);
arc(270,207,140,190,10);
arc(270,215,190,250,10);
floodfill(272,222,2);

//5th tree
setcolor(2);
setfillstyle(1,2);
line(340,272,340,222);
line(360,272,360,222);
line(340,272,360,272);
arc(340,202,160,270,20);
arc(330,182,110,270,20);
arc(340,172,50,190,20);
arc(360,202,270,10,20);
arc(360,172,0,130,20);
arc(365,187,300,90,23);
arc(360,187,182,90,10);
arc(344,204,150,200,10);
floodfill(342,265,2);

//6th tree
setcolor(2);
setfillstyle(1,2);
line(460,272,460,212);
line(480,272,480,212);
line(460,212,430,212);
line(480,212,510,212);
line(430,212,460,192);
line(510,212,480,192);
line(460,192,430,192);
line(480,192,510,192);
line(430,192,460,172);
line(510,192,480,172);
line(460,172,430,172);
line(480,172,510,172);
line(430,172,460,152);
line(510,172,480,152);
line(460,152,430,152);
line(480,152,510,152);
line(430,152,470,132);
line(510,152,470,132);
line(460,272,480,272);
floodfill(462,270,2);

//7th tree
setcolor(2);
setfillstyle(1,2);
line(540,272,540,222);
line(560,272,560,222);
line(540,272,560,272);
arc(540,202,160,270,20);
arc(530,182,110,280,20);
arc(540,172,50,190,20);
arc(560,202,270,10,20);
arc(560,172,0,110,20);
arc(567,188,300,105,20);
arc(565,187,300,90,10);
arc(544,207,150,220,10);
arc(550,162,0,100,10);
arc(540,182,10,200,10);
floodfill(542,265,2);

//base 230 and add 270=500(x-axis position)
lines(50,-95); tree(50,-95);
lines(-100,-72); tree(-100,-72);
lines(175,0);
lines(-70,0); tree(-70,0);
lines(-10,0); tree(-10,0);
lines(155,0); tree(155,0);
lines(380,-90);tree(380,-90);
lines(-210,-95); tree(-210,-95);
lines(170,-95); tree(170,-95);
lines(270,0); tree(270,0);
lines(200,0); tree(200,0);
lines(350,0); tree(350,0);

//base 300
lines1(0,0); tree1(0,0);
lines1(-278,0); tree1(-278,0);
lines1(-60,-65); tree1(-60,-65);
lines1(-225,-95); tree1(-225,-95);
lines1(306,0); tree1(306,0);
lines1(105,-10); tree1(105,-10);
lines1(-190,0); tree1(-190,0);
//base 270
lines2(-215,0);  tree2(-215,0);
setcolor(6);
setfillstyle(1,6);
line(0,110,640,110);
line(0,110,80,20);
line(80,20,130,70);
line(130,70,180,20);
line(180,20,230,70);
line(230,70,280,20);
line(280,20,330,70);

line(330,70,380,20);
line(380,20,430,70);
line(430,70,480,20);
line(480,20,530,70);
line(530,70,580,20);
line(580,20,640,110);
floodfill(122,80,6);
f++;
}
car(15,color);
}
void village()
{
 hide_mouse();
 remove_mouse();

if(v==0)
{ setcolor(15);
 circle(42,42,20);
 setfillstyle(1,15);
 floodfill(43,43,15);
 setcolor(15);
 //cloud 1
 ellipse(200,50,60,240,10,15);
 ellipse(225,40,345,165,20,15);
 ellipse(262,47,340,160,20,15);
 ellipse(268,66,230,50,20,15);
 ellipse(230,71,143,345,40,19);
 ellipse(300,41,20,182,21,19);
 ellipse(325,50,290,100,21,15);
 ellipse(299,65,228,20,33,15);          //line(300,55,300,55);
 setfillstyle(1,1);
 floodfill(300,55,15);
 //cloud 2
 ellipse(400,50,60,240,10,15);
 ellipse(425,40,345,165,20,15);
 ellipse(462,47,340,160,20,15);
 ellipse(468,66,230,50,20,15);
 ellipse(430,71,143,345,40,19);
 ellipse(500,41,20,182,21,19);
 ellipse(525,50,290,100,21,15);
 ellipse(500,65,228,20,33,15);          //line(510,55,510,55);
 setfillstyle(1,1);
 floodfill(510,55,15);
 //Hill 1                               //Base for Hills
 line(10,170,90,120);                   //line(0,170,689,170);
 line(90,120,170,170);
 line(10,170,170,170);                  //line(111,140,111,140);
 setfillstyle(1,6);
 floodfill(111,140,15);
 //Hill 2
 line(130,145,170,120);
 line(170,120,270,170);
 line(170,170,270,170);                 //line(180,145,180,145);
 setfillstyle(1,6);
 floodfill(180,145,15);
 //Hill 3
 line(220,145,270,120);
 line(270,120,350,170);
 line(270,170,350,170);                 //line(231,145,231,145);
 setfillstyle(1,6);
 floodfill(231,145,15);
 //Hill 4
 line(310,145,360,120);
 line(360,120,440,170);
 line(350,170,440,170);                 //line(341,145,341,145);
 setfillstyle(1,6);
 floodfill(341,145,15);
 //Hill 5
 line(400,145,450,120);
 line(450,120,530,170);
 line(440,170,530,170);                 //line(431,145,431,145);
 setfillstyle(1,6);
 floodfill(431,145,15);
 //Hill 6
 line(490,145,540,120);
 line(540,120,620,170);
 line(530,170,620,170);                 //line(521,145,521,145);
 setfillstyle(1,6);
 floodfill(521,145,15);
 //Stones
 arc(38,259,0,180,15);
 arc(30,272,0,180,15);
 arc(50,272,0,129,15);
 line(10,272,70,272);                   //line(48,252,48,252);
 setfillstyle(1,2);
 floodfill(28,262,15);
 setfillstyle(1,2);
 floodfill(58,262,15);
 setfillstyle(1,2);
 floodfill(48,252,15);
 //Cocunut 1
 pieslice(515-240,240-50,45,225,10);
 pieslice(490-240,245-50,230,330,15);
 pieslice(493-240,240-50,315,175,13);
 pieslice(500-240,230-50,75,270,10);
 setfillstyle(1,6);
 arc(323-240,340-50,5,30,200);
 arc(323-240,340-50,5,30,205);
 line(520-240,322-50,528-240,322-50);
 line(497-240,241-50,502-240,241-50);
 floodfill(503-240,249-50,15);
 //Cocunut 2
 setfillstyle(1,2);
 pieslice(515-40,240-50,45,225,10);
 pieslice(490-40,245-50,230,330,15);
 pieslice(493-40,240-50,315,175,13);
 pieslice(500-40,230-50,75,270,10);
 floodfill(470,190,15);
 setfillstyle(1,6);
 arc(323-40,340-50,5,30,200);
 arc(323-40,340-50,5,30,205);
 line(520-40,322-50,528-40,322-50);
 line(497-40,241-50,502-40,241-50);
 floodfill(503-40,249-50,15);
 //Building 1              	       //Base for Building
 //Outerwall	   	  	       //line(0,272,639,272);
 rectangle(210,220,150,272);
 setfillstyle(1,9);
 line(210,220,180,200);
 line(150,220,180,200);  	       //line(180,210,180,210);
 floodfill(180,210,15);
 //Inner door
 setfillstyle(1,4);
 rectangle(170,240,190,272);
 floodfill(175,230,15);
 //2D View code
 setfillstyle(1,9);
 line(140,200,180,200);
 line(140,200,120,220);
 line(120,220,210,220);
 floodfill(135,215,15);
 line(120,220,120,272);
 line(120,272,190,272);
 floodfill(132,270,15);			  //line(132,270,132,270);
 //Building 2
 //outer wall
 rectangle(310,220,370,272);
 //Inner door
 rectangle(330,240,350,272);
 setfillstyle(1,3);
 line(300,220,340,195);
 line(380,220,340,195);
 line(380,220,370,220);
 floodfill(355,235,15);
 line(300,220,310,220);
 circle(340,210,5);                     //line(330,210,330,210);
 setfillstyle(1,7);
 floodfill(340,210,15);
 setfillstyle(1,4);
 floodfill(330,210,15);
 //Building 3
 //outer wall
 rectangle(500,220,580,272);
 setfillstyle(1,3);
 line(500,220,540,195);
 line(580,220,540,195);                 //line(525,210,525,210);
 floodfill(525,210,15);
 //Inner door
 rectangle(525,240,550,272);
 setfillstyle(1,12);
 floodfill(524,245,15);
 //test code
 setfillstyle(1,17);
 line(540,195,580,195);
 line(580,195,610,220);
 line(530,220,610,220);
 floodfill(570,210,15);
 line(610,220,610,272);
 line(610,272,580,272);                 //line(609,245,609,245);
 floodfill(609,245,15);
 //Christmas Tree
 line(240-165,235,275-165,235);
 line(240-165,235,245-165,220);
 line(275-165,235,270-165,220);
 line(245-165,220,240-165,220);
 line(270-165,220,275-165,220);
 line(240-165,220,245-165,205);
 line(275-165,220,270-165,205);
 line(245-165,205,240-165,205);
 line(270-165,205,275-165,205);
 line(240-165,205,258-165,185);
 line(275-165,205,257-165,185);
 line(275-165,205,257-165,185);         //line(250-165,210,250-165,210);
 setfillstyle(1,2);
 floodfill(250-165,210,15);
 //Tree Trunk
 rectangle(252-165,235,263-165,272);
 setfillstyle(1,6);
 floodfill(253-165,236,15);
 ////tree3
 setcolor(7);
 rectangle(50+365,305-55,58+365,321-55);
 setfillstyle(1,6);
 floodfill(51+365,306-55,7);
 setcolor(2);
 circle(47+365,302-55,10);
 setfillstyle(1,2);
 floodfill(48+365,303-55,2);
 circle(62+365,302-55,10);
 setfillstyle(1,2);
 floodfill(63+365,303-55,2);
 circle(54+365,292-55,10);
 setfillstyle(1,2);
 floodfill(55+365,293-55,2);
 //tree2
 setcolor(7);
 rectangle(50+190,305-55,58+190,321-55);
 setfillstyle(1,6);
 floodfill(51+190,306-55,7);
 setcolor(2);
 circle(47+190,302-55,10);
 setfillstyle(1,2);
 floodfill(48+190,303-55,2);
 circle(62+190,302-55,10);
 setfillstyle(1,2);
 floodfill(63+190,303-55,2);
 circle(54+190,292-55,10);
 setfillstyle(1,2);
 floodfill(55+190,293-55,2);
 //Tree 1
 setcolor(7);
 rectangle(50-10,305-90,58-10,321-90);
 setfillstyle(1,6);
 floodfill(51-10,306-90,7);
 setcolor(2);
 circle(47-10,302-90,10);
 setfillstyle(1,2);
 floodfill(48-10,303-90,2);
 circle(62-10,302-90,10);
 setfillstyle(1,2);
 floodfill(63-10,303-90,2);
 circle(54-10,292-90,10);
 setfillstyle(1,2);
 floodfill(55-10,293-90,2);
 //Base
 setcolor(2);
 setfillstyle(1,2);
 rectangle(0,390,639,410);
 floodfill(5,392,2);
 setcolor(6);
 setfillstyle(1,6);
 rectangle(0,411,639,479);
 floodfill(5,435,6);
 setcolor(7);
 line(0,390,639,390);
 line(0,390,639,390);
 v++;
 }
  car(15,color);
}
/////////////////////////////////////////
//CITY FOREST AND VILLAGE CONTROLS
/////////////////////////////////////////
void is_keyhitforest()
{
  sprintf(s,"TIME LEFT IN SECS:-%d",k);
  setcolor(0);
  outtextxy(245,445,s);
 if(kbhit())
   {
     i.h.ah=0;
     int86(22,&i,&o);
     if(o.h.ah==1)
      {
       //exit(0);
      }
     if(o.h.ah==75)
      {
	dispScore(6);
	car(0,0);
	a=a-10;
	score-=20;
	if(score<0)
	   score=0;
	forest();
	dispScore(4);
      }
      if(o.h.ah==77)
      {
       dispScore(6);
       car(0,0);
       a=a+10;
       score+=20;
       forest();
       dispScore(4);
      }
   }
  delay(1000);
   sprintf(s,"TIME LEFT IN SECS:-%d",k);
   setcolor(6);
   outtextxy(245,445,s);
   k=k-1;
   if(k<=0)
   {
    int x,y;
    x=getmaxx()/2;
    y=getmaxy()/2;
    cleardevice();
    setcolor(15);
    rectangle(x-200,y-100,x+200,y+100);
    rectangle(x-201,y-101,x+201,y+101);
    sprintf(s,"YOUR SCORE:-%d",score);
    outtextxy(x-10,y,s);
    delay(3000);
     k=20;score=0;
     f=0;
     i.x.ax=0; // init mouse
 int86(0x33,&i,&i);
 i.x.ax=1; // show mouse
 int86(0x33,&i,&i);
 settextstyle(8,0,3);
 button(190,300,320,330,UNCLICKED,"Continue",4,15);
 button(340,300,470,330,UNCLICKED,"Exit",4,15);
 while(1)
  {
   i.x.ax=3; // getmouse function
   X=i.x.cx; // getmouse function
   Y=i.x.dx; // getmouse function
   int86(0x33,&i,&i); // getmouse function
   if(X>=190 && X<=320 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(190,300,320,330,CLICKED,"Continue",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(190,300,320,330,UNCLICKED,"Continue",4,15);
      delay(100);
      remove_mouse();
      CarColorModule();
    }
   if(X>=340 && X<=470 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(340,300,470,330,CLICKED,"Exit",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(340,300,470,330,UNCLICKED,"Exit",4,15);
      show_mouse();
      exit(0);
    }
  }
   }
}
void is_keyhit()
{
  sprintf(s,"TIME LEFT IN SECS:-%d",k);
  setcolor(0);
  outtextxy(245,445,s);
 if(kbhit())
   {
     i.h.ah=0;
     int86(22,&i,&o);
     if(o.h.ah==1)
      {
       //exit(0);
      }
     if(o.h.ah==75)
      {
	dispScore(6);
	car(0,0);
	a=a-10;
	score-=20;
	if(score<0)
	   score=0;
	city();
	dispScore(4);
      }
      if(o.h.ah==77)
      {
       dispScore(6);
       car(0,0);
       a=a+10;
       score+=20;
       city();
       dispScore(4);
      }
   }
  delay(1000);
   sprintf(s,"TIME LEFT IN SECS:-%d",k);
   setcolor(6);
   outtextxy(245,445,s);
   k=k-1;
   if(k<=0)
   {
    int x,y;
    x=getmaxx()/2;
    y=getmaxy()/2;
    cleardevice();
    setcolor(15);
    rectangle(x-200,y-100,x+200,y+100);
    rectangle(x-201,y-101,x+201,y+101);
    sprintf(s,"YOUR SCORE:-%d",score);
    outtextxy(x-10,y,s);
    delay(3000);
     k=20;score=0;
     i.x.ax=0; // init mouse
 int86(0x33,&i,&i);
 i.x.ax=1; // show mouse
 int86(0x33,&i,&i);
 settextstyle(8,0,3);
 button(190,300,320,330,UNCLICKED,"Continue",4,15);
 button(340,300,470,330,UNCLICKED,"Exit",4,15);
 while(1)
  {
   i.x.ax=3; // getmouse function
   X=i.x.cx; // getmouse function
   Y=i.x.dx; // getmouse function
   int86(0x33,&i,&i); // getmouse function
   if(X>=190 && X<=320 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(190,300,320,330,CLICKED,"Continue",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(190,300,320,330,UNCLICKED,"Continue",4,15);
      delay(100);
      remove_mouse();
      CarColorModule();
    }
   if(X>=340 && X<=470 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(340,300,470,330,CLICKED,"Exit",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(340,300,470,330,UNCLICKED,"Exit",4,15);
      show_mouse();
      exit(0);
    }
  }
   }
}
void is_keyhitvillage()
{
 sprintf(s,"TIME LEFT IN SECS:-%d",k);
 setcolor(0);
 outtextxy(245,445,s);
 if(kbhit())
  {
   i.h.ah=0;
   int86(22,&i,&o);
   if(o.h.ah==1)
    {
   //  exit(0);
    }
   if(o.h.ah==75)
    {
     dispScore(6);
     car(0,0);
     a=a-10;
     score-=20;
     if(score<0)
       score=0;
     village();
     dispScore(4);
    }
   if(o.h.ah==77)
    {
     dispScore(6);
     car(0,0);
     a=a+10;
     score+=20;
     village();
     dispScore(4);
    }
   }
  delay(1000);
   sprintf(s,"TIME LEFT IN SECS:-%d",k);
   setcolor(6);
   outtextxy(245,445,s);
   k=k-1;
   if(k<=0)
   {
    int x,y;
    x=getmaxx()/2;
    y=getmaxy()/2;
    cleardevice();
    setcolor(15);
    rectangle(x-200,y-100,x+200,y+100);
    rectangle(x-201,y-101,x+201,y+101);
    sprintf(s,"YOUR SCORE:-%d",score);
    outtextxy(x-10,y,s);
    delay(5000);
     k=20;v=0;score=0;
     i.x.ax=0; // init mouse
 int86(0x33,&i,&i);
 i.x.ax=1; // show mouse
 int86(0x33,&i,&i);
 settextstyle(8,0,3);
 button(190,300,320,330,UNCLICKED,"Continue",4,15);
 button(340,300,470,330,UNCLICKED,"Exit",4,15);
 while(1)
  {
   i.x.ax=3; // getmouse function
   X=i.x.cx; // getmouse function
   Y=i.x.dx; // getmouse function
   int86(0x33,&i,&i); // getmouse function
   if(X>=190 && X<=320 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(190,300,320,330,CLICKED,"Continue",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(190,300,320,330,UNCLICKED,"Continue",4,15);
      delay(100);
      remove_mouse();
      CarColorModule();
    }
   if(X>=340 && X<=470 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(340,300,470,330,CLICKED,"Exit",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(340,300,470,330,UNCLICKED,"Exit",4,15);
      show_mouse();
      exit(0);
    }
  }
   }
}

/////////////////////////////////////////
// 	PAGE 1 SCREEN
////////////////////////////////////////
void MainScreen()
{
 setcolor(15);
 settextstyle(10,0,9);
 setfillstyle(2,4);
 outtextxy(50,30,"CAR 2D");
 floodfill(93,196,15);
 floodfill(160,196,15);
 floodfill(269,196,15);
 floodfill(426,196,15);
 floodfill(520,196,15);
 i.x.ax=0; // init mouse
 int86(0x33,&i,&i);
 i.x.ax=1; // show mouse
 int86(0x33,&i,&i);
 settextstyle(8,0,3);
 button(200,300,300,330,UNCLICKED,"Play",4,15);
 button(350,300,450,330,UNCLICKED,"Exit",4,15);
 while(1)
  {
   i.x.ax=3; // getmouse function
   X=i.x.cx; // getmouse function
   Y=i.x.dx; // getmouse function
   int86(0x33,&i,&i); // getmouse function
   if(X>=200 && X<=300 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(200,300,300,330,CLICKED,"Play",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(200,300,300,330,UNCLICKED,"Play",4,15);
      delay(100);
      CarColorModule();
    }
   if(X>=350 && X<=450 && Y>=300 && Y<=330 &&i.x.bx ==1)
    {
      hide_mouse();
      button(350,300,450,330,CLICKED,"Exit",4,15);
      show_mouse();
      delay(250);
      hide_mouse();
      button(200,300,450,330,UNCLICKED,"Exit",4,15);
      show_mouse();
      exit(0);
    }
  }

}
//////////////////////////////////////
// PAGE 2 CAR COLOR SELCETION
/////////////////////////////////////
void CarColorModule()
{
 union REGS i,o;
 cleardevice();
  i.x.ax=0; // init mouse
 int86(0x33,&i,&i);
 i.x.ax=1; // show mouse
 int86(0x33,&i,&i);
 outtextxy(150,6,"Select Your Car Color:");
 settextstyle(8,0,3);
 button(200,420,300,450,UNCLICKED,"<-",4,15);
 button(350,420,450,450,UNCLICKED,"->",4,15);
 button(500,420,600,450,UNCLICKED,"Go",4,15);
 button(50,420,150,450,UNCLICKED,"Exit",4,15);
 color=1;
 car(15,color);
 while(1)
 {
  i.x.ax=3; // getmouse function
  X=i.x.cx; // getmouse function
  Y=i.x.dx; // getmouse function
  int86(0x33,&i,&i); // getmouse function
  if(X>=200 && X<=300 && Y>=420 && Y<=450 &&i.x.bx ==1)
   {
     hide_mouse();
     button(200,420,300,450,CLICKED,"<-",4,15);
     show_mouse();
     delay(250);
     hide_mouse();
     button(200,420,300,450,UNCLICKED,"<-",4,15);
     show_mouse();
     if(color==1)
       color=2;
     car(15,--color);
   }
  if(X>=350 && X<=450 && Y>=420 && Y<=450 &&i.x.bx ==1)
   {
     hide_mouse();
     button(350,420,450,450,CLICKED,"->",4,15);
     show_mouse();
     delay(250);
     hide_mouse();
     button(350,420,450,450,UNCLICKED,"->",4,15);
     show_mouse();
      if(color==14)
	color=13;
     car(15,++color);
   }
  if(X>=50 && X<=150 && Y>=420 && Y<=450 &&i.x.bx ==1)
   {
     hide_mouse();
     button(50,420,150,450,CLICKED,"Exit",4,15);
     show_mouse();
     delay(250);
     hide_mouse();
     button(50,420,150,450,UNCLICKED,"Exit",4,15);
     show_mouse();
     exit(0);
   }
  if(X>=500 && X<=600 && Y>=420 && Y<=450 &&i.x.bx ==1)
   {
     hide_mouse();
     button(500,420,600,450,CLICKED,"Go",4,15);
     show_mouse();
     delay(250);
     hide_mouse();
     button(500,420,600,450,UNCLICKED,"Go",4,15);
     delay(100);
     SelectEnvi();

   }
 }
}

///////////////////////////////
// PAGE 3 BACKGROUND SELECTION
///////////////////////////////
void SelectEnvi()
{
 union REGS i,o;
 delay(100);
 i.x.ax=0; // init mouse
 int86(0x33,&i,&i);
 i.x.ax=1; // show mouse
 int86(0x33,&i,&i);
 cleardevice();
 settextstyle(8,0,3);
 outtextxy(150,40,"Select Background:");
 mini_forest();
 mini_city();
 mini_village();
 while(1)
 {
  i.x.ax=3; // getmouse function
  X=i.x.cx; // getmouse function
  Y=i.x.dx; // getmouse function
  int86(0x33,&i,&i); // getmouse function
  if (X>=30 && X<=180 && Y>=365 && Y<=390 &&i.x.bx ==1)
   {
     int k=0;
     hide_mouse();
     button(30,365,180,390,CLICKED,"FOREST",2,0);
     show_mouse();
     delay(250);
     hide_mouse();
     button(30,365,180,390,UNCLICKED,"FOREST",2,0);
     delay(100);
     i.x.ax=0; // init mouse
     int86(0x33,&i,&i);
     i.x.ax=1; // show mouse
     int86(0x33,&i,&i);
     cleardevice();
     a=0;
     if(k==0)
      {
       forest();
       dispScore(4);
       k++;
      }
     while(1)
     {
      is_keyhitforest();
     }

   }
  if (X>=230 && X<=380 && Y>=365 && Y<=390 &&i.x.bx ==1)
   { int k=0;
     hide_mouse();
     button(230,365,380,390,CLICKED,"CITY",1,15);
     show_mouse();
     delay(250);
     hide_mouse();
     button(230,365,380,390,UNCLICKED,"CITY",1,15);
     delay(100);
     i.x.ax=0; // init mouse
     int86(0x33,&i,&i);
     i.x.ax=1; // show mouse
     int86(0x33,&i,&i);
     cleardevice();
    a=0;
     if(k==0)
      {
       city();
       dispScore(4);
       k++;
      }
     while(1)
     {
      is_keyhit();
     }
   }
  if (X>=430 && X<=580 && Y>=365 && Y<=390 &&i.x.bx ==1)
   {
     int k=0;
     hide_mouse();
     button(430,365,580,390,CLICKED,"VILLAGE",4,15);
     show_mouse();
     delay(250);
     hide_mouse();
     button(430,365,580,390,UNCLICKED,"VILLAGE",4,15);
     delay(100);
     i.x.ax=0; // init mouse
     int86(0x33,&i,&i);
     i.x.ax=1; // show mouse
     int86(0x33,&i,&i);
     cleardevice();
     a=0;
     if(k==0)
      {
       village();
       dispScore(4);
       k++;
      }
     while(1)
     {
      is_keyhitvillage();
     }

   }
 }
}
//////////////////////////////////////////////////////
// MINI FOREST ,MINI CITY,MINI VILLAGE (PAGE 3)
//////////////////////////////////////////////////////
void mini_forest()
{
 setcolor(15);
 settextstyle(8,0,2);
 rectangle(30,200,180,350);//1
 setcolor(2);
 setfillstyle(1,2);
 arc(95,280,190,330,16);
 arc(85,270,110,265,16);
 arc(90,260,70,180,18);
 arc(102,250,360,160,18);
 arc(118,260,290,105,16);
 arc(116,278,210,50,16);
 floodfill(105,280,2);
 setcolor(6);
 setfillstyle(1,6);
 rectangle(100,290,110,321);//branch
 floodfill(102,292,6);
 ///////////////small tree 1
 rectangle(50,305,58,321);
 floodfill(51,306,6);
 setcolor(2);
 setfillstyle(1,2);
 circle(47,302,10);
 floodfill(48,303,2);
 circle(62,302,10);
 floodfill(63,303,2);
 circle(54,292,10);
 floodfill(55,293,2);
 /////////small tree 2
 setcolor(6);
 setfillstyle(1,6);
 rectangle(50+100,305,58+100,321);
 floodfill(51+100,306,6);
 setcolor(2);
 setfillstyle(1,2);
 circle(47+100,302,10);
 floodfill(48+100,303,2);
 circle(62+100,302,10);
 floodfill(63+100,303,2);
 circle(54+100,292,10);
 floodfill(55+100,293,2);
 ////ground
 setcolor(2);
 rectangle(31,322,179,330);
 setfillstyle(1,2);
 floodfill(32,323,2);
 setcolor(6);
 setfillstyle(1,6);
 rectangle(31,331,179,349);
 floodfill(32,332,6);   //
 button(30,365,180,390,UNCLICKED,"FOREST",2,0);
}
void mini_city()
{
 setcolor(15);
 settextstyle(8,0,2);
 rectangle(230,200,380,350);
 setcolor(14);
 circle(250,220,10);
 setfillstyle(1,14);
 floodfill(251,221,14);
 button(230,365,380,390,UNCLICKED,"CITY",1,15);
 setcolor(14);
 setfillstyle(1,14);
 rectangle(231,322,379,330);//} __grounds
 floodfill(232,324,14);
 setcolor(12);
 setfillstyle(1,12);
 rectangle(231,331,379,349);//}
 floodfill(232,332,12);
 ////buildings
 setcolor(2);
 setfillstyle(1,2);
 rectangle(260,265,290,321);  //2
 floodfill(261,266,2);
 setcolor(4);
 setfillstyle(1,4);
 rectangle(240,280,270,321);  ///1
 floodfill(241,281,4);
 setcolor(11);
 setfillstyle(1,11);
 rectangle(340,280,370,321);    //5
 floodfill(341,282,11);
 setcolor(1);
 setfillstyle(1,1);
 rectangle(315,265,350,321); ///4
 floodfill(316,267,1);
 setcolor(7);
 setfillstyle(8,7);
 rectangle(285,255,320,321); ///3
 floodfill(286,256,7);
 rectangle(290,240,315,255);  //3
 floodfill(292,241,7);
 rectangle(295,230,310,240);//3
 floodfill(297,231,7);
 rectangle(300,220,306,230); //3
 floodfill(301,221,7);
 line(303,210,303,220);
}
void mini_village()
{
  setcolor(15);
  settextstyle(8,0,2);
  rectangle(430,200,580,350);  //3
  button(430,365,580,390,UNCLICKED,"VILLAGE",4,15);
  ///grounds
  setcolor(2);
  setfillstyle(1,2);
  rectangle(431,322,579,330);
  floodfill(432,323,2);
  setcolor(14);
  setfillstyle(1,14);
  rectangle(431,330,579,349);
  floodfill(432,331,14);
  /////////tree////
  setcolor(15);
  setfillstyle(1,2);
  pieslice(515,240,45,225,10);
  pieslice(490,245,230,330,15);
  pieslice(493,240,315,175,13);
  pieslice(500,230,75,270,10);
  setcolor(6);
  setfillstyle(1,6);
  arc(323,340,5,30,200);
  arc(323,340,5,30,205);
  line(520,322,528,322);
  line(497,241,502,241);
  floodfill(503,249,6); //branch
  //////house///
  setcolor(15);
  setfillstyle(1,4);
  rectangle(465,300,490,321);
  floodfill(467,302,15);
  line(477,285,459,307);
  line(477,285,496,307);
  setfillstyle(1,14);
  floodfill(468,298,15);
  circle(477,295,3);
  setfillstyle(1,2);
  floodfill(478,296,15);
  rectangle(473,310,482,321);
  setfillstyle(1,13);
  floodfill(474,311,15);
  circle(555,225,10); ////moon
  setfillstyle(1,15);
  floodfill(557,227,15);
}

/////////////////////////////////////
// MAIN FUNCTION
////////////////////////////////////
void main()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C:\\Turboc3\\BGI");
MainScreen();//loads page1 screen
}
