#include <graphics.H>
#include<iostream>
#include <stdio.H>
#include <conio.H> //Ahmed Emad Ahmed 20180016
#include <dos.h>
using namespace std;
#define YSize 25 //for the tall of the bar y-axis tall
int n,DELAY;// n is for input number of disks
int IsManual=0,flag=1;
int DiskIsIn[5];
int PosInPeg[5];
int DiskCount[3];
void SetMode()//set graphic driver and mode
{	int graphicsdriver = DETECT/*graphics driver to be used*/, graphicsmode=DETECT/*integer that specifies the initial graphics mode*/;
//here program detect it but it can be vga or vgamed
	initgraph(&graphicsdriver, &graphicsmode, "c:\\tc\\bgi");// function initializes the graphics system by loading a graphics driver from disk
}
void Box(int x1,int y1,int x2,int y2,int doit=1){
		int c2=BROWN,c1=RED;

		bar(x1,y1,x2,y2);

}
void DrawHanoi(int n){
	int i,x,y,size;
	for(i=0;i<n;i++){
		x=5+(DiskIsIn[i]*215)+((4-i)*20);//control moving of solving problem
		y=150+PosInPeg[i]*30;
		size=40+i*40;
		setfillstyle(SOLID_FILL,BLACK);//control the back ground format may solid or if hatch it will be cut in to small squares and the bar colors
		Box(x,y,x+size,y+YSize);
	}
}
void MoveDisk(int Disk,int from, int to){
	int x,y,size=Disk*40,tx,ty;
	x=5+(DiskIsIn[Disk-1]*215)+((5-Disk)*20);
	y=150+PosInPeg[Disk-1]*30;
	do{
		setfillstyle(SOLID_FILL,WHITE);//default color of tall area
		bar(x,y,x+size,y+YSize);
		y-=30;
		setfillstyle(SOLID_FILL,GRAY_BRUSH);
		Box(x,y,x+size,y+YSize);
		if(IsManual) getch();
		else delay(0);// control the speed of moving objects
	}while(y>60);
	tx=5+(to*215)+((5-Disk)*20);
	do{
		setfillstyle(SOLID_FILL,PURGE_RXABORT);//color of wide area during moving bars in it
		bar(x,y,x+size,y+YSize);
		if(tx<x) x-=43; else x+=43;
		setfillstyle(SOLID_FILL,RED);//control color of bars in wide area
		Box(x,y,x+size,y+YSize);
		if(IsManual) getch();
		else delay(DELAY);
	}while(x!=tx);
	PosInPeg[Disk-1]=n-1-DiskCount[to];
	DiskCount[to]++;
	DiskCount[from]--;
	DiskIsIn[Disk-1]=to;
	ty=150+PosInPeg[Disk-1]*30;
	do{
		setfillstyle(SOLID_FILL,WHITE);//color of tall area itself
		bar(x,y,x+size,y+YSize);
		y+=30;
		setfillstyle(SOLID_FILL,RED);//control color of bars in tall area during moving bars in it
		Box(x,y,x+size,y+YSize);
		if(IsManual) getch();
		else delay(DELAY);
	}while(y<ty);
}
void Towers(int n,int from,int to,int aux){
	if(n==1){
		MoveDisk(1,from,to);
		return;
	}
	Towers(n-1,from,aux,to);
	MoveDisk(n,from,to);
	Towers(n-1,aux,to,from);
}
int main(){
	int i;
	do{	printf("\nEnter no. of disks : ");
		cin>>n;
	}while((n<1)&&(n>4));
	DELAY=(6-n)*100;//program won't work
	SetMode();
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	setbkcolor(LIGHTGRAY);
	cleardevice();//clears the screen in graphics mode and sets the current position to (0,0)
	setfillstyle(SOLID_FILL,BLACK);//border of press any key and towers of hanoi
	Box(150,13,490,33,0);
	Box(160,324,480,346,0);
	setcolor(WHITE);
	outtextxy(181,11,"T o w e r s   o f    H a n o i");//function takes coordinate of  points x ,y axis and statement to show
	outtextxy(206,322,"Press any key to S T O P");
	DiskCount[0]=n;
	DiskCount[1]=0;
	DiskCount[2]=0;
	for(i=0;i<n;i++){	PosInPeg[i]=i; DiskIsIn[i]=0; }
	DrawHanoi(n);
	Towers(n,0,2,1);
	getch();
	closegraph();//closes the graphics mode and deallocates all memory allocated by
	return 0;
}
