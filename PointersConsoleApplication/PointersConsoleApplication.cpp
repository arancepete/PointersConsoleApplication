// PointersConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

/**
	Pointers ****
*/
int main()
{

	int SomeArray[10] = { 3, 6, 9, 12, 15, 18, 21, 24, 27, 30 };

	int* pLocation0 = SomeArray;

	for (int i = 0; i < 10; i++)
	{
		cout << pLocation0 + i << " = " << *(pLocation0 + i) << endl;
	}

	//std::cout << "Hello World!\n";

   //////////////////////////////////////////////////////////////////////// Polymorphism ///////////////////////////////////////////////////////////////////////



	struct sSomeBaseObject
	{
		virtual const char* IdentifyYourself()
		{
			return "BaseObject";
		}
	};

	struct sSomeSubObjectA : public sSomeBaseObject
	{
		const char* IdentifyYourself()
		{
			return "SubObject A";
		}
	};

	struct sSomeSubObjectB : public sSomeBaseObject
	{
		const char* IdentifyYourself()
		{
			return "SubObject B";
		}
	};

	//////////////////////////////////////////////////////////////////////////// Stack


	sSomeBaseObject ob_base;
	sSomeSubObjectA ob_A;
	sSomeSubObjectB ob_B;


	cout << ob_base.IdentifyYourself() << endl;
	cout << ob_A.IdentifyYourself() << endl;
	cout << ob_B.IdentifyYourself() << endl;



	sSomeBaseObject objects[10];


	for (int i = 0; i < 10; i++)
	{
		cout << objects[i].IdentifyYourself() << endl;
	}


	//////////////////////////////////////////////////////////////////////////// Heap Array

	sSomeBaseObject** pSomeArray = new sSomeBaseObject * [5]; // To init to zero "new sSomeBaseObject * [5]{0}" or "new sSomeBaseObject * [5]()"

	pSomeArray[0] = new sSomeSubObjectA();
	pSomeArray[1] = new sSomeSubObjectB();
	pSomeArray[2] = new sSomeSubObjectB();
	pSomeArray[3] = new sSomeBaseObject();
	pSomeArray[4] = new sSomeSubObjectA();

	for (int i = 0; i < 5; i++)
	{
		cout << pSomeArray[i]->IdentifyYourself() << endl;
	}


	for (int i = 0; i < 5; i++) delete pSomeArray[i]; // clean up

	delete[] pSomeArray;

	////////////////////////////////////////////////////////////////////////////// Vector

	vector< sSomeBaseObject*> vSomeVector;

	vSomeVector.push_back(new sSomeSubObjectA());
	vSomeVector.push_back(new sSomeSubObjectB());
	vSomeVector.push_back(new sSomeSubObjectB());
	vSomeVector.push_back(new sSomeBaseObject());
	vSomeVector.push_back(new sSomeSubObjectA());

	for (auto& a : vSomeVector)
		cout << a->IdentifyYourself() << endl;

	for (auto& a : vSomeVector)
		delete a;


	vSomeVector.clear();

	//////////////////// BAD BAD BAD ////////// Vectors shouldn't be treated like Array's https://herbsutter.com/2008/04/07/cringe-not-vectors-are-guaranteed-to-be-contiguous/

	vector< sSomeBaseObject> vSomeVector2;

	vSomeVector2.push_back(sSomeBaseObject());
	vSomeVector2.push_back(sSomeBaseObject());
	vSomeVector2.push_back(sSomeBaseObject());
	vSomeVector2.push_back(sSomeBaseObject());
	vSomeVector2.push_back(sSomeBaseObject());
	vSomeVector2.push_back(sSomeBaseObject());

	sSomeBaseObject* pPointerToVectorElement = &vSomeVector2[3]; // <<-- Absolute NO NO!!!

	//////////////////////////////////////////// Smart Pointers

	struct sSomeObject
	{
		int x = 0xA3A2A1A0;
		int y = 0xB3B2B1B0;

		sSomeObject()
		{
			x = 0xC3C2C1C0;
			y = 0xD3D2D1D0;
		}

	};


	// Smart Pointers - Shared - Multiple accessors to pointer. 
	//
	// They encourage the developer to be lazy and not think about memory management 
	// and the journey that data takes through the application.

	{// Scope 1
		shared_ptr<sSomeObject> spSomeObject1 = make_shared< sSomeObject>();

		{ // Scope 2


			shared_ptr<sSomeObject> spSomeObject2 = spSomeObject1;


		} // End Scope 2

	} // End Scope1

	{// Scope 1
		unique_ptr<sSomeObject> upSomeObject1 = make_unique< sSomeObject>();

		{ // Scope 2


			unique_ptr<sSomeObject> upSomeObject2 = std::move(upSomeObject1); // <<--ownership must be transfered to the second pointer.


		} // End Scope 2

	} // End Scope1

	system("pause");

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
