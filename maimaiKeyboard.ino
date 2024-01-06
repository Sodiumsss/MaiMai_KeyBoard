//Arduino Leonardo
//原作者：CrazyRedMachine(Github)

#include <Keyboard.h>
#include <Bounce2.h>

//总按键数
#define TOTAL_BUTTON_COUNT 8

//按键检测间隔，单位：毫秒
#define BOUNCE_INTERVAL 10

//引脚
int buttonPin[] = {4,2,20,18,19,21,5,3,4};
//引脚对应的按键
char buttonKey[] = {'q','w','e','d','c','x','z','a','s'};

Bounce buttonBounce[TOTAL_BUTTON_COUNT];
bool buttonState[TOTAL_BUTTON_COUNT];
bool previousState[TOTAL_BUTTON_COUNT];

void setup() {

 for (int i = 0; i < TOTAL_BUTTON_COUNT; i++){
   buttonBounce[i] = Bounce();
   buttonBounce[i].attach(buttonPin[i], INPUT_PULLUP);
   buttonBounce[i].interval(BOUNCE_INTERVAL);
   buttonState[i] = false;
   previousState[i] = true;
  }
  Keyboard.begin();
}

void loop() {

  for (int i = 0; i < TOTAL_BUTTON_COUNT; i++){
   buttonBounce[i].update();
   buttonState[i] = (buttonBounce[i].read() == LOW);
   if (buttonState[i] && !previousState[i]) { 
    Keyboard.press(buttonKey[i]);
    Serial.print("[+]");
    Serial.println(buttonKey[i]);

   } else if (!buttonState[i] && previousState[i]) {
    Keyboard.release(buttonKey[i]);
    Serial.print("[-]");
    Serial.println(buttonKey[i]);
   }
   previousState[i] = buttonState[i];
  }

}
