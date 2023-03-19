#include <bits/stdc++.h>
using namespace std;

int N;
int maze[25][25];

struct Board
{
    int s11;
    int s12;
    int s13;
    int s21;
    int s22;
    int s23;
    int s31;
    int s32;
    int s33;
};

unordered_set<int> done;
unordered_set<int> winningstates;
vector<int> possmoves[19];

void generate_graph(int i, int j, int m)
{
    if (done.count(625 * m + 25 * i + j))
    {
        return;
    }
    done.insert(625 * m + 25 * i + j);
    if (maze[i][j] == -2)
        return;
    if (maze[i][j] >= 0)
    {
        possmoves[m].push_back(maze[i][j]);
        m = maze[i][j];
    }
    generate_graph(i + 1, j, m);
    generate_graph(i - 1, j, m);
    generate_graph(i, j + 1, m);
    generate_graph(i, j - 1, m);
}

void fromState(int state, Board *board)
{
    board->s11 = state % 3;
    state /= 3;
    board->s12 = state % 3;
    state /= 3;
    board->s13 = state % 3;
    state /= 3;
    board->s21 = state % 3;
    state /= 3;
    board->s22 = state % 3;
    state /= 3;
    board->s23 = state % 3;
    state /= 3;
    board->s31 = state % 3;
    state /= 3;
    board->s32 = state % 3;
    state /= 3;
    board->s33 = state % 3;
    state /= 3;
}

int toState(Board board)
{
    return board.s11 + 3 * board.s12 + 9 * board.s13 + 27 * board.s21 + 81 * board.s22 + 243 * board.s23 + 729 * board.s31 + 2187 * board.s32 + 6561 * board.s33;
}

bool winning(int state)
{
    Board board;
    fromState(state, &board);
    return (board.s11 == 1 && board.s12 == 2 && board.s13 == 2) ||
           (board.s21 == 1 && board.s22 == 2 && board.s23 == 2) ||
           (board.s31 == 1 && board.s32 == 2 && board.s33 == 2) ||
           (board.s11 == 1 && board.s21 == 2 && board.s31 == 2) ||
           (board.s12 == 1 && board.s22 == 2 && board.s32 == 2) ||
           (board.s13 == 1 && board.s23 == 2 && board.s33 == 2) ||
           (board.s11 == 1 && board.s22 == 2 && board.s33 == 2) ||
           (board.s31 == 1 && board.s22 == 2 && board.s13 == 2) ||
           (board.s11 == 2 && board.s12 == 2 && board.s13 == 1) ||
           (board.s21 == 2 && board.s22 == 2 && board.s23 == 1) ||
           (board.s31 == 2 && board.s32 == 2 && board.s33 == 1) ||
           (board.s11 == 2 && board.s21 == 2 && board.s31 == 1) ||
           (board.s12 == 2 && board.s22 == 2 && board.s32 == 1) ||
           (board.s13 == 2 && board.s23 == 2 && board.s33 == 1) ||
           (board.s11 == 2 && board.s22 == 2 && board.s33 == 1) ||
           (board.s31 == 2 && board.s22 == 2 && board.s13 == 1);
}
int applyMoveToState(int move, int state)
{
    Board board;
    fromState(state, &board);
    switch (move)
    {
    default:
        return state;
    case 1:
        if (board.s11 == 0)
            board.s11 = 1;
        break;
    case 2:
        if (board.s12 == 0)
            board.s12 = 1;
        break;
    case 3:
        if (board.s13 == 0)
            board.s13 = 1;
        break;
    case 4:
        if (board.s21 == 0)
            board.s21 = 1;
        break;
    case 5:
        if (board.s22 == 0)
            board.s22 = 1;
        break;
    case 6:
        if (board.s23 == 0)
            board.s23 = 1;
        break;
    case 7:
        if (board.s31 == 0)
            board.s31 = 1;
        break;
    case 8:
        if (board.s32 == 0)
            board.s32 = 1;
        break;
    case 9:
        if (board.s33 == 0)
            board.s33 = 1;
        break;
    case 10:
        if (board.s11 == 0)
            board.s11 = 2;
        break;
    case 11:
        if (board.s12 == 0)
            board.s12 = 2;
        break;
    case 12:
        if (board.s13 == 0)
            board.s13 = 2;
        break;
    case 13:
        if (board.s21 == 0)
            board.s21 = 2;
        break;
    case 14:
        if (board.s22 == 0)
            board.s22 = 2;
        break;
    case 15:
        if (board.s23 == 0)
            board.s23 = 2;
        break;
    case 16:
        if (board.s31 == 0)
            board.s31 = 2;
        break;
    case 17:
        if (board.s32 == 0)
            board.s32 = 2;
        break;
    case 18:
        if (board.s33 == 0)
            board.s33 = 2;
        break;
    }
    return toState(board);
}

void printState(int state)
{
    Board board;
    fromState(state, &board);
    cout << board.s11 << " " << board.s12 << " " << board.s13 << endl;
    cout << board.s21 << " " << board.s22 << " " << board.s23 << endl;
    cout << board.s31 << " " << board.s32 << " " << board.s33 << endl;
}
void exploreAllGames(int state, int lastmove)
{
    if (done.count(19 * state + lastmove))
        return;

    if (winning(state))
    {
        winningstates.insert(state);
        return;
    }
    done.insert(19 * state + lastmove);
    for (int i = 0; i < possmoves[lastmove].size(); i++)
    {
        // printState(applyMoveToState(possmoves[lastmove][i], state));
        exploreAllGames(applyMoveToState(possmoves[lastmove][i], state), possmoves[lastmove][i]);
    }
}

int main()
{
    // freopen("in.in", "r", stdin);
    int si, sj;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string line;
        cin >> line;
        for (int j = 0; j < N; j += 1)
        {
            char c1 = line[3 * j], c2 = line[3 * j + 1], c3 = line[3 * j + 2];
            int mi = c2 - '1';
            int mj = c3 - '1';
            if (c1 == '#')
            {
                maze[i][j] = -2;
            }
            else if (c1 == '.')
            {
                maze[i][j] = -1;
            }
            else if (c1 == 'M')
            {
                maze[i][j] = mi * 3 + mj + 1;
                si = i, sj = j;
            }
            else if (c1 == 'O')
            {
                maze[i][j] = 9 + mi * 3 + mj + 1;
                si = i, sj = j;
            }
            else
            {
                maze[i][j] = 0;
            }
        }
    }
    generate_graph(si, sj, maze[si][sj]);
    /*
    for (int i = 0; i < 19; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < possmoves[i].size(); j++)
        {
            cout << possmoves[i][j] << " ";
        }
        cout << endl;
    }*/
    done.clear();
    exploreAllGames(0, 0);
    cout << winningstates.size() << endl;
}