#include <queue>
#include <vector>
#include "point.cpp"

using namespace std;

void getUserInput(int userMoves[][2]);
void knight_moves(int userMoves[][2], vector<point>& result);
bool isValidPoint(int x, int y);

const int SIZE_OF_BOARD = 8;

int main(){
    int userMoves[2][2];
    vector<point> result;
    getUserInput(userMoves);
    knight_moves(userMoves, result);
    for (int i = 0; i < result[0].prev.size(); ++i) {
        cout << result[0].prev[i] << endl;
    }
}

void getUserInput(int userMoves[][2]){
    //Get user input - start coordinate
    int startRow, startCol;
    cout << "Enter the current Knight’s location: ";
    cin >> startRow >> startCol;
    while(startRow < 0 || startRow > 8){
        cout << "Invalid value for startX! Please re-enter: ";
        cin >> startRow;
    }
    while(startCol < 0 || startCol > 8){
        cout << "Invalid value for startY! Please re-enter: ";
        cin >> startCol;
    }
    //Get user input - end coordinate
    int endRow, endCol;
    cout << "Enter the destination location: ";
    cin >> endRow >> endCol;

    while(endRow < 0 || endRow > 8){
        cout << "Invalid value for endX! Please re-enter: ";
        cin >> endRow;
    }
    while(endCol < 0 || endCol > 8){
        cout << "Invalid value for endY! Please re-enter: ";
        cin >> endCol;
    }

    userMoves[0][0] = startRow;
    userMoves[0][1] = startCol;
    userMoves[1][0] = endRow;
    userMoves[1][1] = endCol;


}

bool isValidPoint(int x, int y){
    bool valid = (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
    return valid;
}


void knight_moves(int userMoves[][2], vector<point>& result) {
    //Initialize variables
    //available movement for knight in x and y
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};

    int startRow = userMoves[0][0], startCol = userMoves[0][1];
    int endRow = userMoves[1][0], endCol = userMoves[1][1];

    point startPoint(startRow, startCol);
    point endPoint(endRow, endCol);

    bool visited[SIZE_OF_BOARD][SIZE_OF_BOARD];
    queue<point> q;

    //Initialize the visited matrix
    for (int i = 0; i < SIZE_OF_BOARD; ++i) {
        for (int j = 0; j < SIZE_OF_BOARD; ++j) {
            visited[i][j] = false;
        }
    }

    visited[startRow][startCol] = true;
    q.push(startPoint);

    //Body of BFS
    while (!q.empty()) {
        point temp = q.front();
        q.pop();
        //check whether this is the destination
        if (temp == endPoint) {
            temp.prev.push_back(endPoint);
            result.push_back(temp);
            //Display result
            cout << "You made it in "<< temp.prev.size() - 1 <<" moves from [" <<
                 startRow << ", " << startCol << "] to ["
                 << endRow << ", " << endCol << "]! Here is your path:  " << endl;
            return;
        }

        for (int i = 0; i < SIZE_OF_BOARD; ++i) {
            //Go through all the possible points in the graph
            int tryRow = temp.getRow() + dx[i];
            int tryCol = temp.getCol() + dy[i];
            if (isValidPoint(tryRow, tryCol) && !visited[tryRow][tryCol]) {
                visited[tryRow][tryCol] = true;
                //New Point
                point validPoint(tryRow, tryCol);
                for (int j = 0; j < temp.prev.size(); ++j) {
                    validPoint.prev.push_back(temp.prev[j]);
                }
                validPoint.prev.push_back(temp);
                q.push(validPoint);
            }

        }
    }



}
