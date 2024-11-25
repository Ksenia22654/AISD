#include <iostream>

using namespace std;

void hanoy(int n, int i, int k, int tmp) {
    if (n == 0) {
        return;
    }

    hanoy(n - 1, i, tmp, k);
    cout << "Переместить диск " << n << " с " << i << " на " << k << " стержень" << endl;
    hanoy(n - 1, tmp, k, i);
}

int main() {
    setlocale(0, "rus");

    int N;
    int finalPeg;

    cout << "Введите количество дисков: ";
    cin >> N;

    cout << "Введите конечный стержень (1, 2 или 3): ";
    cin >> finalPeg;

    // Обеспечим, чтобы временный стержень был корректным
    int tempPeg = 6 - 1 - finalPeg;

    hanoy(N, 1, finalPeg, tempPeg);

    return 0;
}
