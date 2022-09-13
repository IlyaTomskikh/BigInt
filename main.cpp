#include <iomanip>
#include <future>
#include <thread>
#include "BigNum.cpp"

//        cout << test << (test.isPrime() == 1 ? " is a prime number" : " is not a prime number") << endl;


int main()
{
    srand(BigNum::currentTimeMicrosec() + rand());
//    BigNum test;
//    cout << "Enter the number in the base 10" << endl;
//    test.in10();
//
//
//    cout << "Comparison: Fermat's result = " << test.testFermat() << ", Miller-Rabin's result = " << test.testMillerRabin() << endl;

//    cout << "Probabilities:\nFermat's test = " << test.getProbabilityOf("fermat") << "Miller-Rabin's test = " << test.getProbabilityOf("miller-rabin") << endl;

//    int bnlen = 20;
//    BigNum *ptr1 = nullptr;
//    auto result1 = std::thread(BigNum::call, bnlen, &ptr1);
//
//    BigNum *ptr2 = nullptr;
//    auto result2 = std::thread(BigNum::call, bnlen, &ptr2);
//
//    BigNum *ptr3 = nullptr;
//    auto result3 = std::thread(BigNum::call, bnlen, &ptr3);
//
//    BigNum *ptr4 = nullptr;
//    auto result4 = std::thread(BigNum::call, bnlen, &ptr4);
//
//    BigNum *ptr5 = nullptr;
//    auto result5 = std::thread(BigNum::call, bnlen, &ptr5);
//
//    BigNum *ptr6 = nullptr;
//    auto result6 = std::thread(BigNum::call, bnlen, &ptr6);
//
//    result1.detach();
//    result2.detach();
//    result3.detach();
//    result4.detach();
//    result5.detach();
//    result6.detach();

//    while (true)
//    {
//        this_thread::sleep_for(chrono::milliseconds(500));
//        if (ptr1)
//        {
//            cout << "strong prime = " << *ptr1 << endl;
//            break;
//        }
//        if (ptr2)
//        {
//            cout << "strong prime = " << *ptr2 << endl;
//            break;
//        }
//        if (ptr3)
//        {
//            cout << "strong prime = " << *ptr3 << endl;
//            break;
//        }
//        if (ptr4)
//        {
//            cout << "strong prime = " << *ptr4 << endl;
//            break;
//        }
//        if (ptr5)
//        {
//            cout << "strong prime = " << *ptr5 << endl;
//            break;
//        }
//        if (ptr6)
//        {
//            cout << "strong prime = " << *ptr6 << endl;
//            break;
//        }
//
//    }

    BigNum bigNum;
    bigNum.in10();
    auto res = bigNum.fact();
    for (BigNum factor: res) cout << factor << "; ";

//    auto cr = bigNum.superslowcuberoot();
//    cout << endl << "cuberoot(" << bigNum << ") = " << cr << endl;

    auto d = bigNum.algorithmOlvey();
    cout << "d = " << d << endl;

    cout << endl << "--- 777 777 777 777 777 777 ---" << endl;

    //calculatori.ru

    return 0;
}