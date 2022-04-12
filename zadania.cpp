#include <thread> 
#include <iostream> 
#include <mutex> 
#include <atomic> 
#include <condition_variable> 
#include <vector>

int main(){

 //ZADANIE 1  

    // a) Stworz 2 watki wypisujace 50 dowolnych symboli za pomoca funkcji print 
    // b) Dodaj mutex, aby zagwarantowac ze symbole nie beda pomieszane 
    // c) Za pomoca yield zmodyfikuj print aby wypisywal symbole dopiero po wprowadzeniu przez uzytkownika do konsoli wartosci 0 


/* ZADANIE 2 Stwórz wektor o rozmiarze 100000 i wypełnij go losowymi liczbami. Korzystając z 4 wątków  posumuj wszystkie elementy wektora.
        a) jako typ zmiennej suma użyj zmiennej atomowej (wynik będzie poprawny)
        b) jako typ zmiennej suma użyj zmiennej int (niepoprawny wynik), porównaj wyniki. */
        
        
/*ZADANIE 3 Stwórz wektor, który zostanie wypełniony liczbami 1 i 2. Wątek 1. wypełni pierwszą połowę wektora 1, 
    wątek 2. wypełni drugą połowę 2. Skorzystaj z condition_variable*/

}
