// ======================================================================
// \title  LedBlinkerComponentLinux.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Arduino Blink deployment.
// ======================================================================

#include <ArduinoBlink/LedBlinker/LedBlinkerComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"

// #include <Arduino.h>
namespace ArduinoBlink {

  void LedBlinkerComponent ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LedBlinkerComponentBase::init(instance);
  }

  void LedBlinkerComponent ::
    blink()
  {
      this->gpio_out(0, m_state);
  }

} // end namespace ArduinoBlink

