// ======================================================================
// \title  RadioForwarderComponentImpl.cpp
// \author starchmd
// \brief  cpp file for RadioForwarder component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <ArduinoGround/RadioForwarder/RadioForwarderComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  RadioForwarderComponentImpl ::
    RadioForwarderComponentImpl(
        const char *const compName
    ) :
      RadioForwarderComponentBase(compName)
  {

  }

  void RadioForwarderComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    RadioForwarderComponentBase::init(instance);
  }

  RadioForwarderComponentImpl ::
    ~RadioForwarderComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void RadioForwarderComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< The call order*/
    )
  {
     Fw::Buffer buffer;
     buffer.setdata(reinterpret_cast<U64>(this->storage));
     buffer.setsize(static_cast<U64>(sizeof(this->storage)));
     // Poll radio and echo to serial
     radioPoll_out(0, buffer);
     if (buffer.getsize() > 0) {
         serialWrite_out(0, buffer);
     }
     // Reset buffer to hold the full size again
     buffer.setdata(reinterpret_cast<U64>(this->storage));
     buffer.setsize(static_cast<U64>(sizeof(this->storage)));
     // Poll serial and echo to radio
     serialPoll_out(0, buffer);
     if (buffer.getsize() > 0) {
         radioWrite_out(0, buffer);
     }
     buffer.setsize(static_cast<U64>(sizeof(this->storage)));
  }

} // end namespace Arduino
