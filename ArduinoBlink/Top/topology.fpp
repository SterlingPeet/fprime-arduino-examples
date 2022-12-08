module ArduinoBlink {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

    enum Ports_RateGroups {
      rg1
    }

    enum Ports_StaticMemory {
      downlink
    }

  topology ArduinoBlink {

    # ----------------------------------------------------------------------
    # Instances used in the topology
    # ----------------------------------------------------------------------

    instance chanTlm
    instance cmdDisp
    instance comm
    instance downlink
    instance eventLogger
    instance fatalAdapter
    instance fatalHandler
    instance arduinoTime
    instance rg1
    instance rgDriver
    instance staticMemory
    instance textLogger
    instance uplink
    instance ledPin
    instance rateDriver
    instance blinker

    # ----------------------------------------------------------------------
    # Pattern graph specifiers
    # ----------------------------------------------------------------------

    command connections instance cmdDisp

    event connections instance eventLogger

    telemetry connections instance chanTlm

    text event connections instance textLogger

    time connections instance arduinoTime

    # ----------------------------------------------------------------------
    # Direct graph specifiers
    # ----------------------------------------------------------------------
    connections Blinker {
        blinker.gpio -> ledPin.gpioWrite
    }

    connections Downlink {
      chanTlm.PktSend -> downlink.comIn
      eventLogger.PktSend -> downlink.comIn

      downlink.framedAllocate -> staticMemory.bufferAllocate[Ports_StaticMemory.downlink]
      downlink.framedOut -> comm.send

      comm.deallocate -> staticMemory.bufferDeallocate[Ports_StaticMemory.downlink]
    }

    connections FaultProtection {
      eventLogger.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections RateGroups {
      # Block driver
      rateDriver.CycleOut -> rgDriver.CycleIn
      #rateDriver.error -> ledPin.gpioWrite

      # Rate group 1
      rgDriver.CycleOut[Ports_RateGroups.rg1] -> rg1.CycleIn
      #rg1.RateGroupMemberOut[0] -> chanTlm.Run
      rg1.RateGroupMemberOut[0] -> blinker.run
    }

    connections Uplink {
      #comm.allocate -> staticMemory.bufferAllocate[Ports_StaticMemory.uplink]
      comm.$recv -> uplink.framedIn
      uplink.framedDeallocate -> comm.recvReturn

      uplink.comOut -> cmdDisp.seqCmdBuff
      cmdDisp.seqCmdStatus -> uplink.cmdResponseIn

      #uplink.bufferAllocate -> fileUplinkBufferManager.bufferGetCallee
      #uplink.bufferOut -> fileUplink.bufferSendIn
      #uplink.bufferDeallocate -> fileUplinkBufferManager.bufferSendIn
      #fileUplink.bufferSendOut -> fileUplinkBufferManager.bufferSendIn

    }

  }

}
