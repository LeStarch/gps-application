#ifndef __ARD_COMPONENTS_HEADER__
#define __ARD_COMPONENTS_HEADER__

#define COMM_SERIAL
void constructArduinoArchitecture(void);
void exitTasks(void);
void constructApp();

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>
#include <Svc/PrmDb/PrmDbImpl.hpp>
#include <Fw/Obj/SimpleObjRegistry.hpp>
#include <Svc/Health/HealthComponentImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>
#include <Svc/AssertFatalAdapter/AssertFatalAdapterComponentImpl.hpp>
#include <Svc/FatalHandler/FatalHandlerComponentImpl.hpp>

#include <ArduinoGpsTracker/LedBlinker/LedBlinker.hpp>
#include <fprime-arduino/ArduinoDrv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <fprime-arduino/ArduinoDrv/SerialDriver/SerialDriver.hpp>
#include <fprime-arduino/ArduinoTime/ArduinoTimeImpl.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>

#include <ArduinoGpsTracker/RadioWrapper/RadioWrapper.hpp>
#include <ArduinoGpsTracker/Gps/GpsComponentImpl.hpp>

//Core components. Gotta run them all
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Svc::ActiveRateGroupImpl rateGroup1HzComp;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::TlmChanImpl chanTlm;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::GroundInterfaceComponentImpl groundInterface;
extern Svc::AssertFatalAdapterComponentImpl fatalAdapter;
extern Svc::FatalHandlerComponentImpl fatalHandler;
extern Svc::HealthImpl health;
extern Arduino::LedBlinkerComponentImpl ledBlinker;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern Svc::ArduinoTimeImpl time;
extern Arduino::SerialDriverComponentImpl gpsSerialDriver;
extern Gps::GpsComponentImpl gps;
// Scheduler definition
extern Os::TaskRunner taskRunner;

#ifdef COMM_SERIAL
  extern Arduino::SerialDriverComponentImpl comm;
#else
  extern Arduino::RadioWrapperComponentImpl comm;
#endif
#endif
