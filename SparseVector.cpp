//Definicje SparseVector.h
#include "SparseVector.h"
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <cmath>

//Pusty konstruktor
SparseVector::SparseVector() {

}

//Przeciazenie operatora przypisania
//Przypisanie wartosci z danego obiektu na rzecz obiektu ktorego zostal wywolany operator
SparseVector & SparseVector::operator=(const SparseVector &v1){
    this->svector.clear();
    for(auto& x: v1.svector){
        this->svector[x.first] = x.second;
    }
    return * this;
}

//Przeciazenie operatora dodawania
//Jesli w wektorze, na rzecz ktorego jest wywolywany operator, nie ma na danej pozycji wartosci to dodaj pare(nowy element),
//w przeciwnym wypadku dodaj wartosci
SparseVector SparseVector::operator+(const SparseVector &v1){
    SparseVector sum;
    sum=*this;

    for(auto& x: v1.svector){
        std::unordered_map<int,double>::const_iterator y = sum.svector.find(x.first);
        if(y == sum.svector.end()){
            sum.svector.insert(x);
        }else{
            sum.svector[x.first] = sum.svector[x.first] + x.second;
        }
    }
    return sum;
}

//Podobnie jak w dodawaniu (roznica to tylko "this")
SparseVector SparseVector::operator+=(const SparseVector &v1){
    for(auto& x: v1.svector){
        std::unordered_map<int,double>::const_iterator y = this->svector.find(x.first);
        if(y == this->svector.end()){
            this->svector.insert(x);
        }else{
            this->svector[x.first] = this->svector[x.first] + x.second;
        }
    }
    return *this;
}

//Przeciazenie operatora odejmowania
//Jesli w wektorze, na rzecz ktorego jest wywolywany operator, nie ma na danej pozycji wartosci to dodaj pare(nowy element) z przeciwna wartoscia,
//w przeciwnym wypadku odejmij wartosci
SparseVector SparseVector::operator-(const SparseVector &v1){
    SparseVector sum;
    sum=*this;
    for(auto& x: v1.svector){
        std::unordered_map<int, double>::const_iterator y=sum.svector.find(x.first);
        if(y == sum.svector.end()){
            sum.svector[x.first] = -x.second;
        }else{
            sum.svector[x.first] = sum.svector[x.first] - x.second;
        }
    }
    return sum;
}

//Podobnie jak w odejmowaniu (roznica to tylko "this")
SparseVector SparseVector::operator-=(const SparseVector &v1){
    for(auto& x: v1.svector){
        std::unordered_map<int,double>::const_iterator y = this->svector.find(x.first);
        if(y == this->svector.end()){
            this->svector[x.first] = -x.second;
        }else{
            this->svector[x.first] = this->svector[x.first] - x.second;
        }
    }
    return *this;
}

//Przeciazenie operatora mnozenia
SparseVector SparseVector::operator*(const SparseVector &v1){
    SparseVector product;
    product=*this;
    for(auto& x: v1.svector) {
        std::unordered_map<int, double>::const_iterator y = product.svector.find(x.first); //Iterator wskazujacy na wyszukany element
        if (y != product.svector.end()) {                                           //Jesli zostanie znaleziony w 1-szym wektorze to mnozenie
            product.svector[x.first] = product.svector[x.first] * x.second;
        }
    }
    SparseVector product2;
    product2=product;
    for(auto& x: product.svector) {
        std::unordered_map<int, double>::const_iterator y = v1.svector.find(x.first);
        if (y == v1.svector.end()) {                                                //Jesli w 1-szym sa pozycje, ktorych nie ma 2-gi
            product2.svector.erase(product2.svector.find(x.first));                 //to sa one zerowane (usuwane)
        }
    }
    return product2;
}

//Podobnie jak w mnozeniu (roznica to tylko "this")
SparseVector SparseVector::operator*=(const SparseVector &v1){
    for(auto& x: v1.svector) {
        std::unordered_map<int, double>::const_iterator y = this->svector.find(x.first); 
        if (y != this->svector.end()) {                                             
            this->svector[x.first] = this->svector[x.first] * x.second;
        }
    }
    for(auto& x: this->svector) {
        std::unordered_map<int, double>::const_iterator y = v1.svector.find(x.first);
        if (y == v1.svector.end()) {                                                
            this->svector.erase(this->svector.find(x.first));                       
        }
    }
    return *this;
}

//Przeciazenie operatora sprawdzajacego nierownosc wektorow (obiektow)
bool SparseVector::operator==(const SparseVector &v1){
    double eps = 0.001;
    if(this->svector.size()!=v1.svector.size())return false;
    for(auto& x: v1.svector){
        if(fabs(this->svector[x.first]-x.second)>eps){
            return false;
        }
    }
    return true;
}

//Przeciazenie operatora sprawdzajacego rownosc wektorow (obiektow)
bool SparseVector::operator!=(const SparseVector &v1){
    double eps = 0.001;
    if(this->svector.size()!=v1.svector.size())return true;
    for(auto& x: v1.svector){
        if(fabs(this->svector[x.first]-x.second)>eps){
            return true;
        }
    }
    return false;
}

//Przeciazenie operatora wypisujacego caly wektor danego obiektu (pozycje na ktorych sa dane wartosci)
std::ostream & operator<<(std::ostream & os,const SparseVector & v1){
    for(auto& x: v1.svector) os<<x.first<<" : "<<x.second<<std::endl;
    return os;
}

//Przeciazenie operatora wczytujacego
//Aby wczytac obiekt nalezy kolejno podawac pozycje/klucz (int) zatwierdzic enterem, podac wartosc (double) naprzemiennie.
//Konczymy wczytywanie wprowadzajac dowolny znak.
std::istream & operator>>(std::istream & is, SparseVector & v1){
    int key;
    double value;
    while((is>>key)&&(is>>value))v1.svector[key]=value;
    return is;
}

//Funkcja odczytujaca wartosc wektora na danej pozycji
double SparseVector::read(int key){
        double value;
        value=this->svector[key];
        if(this->svector[key]==0) this->svector.erase(this->svector.find(key));
        //^Po odczytaniu elementu niezawartego w hashmapie zostal on tworzony, wiec trzeba go bylo usunac po odczytaniu.
        //W przeciwnym wypadku w wektorze dodawany byl element [pozycja : 0]
        return value;
}

//Funkcja zmieniajaca wartosc wektora na danej pozycji
void SparseVector::change(int key, double value){
        this->svector[key]=value;
}

//Funkcja wyparta przez przeciazenie operatora<<
/*void SparseVector::show(){
    for(auto& x: this->svector){
        std::cout<<x.first<<" : "<<x.second<<std::endl;
    }
}*/