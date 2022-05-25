#include <chrono>
#include <iomanip>
#include "BigNum.cpp"

int currentTimeMicrosec(){
    chrono::time_point<chrono::system_clock, chrono::microseconds> tp = chrono::time_point_cast<chrono::microseconds>(chrono::high_resolution_clock::now());
    auto tmp = chrono::duration_cast<chrono::microseconds>(tp.time_since_epoch());
    return tmp.count();
}

int main()
{
//    using chrono::high_resolution_clock;
//    using chrono::duration_cast;
//    using chrono::duration;
//    using chrono::nanoseconds;
    auto ix = 0;
    srand(currentTimeMicrosec() + rand());
    while (ix < 2)
    {
        ++ix;
        BigNum test;
        cout << "Enter the number in the base 10" << endl;
        test.in10();
        auto isPrime = test.isPrime();
        if (isPrime) cout << test.to_string() << " is a prime number" << endl;
        else cout << test.to_string() << " is not a prime number" << endl;
//        auto start = high_resolution_clock::now();
//        auto square = test.fastSQ();
//        auto end = high_resolution_clock::now();
//        auto time_duration = duration_cast<nanoseconds>(end - start);
//        string res;
//        res = square.out10().str();
//        cout << "Fast square: " << res << endl << "Time took " << time_duration.count() << endl;
//        start = high_resolution_clock::now();
//        square = test * test;
//        end = high_resolution_clock::now();
//        time_duration = duration_cast<nanoseconds>(end - start);
//        res = square.out10().str();
//        cout << "Slow square: " << res << endl << "Time took " << time_duration.count() << endl;
//
//        cout << "Enter the power" << endl;
//        BigNum power;
//        power.in10();
//        start = high_resolution_clock::now();
//        auto exp = test.fastPow(power);
//        end = high_resolution_clock::now();
//        time_duration = duration_cast<nanoseconds>(end - start);
//        res = exp.out10().str();
//        cout << "Fast power: " << res << ", time took " << time_duration.count() << endl;
//
//        start = high_resolution_clock::now();
//        exp = test.slowPow(power);
//        end = high_resolution_clock::now();
//        time_duration = duration_cast<nanoseconds>(end - start);
//        res = exp.out10().str();
//        cout << "Slow power: " << res << ", time took " << time_duration.count() << endl;

//        cout << "Enter the modulo" << endl;
//        BigNum modulo;
//        modulo.in10();
//        //res = test.barret(modulo).to_string();
//        cout << test.to_string() << " mod " << modulo.to_string() << " = " << test.barret(modulo).to_string() << endl;
    }

    //calculatori.ru

    return 0;
}