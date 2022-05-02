#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

const int N = 20;
int WALL = 9999;

void display(vector<pair<int, int>> wave, int **map) {
    for (vector<pair<int, int> >::iterator i = wave.begin(); i != wave.end(); ++i)
    {
        map[i->first][i->second] = -100;
    }
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == WALL) {
                cout << '*';
            } else if (map[i][j] == -100) {
                cout << "@";
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void create_map(int ** map) {
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(rand() % 8 == 0) {
                map[i][j] = WALL;
            }else {
                map[i][j] = -1;
            }
        }
    }
    for (int i = 0; i < N; ++i)
    {
        map[i][0] = WALL;
        map[0][i] = WALL;
        map[i][N - 1] = WALL;
        map[N - 1][i] = WALL;
    }
}

vector<pair<int, int> > get_path(int originX, int originY, int targetX, int targetY, int ** map) {
    map[targetX][targetY] = -1;
    vector<pair<int, int> > oldWave;
    vector<pair<int, int> > wave;
    oldWave.push_back(pair<int, int>(originX, originY));
    int nstep = 0;
    map[originX][originY] = nstep;
    const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
    const int dy[] = {-1, 0, 1, 0, -1, 1, -1, 1};
    bool find = true;
    while (oldWave.size() > 0 && find) {
        ++nstep;
        wave.clear();
        for (vector<pair<int, int> >::iterator i = oldWave.begin(); i != oldWave.end(); ++i) {
            for (int d = 0; d < 8; ++d) {
                int nx = i->first + dx[d];
                int ny = i->second + dy[d];
                if (map[nx][ny] == -1) {
                    wave.push_back(pair<int, int>(nx, ny));
                    map[nx][ny] = nstep;
                    if (nx == targetX && ny == targetY) {
                        find = false;
                        break;
                    }
                }
            }
            if (!find) break;
        }
        oldWave = wave;
    }
    wave.clear();
    wave.push_back(pair<int, int>(targetX, targetY));
    while (map[targetX][targetY] != 0) {
        for (int d = 0; d < 8; ++d) {
            int nx = targetX + dx[d];
            int ny = targetY + dy[d];
            if (map[targetX][targetY] - 1 == map[nx][ny]) {
                targetX = nx;
                targetY = ny;
                wave.push_back(pair<int, int>(targetX, targetY));
                break;
            }
        }
    }
    return wave;
}

int main() {
    const int ESCAPE = 27;
    int ** map = new int *[N];
    for (int i = 0; i < N; i++) {
        map[i] = new int[N];
    }
    while(true) {
        system("cls");
        create_map(map);
        vector<pair<int, int>> path = get_path(1, 1, 5, 5, map);
        display(path, map);
        if (getch() == ESCAPE) {
            break;
        }
    }
    for(int i = 0; i < N; i++) {
        delete []map[i];
    }
    delete []map;
}