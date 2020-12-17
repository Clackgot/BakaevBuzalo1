#include <iostream>
using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	cout << "Выполнил работу: Бакаев Александр\t\t\tГруппа: ФИТУ 2-5" << endl << endl;
	
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