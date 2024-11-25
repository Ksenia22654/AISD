#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <map>

// Узел для дерева Хаффмана
struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Сравнение для приоритетной очереди
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Построение таблицы частоты символов
std::unordered_map<char, int> buildFrequencyTable(const std::string& text) {
    std::unordered_map<char, int> frequency;
    for (char ch : text) {
        frequency[ch]++;
    }
    return frequency;
}

// Построение дерева Хаффмана
Node* buildHuffmanTree(const std::unordered_map<char, int>& frequency) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;

    for (auto pair : frequency) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        minHeap.push(sum);
    }

    return minHeap.top();
}

// Построение таблицы кодов Хаффмана
void buildCodes(Node* root, std::string code, std::map<char, std::string>& huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    buildCodes(root->left, code + "0", huffmanCode);
    buildCodes(root->right, code + "1", huffmanCode);
}

// Кодирование текста
std::string encode(const std::string& text, const std::map<char, std::string>& huffmanCode) {
    std::string encodedText;
    for (char ch : text) {
        encodedText += huffmanCode.at(ch);
    }
    return encodedText;
}

// Вывод информации
void printInfo(const std::unordered_map<char, int>& frequency, const std::map<char, std::string>& huffmanCode, const std::string& encodedText) {
    std::cout << "Частота символов:\n";
    for (auto pair : frequency) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }

    std::cout << "\nКоды Хаффмана:\n";
    for (auto pair : huffmanCode) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }

    std::cout << "\nЗакодированный текст:\n" << encodedText << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    // Построение таблицы частоты
    std::unordered_map<char, int> frequency = buildFrequencyTable(text);

    // Построение дерева Хаффмана
    Node* root = buildHuffmanTree(frequency);

    // Построение кодов Хаффмана
    std::map<char, std::string> huffmanCode;
    buildCodes(root, "", huffmanCode);

    // Кодирование текста
    std::string encodedText = encode(text, huffmanCode);

    // Вывод результатов
    printInfo(frequency, huffmanCode, encodedText);

    return 0;
}