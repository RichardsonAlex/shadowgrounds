
#ifndef NET_NETDRIVERMANAGER_H
#define NET_NETDRIVERMANAGER_H

#include "INetDriver.h"

template<typename T> class LinkedList;

namespace net
{
  class NetDriverManager
  {
  public:
    static void registerDriver(INetDriver *driver);

    static INetDriver *getDriver(char *name);

  private:
    static LinkedList<INetDriver*> *driverList;
  };
}

#endif

