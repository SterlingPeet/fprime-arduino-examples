// ======================================================================
// \title  LedBlinkerComponent.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Arduino Blink deployment.
// ======================================================================

#ifndef ARDUINO_LedBlinkerComponent_HPP
#define ARDUINO_LedBlinkerComponent_HPP

#include "ArduinoBlink/LedBlinker/LedBlinkerComponentAc.hpp"

namespace ArduinoBlink {

  class LedBlinker :
    public LedBlinkerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object LedBlinkerComponent
      //!
      LedBlinkerComponent(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object LedBlinkerComponent
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object LedBlinkerComponent
      //!
      ~LedBlinker(void);

    PRIVATE:
      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for downlinkParams command handler
      //! Command to telemeter the current parameter values in use.
      void downlinkParams_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Blink a given pin
      void blink();
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );
      //! parameter update notification
      //!
      void parameterUpdated(FwPrmIdType id);

      bool m_state;
      U32 m_blinks;
      U32 m_blinkDecimateCntrl;
    };

} // end namespace ArduinoBlink

#endif // end LedBlinkerComponent_HPP
