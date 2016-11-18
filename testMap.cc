#include "map.h"

using namespace std;

int main(void){

  map<string,int> s;
  s["ds1"]=42;
  s["ds2"]=42;
  s["ds5"]=42;
  s["ds8"]=42;
  s["ds4"]=42;
  s["ds4"]=42;
  s["test"]=42;
  s["dsa"]=42;
  s["ds7"]=42;
  s.afficher();
  for(auto it=--s.end();it!=s.begin();--it)
    cout<<(*it).first<<endl;

  

  return 0;
}
