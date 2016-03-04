// v1.0 by @pato_pitaluga patricio.pitaluga@gmail.com
// To set up your own behavior, change the cases of outputAction function.

#include "Keyboard.h"

const int buttonPin[] = {2, 3, 4, 5, 6, 7, 8, 9};
int pinCount = 8;

int buttonState[] = {1, 1, 1, 1, 1, 1, 1, 1};
int prevButtonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
long startedPressing[] = {0, 0, 0, 0, 0, 0, 0, 0};
boolean longPressing[] = {false, false, false, false, false, false, false, false};

long lastDebounceTime[] = {0, 0, 0, 0, 0, 0, 0, 0};

long debounceDelay = 50;

int keyComb(char key1 = 0, char key2 = 0, char key3 = 0, char key4 = 0) {
  if (key1 != 0) { Keyboard.press(key1); }
  if (key2 != 0) { Keyboard.press(key2); }
  if (key3 != 0) { Keyboard.press(key3); }
  if (key4 != 0) { Keyboard.press(key4); }
  delay(100);
  Keyboard.releaseAll();
}

int sendLine(char const * line) {
  Keyboard.print(line);
  delay(750);
  keyComb(KEY_RETURN);
}

// Output actions. Probably the only part that you need to change
int outputAction(int currentButton, int typeOfPress = 0) {
  // typeOfPress 1: on push; 2: on release; 3: on long press; 4: on lingering press.
  // actions on release, on long press and lingering press include the action press. Action lingering press cancels action release and long press.

  if (currentButton + 1 == 1) {
    if (typeOfPress == 1) {
      keyComb(KEY_LEFT_GUI, 'c');
    }
    if (typeOfPress == 3) {
      keyComb(KEY_LEFT_GUI, 'f');
    }
    if (typeOfPress == 4) {
      keyComb(KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'f');
    }
  }

  if (currentButton + 1 == 2) {
    if (typeOfPress == 1) {
      keyComb(KEY_LEFT_GUI, 'v');
    }
    if ((typeOfPress == 3) || (typeOfPress == 4)) {
      keyComb(KEY_RETURN);
    }
  }

  if (currentButton + 1 == 3) {
    if (typeOfPress == 1) {
      keyComb(KEY_RETURN);
    }
    if ((typeOfPress == 3) || (typeOfPress == 4)) {
      keyComb(KEY_BACKSPACE);
      keyComb(KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'd');
    }
  }

  if (currentButton + 1 == 4) {
    if (typeOfPress == 2) {
      keyComb(KEY_LEFT_GUI, 's');
    }
    if (typeOfPress == 3) {
      keyComb(KEY_LEFT_GUI, KEY_LEFT_SHIFT, 's');
    }
    if (typeOfPress == 4) {
      keyComb(KEY_LEFT_GUI, KEY_LEFT_SHIFT, KEY_LEFT_ALT, 's');
    }
  }

  if (currentButton + 1 == 5) {
    if (typeOfPress == 1) {
      keyComb(KEY_LEFT_GUI, KEY_LEFT_SHIFT, KEY_LEFT_CTRL, '3');
    }
    if ((typeOfPress == 3) || (typeOfPress == 4)) {
      keyComb(KEY_LEFT_GUI, ' ');
      sendLine("photoshop");
    }
  }

  if (currentButton + 1 == 6) {
    if (typeOfPress == 2) {
      keyComb(KEY_LEFT_GUI, 'n');
    }
    if (typeOfPress == 3) {
      keyComb(KEY_LEFT_GUI, 'n');
      keyComb(KEY_RETURN);
    }
    if (typeOfPress == 4) {
      keyComb(KEY_LEFT_GUI, 'w');
    }
  }

  if (currentButton + 1 == 7) {
    if (typeOfPress == 1) {
      keyComb(KEY_DOWN_ARROW);
      keyComb(KEY_LEFT_GUI, KEY_RIGHT_ARROW);
    }
    if (typeOfPress == 3) {
      keyComb(KEY_DOWN_ARROW);
      keyComb(KEY_LEFT_GUI, KEY_RIGHT_ARROW);
    }
    if (typeOfPress == 4) {
      keyComb(KEY_DOWN_ARROW);
      keyComb(KEY_LEFT_GUI, KEY_RIGHT_ARROW);
    }
  }

  if (currentButton + 1 == 8) {
    if (typeOfPress == 1) {
      keyComb(KEY_LEFT_GUI, ' ');
      sendLine("https://www.youtube.com/watch?v=dQw4w9WgXcQ"); // Rickroll
    }
    if ((typeOfPress == 3) || (typeOfPress == 4)) {
      keyComb(KEY_LEFT_GUI, ' ');
      sendLine("https://www.youtube.com/watch?v=uxpDa-c-4Mc"); // Hotline bling
    }
  }
}

void setup() {

  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
    pinMode(buttonPin[thisPin], INPUT);
    digitalWrite(buttonPin[thisPin], HIGH); // In some versions use INPUT_PULLUP to use the built-in pull up resistor
  }
  Keyboard.begin();
}

void loop() {
  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
    buttonState[thisPin] = digitalRead(buttonPin[thisPin]);
    // HIGH = state 1 <- button not pressed
    // LOW  = state 0 <- button pressed

    // On longer press
    if ((startedPressing[thisPin] != 0) && ((millis() - startedPressing[thisPin]) > 1200)) {

      outputAction(thisPin, 4);
      longPressing[thisPin] = true;
      startedPressing[thisPin] = 0;
    } else {

      if ((buttonState[thisPin] != prevButtonState[thisPin])) {
        if ((millis() - lastDebounceTime[thisPin]) > debounceDelay) {
  
          if (buttonState[thisPin] == 0) {
            // Button pressed
  
            startedPressing[thisPin] = millis();
            // Standard action
            outputAction(thisPin, 1);
          } else {
            // Button released
  
            if (!longPressing[thisPin]) {
              if ((millis() - startedPressing[thisPin]) < 500) {
                // On release (to avoid standard action if is incompatible with Long or Longer action)
                outputAction(thisPin, 2);              
              } else {
                // Long action (+standard action already sent)
                outputAction(thisPin, 3);
              }
            }
  
            startedPressing[thisPin] = 0;
            longPressing[thisPin] = false;
          }
          lastDebounceTime[thisPin] = millis();
        }
      }
    }

    prevButtonState[thisPin] = buttonState[thisPin];
  }
}


