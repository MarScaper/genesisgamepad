/*
 * GenesisGamepad.cpp
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

#include "GenesisGamepad.h"

GenesisGamepad::GenesisGamepad(int8_t upButtonPin, int8_t downButtonPin, int8_t leftButtonPin, int8_t rightButtonPin,
                               int8_t selectButtonPin, int8_t abButtonPin, int8_t startCButtonPin)
{
  // Store pins
  _upButtonPin     = upButtonPin;
  _downButtonPin   = downButtonPin;
  _leftButtonPin   = leftButtonPin;
  _rightButtonPin  = rightButtonPin;
  _selectButtonPin = selectButtonPin;
  _abButtonPin     = abButtonPin;
  _startCButtonPin = startCButtonPin;
  
  // Set direction pin
  pinMode(_upButtonPin,    INPUT);
  pinMode(_downButtonPin,  INPUT);
  pinMode(_leftButtonPin,  INPUT);
  pinMode(_rightButtonPin, INPUT);
  
  // Set other buttons if select button is set
  if( _selectButtonPin != -1 )
  {
    pinMode(_selectButtonPin, OUTPUT);
    pinMode(_abButtonPin,     INPUT );
    pinMode(_startCButtonPin, INPUT );
  }
  
  _lastRead   = millis();
  _frameDelay = 1000/(float)50; // Default is 50Hz -> 20ms
  _lastInputs = 0;
  _enabled    = true;
}

void GenesisGamepad::setRefreshFrequency(int frequency)
{
  // Convert frequency directly into frame delay for optimization
  _frameDelay = 1000/frequency;
}

void GenesisGamepad::setEnable(bool state)
{
  if( state != _enabled )
  {
    _enabled = state;
    
    if( _enabled == true )
    {
      _lastInputs = 0;
      _lastRead   = millis();
    }
  }
}

#if GENESIS_GAMEPAD_DELEGATE
void GenesisGamepad::setGamepadDelegate(GenesisGamepadDelegate *delegate)
{
  _gamepadDelegate = delegate;
}
#endif

#if GENESIS_GAMEPAD_CALLBACK
void GenesisGamepad::attachInterrupt(void (*gamepadInputsDidChangedCallback)(GenesisGamepad*,byte,byte))
{
  _gamepadInputsDidChangedCallback = gamepadInputsDidChangedCallback;
}
#endif

void GenesisGamepad::update()
{
  if( !_enabled )
  {
    return;
  }
  
  // Update according to refresh rate
  unsigned long time = millis();
  if( time >= _lastRead+_frameDelay )
  {
    _lastRead = time;
    
    //
    // Inputs will be stored in a single byte for optimization
    //
    
    byte newInputs = 0;
    
    if( _selectButtonPin != -1 )
    {
      digitalWrite(_selectButtonPin,LOW);
      newInputs |= (!digitalRead(_startCButtonPin) )<<3; // Start
      newInputs |= (!digitalRead(_abButtonPin)     )<<2; // A
      
      digitalWrite(_selectButtonPin,HIGH);
      newInputs |= (!digitalRead(_abButtonPin)     )<<1; // B
      newInputs |= !digitalRead(_startCButtonPin);       // C
    }
    
    newInputs |= (!digitalRead(_upButtonPin)     )<<7; // Up
    newInputs |= (!digitalRead(_downButtonPin)   )<<6; // Down
    newInputs |= (!digitalRead(_leftButtonPin)   )<<5; // Left
    newInputs |= (!digitalRead(_rightButtonPin)  )<<4; // Right
    
    // Only notify if inputs changed
    if( _lastInputs != newInputs )
    {
#if GENESIS_GAMEPAD_CALLBACK
      if( _gamepadInputsDidChangedCallback )
      {
        // Use C callback for feedback
        _gamepadInputsDidChangedCallback(this,_lastInputs,newInputs);
      }
#endif

#if GENESIS_GAMEPAD_DELEGATE
      if( _gamepadDelegate )
      {
        // Use delegate for feedback
        _gamepadDelegate->gamepadInputsDidChanged(this,_lastInputs,newInputs);
      }
#endif
      
      // Store inputs for next loop
      _lastInputs = newInputs;
    }
  }
}