//
//  map2.h
//  Map-WBT
//
//  Jean Goulet
//  Copyleft 2016 UdeS
//

#ifndef map2_h
#define map2_h

///////////////////////////////////////////////////////////////////////////
// lower_bound

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::lower_bound(const Tclef& c)const{
    noeud *n = RACINE();
    noeud *dernPlusGrandEgal = APRES;

    while(n != nullptr){
        if(c < n->CONTENU->first){
            n = n->GAUCHE;
        }else{
            dernPlusGrandEgal = n;
            n = n->DROITE;
        }
    }

    //Si rien n'a été trouvé, on retourne APRES.
    if(dernPlusGrandEgal->CONTENU->first < c){
        dernPlusGrandEgal = APRES;
        std::cout << "Aucun élément trouvé!" << std::endl;
    }

    return iterator(dernPlusGrandEgal);
}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class iterator
// ce sont des fonctions statiques, qui n'ont pas de paramètre imlicite
// STUBS qui prennent toujours un temps O(log n)
// a remplacer par des fonctions O(1) amorti

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::avancer(noeud*& p){
    //AVANCER le pointeur p vers le prochain noeud en inordre
    //cette fonction fait automatiquement exception
    //si on avance au-dela de la fin
    assert(p->DROITE!=p);
    const Tclef& a_suivre=p->CONTENU->first;
    //trouver la cellule suivant=APRES en remontant
    for(p=p->PARENT;p->POIDS!=0;p=p->PARENT);
    noeud *q=p->GAUCHE; //la racine
    while(q!=nullptr)
        if(a_suivre < q->CONTENU->first){
            p=q;
            q=q->GAUCHE;
        }
        else
            q=q->DROITE;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::reculer(noeud*& p){
    //RECULER le pointeur p vers le noeud precedent en inordre
    //si on est a la fin, descendre a droite
    if(p->POIDS==0){
        for(p=p->GAUCHE;p->DROITE!=nullptr;p=p->DROITE);
        return;
    }
    //trouver la cellule suivant=APRES en remontant
    const Tclef& a_preceder=p->CONTENU->first;
    for(;p->POIDS!=0;p=p->PARENT);
    noeud *q=p->GAUCHE; //la racine
    while(q!=nullptr)
        if(q->CONTENU->first < a_preceder){
            p=q;
            q=q->DROITE;
        }
        else
            q=q->GAUCHE;
    assert(p->DROITE!=p);
    //cette fonction plante
    //si on recule du debut
}


///////////////////////////////////////////////////////////////////////////
// equilibre


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_droite(noeud*& p){
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){

    if(p->GAUCHE != nullptr){
        if(p->GAUCHE->POIDS * 3 < p->DROITE->POIDS){
            if(p->DROITE->GAUCHE != nullptr
              && p->DROITE->DROITE != nullptr
              && !(p->DROITE->GAUCHE->POIDS < p->DROITE->DROITE->POIDS * 2)){
              rotation_gauche_droite(p->DROITE);
            }

            rotation_droite_gauche(p);
        }
    }else if(p->GAUCHE == nullptr && 3 < p->DROITE->POIDS){
      rotation_droite_gauche(p);
    }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){
    /*Vérifier les cas limites pour le calcul de poid (si enfants existent pas)*/

    noeud *hook = p->DROITE;

    p = hook->DROITE;
    hook->DROITE = p->GAUCHE;
    p->GAUCHE = hook;

    hook->POIDS = hook->GAUCHE->POIDS + hook->DROITE->POIDS + 1;
    p->POIDS = p->GAUCHE->POIDS + p->DROITE->POIDS + 1;
}



#endif /* map2_h */
