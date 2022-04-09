#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <sstream>

///short == 16
#define BASE_SIZE (sizeof(BASE)*8)
#define MAX_BASE_VALUE ((DBASE) 1 << BASE_SIZE)
using namespace std;
typedef unsigned short BASE;
typedef unsigned int DBASE;
typedef unsigned long long QBASE;


class BigNum
{
private:
    int maxLen;
    int len;
    BASE *digits;
public:

//	DEC CIN/COUT
    friend istream & operator>> (istream &in, BigNum &that)
    {
        string s;
        in >> s;
        delete[] that.digits;
        that.len = 1;
        that.maxLen = (s.length() - 1) / (BASE_SIZE / 4) + 1;
        that.digits = new BASE[that.maxLen];
        for (int i = 0; i < that.maxLen; ++i) that.digits[i] = 0;
        for (char i: s) if (i >= '0' && i <= '9')
        {
            that *= 10;
            that += i - '0';
        }
        that.lenNorm();
        return in;
    }
    friend ostream & operator<< (ostream &out, BigNum &that)
    {
        if (!(that.digits[0] == 0 && that.len == 1))
        {
            string s;
            BigNum tmp(that);
            while (tmp.digits[0] != 0 || tmp.len > 1)
            {
                char _ch = tmp % 10 + '0';
                s.push_back(_ch);
                tmp /= 10;
            }
            reverse(s.begin(), s.end());
            out << s;
        }
        else out << 0;
        return out;
    }

    string in2()
    {
        string str;
        cin >> str;
        delete[] digits;
        len = 1;
        maxLen = (str.length() - 1) / (BASE_SIZE / 4) + 1;
        digits = new BASE[maxLen];
        for (auto i = 0; i < maxLen; ++i) digits[i] ^= digits[i];
        for (auto i : str) if (i == '0' || i == '1')
        {
            *this *= 2;
            *this += i - '0';
        }
        lenNorm();
        return str;
    }
    string in10()
    {
        string s;
        cin >> s;
        delete[] digits;
        len = 1;
        maxLen = (s.length() - 1) / (BASE_SIZE / 4) + 1;
        digits = new BASE[maxLen];
        for (int i = 0; i < maxLen; ++i) digits[i] = 0;
        for (char i: s) if (i >= '0' && i <= '9')
        {
            *this *= 10;
            *this += i - '0';
        }
        this->lenNorm();
        return s;
    }
    string in16()
    {
        string str;
        cin >> str;
        delete[] digits;
        len = (str.length() - 1) / (BASE_SIZE / 4) + 1;
        digits = new BASE[len];
        for (int i = len; i--;) digits[i] = 0;
        int j = 0, k = 0;
        BASE tmp;
        for (int i = str.length(); i--;)
        {
            if (str[i] <= '9' && str[i] >= '0') tmp = str[i] - '0';
            else
            {
                if (str[i] <= 'f' && str[i] >= 'a') tmp = str[i] - 'a' + 10;
                else
                {
                    if (str[i] <= 'F' && str[i] >= 'A') tmp = str[i] - 'A' + 10;
                    else break;
                }
            }
            digits[j] |= tmp << (k * 4);
            ++k;
            if (k >= BASE_SIZE / 4)
            {
                k = 0;
                ++j;
            }
        }
        lenNorm();
        return str;
    }
    stringstream out16()
    {
        stringstream ss;
        if (digits)
        {
            for (auto i = len; i--;)
            {
                ss.width(BASE_SIZE / 4);
                ss.fill('0');
                ss << hex << (int) digits[i] << dec;
            }
        }
        else ss << ' ';
        return ss;
    }
    stringstream out10()
    {
        stringstream out;
        if (!(digits[0] == 0 && len == 1))
        {
            string s;
            BigNum tmp(*this);
            while (tmp.digits[0] != 0 || tmp.len > 1)
            {
                char _ch = tmp % 10 + '0';
                s.push_back(_ch);
                tmp /= 10;
            }
            reverse(s.begin(), s.end());
            out << s;
        }
        else out << 0;
        return out;
    }
    stringstream out2()
    {
        stringstream out;
        if (!(digits[0] == 0 && len == 1))
        {
            string s;
            BigNum tmp(*this);
            while (tmp.digits[0] != 0 || tmp.len > 1)
            {
                char _ch = tmp % 2 + '0';
                s.push_back(_ch);
                tmp /= 2;
            }
            reverse(s.begin(), s.end());
            out << s;
        }
        else out << 0;
        return out;
    }

    BigNum(string &str)
    {
        len = maxLen = 0;
        std::stringstream sin;
        sin << str;
        sin >> *this;
    }

    BigNum(int l = 1, bool flag = true): len(l), maxLen(l)
    {
        digits = new BASE[len];
        if (flag) for(int i = 0; i < len; ++i) digits[i] = 0;
        else
        {
            for(int i = 0; i < len; ++i)
            {
                default_random_engine rng(time(0));
                uniform_int_distribution<int> rng_dist(0, 255);
                digits[i] = static_cast<BASE>(rng_dist(rng));
            }
            lenNorm();
        }
    }
    BigNum(const BigNum &that): len(that.len), maxLen(that.maxLen)
    {
        digits = new BASE[maxLen];
        for (int i = 0; i < maxLen; ++i) digits[i] = that.digits[i];
    }
    ~BigNum()
    {
        len ^= len;
        maxLen ^= maxLen;
        delete[] digits;
        digits = nullptr;
    }
    BigNum & operator= (const BigNum &that)
    {
        if (this != &that)
        {
            len = that.len;
            maxLen = that.maxLen;
            delete[] digits;
            digits = new BASE[maxLen];
            for (int i = 0; i < maxLen; i++) digits[i] = that.digits[i];
        }
        return *this;
    }


    BASE & operator[](int ix)
    {
        return digits[ix];
    }

    short cmp(const BigNum &that)
    {
        if (this == &that) return 0;
        if (len < that.len) return -1;
        if (len > that.len) return 1;
        for (int i = len - 1; i >= 0; i--)
        {
            if (digits[i] < that.digits[i]) return -1;
            if (digits[i] > that.digits[i]) return 1;
        }
        return 0;
    }
    bool operator== (const BigNum &that)
    {
        for (int i = 0; i < len; ++i) if (digits[i] != that.digits[i]) return false;
        return true;
    }
    bool operator!= (const BigNum &that)
    {
        return !(*this == that);
    }
    bool operator< (const BigNum &that)
    {
        if (cmp(that) < 0) return true;
        else return false;
    }
    bool operator> (const BigNum &that)
    {
        if (cmp(that) > 0) return true;
        else return false;
    }
    bool operator<= (const BigNum &that)
    {
        if (cmp(that) <= 0) return true;
        else return false;
    }
    bool operator>= (const BigNum &that)
    {
        if (cmp(that) >= 0) return true;
        else return false;
    }
    BigNum operator+ (const BigNum &that)
    {
        BigNum sum(max(len, that.len) + 1);
        int nm = min(len, that.len), j = 0, k = 0;
        DBASE tmp = 0;
        while (j < nm)
        {
            tmp = DBASE(digits[j]) + DBASE(that.digits[j]) + DBASE(k);
            sum.digits[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
            ++j;
        }
        while (j < len)
        {
            tmp = DBASE(digits[j]) + DBASE(k);
            sum.digits[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
            ++j;
        }
        while (j < that.len)
        {
            tmp = DBASE(that.digits[j]) + DBASE(k);
            sum.digits[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
            ++j;
        }
        sum.digits[j] = k;
        sum.lenNorm();
        return sum;
    }
    BigNum operator+= (const BigNum &that)
    {
        *this = *this + that;
        return *this;
    }
    BigNum operator+ (BASE num)
    {
        BASE k = 0;
        int newLen = maxLen;
        if (len + 1 > maxLen) newLen = len + 1;
        BigNum result(newLen);
        DBASE tmp = DBASE(digits[0]) + DBASE(num) + DBASE(k);
        k = (BASE)(tmp >> BASE_SIZE);
        result.digits[0] = (BASE)tmp;
        for (int i = 1; i < len; i++)
        {
            tmp = DBASE(digits[i]) + DBASE(k);
            k = (BASE)(tmp >> BASE_SIZE);
            result.digits[i] = (BASE)tmp;
        }
        result.digits[len] = k;
        result.lenNorm();
        return result;
    }
    BigNum operator+= (BASE num)
    {
        *this = *this + num;
        return *this;
    }
    BigNum operator- (const BigNum &that)
    {
        BigNum sub(len);
        if (*this >= that)
        {
            DBASE tmp;
            int k = 0, j = 0;
            while (j < that.len)
            {
                tmp = MAX_BASE_VALUE + digits[j];
                tmp = tmp - that.digits[j] - k;
                sub.digits[j] = (BASE)tmp;
                k = !(tmp >> BASE_SIZE);
                // ! is safer then ~
                ++j;
            }
            while (j < len)
            {
                tmp = MAX_BASE_VALUE + digits[j];
                tmp -= k;
                sub.digits[j] = (BASE)tmp;
                k = !(tmp >> BASE_SIZE);
                ++j;
            }
            sub.lenNorm();
        }
        else
        {
            cerr << "right operand must be less or equal" << endl;
            return *this;
        }
        return sub;
    }
    BigNum operator-= (const BigNum &that)
    {
        *this = *this - that;
        return *this;
    }
    BigNum operator* (const BASE num)
    {
        BigNum mul(len + 1);
        mul.len = len + 1;
        DBASE tmp = 0;
        BASE k = 0;
        for (int j = 0; j < len; ++j)
        {
            tmp = (DBASE(digits[j]) * DBASE(num)) + DBASE(k);
            mul.digits[j] = (BASE)tmp;
            k = tmp >> BASE_SIZE;
        }
        mul.digits[len] = k;
        mul.lenNorm();
        return mul;
    }
    BigNum operator*= (const BASE num)
    {
        *this = *this * num;
        return *this;
    }
    BigNum operator* (const BigNum &that)
    {
        BigNum mul(len + that.len);
        DBASE tmp;
        for (int i = 0; i < len; ++i)
        {
            int k = 0;
            for (int j = 0; j < that.len; ++j)
            {
                tmp = DBASE(that.digits[j]) * DBASE(digits[i]) + DBASE(mul.digits[i + j]) + DBASE(k);
                mul.digits[i + j] = (BASE)tmp;
                k = (BASE)(tmp >> BASE_SIZE);
            }
            mul.digits[that.len + i] += k;
        }
        mul.lenNorm();
        return mul;
    }
    BigNum operator*= (const BigNum &that)
    {
        *this = (*this) * (that);
        return *this;
    }
    BigNum operator/ (const BASE num)
    {
        DBASE tmp, k = 0;
        BigNum q(len);
        for(int i = len - 1; i >= 0; --i)
        {
            tmp = (k << BASE_SIZE) + digits[i];
            k = tmp % num;
            q.digits[i] = tmp / num;
        }
        q.lenNorm();
        return q;
    }
    BigNum operator/= (const BASE num)
    {
        *this = *this / num;
        return *this;
    }
    BASE operator% (const BASE num)
    {
        DBASE tmp, r = 0;
        for (int i = len - 1; i >= 0; --i)
        {
            tmp = ((DBASE) r << BASE_SIZE) + digits[i];
            r = (BASE) (tmp % num);
        }
        return r;
    }
    BASE operator%= (const BASE num)
    {
        BASE mod = *this % num;
        return mod;
    }

    BigNum operator/ (BigNum &that)
    {
        if (that.len == 1)
        {
            BigNum res = *this / that.digits[0];
            return res;
        }
        if (that.digits[that.len - 1] == 0 || that.len < 1 || *this < that)
        {
            cout << "that.digits[that.len - 1] == 0 || that.len < 1 || *this < that" << endl;
            return *this;
        }
        return divmod(*this, that).first;
    }
    BigNum operator/= (BigNum &that)
    {
        *this = *this / that;
        return *this;
    }

    BigNum operator% (BigNum &that)
    {
        if (that.len == 1)
        {
            BigNum r(1);
            r.digits[0] = *this % that.digits[0];
            return r;
        }
        if (that.digits[that.len - 1] == 0 || that.len < 1 || *this < that)
        {
            cout << "that.digits[that.len - 1] == 0 || that.len < 1 || *this < that" << endl;
            return *this;
        }
        return divmod(*this, that).second;
    }
    BigNum operator%= (BigNum &that)
    {
        *this = *this % that;
        return *this;
    }

    BigNum fastSQ ()
    {
        auto x = digits;
        auto y = BigNum(2 * len);
        auto x_square = y.digits;
        QBASE cuv, tmp;
        ///step 2.1:
        for (auto i = 0; i < len; ++i)
        {
            ///cuv = y_2i + x_i^2:
            cuv = QBASE(x_square[2 * i]) + QBASE(x[i]) * QBASE(x[i]);
            ///y_2i = u:
            x_square[2 * i] = BASE(cuv);
            ///step 2.2:
            for (auto j = i + 1; j < len; ++j)
            {
                ///cuv = y_(i+j) + 2*x_i*x_j + carry:
                cuv = QBASE(x_square[i + j]) + QBASE(2) * QBASE(x[i]) * QBASE(x[j]) + (cuv >> BASE_SIZE);
                ///y_(i + j) = v:
                x_square[i + j] = BASE(cuv);
            }
            ///step 2.3:
            ///computations with carry bits - [y_(i+len+1), y_(i+len)] += [c, u]:
            tmp = QBASE(x_square[i + len + 1] << BASE_SIZE | x_square[i + len]) + QBASE(cuv >> BASE_SIZE);
            ///+= has been transformed to = due to the presence of y_(i + len) && y_(i + len + 1) in the variable tmp
            ///y_(i + len) += u:
            x_square[i + len] = BASE(tmp);
            ///y_(i + len + 1) += c:
            x_square[i + len + 1] = BASE(tmp >> BASE_SIZE);
        }
        y.lenNorm();
        return y;
    }

    QBASE bits()
    {
        ///<bit> = [b]
        ///[0]100 0110 1111
        ///<bit> = 0 != 1
        ///0[1]00 0110 1111
        ///<bit> = 1 == 1 -> return: number_of_units_in_the_digits_array * size_of_unit + position_of(<bit>)
        for (auto i = len - 1; i >= 0; --i)
            for (auto j = BASE_SIZE - 1; j >= 0; --j)
                if ((digits[i] >> j) & 1) return (i * BASE_SIZE + j + 1);
        return 0;
    }

    bool is1(int pos)
    {
        if (pos < 0) throw "NegativeIndexException";
        auto unit = pos / BASE_SIZE;    ///to make it faster
        if (unit > 1) throw "IndexOutOfBoundsException";
        return digits[unit] & 1 << pos % BASE_SIZE;
    }

    ///<-
    BigNum fastPow(BigNum power)
    {
        BigNum q = BigNum(*this);
        BigNum res(1);
        ///step 1:
        if (power.is1(0)) res = *this;
        else res += BASE(1);
        auto powerBits = power.bits();
        ///step 2:
        for (auto i = 1; i < powerBits; ++i)
        {
            q = q.fastSQ();                    ///2.1
            if (power.is1(i)) res *= q;    ///2.2
        }
        return res;
    }

    BigNum slowPow(const BigNum& power) const
    {
        BigNum iter(1);
        BigNum res(1);
        res += 1;
        while (iter < power)
        {
            res *= *this;
            iter += 1;
        }
        return res;
    }

    friend pair<BigNum, BigNum> divmod(BigNum &a, BigNum &that)	///a div that && a mod that
    {
        BigNum divident = a,
                divisor = that,
                q(a.len);
        q.len = 1;
        //нормализация (D1)
        DBASE q_, r_, b = MAX_BASE_VALUE,
                d = MAX_BASE_VALUE / ((DBASE)that.digits[that.len - 1] + (DBASE)1);;
        if(d != 1)
        {
            divident *= d;
            divisor *= d;
        }
        BigNum tmpDivident = divident;
        if (a.len == divident.len)
        {
            delete[] divident.digits;
            divident.digits = new BASE[tmpDivident.len + 1];
            divident.maxLen++;
            divident.len++;
            for(int i = 0; i < tmpDivident.len; ++i) divident.digits[i] = tmpDivident.digits[i];
            divident.digits[divident.len - 1] = 0;
        }
        //начальная установка индекса (D2)
        int j = a.len - that.len, k = divisor.len;
        for(; j >= 0; --j)	//шаг цикла (D7)
        {
            //вычисление q^ и r^, проверка сложного условия (D3)
            q_ = (((DBASE(divident.digits[j + k]) << BASE_SIZE)) + divident.digits[j + k - 1]) / divisor.digits[k - 1];
            r_ = (((DBASE(divident.digits[j + k]) << BASE_SIZE)) + divident.digits[j + k - 1]) % divisor.digits[k - 1];
            if ((q_ == b) || ((q_ * divisor.digits[k - 2]) > (b * r_ + divident.digits[j + k - 2])))
            {
                --q_;
                r_ = r_ + divisor.digits[k - 1];
                if ((r_ < b) && ((q_ == b) || (q_ * divisor.digits[k - 2] > b * r_ + divident.digits[j + k - 2]))) --q_;
            }
            int dl = divisor.len;
            BigNum tmpDivisor = divisor * q_;
            //умножить-вычесть (D4)
            DBASE tmp = 0, k_ = 0;
            int ix = j, jx = dl, i = ix, l = 0;
            while (i <= ix + jx)
            {
                tmp = MAX_BASE_VALUE + DBASE(divident.digits[i]);
                tmp -= DBASE(tmpDivisor.digits[l]) + DBASE(k_);
                divident.digits[i] = (BASE) tmp;
                k_ = !(tmp >> BASE_SIZE);
                ++i;
                ++l;
            }
            divident.lenNorm();
            DBASE fl = k_;
            //присваивание и проверка условия (D5)
            q.digits[j] = q_;
            q.len++;
            if (fl < 0)
            {
                //компенсировать сложение (D6)
                i = j;
                l = 0;
                int ln = i + divisor.len;
                for (; i <= ln; ++i)
                {
                    DBASE tmp = DBASE(divident.digits[i]) + DBASE(divisor.digits[l]) + DBASE(k_);
                    k_ = (BASE) (tmp >> BASE_SIZE);
                    divident.digits[i] = (BASE) tmp;
                    ++l;
                }
                divident.digits[i] = k_;
                divident.lenNorm();
                q.digits[j]--;
            }
        }
        divident.len = divisor.len;
        divident.maxLen = divisor.maxLen;
        BigNum r = divident / d;	//D8 - денормализация для модуля
        q.lenNorm();
        return make_pair(q, r);
    }

    string to_string()
    {
        string s;
        BigNum tmp(*this);
        while (tmp.digits[0] != 0 || tmp.len > 1)
        {
            char _ch = tmp % 10 + '0';
            s.push_back(_ch);
            tmp /= 10;
        }
        reverse(s.begin(), s.end());
        return s;
    }

    void lenNorm()
    {
        while (len - 1 > 0 && digits[len - 1] == 0) --len;
    }

    BigNum getBarretZ(BigNum modulo)
    {
        auto z = BigNum(2 * modulo.len + 1);
        z.digits[2 * modulo.len] = 1;  ///z^2k
        z.len = 2 * modulo.len + 1;
        z /= modulo;
        return z;
    }

    ///*this / base^k
    BigNum barretDIV(int k)
    {
        if (k > len)
        {
            BigNum res(len);
            res.len = len;
            return res;
        }
        auto tmp = len - k;
        BigNum res(tmp);
        res.len = tmp;
        for (auto i = 0; i < tmp; ++i) res.digits[i] = digits[i + k];
        return res;
    }

    ///*this mod base^k
    BigNum barretMOD(int k)
    {
        if (k > len) return *this;
        BigNum res(k);
        res.len = k;
        for (auto i = 0; i < k; ++i) res.digits[i] = digits[i];
        return res;
    }

    BigNum barret(const BigNum& modulo)
    {
        if (len > modulo.len * 2) return *this;
        ///z = [b^2k / m]
        auto z = getBarretZ(modulo);

        ///q' = [([x / b^k-1] * z] / b^k+1]
        auto q = (barretDIV(modulo.len - 1) * z).barretDIV(modulo.len + 1);

        ///r1 = x mod b^k+1
        auto r1 = barretMOD(modulo.len + 1);
        ///r2 = q' * m mod b^k+1
        auto r2 = (q * modulo).barretMOD(modulo.len + 1);

        BigNum r(modulo.len + 2);
        if (r1 >= r2) r = r1 - r2;
        else
        {
            r.digits[modulo.len + 1] = 1;
            r.len = modulo.len + 2;
            r += r1 - r2;
        }
        while (r >= modulo) r -= modulo;
        return r;
    }
};