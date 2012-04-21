
#ifndef GAMEOBJECTLIST_H
#define GAMEOBJECTLIST_H

#include "../container/LinkedList.h"

namespace game
{

  // incomplete class def...
  class GameObject;


  class GameObjectList
  {
  public:
    GameObjectList();
    ~GameObjectList();
    
    const ListNode<GameObject*>* add(GameObject *obj);
    void remove(GameObject *obj);
    void removeByNode(const ListNode<GameObject*>* node, GameObject* obj);

    void resetIterate();
    bool iterateAvailable();
    GameObject *iterateNext();

  private:
    LinkedList<GameObject*> *objects;

  };

}

#endif
