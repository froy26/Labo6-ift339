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
    //STUB O(n log n) a remplacer par une fonction O(log n)
    //iterator i = begin();
    noeud *n = RACINE();

    //while(n->GAUCHE != nullptr || n->DROITE != nullptr){
    while(n != nullptr){
        if(!(c < n->CONTENU->first))break;

        if(c < n->CONTENU->first){
            n = n->GAUCHE;
        }else{
            n = n->DROITE;
        }
    }

    //Si rien n'a été trouvé, on retourne APRES.
    if(n == nullptr){
        n = APRES;
        std::cout << "Aucun élément trouvé!!!" << std::endl;
    }

    /*for(i=begin();i!=end();++i)
        if(!(i->first < c))break;*/



    return iterator(n);
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
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){
}



#endif /* map2_h */
