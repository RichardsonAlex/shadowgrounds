#ifndef NET_DUMMYBIND_H
#define NET_DUMMYBIND_H

// Copyright(C) Jukka Kokkonen, 2002

#include "../INetBind.h"
#include "DummyConnection.h"

template<typename T> class LinkedList;

namespace net
{
  namespace dummy
  {
    // proto
    class DummyDriver;


    /**
     * Dummy net bind interface.
     */
    class DummyBind : public INetBind
    {
    public:
      DummyBind(const char *name);

      virtual INetConnection *acceptConnection()
        throw (NetDriverException*);

      virtual void listen(int backlog)
        throw (NetDriverException*);

      virtual int getMaxBacklog();

      virtual void unbind()
        throw (NetDriverException*);

      virtual ~DummyBind();

      const char *getName();

    private:
      char *name;
      int acceptAmount;

      LinkedList<DummyConnection*> *acceptedConnections;

      void addAcceptedConnection(DummyConnection *connection);

      bool isAcceptingConnections();

      friend DummyDriver;
    };
  }
}

#endif

