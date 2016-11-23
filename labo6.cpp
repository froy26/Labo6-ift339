
#include "map.h"
//#include <set>
//#include <iostream>
//using namespace std;

int main()
{
	map<char,int> m = map<char, int>();
    map<char,int>::iterator i = m.begin();

	m['q']=10;
	m['w']=15;
	m['e']=17;
	m['r']=20;
	m['t']=30;
	m['y']=35;
	m['u']=40;
	m['i']=42;
	m['o']=45;
	m['p']=50;

	m.afficher();

    i = m.lower_bound('u');

    std::cout << i->first << std::endl;


  return 0;
}
