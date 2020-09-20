#include <iostream>
#include "DataBase.h"
using namespace std;

int main()
{
	DataBase dataBase;
	dataBase.Init();
	//1
	char model1Name[30] = "Atlas V";
	char model2Name[30] = "Saturn V";
	char model3Name[30] = "Falcon 9";
	char model4Name[30] = "Ariane 6";
	char model5Name[30] = "Falcon Heavy";
	RocketModel rocketModel1(model1Name, 2, 1);
	RocketModel rocketModel2(model2Name, 3, 9);
	RocketModel rocketModel3(model3Name, 2, 10);
	RocketModel rocketModel4(model4Name, 2, 2);
	RocketModel rocketModel5(model5Name, 3, 3);
	dataBase.insert_m(&rocketModel1);
	dataBase.insert_m(&rocketModel2);
	dataBase.insert_m(&rocketModel3);
	dataBase.insert_m(&rocketModel4);
	dataBase.insert_m(&rocketModel5);
	//2
	char mission1Name[30] = "Mars 2020";
	char mission2Name[30] = "Apollo 11";
	char mission3Name[30] = "Apollo 12";
	char mission4Name[30] = "Crew Demo-2";
	char mission5Name[30] = "Saocom 1b";
	char mission6Name[30] = "Starlink 12 v1.0";
	Rocket rocket1(mission1Name, 1);
	Rocket rocket2(mission2Name, 9);
	Rocket rocket3(mission3Name, 9);
	Rocket rocket4(mission4Name, 10);
	Rocket rocket5(mission5Name, 10);
	Rocket rocket6(mission6Name, 10);
	dataBase.insert_s(&rocket1);
	dataBase.insert_s(&rocket2);
	dataBase.insert_s(&rocket3);
	dataBase.insert_s(&rocket4);
	dataBase.insert_s(&rocket5);
	dataBase.insert_s(&rocket6);
	//3	
	cout << "Step 3:" << endl;
	dataBase.ut_m();
	dataBase.ut_s();
	cout << endl;
	//4
	dataBase.delete_m(9);
	//5
	dataBase.delete_s(2, 10);
	//6
	cout << "Step 6:" << endl;
	dataBase.ut_m();
	dataBase.ut_s();
	cout << endl;
	//7
	char model6Name[30] = "Starship";
	RocketModel rocketModel6(model6Name, 2, 4);
	char mission7Name[30] = "20 Km Hop";
	Rocket rocket7(mission7Name, 4);
	dataBase.insert_m(&rocketModel6);
	dataBase.insert_s(&rocket7);
	//8
	cout << "Step 8:" << endl;
	dataBase.ut_m();
	dataBase.ut_s();
	cout << endl;
	//9
	char model7Name[30] = "New Glenn";
	dataBase.update_m(4, model7Name, 3);
	char mission8Name[30] = "Payload to ISS";
	dataBase.update_s(1, 4, mission8Name);
	//10
	cout << "Step 10:" << endl;
	dataBase.ut_m();
	dataBase.ut_s();
	cout << endl;
	//Extra:
	cout << "Extra:" << endl;
	cout << "Get rocket model with index 9 (get_m(9)):" << endl;
	dataBase.get_m(9);
	cout << "Get rocket with index 3, rocket model is 10 (get_s(3,10)):" << endl;
	dataBase.get_s(3, 10);
	cout << "Get rocket with index 2, rocket model is 10 (get_s(2,10)):" << endl;
	dataBase.get_s(2, 10);
}

