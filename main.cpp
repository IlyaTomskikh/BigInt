#include <iomanip>
#include <future>
#include <thread>
#include "BigNum.cpp"


int main()
{
//    using chrono::high_resolution_clock;
//    using chrono::duration_cast;
//    using chrono::duration;
//    using chrono::nanoseconds;
    auto ix = 0;
    srand(BigNum::currentTimeMicrosec() + rand());
    while (ix < 2)
    {
        ++ix;
//        BigNum test;
//        cout << "Enter the number in the base 10" << endl;
//        test.in10();
//
//        cout << test << (test.isPrime() == 1 ? " is a prime number" : " is not a prime number") << endl;

//        cout << "Comparison: Fermat's result = " << test.testFermat() << ", Miller-Rabin's result = " << test.testMillerRabin() << endl;

//        cout << "Probabilities:\nFermat's test = " << test.getProbabilityOf("fermat") << "Miller-Rabin's test = " << test.getProbabilityOf("miller-rabin") << endl;
        int bnlen = 20;
        BigNum *ptr1 = nullptr;
        auto result1 = std::thread(BigNum::call, bnlen, &ptr1);

        BigNum *ptr2 = nullptr;
        auto result2 = std::thread(BigNum::call, bnlen, &ptr2);

        BigNum *ptr3 = nullptr;
        auto result3 = std::thread(BigNum::call, bnlen, &ptr3);

        BigNum *ptr4 = nullptr;
        auto result4 = std::thread(BigNum::call, bnlen, &ptr4);

        BigNum *ptr5 = nullptr;
        auto result5 = std::thread(BigNum::call, bnlen, &ptr5);

        BigNum *ptr6 = nullptr;
        auto result6 = std::thread(BigNum::call, bnlen, &ptr6);

        result1.detach();
        result2.detach();
        result3.detach();
        result4.detach();
        result5.detach();
        result6.detach();

        while (true)
        {
            this_thread::sleep_for(chrono::milliseconds(500));
            if (ptr1)
            {
                cout << "that = " << *ptr1 << endl;
                break;
            }
            if (ptr2)
            {
                cout << "that = " << *ptr2 << endl;
                break;
            }
            if (ptr3)
            {
                cout << "that = " << *ptr3 << endl;
                break;
            }
            if (ptr4)
            {
                cout << "that = " << *ptr4 << endl;
                break;
            }
            if (ptr5)
            {
                cout << "that = " << *ptr5 << endl;
                break;
            }
            if (ptr6)
            {
                cout << "that = " << *ptr6 << endl;
                break;
            }

        }

        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

//        cout << "Enter the prime number len" << endl;
//        int l;
//        cin >> l;
//        auto sp = BigNum::strongPrimeGeneratorGordon(l);
//        cout << "Strong Prime = " << sp << endl;
    }

    //calculatori.ru

    return 0;
}