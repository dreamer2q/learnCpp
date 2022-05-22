
#include "graph.h"

void showMap() {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "-                                                                      -" << endl;
    cout << "-          ┏━━━━━━━━━━━━━━ 9藤廊寄梦━━━━━━━━━━━━━┓                     -" << endl;
    cout << "-          ┃        750                 650      ┃                     -" << endl;
    cout << "-      450 ┃                                     ┃500                  -" << endl;
    cout << "-          ┃                                     ┃                     -" << endl;
    cout << "-          ┃        850                750       ┃  450                -" << endl;
    cout << "-      2巨碟邀星━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┻━━━━━━━━ 6艺苑秋歌   -" << endl;
    cout << "-          ┃                  250┃                          200┃       -" << endl;
    cout << "-          ┃                     ┃           900               ┃       -" << endl;
    cout << "-          ┃                 8三省问天━━━━━━━━━━━━━━━━━━━━ 7从鱼听学   -" << endl;
    cout << "-          ┃                     ┃                             ┃       -" << endl;
    cout << "-          ┃ 800                 ┃ 300                      400┃       -" << endl;
    cout << "-          ┃                     ┃                             ┃       -" << endl;
    cout << "-          ┃                 4书海风荷                         ┃       -" << endl;
    cout << "-          ┃        1050         ┃150          1400        5兰亭春晓   -" << endl;
    cout << "-        ┏━┻━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━┳━━━┛        -" << endl;
    cout << "-     10正心修读                 ┃ 250       1200         ┃  150       -" << endl;
    cout << "-                                ┃                    3雅湖云影        -" << endl;
    cout << "-                            1长虹揽月                                 -" << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

void showMenu() {
    cout << "                   ★-----★---------★---------★-----★" << endl;
    cout << "                               杭电导游系统              " << endl;
    cout << "                   ☆                                  ☆" << endl;
    cout << "                               1   杭电一览              " << endl;
    cout << "                   ☆          2   查询路径            ☆" << endl;
    cout << "                               3   查询景点              " << endl;
    cout << "                   ☆          4   修改信息            ☆" << endl;
    cout << "                               0   退出系统              " << endl;
    cout << "                   ☆                                  ☆" << endl;
    cout << "                              杭电师生欢迎您             " << endl;
    cout << "                   ★-----★---------★---------★-----★" << endl;
    cout << endl;
    cout << endl;
    cout << "请选择数字命令：";
}

void bye() {
    cout << "                   ★-----★---------★---------★-----★" << endl;
    cout << endl;
    cout << "                   ☆            感谢您的使用！        ☆" << endl;
    cout << endl;
    cout << "                   ★-----★---------★---------★-----★" << endl;
    cout << endl;
}

void cls() {
    system("cls");
}
void pause() {
    system("pause");
}

void showScenes() {
    cout << "景点编号\t景点名称" << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < VERTEX_NUM; i++) {
        cout << "  " << scenesVex[i].id << "\t\t" << scenesVex[i].title << endl;
    }
    cout << endl;
}

void queryScene() {
    showScenes();
    int sel;
    cout << "查询编号(0返回上一级):";
    while (cin >> sel, sel) {
        cout << "\n\t\t\t" << scenesVex[sel - 1].title << endl;
        cout << "\n\t" << scenesVex[sel - 1].intro << endl;
        cout << endl;
        cout << "查询编号(0返回上一级):";
    }
}

void updateScene() {
    showMap();
    cout << "需要修改的景点编号:";
    int sel;
    cin >> sel;
    sel--;
    string title, content;
    cout << endl;
    cout << "标题：";
    cin >> title;
    cout << "介绍：";
    cin >> content;
    scenesVex[sel].title = title;
    scenesVex[sel].intro = content;
    cout << endl;
    cout << "修改成功" << endl;
    pause();
}

void queryPath() {
    showMap();
    int s, e;
    cout << "起始编号：";
    cin >> s;
    cout << "借宿编号：";
    cin >> e;
    auto result = Dijkstra(sceneGraph, s - 1, e - 1);
    cout << "最短路径长度为：" << get<0>(result) << endl;
    cout << "最短路径为：";
    auto routes = get<1>(result);
    for (int i = 0; i < routes.size() - 1; i++) {
        cout << routes[i] + 1 << " --> ";
    }
    cout << routes[routes.size() - 1] + 1 << endl;
    system("pause");
}

int main() {
    showMenu();
    char ch;
    while (ch = getchar()) {
        cls();
        if (ch == '1') {
            showMap();
            pause();
        } else if (ch == '2') {
            queryPath();
        } else if (ch == '3') {
            queryScene();
        } else if (ch == '4') {
            updateScene();
        } else if (ch == '0') {
            bye();
            pause();
            return 0;
        } else {
            showMenu();
        }
    }
    return 0;
}
