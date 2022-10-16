module ArduinoBlink {

  # ----------------------------------------------------------------------
  # Defaults
  # ----------------------------------------------------------------------

  module Default {
    constant queueSize = 10
    constant stackSize = 64 * 1024
  }

  # ----------------------------------------------------------------------
  # Active component instances
  # ----------------------------------------------------------------------

  instance rg1: Svc.ActiveRateGroup base id 0x0200 \
    queue size Default.queueSize \
    stack size Default.stackSize \
    priority 120 \
  {

    phase Fpp.ToCpp.Phases.configObjects """
    NATIVE_INT_TYPE context[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    """

    phase Fpp.ToCpp.Phases.configComponents """
    rateGroup1Comp.configure(
        ConfigObjects::rg1::context,
        FW_NUM_ARRAY_ELEMENTS(ConfigObjects::rg1::context)
    );
    """

  }

  instance cmdDisp: Svc.CommandDispatcher base id 0x0500 \
    queue size 20 \
    stack size Default.stackSize \
    priority 101

  instance eventLogger: Svc.ActiveLogger base id 0x0B00 \
    queue size Default.queueSize \
    stack size Default.stackSize \
    priority 98

  instance chanTlm: Svc.TlmChan base id 0x0C00 \
    queue size Default.queueSize \
    stack size Default.stackSize \
    priority 97

  # ----------------------------------------------------------------------
  # Passive component instances
  # ----------------------------------------------------------------------

  @ Communications driver. May be swapped with other comm drivers like UART
  instance comm: Drv.ByteStreamDriverModel base id 0x4000 \
    type "Arduino::SerialDriverComponentImpl" \
    at "../../Arduino/Drv/SerialDriver/SerialDriver.hpp" \
  {

    phase Fpp.ToCpp.Phases.configConstants """
    enum {
      PRIORITY = 100,
      STACK_SIZE = Default::stackSize
    };
    """

    phase Fpp.ToCpp.Phases.startTasks """
    // Initialize socket server if and only if there is a valid specification
    if (state.hostName != nullptr && state.portNumber != 0) {
        Os::TaskString name("ReceiveTask");
        // Uplink is configured for receive so a socket task is started
        comm.configure(state.hostName, state.portNumber);
        comm.startSocketTask(
            name,
            true,
            ConfigConstants::comm::PRIORITY,
            ConfigConstants::comm::STACK_SIZE
        );
    }
    """

    phase Fpp.ToCpp.Phases.freeThreads """
    comm.stopSocketTask();
    (void) comm.joinSocketTask(nullptr);
    """

  }

  instance downlink: Svc.Framer base id 0x4100 {

    phase Fpp.ToCpp.Phases.configObjects """
    Svc::FprimeFraming framing;
    """

    phase Fpp.ToCpp.Phases.configComponents """
    downlink.setup(ConfigObjects::downlink::framing);
    """

  }

  instance fatalAdapter: Svc.AssertFatalAdapter base id 0x4200

  instance fatalHandler: Svc.FatalHandler base id 0x4300

  instance arduinoTime: Svc.Time base id 0x4500 \
      type "Svc::ArduinoTimeImpl" \
      at "../../Arduino/ArduinoTime/ArduinoTimeImpl.hpp"

  instance rgDriver: Svc.RateGroupDriver base id 0x4600 {

    phase Fpp.ToCpp.Phases.configObjects """
    NATIVE_INT_TYPE rgDivs[Svc::RateGroupDriver::DIVIDER_SIZE] = { 1, 2, 4 };
    """
    
    phase Fpp.ToCpp.Phases.configComponents """
    rgDriver.configure(
        ConfigObjects::rgDriver::rgDivs,
        FW_NUM_ARRAY_ELEMENTS(ConfigObjects::rgDriver::rgDivs)
    );
    """

  }

  instance staticMemory: Svc.StaticMemory base id 0x4800

  instance textLogger: Svc.PassiveTextLogger base id 0x4900

  instance uplink: Svc.Deframer base id 0x4A00 {

    phase Fpp.ToCpp.Phases.configObjects """
    Svc::FprimeDeframing deframing;
    """

    phase Fpp.ToCpp.Phases.configComponents """
    uplink.setup(ConfigObjects::uplink::deframing);
    """

  }

  instance rateDriver: HardwareRateDriver.HardwareRateDriver base id 0x4900 \
    type "HardwareRateDriver::HardwareRateDriver" \
    at "../../Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp" \
  

  instance ledPin: Arduino.GpioDriver base id 0x5000
  instance blinker: ArduinoBlink.LedBlinker base id 0x5100
}
