
#include "precompiled.h"

#include <assert.h>

#include "GameObjectList.h"
#include "GameObject.h"
#include "../util/Debug_MemoryManager.h"

namespace game
{

  GameObjectList::GameObjectList() {
      objects = new LinkedList<GameObject*>();
  }

  GameObjectList::~GameObjectList()
  {
    // NOTICE: does not delete the objects listed by this one, but only the
    // list of them. All listnode pointers of the objects listed by this one
    // are invalid now, though.

    // Check that all game objects were deleted.
    assert(objects.isEmpty());

    delete objects;
  }

  void GameObjectList::add(GameObject *obj)
  {
    objects->append(obj);
  }

  void GameObjectList::remove(GameObject *obj)
  {
    objects->remove(obj);
  }

  // NOTE, iterator is not a seperate object -> not thread safe

  void GameObjectList::resetIterate()
  {
    objects->resetIterate();
  }

  bool GameObjectList::iterateAvailable()
  {
    return objects->iterateAvailable();
  }

  GameObject* GameObjectList::iterateNext()
  {
    return objects->iterateNext();
  }

}

