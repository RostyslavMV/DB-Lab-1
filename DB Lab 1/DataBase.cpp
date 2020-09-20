#include "DataBase.h"
#include <cstdio>
#include <iostream>
using namespace std;

void DataBase::Init()
{
	FILE* file_m = fopen(filename_m, "wb+");
	fclose(file_m);
	FILE* file_s = fopen(filename_s, "wb+");
	fclose(file_s);
	FILE* file_i = fopen(filename_i, "wb+");
	fclose(file_i);
}

void DataBase::loadIndexTable()
{
	FILE* file_i = fopen(filename_i, "rb+");
	for (int i = 0; i < rocketModelCount; i++) {
		fread(&indexTable[i].index, sizeof(int), 1, file_i);
		fread(&indexTable[i].address, sizeof(int), 1, file_i);
	}
	fclose(file_i);
}

void DataBase::rewriteIndexTable()
{
	FILE* file_i = fopen(filename_i, "wb+");
	for (int i = 0; i < rocketModelCount; i++) {
		fwrite(&indexTable[i].index, sizeof(int), 1, file_i);
		fwrite(&indexTable[i].address, sizeof(int), 1, file_i);
	}
	fclose(file_i);
}

void DataBase::sortTable()
{
	IndexAddress temp;
	for (int i = 0; i < rocketModelCount; i++) {
		for (int j = 0; j < rocketModelCount; j++) {
			if ((indexTable[j].index > indexTable[j + 1].index && indexTable[j + 1].index != NULL
				&& indexTable[j].index != NULL) ||
				(indexTable[j].index == NULL && indexTable[j + 1].index != NULL))
			{
				temp = indexTable[j];
				indexTable[j] = indexTable[j + 1];
				indexTable[j + 1] = temp;
			}
		}
	}
}

int DataBase::getAddress(int index)
{
	for (int i = 0; i < rocketModelCount; i++) {
		if (indexTable[i].index == index) {
			return indexTable[i].address;
		}
	}
	return -1;
}

void DataBase::deleteOnIndex(int index)
{
	for (int i = 0; i < rocketModelCount; i++) {
		if (indexTable[i].index == index) {
			indexTable[i].index = NULL;
			indexTable[i].address = NULL;
			return;
		}
	}
}

void DataBase::rewriteAddressOfRocket(int oldAddress, int newAddress)
{
	FILE* file_m = fopen(filename_m, "rb+");
	int RocketAddress = -1;
	for (int i = 0; i < rocketModelCount; i++) {
		fseek(file_m, 38, SEEK_CUR);
		fread(&RocketAddress, sizeof(int), 1, file_m);
		if (RocketAddress == oldAddress) {
			fseek(file_m, -4, SEEK_CUR);
			fwrite(&newAddress, sizeof(int), 1, file_m);
			break;
		}
	}
	fclose(file_m);
	RocketAddress = -1;
	FILE* file_s = fopen(filename_s, "rb+");
	for (int i = 0; i < rocketCount; i++) {
		fseek(file_s, 30, SEEK_CUR);
		fread(&RocketAddress, sizeof(int), 1, file_s);
		if (RocketAddress == oldAddress) {
			fseek(file_s, -4, SEEK_CUR);
			fwrite(&newAddress, sizeof(int), 1, file_s);
			break;
		}
	}
	fclose(file_s);
}

void DataBase::ut_s()
{
	cout << "ut_s:" << endl;
	FILE* file = fopen(filename_s, "rb+");
	char missionName[30];
	int nextRocketAddress;
	for (int i = 0; i < rocketCount; i++) {
		fread(&missionName, sizeof(missionName), 1, file);
		fread(&nextRocketAddress, sizeof(int), 1, file);
		cout << "Mission name: " << missionName << ", next rocket address: "
			<< nextRocketAddress << endl;
	}
}

void DataBase::ut_m()
{
	cout << "ut_m:" << endl;
	FILE* file = fopen(filename_m, "rb+");
	int index, stagesNumber, firstRocketAddress;
	char modelName[30];
	for (int i = 0; i < rocketModelCount; i++) {
		fread(&index, sizeof(int), 1, file);
		fread(&modelName, sizeof(modelName), 1, file);
		fread(&stagesNumber, sizeof(int), 1, file);
		fread(&firstRocketAddress, sizeof(int), 1, file);
		cout << "index: " << index << ", model name: " << modelName <<
			", number of stages: " << stagesNumber << ", first rocket address: " << firstRocketAddress << endl;
	}

}


void DataBase::get_m(int index)
{
	int offset = getAddress(index);
	if (offset == -1) {
		cout << "There is no rocket model at index " << index << endl;
		return;
	}
	FILE* file_m = fopen(filename_m, "rb+");
	fseek(file_m, offset, SEEK_SET);
	int rocketIndex, stagesNumber, firstRocketAddress;
	char modelName[30];
	fread(&rocketIndex, sizeof(int), 1, file_m);
	fread(&modelName, sizeof(modelName), 1, file_m);
	fread(&stagesNumber, sizeof(int), 1, file_m);
	fread(&firstRocketAddress, sizeof(int), 1, file_m);
	cout << "Rocket model at index " << rocketIndex << " = model name: " << modelName <<
		", number of stages: " << stagesNumber << endl;
	fclose(file_m);
}

void DataBase::get_s(int index_s, int index_m)
{
	int offset_m = getAddress(index_m);
	if (offset_m == -1) {
		cout << "There is no rocket model at index " << index_m << endl;
		return;
	}
	FILE* file_m = fopen(filename_m, "rb+");
	fseek(file_m, offset_m + 38, SEEK_SET);
	int firstRocketAddress;
	fread(&firstRocketAddress, sizeof(int), 1, file_m);
	fclose(file_m);
	if (firstRocketAddress == -1) {
		cout << "There are no rockets of this model" << endl;
		return;
	}
	else {
		FILE* file_s = fopen(filename_s, "rb+");
		fseek(file_s, firstRocketAddress, SEEK_SET);
		char missionName[30];
		if (index_s == 1)
		{
			fread(&missionName, sizeof(missionName), 1, file_s);
			cout << "Rocket model index " << index_m << ". Mission name of with index " <<
				index_s << ": " << missionName << endl;
		}
		else {
			fseek(file_s, 30, SEEK_CUR);
			int nextRocketAddress;
			for (int i = 1; i < index_s; i++) {
				fread(&nextRocketAddress, sizeof(int), 1, file_s);
				fseek(file_s, nextRocketAddress + 30, SEEK_SET);
			}
			if (nextRocketAddress < 0) {
				cout << "There is no rocket with index " << index_s <<
					" for a rocket model with index " << index_m << endl;
				return;
			}
			fseek(file_s, -30, SEEK_CUR);
			fread(&missionName, sizeof(missionName), 1, file_s);
			cout << "Rocket model index " << index_m << ". Mission name of rocket with index " <<
				index_s << ": " << missionName << endl;
		}
		fclose(file_s);
	}
}

void DataBase::delete_m(int index)
{
	int offset_m = getAddress(index);
	if (offset_m == -1) {
		cout << "There is no rocket model at index " << index << endl;
		return;
	}
	FILE* file_m = fopen(filename_m, "rb+");
	int offsetFromEnd = sizeof(RocketModel) - 2;
	fseek(file_m, rocketModelEndAddress - offsetFromEnd, SEEK_SET);
	int rocketIndex, stagesNumber, firstRocketAddress;
	char modelName[30];
	int deletedFirstRocketAddress;
	fread(&rocketIndex, sizeof(int), 1, file_m);
	fread(&modelName, sizeof(modelName), 1, file_m);
	fread(&stagesNumber, sizeof(int), 1, file_m);
	fread(&firstRocketAddress, sizeof(int), 1, file_m);

	fseek(file_m, offset_m + 38, SEEK_SET);
	fread(&deletedFirstRocketAddress, sizeof(int), 1, file_m);
	fseek(file_m, offset_m, SEEK_SET);

	fwrite(&rocketIndex, sizeof(int), 1, file_m);
	fwrite(&modelName, sizeof(modelName), 1, file_m);
	fwrite(&stagesNumber, sizeof(int), 1, file_m);
	fwrite(&firstRocketAddress, sizeof(int), 1, file_m);

	fclose(file_m);
	if (deletedFirstRocketAddress != -1) {
		int nextRocketAddress = deletedFirstRocketAddress;
		FILE* file_s = fopen(filename_s, "rb+");
		char rewritedMissionName[30];
		int rewritedNextRocketAddress;
		int deletedAdress;
		while (nextRocketAddress != -1) {
			deletedAdress = nextRocketAddress;
			fseek(file_s, nextRocketAddress + 30, SEEK_SET);
			fread(&nextRocketAddress, sizeof(int), 1, file_s);
			fseek(file_s, rocketEndAddress - 34, SEEK_SET);
			fread(&rewritedMissionName, sizeof(rewritedMissionName), 1, file_s);
			fread(&rewritedNextRocketAddress, sizeof(int), 1, file_s);
			fseek(file_s, deletedAdress, SEEK_SET);
			fwrite(&rewritedMissionName, sizeof(rewritedMissionName), 1, file_s);
			fwrite(&rewritedNextRocketAddress, sizeof(int), 1, file_s);
			rewriteAddressOfRocket(rocketEndAddress - 34, deletedAdress);
			rocketEndAddress -= sizeof(Rocket) - 6;
			rocketCount--;
		}
		fclose(file_s);
	}

	rocketModelEndAddress -= sizeof(RocketModel) - 2;
	loadIndexTable();
	deleteOnIndex(index);
	sortTable();
	rewriteIndexTable();
	rocketModelCount--;
}

void DataBase::delete_s(int index_s, int index_m)
{
	int offset_m = getAddress(index_m);
	if (offset_m == -1) {
		cout << "There is no rocket model at index " << index_m << endl;
		return;
	}
	FILE* file_m = fopen(filename_m, "rb+");
	int firstRocketAddress;
	fseek(file_m, offset_m + 38, SEEK_SET);
	fread(&firstRocketAddress, sizeof(int), 1, file_m);
	if (firstRocketAddress == -1) {
		cout << "There are no rockets of this model" << endl;
		return;
	}
	else {
		FILE* file_s = fopen(filename_s, "rb+");
		int nextRocketAddress = firstRocketAddress;
		for (int i = 1; i < index_s; i++) {
			fseek(file_s, nextRocketAddress + 30, SEEK_SET);
			fread(&nextRocketAddress, sizeof(int), 1, file_s);
		}
		int deletedAddress = nextRocketAddress;
		if (nextRocketAddress == -1) {
			cout << "There is no rocket with index " << index_s <<
				" for a rocket model with index " << index_m;
			return;
		}
		fseek(file_s, rocketEndAddress - 34, SEEK_SET);
		char rewritedMissionName[30];
		int rewritedNextRocketAddress;
		int deletedNextAddress;
		fread(&rewritedMissionName, sizeof(rewritedMissionName), 1, file_s);
		fread(&rewritedNextRocketAddress, sizeof(int), 1, file_s);
		fseek(file_s, deletedAddress + 30, SEEK_SET);
		fread(&deletedNextAddress, sizeof(int), 1, file_s);
		fseek(file_s, -34, SEEK_CUR);
		fwrite(&rewritedMissionName, sizeof(rewritedMissionName), 1, file_s);
		fwrite(&rewritedNextRocketAddress, sizeof(int), 1, file_s);
		fclose(file_s);
		rewriteAddressOfRocket(deletedAddress, deletedNextAddress);
		rewriteAddressOfRocket(rocketEndAddress - 34, deletedAddress);
		rocketEndAddress -= sizeof(Rocket) - 6;
		rocketCount--;
	}
	fclose(file_m);
}

void DataBase::update_m(int index, char newModelName[30], int newStagesNumber)
{
	int offset = getAddress(index);
	if (offset == -1) {
		cout << "There is no rocket model at index " << index << endl;
		return;
	}
	FILE* file_m = fopen(filename_m, "rb+");
	fseek(file_m, offset + 4, SEEK_SET);
	fwrite(newModelName, 30, 1, file_m);
	fwrite(&newStagesNumber, sizeof(int), 1, file_m);
	fclose(file_m);
}

void DataBase::update_s(int index_s, int index_m, char newMissionName[30])
{
	int offset_m = getAddress(index_m);
	if (offset_m == -1) {
		cout << "There is no rocket model at index " << index_m << endl;
		return;
	}
	FILE* file_m = fopen(filename_m, "rb+");
	fseek(file_m, offset_m + 38, SEEK_SET);
	int firstRocketAddress;
	fread(&firstRocketAddress, sizeof(int), 1, file_m);
	fclose(file_m);
	if (firstRocketAddress == -1) {
		cout << "There are no rockets of this model" << endl;
		return;
	}
	else {
		FILE* file_s = fopen(filename_s, "rb+");
		fseek(file_s, firstRocketAddress, SEEK_SET);
		if (index_s == 1)
		{
			fwrite(newMissionName, 30, 1, file_s);
		}
		else {
			fseek(file_s, 30, SEEK_CUR);
			int nextRocketAddress;
			for (int i = 1; i < index_s; i++) {
				fread(&nextRocketAddress, sizeof(int), 1, file_s);
				fseek(file_s, nextRocketAddress + 30, SEEK_SET);
			}
			if (nextRocketAddress < 0) {
				cout << "There is no rocket with index " << index_s <<
					" for a rocket model with index " << index_m << endl;
				return;
			}
			fseek(file_s, -30, SEEK_CUR);
			fwrite(newMissionName, 30, 1, file_s);
		}
		fclose(file_s);
	}
}

void DataBase::insert_m(RocketModel* rocketModel)
{
	for (int i = 0; i < rocketModelCount; i++) {
		if (indexTable[i].index == rocketModel->index) {
			cout << "This key is allready used" << endl;
			return;
		}
	}
	FILE* file = fopen(filename_m, "rb+");
	loadIndexTable();
	indexTable[rocketModelCount].index = rocketModel->index;
	indexTable[rocketModelCount].address = rocketModelCount * (sizeof(RocketModel) - 2);
	fseek(file, rocketModelEndAddress, SEEK_SET);
	rocketModelEndAddress += sizeof(RocketModel) - 2;

	fwrite(&rocketModel->index, sizeof(int), 1, file);
	fwrite(&rocketModel->modelName, sizeof(rocketModel->modelName), 1, file);
	fwrite(&rocketModel->stagesNumber, sizeof(int), 1, file);
	fwrite(&rocketModel->firstRocketAddress, sizeof(int), 1, file);

	sortTable();
	rewriteIndexTable();
	rocketModelCount++;
	fclose(file);
}

void DataBase::insert_s(Rocket* rocket)
{
	FILE* file_s = fopen(filename_s, "rb+");
	fseek(file_s, rocketEndAddress, SEEK_SET);
	rocketEndAddress += (sizeof(Rocket) - 6);
	fwrite(&rocket->missionName, sizeof(rocket->missionName), 1, file_s);
	fwrite(&rocket->nextRocketAddress, sizeof(int), 1, file_s);

	//38 is the size of fields before firstRocketAddress
	int offset = getAddress(rocket->rocketModelIndex) + 38;
	FILE* file_m = fopen(filename_m, "rb+");
	fseek(file_m, offset, SEEK_SET);
	int firstRocketAddress;
	fread(&firstRocketAddress, sizeof(int), 1, file_m);
	int address = rocketCount * (sizeof(Rocket) - 6);
	if (firstRocketAddress == -1) {
		fseek(file_m, -4, SEEK_CUR);
		fwrite(&address, sizeof(int), 1, file_m);
	}
	else {
		int nextRocketAddress = firstRocketAddress;
		while (nextRocketAddress != -1) {
			fseek(file_s, nextRocketAddress + 30, SEEK_SET);
			fread(&nextRocketAddress, sizeof(int), 1, file_s);
		}
		fseek(file_s, -4, SEEK_CUR);
		fwrite(&address, sizeof(int), 1, file_s);
	}

	rocketCount++;
	fclose(file_s);
	fclose(file_m);
}
