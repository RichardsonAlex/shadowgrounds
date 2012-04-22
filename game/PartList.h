
#ifndef PARTLIST_H
#define PARTLIST_H

#include "GameObject.h"
#include "Part.h"

template<typename T> class LinkedList;

namespace game
{

  class PartList : public GameObject
  {
  public:
    PartList();
    ~PartList();

    virtual SaveData *getSaveData() const;

    virtual const char *getStatusInfo() const;

    int getAllPartAmount();
    int getOwnedPartAmount(int player);

    LinkedList<Part*> *getAllParts();
    LinkedList<Part*> *getOwnedParts(int player);

    void addPart(Part *part);
    void removePart(Part *part);

  private:
    LinkedList<Part*> *allParts;
    LinkedList<Part*> **ownedParts;
  };

}

#endif

