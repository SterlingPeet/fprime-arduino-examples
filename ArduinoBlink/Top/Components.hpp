#ifndef __ARDUINOBLINK_COMPONENTS_HEADER__
#define __ARDUINOBLINK_COMPONENTS_HEADER__

#include <Fw/Obj/SimpleObjRegistry.hpp>
#include <ArduinoBlink/LedBlinker/LedBlinkerComponent.hpp>
#include <ATmega/Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include <ATmega/Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <ATmega/Svc/AssertReset/AssertResetComponent.hpp>
#include <ATmega/Svc/ATmegaTime/ArduinoTimeImpl.hpp>
#include <ATmega/Svc/EePrmDb/EePrmDbComponentImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>


void constructApp(void);
void constructArduinoBlinkArchitecture(void);
void exitTasks(void);


extern Arduino::HardwareRateDriver hardwareRateDriver;
extern ArduinoBlink::LedBlinkerComponent ledBlinker;
extern ATmega::AssertResetComponent assertResetter;
extern ATmega::EePrmDbComponentImpl eePrmDb;
extern Drv::ATmegaGpioDriverComponentImpl ledGpio;
extern Drv::ATmegaSerialDriverComponentImpl uartDriver;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::ActiveRateGroupImpl rateGroup1Comp;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::GroundInterfaceComponentImpl groundInterface;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::LinuxTimeImpl arduinoTime;
extern Svc::TlmChanImpl chanTlm;
// extern Svc::ActiveRateGroupImpl rg2Context;
// extern Svc::ActiveRateGroupImpl rg3Context;
// Scheduler definition
extern Os::TaskRunner taskRunner;
#endif  // end __ARDUINOBLINK_COMPONENTS_HEADER__
