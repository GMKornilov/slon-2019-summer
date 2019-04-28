#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;

pair<int, int> neigh[4] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

signed main(){
    freopen("puddle.in", "r", stdin);
    freopen("puddle.out", "w", stdout);

    int n = 20, m = 30;
    int d[n][m], len[n][m];
    pair<int, int> p[n][m];
    bool used[n][m];
    char field[n][m];

    for(int i = 0; i < n; i++){
        string temp;
        getline(cin, temp);
        for(int j = 0; j < m; j++){
            d[i][j] = INF;
            len[i][j] = INF;
            used[i][j] = false;
            p[i][j] = {-1, -1};
            field[i][j] = temp[j];
        }
    }

    d[0][0] = 0;
    len[0][0] = 1;

    while(true){
        pair<int, int> cur = {-1, -1};
        int minn = INF;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!used[i][j] && field[i][j] != '#' && minn > d[i][j]){
                    minn = d[i][j];
                    cur = {i, j};
                }
            }
        }
        if(minn == INF){
            break;
        }

        int x = cur.first;
        int y = cur.second;
        used[x][y] = true;

        for(int i = 0; i < 4; i++){
            int xx = neigh[i].first;
            int yy = neigh[i].second;
            if(x + xx < 0 || x + xx >= n || y + yy < 0 || y + yy >= m){
                continue;
            }
            if(field[x + xx][y + yy] == '#'){
                continue;
            }

            if(d[x + xx][y + yy] > d[x][y] + (field[x + xx][y + yy] == '@')){
                d[x + xx][y + yy] = d[x][y] + (field[x + xx][y + yy] == '@');
                p[x + xx][y + yy] = {x, y};
                len[x + xx][y + yy] = len[x][y] + 1;
            }
            else if(d[x + xx][y + yy] == d[x][y] + (field[x + xx][y + yy] == '@') && len[x + xx][y + yy] >= len[x][y] + 1){
                d[x + xx][y + yy] = d[x][y] + (field[x + xx][y + yy] == '@');
                p[x + xx][y + yy] = {x, y};
                len[x + xx][y + yy] = len[x][y] + 1;
            }
        }
    }

    pair<int, int> cur = {n - 1, m - 1};
    while(cur.first != 0 || cur.second != 0){
        if(field[cur.first][cur.second] == '@'){
            field[cur.first][cur.second] = '*';
        }
        else{
            field[cur.first][cur.second] = '.';
        }
        pair<int, int> temp = p[cur.first][cur.second];
        cur = temp;
    }
    if(field[cur.first][cur.second] == '@'){
        field[cur.first][cur.second] = '*';
    }
    else{
        field[cur.first][cur.second] = '.';
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << field[i][j];
        }
        cout << '\n';
    }
    cout << len[n - 1][m - 1] << " " << d[n - 1][m - 1];
}
