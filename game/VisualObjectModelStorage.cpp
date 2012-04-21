
#include "precompiled.h"

#include "VisualObjectModelStorage.h"

#include <cassert>
#include <cstring>

#include "../ui/VisualObjectModel.h"
#include "../container/LinkedList.h"

using namespace ui;

namespace game
{
	VisualObjectModelStorage::VisualObjectModelStorage()
	{
		models = new LinkedList<VisualObjectModel*>();
	}

	VisualObjectModelStorage::~VisualObjectModelStorage()
	{
		clear();
		delete models;
	}

	void VisualObjectModelStorage::clear()
	{
		while (!models->isEmpty())
		{
			VisualObjectModel *vom = models->popLast();
			delete vom;
		}
	}

	VisualObjectModel *VisualObjectModelStorage::getVisualObjectModel(const char *filename)
	{
		// TODO: optimize? is it necessary?
		LinkedListIterator<VisualObjectModel*> iter(models);
		while (iter.iterateAvailable())
		{
			VisualObjectModel *vom = iter.iterateNext();
			if (filename == NULL && vom->getFilename() == NULL)
				return vom;
			if (vom->getFilename() != NULL && filename != NULL
				&& strcmp(vom->getFilename(), filename) == 0)
				return vom;
		}
		VisualObjectModel *newvom = new VisualObjectModel(filename);
		models->append(newvom);
		return newvom;
	}

}

