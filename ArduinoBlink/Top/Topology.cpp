#include <Components.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>
#include <Os/Task.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Os/Log.hpp>
#include <Fw/Types/MallocAllocator.hpp>


#ifdef ARDUINO
    #include <avr/io.h>
#else
    volatile uint8_t DDRB = 2;
    volatile uint8_t PORTB = 2;
    #define PB0 0
    #define PB1 1
    #define PB2 2
    #define PB3 3
    #define PB4 4
    #define PB5 5
    #define PB6 6
    #define PB7 7
#endif

#if defined TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>
#endif

// List of context IDs
enum {
    UPLINK_BUFFER_STORE_SIZE = 3000,
    UPLINK_BUFFER_QUEUE_SIZE = 30,
    UPLINK_BUFFER_MGR_ID = 200
};

Os::Log osLogger;


// Registry
#if FW_OBJECT_REGISTRATION == 1
static Fw::SimpleObjRegistry simpleReg;
#endif

// Component instance pointers

// Setup the rate group driver used to drive all the ActiveRateGroups connected to it.
// For each active rate group, there is a rate divisor that represents how often it is run.
static NATIVE_INT_TYPE rgDivs[] = {1, 2, 4};
Svc::RateGroupDriverImpl rateGroupDriverComp(FW_OPTIONAL_NAME("RGDvr"),rgDivs,FW_NUM_ARRAY_ELEMENTS(rgDivs));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in ArduinoBlinkTopologyAi.xml
static NATIVE_UINT_TYPE rg1Context[] = {0,0,0,0,0,0,0,0,0,0};
Svc::ActiveRateGroupImpl rateGroup1Comp(FW_OPTIONAL_NAME("RG1"),rg1Context,FW_NUM_ARRAY_ELEMENTS(rg1Context));

// static NATIVE_UINT_TYPE rg2Context[] = {0,0,0,0,0,0,0,0,0,0};
// Svc::ActiveRateGroupImpl rateGroup2Comp(FW_OPTIONAL_NAME("RG2"),rg2Context,FW_NUM_ARRAY_ELEMENTS(rg2Context));

// static NATIVE_UINT_TYPE rg3Context[] = {0,0,0,0,0,0,0,0,0,0};
// Svc::ActiveRateGroupImpl rateGroup3Comp(FW_OPTIONAL_NAME("RG3"),rg3Context,FW_NUM_ARRAY_ELEMENTS(rg3Context));

ATmega::AssertResetComponent assertResetter(FW_OPTIONAL_NAME("assertResetter"));
Arduino::HardwareRateDriver hardwareRateDriver(FW_OPTIONAL_NAME("hardwareRateDriver"), 100);
Svc::CommandDispatcherImpl cmdDisp(FW_OPTIONAL_NAME("cmdDisp"));
Svc::TlmChanImpl chanTlm(FW_OPTIONAL_NAME("chanTlm"));
Svc::ActiveLoggerImpl eventLogger(FW_OPTIONAL_NAME("eventLogger"));
ATmega::EePrmDbComponentImpl eePrmDb(FW_OPTIONAL_NAME("eePrmDb"));
Svc::LinuxTimeImpl arduinoTime(FW_OPTIONAL_NAME("arduinoTime"));
Drv::ATmegaSerialDriverComponentImpl uartDriver(FW_OPTIONAL_NAME("uartDriver"));
Svc::GroundInterfaceComponentImpl groundInterface(FW_OPTIONAL_NAME("groundInterface"));
Drv::ATmegaGpioDriverComponentImpl ledGpio(FW_OPTIONAL_NAME("ledGpio"));
ArduinoBlink::LedBlinkerComponent ledBlinker(FW_OPTIONAL_NAME("ledBlinker"));

// Baremetal setup for the task runner
Os::TaskRunner taskRunner;


/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
void constructApp(void) {

#if FW_PORT_TRACING
    Fw::PortBase::setTrace(false);
#endif

    // Initialize each component instance in memory
    assertResetter.init();
    hardwareRateDriver.init(0);
    rateGroupDriverComp.init();
    rateGroup1Comp.init(10, 0);
    cmdDisp.init(2, 0);
    chanTlm.init(4, 0);
    eventLogger.init(4, 0);
    eePrmDb.init(0, 32, 1024);
    arduinoTime.init(0);
    uartDriver.init(0);
    groundInterface.init(0);
    ledGpio.init(0);
    ledBlinker.init(0);

    Fw::Logger::logMsg("Constructing Architecture.\n");

    // Callback to initialize architecture, connect ports, etc.
    // The contents of the function are autocoded from the
    // ArduinoBlinkTopologyAppAi.xml, and
    // incorporates the assembly name.
    constructArduinoBlinkArchitecture();

    /* Register commands */
    cmdDisp.regCommands();
    eventLogger.regCommands();

    // read parameters
    ledBlinker.loadParameters();


    // Configure hardware
    uartDriver.open(Drv::ATmegaSerialDriverComponentImpl::DEVICE::USART0,
                    Drv::ATmegaSerialDriverComponentImpl::BAUD_RATE::BAUD_115K,
                    Drv::ATmegaSerialDriverComponentImpl::PARITY::PARITY_NONE);
    ledGpio.setup(DDRB, PORTB, PB5, Drv::ATmegaGpioDriverComponentImpl::GPIO_OUT);

    // Active component startup
    //   The .start() function has the following arguments:
    //    1. Thread ID, unique value for each thread, not used for Linux or Baremetal
    //    2. Thread Priority, passed to underlying OS
    //    3. Thread Stack Size, passed to underlying OS, not used for Baremetal
    rateGroup1Comp.start(0, 100, 10*1024);
    cmdDisp.start(1, 99, 10*1024);
    chanTlm.start(2, 98, 10*1024);
    eventLogger.start(3, 97, 10*1024);

}

/**
 * Exit Tasks:
 *
 * Exits the tasks in preparation for stopping the software. This is likely
 * not needed for Arduino projects, as they run forever, however; it is here
 * for completeness.
 */
void exitTasks(void) {
    rateGroup1Comp.exit();
    cmdDisp.exit();
    chanTlm.exit();
    eventLogger.exit();

}
