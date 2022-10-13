// ======================================================================
// \title  LedBlinker.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Arduino Blink deployment.
// ======================================================================


#include <ArduinoBlink/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace ArduinoBlink {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LedBlinker :: LedBlinker(
        const char *const compName
    ) :
      LedBlinkerComponentBase(compName),
    m_state(false),
    m_blinks(0),
    m_blinkDecimateCntrl(0)
  {}

  LedBlinker ::
    ~LedBlinker(void)
  {

  }
  
  void LedBlinker ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LedBlinkerComponentBase::init(instance);
  }

  void LedBlinker ::
    blink()
  {
      this->gpio_out(0, (m_state) ? Fw::Logic::HIGH : Fw::Logic::LOW);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LedBlinker ::
    run_handler(
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

  void LedBlinker ::
    downlinkParams_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    Fw::ParamValid valid;
    U8 val1 = this->paramGet_blinkDecimate(valid);
    this->tlmWrite_blinkDecimate(val1);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void LedBlinker ::
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

