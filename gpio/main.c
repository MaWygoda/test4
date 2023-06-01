#include <LPC21xx.H>

#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000 
#define BUTTON0_bm 0x10
#define BUTTON1_bm 0x40
#define BUTTON2_bm 0x20
#define BUTTON3_bm 0x80


// zmiana test4


enum KeyboardState{RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum Direction{RIGHT, LEFT};

void Delay(unsigned int uiWaitMiliSeconds){
	
	unsigned int uiCounter1;
	unsigned int uiCounter2;
	
	for(uiCounter1=0; uiCounter1<uiWaitMiliSeconds; uiCounter1++)
		{
		for(uiCounter2=0; uiCounter2<1497; uiCounter2++){}
		}
}

void LedInit(void){
	
	IO1DIR=IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1CLR=(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1SET=LED0_bm;
}

void KeyboardInit(void){
	
	IO0DIR=IO0DIR&(~(BUTTON1_bm|BUTTON2_bm|BUTTON3_bm|BUTTON0_bm));
	
}


void LedOn(unsigned char ucLedIndeks){
	
	IO1CLR=(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	
	switch(ucLedIndeks){
		case 0:
			IO1SET=LED0_bm;
			break;
		case 1:
			IO1SET=LED1_bm;
			break;
		case 2:
			IO1SET=LED2_bm;
			break;
		case 3:
			IO1SET=LED3_bm;
			break;
		default:
			break;
	}
}

enum KeyboardState eKeyboardRead(void){
	
	if ((IO0PIN&BUTTON0_bm) == 0){
		return(BUTTON_0);
	}
	else if ((IO0PIN&BUTTON1_bm) == 0){
		return(BUTTON_1);
	}
	else if ((IO0PIN&BUTTON2_bm) == 0){
		return(BUTTON_2);
	}	
	else if ((IO0PIN&BUTTON3_bm) == 0){
		return(BUTTON_3);
	}
	else {
		return (RELASED);
	}
}

void LedStep(enum Direction eStepDirection){
	
	static unsigned int uiDioda;
	
	switch(eStepDirection){
		case RIGHT:
			LedOn(2);
			uiDioda--;
			break;
		case LEFT:
			uiDioda++;
			break;
	}
	LedOn(uiDioda%4);
	
}

void LedStepLeft(void){
	LedStep(LEFT);
}
void LedStepRight(void){
	LedStep(RIGHT);
}


int main(){
	
	
	LedInit();
	KeyboardInit();
	
	while(1){
	
	Delay(500);
		
	switch(eKeyboardRead()){
		case BUTTON_0:
//		LedOn(1);
			break;
		case BUTTON_1:
			LedStepRight();
			break;		
		case BUTTON_2:
			LedStepLeft();
			break;		
		case BUTTON_3:
			break;	
		case RELASED:
			LedOn(4);
			break;				
	}

	}
}
