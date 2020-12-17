#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;


int digitCount(int value)
{
	int n = 1;
	while ((value /= 10) > 0) n++;
	return n;
}

typedef class Lnum
{
private:
	vector<int> num = vector<int>();
	static const int base;
public:
	Lnum(unsigned int size)
	{
		num = vector<int>(size);
	}
	Lnum()
	{
	}
	friend std::ostream& operator<< (std::ostream& out, const Lnum& in)
	{
		auto num = in.num;
		cout << (int)(num.empty() ? 0 : num.back());
		for (int i = (int)num.size() - 2; i >= 0; --i)
			cout << setw(9) << setfill('0') << num[i];
		return out;
	}
	friend std::istream& operator>> (std::istream& in, Lnum& out)
	{
		string s;
		in >> s;
		for (int i = (int)s.length(); i > 0; i -= 9)
			if (i < 9)
				out.num.push_back(atoi(s.substr(0, i).c_str()));
			else
				out.num.push_back(atoi(s.substr(i - 9, 9).c_str()));
		return in;
	}
	friend Lnum operator+(const Lnum& n1, const Lnum& n2)
	{
		auto tn1 = n1;
		int carry = 0;
		for (size_t i = 0; i < max(tn1.num.size(), n2.num.size()) || carry; ++i) {
			if (i == tn1.num.size())
				tn1.num.push_back(0);
			tn1.num[i] += carry + (i < n2.num.size() ? n2.num[i] : 0);
			carry = tn1.num[i] >= base;
			if (carry)  tn1.num[i] -= base;
		}
		return tn1;
	}
	friend Lnum operator-(const Lnum& n1, const Lnum& n2)
	{
		auto tn1 = n1;

		int carry = 0;
		for (size_t i = 0; i < n2.num.size() || carry; ++i) {
			tn1.num[i] -= carry + (i < n2.num.size() ? n2.num[i] : 0);
			carry = tn1.num[i] < 0;
			if (carry)  tn1.num[i] += base;
		}
		while (tn1.num.size() > 1 && tn1.num.back() == 0)
			tn1.num.pop_back();
		return tn1;
	}
	friend Lnum operator*(const Lnum& n1, const Lnum& n2)
	{
		Lnum c(n1.num.size() + n2.num.size());
		for (size_t i = 0; i < n1.num.size(); ++i)
			for (int j = 0, carry = 0; j < (int)n2.num.size() || carry; ++j) {
				long long cur = c.num[i + j] + n1.num[i] * 1ll * (j < (int)n2.num.size() ? n2.num[j] : 0) + carry;
				c.num[i + j] = int(cur % base);
				carry = int(cur / base);
			}
		while (c.num.size() > 1 && c.num.back() == 0)
			c.num.pop_back();

		return c;
	}
	friend int operator%(const Lnum& n1, long long n2)
	{
		auto tn1 = n1;
		auto &a = tn1.num;
		auto b = n2;

		int carry = 0;
		for (int i = (int)a.size() - 1; i >= 0; --i) {
			long long cur = a[i] + carry * 1ll * base;
			a[i] = int(cur / b);
			carry = int(cur % b);
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
		return carry;
	}
	friend bool operator==(const Lnum& n1, const Lnum& n2)
	{
		auto a = n1.num;
		auto b = n2.num;

		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
		while (b.size() > 1 && b.back() == 0)
			b.pop_back();

		if (a.size() != b.size())
		{
			return false;
		}
		else
		{
			for (size_t i = 0; i < n1.num.size(); ++i)
			{
				if (n1.num[i] != n2.num[i])
				{
					return false;
				}
			}
		}
		return true;
	}
	friend bool operator<(const Lnum& n1, const Lnum& n2)
	{
		auto a = n1.num;
		auto b = n2.num;

		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
		while (b.size() > 1 && b.back() == 0)
			b.pop_back();

		if (a.size() < b.size())
		{
			return true;
		}
		else
		{
			for (size_t i = 0; i < n1.num.size(); ++i)
			{
				if (n1.num[i] < n2.num[i])
				{
					return true;
				}
			}
		}
		return false;
	}
	friend bool operator>(const Lnum& n1, const Lnum& n2)
	{
		return !(n1 < n2);
	}
	friend bool operator<=(const Lnum& n1, const Lnum& n2)
	{
		return n1 < n2 || n1 == n2;
	}
	friend bool operator>=(const Lnum& n1, const Lnum& n2)
	{
		return n1 > n2 || n1 == n2;
	}
};
const int Lnum::base= 1000 * 1000 * 1000;




int main(){
	setlocale(LC_ALL, "Russian");
	cout << "Выполнил работу: Бакаев Александр\t\t\tГруппа: ФИТУ 2-5" << endl << endl;
	



	
	
	typedef vector<int> lnum;
	

	unsigned long long int a, b = 0;
	bool founded = false;
	cin >> a;
	clock_t start = clock();
	if (a % 2 == 0)
	{
		cout << "NO" << endl;
		cout << "Т.к. a % 2 == 0" << endl;
	}
	else
	{
		for (unsigned long long int n = 1; n <= 11111111111111111111; n = n * 10 + 1)
		{
			if (n % a == 0)
			{
				cout << n << endl;
				founded = true;
			}
			++b;
		}
		if (!founded)cout << "NO" << endl;
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Время выполнения: %f сек.\n", seconds);

	return 0;
}