
#ifndef GAMEOBJECTLIST_H
#define GAMEOBJECTLIST_H

template<typename T> class LinkedList;

namespace game
{

  // incomplete class def...
  class GameObject;


  class GameObjectList
  {
  public:
    GameObjectList();
    ~GameObjectList();

    void add(GameObject *obj);
    void remove(GameObject* obj);

    void resetIterate();
    bool iterateAvailable();
    GameObject* iterateNext();

  private:
    LinkedList<GameObject*> *objects;

  };

}

#endif
