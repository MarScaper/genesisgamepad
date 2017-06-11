# Genesis/Mega Drive Gamepad
![Alt text](/genesisgamepad.jpg?raw=true "Optional Title")

## Synopsis
Simple C++ library allowing to control a Genesis/Mega Drive gamepad with an Arduino.

## Features
- Press and release button feedback (see sample code).
- Enable/disable gamepad.
- Adjustable refresh rate (default is 50Hz).
- Multiple gamepad allowed.
- Full C++ approach with delegation paradigm for asynchronous callbacks.
- C compatibility with enhanced C function callbacks.

## DB9 connector
![Alt text](/db9_female.jpg?raw=true "Optional Title")

|Pin |	Button(s) | Wire |
|----|------------|------|
|1   |Up          |Brown |
|2   |Down        |Red   |
|3   |Left        |Orange|
|4   |Right       |Yellow|
|5   |+5V         |Green |
|6   |A/B         |Blue  |
|7   |Select      |Grey  |
|8   |Ground      |Black |
|9   |Start/C     |White |

## Code Example
```
#include <GenesisGamepad.h>

// Use the pins you want here
int8_t upButtonPin     = A0;
int8_t downButtonPin   = A1;
int8_t leftButtonPin   = A2;
int8_t rightButtonPin  = A3;
int8_t selectButtonPin = 2;
int8_t abButtonPin     = 3;
int8_t startCButtonPin = 4;

GenesisGamepad *gamePad = NULL;

void setup() 
{
  Serial.begin(9600);

  gamePad = new GenesisGamepad(upButtonPin,downButtonPin,leftButtonPin,rightButtonPin,
                               selectButtonPin,abButtonPin,startCButtonPin);
                               
  gamePad->attachCallback(gamepadInputsDidChangedCallback);

  Serial.println("-Press buttons on your gamepad-");
}

void loop() 
{
  gamePad->update();
}

void gamepadInputsDidChangedCallback(GenesisGamepad *sender, byte previousInputs, byte newInputs)
{
  Serial.println("Button state changed.");
}
```
See examples directory for full sample code.

## Motivation

This library is part of a personnal project to improve my EM10 Takahashi mount thanks to Arduino.

## License

Copyright (c) 2017 by Sebastien MARCHAND 
Web:www.marscaper.com - Email:sebastien@marscaper.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
