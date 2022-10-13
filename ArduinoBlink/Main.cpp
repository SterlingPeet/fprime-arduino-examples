#include <Os/Log.hpp>
#include <ArduinoBlink/Top/ArduinoBlinkTopologyAc.hpp>

// Enable the console logging provided by Os::Log
Os::Log logger;


void setup() {
    ArduinoBlink::TopologyState state;
    ArduinoBlink::setup(state);
}


void loop() {

}