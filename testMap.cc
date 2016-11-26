#include "map.h"

using namespace std;

int main(void){

  map<string,int> s;
  s["ds1"]=42;
  s["ds2"]=42;
  s["ds5"]=42;
  //s.afficher();
  s["ds8"]=42;
  //s.afficher();
  s["ds4"]=42;
  //s.afficher();
  s["ds4"]=42;
  //s.afficher();
  s["test"]=42;
  //s.afficher();
  s["dsa"]=42;
  //s.afficher();
  s["ds'"]=42;
  //s.afficher();
  s["ds("]=42;
  //s.afficher();
  s["ds-"]=42;//ici ---------
  //s.afficher();
//s["ds_"]=42;
////s.afficher();
//s["ds)"]=42;
////s.afficher();
//s["ds°"]=42;
//s.afficher();
  for(auto it=--s.end();it!=s.begin();--it)
    cout<<(*it).first<<endl;
  cout<<"lower bound"<<s.lower_bound("ds5")->first<<endl;
  
  return 0;
}
