#include <Fw/Types/Assert.hpp>
#include <Os/Task.hpp>
#include <Os/Log.hpp>
#include <Os/File.hpp>
#include <Fw/Types/MallocAllocator.hpp>
#include <ArduinoGround/Top/ArduinoSchedContexts.hpp>
#include "ArduinoGround/Top/Components.hpp"

// Setup the rate group driver used to drive all the ActiveRateGroups connected to it.
// For each active rate group, there is a rate divisor that represents how often it is run.
static NATIVE_INT_TYPE rate_divisors[] = {2, 100};
Svc::RateGroupDriverImpl rateGroupDriverComp(FW_OPTIONAL_NAME("RGDRV"), rate_divisors, FW_NUM_ARRAY_ELEMENTS(rate_divisors));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in RPITopologyAi.xml
static NATIVE_UINT_TYPE rg20HzContext[] = {Arduino::CONTEXT_RPI_DEMO_20Hz, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup20HzComp(FW_OPTIONAL_NAME("RG20Hz"),rg20HzContext,FW_NUM_ARRAY_ELEMENTS(rg20HzContext));
static NATIVE_UINT_TYPE rg1HzContext[] = {0, 0, Arduino::CONTEXT_RPI_DEMO_1Hz, 0};
Svc::ActiveRateGroupImpl rateGroup1HzComp(FW_OPTIONAL_NAME("RG1Hz"),rg1HzContext,FW_NUM_ARRAY_ELEMENTS(rg1HzContext));

// Standard system components
Svc::ActiveLoggerImpl eventLogger(FW_OPTIONAL_NAME("EventLogger"));
Svc::TlmChanImpl chanTlm(FW_OPTIONAL_NAME("Telemetry"));
Svc::CommandDispatcherImpl cmdDisp(FW_OPTIONAL_NAME("CmdDisp"));
Svc::HealthImpl health(FW_OPTIONAL_NAME("Health"));

Svc::GroundInterfaceComponentImpl groundInterface(FW_OPTIONAL_NAME("Ground"));

// Arduino specific components
Arduino::HardwareRateDriver hardwareRateDriver(FW_OPTIONAL_NAME("HardDriver"), 10);
Svc::ArduinoTimeImpl timeImpl(FW_OPTIONAL_NAME("Time"));
Arduino::RadioWrapperComponentImpl radio(FW_OPTIONAL_NAME("RADIO"));
Arduino::RadioForwarderComponentImpl relay(FW_OPTIONAL_NAME("RELAY"));

// Baremetal setup for the task runner
Os::TaskRunner taskRunner;


Arduino::SerialDriverComponentImpl comm(FW_OPTIONAL_NAME("COMM"), 0);

const char* getHealthName(Fw::ObjBase& comp) {
   #if FW_OBJECT_NAMES == 1
       return comp.getObjName();
   #else
      return "";
   #endif
}
/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
void constructApp() {
    timeImpl.init(0);
    // Initialize rate group driver
    rateGroupDriverComp.init();

    // Initialize the rate groups
    rateGroup20HzComp.init(10, 0);
    rateGroup1HzComp.init(10, 1);

    // Initialize the core data handling components
    eventLogger.init(10, 0);
    chanTlm.init(20, 0);
    cmdDisp.init(10,0);
    health.init(25,0);
    groundInterface.init(0);
    comm.init(0, 115200);
    relay.init(0);
    radio.init(0, NODEID_GROUND, NODEID_REMOTE);

    // Callback to initialize architecture, connect ports, etc.
    constructArduinoArchitecture();

    // Register all commands into the system
    cmdDisp.regCommands();
    eventLogger.regCommands();
    health.regCommands();

    // Setup the health an ping entries. These need to be in the same order as the
    // ports connected to the health component. Once the ping entry array is created
    // pass it into the ping-entries array.
    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3, 5, getHealthName(rateGroup20HzComp)},
        {3, 5, getHealthName(rateGroup1HzComp)},
        {3, 5, getHealthName(cmdDisp)},
        {3, 5, getHealthName(chanTlm)},
        {3, 5, getHealthName(eventLogger)}
    };
    health.setPingEntries(pingEntries,FW_NUM_ARRAY_ELEMENTS(pingEntries),0x123);
    hardwareRateDriver.start();
    // Start all active components' tasks thus finishing the setup portion of this code
    rateGroup20HzComp.start(0, 120, 10 * 1024);
    rateGroup1HzComp.start(0, 119, 10 * 1024);
    cmdDisp.start(0, 101, 10 * 1024);
    eventLogger.start(0, 98, 10 * 1024);
    chanTlm.start(0, 97, 10 * 1024);
}
/**
 * Exit Tasks:
 *
 * Exits the tasks in preparation for stopping the software. This is likely
 * not needed for Arduino projects, as they run forever, however; it is here
 * for completeness.
 */
void exitTasks(void) {
    rateGroup1HzComp.exit();
    rateGroup20HzComp.exit();
    cmdDisp.exit();
    eventLogger.exit();
    chanTlm.exit();
}
