#include <chrono>
#include <iomanip>
#include "BigNum.cpp"


int main()
{
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::nanoseconds;
    while (true)
    {
        int base;
        cout << "Enter 'close' to exit the program" << endl;
        cout << "Enter the base" << endl;
        string input;
        cin >> input;
        if (input == "close") return 1;
        base = stoi(input);
        BigNum test;
        cout << "Enter a big integer" << endl;
        switch (base) {
            case 10: {
                test.in10();
                break;
            }
            case 16: {
                test.in16();
                break;
            }
            default:
                return 666;
        }
        auto start = high_resolution_clock::now();
        auto square = test.fastSQ();
        auto end = high_resolution_clock::now();
        auto time_duration = duration_cast<nanoseconds>(end - start);
        string res;
        switch (base) {
            case 16: {
                res = square.out16().str();
                break;
            }
            case 10: {
                res = square.out10().str();
                break;
            }
        }
        cout << "Fast square: " << res << endl << "Time took " << time_duration.count() << endl;
        start = high_resolution_clock::now();
        square = test * test;
        end = high_resolution_clock::now();
        time_duration = duration_cast<nanoseconds>(end - start);
        switch (base) {
            case 16: {
                res = square.out16().str();
                break;
            }
            case 10: {
                res = square.out10().str();
                break;
            }
        }
        cout << "Slow square: " << res << endl << "Time took " << time_duration.count() << endl;

        cout << "Enter the power" << endl;
        BigNum power;
        power.in10();
        start = high_resolution_clock::now();
        auto exp = test.fastPow(power);
        end = high_resolution_clock::now();
        time_duration = duration_cast<nanoseconds>(end - start);
        res = exp.out10().str();
        cout << "Fast power: " << res << ", time took " << time_duration.count() << endl;

        start = high_resolution_clock::now();
        exp = test.slowPow(power);
        end = high_resolution_clock::now();
        time_duration = duration_cast<nanoseconds>(end - start);
        res = exp.out10().str();
        cout << "Slow power: " << res << ", time took " << time_duration.count() << endl;
    }



    //calculatori.ru

    return 777;
}