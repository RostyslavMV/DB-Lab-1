#pragma once
#include "Rocket.h"
#define _CRT_SECURE_NO_DEPRECATE
#define SIZE 1000

struct IndexAddress {
	int index;
	int address;
};

class DataBase
{
public:
	void get_m(int index);
	void get_s(int index_s,int index_m);
	void delete_m(int index);
	void delete_s(int index_s, int index_m);
	void update_m(int index, char newModelName[30], int newStagesNumber);
	void update_s(int index_s, int index_m, char newMissionName[30]);
	void insert_m(RocketModel* rocketModel);
	void insert_s(Rocket* rocket);
	void ut_m();
	void ut_s();
	void Init();
private:
	int rocketModelCount = 0;
	int rocketCount = 0;

	int rocketModelEndAddress = 0;
	int rocketEndAddress = 0;
	IndexAddress indexTable[SIZE];

	const char* filename_m = "RocketModels.bin";
	const char* filename_s = "Rockets.bin";
	const char* filename_i = "RocketModelsIndexes.bin";

	void loadIndexTable();
	void rewriteIndexTable();
	void sortTable();
	int getAddress(int index);
	void deleteOnIndex(int index);
	void rewriteAddressOfRocket(int oldAddress, int newAddress);
};

