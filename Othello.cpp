/**
 * This program is to implement the othello game. Also an AI.
 *
 * @author Shixi Chen(Ethan)
 * @section CPSC 1160 - 01
 * @date Oct 25, 2019
 */

/**
 *                              CAUTION!!
 * Since I have used "●" and "◯" as the symbols of the disc, I am not sure
 * is it gonna cause compilation error.(I have that issue on my home
 * computer but not my laptop). If that is the case, just change the symbol in the
 * function - "displayBoard". I think it's around line 315 - 317.
 */

/**
 * Computer's features:
 *
 * Computer’s strategy is to evaluate next possible positions’
 * scores and place it to the highest-score corresponding position. The method
 * of evaluating possible coordinates is: for every single possible
 * coordinate, calculate the number of discs that user will be flipped
 * and also user’s number of available coordinates in the next round.
 * Make a ratio between number of flipped disc and the number of user
 * available positions. Also, the computer will add additional biases
 * to the corners and sides. It will also try to eliminate user’s chance of
 * getting corners by dividing a constant bias. At the end, computer
 * will pick the highest ratio, and that will be the computer’s move.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Global data field
int width = 8;
int length = 8;

char black[8][8];
char white[8][8];

bool quit = false;

//Store all the existing coordinates into the vector
vector<string> checkDuplicate;

//Store B/C existing coordinates into the vector
vector<string> blackCoordinates;
vector<string> whiteCoordinates;
//Available next steps' coordinates are stored in this array
vector<string> nextStep;


//Function prototypes
string getUserInput();
void displayBoard(char blackC[][8], char whiteC[][8], vector<string> &nextCoor);
bool isGameOver();
vector<string> generateValidCoordinates(int turns, char blackC[][8], char whiteC[][8], vector<string> &blackCoor, vector<string> &whiteCoor);
void flip(string &s, int order, char blackC[][8], char whiteC[][8], vector<string> &blackCoor, vector<string> &whiteCoor);
void displayAvailableCoordinates(vector<string> &coor);
string computerMove();
bool isValidKey(string &key);

/**
 * Print out all the elements in the vector.(linear)
 * @tparam T, type
 * @param a, vector
 */
template<typename T>
void printArray(vector<T> a) {
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

/**
 * Erase the target element in the vector
 * @tparam T, type
 * @param vector, target vector
 * @param value, the target element
 */
template<typename T>
void erase(vector<T> &vector, T const &value) {
    vector.erase(remove(begin(vector), end(vector), value), end(vector));
}

//TODO Odd index means black!
int main() {
    int passCheck = 0;
    //Set the default values before the game starts
    checkDuplicate.push_back("4d");
    black[3][4] = 'b';
    blackCoordinates.push_back("34");
    checkDuplicate.push_back("4e");
    black[4][3] = 'b';
    blackCoordinates.push_back("43");
    checkDuplicate.push_back("5d");
    white[3][3] = 'w';
    whiteCoordinates.push_back("33");
    checkDuplicate.push_back("5e");
    white[4][4] = 'w';
    whiteCoordinates.push_back("44");


    for (int i = 1; i <= 100 && !isGameOver() && !quit; i++) {
        string user;
        string computer;
        string finalCoorComputer;
        nextStep = generateValidCoordinates(i, black, white, blackCoordinates, whiteCoordinates);
        displayBoard(black, white, nextStep);
        displayAvailableCoordinates(nextStep);
        cout << "Black:  " << blackCoordinates.size() << "       White:  " << whiteCoordinates.size() << endl;
        if (i % 2 != 0) {//Odd represents black player
            //Check PASS
            if (nextStep.size() == 0) {
                cout << "PASS!" << endl;
                passCheck++;
                if (passCheck >= 2) {
                    displayBoard(black, white, nextStep);
                    cout << "Black:  " << blackCoordinates.size() << "       White:  " << whiteCoordinates.size() << endl;
                    cout << "Gameover! The winner is: ";
                    whiteCoordinates.size() > blackCoordinates.size() ? cout << "WHITE." << endl : cout << "BLACK." << endl;
                    exit(0);
                } else {
                    passCheck = 0;
                    continue;
                }
            }
            cout << "Black's turn" << endl;
            user = getUserInput();
            int first = user[0] - '1'; //zong zuo biao
            int second = user[1] - 'a'; // heng zuo biao
            string coor = to_string(first) + to_string(second); //Coordinates in index's form

            black[first][second] = 'b';
            blackCoordinates.push_back(coor);
        } else {//Even represents white player(Computer)
            cout << "Press 'y' to let computer place its disc: ";
            char y;
            cin >> y;
            //Check PASS
            if (nextStep.size() == 0) {
                cout << "PASS!" << endl;
                passCheck++;
                if (passCheck >= 2) {
                    displayBoard(black, white, nextStep);
                    cout << "Gameover! The winner is: ";
                    whiteCoordinates.size() > blackCoordinates.size() ? cout << "WHITE." << endl : cout << "BLACK." << endl;
                    exit(0);
                } else {
                    passCheck = 0;
                    continue;
                }
            }
            computer = computerMove();
            char x = (char) (computer[0] + 1);
            char y1 = (char) (computer[1] - '0' + 'a');
            cout << computer << endl;
            int x1 = computer[0] - '0';
            int y2 = computer[1] - '0';
            white[x1][y2] = 'w';
            finalCoorComputer = string(1, x) + y1;
            whiteCoordinates.push_back(computer);
            cout << "Computer's choice: " << finalCoorComputer << endl;
        }
        if (i % 2 != 0) {
            flip(user, i, black, white, blackCoordinates, whiteCoordinates);
        } else {
            flip(finalCoorComputer, 2, black, white, blackCoordinates, whiteCoordinates);
        }
    }

    //When the game is finished
    displayBoard(black, white, nextStep);
    cout << "Black:  " << blackCoordinates.size() << "       White:  " << whiteCoordinates.size() << endl;
    cout << "Gameover! The winner is: ";
    whiteCoordinates.size() > blackCoordinates.size() ? cout << "WHITE" << endl : cout << "BLACK" << endl;

    return 0;
}


/**
 * Generate computer's move
 */
string computerMove() {
    double ratio = 0;
    double previousRatio = 0;
    string finalComputerCoordinate;

    for (int i = 0; i < nextStep.size(); i++) {
        //Copy their coordinates
        vector<string> testBlackCoordinates;
        vector<string> testWhiteCoordinates;
        char testWhite[8][8];
        char testBlack[8][8];
        //Deep copy white and black array
        for (int j = 0; j < width; j++) {
            for (int x = 0; x < length; x++) {
                testBlack[j][x] = black[j][x];
                testWhite[j][x] = white[j][x];
            }
        }
        for (int k = 0; k < blackCoordinates.size(); k++) {
            testBlackCoordinates.push_back(blackCoordinates.at(k));
        }
        for (int l = 0; l < whiteCoordinates.size(); l++) {
            testWhiteCoordinates.push_back(whiteCoordinates.at(l));
        }

        int first = nextStep.at(i)[0] - '0';
        int second = nextStep.at(i)[1] - '0';
        testWhite[first][second] = 'w';

        char c1 = (char) (nextStep.at(i)[0] + 1);
        char c2 = (char) (nextStep.at(i)[1] - '0' + 'a');
        string realCoorForFlip = string(1, c1) + c2;

        testWhiteCoordinates.push_back(nextStep.at(i));

        int beforeFlip = testBlackCoordinates.size();
        flip(realCoorForFlip, 2, testBlack, testWhite, testBlackCoordinates, testWhiteCoordinates);
        vector<string> userAvailableStep = generateValidCoordinates(1, testBlack, testWhite, testBlackCoordinates,
                                                                    testWhiteCoordinates);
        bool userHasCorner = false;
        for (int m = 0; m < userAvailableStep.size(); m++) {
            int a1 = userAvailableStep.at(m)[0] - '0';
            int a2 = userAvailableStep.at(m)[1] - '0';
            userHasCorner = (a1 == 0 && a2 == 0) || (a1 == 0 && a2 == 7) || (a1 == 7 && a2 == 0) || (a1 == 7 && a2 == 7);
            if(userHasCorner) break;
        }

        int afterFlipped = testBlackCoordinates.size();
        double numberOfFlippedDis = beforeFlip - afterFlipped;
        double userAvailable = userAvailableStep.size();
        ratio = numberOfFlippedDis / userAvailable;

        bool isCorner = (first == 0 && second == 0) || (first == 0 && second == 7) || (first == 7 && second == 0) || (first == 7 && second == 7);
        bool isSide = (first == 0 && (second >= 0 && second <= 7)) || (first == 7 && (second >= 0 && second <= 7))
                      || (second == 0 && (first >= 0 && first <= 7)) || (second == 7 && (first >= 0 && first <= 7));

        if(isCorner){
            ratio *= 100;
        }else if(isSide && !isCorner){
            ratio *= 20;
        }else if(userHasCorner){
            ratio /= 1000;
        }

        //Find the largest ratio
        if (ratio > previousRatio) {
            previousRatio = ratio;
            //Store the final coordinate to the variable
            finalComputerCoordinate = nextStep.at(i);
        }
    }//For loop bracket
    return finalComputerCoordinate;
}

/**
 * Check whether the game is over.
 * @return true - the game is over || false - the game keeps going
 */
bool isGameOver() {
    bool occuoied = (whiteCoordinates.size() + blackCoordinates.size() >= width * length);
    bool noWhiteOrBlack = whiteCoordinates.size() == 0 || blackCoordinates.size() == 0;
    return occuoied || noWhiteOrBlack;
}

/**
 * Check whether the coordinate is validate
 * @param key, coordinates
 * @return true -> valid corrdinate, false -> invalid coordinate
 */
bool isValidKey(string &key) {
    bool firstPart = key[0] >= '0' && key[0] <= '7';
    bool secondPart = key[1] >= '0' && key[1] <= '7';
    bool l = key.length() == 2;
    return firstPart && secondPart && l;
}

/**
 * Display the chess board.
 * @param blackC, existing black coordinates
 * @param whiteC, existing white coordinates
 * @param nextCoor, available next-step coordinates
 */
void displayBoard(char blackC[][8], char whiteC[][8], vector<string> &nextCoor) {
    //Display the alphabets
    cout << "    ";
    for (int i = 0; i < width; i++) {
        cout << char('a' + i) << "   ";
    }
    cout << endl;

    for (int i = 1; i <= width; i++) {
        //Display the dashes
        cout << "  ";
        for (int k = 0; k < width; k++) {
            cout << "----";
        }
        cout << endl;
        cout << i << " ";
        for (int j = 1; j <= length; j++) {
            //Display the disc
            bool hasBlack = blackC[i - 1][j - 1] == 'b';
            bool hasWhite = whiteC[i - 1][j - 1] == 'w';
            string key = to_string(i - 1) + to_string(j - 1);
            bool hasNextStep = count(nextCoor.begin(), nextCoor.end(), key);
            if (hasBlack) {
                cout << "| ● ";
            } else if (hasWhite) {
                cout << "| ◯ ";
            } else if (hasNextStep) {
                cout << "| ? ";
            } else {
                cout << "|   ";//3spaces
            }

            if (j == length) {
                cout << "|";
            }
        }
        cout << endl;
        //Display the bottom dashes
        if (i == width) {
            cout << "  ";
            for (int k = 0; k < width; k++) {
                cout << "----";
            }
            cout << endl;
        }
    }
}

/**
 * Display available coordinates.
 * E.g: Your available coordinates are: 3c 3e 5c
 * @param coor, next-step available coordinates
 */
void displayAvailableCoordinates(vector<string> &coor) {
    cout << "Your available coordinates are: ";
    for (int i = 0; i < coor.size(); i++) {
        char a = char(coor[i][0] + 1);
        char b = char(coor[i][1] - '0' + 'a');
        cout << a << b << " ";
    }
    cout << endl;
}

/**
 * Get user valid input. Also check whether user's input is valid
 * or invalid, or wanna quit the game.
 * @return user's valid coordinate
 */
string getUserInput() {
    string user;
    cout << "(Enter (quit) to exit the program)" << endl;
    cout << "Please enter a coordinate: ";
    bool valid = true;
    while (valid) {
        cin >> user;
        if(user == "quit"){
            quit = true;
            break;
        }
        if (isdigit(user[0]) && isalpha(user[1])) {
            //check whether the input is in the range
            bool firstPart = user[0] >= '1' && user[0] <= '8';
            bool secondPart = user[1] >= 'a' && user[1] <= 'h';
            //Check the first and second index of user's input, and also check duplicate
            if (firstPart && secondPart) {
                //Put two chars into a string
                char a = user[0] - 1;
                char b = (char) ('0' + (user[1] - 'a'));
                string k = string(1, a) + b;
                //Check if it's an element of nextStep
                if (count(nextStep.begin(), nextStep.end(), k)) {
                    checkDuplicate.push_back(k);
                    valid = false;
                } else {
                    cout << "Invalid coordinate. ";
                    cout << "Please enter a coordinate: ";
                    continue;
                }
            } else {
                cout << "Invalid coordinate. ";
                cout << "Please enter a coordinate: ";
                continue;
            }
        } else {
            cout << "Invalid coordinate. ";
            cout << "Please enter a coordinate: ";
        }
    }//while loop
    return user;
}

/**
 * Generate valid coordinates for next round.
 * @param turns, odd means is black's term, even means is white's term
 * @param blackC, existing black coordinates
 * @param whiteC, existing white coordinates
 * @param blackCoor, existing black coordinates (in the form of vector)
 * @param whiteCoor, existing white coordinates (in the form of vector)
 * @return a vector that holds all the available coordinates for next step
 */
vector<string> generateValidCoordinates(int turns, char blackC[][8], char whiteC[][8], vector<string> &blackCoor,
                                        vector<string> &whiteCoor) {
    vector<string> result;
    if (turns % 2 != 0) {//generate black avaliable coordinates
        //Search for the all the black disc
        for (int i = 0; i < blackCoor.size(); i++) {

            //Get the coordinates of existing black disc
            int coor = stoi(blackCoor[i]);
            int shu = coor / 10;
            int heng = coor % 10;
            int countW = 0;


            //Searching horizontally -- East
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu][heng + 1] != 'w') break;
                    //Otherwise(there's white disc next to it), search for empty space
                else {
                    string key = to_string(shu) + to_string(heng + j);
                    if (whiteC[shu][heng + j] == 'w') countW++;
                    //When the place is empty
                    if (whiteC[shu][heng + j] != 'w' && blackC[shu][heng + j] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// H-East
            countW = 0;

            //Searching horizontally -- west
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu][heng - 1] != 'w') break;
                    //Otherwise(there's white disc next to it), search for empty space
                else {
                    string key = to_string(shu) + to_string(heng - j);
                    if (whiteC[shu][heng - j] == 'w') countW++;
                    //When the place is empty
                    if (whiteC[shu][heng - j] != 'w' && blackC[shu][heng - j] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// H-West

            countW = 0;


            //Searching vertically -- North
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu - 1][heng] != 'w') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (whiteC[shu - j][heng] == 'w') countW++;
                    string key = to_string(shu - j) + to_string(heng);
                    if (whiteC[shu - j][heng] != 'w' && blackC[shu - j][heng] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// V-North
            countW = 0;

            //Searching vertically -- South
            for (int j = 1; j < length; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu + 1][heng] != 'w') { break; }
                    //Otherwise(there's white disc next to it, search for empty space
                else {
                    if (whiteC[shu + j][heng] == 'w') countW++;
                    string key = to_string(shu + j) + to_string(heng);
                    if (whiteC[shu + j][heng] != 'w' && blackC[shu + j][heng] != 'b') {
                        if (countW == (j - 1) && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// V-South

            countW = 0;

            //Searching diagonally-- North West
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu - 1][heng - 1] != 'w') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (whiteC[shu - j][heng - j] == 'w') countW++;
                    string key = to_string(shu - j) + to_string(heng - j);
                    if (whiteC[shu - j][heng - j] != 'w' && blackC[shu - j][heng - j] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// North-West
            countW = 0;

            //Searching diagonally-- North East
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu - 1][heng + 1] != 'w') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (whiteC[shu - j][heng + j] == 'w') countW++;
                    string key = to_string(shu - j) + to_string(heng + j);
                    if (whiteC[shu - j][heng + j] != 'w' && blackC[shu - j][heng + j] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// North-East

            countW = 0;


            //Searching diagonally -- South West
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu + 1][heng - 1] != 'w') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (whiteC[shu + j][heng - j] == 'w') countW++;
                    string key = to_string(shu + j) + to_string(heng - j);
                    if (whiteC[shu + j][heng - j] != 'w' && blackC[shu + j][heng - j] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// South-West
            countW = 0;

            //Searching diagonally -- South East
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (whiteC[shu + 1][heng + 1] != 'w') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (whiteC[shu + j][heng + j] == 'w') countW++;
                    string key = to_string(shu + j) + to_string(heng + j);
                    if (whiteC[shu + j][heng + j] != 'w' && blackC[shu + j][heng + j] != 'b') {
                        if (countW == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// South-East
            countW = 0;


        }
    } else {//Search for white disc
        // Mechanisms are mostly same as the previous if block

        //Search for the all the white disc
        for (int i = 0; i < whiteCoor.size(); i++) {

            //Get the coordinates of existing black disc
            int coor = stoi(whiteCoor[i]);
            int shu = coor / 10;
            int heng = coor % 10;
            int countB = 0;

            //Searching horizontally -- to right
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu][heng + 1] != 'b') break;
                    //Otherwise(there's white disc next to it), search for empty space
                else {
                    string key = to_string(shu) + to_string(heng + j);
                    if (blackC[shu][heng + j] == 'b') countB++;
                    //When the place is empty
                    if (blackC[shu][heng + j] != 'b' && whiteC[shu][heng + j] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// H-Right
            countB = 0;


            //Searching horizontally -- to left
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu][heng - 1] != 'b') break;
                    //Otherwise(there's white disc next to it), search for empty space
                else {
                    string key = to_string(shu) + to_string(heng - j);
                    if (blackC[shu][heng - j] == 'b') countB++;
                    //When the place is empty
                    if (blackC[shu][heng - j] != 'b' && whiteC[shu][heng - j] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// H-Left
            countB = 0;

            //Searching vertically -- North
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu - 1][heng] != 'b') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (blackC[shu - j][heng] == 'b') countB++;
                    string key = to_string(shu - j) + to_string(heng);
                    if (blackC[shu - j][heng] != 'b' && whiteC[shu - j][heng] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// H-Right
            countB = 0;

            //Searching vertically -- South
            for (int j = 1; j < length; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu + 1][heng] != 'b') { break; }
                    //Otherwise(there's white disc next to it, search for empty space
                else {
                    if (blackC[shu + j][heng] == 'b') countB++;
                    string key = to_string(shu + j) + to_string(heng);
                    if (blackC[shu + j][heng] != 'b' && whiteC[shu + j][heng] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// South
            countB = 0;

            //Searching diagonally-- North West
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu - 1][heng - 1] != 'b') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (blackC[shu - j][heng - j] == 'b') countB++;
                    string key = to_string(shu - j) + to_string(heng - j);
                    if (blackC[shu - j][heng - j] != 'b' && whiteC[shu - j][heng - j] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// North-West
            countB = 0;

            //Searching diagonally-- North East
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu - 1][heng + 1] != 'b') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (blackC[shu - j][heng + j] == 'b') countB++;
                    string key = to_string(shu - j) + to_string(heng + j);
                    if (blackC[shu - j][heng + j] != 'b' && whiteC[shu - j][heng + j] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// North-East
            countB = 0;

            //Searching diagonally-- South West
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu + 1][heng - 1] != 'b') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (blackC[shu + j][heng - j] == 'b') countB++;
                    string key = to_string(shu + j) + to_string(heng - j);
                    if (blackC[shu + j][heng - j] != 'b' && whiteC[shu + j][heng - j] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// South-West
            countB = 0;

            //Searching diagonally-- South East
            for (int j = 1; j < width; j++) {
                //If there's non-white disc next to a black, break!
                if (blackC[shu + 1][heng + 1] != 'b') { break; }
                    //Otherwise there's white disc next to it, search for empty space
                else {
                    if (blackC[shu + j][heng + j] == 'b') countB++;
                    string key = to_string(shu + j) + to_string(heng + j);
                    if (blackC[shu + j][heng + j] != 'b' && whiteC[shu + j][heng + j] != 'w') {
                        if (countB == j - 1 && !count(result.begin(), result.end(), key) && isValidKey(key)) {
                            result.push_back(key);
                        }
                        break;
                    }
                }
            }// South-East
            countB = 0;

        }//outer for loop
    }//else block

    //Filter out invalid coordinates
    for (int i = 0; i < result.size(); i++) {
        string &element = result.at(i);
        bool firstPart = element[0] >= '0' && element[0] <= '7';
        bool secondPart = element[1] >= '0' && element[1] <= '7';
        if (!firstPart || !secondPart) {
            erase(result, element);
        }
    }
    //sort the vector
    sort(result.begin(), result.end());

    return result;
}

/**
 * According to whoes term, flip opponent's disc.
 * @param s, user's or computer's coordinates
 * @param order, odd means is black term, even means is white's term
 * @param blackC existing black coordinates
 * @param whiteC, existing white coordinates
 * @param blackCoor, existing black coordinates (in the form of vector)
 * @param whiteCoor, existing white coordinates (in the form of vector)
 */
void flip(string &s, int order, char blackC[][8], char whiteC[][8], vector<string> &blackCoor, vector<string> &whiteCoor) {
    int shu = s[0] - '1'; //zong zuo biao
    int heng = s[1] - 'a'; // heng zuo biao

    if (order % 2 != 0) {//ODD flip the white disc
        //Searching horizontally -- to right
        for (int i = 1; i < width && ((heng + i) <= 7); i++) {
            if (blackC[shu][heng + i] == 'b') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    whiteC[shu][heng + j] = '\0';
                    blackC[shu][heng + j] = 'b';
                    //Update the vector
                    string coordinateInString = to_string(shu) + to_string(heng + j);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }

                }
                break;
            } else if (whiteC[shu][heng + i] == 'w') continue;
            else break;
        }// H-Right

        //H-Left
        for (int i = 1; i < width && ((heng - i) >= 0); i++) {
            if (blackC[shu][heng - i] == 'b') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    whiteC[shu][heng - j] = '\0';
                    blackC[shu][heng - j] = 'b';
                    string coordinateInString = to_string(shu) + to_string(heng - j);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu][heng - i] == 'w') continue;
            else break;
        }

        //Verticle Upward
        for (int i = 1; i < width && ((shu - i) >= 0); i++) {
            if (blackC[shu - i][heng] == 'b') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    whiteC[shu - j][heng] = '\0';
                    blackC[shu - j][heng] = 'b';
                    string coordinateInString = to_string(shu - j) + to_string(heng);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu - i][heng] == 'w') continue;
            else break;
        }

        //Vertical Downward
        for (int i = 1; i < width && ((shu + i) <= 7); i++) {
            if (blackC[shu + i][heng] == 'b') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    whiteC[shu + j][heng] = '\0';
                    blackC[shu + j][heng] = 'b';
                    string coordinateInString = to_string(shu + j) + to_string(heng);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu + i][heng] == 'w') continue;
            else break;
        }

        //Diagnoal Direction -> South East
        for (int i = 1; i < width && ((shu + i) <= 7) && ((heng + i) <= 7); i++) {
            if (blackC[shu + i][heng + i] == 'b') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    whiteC[shu + j][heng + j] = '\0';
                    blackC[shu + j][heng + j] = 'b';
                    string coordinateInString = to_string(shu + j) + to_string(heng + j);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu + i][heng + i] == 'w') continue;
            else break;
        }

        //Diagnoal Direction -> North West
        for (int i = 1; i < width && ((shu - i) >= 0) && ((heng - i) >= 0); i++) {
            if (blackC[shu - i][heng - i] == 'b') {
                //Flip the white disc
                for (int j = 0; j < i; j++) {
                    whiteC[shu - j][heng - j] = '\0';
                    blackC[shu - j][heng - j] = 'b';
                    string coordinateInString = to_string(shu - j) + to_string(heng - j);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu - i][heng - i] == 'w') continue;
            else break;
        }

        //Diagnoal Direction -> North East
        for (int i = 1; i < width && ((shu - i) >= 0) && ((heng + i) <= 7); i++) {
            if (blackC[shu - i][heng + i] == 'b') {
                //Flip the white disc
                for (int j = 0; j < i; j++) {
                    whiteC[shu - j][heng + j] = '\0';
                    blackC[shu - j][heng + j] = 'b';
                    string coordinateInString = to_string(shu - j) + to_string(heng + j);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu - i][heng + i] == 'w') continue;
            else break;
        }

        //Diagnoal Direction -> South West
        for (int i = 1; i < width && ((shu + i) <= 7) && ((heng - i) >= 0); i++) {
            if (blackC[shu + i][heng - i] == 'b') {
                //Flip the white disc
                for (int j = 0; j < i; j++) {
                    whiteC[shu + j][heng - j] = '\0';
                    blackC[shu + j][heng - j] = 'b';
                    string coordinateInString = to_string(shu + j) + to_string(heng - j);
                    if (!count(blackCoor.begin(), blackCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        blackCoor.push_back(coordinateInString);
                        erase(whiteCoor, coordinateInString);
                    }
                }
                break;
            } else if (whiteC[shu + i][heng - i] == 'w') continue;
            else break;
        }


    } else {//flip the black disc

        //H-right
        for (int i = 1; i < width && ((heng + i) <= 7); i++) {
            if (whiteC[shu][heng + i] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu][heng + j] = '\0';
                    whiteC[shu][heng + j] = 'w';
                    string coordinateInString = to_string(shu) + to_string(heng + j);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu][heng + i] == 'b') continue;
            else break;
        }// H-Right

        //H-Left
        for (int i = 1; i < width && ((heng - i) >= 0); i++) {
            if (whiteC[shu][heng - i] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu][heng - j] = '\0';
                    whiteC[shu][heng - j] = 'w';
                    string coordinateInString = to_string(shu) + to_string(heng - j);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu][heng - i] == 'b') continue;
            else break;
        }

        //Vertical Upward
        for (int i = 1; i < width && ((shu - i) >= 0); i++) {
            if (whiteC[shu - i][heng] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu - j][heng] = '\0';
                    whiteC[shu - j][heng] = 'w';
                    string coordinateInString = to_string(shu - j) + to_string(heng);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu - i][heng] == 'b') continue;
            else break;
        }

        //Vertical Downward
        for (int i = 1; i < width && ((shu + i) <= 7); i++) {
            if (whiteC[shu + i][heng] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu + j][heng] = '\0';
                    whiteC[shu + j][heng] = 'w';
                    string coordinateInString = to_string(shu + j) + to_string(heng);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu + i][heng] == 'b') continue;
            else break;
        }

        //TODO Changed - from j = 0 -> j = 1 (check is it work?)  从这往下都改了
        //Diagnoal Direction -> South East
        for (int i = 1; i < width && ((shu + i) <= 7) && ((heng + i) <= 7); i++) {
            if (whiteC[shu + i][heng + i] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu + j][heng + j] = '\0';
                    whiteC[shu + j][heng + j] = 'w';
                    string coordinateInString = to_string(shu + j) + to_string(heng + j);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu + i][heng + i] == 'b') continue;
            else break;
        }

        //Diagnoal Direction -> North West
        for (int i = 1; i < width && ((shu - i) >= 0) && ((heng - i) >= 0); i++) {
            if (whiteC[shu - i][heng - i] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu - j][heng - j] = '\0';
                    whiteC[shu - j][heng - j] = 'w';
                    string coordinateInString = to_string(shu - j) + to_string(heng - j);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu - i][heng - i] == 'b') continue;
            else break;
        }


        //Diagonal Direction -> North East
        for (int i = 1; i < width && ((shu - i) >= 0) && ((heng + i) <= 7); i++) {
            if (whiteC[shu - i][heng + i] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu - j][heng + j] = '\0';
                    whiteC[shu - j][heng + j] = 'w';
                    string coordinateInString = to_string(shu - j) + to_string(heng + j);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu - i][heng + i] == 'b') continue;
            else break;
        }

        //Diagonal Direction -> South West
        for (int i = 1; i < width && ((shu + i) <= 7) && ((heng - i) >= 0); i++) {
            if (whiteC[shu + i][heng - i] == 'w') {
                //Flip the white disc
                for (int j = 1; j <= i; j++) {
                    blackC[shu + j][heng - j] = '\0';
                    whiteC[shu + j][heng - j] = 'w';
                    string coordinateInString = to_string(shu + j) + to_string(heng - j);
                    if (!count(whiteCoor.begin(), whiteCoor.end(), coordinateInString) &&
                        isValidKey(coordinateInString)) {
                        whiteCoor.push_back(coordinateInString);
                        erase(blackCoor, coordinateInString);
                    }
                }
                break;
            } else if (blackC[shu + i][heng - i] == 'b') continue;
            else break;
        }

    }
}