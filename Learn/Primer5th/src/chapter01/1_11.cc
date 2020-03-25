#include <iostream>

void print_range(int low, int high)
{
    if (low > high)
        print_range(high, low);

    while (low <= high)
        std::cout << low++ << " ";
}

int main()
{
    int low = 0, high = 0;
    std::cout << "Please input tow integers:\n";
    std::cin >> low >> high;
    print_range(low, high);
    return 0;
}