#include "ParticleSystem.h"

#define N 1000

int main() {
	//create one array of particles and one array to store the dead particle indicies
	particle* List = new particle[N];
	int* Deads = new int[N];

	//spawn location
	vec3 Spawn = vec3(5, 2, 8);

	pInfo INFO;

	INFO.number = N;	//how many
	INFO.Spawn = Spawn;	//location
	INFO.actives = N;
	INFO.dead_i = 0;	//dead particle index
	int cycles = 0;

	//spawn N particles
	summonParticles(INFO, List, Deads);

	//run the simulation
	printf("\nStart: Cycle %d\n\n", cycles);
	while (true)
	{
		//update
		updateParticles(INFO, List, Deads, cycles);

		//stop after 3 cycles...
		if (cycles == 3 && INFO.actives<=1) {
			break;
		}
	}

	//Print the simulation end
	printf("\nAll particles dead! ALIVE:%d CYCLES: %d\n", INFO.actives-1, cycles);

	//Free the memory
	delete[] List;
	delete[] Deads;
	return 0;
}