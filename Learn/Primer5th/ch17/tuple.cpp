
#include <bits/stdc++.h>

using namespace std;

//定义一个类型，表示一个三维坐标
using Coord3 = tuple<int, int, int>;

int randn(int a, int b) {
    return rand() % (b - a) + a;
}

Coord3 getRandomCoord() {
    int a = randn(0, 100);
    int b = randn(0, 100);
    int c = randn(0, 100);
    return Coord3(a, b, c);  //使用tuple的值初始化
}

int main() {
    srand(time(NULL));

    //# tuple, 快速而随意的数据结构
    // 可以与pair作比较，pair只有两个成员，而tuple可以有随意个，
    // 但是tuple的获取方式不同，需要使用 get<n>(tupleItem) 来获取第n个元素
    // 完全可以自定义结构体来取代tuple
    vector<tuple<int, int, int>> threeD;
    for (int i = 0; i < 10; i++) {
        threeD.push_back(make_tuple(i, i, i));
    }
    for_each(threeD.begin(), threeD.end(), [](const decltype(threeD[0])& item) {
        cout << "(" << get<0>(item) << "," << get<1>(item) << "," << get<2>(item) << ")" << endl;
    });
    cout << endl;

    //# 使用tuple返回多个值
    for (int i = 0; i < 10; i++) {
        auto item = getRandomCoord();
        cout << "(" << get<0>(item) << "," << get<1>(item) << "," << get<2>(item) << ")" << endl;
    }
    cout << endl;

    //# 可以看到， tuple的用法总体还是与pair相似的
}