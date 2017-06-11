/*
 * GenesisGamepad.h
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

#ifndef GenesisGamepad_h
#define GenesisGamepad_h

#include <Arduino.h>

// Disable/Enable paradigm to your need to optimize memory
#define GENESIS_GAMEPAD_CALLBACK    1
#define GENESIS_GAMEPAD_DELEGATE    1

#define GENESIS_GAMEPAD_UP_BUTTON    B10000000
#define GENESIS_GAMEPAD_DOWN_BUTTON  B01000000
#define GENESIS_GAMEPAD_LEFT_BUTTON  B00100000
#define GENESIS_GAMEPAD_RIGHT_BUTTON B00010000
#define GENESIS_GAMEPAD_START_BUTTON B00001000
#define GENESIS_GAMEPAD_A_BUTTON     B00000100
#define GENESIS_GAMEPAD_B_BUTTON     B00000010
#define GENESIS_GAMEPAD_C_BUTTON     B00000001

class GenesisGamepad;

/*!
 *  The class GenesisGamepad is used to define delegation paradigm for GenesisGamepad.
 *
 *  @ingroup Protocol
 */
class GenesisGamepadDelegate
{
  
public:
  
  /*! This method is called when gamepad inputs did changed. */
  virtual void gamepadInputsDidChanged(GenesisGamepad *sender, byte previousInputs, byte newInputs) = 0;
  
};

/*!
 *  This class manage a Genesis/Mega Drive gamepad.
 *
 *  @ingroup Protocol
 */
class GenesisGamepad
{
  
public:
  
  GenesisGamepad(int8_t upButtonPin, int8_t downButtonPin, int8_t leftButtonPin, int8_t rightButtonPin,
                 int8_t selectButtonPin=-1, int8_t abButtonPin=-1, int8_t startCButtonPin=-1);
  
  /*! Update should be called by main loop. */
  void update();
  
  /*! Set the refresh frequency. Default frequency is 50Hz. */
  void setRefreshFrequency(int frequency);
  
  /*! Enable/disable gamepad refresh. */
  void setEnable(bool state);
  
#if GENESIS_GAMEPAD_DELEGATE
  /*! Set delegate for asynchronous feedback */
  void setGamepadDelegate(GenesisGamepadDelegate *delegate);
  
  /*! Get delegate used for asynchronous feedback. */
  inline GenesisGamepadDelegate *gamepadDelegate() {return _gamepadDelegate;};
#endif

#if GENESIS_GAMEPAD_CALLBACK
  /*! Set call back function for C backward compatibility if needed. */
  void attachInterrupt(void (*gamepadInputsDidChangedCallback)(GenesisGamepad*,byte,byte));
#endif
  
private:
  
  int8_t _upButtonPin;
  int8_t _downButtonPin;
  int8_t _leftButtonPin;
  int8_t _rightButtonPin;
  int8_t _selectButtonPin;
  int8_t _abButtonPin;
  int8_t _startCButtonPin;
  
  unsigned short _frameDelay;
  
  unsigned long _lastRead;
  
  byte _lastInputs;
  
  bool _enabled;
  
#if GENESIS_GAMEPAD_DELEGATE
  GenesisGamepadDelegate *_gamepadDelegate = NULL;
#endif
  
#if GENESIS_GAMEPAD_CALLBACK
  void (*_gamepadInputsDidChangedCallback)(GenesisGamepad*,byte,byte) = NULL;
#endif
};

#endif
