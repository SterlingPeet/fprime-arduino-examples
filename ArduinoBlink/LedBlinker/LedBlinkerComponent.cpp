// ======================================================================
// \title  LedBlinkerComponent.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Arduino Blink deployment.
// ======================================================================


#include <ArduinoBlink/LedBlinker/LedBlinkerComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace ArduinoBlink {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LedBlinkerComponent ::
#if FW_OBJECT_NAMES == 1
    LedBlinkerComponent(
        const char *const compName
    ) :
      LedBlinkerComponentBase(compName),
#else
    LedBlinkerComponent(void) :
#endif
    m_state(false),
    m_blinks(0),
    m_blinkDecimateCntrl(0)
  {}

  LedBlinkerComponent ::
    ~LedBlinkerComponent(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LedBlinkerComponent ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    Fw::ParamValid valid;
    m_blinkDecimateCntrl++;

    if(m_blinkDecimateCntrl >= this->paramGet_blinkDecimate(valid))
    {
      blink();
      m_state = !m_state;
      m_blinkDecimateCntrl = 0;

      if(m_state)
      {
        m_blinks++;
        tlmWrite_numBlinks(m_blinks);
      }
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void LedBlinkerComponent ::
    downlinkParams_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    Fw::ParamValid valid;
    U8 val1 = this->paramGet_blinkDecimate(valid);
    this->tlmWrite_blinkDecimate(val1);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void LedBlinkerComponent ::
    parameterUpdated(
        FwPrmIdType id
    )
  {
    this->log_ACTIVITY_LO_LedBlinkerParameterUpdated(id);
    Fw::ParamValid valid;
    switch(id) {
      case PARAMID_BLINKDECIMATE: {
        U8 val = this->paramGet_blinkDecimate(valid);
        this->tlmWrite_blinkDecimate(val);
        break;
      }
      default:
        FW_ASSERT(0,id);
        break;
    }
  }

} // end namespace ArduinoBlink

