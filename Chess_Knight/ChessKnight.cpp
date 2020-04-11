/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * AVL.cpp: This program is to knight shortest path.
*/


#include <queue>
#include "point.h"

using namespace std;

void getUserInput(int userMoves[][2]);
vector<point> knight_moves(int userMoves[][2]);
bool isValidPoint(int x, int y);

const int SIZE_OF_BOARD = 8;

int main(){
    int userMoves[2][2];
    getUserInput(userMoves);
    vector<point> result = knight_moves(userMoves);

    int startRow = userMoves[0][0], startCol = userMoves[0][1];
    int endRow = userMoves[1][0], endCol = userMoves[1][1];

    //Display result
    cout << "You made it in "<< result.size() - 1 <<" moves from [" <<
         startRow << ", " << startCol << "] to ["
         << endRow << ", " << endCol << "]! Here is your path:  " << endl;

    //Display coordinates
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
}

/**
 * Get user's input
 * @param userMoves, pass by reference - an array contains the start and goal coordinates
 */
void getUserInput(int userMoves[][2]){
    //Get user input - start coordinate
    int startRow, startCol;
    cout << "Enter the current Knight’s location: ";
    cin >> startRow >> startCol;
    while(startRow < 0 || startRow > 7){
        cout << "Invalid value for startX! Please re-enter: ";
        cin >> startRow;
    }
    while(startCol < 0 || startCol > 7){
        cout << "Invalid value for startY! Please re-enter: ";
        cin >> startCol;
    }
    //Get user input - end coordinate
    int endRow, endCol;
    cout << "Enter the destination location: ";
    cin >> endRow >> endCol;

    while(endRow < 0 || endRow > 7){
        cout << "Invalid value for endX! Please re-enter: ";
        cin >> endRow;
    }
    while(endCol < 0 || endCol > 7){
        cout << "Invalid value for endY! Please re-enter: ";
        cin >> endCol;
    }

    userMoves[0][0] = startRow;
    userMoves[0][1] = startCol;
    userMoves[1][0] = endRow;
    userMoves[1][1] = endCol;

}

/**
 * Check whether the input coordinate is valid or not
 * @param x
 * @param y
 * @return true - valid, false - invalid
 */
bool isValidPoint(int x, int y){
    bool valid = (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
    return valid;
}


/**
 * Major function
 * @param userMoves, user's input
 * @return a vector of points
 */
vector<point> knight_moves(int userMoves[][2]) {
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
            return temp.prev;
        }

        for (int i = 0; i < SIZE_OF_BOARD; ++i) {
            //Go through all the possible points in the graph
            int tryRow = temp.getRow() + dx[i];
            int tryCol = temp.getCol() + dy[i];
            if (isValidPoint(tryRow, tryCol) && !visited[tryRow][tryCol]) {
                visited[tryRow][tryCol] = true;
                //New Point
                point validPoint(tryRow, tryCol);
                //Copy all the previous path into the new cell
                for (int j = 0; j < temp.prev.size(); ++j) {
                    validPoint.prev.push_back(temp.prev[j]);
                }
                //Copy the current cell
                validPoint.prev.push_back(temp);
                q.push(validPoint);
            }

        }
    }

    return startPoint.prev;
}
