//
//  map.h
//  Map-WBT
//
//  Jean Goulet
//  Copyleft 2016
//
//  modification de la declaration de afficher
//  modification du destructeur de map
//

#ifndef map_h
#define map_h


#include <vector>
#include <string>
#include <cassert>
#include <cmath>

#include <iostream>
using namespace std;

template <typename Tclef, typename Tvaleur>
class map{
public:
    class iterator;
    friend class iterator;
    typedef std::pair<const Tclef,Tvaleur> PAIR;
private:
    struct noeud{
        PAIR* CONTENU;
        noeud *PARENT,*GAUCHE,*DROITE;
        size_t POIDS;
        noeud(const Tclef& c,noeud* PAR,noeud*GAU=nullptr,noeud*DRO=nullptr)
            :PARENT(PAR),GAUCHE(GAU),DROITE(DRO),POIDS(1){
            CONTENU=new PAIR(c,Tvaleur());}
        noeud():CONTENU(nullptr),PARENT(nullptr),GAUCHE(nullptr),DROITE(nullptr),POIDS(0){}
        ~noeud(){delete CONTENU;CONTENU=nullptr;PARENT=GAUCHE=DROITE=nullptr;}
    };
    size_t SIZE;
    noeud *APRES;
    //fonctions privees
    noeud*& RACINE()const{return APRES->GAUCHE;}
    void vider(noeud*&);
    void copier(noeud*,noeud*&,noeud*);
    
    bool insert(const Tclef&,noeud*&,iterator&);
    bool ajoute_gauche(const Tclef&,noeud*&,iterator&);
    bool ajoute_droite(const Tclef&,noeud*&,iterator&);
    
    bool erase(const Tclef&,noeud*&,noeud*&);
    bool enleve_gauche(const Tclef&,noeud*&,noeud*&);
    bool enleve_droite(const Tclef&,noeud*&,noeud*&);
    bool eliminer(noeud*&,noeud*&);
    
    void transferer_vers_la_droite(noeud*&);
    void transferer_vers_la_gauche(noeud*&);
    void rotation_gauche_droite(noeud*&);
    void rotation_droite_gauche(noeud*&);
    
    void afficher(noeud*,int,std::vector<std::string>&,double&,int&)const;
    void afficher_barres(std::vector<std::string>&,int)const;
public:
    map();
    ~map();
    map(const map&);
    map& operator=(const map&);
    void swap(map&);
    
    size_t size()const{return SIZE;}
    bool empty()const{return SIZE==0;}
    void clear();
    
    iterator find(const Tclef&)const;
    iterator lower_bound(const Tclef&)const;
    Tvaleur& operator[](const Tclef&);
    std::pair<iterator,bool> insert(PAIR&);
    size_t erase(const Tclef&);
    iterator erase(iterator);
    
    //fonction d'iteration
    iterator begin()const;
    iterator end()const;
    
    //fonction de mise au point
    bool verifier_poids(noeud* =nullptr,bool=true)const;
    void afficher()const;
};

template <typename Tclef, typename Tvaleur>
class map<Tclef,Tvaleur>::iterator{
private:
    noeud* POINTEUR;
    static void avancer(noeud*&);
    static void reculer(noeud*&);
    friend class map<Tclef,Tvaleur>;
public:
    iterator(noeud*p=nullptr):POINTEUR(p){}
    iterator(const iterator&)=default;
    iterator& operator=(const iterator&)=default;
    PAIR& operator*()const{return *(POINTEUR->CONTENU);}
    PAIR* operator->()const{return POINTEUR->CONTENU;}
    iterator& operator++(){avancer(POINTEUR);return *this;}                         //++i
    iterator operator++(int){iterator copie(*this);avancer(POINTEUR);return copie;} //i++
    iterator& operator--(){reculer(POINTEUR);return *this;}                         //--i
    iterator operator--(int){iterator copie(*this);reculer(POINTEUR);return copie;} //i--
    bool operator==(const iterator& dr)const{return POINTEUR==dr.POINTEUR;}
    bool operator!=(const iterator& dr)const{return POINTEUR!=dr.POINTEUR;}
};

///////////////////////////////////////////////////////////////////////////
// fonctions d'iteration

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::begin()const{
    noeud* p=APRES;
    while(p->GAUCHE!=nullptr)p=p->GAUCHE;
    return iterator(p);
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::end()const{
    return iterator(APRES);
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::vider(noeud*& p){
    if(p==nullptr)return;
    vider(p->GAUCHE);
    vider(p->DROITE);
    delete p;
    p=nullptr;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::copier(noeud* source,noeud*& dest,noeud* parent){
    if(source==nullptr)return;
    dest=new noeud(*source);
    dest->PARENT=parent;
    dest->POIDS=source->POIDS;
    copier(source->DROITE,dest->DROITE,dest);
    copier(source->GAUCHE,dest->GAUCHE,dest);
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'insertion

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::insert(const Tclef& c,noeud*& p,iterator& r){
    if(c<p->CONTENU->first){
        if(ajoute_gauche(c,p,r)){
            ++(p->POIDS);
            transferer_vers_la_droite(p);
            return true;
        }
    }
    else if(p->CONTENU->first<c){
        if(ajoute_droite(c,p,r)){
            ++(p->POIDS);
            transferer_vers_la_gauche(p);
            return true;
        }
    }
    else r=iterator(p);
    return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::ajoute_gauche(const Tclef& c,noeud*& p,iterator& r){
    if(p->GAUCHE==nullptr){  //nouvelle feuille
        p->GAUCHE=new noeud(c,p);
        ++SIZE;
        r=iterator(p->GAUCHE);
        return true;
    }
    else                    //ajout general a gauche
        return insert(c,p->GAUCHE,r);
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::ajoute_droite(const Tclef& c,noeud*& p,iterator& r){
    if(p->DROITE==nullptr){  //nouvelle feuille
        p->DROITE=new noeud(c,p);
        ++SIZE;
        r=iterator(p->DROITE);
        return true;
    }
    else  //ajout general a droite
        return insert(c,p->DROITE,r);
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'elimination

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::erase(const Tclef& c,noeud*& p,noeud*& aRemplacer){
    if(c<p->CONTENU->first)
        return enleve_gauche(c,p,aRemplacer);
    else if(p->CONTENU->first<c)
        return enleve_droite(c,p,aRemplacer);
    else{
        aRemplacer=p;
        return enleve_gauche(c,p,aRemplacer);
    }
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::enleve_gauche(const Tclef& c,noeud*& p,noeud*& aRemplacer){
    if(p->GAUCHE==nullptr)
        return eliminer(p,aRemplacer);
    else if(erase(c,p->GAUCHE,aRemplacer)){
        --(p->POIDS);
        transferer_vers_la_gauche(p);
        return true;
    }
    else
        return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::enleve_droite(const Tclef& c,noeud*& p,noeud*& aRemplacer){
    if(p->DROITE==nullptr)
        return eliminer(p,aRemplacer);
    else if(erase(c,p->DROITE,aRemplacer)){
        --(p->POIDS);
        transferer_vers_la_droite(p);
        return true;
    }
    else
        return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::eliminer(noeud*& p,noeud*& aRemplacer){
    if(aRemplacer!=nullptr){
        delete aRemplacer->CONTENU;
        aRemplacer->CONTENU=p->CONTENU;
        p->CONTENU=nullptr;
        aRemplacer=p;
        if(p->GAUCHE==nullptr)p=p->DROITE;else p=p->GAUCHE;
        if(p!=nullptr)p->PARENT=aRemplacer->PARENT;
        --SIZE;
        return true;
    }
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions publiques

template <typename Tclef, typename Tvaleur>
map<Tclef,Tvaleur>::map(){
    APRES=new noeud;
    SIZE=0;
}

template <typename Tclef, typename Tvaleur>
map<Tclef,Tvaleur>::~map(){
    clear();
    delete APRES;
    APRES=nullptr;
}

template <typename Tclef, typename Tvaleur>
map<Tclef,Tvaleur>::map(const map& source):map(){
    copier(source.RACINE(),RACINE(),nullptr);
    SIZE=source.size();
}

template <typename Tclef, typename Tvaleur>
map<Tclef,Tvaleur>& map<Tclef,Tvaleur>::operator=(const map& source){
    if(this==&source)return *this;
    map<Tclef,Tvaleur> copie(source);
    this->swap(copie);
    return *this;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::swap(map& source){
    std::swap(SIZE,source.SIZE);
    std::swap(APRES,source.APRES);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::clear(){
    vider(RACINE());
    SIZE=0;
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::find(const Tclef& c)const{
    iterator retour=lower_bound(c);
    if(retour==end() || c<retour->first)return end();
    return retour;
}

template <typename Tclef, typename Tvaleur>
Tvaleur& map<Tclef,Tvaleur>::operator[](const Tclef& c){
    PAIR P=std::make_pair(c,Tvaleur());
    auto r=insert(P);
    auto i=r.first;
    PAIR* pa=i.POINTEUR->CONTENU;
    return pa->second;
}

template <typename Tclef, typename Tvaleur>
std::pair<typename map<Tclef,Tvaleur>::iterator,bool> map<Tclef,Tvaleur>::insert(PAIR& p){
    const Tclef& c(p.first);
    iterator retour;
    if(SIZE==0){  //arbre vide
        RACINE()=new noeud(c,APRES);
        SIZE=1;
        return std::make_pair(begin(),true);
    }
    bool valeur=insert(c,RACINE(),retour);
    retour->second=p.second;
    return std::make_pair(retour,valeur);
}

template <typename Tclef, typename Tvaleur>
size_t map<Tclef,Tvaleur>::erase(const Tclef& c){
    if(SIZE!=0){
        noeud* aRemplacer=nullptr;
        if(erase(c,RACINE(),aRemplacer))return 1;
    }
    return 0;
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::erase(iterator i){
    assert(i!=end());
    Tclef c=i->first;
    erase(c);
    return lower_bound(c);
}

///////////////////////////////////////////////////////////////////////////
// fonctions de mise au point
template <typename Tclef, typename Tvaleur>
bool map<Tclef,Tvaleur>::verifier_poids(noeud* p,bool retour)const{
    using namespace std;
    if(!retour)return false;
    if(p==nullptr){
        if(RACINE()==nullptr)return true;
        else p=APRES->GAUCHE;
    }
    size_t po=p->POIDS;
    if(po<=3)return true;
    size_t pg=0;if(p->GAUCHE!=nullptr)pg=p->GAUCHE->POIDS;
    size_t pd=0;if(p->DROITE!=nullptr)pd=p->DROITE->POIDS;
    if(pg>3*pd || pd>3*pg){
        cerr<<"le noeud "<<p->CONTENU->first;
        cerr<<" est de poids "<<p->POIDS;
        cerr<<"="<<pg<<"+"<<pd<<"+1"<<endl;
        retour=false;
    }
    if(p->GAUCHE!=nullptr)retour=verifier_poids(p->GAUCHE,retour);
    if(p->DROITE!=nullptr)retour=verifier_poids(p->DROITE,retour);
    return retour;
}


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::afficher()const{
    using namespace std;
    double total=0.;
    int max=0;
    cout<<"-------------------------------"<<endl;
    vector<string> barres;
    barres.push_back("    ");
    afficher(RACINE(),1,barres,total,max);
    total=total/SIZE;
    cout<<SIZE<<" element";if(SIZE>1)cout<<"s";cout<<endl;
    cout<<"log("<<SIZE<<"): "<<log2(double(SIZE))<<endl;
    cout<<"hauteur moyenne: "<<total<<endl;
    cout<<"hauteur maximale: "<<max<<endl;
    cout<<"-------------------------------"<<endl;
}


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::afficher(map<Tclef,Tvaleur>::noeud* p,int niveau,std::vector<std::string>& barres,double& total,int& max)const{
    using namespace std;
    if(p==0)return;
    total+=niveau;
    if(niveau>max)max=niveau;
    if(niveau>=barres.size())barres.push_back("    ");
    
    afficher(p->DROITE,niveau+1,barres,total,max);
    
    //si on est un enfant de gauche arreter les barres a ce niveau
    if(p->PARENT!=0 && p->PARENT->GAUCHE==p)barres[niveau-1]="    ";
    
    //cout<<niveau;
    afficher_barres(barres,niveau);
    cout<<"---> [";
    cout<<p->CONTENU->first<<","<<p->CONTENU->second<<"] ("<<p->POIDS;
    //cout<<", "<<p;
    //cout<<", par="<<p->PARENT;
    //cout<<", gau="<<p->GAUCHE;;
    //cout<<", dro="<<p->DROITE;
    cout<<")"<<endl;
    
    //si on est un enfant de droite barre a mon niveau
    if(p->PARENT->DROITE==p)barres[niveau-1]="   |";
    
    //si on a un enfant a gauche mettre des barres apres
    if(p->GAUCHE!=0)barres[niveau]="   |";
    else barres[niveau]="    ";
    
    //cout<<niveau;
    afficher_barres(barres,niveau+1);
    cout<<endl;
    
    afficher(p->GAUCHE,niveau+1,barres,total,max);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::afficher_barres(std::vector<std::string>& barres,int n)const{
    for(int i=0;i<n;++i)std::cout<<barres[i];
}

#include "map2.h"



#endif /* map_h */
