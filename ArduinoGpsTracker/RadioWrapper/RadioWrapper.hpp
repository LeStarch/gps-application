// ====================================================================== 
// \title  RadioWrapperImpl.hpp
// \author lestarch
// \brief  hpp file for RadioWrapper component implementation class
// ====================================================================== 

#ifndef RadioWrapper_HPP
#define RadioWrapper_HPP

#include "ArduinoGpsTracker/RadioWrapper/RadioWrapperComponentAc.hpp"
#include "ArduinoGpsTracker/RFM69/RFM69.h"

#define NODEID_GROUND 0
#define NODEID_REMOTE 1
#define NETWORK_ID 50
namespace Arduino {

  class RadioWrapperComponentImpl :
    public RadioWrapperComponentBase
  {

    public:
      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object RadioWrapper
      //!
      RadioWrapperComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object RadioWrapper
      //!
      void init(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U8 node, /*!< node ID for radio */
          const U8 dest  /*!< node ID for destination radio */
      );

      //! Destroy object RadioWrapper
      //!
      ~RadioWrapperComponentImpl(void);

    PRIVATE:
      //! Read the actual data
      void read_data(Fw::Buffer &fwBuffer);
      //! Write the actual data
      void write_data(Fw::Buffer &fwBuffer);
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for write
      //!
      void write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer 
      );

      //! Handler implementation for readPoll
      //!
      void readPoll_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer 
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );
#ifdef ARDUINO
      RFM69 m_radio;
#else
      //! Data store for self-generated serial data
      U8 m_data[61]; // Max data in 1/10th second at 115200
#endif
      //! Buffer to wrap
      Fw::Buffer m_local_buffer;
      //! Destination node
      U8 m_dest;
    };

} // end namespace Arduino

#endif
