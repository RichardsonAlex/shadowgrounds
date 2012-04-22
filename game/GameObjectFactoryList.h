
#ifndef GAMEOBJECTFACTORYLIST_H
#define GAMEOBJECTFACTORYLIST_H

#include "IGameObjectFactory.h"

template<typename T> class LinkedList;

namespace game
{
  class GameObjectFactoryNode;

  class GameObjectFactoryList
  {
  public:
    GameObjectFactoryList();
    ~GameObjectFactoryList();

    void addFactory(int id, IGameObjectFactory *factory);
    IGameObjectFactory *getById(int id);

  private:
    LinkedList<GameObjectFactoryNode*> *factories;

  };

}

#endif
