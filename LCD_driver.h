//#define	PHILLIPS
#define	EPSON

#ifdef __cplusplus
extern "C" {
#endif

//********************************************************************
//
//				General Function Definitions
//
//********************************************************************
void LCDCommand(unsigned char data);
void LCDData(unsigned char data);
void LCDInit(void);
void LCDClear(int color);
void LCDPrintLogo(void);
void LCDContrast(char setting);
void LCDSetPixel(int color, unsigned char x, unsigned char y);
void ioinit(void);
void LCDSetLine(int x0, int y0, int x1, int y1, int color);
void LCDSetRect(int x0, int y0, int x1, int y1, unsigned char fill, int color);
void LCDPutChar(char c, int x, int y, int fColor, int bColor);
void LCDPutStr(char *pString, int x, int y, int fColor, int bColor);
void LCDContrast(char setting);
void LCDDrawCircle (int xCenter, int yCenter, int radius, int color, int circleType);

//********************************************************************
//
//					LCD Dimension Definitions
//
//********************************************************************
#define ROW_LENGTH	132
#define COL_HEIGHT	132
#define ENDPAGE     132
#define ENDCOL      130

//********************************************************************
//
//					EPSON Controller Definitions
//
//********************************************************************
#define DISON       0xAF
#define DISOFF      0xAE
#define DISNOR      0xA6
#define DISINV      0xA7
#define SLPIN       0x95
#define SLPOUT      0x94
#define COMSCN      0xBB
#define DISCTL      0xCA
#define PASET       0x75
#define CASET       0x15
#define DATCTL      0xBC
#define RGBSET8     0xCE
#define RAMWR       0x5C
#define RAMRD       0x5D
#define PTLIN       0xA8
#define PTLOUT      0xA9
#define RMWIN       0xE0
#define RMWOUT      0xEE
#define ASCSET      0xAA
#define SCSTART     0xAB
#define OSCON       0xD1
#define OSCOFF      0xD2
#define PWRCTR      0x20
#define VOLCTR      0x81
#define VOLUP       0xD6
#define VOLDOWN     0xD7
#define TMPGRD      0x82
#define EPCTIN      0xCD
#define EPCOUT      0xCC
#define EPMWR       0xFC
#define EPMRD       0xFD
#define EPSRRD1     0x7C
#define EPSRRD2     0x7D
#define NOP         0x25

//********************************************************************
//
//			PHILLIPS Controller Definitions
//
//********************************************************************
//LCD Commands
//*	Apr  4,	2010	<MLS> see definitions below, 
#if 0
	#define	NOPP		0x00	// nop 
	#define	BSTRON		0x03	
	#define SLEEPIN     0x10	
	#define	SLEEPOUT	0x11	
	#define	NORON		0x13	
	#define	INVOFF		0x20	
	#define INVON      	0x21	
	#define	SETCON		0x25	
	#define DISPOFF     0x28	
	#define DISPON      0x29	
	#define CASETP      0x2A	
	#define PASETP      0x2B	
	#define RAMWRP      0x2C	
	#define RGBSET	    0x2D	
	#define	MADCTL		0x36	
	#define	COLMOD		0x3A	
	#define DISCTR      0xB9	
	#define	EC			0xC0	
#endif

//*************************************************************************************
//	LCD Include File for Philips PCF8833 STN RGB- 132x132x3 Driver 
// 
//		Taken from Philips data sheet Feb 14, 2003 
//*************************************************************************************
//*	I changed them to P_ for Philips
//*	many of these commands are not used but I wanted them all listed in case
//*	anyone wants to write more features
//	Philips PCF8833 LCD controller command codes 
#define	P_NOP			0x00	// nop 
#define	P_SWRESET		0x01	// software reset 
#define	P_BSTROFF		0x02	// booster voltage OFF 
#define	P_BSTRON		0x03	// booster voltage ON 
#define	P_RDDIDIF		0x04	// read display identification 
#define	P_RDDST			0x09	// read display status 
#define	P_SLEEPIN		0x10	// sleep in 
#define	P_SLEEPOUT		0x11	// sleep out 
#define	P_PTLON			0x12	// partial display mode 
#define	P_NORON			0x13	// display normal mode 
#define	P_INVOFF		0x20	// inversion OFF 
#define	P_INVON			0x21	// inversion ON 
#define	P_DALO			0x22	// all pixel OFF 
#define	P_DAL			0x23	// all pixel ON 
#define	P_SETCON		0x25	// write contrast 
#define	P_DISPOFF		0x28	// display OFF 
#define	P_DISPON		0x29	// display ON 
#define	P_CASET			0x2A	// column address set 
#define	P_PASET			0x2B	// page address set 
#define	P_RAMWR			0x2C	// memory write 
#define	P_RGBSET		0x2D	// colour set 
#define	P_PTLAR			0x30	// partial area 
#define	P_VSCRDEF		0x33	// vertical scrolling definition 
#define	P_TEOFF			0x34	// test mode 
#define	P_TEON			0x35	// test mode 
#define	P_MADCTL		0x36	// memory access control 
#define	P_SEP			0x37	// vertical scrolling start address 
#define	P_IDMOFF		0x38	// idle mode OFF 
#define	P_IDMON			0x39	// idle mode ON 
#define	P_COLMOD		0x3A	// interface pixel format 
#define	P_SETVOP		0xB0	// set Vop
#define	P_BRS			0xB4	// bottom row swap 
#define	P_TRS			0xB6	// top row swap 
#define	P_DISCTR		0xB9	// display control 
#define	P_DOR			0xBA	// data order 
#define	P_TCDFE			0xBD	// enable/disable DF temperature compensation 
#define	P_TCVOPE		0xBF	// enable/disable Vop temp comp 
#define	P_EC			0xC0	// internal or external oscillator 
#define	P_SETMUL		0xC2	// set multiplication factor 
#define	P_TCVOPAB		0xC3	// set TCVOP slopes A and B 
#define	P_TCVOPCD		0xC4	// set TCVOP slopes c and d 
#define	P_TCDF			0xC5	// set divider frequency 
#define	P_DF8COLOR		0xC6	// set divider frequency 8-color mode 
#define	P_SETBS			0xC7	// set bias system 
#define	P_RDTEMP		0xC8	// temperature read back 
#define	P_NLI			0xC9	// n-line inversion 
#define	P_RDID1			0xDA	// read ID1 
#define	P_RDID2			0xDB	// read ID2 
#define	P_RDID3			0xDC	// read ID3 
 

//*******************************************************
//				12-Bit Color Definitions
//*******************************************************
#define WHITE	0xFFF
#define BLACK	0x000
#define RED	0xF00
#define	GREEN	0x0F0
#define BLUE	0x00F
#define CYAN	0x0FF
#define MAGENTA	0xF0F
#define YELLOW	0xFF0
#define BROWN	0xB22
#define ORANGE	0xFA0
#define PINK	0xF6A

typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} RGBColor;


#ifdef __cplusplus
}
#endif
//*******************************************************
//				Button Pin Definitions
//*******************************************************
#define	kSwitch1_PIN	3
#define	kSwitch2_PIN	4
#define	kSwitch3_PIN	5

//*******************************************************
//                              Circle Definitions
//*******************************************************
#define FULLCIRCLE 1
#define OPENSOUTH  2
#define OPENNORTH  3
#define OPENEAST   4
#define OPENWEST   5
#define OPENNORTHEAST 6
#define OPENNORTHWEST 7
#define OPENSOUTHEAST 8
#define OPENSOUTHWEST 9

// *************************************************************************************
// NOKIA TESTER.h
// *************************************************************************************
void delay_us(int x);
void delay_ms(int x);
void ioinit(void);
void reset(void);

// New
//************************************************************************
//*	adapted for Arduino and Mega by Mark Sproul
//*	Pin definitions
//*		RES	Reset			Digital Pin 8
//*		CS	Chip Select		Digital Pin 9
//*		DIO	Data I/O		Digital Pin 11
//*		SCK	Serial Clock	Digital Pin 13
//************************************************************************
//*		At first I tried to port it to the Arduino pin model, i.e. digitalWrite.
//*		As I feared, it introduced a noticeable decrease in speed.  For the LCD
//*		interface it needs to stay as it was. I now have it fully working on the
//*		mega utilizing the original code. This was done by modifying the pin
//*		definitions in the .h file.  Very straight forward and very clean. In fact
//*		it worked first shot on the Mega.
//************************************************************************
//*	these define the PORT and BIT number for each control pin
#define _USE_ARDUINO_FOR_NOKIEA_

//*	Arduino pin number defs
#define	LCD_RES_PIN	8
#define	CS_PIN		9
#define	DIO_PIN		11
#define	SCK_PIN		13

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	//*	Arduino Mega bit numbers
	#define LCD_RES		5		// D8
	#define CS			6		// D9
	#define DIO			5		// D11
	#define SCK			7		// D13

	//*	Arduino Mega ports
	#define	LCD_PORT_CS		PORTH
	#define	LCD_PORT_SCK	PORTB
	#define	LCD_PORT_RES	PORTH
	#define	LCD_PORT_DIO	PORTB
#else
	//*	Arduino Duemilanove bit numbers
	#define LCD_RES		0		// D8
	#define CS			1		// D9
	#define DIO			3		// D11
	#define SCK			5		// D13
	//#define LCD_PORT	PORTB

	//*	Arduino Duemilanove ports
	#define	LCD_PORT_CS		PORTB
	#define	LCD_PORT_SCK	PORTB
	#define	LCD_PORT_RES	PORTB
	#define	LCD_PORT_DIO	PORTB
#endif


/* Old
#define CS			2		// D10
#define SCK			3		// D11
#define LCD_RES		1		// D9
#define DIO			4		// D12
#define LCD_PORT	PORTB
*/

//*******************************************************
//						Macros
//*******************************************************
#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

//*******************************************************
//					General Definitions
//*******************************************************
#define MYUBRR 16	//Used to set the AVR Baud Rate TO 115200 (External 16MHz Oscillator)
