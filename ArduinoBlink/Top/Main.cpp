#include <ArduinoBlink/Top/Components.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Os/Log.hpp>
#ifdef ARDUINO
    #include <ATmega/ATmegaOs/Arduino/StreamLog.hpp>
    #include <Arduino.h>
    #include <ATmega/ATmegaOs/AVR/XMem.hpp>
#endif

#define STARTUP_DELAY_MS 2000

#if defined (DEBUG_TOP_FREE_RAM) || defined (DEBUG_TOP_SETUP)
    #ifdef ARDUINO
        // #include <Arduino.h>
        #include <ATmega/vendor/libraries/MemoryFree/MemoryFree.h>
    #endif
    #ifndef DEBUG_Serial
        #define DEBUG_Serial Serial
    #endif
#endif

/**
 * In a production deployment, the following version definitions should
 * be kept in a component that can telemeter the values on-demand, and
 * those definitions can be used directly in the logMsg call rather than
 * being re-defined below.
 */
#define ARDUINOBLINK_VERSION_MAJOR 0
#define ARDUINOBLINK_VERSION_MINOR 0
#define ARDUINOBLINK_VERSION_PATCH 1

/**
 * Main function for Arduino Blink Deployment executable.
 */
int main(int argc, char* argv[]) {
#ifdef ARDUINO
    init();
#endif

#ifdef ARDUINO
    #ifndef LOG_Serial
        #ifndef DEBUG_Serial
            #define LOG_Serial Serial
        #else
            #define LOG_Serial DEBUG_Serial
        #endif
    #endif

    LOG_Serial.begin(115200);
    Os::setArduinoStreamLogHandler(&LOG_Serial);
#endif
    Os::Log logger;

#ifndef RELEASE_BUILD
    Fw::Logger::logMsg("\r\nArduinoBlink Version %d.%d.%d-devel\r\n",
                       ARDUINOBLINK_VERSION_MAJOR,
                       ARDUINOBLINK_VERSION_MINOR,
                       ARDUINOBLINK_VERSION_PATCH);
#else
    Fw::Logger::logMsg("\r\nArduinoBlink Version %d.%d.%d\r\n",
                       ARDUINOBLINK_VERSION_MAJOR,
                       ARDUINOBLINK_VERSION_MINOR,
                       ARDUINOBLINK_VERSION_PATCH);
#endif
    delay(2000);

#ifdef ARDUINO
    // Two quick flashes for viz indication
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(600);
#endif

#ifdef DEBUG_TOP_FREE_RAM
    #ifdef ARDUINO
    DEBUG_Serial.print("\nFree RAM: ");
    DEBUG_Serial.println(freeMemory());
    #endif
#endif

    constructApp();

#ifndef ARDUINO
    (void) printf("Starting TaskRunner.\n");
#endif
    while(1){taskRunner.run();}

    return 0;
}
