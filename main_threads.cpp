#include <thread> 
#include <iostream> 
#include <mutex> 
#include <atomic> 
#include <condition_variable> 
#include <vector>

//do zadania 1  

std::mutex mtx;

void print(int n, char c){
    int m = 1;
    mtx.lock();
    std::cout << "Czekam\n";
    while (m != 0)
    {
        std::cin >> m;
        //std::this_thread::yield();
    }

    for (int i = 0; i < n; ++i)\
        std::cout << c;

    std::cout << '\n';
    mtx.unlock();
}

//do zadania 2a 

int size = 100000; int firBound = 25000; int secBound = 50000; int thiBound = 75000; int fouBound = 100000;

void sumUpAtomic(std::atomic<int>& sum, const std::vector<int>& vec, int beg, int end) {
    for (auto it = beg; it < end; ++it)
        sum += vec[it];
}//2b 

void sumUpNonAtomic(int& sum, const std::vector<int>& vec, int beg, int end) {
    for (auto it = beg; it < end; ++it)
        sum += vec[it];
}

// zadanie 3 
std::mutex mut;
std::condition_variable cv;
bool ready = false;
std::vector<int> myvec(10);

void put_1() {
    std::unique_lock<std::mutex> locker(mut);
    for (int i = 0; i < myvec.size() / 2; i++)
        myvec[i] = 1;

    locker.unlock();
    cv.notify_one();
    ready = true;
}

void put_2() {
    std::unique_lock<std::mutex> locker(mut);
    cv.wait(locker, []() {return ready; });
    for (int i = 0; i < myvec.size() / 2; i++) 
        myvec[i + myvec.size() / 2] = 2;

    locker.unlock();
}


int main()

{

    //ZADANIE 1  

    // a) Stworz 2 watki wypisujace 50 dowolnych symboli za pomoca funkcji print 
    // b) Dodaj mutex, aby zagwarantowac ze symbole nie beda pomieszane 
    // c) Za pomoca yield zmodyfikuj print aby wypisywal symbole dopiero po wprowadzeniu przez uzytkownika do konsoli wartosci 0 

    //Rozw 
    std::cout << "zadanie 1" << std::endl;
    std::thread th1(print, 50, '*');
    std::thread th2(print, 50, '@');

    th1.join();
    th2.join();

    /* ZADANIE 2 Stwórz wektor o rozmiarze 100000 i wype³nij go losowymi liczbami. Korzystaj¹c z 4 w¹tków  posumuj wszystkie elementy wektora.
        a) jako typ zmiennej suma u¿yj zmiennej atomowej (wynik bêdzie poprawny)
        b) jako typ zmiennej suma u¿yj zmiennej int (niepoprawny wynik), porównaj wyniki. */



        //-----------atomic addition 
    std::cout << std::endl << "zadanie 2" << std::endl;
    std::vector<int> toSumUp;
    toSumUp.reserve(size);

    for (int i = 0; i < size; ++i)
        toSumUp.push_back(rand());

    //2a 
    std::atomic<int> sum(0);
    std::thread t1(sumUpAtomic, std::ref(sum), std::ref(toSumUp), 0, firBound);
    std::thread t2(sumUpAtomic, std::ref(sum), std::ref(toSumUp), firBound, secBound);
    std::thread t3(sumUpAtomic, std::ref(sum), std::ref(toSumUp), secBound, thiBound);
    std::thread t4(sumUpAtomic, std::ref(sum), std::ref(toSumUp), thiBound, fouBound);

    t1.join(); t2.join();
    t3.join(); t4.join();

    std::cout << "atomic result: " << sum << std::endl;
    //2b 
    int sum2 = 0;
    std::thread t5(sumUpNonAtomic, std::ref(sum2), std::ref(toSumUp), 0, firBound);
    std::thread t6(sumUpNonAtomic, std::ref(sum2), std::ref(toSumUp), firBound, secBound);
    std::thread t7(sumUpNonAtomic, std::ref(sum2), std::ref(toSumUp), secBound, thiBound);
    std::thread t8(sumUpNonAtomic, std::ref(sum2), std::ref(toSumUp), thiBound, fouBound);

    t5.join(); t6.join();
    t7.join(); t8.join();
    std::cout << "Non atomic result: " << sum2 << std::endl;

    /*ZADANIE 3 Stwórz wektor, który zostanie wype³niony liczbami 1 i 2. W¹tek 1. wype³ni pierwsz¹ po³owê wektora 1, 
    w¹tek 2. wype³ni drug¹ po³owê 2. Skorzystaj z condition_variable*/

    std::cout << std::endl << "zadanie 3" << std::endl;
    std::thread th_put_1(put_1);
    std::thread th_put_2(put_2);

    th_put_1.join();
    th_put_2.join();

    for (int i = 0; i < myvec.size(); i++)
        std::cout << myvec[i] << ' ';

    return 0;
}