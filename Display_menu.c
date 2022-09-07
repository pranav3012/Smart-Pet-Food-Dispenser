/*
 * Display_menu.c
 *
 *  Created on: Jul 25, 2022
 *      Author: prana
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "KeyPad.h"

extern int Set_Weight1 (void);
extern int Set_Time1 (void);

extern int Set_Weight2 (void);
extern int Set_Time2 (void);

extern int Set_Weight3 (void);
extern int Set_Time3 (void);
extern int Real_Time(void);
extern void Disp_Para (int No);

extern void HD44780_Init(void);
extern void HD44780_PutChar(unsigned char c);
extern void HD44780_GotoXY(unsigned char x, unsigned char y);
extern void HD44780_PutStr(char *str);
extern void HD44780_ClrScr(void);

extern void set_time (void);


extern int Page_Counter;
extern int Key_Scanning;
extern int32_t Weight[3];
extern int32_t Time[3];
extern int32_t Tmin[3];

extern int32_t Weight2[3];
extern int32_t Time2[3];
extern int32_t Tmin2[3];

extern int32_t Weight3[3];
extern int32_t Time3[3];
extern int32_t Tmin3[3];

extern char targetHrs;
extern char targetmin;
extern char targetsec;
extern int min_Int;
extern int32_t target_weight;

extern char targetHrs2;
extern char targetmin2;
extern int32_t target_weight2;

extern char targetHrs3;
extern char targetmin3;
extern int32_t target_weight3;

extern char Key;
extern volatile int Real_Min;
extern volatile int Real_Hour;
extern int result;
extern int PC;
extern int start_Delay;
//							    0123456789012345
extern unsigned char Para1[2][17];	// Multi Dimensional Array to display the string Temperature and the Temperature



void Display_Menu (int PC)
{
	//			       0123456789012345
	char Menu1[17] = {"1:Set Meal Time1"};
	char Menu2[17] = {"2:Set Meal Time2"};
	char Menu3[17] = {"3:Set Meal Time3"};
	char Menu4[17] = {"4:Set Real Time "};
	char Menu5[17] = {"5:Disp Savd Para"};
	//			         0123456789012345
//	char Menu3_1[17] = {"3:Enter Weight  "};
//	char Menu3_2[17] = {"Entrd Amt    grm"};

	if (PC == 1)
	{
		HD44780_ClrScr();
		HD44780_GotoXY(0, 0);
		HD44780_PutStr(Menu1);

		HD44780_GotoXY(0, 1);
		HD44780_PutStr(Menu2);

	}

	else if (PC == 2)
	{
		HD44780_ClrScr();
		HD44780_GotoXY(0, 0);
		HD44780_PutStr(Menu3);

		HD44780_GotoXY(0, 1);
		HD44780_PutStr(Menu4);
	}
	else if (PC == 3)
	{
		HD44780_ClrScr();
		HD44780_GotoXY(0, 0);
		HD44780_PutStr(Menu5);
	}


}

int Set_Time1 (void)
{
	//							  0123456789012345
	unsigned char Min[2][17] = {{"Enter time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								{"Minute:-        "}};
	//							   0123456789012345
	unsigned char hour[2][17] = {{"Enter Time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								 {"Hour:-          "}};


//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Tmin [0] = Key - '0';
	Min[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Tmin [1] = Key - '0';
	Min[1][10] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		result = (result * 10) + (Tmin[i]);
	}

	targetmin = result;

//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Time [0] = Key - '0';
	hour[1][8] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Time [1] = Key - '0';
	hour[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		result = (result * 10) + Time[i];
	}
	targetHrs = result;

	Set_Weight1();
	return 1;
}

int Set_Weight1 (void)
{

	unsigned char lcdData[2][17] = {{"3:Enter Weight  "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								    {"Entrd Amt    grm"}};
	//								  0123456789012345
	unsigned char Save_Msg[2][17] = {{"   Data Saved   "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								     {"  Successfully  "}};

	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight [0] = Key - '0';
	lcdData[1][10] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight [1] = Key - '0';
	lcdData[1][11] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight [2] = Key - '0';
	lcdData[1][12] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}
	result = 0;
	for (int i=0; i <= 2; i++)
	{
		result = (result * 10) + Weight[i];
	}
	target_weight2 = result;



	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[0][i]);
	}
	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}
	start_Delay = 1;

	return 1;
}


/*
#######################################################################################################################################################################
#######################################################################################################################################################################
Parameter 2
#######################################################################################################################################################################
#######################################################################################################################################################################
*/

int Set_Time2 (void)
{
	//							  0123456789012345
	unsigned char Min[2][17] = {{"Enter time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								{"Minute:-        "}};
	//							   0123456789012345
	unsigned char hour[2][17] = {{"Enter Time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								 {"Hour:-          "}};


//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Tmin2 [0] = Key - '0';
	Min[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Tmin2 [1] = Key - '0';
	Min[1][10] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		result = (result * 10) + Tmin2[i];
	}
	targetmin2 = result;

//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Time2 [0] = Key - '0';
	hour[1][8] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Time2 [1] = Key - '0';
	hour[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		result = (result * 10) + Time2[i];
	}
	targetHrs2 = result;

	Set_Weight2();
	return 1;
}

int Set_Weight2 (void)
{

	unsigned char lcdData[2][17] = {{"3:Enter Weight  "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								    {"Entrd Amt    grm"}};
	//								  0123456789012345
	unsigned char Save_Msg[2][17] = {{"   Data Saved   "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								     {"  Successfully  "}};

	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight2 [0] = Key - '0';
	lcdData[1][10] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight2 [1] = Key - '0';
	lcdData[1][11] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight2 [2] = Key - '0';
	lcdData[1][12] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}
	result = 0;
	for (int i=0; i <= 2; i++)
	{
		result = (result * 10) + Weight2[i];
	}
	target_weight2 = result;



	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[0][i]);
	}
	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}
	start_Delay = 1;

	return 1;
}


/*
#######################################################################################################################################################################
#######################################################################################################################################################################
Parameter 3
#######################################################################################################################################################################
#######################################################################################################################################################################
*/

int Set_Time3 (void)
{
	//							  0123456789012345
	unsigned char Min[2][17] = {{"Enter time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								{"Minute:-        "}};
	//							   0123456789012345
	unsigned char hour[2][17] = {{"Enter Time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								 {"Hour:-          "}};


//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Tmin3 [0] = Key - '0';
	Min[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Tmin3 [1] = Key - '0';
	Min[1][10] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		result = (result * 10) + Tmin3[i];
	}
	targetmin3 = result;

//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 15; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}
	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 15; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Time3 [0] = Key - '0';
	hour[1][8] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Time3 [1] = Key - '0';
	hour[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		result = (result * 10) + Time3[i];
	}
	targetHrs3 = result;

	Set_Weight3();
	return 1;
}

int Set_Weight3 (void)
{

	unsigned char lcdData[2][17] = {{"3:Enter Weight  "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								    {"Entrd Amt    grm"}};
	//								  0123456789012345
	unsigned char Save_Msg[2][17] = {{"   Data Saved   "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								     {"  Successfully  "}};

	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight3 [0] = Key - '0';
	lcdData[1][10] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight3 [1] = Key - '0';
	lcdData[1][11] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	Weight3 [2] = Key - '0';
	lcdData[1][12] = Key;
//			HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (lcdData[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}
	result = 0;
	for (int i=0; i <= 2; i++)
	{
		result = (result * 10) + Weight3[i];
	}
	target_weight3 = result;



	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[0][i]);
	}
	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}
	start_Delay = 1;

	return 1;
}

/*
#######################################################################################################################################################################
#######################################################################################################################################################################
Real Time
#######################################################################################################################################################################
#######################################################################################################################################################################
*/

int Real_Time (void)
{
	//							  0123456789012345
	unsigned char Min[2][17] = {{"Enter time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								{"Minute:-        "}};
	//							   0123456789012345
	unsigned char hour[2][17] = {{"Enter Time      "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								 {"Hour:-          "}};

	unsigned char Save_Msg[2][17] = {{"   Data Saved   "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								     {"  Successfully  "}};
	int16_t Mresult = 0;
	int16_t Hresult = 0;

	int32_t RMin[3] = {0};
	int32_t RHour[3] = {0};


//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	RMin [0] = Key - '0';
	Min[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	RMin [1] = Key - '0';
	Min[1][10] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Min[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}

	for (int i=0; i <= 1; i++)
	{
		Mresult = (Mresult * 10) + RMin[i];
	}
	Real_Min = Mresult;

//-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=//
	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	RHour [0] = Key - '0';
	hour[1][8] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Key = KeyPad_WaitForKeyGetChar(0);
	RHour [1] = Key - '0';
	hour[1][9] = Key;
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[0][i]);
	}

	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (hour[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.

	}
	result = 0;
	for (int i=0; i <= 1; i++)
	{
		Hresult = (Hresult * 10) + RHour[i];
	}


	HD44780_ClrScr();
	HD44780_GotoXY(0,0);
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[0][i]);
	}
	HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
	for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
	{
		HD44780_PutChar (Save_Msg[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
	}

	Real_Hour = Hresult;
	Real_Min = Mresult;
	set_time();
	start_Delay = 1;
	return 1;

}

/*
#######################################################################################################################################################################
#######################################################################################################################################################################
Display Parameters
#######################################################################################################################################################################
#######################################################################################################################################################################
*/

void Disp_Para (int No)
{
	//							    0123456789012345
	unsigned char Para0[2][17] = {{"Select 1,2 or 3 "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								  {" Up*  Down# C   "}};

//	//							    0123456789012345
//	unsigned char Para1[2][17] = {{"1:Time:-        "},		// Multi Dimensional Array to display the string Temperature and the Temperature
//								  {"1:Weight:-      "}};
	//							    0123456789012345
	unsigned char Para2[2][17] = {{"2:Time:-        "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								  {"2:Weight:-      "}};
	//							    0123456789012345
	unsigned char Para3[2][17] = {{"3:Time:-        "},		// Multi Dimensional Array to display the string Temperature and the Temperature
								  {"3:Weight:-      "}};
	switch (No)
	{
	case 0:
		HD44780_ClrScr();
		Para0[1][12] = 0x7F;
		HD44780_GotoXY(0,0);
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para0[0][i]);
		}
		HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para0[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
		}
		break;
	case 1:
		Para1[0][8] = Time [0] + '0';
		Para1[0][9] = Time [1] + '0';
		Para1[0][10] = ':';
		Para1[0][11] = Tmin [0] + '0';
		Para1[0][12] = Tmin [1] + '0';

		Para1[1][11] = Weight [0] + '0';
		Para1[1][12] = Weight [1] + '0';
		Para1[1][13] = Weight [2] + '0';
		HD44780_ClrScr();
		HD44780_GotoXY(0,0);
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para1[0][i]);
		}
		HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para1[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
		}
		break;
	case 2:
		Para2[0][8] = Time2 [0] + '0';
		Para2[0][9] = Time2 [1] + '0';
		Para1[0][10] = ':';
		Para1[0][11] = Tmin2 [0] + '0';
		Para1[0][12] = Tmin2 [1] + '0';
		Para2[1][11] = Weight2 [0] + '0';
		Para2[1][12] = Weight2 [1] + '0';
		Para2[1][13] = Weight2 [2] + '0';
		HD44780_ClrScr();
		HD44780_GotoXY(0,0);
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para2[0][i]);
		}
		HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para2[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
		}
		break;
	case 3:
		Para3[0][8] = Time3 [0] + '0';
		Para3[0][9] = Time3 [1] + '0';
		Para1[0][10] = ':';
		Para1[0][11] = Tmin3 [0] + '0';
		Para1[0][12] = Tmin3 [1] + '0';
		Para3[1][11] = Weight3 [0] + '0';
		Para3[1][12] = Weight3 [1] + '0';
		Para3[1][13] = Weight3 [2] + '0';
		HD44780_ClrScr();
		HD44780_GotoXY(0,0);
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para3[0][i]);
		}
		HD44780_GotoXY(0,1);							// Pointing to the next location of the 16*2 LCD Display i.e., Second row  0th column
		for (int i = 0; i < 16; i++)					// For loop to Write the data on the 16*2 LCD display
		{
			HD44780_PutChar (Para3[1][i]);			// Writing data in LCD i.e., Second row data which is the Present temperature value.
		}
		break;
	case 4:
		break;


	}
}
