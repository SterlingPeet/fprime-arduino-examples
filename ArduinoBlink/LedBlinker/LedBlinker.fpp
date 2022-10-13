module ArduinoBlink {

  passive component LedBlinker {

    sync input port run: [1] Svc.Sched

    output port gpio: [1] Drv.GpioWrite

    @ Command to telemeter the current parameter values in use.
    sync command downlinkParams \
      opcode 0

    @ Report parameter update
    event LedBlinkerParameterUpdated(
                                      $id: U32 @< The ID argument
                                    ) \
      severity activity low \
      id 0 \
      format "Led Blinker Parameter {} was updated"


    @ A port for getting the time
    time get port timeGetOut

    @ A port for emitting telemetry
    telemetry port tlmOut

    @ A port for emitting events
    event port eventOut

    @ A port for emitting text events
    text event port textEventOut

    @ A port for receiving commands
    command recv port cmdIn

    @ A port for sending command registration requests
    command reg port cmdRegOut

    @ A port for sending command responses
    command resp port cmdResponseOut

    @ A port for getting parameter values
    param get port prmGetOut

    @ A port for setting parameter values
    param set port prmSetOut

    @ The number of sched cycles to skip before changing LED state, higher is longer.
    param blinkDecimate: U8 default 2 id 0 \
      set opcode 1 \
      save opcode 2

    @ Number of blinks since startup
    telemetry numBlinks: U32 id 0

    @ Current setting of the blinkDecimate parameter.
    telemetry blinkDecimate: U8 id 1

  }

}
