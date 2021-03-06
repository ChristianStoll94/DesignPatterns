#include "stdafx.h"

using namespace std;

//Интерфейс
class IWallCreator
{
public:
	virtual void BuildWall() = 0;
	virtual void BuildWallWithDoor() = 0;
	virtual void BuildWallWithWindow() = 0;
};

//Конкретная реализаия интерфейса
class BrickWallCreator :public IWallCreator
{
public:
	virtual void BuildWall() { cout << "Brick & mortar wall.\n"; }
	virtual void BuildWallWithDoor() { cout << "Brick & mortar wall with door hole.\n"; }
	virtual void BuildWallWithWindow() { cout << "Brick & mortar wall with window hole.\n"; }
};

//Конкретная реализаия интерфейса
class FoamblockWallCreator :public IWallCreator
{
public:
	virtual void BuildWall() { cout << "Foam wall.\n"; }
	virtual void BuildWallWithDoor() { cout << "Foam wall.\n"; }
	virtual void BuildWallWithWindow() { cout << "Foam wall.\n"; }
};

//Интерфейс
class IBuildCompany
{
protected:
	//Мост
	IWallCreator * creator;

public:
	void SetCretor(IWallCreator* c)
	{
		creator = c;
	}
	virtual void BuildFoundation() = 0;
	virtual void BuildRoom() = 0;
	virtual void BuildRoof() = 0;
};

//Конкретная реализация рпедыдущего интерфейса
class TownBuildCompany :public IBuildCompany
{
public:
	virtual void BuildFoundation() { cout << "Concrete solid foundation is finished.\n"; }
	virtual void BuildRoom()
	{
		creator->BuildWallWithWindow();
		creator->BuildWall();
		creator->BuildWall();
		creator->BuildWallWithDoor();
		cout << "Room is finished.\n";
	}
	virtual void BuildRoof() { cout << "Flat roof is finished.\n"; }
};

//Конкретная реализация рпедыдущего интерфейса
class CoountryBuildCompany :public IBuildCompany
{
public:
	virtual void BuildFoundation() { cout << "Country foundation is finished.\n"; }
	virtual void BuildRoom()
	{
		creator->BuildWallWithDoor();
		creator->BuildWallWithWindow();
		creator->BuildWallWithWindow();
		creator->BuildWall();
		cout << "Room is finished.\n";
	}
	virtual void BuildRoof() { cout << "Roof is finished.\n"; }
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Bridge"));

	//Материалы
	BrickWallCreator * brick = new BrickWallCreator;
	FoamblockWallCreator * block = new FoamblockWallCreator;

	TownBuildCompany * BigCompany = new TownBuildCompany;
	CoountryBuildCompany * SmallCompany = new CoountryBuildCompany;

	cout << "Big company start building:" << endl;
	BigCompany->BuildFoundation();
	BigCompany->SetCretor(brick);
	BigCompany->BuildRoom();
	BigCompany->BuildRoom();
	cout << "Material change..." << endl;
	BigCompany->SetCretor(block);
	BigCompany->BuildRoof();

	cout << "Small company start building:" << endl;
	SmallCompany->BuildFoundation();
	SmallCompany->SetCretor(block);
	SmallCompany->BuildRoom();
	SmallCompany->BuildRoom();
	SmallCompany->BuildRoof();

	system("pause");
	return 0;
}

