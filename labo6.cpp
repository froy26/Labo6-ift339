
#include "map.h"
//#include <set>
//#include <iostream>
//using namespace std;

int main()
{
	map<char,int> m = map<char, int>();

	m['a']=10;
	m['b']=15;
	m['c']=17;
	m['d']=20;
	m['e']=30;
	m['f']=35;
	m['g']=40;
	m['h']=42;
	m['i']=45;
	m['j']=50;

	m.afficher();

  return 0;
}
