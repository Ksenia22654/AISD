#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> findLIS(std::vector<int>& nums) {
    if (nums.empty()) return {};

    std::vector<int> dp(nums.size(), 1);
    std::vector<int> prev(nums.size(), -1);

    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }

    int maxLength = *std::max_element(dp.begin(), dp.end());
    std::vector<int> lis;
    for (int i = nums.size() - 1; i >= 0; --i) {
        if (dp[i] == maxLength) {
            std::vector<int> temp;
            for (int j = i; j >= 0; j = prev[j]) {
                temp.push_back(nums[j]);
                if (prev[j] == -1) break;
            }
            std::reverse(temp.begin(), temp.end());
            if (temp.size() > lis.size()) {
                lis = temp;
            }
        }
    }

    return lis;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int N;
    std::cout << "Введите число элементов последовательности: ";
    std::cin >> N;

    std::vector<int> nums(N);
    std::cout << "Введите элементы последовательности: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> nums[i];
    }

    std::vector<int> lis = findLIS(nums);

    std::cout << "Длина максимальной возрастающей подпоследовательности: " << lis.size() << std::endl;
    std::cout << "Максимальная возрастающая подпоследовательность: ";
    for (int num : lis) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
