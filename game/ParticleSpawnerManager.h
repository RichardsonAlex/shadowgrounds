
#ifndef PARTICLESPAWNERMANAGER_H
#define PARTICLESPAWNERMANAGER_H

template<typename T> class LinkedList;

#include <DatatypeDef.h>

namespace game
{
  class Game;

  class ParticleSpawner;

  class ParticleSpawnerManager
  {
    public:
      ParticleSpawnerManager(Game *game);

      ~ParticleSpawnerManager();

      ParticleSpawner *createParticleSpawner();

      void deleteParticleSpawner(ParticleSpawner *spawner);

      ParticleSpawner *getParticleSpawnerByName(const char *name);

      void deleteAllParticleSpawners();
      void disableAllParticleSpawners();

			int getParticleSpawnerAmount();

      void run();

			void setPlayerPosition(const VC3 &playerPosition);

    private:
      Game *game;

      LinkedList<ParticleSpawner*> *spawnerList;

			VC3 playerPosition;

  };
}

#endif


