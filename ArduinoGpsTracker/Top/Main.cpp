#include <Components.hpp>
#include <fprime-arduino/ArduinoTypes/GenericLogAssert.hpp>
#include <Os/Log.hpp>
#ifdef ARDUINO
    #include <fprime-arduino/ArduinoOs/StreamLog.hpp>
    #include <Arduino.h>
#else
    #include <fprime-arduino/ArduinoDrv/SerialDriver/SerialDriver.hpp>
#endif

// Global handlers for this Topology
Fw::LogAssertHook assert;

// Comm serial logger remapping
#ifdef COMM_SERIAL
    #define LOG_PORT Serial1
#else 
    #define LOG_PORT Serial
#endif

U32 FreeMem() { // for Teensy 3.0
    U32 stackTop;
    U32 heapTop;

    // current position of the stack.
    stackTop = (U32) &stackTop;

    // current position of heap.
    void* hTop = malloc(1);
    heapTop = (U32) hTop;
    free(hTop);

    // The difference is (approximately) the free, available ram.
    return stackTop - heapTop;
}

#define STARTUP_DELAY_MS 2000

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
    Os::Log logger;
    assert.registerHook();
#ifdef ARDUINO
    // Start Serial for logging, and give logger time to connect
    Serial.begin(115200);
    delay(STARTUP_DELAY_MS);
    // Setup log handler
    Os::setArduinoStreamLogHandler(&LOG_PORT);
    Fw::Logger::logMsg("[SETUP] Logger registered, hello world!\n", 0, 0, 0, 0, 0, 0);
#else
    // Set serial port
    FW_ASSERT(argc <= 2);
    if (argc == 2) {
        Arduino::SERIAL_PORT = reinterpret_cast<char**>(&argv[1]);
    }
#endif
    Fw::Logger::logMsg("[SETUP] Constructing system\n", 0, 0, 0, 0, 0, 0);
    constructApp();
    Fw::Logger::logMsg("[SETUP] Lanuching rate groups\n", 0, 0, 0, 0, 0, 0);
    // Start the task for the rate group
    U32 cycle = 0;
    while (1) {
        U32 mem = FreeMem();
	if (cycle == 0) {
	    Fw::Logger::logMsg("[RAM] Free: %lu\n", mem);
        }
        taskRunner.run();
	cycle = (cycle + 1) % 100000;
    }
    return 0;
}
