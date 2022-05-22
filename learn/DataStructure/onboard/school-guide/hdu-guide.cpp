
#include "graph.h"

void showMap() {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "-                                                                      -" << endl;
    cout << "-          ������������������������������ 9���ȼ��Ω���������������������������                     -" << endl;
    cout << "-          ��        750                 650      ��                     -" << endl;
    cout << "-      450 ��                                     ��500                  -" << endl;
    cout << "-          ��                                     ��                     -" << endl;
    cout << "-          ��        850                750       ��  450                -" << endl;
    cout << "-      2�޵����ǩ����������������������������������ש������������������������������ߩ��������������� 6��Է���   -" << endl;
    cout << "-          ��                  250��                          200��       -" << endl;
    cout << "-          ��                     ��           900               ��       -" << endl;
    cout << "-          ��                 8��ʡ���쩥�������������������������������������� 7������ѧ   -" << endl;
    cout << "-          ��                     ��                             ��       -" << endl;
    cout << "-          �� 800                 �� 300                      400��       -" << endl;
    cout << "-          ��                     ��                             ��       -" << endl;
    cout << "-          ��                 4�麣���                         ��       -" << endl;
    cout << "-          ��        1050         ��150          1400        5��ͤ����   -" << endl;
    cout << "-        �����ߩ������������������������������������������贈�����������������������������������������������ש�������        -" << endl;
    cout << "-     10�����޶�                 �� 250       1200         ��  150       -" << endl;
    cout << "-                                ��                    3�ź���Ӱ        -" << endl;
    cout << "-                            1��������                                 -" << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

void showMenu() {
    cout << "                   ��-----��---------��---------��-----��" << endl;
    cout << "                               ���絼��ϵͳ              " << endl;
    cout << "                   ��                                  ��" << endl;
    cout << "                               1   ����һ��              " << endl;
    cout << "                   ��          2   ��ѯ·��            ��" << endl;
    cout << "                               3   ��ѯ����              " << endl;
    cout << "                   ��          4   �޸���Ϣ            ��" << endl;
    cout << "                               0   �˳�ϵͳ              " << endl;
    cout << "                   ��                                  ��" << endl;
    cout << "                              ����ʦ����ӭ��             " << endl;
    cout << "                   ��-----��---------��---------��-----��" << endl;
    cout << endl;
    cout << endl;
    cout << "��ѡ���������";
}

void bye() {
    cout << "                   ��-----��---------��---------��-----��" << endl;
    cout << endl;
    cout << "                   ��            ��л����ʹ�ã�        ��" << endl;
    cout << endl;
    cout << "                   ��-----��---------��---------��-----��" << endl;
    cout << endl;
}

void cls() {
    system("cls");
}
void pause() {
    system("pause");
}

void showScenes() {
    cout << "������\t��������" << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < VERTEX_NUM; i++) {
        cout << "  " << scenesVex[i].id << "\t\t" << scenesVex[i].title << endl;
    }
    cout << endl;
}

void queryScene() {
    showScenes();
    int sel;
    cout << "��ѯ���(0������һ��):";
    while (cin >> sel, sel) {
        cout << "\n\t\t\t" << scenesVex[sel - 1].title << endl;
        cout << "\n\t" << scenesVex[sel - 1].intro << endl;
        cout << endl;
        cout << "��ѯ���(0������һ��):";
    }
}

void updateScene() {
    showMap();
    cout << "��Ҫ�޸ĵľ�����:";
    int sel;
    cin >> sel;
    sel--;
    string title, content;
    cout << endl;
    cout << "���⣺";
    cin >> title;
    cout << "���ܣ�";
    cin >> content;
    scenesVex[sel].title = title;
    scenesVex[sel].intro = content;
    cout << endl;
    cout << "�޸ĳɹ�" << endl;
    pause();
}

void queryPath() {
    showMap();
    int s, e;
    cout << "��ʼ��ţ�";
    cin >> s;
    cout << "���ޱ�ţ�";
    cin >> e;
    auto result = Dijkstra(sceneGraph, s - 1, e - 1);
    cout << "���·������Ϊ��" << get<0>(result) << endl;
    cout << "���·��Ϊ��";
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
