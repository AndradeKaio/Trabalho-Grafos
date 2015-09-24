#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <err.h>


#define MAX 10

using namespace std;

class A 
{

	public:
		A()
		{

		}

	private:
		int a;
		B b;
		

	public:
		
		void mostraA()
		{
			cout << "A";
		}

};

class B
{
	public:
		int B;
		A b;
		A a [2];
	public:
		void mostraB()
		{
			cout << "A", a;
		}
		void teste()
		{
			A a;
			a.mostraA();
		}
};

int main()
{

	B b;
	A c;
	b.a[0] =a; 
}