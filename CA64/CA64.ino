#include <Keypad.h>
#include <Keyboard.h>

  const byte debug = 0;

  const signed char NO_VAL = -19;

  const byte ROWS = 8;
  const byte COLS = 8;
  
  const signed char commodoreDelKey = -2;
  const signed char commodoreBackspaceKey = -3;
  const signed char commodoreReturnKey = -4;
  const signed char commodoreCTRLKey = -5;
  const signed char commodoreLeftRightArrowKey = -6;
  const signed char commodoreRunStopKey = -7;
  const signed char commodoreLShiftKey = -8;
  const signed char commodoreUpDownArrowKey = -9;
  const signed char commodoreRShiftKey = -10;
  const signed char commodoreF1Key = -11;
  const signed char commodoreKey = -12;
  const signed char commodoreF3Key = -13;
  const signed char commodoreArrowKey = -14; 
  const signed char commodoreF5Key = -15;
  const signed char commodoreHomeKey = -16;
  const signed char commodoreF7Key = -17;
  const signed char commodoreAtKey = -18;

  byte rowPins[ROWS] = {7, 6, 5,4,3,2,1,0};
  byte colPins[COLS] = {19, 18,13,12,11,10,9,8};
  
  signed char keys[ROWS][COLS] = {
   {'1', '3', '5', '7' , '9', '+', '£', commodoreDelKey },
   {commodoreBackspaceKey, 'w',  'r', 'y', 'i', 'p', '*', commodoreReturnKey},
   {commodoreCTRLKey, 'a', 'd', 'g', 'j', 'l', ';', commodoreLeftRightArrowKey},
   {commodoreRunStopKey, commodoreLShiftKey, 'x', 'v', 'n', ',', '/', commodoreUpDownArrowKey},
   {' ', 'z', 'c', 'b', 'm', '.', commodoreRShiftKey, commodoreF1Key},
   {commodoreKey, 's', 'f', 'h', 'k', ':', '=', commodoreF3Key},
   {'q', 'e', 't', 'u', 'o', commodoreAtKey, commodoreArrowKey, commodoreF5Key},
   {'2', '4', '6', '8', '0', '-', commodoreHomeKey, commodoreF7Key}
  };
  
  Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void debugLogPress(char value) {
  if (!debug)
    return;

  Serial.println("Pressing value: " + (value == ' ' ? "space" : String(value)));
}

void writeDebugLog(const char message[]) {
  if (!debug)
    return;

  Serial.println(message);
}

void setupDebugLog() {
  if (!debug)
    return;
    
  Serial.begin(9600);

  while (!Serial) {};
  
  Serial.println("@@@@@@@@@@........@@@@@@@@@@@");
  Serial.println("@@@@@@............@@@@@@@@@@@");
  Serial.println("@@@@..............@@@@@@@@@@@");
  Serial.println("@@/...............@@@@@@@@@@@");
  Serial.println("@.........@@@@@@@@...........");
  Serial.println("@.......@@@@@@@@@@.........@@");
  Serial.println(".......*@@@@@@@@@@.......@@@@");
  Serial.println(".......@@@@@@@@@@@******@@@@@");
  Serial.println("@.......@@@@@@@@@@,,,,,,,*@@@");
  Serial.println("@........@@@@@@@@@,,,,,,,,,*@");
  Serial.println("@@..........@@@@#.@@@@@@@@@@@");
  Serial.println("@@@...............@@@@@@@@@@@");
  Serial.println("@@@@@.............@@@@@@@@@@@");
  Serial.println("@@@@@@@@..........@@@@@@@@@@@");
}
  
void setup() {
  setupDebugLog();
  Keyboard.begin();
}

void getAltVal(char v, char* value) {
  switch(v) {
    case '1':
      value[0] = '!';
      break;
    case '2':
      value[0] = '"';
      break;
    case '3':
      value[0] = '#';
      break;
    case '4':
      value[0] = '$';
      break;
    case '5':
      value[0] = '%';
      break;
    case '6':
      value[0] = '&';
      break;
    case '7':
      value[0] = '\'';
      break;
    case '8':
      value[0] = '(';
      break;
    case '9':
      value[0] = ')';
      break;
    case ',':
      value[0] = '<';
      break;
    case '.':
      value[0] = '>';
      break;
    case ':':
      value[0] = '(';
      break;
    case ';':
      value[0] = ')';
      break;
    case '/':
      value[0] = '?';
      break;
    case '£':
      value[0] = KEY_LEFT_SHIFT;
      value[1] = '3';
      break;
    case commodoreLeftRightArrowKey:
      value[0] = KEY_RIGHT_ARROW;
      break;
    case commodoreUpDownArrowKey:
      value[0]= KEY_DOWN_ARROW;
      break;
    default:
      value[0] = v;
      value[1] = NO_VAL;
      break;
  }
}

void getValue(char val, char* value) {    
    value[1] = NO_VAL;
    
    switch(val) {
      case commodoreDelKey:
        value[0] = KEY_DELETE;
        break;
      case commodoreBackspaceKey:
        value[0] = KEY_BACKSPACE;
      break;
      case commodoreReturnKey:
        value[0] = KEY_RETURN;
        break;
      case commodoreCTRLKey:
        value[0] = KEY_LEFT_CTRL;
        break;
      case commodoreLShiftKey:
        value[0] = KEY_LEFT_SHIFT;
      case commodoreRShiftKey:
        value[0] = KEY_RIGHT_SHIFT;
        break;
      case commodoreLeftRightArrowKey:
        value[0] = KEY_LEFT_ARROW;
        break;
      case commodoreUpDownArrowKey:
        value[0] = KEY_UP_ARROW;
        break;
      case commodoreAtKey:
        value[0] = KEY_LEFT_SHIFT;
        value[1] = '\'';
        break;
      case commodoreHomeKey:
        value[0] = KEY_HOME;
        break;
      default:
        value[0] = val;
      break;
    } 
}

void loop() { 
  if (keypad.getKeys())
  {       
    int index = 0;

    if ((keypad.key[0].kstate == PRESSED || keypad.key[0].kstate == HOLD) && (keypad.key[0].kchar == commodoreLShiftKey || keypad.key[0].kchar == commodoreRShiftKey)) {
      index = 1;      
    }

    Key key = keypad.key[index];
    char value[2];

    if (index == 0)
      getValue(key.kchar, value);
    else
      getAltVal(key.kchar, value);
    
    if ( key.stateChanged )
    {
        switch (key.kstate) {
          case PRESSED:      
            if (key.kchar == commodoreKey) {
              writeDebugLog("Bespoke Windows Key Handler");
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.releaseAll();               
            } else {            
              for (int i = 0; i < 2; i++) {
                if (value[i] != NO_VAL){
                  debugLogPress(value[i]);
                  Keyboard.press(value[i]);   
                }             
              }
  
              writeDebugLog("Releasing");
              Keyboard.releaseAll();              
            }
          break;
        }
    }
  }
}
