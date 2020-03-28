#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <graphics.h>
#include<windows.h>
#include<MMSystem.h>
#include<dos.h>
#include<string.h>
#include<conio.h>
#include<fstream>
#include <winbgim.h>
#include <cstdio>
#include <cstring>
using namespace std;
ifstream fin("evaluare.in");
#define LMAX 2
char operatori[4][4] = { "+-", "*/%", "^", "" };
int DIMENSIUNE=0;
#define DIMENSIUNE 1000
char text[200];
char S[DIMENSIUNE ], *p;
int nivelMax, distantaYnivele;

struct node {
	int val;
	char operatori;
	node *left, *right;

	node( int a = 0, char b = 0, node *c = 0, node *d = 0 ) :
		val(a), operatori(b), left(c), right(d) {}
} *A;

node *expr( int lev, int nivel ) {
	node *x, *y;
	if ( nivel > nivelMax ) nivelMax = nivel;

	if( lev == LMAX )
		if( *p == '(' )
			++p, x = expr(0, nivel++), ++p;
		else
			for( x = new node(); *p >= '0' && *p <= '9' ; ++p )
				x->val = x->val * 10 + *p - '0';
	else
		for( x = expr( lev+1, nivel++ ); strchr( operatori[lev], *p ); x = y )
			y = new node( 0, *p++, x, expr( lev+1, nivel++ ) );
	return x;
}
int maxDepth(node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* calculeaza adancimea fiecarui subarbore */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
void afisare(struct node *n, int x, int y, int nivel)
{int RAZA=15;
setcolor(11);
setlinestyle(2,USERBIT_LINE,1);
    if ( n )
    {
            if ( n -> operatori == '+' ||
                 n -> operatori == '-' ||
                 n -> operatori == '*' ||
                 n -> operatori == '/' ||
                 n -> operatori == '%' ||
                 n -> operatori == '^'
               ) { printf("%c", n -> operatori);
               rectangle(x-RAZA, y-RAZA, x+RAZA,y+RAZA);
               bgiout << n -> operatori;
               outstreamxy(x-5, y-5); } //patrat cu operator

            else { printf("%d", n -> val);
            //raza cercului se schimba in functie de valoarea din nod
            if((n->val) > 9)
                RAZA=20;
             if((n->val)>99)
                RAZA=25;
            if((n->val)>999)
                RAZA=30;


        circle(x, y, RAZA);
        bgiout << n -> val;
        outstreamxy(x-RAZA/2, y-10); } //cerc cu valoare numerica

            int distanta = 1280 / (( 1 << ( nivel + 1 )) + 1 ) / 2; //jumate din distanta dintre nodurile de pe nivelul urmator

            //daca unul dintre subarbori este mai mare
            //atunci nu mai impartim spatiul in jumatate pentru a evita suprapunerile
            if((maxDepth(n->left)>maxDepth(n->right))||(maxDepth(n->left)<maxDepth(n->right))){
                    if (n -> left)
            {
                afisare(n -> left, x - distanta/2, y + distantaYnivele, nivel+1);
                line(x, y + RAZA, x - distanta/2, y + distantaYnivele - RAZA);
            }
             if (n -> right)
            {
                afisare(n -> right, x + 3*distanta/2, y + distantaYnivele, nivel+1);
                line(x, y + RAZA, x + 3*distanta/2, y + distantaYnivele - RAZA);
            }}

            // daca subarborii sunt egali se pastreaza regula impartirii egale a spatiului
            if(maxDepth(n->left)==maxDepth(n->right)){
                    if (n -> left)
            {
                afisare(n -> left, x - distanta, y + distantaYnivele, nivel+1);
                line(x, y + RAZA, x - distanta, y + distantaYnivele - RAZA);
            }
             if (n -> right)
            {
                afisare(n -> right, x + distanta, y + distantaYnivele, nivel+1);
                line(x, y + RAZA, x + distanta, y + distantaYnivele - RAZA);
            }}
    }
}

int eval( node *n ) {
	switch( n->operatori ) {
		case '+': return eval( n->left ) + eval( n->right );
		case '-': return eval( n->left ) - eval( n->right );
		case '*': return eval( n->left ) * eval( n->right );
		case '/': return eval( n->left ) / eval( n->right );
		case '%': return eval( n->left ) % eval( n->right );
		default: return n->val;
	}
}
//rezolutia ecranului
DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
int wid1 = initwindow(screenWidth, screenHeight, "Vizualizator de arbori");


void drawStartButton(){
     setcolor(11);
		 setlinestyle(0, 1, 3);
		 line(540, 310, 660, 310);
		 line(540, 370, 660, 370);
		 arc(540, 340, 90, 270, 30);
		 arc(660, 340, 270, 90, 30);

		 char* textstring1 = "START";
		 int text_w = textwidth(textstring1);
		 int text_h = textheight(textstring1);
		 int rect_w = 660 - 540;
		 int rect_h = 370 - 310;
		 int x1 = 540 + (rect_w - text_w) / 2;
		 int y1 = 310 + (rect_h - text_h) / 2;
		 outtextxy(x1, y1, textstring1);
		 settextstyle(3, HORIZ_DIR, 2);
}

void drawSettingsButton(){
 char* textstring2 = "Settings";
		 int text_w2 = textwidth(textstring2);
		 int text_h2 = textheight(textstring2);
		 int rect_w2 = 660 - 540;
		 int rect_h2 = 490 - 430;
		 int x2 = 540 + (rect_w2 - text_w2) / 2;
		 int y2 = 430 + (rect_h2 - text_h2) / 2;
		 outtextxy(x2, y2, textstring2);
		 settextstyle(3, HORIZ_DIR, 2);}

void drawHelpButton(){
char* textstring3 = "?";
		 int text_w3 = textwidth(textstring3);
		 int text_h3 = textheight(textstring3);
		 int x3 = 600 - (20 - text_w3) / 2;
		 int y3 = 520 - 20 + text_h3 / 2;
		 circle(600, 520, 20);
		 outtextxy(x3, y3, textstring3);
}
//Functia functioneaza insa variabila text nu poate fi
//transmisa corect catre *p astfel incat arborele
//sa fie afisat corespunzator
void citesteInModGrafic(char text[200], int x, int y, int culoareFundal, int culoareText)
{
    char tasta, sir[2];
    sir[1]='\0';
    char text_[200];
    strcpy(text,"");
    strcpy(text_,"_");
    setcolor(culoareText);
    outtextxy(x,y,text_);
    do
    {
        tasta=getch();
        if (tasta==8 && strlen(text)>0)
        {
            strcpy(text_,text);
            strcat(text_,"_");
            setcolor(culoareFundal);
            outtextxy(x,y,text_);
            text[strlen(text)-1]='\0';
            strcpy(text_,text);
            strcat(text_,"_");
            setcolor(culoareText);
            outtextxy(x,y,text_);
        }
        if (tasta>=32 && tasta<=127)
        {
            strcpy(text_,text);
            strcat(text_,"_");
            setcolor(culoareFundal);
            outtextxy(x,y,text_);
            text_[strlen(text_)-1]='\0';
            sir[0]=tasta;
            setcolor(culoareText);
            strcat(text,sir);
            strcpy(text_,text);
            strcat(text_,"_");
            outtextxy(x,y,text_);
        }
    }
    while (tasta!=13 && tasta!=27);
    setcolor(culoareFundal);
    outtextxy(x,y,text_);
    if (tasta==27) strcpy(text,"");
}
void drawBack() {
	//desenam o sageata
	//coordonatele varfurilor se calculeaza cu formule matematice elementare aplicate in triunghi/dreptunghi

	int arrow[16]={500,500,545,545,545,515,635,515,635,485,545,485,545,455,500,500};
	setcolor(RED);
	drawpoly(8, arrow);
	setfillstyle(1, 11);
	fillpoly(8, arrow);

}
void drawTextBox(){
  int  left =200;
   int top = 250;
   int right = 500;
   int bottom = 280;
   /* draw a rectangle */
   rectangle(left,top,right,bottom);
}
void drawEnterButton(){
    ellipse(580,265,0,360,38,18);
    settextstyle(3,HORIZ_DIR,1);
    outtextxy(552,255,"ENTER");
}
void backToMain() {
	closegraph(CURRENT_WINDOW);
	setcurrentwindow(wid1);
}
void enterButton(){

                int wid5 = initwindow(screenWidth, screenHeight, "Vizualizator de arbori");
	            setcurrentwindow(wid5);
	            freopen("evaluare.in","r",stdin);
	            fgets( S, DIMENSIUNE, stdin ), p = S;
	            A = expr( 0, 1 );
      distantaYnivele = screenHeight / (nivelMax) ;
       afisare( A , screenWidth/2, 30, 0 );
            int rez=eval(A);
	            bgiout<<"The final result is:"<<rez;
	           outstreamxy(50,50);
	           settextstyle(3,HORIZ_DIR,3);

}
void startButton() {
    //closegraph(CURRENT_WINDOW);
	int wid2 = initwindow(screenWidth, screenHeight, "Vizualizator de arbori");
	setcurrentwindow(wid2);
	drawBack();
	settextstyle(3, HORIZ_DIR, 2);
	setcolor(11);
	outtextxy(200,200,"Introdu in fisier o expresie algebrica:");
	drawTextBox();
	drawEnterButton();
	int x,y;
	int ok=0;
	do{
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            //cout<<x<<endl<<y<<endl;
            if((x>=500)&&(x<=636)&&(y>=450)&&(y<=545))
                        {backToMain();
                        ok=1;}
            if((x>=200)&&(x<=500)&&(y>=250)&&(y<=280)){
                        double a;


    citesteInModGrafic(text,210,255, BLACK,WHITE);
    a=atof(text);
            }
            //cout<<x<<endl<<y<<endl;
    if((x>=540)&&(x<=620)&&(y>=245)&&(y<=285))
            {
                ok=1;
                //cout<<"true";
                enterButton();}
       } clearmouseclick(WM_LBUTTONDOWN);
	}while(ok==0);

}

void settingsButton() {
    //closegraph(CURRENT_WINDOW);
	int wid3 = initwindow(screenWidth, screenHeight, "Vizualizator de arbori");
	setcurrentwindow(wid3);
	drawBack();
	settextstyle(3,HORIZ_DIR,0);
	setcolor(11);
	outtextxy(50,100,"Sound");
	outtextxy(280,100,"On");
	outtextxy(360,100,"/");
	outtextxy(400,100,"Off");


	int x,y;
	int ok=0;
	do{
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            //cout<<x<<endl<<y<<endl;
            if((x>=500)&&(x<=636)&&(y>=450)&&(y<=545))
                        {backToMain();
                        ok=1;}
                        //On/Off muzica de fundal
            if((x>=400)&&(x<=500)&&(y>=80)&&(y<=120))
                PlaySound(NULL,0,0);
            if((x>=280)&&(x<=360)&&(y>=80)&&(y<120))
                 PlaySound("sound.wav",NULL,SND_FILENAME | SND_LOOP | SND_ASYNC);
                }
                        }while(ok==0);

}
void helpButton() {
	int wid4 = initwindow(screenWidth/1.5, screenHeight/3, "Help",0,0,0,0);
	setcurrentwindow(wid4);
	settextstyle(8,HORIZ_DIR,1);
	setcolor(11);
	outtextxy(20,10,"Instructions:");
	outtextxy(20,40,"To enter any algebraic equations, use the text file provided.");
	circle(10,50,5);
	outtextxy(20,60,"Then press the start, respectively enter buttons.");
	circle(10,70,5);
	outtextxy(20,80,"If you ever want to go back, use the back button.");
	circle(10,90,5);
	outtextxy(20,100,"Use the settings option in order to turn the sound on/off.");
	circle(10,110,5);
	outtextxy(20,120,"At the end, close the window and try with as many equations as you wish.");
	circle(10,130,5);
	outtextxy(20,140,"To close the help window, just click anywhere in this window.");
	circle(10,150,5);
	}



int main() {
    PlaySound("sound.wav",NULL,SND_FILENAME | SND_LOOP | SND_ASYNC);//muzica de fundal
	 int k = 1;
	 int x=0,y=0;
	 while (k) {
		 //putpixel(rand() % screenWidth, rand() % (screenHeight/3), rand() % 15);
		 //delay(10);
		drawStartButton();
		drawSettingsButton();
		drawHelpButton();
		 setlinestyle(1, 1, 3);
		 line(0, 660, 1280, 660);
		 line(0, 670, 1280, 670);
		 int ok=0;
		 do{
             putpixel(rand() % screenWidth, rand() % screenHeight, rand() % 15);
		 delay(10);
		 if (ismouseclick(WM_LBUTTONDOWN))
		 {
				 getmouseclick(WM_LBUTTONDOWN, x, y);
				 if ((x >= 540) && (x <= 660) && (y >= 310) && (y <= 370))
				 {
					k = 0;
					 startButton();
					 k = 1;

				 }
				 else if ((x >= 540) && (x <= 660) && (y >= 430) && (y <= 490))
				 {
					 k = 0;
					 settingsButton();
					 k = 1;
				 }
				 else if( (x>=580)&&(x<=620)&&(y>=500)&&(y<=540))

				 {
					 k = 0;
					 helpButton();
					 while (!ismouseclick(WM_LBUTTONDOWN))
						 delay(50);
					 getmouseclick(WM_LBUTTONDOWN, x, y);
					 backToMain();
					 k = 1;
				 }
		 }

		 }while(ok==0);
	 }
	getch();
	closegraph();
	return 0;
	 }
