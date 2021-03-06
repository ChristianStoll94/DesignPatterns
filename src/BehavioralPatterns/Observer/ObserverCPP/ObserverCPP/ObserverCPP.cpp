#include "stdafx.h"

using namespace std;

class Object;

//Интерфейс обсервера
class IObserver
{
public:
	virtual void HandleEvent(const Object&) = 0;
};

//Объект над котрым будет вестись наблюдение обсерверами
class Object
{
	string data;
	list<IObserver*> observers;

public:
	void AddObserver(IObserver *ref) { observers.push_back(ref); }
	void RemoveObserver(IObserver *ref) { observers.remove(ref); }

	const string& GetData() const { return data; }
	void SetData(string d) 
	{
		data = d;
		Notify();
	}

private:
	void Notify()
	{
		for (auto i : observers)
			i->HandleEvent(*this);
	}
};

//Обсервер котрый выводит новые данные
//при изменении обьекта
class ReflectorObserver : public virtual IObserver
{
public:
	virtual void HandleEvent(const Object& ref) override { cout << "Reflector: '" << ref.GetData() << "'\n"; }
};

//Обсервер кторый информируе про изменения длины строки
class LenghtObserver : public virtual IObserver
{
public:
	virtual void HandleEvent(const Object& ref) override { cout << "Lenght: '" << ref.GetData().length() << "'\n"; }
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Memento"));

	Object obj;

	ReflectorObserver ro;
	LenghtObserver lo;

	obj.AddObserver(&ro);
	obj.AddObserver(&lo);

	obj.SetData("Hello World!");
	obj.SetData("Hi, motherland!");

	obj.RemoveObserver(&lo);

	obj.SetData("Best ever!");

	system("pause");
	return 0;
}

