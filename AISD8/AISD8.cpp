#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

struct Product {
    std::string name;
    int weight = 0;
    int value = 0;
};

bool getInput(int& value, const std::string& prompt) {
    std::cout << prompt;
    while (!(std::cin >> value) || value <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Пожалуйста, введите корректное значение: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

bool getInput(std::string& value, const std::string& prompt) {
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Пожалуйста, введите корректное значение: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

void findMaxValueProducts(int N, Product* products, int productCount, Product* selectedProducts, int& selectedProductCount) {
    int** dp = new int* [productCount + 1];
    for (int i = 0; i <= productCount; ++i) {
        dp[i] = new int[N + 1];
    }
    for (int i = 0; i <= productCount; ++i) {
        for (int w = 0; w <= N; ++w) {
            dp[i][w] = 0;
        }
    }

    for (int i = 1; i <= productCount; ++i) {
        for (int w = 1; w <= N; ++w) {
            if (products[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - products[i - 1].weight] + products[i - 1].value);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int w = N;
    selectedProductCount = 0;
    for (int i = productCount; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedProducts[selectedProductCount++] = products[i - 1];
            w -= products[i - 1].weight;
        }
    }

    for (int i = 0; i <= productCount; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int N;
    getInput(N, "Введите максимальную вместимость рюкзака: ");

    int productCount;
    getInput(productCount, "Введите количество предметов: ");

    Product* products = new Product[productCount];
    for (int i = 0; i < productCount; ++i) {
        getInput(products[i].name, "Введите название предмета " + std::to_string(i + 1) + ": ");
        getInput(products[i].weight, "Введите вес предмета " + std::to_string(i + 1) + ": ");
        getInput(products[i].value, "Введите стоимость предмета " + std::to_string(i + 1) + ": ");
    }

    Product* selectedProducts = new Product[productCount];
    for (int i = 0; i < productCount; ++i) {
        selectedProducts[i] = { "", 0, 0 }; // Инициализация каждого элемента массива selectedProducts
    }

    int selectedProductCount = 0;
    findMaxValueProducts(N, products, productCount, selectedProducts, selectedProductCount);

    int totalValue = 0;
    std::cout << "\nПредметы, выбранные для рюкзака:\n";
    for (int i = 0; i < selectedProductCount; ++i) {
        std::cout << "Название: " << selectedProducts[i].name << ", Вес: " << selectedProducts[i].weight << ", Стоимость: " << selectedProducts[i].value << "\n";
        totalValue += selectedProducts[i].value;
    }

    std::cout << "Максимальная стоимость предметов в рюкзаке: " << totalValue << "\n";

    delete[] products;
    delete[] selectedProducts;

    return 0;
}
