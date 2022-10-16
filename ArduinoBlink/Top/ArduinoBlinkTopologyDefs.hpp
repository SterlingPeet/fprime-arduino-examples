#ifndef TopologyDefs_HPP
#define TopologyDefs_HPP

#include "Fw/Types/MallocAllocator.hpp"
#include "ArduinoBlink/Top/FppConstantsAc.hpp"
#include "Svc/FramingProtocol/FprimeProtocol.hpp"

namespace ArduinoBlink {

  namespace Allocation {
    // Malloc allocator for topology construction
    extern Fw::MallocAllocator mallocator;
  }
  struct TopologyState {
      const PlatformIntType LED_PIN = 13;
  };

}

#endif
