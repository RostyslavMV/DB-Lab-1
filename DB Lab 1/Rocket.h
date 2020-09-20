#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>

class RocketModel
{
public:
	int index;
	char modelName[30];
	int stagesNumber;
	int firstRocketAddress;

	RocketModel() {
		this->index = -1;
		this->stagesNumber = -1;
		this->firstRocketAddress = -1;
	}

	RocketModel(char modelName[30], int stagesNumber, int index) {
		strncpy_s(this->modelName, modelName, 30);
		this->stagesNumber = stagesNumber;
		this->index = index;
		this->firstRocketAddress = -1;
	}
};



class Rocket
{
public:
	int rocketModelIndex;
	char missionName[30];
	int nextRocketAddress;

	Rocket(char missionName[30],int rocketModelIndex) {
		strncpy_s(this->missionName, missionName, 30);
		this->nextRocketAddress = -1;
		this->rocketModelIndex = rocketModelIndex;
	}
};

