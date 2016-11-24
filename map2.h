//
//  map2.h
//  Map-WBT
//
//  Jean Goulet
//  Copyleft 2016 UdeS
//

#ifndef map2_h
#define map2_h

#define RATIO 3  // 3:1

///////////////////////////////////////////////////////////////////////////
// lower_bound

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::lower_bound(const Tclef& c)const{
    noeud* a=RACINE();
    for(;a->POIDS!=1;){
      if(c < a->CONTENU->first)
        a=a->GAUCHE;
      else if(a->CONTENU->first < c)
        a=a->DROITE;
      else
        return iterator(a);
    }
    if(a->CONTENU->first < c)
      iterator::avancer(a);
    return iterator(a);

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
    return ;
  }
  while(p->PARENT->DROITE==p && p->PARENT->POIDS!=0) p=p->PARENT;
  p=p->PARENT;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::reculer(noeud*& p){
  if(p->GAUCHE!=nullptr){

    p=p->GAUCHE;
    while(p->DROITE!=nullptr) p=p->DROITE;
    return ;
  }
  while(p->PARENT->GAUCHE==p && p->PARENT->POIDS!=0) p=p->PARENT;
  p=p->PARENT;
}



///////////////////////////////////////////////////////////////////////////
// equilibre


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_droite(noeud*& p){
  size_t poidsDroite=(p->DROITE==nullptr)?0:p->DROITE->POIDS;
  size_t poidsGauche=(p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS;
  if(p->POIDS>3 && poidsGauche > poidsDroite*RATIO)
    rotation_gauche_droite(p);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){
  size_t poidsDroite=(p->DROITE==nullptr)?0:p->DROITE->POIDS;
  size_t poidsGauche=(p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS;
  if(p->POIDS>3 && poidsDroite > poidsGauche*RATIO)
    rotation_droite_gauche(p);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud* p){
  noeud* gauche=p->GAUCHE;
  p->GAUCHE=gauche->DROITE;
  if(gauche->DROITE!=nullptr)gauche->DROITE->PARENT=p;
  gauche->DROITE=p;
  if(p->PARENT->GAUCHE == p)
    p->PARENT->GAUCHE=gauche;
  else
    p->PARENT->DROITE=gauche;
  gauche->PARENT=p->PARENT;
  p->PARENT=gauche;


  gauche->POIDS=p->POIDS;
  p->POIDS=
    ((p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS)
    + ((p->DROITE==nullptr)?0:p->DROITE->POIDS) +1;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud* p){
  noeud* droite=p->DROITE;
  p->DROITE=droite->GAUCHE;
  if(droite->GAUCHE!=nullptr)droite->GAUCHE->PARENT=p;
  droite->GAUCHE=p;
  if(p->PARENT->GAUCHE == p)
    p->PARENT->GAUCHE=droite;
  else
    p->PARENT->DROITE=droite;
  droite->PARENT=p->PARENT;
  p->PARENT=droite;


  droite->POIDS=p->POIDS;
  p->POIDS=
    ((p->GAUCHE==nullptr)?0:p->GAUCHE->POIDS)
    + ((p->DROITE==nullptr)?0:p->DROITE->POIDS) +1;
}



#endif /* map2_h */
