// ====================================================================== 
// \title  RadioWrapperImpl.cpp
// \author lestarch
// \brief  cpp file for RadioWrapper component implementation class
// ====================================================================== 


#include <ArduinoGpsTracker/RadioWrapper/RadioWrapper.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Arduino.h>

namespace Arduino {

  void RadioWrapperComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance,
        const U8 node,
        const U8 dest
    )
  {
      RadioWrapperComponentBase::init(instance);
      m_radio.setCS(15);
      bool success = m_radio.initialize(RF69_915MHZ, node, NETWORK_ID);
      m_radio.setHighPower();
      m_dest = dest;
  }


  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void RadioWrapperComponentImpl ::
    write_data(
        Fw::Buffer &fwBuffer
    )
  {
      m_radio.send(m_dest, reinterpret_cast<U8*>(fwBuffer.getdata()), fwBuffer.getsize());
  }

  void RadioWrapperComponentImpl ::
    read_data(Fw::Buffer& fwBuffer)
  {
      U32 i = 0;
      fwBuffer.setsize(0);
      if (m_radio.receiveDone()) {
          for (i = 0; i < m_radio.DATALEN; i++) {
              reinterpret_cast<U8*>(fwBuffer.getdata())[i] = m_radio.DATA[i];  
          }
          fwBuffer.setsize(m_radio.DATALEN);
      }
  }
} // end namespace Svc
