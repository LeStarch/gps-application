// ======================================================================
// \title  RadioForwarderComponentImpl.hpp
// \author starchmd
// \brief  hpp file for RadioForwarder component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef RadioForwarder_HPP
#define RadioForwarder_HPP

#include "ArduinoGround/RadioForwarder/RadioForwarderComponentAc.hpp"

namespace Arduino {

  class RadioForwarderComponentImpl :
    public RadioForwarderComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object RadioForwarder
      //!
      RadioForwarderComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object RadioForwarder
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object RadioForwarder
      //!
      ~RadioForwarderComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );
      char storage[1024];
    };

} // end namespace Arduino

#endif
