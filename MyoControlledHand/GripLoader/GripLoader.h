#ifndef GripLoader_h
#define GripLoader_h

#include "Arduino.h"
#include "Config.h"
#include "GripUtil.h"

class GripLoader {
  public:

    GripLoader();

    Grip load(String gripName);

  private:
};


#endif // GripLoader_h
