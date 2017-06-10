/*
 * AppController.cpp
 *
 * Copyright (c) 2017 by Sebastien MARCHAND (Web:www.marscaper.com, Email:sebastien@marscaper.com)
 */
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AppController.hpp"

// Use the pins you want here
int8_t upButtonPin     = A0;
int8_t downButtonPin   = A1;
int8_t leftButtonPin   = A2;
int8_t rightButtonPin  = A3;
int8_t selectButtonPin = 2;
int8_t abButtonPin     = 3;
int8_t startCButtonPin = 4;

AppController::AppController()
{
  //
  // Setup is here
  //

  Serial.begin(9600);

  _gamePad = new GenesisGamepad(upButtonPin,downButtonPin,leftButtonPin,rightButtonPin,
                               selectButtonPin,abButtonPin,startCButtonPin);
                               
  _gamePad->setGamepadDelegate(this);

  Serial.println("-Press buttons on your gamepad-");
}

void AppController::loop()
{
  //
  // Your loop is here
  //
  
  _gamePad->update();
}

void AppController::gamepadInputsDidChanged(GenesisGamepad *sender, byte previousInputs, byte newInputs)
{
  // Filter updated inputs
  byte updatedInputs = previousInputs ^ newInputs;
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_UP_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_UP_BUTTON )
    {
      Serial.println("Up button pressed.");
    }
    else
    {
      Serial.println("Up button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_DOWN_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_DOWN_BUTTON )
    {
      Serial.println("Down button pressed.");
    }
    else
    {
      Serial.println("Down button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_LEFT_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_LEFT_BUTTON )
    {
      Serial.println("Left button pressed.");
    }
    else
    {
      Serial.println("Left button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_RIGHT_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_RIGHT_BUTTON )
    {
      Serial.println("Right button pressed.");
    }
    else
    {
      Serial.println("Right button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_START_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_START_BUTTON )
    {
      Serial.println("Start button pressed.");
    }
    else
    {
      Serial.println("Start button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_A_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_A_BUTTON )
    {
      Serial.println("A button pressed.");
    }
    else
    {
      Serial.println("A button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_B_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_B_BUTTON )
    {
      Serial.println("B button pressed.");
    }
    else
    {
      Serial.println("B button released.");
    }
  }
  
  // Test if button was update
  if( updatedInputs & GENESIS_GAMEPAD_C_BUTTON )
  {
    // Get state
    if( newInputs & GENESIS_GAMEPAD_C_BUTTON )
    {
      Serial.println("C button pressed.");
    }
    else
    {
      Serial.println("C button released.");
    }
  }
}
