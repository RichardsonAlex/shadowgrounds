
#include "precompiled.h"

#ifdef _MSC_VER
#pragma warning(disable:4103)
#pragma warning(disable:4786)
#endif

#include "DecorationManager.h"

#include "Decoration.h"
#include "VisualObject.h"
#include "../container/LinkedList.h"
#include "../util/ColorMap.h"
#include "../system/Logger.h"


namespace ui
{

	DecorationManager::DecorationManager()
  {
    decorList = new LinkedList<Decoration*>();
  }


  DecorationManager::~DecorationManager()
  {
		while (!decorList->isEmpty())
		{
			Decoration *d = decorList->popLast();
			delete d;
		}
		delete decorList;
  }


  Decoration *DecorationManager::createDecoration()
  {
		Decoration *decor = new Decoration();
		decorList->append(decor);
		return decor;
  }


  void DecorationManager::deleteDecoration(Decoration *decoration)
  {
		decorList->remove(decoration);
		delete decoration;
	}


  Decoration *DecorationManager::getDecorationByName(const char *name) const
  {
		LinkedListIterator<Decoration*> iter(decorList);
		while (iter.iterateAvailable())
		{
			Decoration *decor = iter.iterateNext();
			if (decor->name != NULL && strcmp(decor->name, name) == 0)
			{
				return decor;
			}
		}
		return NULL;
  }


  void DecorationManager::run()
  {
		LinkedListIterator<Decoration*> iter(decorList);
		while (iter.iterateAvailable())
		{
			Decoration *decor = iter.iterateNext();
			decor->run();
		}
  }


  void DecorationManager::synchronizeAllDecorations() const
  {
		LinkedListIterator<Decoration*> iter(decorList);
		while (iter.iterateAvailable())
		{
			Decoration *decor = iter.iterateNext();
			for (int i = 0; i < DECORATION_MAX_EFFECTS; i++)
				decor->effectValue[i] = 0;
		}
  }

	void DecorationManager::updateDecorationIllumination(util::ColorMap *colorMap)
	{
		LinkedListIterator<Decoration*> iter(decorList);
		while (iter.iterateAvailable())
		{
			Decoration *decor = (Decoration *)iter.iterateNext();
			if (decor->getVisualObject() != NULL)
			{
				VC3 pos = decor->getPosition();
				COL col = colorMap->getColorAtScaled(pos.x, pos.z);
				decor->getVisualObject()->setSelfIllumination(col);
			}
		}
	}


	int DecorationManager::getIdForDecoration(Decoration *decor)
	{
		assert(decor != NULL);

		int i = DECORID_LOWEST_POSSIBLE_VALUE;

		LinkedListIterator<Decoration*> iter(decorList);
		while (iter.iterateAvailable())
		{
			Decoration *d = iter.iterateNext();
			if (decor == d) return i;
			i++;
		}

		assert(!"DecorationManager::getIdForDecoration - Unable to solve an id for given decoration.");
		return 0;
	}

	Decoration *DecorationManager::getDecorationById(int id)
	{
		int i = DECORID_LOWEST_POSSIBLE_VALUE;

		LinkedListIterator<Decoration*> iter(decorList);
		while (iter.iterateAvailable())
		{
			Decoration *d = iter.iterateNext();
			if (i == id) return d;
			i++;
		}

		Logger::getInstance()->debug("DecorationManager::getDecorationById - Given id did not match any decoration.");
		//assert(!"DecorationManager::getDecorationById - Given id did not match any decoration.");
		return NULL;
	}



}




