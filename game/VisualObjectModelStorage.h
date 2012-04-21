
#ifndef VISUALOBJECTMODELSTORAGE_H
#define VISUALOBJECTMODELSTORAGE_H

template<typename T> class LinkedList;
namespace ui
{
	class VisualObjectModel;
}

namespace game
{
	class VisualObjectModelStorage
	{
		public:
			VisualObjectModelStorage();

			~VisualObjectModelStorage();

			void clear();

			ui::VisualObjectModel *getVisualObjectModel(const char *filename);

		private:
			LinkedList<ui::VisualObjectModel*>* models;
	};
}

#endif

