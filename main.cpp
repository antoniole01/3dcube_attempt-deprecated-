#include <iostream>
#include <math.h>

#include <sdl.h>
#include <sdl_ttf.h>

#include "c:\z\_MI\Window.h"
#include "c:\z\_MI\defines.h"
#include "c:\z\_MI\colors.h"
#include "c:\z\_MI\drawshapes.h"

#undef main

SDL_Renderer*  renderer;
SDL_Window*    window;
SDL_Event      e;

SDL_Texture*	solidTexture;
SDL_Texture*	text;
SDL_Rect			solidRect;
TTF_Font*		gFont;

struct Vertice
{
	double x,y,z;
};

struct V3
{
	int x,y,z;
};

struct Rect
{
	int x, y, w, h;
};

float FPS =    1000/33.3f;

bool running = true;

void drawLine2(int nx1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	int   dx = x2 - nx1;
	int   dy = y2 - y1;

	if( abs( dy ) > abs( dx ) )
	{
#pragma warning(disable:4244)

		if( y1 > y2 )
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			temp = x2;
			x2 = nx1;
			nx1 = temp;
		}
		
		
		float m = (float)dx / (float)dy;
		float bb = nx1 - m * y1;
		for(int y = y1; y < y2; y++)
		{
			int x = m * y + bb + 0.5;
			drawPoint(x,y,r,g,b,a);
		}
	}
	else
	{
		if( nx1 > x2 )
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			temp = x2;
			x2 = nx1;
			nx1 = temp;
		}

		float m  = (float)dy / (float)dx;
		float bb = y1 - m * nx1;
		for(int x = nx1; x < x2; x++)
		{
			int y = m * x + bb + 0.5;
			drawPoint(x,y,r,g,b,a);
		}
	}
}

void cubepointreference()
{
	int center = 300;
	drawPoint( center      , center      , RED);
	
	drawPoint( center - 50 , center      , RED);
	drawPoint( center + 50 , center      , RED);
	drawPoint( center      , center - 50 , RED);
	drawPoint( center      , center + 50 , RED);
	
	drawPoint( center - 50 , center - 50 , RED);	
	drawPoint( center + 50 , center - 50 , RED);	
	drawPoint( center - 50 , center + 50 , RED);	
	drawPoint( center + 50 , center + 50 , RED);	
}

void linerect()
{

	static int pivot = 300;
	static int w = 50 * 2;
	static int h = 50 * 2;
	// 1 0
	// 2 0.775
	// 3 1.56
	// 4 2.35
	// 5 3.15
	// 6 3.95
   //-2 -0.774
	//-3 -1.53
	//-4 -2.35
	//-5 -3.15
	static double angle1x = -2.35;
	static double angle1y = -2.35;
	static double angle2x =  2.35;
	static double angle2y =  2.35;
	
	static double angle3x = -0.774;
	static double angle3y = -0.774;
	static double angle4x =  0.774;
	static double angle4y =  0.774;
	
	static double angle5x = -0.774;
	static double angle5y = -0.774;
	static double angle6x = -2.35;
	static double angle6y = -2.35;
	
	static double angle7x =  2.35;
	static double angle7y =  2.35;
	static double angle8x =  0.774;
	static double angle8y =  0.774;
	static int pivotpoint = 0;
	
	static int x = 0;
	static int y = 0;
	static int z = 0;

	static int radius = 72;
	static int value = 72;
	static double size1 = 0.0;
	static double size2 = 0.0;

	static int xpos = 0;
	static int ypos = 0;
	
	//front
	drawLine2( ( pivot + xpos ) + sin( angle1x - size1 ) * radius,//top
				  ( pivot        ) + cos( angle1y + size2 ) * radius,
				  ( pivot + xpos ) + sin( angle2x - size1 ) * radius,
				  ( pivot        ) + cos( angle2y + size2 ) * radius,WHITE);
	
	drawLine2( ( pivot + xpos ) + sin( angle3x + size1 ) * radius,//bottom
				  ( pivot        ) + cos( angle3y - size2 ) * radius,
				  ( pivot + xpos ) + sin( angle4x + size1 ) * radius,
				  ( pivot        ) + cos( angle4y - size2 ) * radius,WHITE);
	
	drawLine2( ( pivot + xpos ) + sin( angle5x + size1 ) * radius,//left
				  ( pivot        ) + cos( angle5y + size2 ) * radius,
				  ( pivot + xpos ) + sin( angle6x - size1 ) * radius,
				  ( pivot        ) + cos( angle6y - size2 ) * radius,WHITE);
	
	drawLine2( ( pivot + xpos ) + sin( angle7x - size1 ) * radius,//right
				  ( pivot        ) + cos( angle7y - size2 ) * radius,
				  ( pivot + xpos ) + sin( angle8x + size1 ) * radius,
				  ( pivot        ) + cos( angle8y + size2 ) * radius,WHITE);

	//back
	drawLine2( ( pivot - xpos ) + sin( angle1x + size1 ) * radius,//top
				  ( pivot        ) + cos( angle1y - size2 ) * radius,
				  ( pivot - xpos ) + sin( angle2x + size1 ) * radius,
				  ( pivot        ) + cos( angle2y - size2 ) * radius,WHITE);
	
	drawLine2( ( pivot - xpos ) + sin( angle3x - size1 ) * radius,//bottom
				  ( pivot        ) + cos( angle3y + size2 ) * radius,
				  ( pivot - xpos ) + sin( angle4x - size1 ) * radius,
				  ( pivot        ) + cos( angle4y + size2 ) * radius,WHITE);
	
	drawLine2( ( pivot - xpos ) + sin( angle5x - size1 ) * radius,//left
				  ( pivot        ) + cos( angle5y - size2 ) * radius,
				  ( pivot - xpos ) + sin( angle6x + size1 ) * radius,
				  ( pivot        ) + cos( angle6y + size2 ) * radius,WHITE);
	
	drawLine2( ( pivot - xpos ) + sin( angle7x + size1 ) * radius,//right
				  ( pivot        ) + cos( angle7y + size2 ) * radius,
				  ( pivot - xpos ) + sin( angle8x - size1 ) * radius,
				  ( pivot        ) + cos( angle8y - size2 ) * radius,WHITE);

	
	//left
	drawLine2( ( pivot        ) + sin( angle1x - size1 ) * radius,//top back
				  ( pivot + xpos ) + cos( angle1y + size2 ) * radius,
				  ( pivot        ) + sin( angle2x - size1 ) * radius,
				  ( pivot + xpos ) + cos( angle2y + size2 ) * radius,ORANGE);
	
	drawLine2( ( pivot        ) + sin( angle1x + size1 ) * radius,//front
				  ( pivot + xpos ) + cos( angle1y - size2 ) * radius,
				  ( pivot        ) + sin( angle2x + size1 ) * radius,
				  ( pivot + xpos ) + cos( angle2y - size2 ) * radius,ORANGE);
	
	drawLine2( ( pivot        ) + sin( angle1x + size1 ) * radius,//left
				  ( pivot + xpos ) + cos( angle1y + size2 ) * radius,
				  ( pivot        ) + sin( angle2x - size1 ) * radius,
				  ( pivot + xpos ) + cos( angle2y - size2 ) * radius,ORANGE);
	
	drawLine2( ( pivot        ) + sin( angle1x - size1 ) * radius,//right
				  ( pivot + xpos ) + cos( angle1y - size2 ) * radius,
				  ( pivot        ) + sin( angle2x + size1 ) * radius,
				  ( pivot + xpos ) + cos( angle2y + size2 ) * radius,ORANGE);

	//right
	drawLine2( ( pivot        ) + sin( angle5x + size1 ) * radius,//top
				  ( pivot + xpos ) + cos( angle5y - size2 ) * radius,
				  ( pivot        ) + sin( angle8x + size1 ) * radius,
				  ( pivot + xpos ) + cos( angle8y - size2 ) * radius,CYAN);
	
	drawLine2( ( pivot        ) + sin( angle5x - size1 ) * radius,//bottom
				  ( pivot + xpos ) + cos( angle5y + size2 ) * radius,
				  ( pivot        ) + sin( angle8x - size1 ) * radius,
				  ( pivot + xpos ) + cos( angle8y + size2 ) * radius,CYAN);
	
	drawLine2( ( pivot        ) + sin( angle5x - size1 ) * radius,//left
				  ( pivot + xpos ) + cos( angle5y - size2 ) * radius,
				  ( pivot        ) + sin( angle8x + size1 ) * radius,
				  ( pivot + xpos ) + cos( angle8y + size2 ) * radius,CYAN);
	
	drawLine2( ( pivot        ) + sin( angle5x + size1 ) * radius,//right
				  ( pivot + xpos ) + cos( angle5y + size2 ) * radius,
				  ( pivot        ) + sin( angle8x - size1 ) * radius,
				  ( pivot + xpos ) + cos( angle8y - size2 ) * radius,CYAN);
	
	cubepointreference();

	size2 = -0.20;
	
	if(SC_LEFT)
	{
		size1 -= 0.01;
		size2 += 0.01;
	}

	if(SC_RIGHT)
	{
		size1 += 0.01;
		size2 -= 0.01;
	}
	
	// if(SC_LEFT)
	// {
	// 	radius += 1;
	// }
	
	// // x y intensity
	// if(SC_LEFT)
	// {
	// 	angle1x -= 0.1;
	// 	angle2x -= 0.1;
	// }
	
	// // pivot point
	// if(SC_LEFT) {xpos += 2;}

	// //size
	// if(SC_LEFT) {radius -= 1;}
	// if(SC_RIGHT){radius += 1;}
	
	bool rotating = false;

	bool sizerot = false;
	if(!SC_SPACE){sizerot = true;}
	if(sizerot){size1 += 0.1;}
	
	// size2 += 0.01;
	// size2 -= 0.01;
	
	if(rotating)
	{
		angle1x += 0.1;
		angle1y += 0.1;
		angle2x += 0.1;
		angle2y += 0.1;
	
		angle3x += 0.1;
		angle3y += 0.1;
		angle4x += 0.1;
		angle4y += 0.1;
	
		angle5x += 0.1;
		angle5y += 0.1;
		angle6x += 0.1;
		angle6y += 0.1;
	
		angle7x += 0.1;
		angle7y += 0.1;
		angle8x += 0.1;
		angle8y += 0.1;
	}	
}

void cubefoldingonitself()
{

	static double angle = 0.0;
	
	//NOTE: can't rotate shape
	drawFillRect( ( 300 - 50 ) + sin( angle ) * -50,
					  ( 300 - 50 ) + cos( angle ) * -50,
					  sin ( angle ) * 100,
					  cos ( angle ) * 100,
					  BLUE);
	angle += 0.1;
}

void cubefrontplane()
{
	V3 v[7] = {300,300,300};//xyz
	
	Rect r = {300,300,50,50};//xywh
	
	static double a1 = 0.0;  //0 - 1.57 - 3.15 - 4.72
	static double a2 = 1.58;
	static double a3 = 0.8;
	static double a4 = 3.2;
	

	static double orig = 50;
	static double radx = 50;
	static double rady = 50;

	static int posx = r.x;
	static int posy = r.y;
	
	drawLine(posx-r.w, posy-r.h,r.w*2,0,BLUE);
	
	drawLine(posx-r.w, posy+r.h, r.w*2,0,BLUE);
	drawLine(posx-r.w, posy-r.h, 0,r.h*2,BLUE);
	drawLine(posx+r.w, posy-r.h, 0,r.h*2,BLUE);

	
	drawPoint(r.x,r.y,RED);//c
	
	drawPoint(posx,    posy-r.h,YELLOW);//t
	drawPoint(r.x,     r.y+r.h,YELLOW);//b
	drawPoint(r.x+r.w, r.y,YELLOW);//l
	drawPoint(r.x-r.w, r.y,YELLOW);//r
	
	drawPoint(r.x-r.w, r.y-r.h,GREEN);//tl
	drawPoint(r.x+r.w, r.y-r.h,GREEN);//tr
	drawPoint(r.x+r.w, r.y+r.w,GREEN);//bl
   drawPoint(r.x-r.w, r.y+r.w,GREEN);//br

	static double anglespeed = 0.1;
	
	a1 += anglespeed;
	a2 += anglespeed;
	a3 += anglespeed;
	a4 += anglespeed;
	
	if(SC_UP)   {a1+=0.01;}
	if(SC_DOWN) {a1-=0.01;}
	if(SC_LEFT) {r.h+=1;}
	if(SC_RIGHT){r.h-=1;}
	
}

void rotating_cube_zero_origin()
{
	static Rect r = {300,300,100,100};

	static double ang1 = 0.0;
	static double ang2 = 1.58;
	static double ang3 = 0.0;
	static double ang4 = 1.58;
	
	static double kspeed = 10;
	
	if(SC_LEFT) {r.x -= kspeed;}
	if(SC_RIGHT){r.x += kspeed;}
	if(SC_UP)   {r.y -= kspeed;}
	if(SC_DOWN) {r.y += kspeed;}

	//        x                  y                  w              h              c
	drawLine( r.x,               r.y,               sin(ang1)*r.w, cos(ang1)*r.w, BLUE  );//l
	drawLine( r.x,               r.y,               sin(ang2)*r.w, cos(ang2)*r.w, BLUE  );//t
	drawLine( r.x+sin(ang4)*r.w, r.y+cos(ang4)*r.w, sin(ang3)*r.w, cos(ang3)*r.w, BLUE  );//r
	drawLine( r.x+sin(ang3)*r.w, r.y+cos(ang3)*r.w, sin(ang4)*r.w, cos(ang4)*r.w, BLUE  );//b
	
	double speed = 0.01;
	
	drawPoint(r.x,r.y,RED);
	drawPoint(r.x+r.w,r.y,YELLOW);// w
	drawPoint(r.x,r.y+r.h,YELLOW);//-h
	drawPoint(r.x-r.w,r.y,YELLOW);//-w
	drawPoint(r.x,r.y-r.h,YELLOW);// h
	
	ang1 += speed;
	ang2 += speed;
	ang3 += speed;
	ang4 += speed;
}

void rotating_cube_attemp()
{
	Vertice v = {300,300,10};

	int w=50.0;
	int h=50.0;
	
	static double ang1 = 0.0;
	static double ang2 = 1.58;
	static double ang3 = 0.8;
	static double ang4 = 3.2;
	
	// CYAN
	drawLine( v.x+v.z,               v.y+v.z,           sin(ang1)*w, cos(ang1)*w, CYAN  );
	drawLine( v.x+v.z,               v.y+v.z,           sin(ang2)*w, cos(ang2)*w, CYAN  );
	drawLine( v.x+v.z+sin(ang1)*w, v.y+v.z+cos(ang1)*w, sin(ang2)*w, cos(ang2)*w, CYAN  );
	drawLine( v.x+v.z+sin(ang2)*w, v.y+v.z+cos(ang2)*w, sin(ang1)*w, cos(ang1)*w, CYAN  );

	// ORANGE
	drawLine( v.x+sin(ang1),       v.y+cos(ang1), sin(ang1)*w, cos(ang1)*w, ORANGE  );
	drawLine( v.x+sin(ang2),       v.y+cos(ang2), sin(ang2)*w, cos(ang2)*w, ORANGE  );
	drawLine( v.x+v.z+sin(ang3)*w, v.y+v.z+cos(ang3)*w, sin(ang4)*w, cos(ang4)*w, ORANGE  );
	drawLine( v.x+v.z+sin(ang4)*w, v.y+v.z+cos(ang4)*w, sin(ang3)*w, cos(ang3)*w, ORANGE  );

	double speed = 0.01;
	ang1 += speed;
	ang2 += speed;
	ang3 += speed;
	ang4 += speed;

}

void rotating_cube_center_origin()
{
	#pragma warning(disable:4244)
	
	Vertice v = {300,300,10};

	int w=50.0;
	int h=50.0;
	
	static double ang1 = 0.0;
	static double ang2 = 1.58;
	static double ang3 = 0.8;
	static double ang4 = 3.2;

	int orig = 0;
	
	static double valx = 0.0, valy = 0.0;
	
	if(SC_UP)    {valy -= 0.15;}
	if(SC_DOWN)  {valy += 0.15;}
	if(SC_LEFT)  {valx -= 0.15;}
	if(SC_RIGHT) {valx += 0.15;}

	//drawLine( x+z, y+z, x+z+w, y+z+w)
	
	drawLine( v.x + (sin(ang1)*(w)),
				 v.y + (cos(ang1)*(w)),
				        sin(ang2)*(w),
				        cos(ang2)*(w),
				 ORANGE  );
	
	drawLine( v.x+(sin(ang2)*w),
				 v.y+(cos(ang2)*w),
				 sin(ang1)*w,
				 cos(ang1)*w,
				 BLUE  );
	drawLine( v.x+(-sin(ang1)*w),
				 v.y+(-cos(ang1)*w),
				 -sin(ang2)*w,
				 -cos(ang2)*w,
				 BLUE  );
	drawLine( v.x+(-sin(ang2)*w),
				 v.y+(-cos(ang2)*w),
				 -sin(ang1)*w,
				 -cos(ang1)*w,
				 BLUE  );
	
	drawPoint(      v.x,   v.y, RED);   //c
	drawPoint(    v.x+w,   v.y, YELLOW);//r
	drawPoint(      v.x, v.y+w, YELLOW);//b
	drawPoint(    v.x-w,   v.y, YELLOW);//l
	drawPoint(      v.x, v.y-w, YELLOW);//t
	
	drawPoint(    v.x+w, v.y+w, YELLOW);//br
	drawPoint(    v.x-w, v.y+w, YELLOW);//bl
	drawPoint(    v.x-w, v.y-w, YELLOW);//tl
	drawPoint(    v.x+w, v.y-w, YELLOW);//tr

	double speed = 0.01;
	ang1 += speed;
	ang2 += speed;
	ang3 += speed;
	ang4 += speed;
}

void lineindicator(int x,int y, int w, int h, Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	drawLine2(x,y,w,h,r,g,b,a);
	drawPoint(x,y,RED);
	drawPoint(w,h,YELLOW);
}

void linear_rotating_line(int x, int y, int rx, int ry)
{
	lineindicator(x,y,x+(int)(rx),y+(int)(ry),ORANGE);
}

void linear_rotating_line_update(double &rx, double &ry, bool &rxs, bool &rys)
{
	if(rxs)
	{
		rx += 1.0;
		if(rx > 50)
		{
			rxs = false;
		}
	}
	else
	{
		rx -= 1.0;
		if(rx < -50)
		{
			rxs = true;
		}
	}
	
	if(rys)
	{
		ry += 1.0;
		if(ry > 50)
		{
			rys = false;
		}
	}
	else
	{
		ry -= 1.0;
		if(ry < -50)
		{
			rys = true;
		}
	}
}

void circle_line_notation()
{
	int x = 300, y = 300, w = 50, h = 50;
	
	static double rx = 0;
	static double ry = 50;
	
	static bool rxs = true;
	static bool rys = true;
	
	//(w/2)+9, (h/2)+9
	lineindicator(x,y,x+-45,y+ 17,BLUE);
	lineindicator(x,y,x+-48,y+  9,BLUE);
	lineindicator(x,y,x+-49,y+  5,BLUE);
	lineindicator(x,y,x+-50,y+  3,BLUE);
	
	  lineindicator(x,y,x+-50,y+  0,YELLOW);
	
	lineindicator(x,y,x+-50,y+ -3,BLUE);
	lineindicator(x,y,x+-49,y+ -5,BLUE);
	lineindicator(x,y,x+-48,y+ -9,BLUE);
	lineindicator(x,y,x+-45,y+-17,BLUE);

	  lineindicator(x,y,x+-34,y+-34,CYAN);
	
	lineindicator(x,y,x+-17,y+-45,BLUE);
	lineindicator(x,y,x+ -9,y+-48,BLUE);
	lineindicator(x,y,x+ -5,y+-49,BLUE);
	lineindicator(x,y,x+ -3,y+-50,BLUE);
	
	lineindicator(x,y,x+  0,y+-50,YELLOW);

	lineindicator(x,y,x+  3,y+-50,BLUE);
	lineindicator(x,y,x+  5,y+-49,BLUE);
	lineindicator(x,y,x+  9,y+-48,BLUE);
	lineindicator(x,y,x+ 17,y+-45,BLUE);
	
	  lineindicator(x,y,x+ 34,y+-34,CYAN);
	
	lineindicator(x,y,x+ 45,y+-17,BLUE);
	lineindicator(x,y,x+ 48,y+ -9,BLUE);
	lineindicator(x,y,x+ 49,y+ -5,BLUE);
	lineindicator(x,y,x+ 50,y+ -3,BLUE);
	
	lineindicator(x,y,x+ 50,y+  0,YELLOW);
	
	lineindicator(x,y,x+ 50,y+  3,BLUE);
	lineindicator(x,y,x+ 49,y+  5,BLUE);
	lineindicator(x,y,x+ 48,y+  9,BLUE);
	lineindicator(x,y,x+ 45,y+ 17,BLUE);
	
	  lineindicator(x,y,x+ 34,y+ 34,CYAN);
	
	lineindicator(x,y,x+ 17,y+ 45,BLUE);
	lineindicator(x,y,x+  9,y+ 48,BLUE);
	lineindicator(x,y,x+  5,y+ 49,BLUE);
	lineindicator(x,y,x+  3,y+ 50,BLUE);
	
	  lineindicator(x,y,x+  0,y+ 50,YELLOW);
	
	lineindicator(x,y,x+ -3,y+ 50,BLUE);
	lineindicator(x,y,x+ -5,y+ 49,BLUE);
	lineindicator(x,y,x+ -9,y+ 48,BLUE);
	lineindicator(x,y,x+-17,y+ 45,BLUE);
	
	  lineindicator(x,y,x+-34,y+ 34,CYAN);

	linear_rotating_line(x,y,rx,ry);
	linear_rotating_line_update(rx,ry,rxs,rys);
}

void rotating_line()
{
	#pragma warning(disable:4244)
	int lx = 300;
	int ly = 300;
	static double angle = 0.0;
	drawLine(lx,ly, sin(angle)*50,cos(angle)*50,BLUE);
	angle += 0.2;
}

void input()
{
   if(POLLEVENT)
   {
      if(QUIT){exit(0);}
      if(UPPRESS)
      {
         if(ESCAPE){exit(0);}
      }
   }
}

void cubeforloop_test()
{
	
	struct Vert
	{
		double x,y,z;
	};

#pragma warning(disable:4709)

	const int max = 4;
	//static int val[max][max][max];
	static Vert p[max][max][max] = {0};

	for(int x = -1; x <= 1; x++)
	{
		for(int y = -1; y <= 1; y++)
		{
			for(int z = -1; z <= 1; z++)
			{
				p[x][y][z].x = x;
				p[x][y][z].y = y;
				p[x][y][z].z = z;
				
			}
		}
	}

	for(int x = -1; x <= 1; x++)
	{
		for(int y = -1; y <= 1; y++)
		{
			for(int z = -1; z <= 1; z++)
			{
				printf( "x:%0.0f  y:%0.0f z:%0.0f\t\t", p[x][y][z].x, p[x][y][z].y, p[x][y][z].z );
			}
			printf("\n");
		}
		printf("\n");
	}
	
}

void draw()
{
	SDL_SetRenderDrawColor(renderer,BLACK);
	SDL_RenderClear(renderer);  

	//rotating_line();
	//circle_line_notation();
	//rotating_cube_zero_origin();
	//rotating_cube_attemp();
	//rotating_cube_center_origin();
	//cubefrontplane();
	//cubefoldingonitself();
	//drawLine2(300,300,400,400,WHITE);
	cubeforloop_test();
	
	//linerect();
	
	SDL_RenderPresent(renderer);
}
void update()
{
	
	SDL_Delay(1000/33);
}

int main()
{
	init_Window(600,200,800,600,0,1);
	
	while(running)
	{
		input();
		draw();
		update();;
	}
		
	return(0);
}

/*

3D graphics tutorial
Rotating objects
Home About
Introduction
Creating 3D objects
Drawing 3D objects
Rotating 3D objects
Generating 3D objects
My sister's handmade cards on Etsy.
Drawing of a pile of animals 
A cube rotating about its z-axis.
Rotating things in three dimensions sounds complicated and it can be, but there are some simple rotations. For example, if we imagine rotating our cube around the z-axis (which points out of the screen), we are actually just rotating a square in two dimensions.

There is a reason to learn trigonometry

Rotating a point (x, 0) around the origin by θ.
We can simplify things further, by just looking at a single node at position (x, 0). Using simple trigonometry we can find that the position of the point after rotating it by θ around the origin is (x', y'), where,

x' = x × cos(θ)
y' = x × sin(θ)
If you don't understand where these equations came from, this video might help.

Rotating a point about the origin

Rotating a point (x, y) around the origin by β.
The example above allows us to rotate a point that starts on the x-axis about the origin, but what if it isn't on the x-axis? This requires some slightly more advanced trigonometry. If we call the distance between the point (x, y) and the origin r, and the angle between the line to (x, y) and x-axis, α then,

x = r × cos(α)
y = r × sin(α)
If we rotate by β to point (x', y'), then,

x' = r × cos(α + β)
y' = r × sin(α + β)
Using the trigonometric addition equations (derived here and here), we get,

x' = r × cos(α) cos(β) - r × sin(α) sin(β)
y' = r × sin(α) cos(β) + r × cos(α) sin(β)
Substituting in the values for x and y above, we get an equation for the new coordinates as a function of the old coordinates and the angle of rotation:

x' = x × cos(β) - y × sin(β)
y' = y × cos(β) + x × sin(β)
Writing a rotate function
Now we know the mathematics, we can write a function to rotate a node, or even better, our array of nodes, around the z-axis.

var rotateZ3D = function(theta) {
    var sin_t = sin(theta);
    var cos_t = cos(theta);
    
    for (var n = 0; n < nodes.length; n++) {
        var node = nodes[n];
        var x = node[0];
        var y = node[1];
        node[0] = x * cos_t - y * sin_t;
        node[1] = y * cos_t + x * sin_t;
    }
};
A square at a jaunty angle
Our cube is slightly more interesting, but not much.
This function loops through all the nodes in the node array, finds its current x and y coordinates and then updates them. We find sin(theta) and cos(theta) outside the loop so we only need to calculate it once.

We can test the function by calling it. Try rotating the cube by 30 degrees.

rotateZ3D(30);
You can see the complete code here.

See? Trigonometry can be useful!

Rotating in three dimensions
We can now rotate our cube in two dimensions, but it still looks like a square. What if we want to rotate our cube around the y-axis (veritcal axis). If we imagine looking down on our cube as we rotate it around the y-axis, what we would see is a rotating square, just like we do when we rotate about the z-axis.

So if we imagine our relabelling our axes, so the z-axis becomes the y-axis, we can come up with a new function for rotating around the y-axis. In this case, the y-coordinates of the node do not change.

var rotateY3D = function(theta) {
    var sin_t = sin(theta);
    var cos_t = cos(theta);
    
    for (var n = 0; n < nodes.length; n++) {
        var node = nodes[n];
        var x = node[0];
        var z = node[2];
        node[0] = x * cos_t - z * sin_t;
        node[2] = z * cos_t + x * sin_t;
    }
};
And we can use the same argument to create a function that rotates our cube around the x-axis:

var rotateX3D = function(theta) {
    var sin_t = sin(theta);
    var cos_t = cos(theta);
    
    for (var n = 0; n < nodes.length; n++) {
        var node = nodes[n];
        var y = node[1];
        var z = node[2];
        node[1] = y * cos_t - z * sin_t;
        node[2] = z * cos_t + y * sin_t;
    }
};
Again, we can test the code by calling the function.

rotateX3D(30);
rotateY3D(30);
You can see the complete code here. Try using the slider to change the values in the function calls.

User interaction
A cube looking like a cube
I told you it was a cube!
We can rotate the cube by adding function calls, but it's a lot more useful (and satisfying) if we can rotate it using the mouse. For this we need to create a mouseDragged() function. This function is automatically called whenever the mouse is dragged.

var mouseDragged = function() {
    rotateY3D(mouseX - pmouseX);
    rotateX3D(mouseY - pmouseY);
};
mouseX and mouseY are built-in variables that contain the current position of the mouse. pmouseX and pmouseY are built-in variables that contain the position of the mouse in the previous frame. So if the x-coordinate has increased (we move the mouse right), we send a postive value to rotateY3D() and rotate the cube counter-clockwise around the y-axis.

You can see for yourself here.

 
This website was created by Peter Collingridge.
 */



/*

Home > Articles > Programming

Drawing and Transforming Triangles in WebGL

By Kouichi Matsuda and Rodger Lea
Aug 5, 2013
📄 Contents

␡
Drawing Multiple Points
Hello Triangle
Moving, Rotating, and Scaling
Summary
⎙ Print + Share This
< Back Page 3 of 4 Next >
This chapter is from the book 
This chapter is from the book
WebGL Programming Guide: Interactive 3D Graphics Programming with WebGLWebGL Programming Guide: Interactive 3D Graphics Programming with WebGL 

Learn More Buy
This chapter is from the book
WebGL Programming Guide: Interactive 3D Graphics Programming with WebGLWebGL Programming Guide: Interactive 3D Graphics Programming with WebGL 

Learn More Buy
Moving, Rotating, and Scaling
Now that you understand the basics of drawing shapes like triangles and rectangles, let’s take another step and try to move (translate), rotate, and scale the triangle and display the results on the screen. These operations are called transformations (affine transformations). This section introduces some math to explain each transformation and help you to understand how each operation can be realized. However, when you write your own programs, you don’t need the math; instead, you can use one of several convenient libraries, explained in the next section, that handle the math for you.

If you find reading this section and in particular the math too much on first read, it’s okay to skip it and return later. Or, if you already know that transformations can be written using a matrix, you can skip this section as well.

First, let’s write a sample program, TranslatedTriangle, that moves a triangle 0.5 units to the right and 0.5 units up. You can use the triangle you drew in the previous section. The right direction means the positive direction of the x-axis, and the up direction means the positive direction of the y-axis. (See the coordinate system in Chapter 2.) Figure 3.18 shows TranslatedTriangle.


Figure 3.18
Figure 3.18 TranslatedTriangle

Translation
Let us examine what kind of operations you need to apply to each vertex coordinate of a shape to translate (move) the shape. Essentially, you just need to add a translation distance for each direction (x and y) to each component of the coordinates. Looking at Figure 3.19, the goal is to translate the point p (x, y, z) to the point p’ (x’, y’, z’), so the translation distance for the x, y, and z direction is Tx, Ty, and Tz, respectively. In this figure, Tz is 0.

To determine the coordinates of p’, you simply add the T values, as shown in Equation 3.1.

Equation 3.1

x’ = x + Tx

y’ = y + Ty

z’ = z + Tz


Figure 3.19
Figure 3.19 Calculating translation distances

These simple equations can be implemented in a WebGL program just by adding each constant value to each vertex coordinate. You’ve probably realized already that because they are a per-vertex operation, you need to implement the operations in a vertex shader. Conversely, they clearly aren’t a per-fragment operation, so you don’t need to worry about the fragment shader.

Once you understand this explanation, implementation is easy. You need to pass the translation distances Tx, Ty, and Tz to the vertex shader, apply Equation 3.1 using the distances, and then assign the result to gl_Position. Let’s look at a sample program that does this.

Sample Program (TranslatedTriangle.js)
Listing 3.4 shows TranslatedTriangle.js, in which the vertex shader is partially modified to carry out the translation operation. However, the fragment shader is the same as in HelloTriangle.js in the previous section. To support the modification to the vertex shader, some extra code is added to the main() function in the JavaScript.

Listing 3.4 TranslatedTriangle.js
 1 // TranslatedTriangle.js
 2 // Vertex shader program
 3 var VSHADER_SOURCE =
 4   'attribute vec4 a_Position;\n' +
 5   'uniform vec4 u_Translation;\n' +
 6   'void main() {\n' +
 7   '  gl_Position = a_Position + u_Translation;\n' +
 8   '}\n';
 9
10 // Fragment shader program
    ...
16 // The translation distance for x, y, and z direction
17 var Tx = 0.5, Ty = 0.5, Tz = 0.0;
18
19 function main() {
    ...
23   // Get the rendering context for WebGL
24   var gl = getWebGLContext(canvas);
    ...
30   // Initialize shaders
31   if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    ...
34  }
35
36   // Set the positions of vertices
37   var n = initVertexBuffers(gl);
    ...
43   // Pass the translation distance to the vertex shader
44   var u_Translation = gl.getUniformLocation(gl.program, 'u_Translation');
    ...
49   gl.uniform4f(u_Translation, Tx, Ty, Tz, 0.0);
50
51   // Set the color for clearing <canvas>
    ...
57   // Draw a triangle
58   gl.drawArrays(gl.TRIANGLES, 0, n);
59 }
60
61 function initVertexBuffers(gl) {
62   var vertices = new Float32Array([
63     0.0.0, 0.5,   -0.5, -0.5,   0.5, -0.5
64   ]);
65   var n = 3; // The number of vertices
    ...
90   return n;
93 }
First, let’s examine main() in JavaScript. Line 17 defines the variables for each translation distance of Equation 3.1:

17 var Tx = 0.5, Ty = 0.5, Tz = 0.0;
Because Tx, Ty, and Tz are fixed (uniform) values for all vertices, you use the uniform variable u_Translation to pass them to a vertex shader. Line 44 retrieves the storage location of the uniform variable, and line 49 assigns the data to the variable:

44 var u_Translation = gl.getUniformLocation(gl.program, 'u_Translation');
...
49 gl.uniform4f(u_Translation, Tx, Ty, Tz, 0.0);
Note that gl.uniform4f() requires a homogenous coordinate, so we supply a fourth argument (w) of 0.0. This will be explained in more detail later in this section.

Now, let’s take a look at the vertex shader that uses this translation data. As you can see, the uniform variable u_Translation in the shader, to which the translation distances are passed, is defined as type vec4 at line 5. This is because you want to add the components of u_Translation to the vertex coordinates passed to a_Position (as defined by Equation 3.1) and then assign the result to the variable gl_Position, which has type vec4. Remember, per Chapter 2, that the assignment operation in GLSL ES is only allowed between variables of the same types:

4   'attribute vec4 a_Position;\n' +
5   'uniform vec4 u_Translation;\n' +
6   'void main() {\n' +
7   '  gl_Position = a_Position + u_Translation;\n' +
8   '}\n';
After these preparations have been completed, the rest of tasks are straightforward. To calculate Equation 3.1 within the vertex shader, you just add each translation distance (Tx, Ty, Tz) passed in u_Translation to each vertex coordinate (x, y, z) passed in a_Position.

Because both variables are of type vec4, you can use the + operator, which will actually add the four components simultaneously (see Figure 3.20). This easy addition of vectors is a feature of GLSL ES and will be explained in more detail in Chapter 6.


Figure 3.20
Figure 3.20 Addition of vec4 variables

Now, we’ll return to the fourth element, (w), of the vector. As explained in Chapter 2, you need to specify the homogeneous coordinate to gl_Position, which is a four-dimensional coordinate. If the last component of the homogeneous coordinate is 1.0, the coordinate indicates the same position as the three-dimensional coordinate. In this case, because the last component is w1+w2 to ensure that w1+w2 is 1.0, you need to specify 0.0 to the value of w (the fourth parameter of gl.uniform4f()).

Finally, at line 58, gl.drawArrays(gl.TRIANGLES, 0, n) executes the vertex shader. For each execution, the following three steps are performed:

Each vertex coordinate set is passed to a_Position.
u_Translation is added to a_Position.
The result is assigned to gl_Position.
Once executed, you’ve achieved your goal because each vertex coordinate set is modified (translated), and then the translated shape (in this case, a triangle) is displayed on the screen. If you now load TranslatedTriangle.html into your browser, you will see the translated triangle.

Now that you’ve mastered translation (moving), the next step is to look at rotation. The basic approach to realize rotation is the same as translation, requiring you to manipulate the vertex coordinates in the vertex shader.

Rotation
Rotation is a little more complex than translation because you have to specify multiple items of information. The following three items are required:

Rotation axis (the axis the shape will be rotated around)
Rotation direction (the direction: clockwise or counterclockwise)
Rotation angle (the number of degrees the shape will be rotated through)
In this section, to simplify the explanation, you can assume that the rotation is performed around the z-axis, in a counterclockwise direction, and for β degrees. You can use the same approach to implement other rotations around the x-axis or y-axis.

In the rotation, if β is positive, the rotation is performed in a counterclockwise direction around the rotation axis looking at the shape toward the negative direction of the z-axis (see Figure 3.21); this is called positive rotation. Just as for the coordinate system, your hand can define the direction of rotation. If you take your right hand and have your thumb follow the direction of the rotation axis, your fingers show the direction of rotation. This is called the right-hand-rule rotation. As we discussed in Chapter 2, it’s the default we are using for WebGL in this book.

Now let’s find the expression to calculate the rotation in the same way that you did for translation. As shown in Figure 3.22, we assume that the point p’ (x’, y’, z’) is the β degree rotated point of p (x, y, z) around the z-axis. Because the rotation is around the z-axis, the z coordinate does not change, and you can ignore it for now. The explanation is a little mathematical, so let’s take it a step at a time.

Figure 3.21
Figure 3.21Positive rotation around the z-axis

Figure 3.22
Figure 3.22 Calculating rotation around the z-axis

In Figure 3.22, r is the distance from the origin to the point p, and α is the rotation angle from the x-axis to the point. You can use these items of information to represent the coordinates of p, as shown in Equation 3.2.

Equation 3.2

x = r cos α

y = r sin α

Similarly, you can find the coordinate of p’ by using r, α, and β as follows:

x’ = r cos (α + β)

y’ = r sin (α + β)

Then you can use the addition theorem of trigonometric functions1 to get the following:

x’ = r (cos α cos β – sin α sin β)

y’ = r (sin α cos β + cos α sin β)

Finally, you get the following expressions (Equation 3.3) by assigning Equation 3.2 to the previous expressions and removing r and α.

Equation 3.3

x’ = x cos β – y sin β

y’ = x sin β + y cos β

z’ = z

So by passing the values of sin β and cos β to the vertex shader and then calculating Equation 3.3 in the shader, you get the coordinates of the rotated point. To calculate sin β and cos β, you can use the methods of the JavaScript Math object.

Let’s look at a sample program, RotatedTriangle, which rotates a triangle around the z-axis, in a counterclockwise direction, by 90 degrees. Figure 3.23 shows RotatedTriangle.


Figure 3.23
Figure 3.23 RotatedTriangle

cos(a ± b) = cos a cos b β sin a sin b

Sample Program (RotatedTriangle.js)
Listing 3.5 shows RotatedTriangle.js which, in a similar manner to TranslatedTriangle.js, modifies the vertex shader to carry out the rotation operation. The fragment shader is the same as in TranslatedTriangle.js and, as usual, is not shown. Again, to support the shader modification, several processing steps are added to main() in the JavaScript program. Additionally, Equation 3.3 is added in the comments from lines 4 to 6 to remind you of the calculation needed.

Listing 3.5 RotatedTriangle.js
 1   // RotatedTriangle.js
 2   // Vertex shader program
 3   var VSHADER_SOURCE =
 4    // x' = x cos b - y sin b
 5    // y' = x sin b + y cos b                             Equation 3.3
 6    // z' = z
 7    'attribute vec4 a_Position;\n' +
 8    'uniform float u_CosB, u_SinB;\n' +
 9    'void main() {\n' +
10   '  gl_Position.x = a_Position.x * u_CosB - a_Position.y *u_SinB;\n'+
11  '  gl_Position.y = a_Position.x * u_SinB + a_Position.y * u_CosB;\n'+
12   '  gl_Position.z = a_Position.z;\n' +
13   '  gl_Position.w = 1.0;\n' +
14   '}\n';
15
16   // Fragment shader program
      ...
22   // Rotation angle
23   var ANGLE = 90.0;
24
25   function main() {
        ...
42      // Set the positions of vertices
43      var n = initVertexBuffers(gl);
         ...
49      // Pass the data required to rotate the shape to the vertex shader
50      var radian = Math.PI * ANGLE / 180.0; // Convert to radians
51      var cosB = Math.cos(radian);
52      var sinB = Math.sin(radian);
53
54      var u_CosB = gl.getUniformLocation(gl.program, 'u_CosB');
55      var u_SinB = gl.getUniformLocation(gl.program, 'u_SinB');
         ...
60   gl.uniform1f(u_CosB, cosB);
61   gl.uniform1f(u_SinB, sinB);
62
63      // Set the color for clearing <canvas>
         ...
69      // Draw a triangle
70      gl.drawArrays(gl.TRIANGLES, 0, n);
71   }
72
73   function initVertexBuffers(gl) {
74      var vertices = new Float32Array([
75        0.0, 0.5,  -0.5, -0.5,  0.5, -0.5
76      ]);
77      var n = 3; // The number of vertices
         ...
105      return n;
106   }
Let’s look at the vertex shader, which is straightforward:

 2   // Vertex shader program
 3   var VSHADER_SOURCE =
 4    // x' = x cos b - y sin b
 5    // y' = x sin b + y cos b
 6    // z' = z
 7    'attribute vec4 a_Position;\n' +
 8    'uniform float u_CosB, u_SinB;\n' +
 9    'void main() {\n' +
10   '  gl_Position.x = a_Position.x * u_CosB - a_Position.y * u_SinB;\n'+
11   '  gl_Position.y = a_Position.x * u_SinB + a_Position.y * u_CosB;\n'+
12   '  gl_Position.z = a_Position.z;\n' +
13   '  gl_Position.w = 1.0;\n' +
14   '}\n';
Because the goal is to rotate the triangle by 90 degrees, the sine and cosine of 90 need to be calculated. Line 8 defines two uniform variables for receiving these values, which are calculated in the JavaScript program and then passed to the vertex shader.

You could pass the rotation angle to the vertex shader and then calculate the values of sine and cosine in the shader. However, because they are identical for all vertices, it is more efficient to do it once in the JavaScript.

The name of these uniform variables, u_CosB and u_SinB, are defined following the naming rule used throughout this book. As you will remember, you use the uniform variable because the values of these variables are uniform (unchanging) per vertex.

As in the previous sample programs, x, y, z, and w are passed in a group to the attribute variable a_Position in the vertex shader. To apply Equation 3.3 to x, y, and z, you need to access each component in a_Position separately. You can do this easily using the. operator, such as a_Position.x, a_Position.y, and a_Position.z (see Figure 3.24 and Chapter 6).


Figure 3.24
Figure 3.24 Access methods for each component in a vec4

Handily, you can use the same operator to access each component in gl_Position to which the vertex coordinate is written, so you can calculate x’ = x cos β – y sin β from Equation 3.3 as shown at line 10:

10   '  gl_Position.x = a_Position.x * u_CosB - a_Position.y * u_SinB;\n'+
Similarly, you can calculate y’ as follows:

11   '  gl_Position.y = a_Position.x * u_SinB + a_Position.y * u_CosB;\n'+
According to Equation 3.3, you just need to assign the original z coordinate to z’ directly at line 12. Finally, you need to assign 1.0 to the last component w2:

12   '  gl_Position.z = a_Position.z;\n' +
13   '  gl_Position.w = 1.0;\n' +
Now look at main() in the JavaScript code, which starts from line 25. This code is mostly the same as in TranslatedTriangle.js. The only difference is passing cos β and sin β to the vertex shader. To calculate the sine and cosine of β, you can use the JavaScript Math.sin() and Math.cos() methods. However, these methods expect parameters in radians, not degrees, so you need to convert from degrees to radians by multiplying the number of degrees by pi and then dividing by 180. You can utilize Math.PI as the value of pi as shown at line 50, where the variable ANGLE is defined as 90 (degrees) at line 23:

50 var radian = Math.PI * ANGLE / 180.0; // Converts degrees to radians
Once you have the angle in radians, lines 51 and 52 calculate cos β and sin β, and then lines 60 and 61 pass them to the uniform variables in the vertex shader:

51   var cosB = Math.cos(radian);
52   var sinB = Math.sin(radian);
53
54   var u_CosB = gl.getUniformLocation(gl.program, 'u_CosB');
55   var u_SinB = gl.getUniformLocation(gl.program, 'u_SinB');
...
60   gl.uniform1f(u_CosB, cosB);
61   gl.uniform1f(u_SinB, sinB);
When you load this program into your browser, you can see the triangle, rotated through 90 degrees, on the screen. If you specify a negative value to ANGLE, you can rotate the triangle in the opposite direction (clockwise). You can also use the same equation. For example, to rotate the triangle in the clockwise direction, you can specify –90 instead of 90 at line 23, and Math.cos() and Math.sin() will deal with the remaining tasks for you.

For those of you concerned with speed and efficiency, the approach taken here (using two uniform variables to pass the values of cos β and sin β) isn’t optimal. To pass the values as a group, you can define the uniform variable as follows:

uniform vec2 u_CosBSinB;
and then pass the values by:

gl.uniform2f(u_CosBSinB,cosB, sinB);
Then in the vertex shader, you can access them using u_CosBSinB.x and u_CosBSinB.y.

Transformation Matrix: Rotation
For simple transformations, you can use mathematical expressions. However, as your needs become more complex, you’ll quickly find that applying a series of equations becomes quite complex. For example a “translation after rotation” as shown in Figure 3.25 can be realized by using Equations 3.1 and 3.3 to find the new mathematical expressions for the transformation and then implementing them in a vertex shader.

Figure 3.25
Figure 3.25 Rotate first and then translate a triangle

However, it is time consuming to determine the mathematical expressions every time you need a new set of transformation and then implement them in a vertex shader. Fortunately, there is another tool in the mathematical toolbox, the transformation matrix, which is excellent for manipulating computer graphics.

As shown in Figure 3.26, a matrix is a rectangular array of numbers arranged in rows (in the horizontal direction) and columns (in the vertical direction). This notation makes it easy to write the calculations explained in the previous sections. The brackets indicate that these numbers are a group.

Figure 3.26
Figure 3.26 Example of a matrix

Before explaining the details of how to use a transformation matrix to replace the equations used here, you need to make sure you understand the multiplication of a matrix and a vector. A vector is an object represented by an n-tuple of numbers, such as the vertex coordinates (0.0, 0.5, 1.0).

The multiplication of a matrix and a vector can be written as shown in Equation 3.4. (Although the multiply operator × is often omitted, we explicitly write the operator in this book for clarity.) Here, our new vector (on the left) is the result of multiplying a matrix (in the center) by our original vector (on the right). Note that matrix multiplication is noncommutative. In other words, A × B is not the same as B × A. We discuss this further in Chapter 6.

Equation 3.4

03equ01.jpg
This matrix has three rows and three columns and is called a 3×3 matrix. The rightmost part of the equation is a vector composed of x, y, and z. (In the case of a multiplication of a matrix and vector, the vector is written vertically, but it has the same meaning as when it is written horizontally.) This vector has three elements, so it is called a three-dimensional vector. Again, the brackets on both sides of the array of numbers (vector) are also just notation for recognizing that these numbers are a group.

In this case, x’, y’, and z’ are defined using the elements of the matrix and the vector, as shown by Equation 3.5. Note that the multiplication of a matrix and vector can be defined only if the number of columns in a matrix matches the number of rows in a vector.

Equation 3.5

x’ = ax + by + cz

y’ = dx + ey + fz

z’ = gx + hy + iz

Now, to understand how to use a matrix instead of our original equations, let’s compare the matrix equations and Equation 3.3 (shown again as Equation 3.6).

Equation 3.6

x’ = x cos β – y sin β

y’ = x sin β + y cos β

z’ = z

For example, compare the equation for x’:

x’ = ax + by + cz

x’ = x cos β – y sin β

In this case, if you set a = cos β, b = -sin β, and c = 0, the equations become the same. Similarly, let us compare the equation for y’:

y’ = dx + ey + fz

y’ = x sin β + y cos β

In this case, if you set d = sin β, e = cos β, and f = 0, you get the same equation. The last equation about z’ is easy. If you set g = 0, h = 0, and i = 1, you get the same equation.

Then, by assigning these results to Equation 3.4, you get Equation 3.7.

Equation 3.7

03equ02.jpg
This matrix is called a transformation matrix because it “transforms” the right-side vector (x, y, z) to the left-side vector (x’, y’, z’). The transformation matrix representing a rotation is called a rotation matrix.

You can see that the elements of the matrix in Equation 3.7 are an array of coefficients in Equation 3.6. Once you become accustomed to matrix notation, it is easier to write and use matrices than to have to deal with a set of transformation equations.

As you would expect, because matrices are used so often in 3DCG, multiplication of a matrix and a vector is easy to implement in shaders. However, before exploring how, let’s quickly look at other types of transformation matrices, and then we will start to use them in shaders.

Transformation Matrix: Translation
Obviously, if we can use a transformation matrix to represent a rotation, we should be able to use it for other types of transformation, such as translation. For example, let us compare the equation for x’ in Equation 3.1 to that in Equation 3.5 as follows:

x’ = ax + by + cz - - - from Equation (3.5)

x’ = x + Tx - - - from Equation (3.1)

Here, the second equation has the constant term Tx, but the first one does not, meaning that you cannot deal with the second one by using the 3×3 matrix of the first equation. To solve this problem, you can use a 4×4 matrix and the fourth components of the coordinate, which are set to 1 to introduce the constant terms. That is to say, we assume that the coordinates of point p are (x, y, z, 1), and the coordinates of the translated point p (p’) are (x’, y’, z’, 1). This gives us Equation 3.8.

Equation 3.8

03equ03.jpg
This multiplication is defined as follows:

Equation 3.9

x’ = ax + by + cz +d

y’ = ex + fy + gz + h

z’ = ix + jy + kz + l

1 = mx + ny + oz+ p

From the equation1 = mx + ny + oz + p, it is easy to find that the coefficients are m = 0, n = 0, o = 0, and p = 1. In addition, these equations have the constant terms d, h, and l, which look helpful to deal with Equation 3.1 because it also has constant terms. Let us compare Equation 3.9 and Equation 3.1 (translation), which is reproduced again:

x’ = x + Tx

y’ = y + Ty

z’ = z + Tz

When you compare the x’ component of both equations, you can see that a=1, b=0, c=0, and d=Tx. Similarly, when comparing y’ from both equations, you find e = 0, f = 1, g = 0, and h = Ty; when comparing z’ you see i=0, j=0, k=1, and l=Tz. You can use these results to write a matrix that represents a translation, called a translation matrix, as shown in Equation 3.10.

Equation 3.10

03equ04.jpg
Rotation Matrix, Again
At this stage you have successfully created a rotation and a translation matrix, which are equivalent to the two equations you used in the example programs earlier. The final step is to combine these two matrices; however, the rotation matrix (3×3 matrix) and transformation matrix (4×4 matrix) have different numbers of elements. Unfortunately, you cannot combine matrices of different sizes, so you need a mechanism to make them the same size.

To do that, you need to change the rotation matrix (3×3 matrix) into a 4×4 matrix. This is straightforward and requires you to find the coefficient of each equation in Equation 3.9 by comparing it with Equation 3.3. The following shows both equations:

x’ = x cos β – y sin β

y’ = x sin β + y cos β

z’ = z

x’ = ax + by + cz + d

y’ = ex + fy + gz + h

z’ = ix + iy + kz + l

1 = mx + ny + oz + p

For example, when you compare x’ = x cos β – y sin β with x’ = ax + by + cz +d, you find a = cos β, b = –sin β, c = 0, and d = 0. In the same way, after comparing in terms of y and z, you get the rotation matrix shown in Equation 3.11:

Equation 3.11

03equ05.jpg
This allows you to represent both a rotation matrix and translation matrix in the same 4×4 matrix, achieving the original goal!

Sample Program (RotatedTriangle_Matrix.js)
Having constructed a 4×4 rotation matrix, let’s go ahead and use this matrix in a WebGL program by rewriting the sample program RotatedTriangle, which rotates a triangle 90 degrees around the z-axis in a counterclockwise direction, using the rotation matrix. Listing 3.6 shows RotatedTriangle_Matrix.js, whose output will be the same as Figure 3.23 shown earlier.

Listing 3.6 RotatedTriangle_Matrix.js
 1  // RotatedTriangle_Matrix.js
 2  // Vertex shader program
 3  var VSHADER_SOURCE =
 4    'attribute vec4 a_Position;\n' +
 5    'uniform mat4 u_xformMatrix;\n' +
 6    'void main() {\n' +
 7    '  gl_Position = u_xformMatrix * a_Position;\n' +
 8    '}\n';
 9
10  // Fragment shader program
     ...
16  // Rotation angle
17  var ANGLE = 90.0;
18
19  function main() {
      ...
36    // Set the positions of vertices
37    var n = initVertexBuffers(gl);
      ...
43    // Create a rotation matrix
44    var radian = Math.PI * ANGLE / 180.0; // Convert to radians
45    var cosB = Math.cos(radian), sinB = Math.sin(radian);
46
47     // Note: WebGL is column major order
48    var xformMatrix = new Float32Array([
49       cosB, sinB, 0.0, 0.0,
50       -sinB, cosB, 0.0, 0.0,
51       0.0, 0.0, 1.0, 0.0,
52       0.0, 0.0, 0.0, 1.0
53    ]);
54
55    // Pass the rotation matrix to the vertex shader
56     var u_xformMatrix = gl.getUniformLocation(gl.program, 'u_xformMatrix');
       ...
61    gl.uniformMatrix4fv(u_xformMatrix, false, xformMatrix);
62
63    // Set the color for clearing <canvas>
      ...
69    // Draw a triangle
70    gl.drawArrays(gl.TRIANGLES, 0, n);
71  }
72
73  function initVertexBuffers(gl) {
74    var vertices = new Float32Array([
75      0.0, 0.5, -0.5, -0.5, 0.5, -0.5
76    ]);
77    var n = 3; // Number of vertices
      ...
105   return n;
106  }
First, let us examine the vertex shader:

2  // Vertex shader program
3  var VSHADER_SOURCE =
4    'attribute vec4 a_Position;\n' +
5    'uniform mat4 u_xformMatrix;\n' +
6    'void main() {\n' +
7    '  gl_Position = u_xformMatrix * a_Position;\n' +
8    '}\n';
At line 7, u_xformMatrix, containing the rotation matrix described in Equation 3.11, and a_Position, containing the vertex coordinates (this is the right-side vector in Equation 3.11), are multiplied, literally implementing Equation 3.11.

In the sample program TranslatedTriangle, you were able to implement the addition of two vectors in one line (gl_Position = a_Position + u_Translation). In the same way, a multiplication of a matrix and vector can be written in one line in GLSL ES. This is convenient, allowing the calculation of the four equations (Equation 3.9) in one line. Again, this shows how GLSL ES has been designed specifically for 3D computer graphics by supporting powerful operations like this.

Because the transformation matrix is a 4×4 matrix and GLSL ES requires the data type for all variables, line 5 declares u_xformMatrix as type mat4. As you would expect, mat4 is a data type specifically for holding a 4×4 matrix.

Within the main JavaScript program, the rest of the changes just calculate the rotation matrix from Equation 3.11 and then pass it to u_xformMatrix. This part starts from line 44:

43   // Create a rotation matrix
44   var radian = Math.PI * ANGLE / 180.0; // Convert to radians
45   var cosB = Math.cos(radian), sinB = Math.sin(radian);
46
47   // Note: WebGL is column major order
48   var xformMatrix = new Float32Array([
49      cosB, sinB, 0.0, 0.0,
50     -sinB, cosB, 0.0, 0.0,
51       0.0, 0.0, 1.0, 0.0,
52       0.0, 0.0, 0.0, 1.0
53   ]);
54
55   // Pass the rotation matrix to the vertex shader
    ...
61   gl.uniformMatrix4fv(u_xformMatrix, false, xformMatrix);
Lines 44 and 45 calculate the values of cosine and sine, which are required in the rotation matrix. Then line 48 creates the matrix xformMatrix using a Float32Array. Unlike GLSL ES, because JavaScript does not have a dedicated object for representing a matrix, you need to use the Float32Array. One question that arises is in which order you should store the elements of the matrix (which is arranged in rows and columns) in the elements of the array (which is arranged in a line). There are two possible orders: row major order and column major order (see Figure 3.27).

Figure 3.27
Figure 3.27 Row major order and column major order

WebGL, just like OpenGL, requires you to store the elements of a matrix in the elements of an array in column major order. So, for example, the matrix shown in Figure 3.27 is stored in an array as follows: [a, e, i, m, b, f, j, n, c, g, k, o, d, h, l, p]. In the sample program, the rotation matrix is stored in the Float32Array in this order in lines 49 to 52.

The array created is then passed to the uniform variable u_xformMatrix by using gl.uniformMatrix4fv() at line 61. Note that the last letter of this method name is v, which indicates that the method can pass multiple data values to the variable.

gl.uniformMatrix4fv (location, transpose, array)

Assign the 4×4 matrix specified by array to the uniform variable specified by location.

Parameters

location

Specifies the storage location of the uniform variable.

Transpose

Must be false in WebGL.3

array

Specifies an array containing a 4×4 matrix in column major order (typed array).

Return value

None

Errors

INVALID_OPERATION

There is no current program object.

INVALID_VALUE

transpose is not false, or the length of array is less than 16.

If you load and run the sample program in your browser, you’ll see the rotated triangle. Congratulations! You have successfully learned how to use a transformation matrix to rotate a triangle.

Reusing the Same Approach for Translation
Now, as you have seen with Equations 3.10 and 3.11, you can represent both a translation and a rotation using the same type of 4×4 matrix. Both equations use the matrices in the form <new coordinates> = <transformation matrix> * <original coordinates>. This is coded in the vertex shader as follows:

7   '   gl_Position = u_xformMatrix * a_Position;\n' +
This means that if you change the elements of the array xformMatrix from those of a rotation matrix to those of a translation matrix, you will be able to apply the translation matrix to the triangle to achieve the same result as shown earlier but which used an equation (Figure 3.18).

To do that, change line 17 in RotatedTriangle_Matrix.js using the translation distances from the previous example:

17   varTx = 0.5, Ty = 0.5, Tz = 0.0;
You need to rewrite the code for creating the matrix, remembering that you need to store the elements of the matrix in column major order. Let’s keep the same name for the array variable, xformMatrix, even though it’s now being used to hold a translation matrix, because it reinforces the fact that we are using essentially the same code. Finally, you are not using the variable ANGLE, so lines 43 to 45 are commented out:

43   // Create a rotation matrix
44   // var radian = Math.PI * ANGLE / 180.0; // Convert to radians
45   // var cosB = Math.cos(radian), sinB = Math.sin(radian);
46
47    // Note: WebGL is column major order
48    var xformMatrix = new Float32Array([
49       1.0, 0.0, 0.0, 0.0,
50       0.0, 1.0, 0.0, 0.0,
51       0.0, 0.0, 1.0, 0.0,
52       Tx, Ty, Tz, 1.0
53    ]);
Once you’ve made the changes, run the modified program, and you will see the same output as shown in Figure 3.18. By using a transformation matrix, you can apply various transformations using the same vertex shader. This is why the transformation matrix is such a convenient and powerful tool for 3D graphics, and it’s why we’ve covered it in detail in this chapter.

Transformation Matrix: Scaling
Finally, let’s define the transformation matrix for scaling using the same assumption that the original point is p and the point after scaling is p’.

Figure 3.28
Figure 3.28 A scaling transformation

Assuming the scaling factor for the x-axis, y-axis, and z-axis is Sx, Sy, and Sz respectively, you obtain the following equations:

x’ = Sx × x

y’ = Sy × y

z’ = Sz × z

The following transformation matrix can be obtained by comparing these equations with Equation 3.9.

03equ06.jpg
As with the previous example, if you store this matrix in xformMatrix, you can scale the triangle by using the same vertex shader you used in RotatedTriangle_Matrix.js. For example, the following sample program will scale the triangle by a factor of 1.5 in a vertical direction, as shown in Figure 3.29:

17   varSx = 1.0, Sy = 1.5, Sz = 1.0;
      ...
47     // Note: WebGL is column major order
48     var xformMatrix = new Float32Array([
49        Sx, 0.0, 0.0, 0.0,
50        0.0, Sy, 0.0, 0.0,
51        0.0, 0.0, Sz, 0.0,
52        0.0, 0.0, 0.0, 1.0
53     ]

Figure 3.29
Figure 3.29 Triangle scaled in a vertical direction

Note that if you specify 0.0 to Sx, Sy, or Sz, the scaled size will be 0.0. If you want to keep the original size, specify 1.0 as the scaling factor.

 */


/*
double vertices[8][3] = {
    { 1.0f, 1.0f, 1.0f}, //0
    { 1.0f, 1.0f,-1.0f}, //1
    { 1.0f,-1.0f,-1.0f}, //2
    {-1.0f,-1.0f,-1.0f}, //3
    {-1.0f,-1.0f, 1.0f}, //4
    {-1.0f, 1.0f, 1.0f}, //5
    {-1.0f, 1.0f,-1.0f}, //6
    { 1.0f,-1.0f, 1.0f}  //7
};

nt[12][2] indices = {
    {5,4},
    {5,0},

    {4,7},
    {7,0},

    {6,5},
    {1,0},

    {3,4},
    {2,7},

    {6,3},
    {6,1},

    {3,2},
    {2,1}
}
and loop over that:

glBegin(GL_LINES);

for ( int i=0; i<12; i+=1 ) {

    glVertex3f(vertices[indices[i][0]][0],vertices[indices[i][0]][1],vertices[indices[i][0]][2]);
    glVertex3f(vertices[indices[i][1]][0],vertices[indices[i][1]][1],vertices[indices[i][1]][2]);
}
glEnd();
*/

/*

If you try to rotate cube in C without help of any specialized library you should use Matrix operations to transform coordinates.

You sohuld get roatation matrix (Let's call it M)
You should multiply M to your coordinates vector - result is new coordinates.
for 2D rotation, example (f - rotation angle, +- is rotation direction):

|cos f +-sin f| |x|   |x'|
|             | | | = |  |
|+-sin f cos f| |y|   |y'|
for 3D rotation, you should use 3x3 marix. Alsoo you should rotation axis, depending on it you should choose matrix M:

Mx (rotate around x axis):

|1      0       0 ||x|   |x'|
|0   cos f  -sin f||y| = |y'|                       
|0   sin f   cos f||z|   |z'|
My (rotate around y axis):

|cos f      0      sin f ||x|   |x'|
| 0         1      0     ||y| = |y'|                       
|-sin f     0      cos f ||z|   |z'|
Mz (rotate around z axis):

| cos f   -sin f    0    ||x|   |x'|
| sin f   cos f     0    ||y| = |y'|                       
| 0        0        1    ||z|   |z'|

 */
