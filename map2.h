//
//  map2.h
//  Map-WBT
//
//  Jean Goulet
//  Copyleft 2016 UdeS
//
// Felix Roy     16 061 351
// Jules Lagarde 16 140 445
//

#ifndef map2_h
#define map2_h
#include <iostream>

#define RATIO1 3  // 3:1
#define RATIO2 2

///////////////////////////////////////////////////////////////////////////
// lower_bound

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::lower_bound(const Tclef& c)const{
  noeud* best=APRES;
  noeud* a=RACINE();
  while(a!=nullptr && a->POIDS!=1){
    if(c < a->CONTENU->first){
      best=a;
      a=a->GAUCHE;
    }else
      a=a->DROITE;
  }
  return iterator(best);

}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class iterator
// ce sont des fonctions statiques, qui n'ont pas de paramètre imlicite
// STUBS qui prennent toujours un temps O(log n)
// a remplacer par des fonctions O(1) amorti

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::avancer(noeud*& p){
  if(p->DROITE!=nullptr){
    p=p->DROITE;
    while(p->GAUCHE!=nullptr) p=p->GAUCHE;
  }else{
    while(p->PARENT->DROITE==p && p->PARENT->POIDS!=0) p=p->PARENT;
    p=p->PARENT;
  }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::reculer(noeud*& p){
  if(p->GAUCHE!=nullptr){

    p=p->GAUCHE;
    while(p->DROITE!=nullptr) p=p->DROITE;
  }else{
    while(p->PARENT->GAUCHE==p && p->PARENT->POIDS!=0) p=p->PARENT;
    p=p->PARENT;
  }
}



///////////////////////////////////////////////////////////////////////////
// equilibre


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_droite(noeud*& p){
  noeud*& gauche=p->GAUCHE;
  size_t poidsDroite=(p->DROITE==nullptr)?0:p->DROITE->POIDS;
  size_t poidsGauche=0;
  if(gauche!=nullptr){
    poidsGauche=gauche->POIDS;
    size_t poidsGDroite=(gauche->DROITE==nullptr)?0:gauche->DROITE->POIDS;
    size_t poidsGGauche=(gauche->GAUCHE==nullptr)?0:gauche->GAUCHE->POIDS;
    if(poidsGauche>RATIO2 && poidsGDroite > poidsGGauche*RATIO2)
      rotation_droite_gauche(gauche);
  }

  if(p->POIDS>RATIO1 && poidsGauche > poidsDroite*RATIO1)
    rotation_gauche_droite(p);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){
  noeud*& droite=p->DROITE;
  size_t poidsDroite=0;
  size_t poidsGauche=(p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS;
  if(droite!=nullptr){
    poidsDroite=droite->POIDS;
    size_t poidsDDroite=(droite->DROITE==nullptr)?0:droite->DROITE->POIDS;
    size_t poidsDGauche=(droite->GAUCHE==nullptr)?0:droite->GAUCHE->POIDS;

    if(poidsDroite>RATIO2 && poidsDGauche > poidsDDroite*RATIO2)
      rotation_gauche_droite(droite);
  }

  if(p->POIDS>RATIO1 && poidsDroite > poidsGauche*RATIO1)
    rotation_droite_gauche(p);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
  noeud* gauche=p->GAUCHE;
  p->GAUCHE=gauche->DROITE;
  if(gauche->DROITE!=nullptr)gauche->DROITE->PARENT=p;
  gauche->DROITE=p;
  gauche->PARENT=p->PARENT;
  p->PARENT=gauche;

  gauche->POIDS=p->POIDS;
  p->POIDS=
    ((p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS)
    + ((p->DROITE==nullptr)?0:p->DROITE->POIDS) +1;

  p=gauche;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){
  noeud* droite=p->DROITE;


  p->DROITE=droite->GAUCHE;
  if(droite->GAUCHE!=nullptr)droite->GAUCHE->PARENT=p;
  droite->GAUCHE=p;
  droite->PARENT=p->PARENT;
  p->PARENT=droite;

  droite->POIDS=p->POIDS;
  p->POIDS=
    ((p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS)
    + ((p->DROITE==nullptr)?0:p->DROITE->POIDS) +1;

  p=droite;
}



#endif /* map2_h */
