/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "MonochromeLib.h"
#include "stdlib.h"

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************

#define RES 60
#define SPD 60

int i;
int f = SPD+1;

float p1x = 64;
float p1y = 32;
float p2x = 64;
float p2y = 32;
float p3x = 64;
float p3y = 32;
float p4x = 64;
float p4y = 32;

int op1x;
int op1y;
int op2x;
int op2y;
int op3x;
int op3y;
int op4x;
int op4y;

int vp1x;
int vp1y;
int vp2x;
int vp2y;
int vp3x;
int vp3y;
int vp4x;
int vp4y;


float t1x;
float t1y;
float t2x;
float t2y;
float t3x;
float t3y;
float t4x;
float t4y;

float v1x;
float v1y;
float v2x;
float v2y;
float v3x;
float v3y;

float r1x;
float r1y;
float r2x;
float r2y;

static int SysCallCode[] = {0xD201422B,0x60F20000,0x80010070};
static int (*SysCall)(int R4, int R5, int R6, int R7, int FNo ) = (void*)&SysCallCode;

int RTC_getTicks()
{
     return (*SysCall)(0, 0, 0, 0, 0x3B);
}

int rand_int(int max)
{
    return rand() % max;
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
	srand(RTC_getTicks());
	
    ML_clear_vram();

    while(1){
		if (f == SPD+1)
		{
			GetKey(&key);
			op1x = p1x;
			op1y = p1y;
			op2x = p2x;
			op2y = p2y;
			op3x = p3x;
			op3y = p3y;
			op4x = p4x;
			op4y = p4y;
			
			vp1x = rand_int(127); //random
			vp1y = rand_int(63);
			vp2x = rand_int(127);
			vp2y = rand_int(63);
			vp3x = rand_int(127);
			vp3y = rand_int(63);
			vp4x = rand_int(127);
			vp4y = rand_int(63);
			f = 0;
		}
		else 
		{
			ML_display_vram();
			ML_clear_vram();
		}
		
		f++;
		
		p1x = (vp1x - op1x)*f/SPD+op1x;
		p1y = (vp1y - op1y)*f/SPD+op1y;
		p2x = (vp2x - op2x)*f/SPD+op2x;
		p2y = (vp2y - op2y)*f/SPD+op2y;
		p3x = (vp3x - op3x)*f/SPD+op3x;
		p3y = (vp3y - op3y)*f/SPD+op3y;
		p4x = (vp4x - op4x)*f/SPD+op4x;
		p4y = (vp4y - op4y)*f/SPD+op4y;
		
		t2x = p3x; // init des crayons
		t2y = p3y;
		t4x = p4x;
		t4y = p4y;
		r2x = p4x;
		r2y = p4y;
		
		// ML_clear_vram();
		
		// ML_line(p1x, p1y, p2x, p2y, 1); //ligne verte quoi
		// ML_line(p2x, p2y, p3x, p3y, 1); //ligne verte quoi
		// ML_line(p3x, p3y, p4x, p4y, 1); //ligne verte quoi
		ML_point(p1x, p1y, 2, 1);
		ML_point(p2x, p2y, 2, 1);
		ML_point(p3x, p3y, 2, 1);
		ML_point(p4x, p4y, 2, 1);
				
		for (i = 1; i < RES+1; i++)
		{
			t1x = t2x; //antécedent des crayons pour tracer les droites
			t1y = t2y;
			t3x = t4x;
			t3y = t4y;
			r1x = r2x;
			r1y = r2y;
			
			//calcule
			v1x = (p1x - p2x)*i/RES+p2x;
			v1y = (p1y - p2y)*i/RES+p2y;
			v2x = (p2x - p3x)*i/RES+p3x;
			v2y = (p2y - p3y)*i/RES+p3y;
			v3x = (p3x - p4x)*i/RES+p4x;
			v3y = (p3y - p4y)*i/RES+p4y;
			
			t2x = (v1x - v2x)*i/RES+v2x;
			t2y = (v1y - v2y)*i/RES+v2y;
			t4x = (v2x - v3x)*i/RES+v3x;
			t4y = (v2y - v3y)*i/RES+v3y;
			
			r2x = (t2x - t4x)*i/RES+t4x;
			r2y = (t2y - t4y)*i/RES+t4y;
			//fin calcule
			
			ML_line(r2x, r2y, r1x, r1y, 1); //crb
			//ML_pixel(r2x, r2y, 1);
			
		}
        // GetKey(&key);
		// ML_display_vram();
    }
    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

