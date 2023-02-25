#include <Os/Log.hpp>
#include <ArduinoBlink/Top/ArduinoBlinkTopologyAc.hpp>
#include <FprimeArduino.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>
#include <Arduino/Os/StreamLog.hpp>

// Enable the console logging provided by Os::Log
Os::Log logger;

extern "C" {
    int _write( int handle, char *buf, int count) {
        Serial2.write(buf, count);
         return count;
    }
};
#include <new>
namespace std {
    const std::nothrow_t nothrow;
}
void* operator new(unsigned int size, std::nothrow_t const&){ return malloc(size);}
void* operator new[](unsigned int size, std::nothrow_t const&){ return malloc(size);}

Os::TaskRunner taskRunner;

int main() {
    Serial2.begin(115200);
    Os::setArduinoStreamLogHandler(&Serial2);
    ArduinoBlink::TopologyState state;
    ArduinoBlink::setup(state);
    digitalWrite(13, 1);
    while (1) {
        taskRunner.run();
    }
}

