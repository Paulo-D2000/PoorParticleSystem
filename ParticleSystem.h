#pragma once
#ifndef PARTICLESYSTEM_H

#include <iostream>
inline float random_float() {
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random_float();
}

struct vec3 {
	float x, y, z;
	vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vec3(float x) {
		this->x = x;
		this->y = x;
		this->z = x;
	}
	vec3() {
		x = 0;
		y = 0;
		z = 0;
	}
	vec3 random() {
		return vec3(random_float(), random_float(), random_float());
	}
};

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

//Particle object
struct particle {
	vec3 pos;
	vec3 vel;
	float lifetime;
	particle() {
		pos = vec3(0.0);
		vel = vec3(0.0);
		lifetime = 99.0;
	}
	particle(vec3 pos, vec3 vel, float lifetime) {
		this->pos = pos;
		this->vel = vel;
		this->lifetime = lifetime;
	}
};

//particle info
struct pInfo {
	vec3 Spawn;
	int actives;
	int dead_i;
	int number;
};

//summon pInfo.{number} particles at pInfo.{Spawn(x,y,z)} with random speed!
void summonParticles(pInfo& info, particle* list, int* deads) {
	for (int i = 0; i < info.number; i++) {
		list[i] = particle(info.Spawn, vec3().random(), random_float(1.0f, 99.0f));
		deads[i] = -1;
	}
}

void updateParticles(pInfo& info, particle* list, int* deads, int& cycles) {
	//reduce one random particle life time
	list[int(random_float(0, info.number - 1))].lifetime -= 0.1;

	//update all the active positions!
	for (int i = 0; i < info.actives; i++)
	{
		//if the particle is dead skip it
		if (i == deads[info.dead_i]) continue;

		//if the lifetime has ended add it to the deads list 
		if (list[i].lifetime < 0.0) {
			deads[info.dead_i++] = i;
			info.actives--;
		}
		else {
			//step the lifitime
			list[i].lifetime -= 1.0;
			//update the position
			list[i].pos = list[i].pos + list[i].vel;
			//debug
			printf("%d alive\n", info.actives - 1);
		}
	}

	//if the active particles all have died summon new ones
	if (info.actives <= 0) {
		//debug
		printf("\nRestart: Cycle %d\n\n", cycles);
		cycles++;
		info.actives = info.number;
		info.dead_i = 0;
		summonParticles(info, list, deads);
	}

}

#endif // !PARTICLE_SYSTEM_H