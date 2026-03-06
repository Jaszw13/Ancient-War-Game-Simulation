// === Region: Project Declaration ===
//
//  COMP2011 Fall 2024
//  PA1: Ancient War Game Simulation
//
//  Your name: SU, Ziwen
//  Your ITSC email: zsuat@connect.ust.hk
//
//  Note: Generative AI is NOT allowed in completing your lab exercises or programming assignments
//  Reference: https://course.cse.ust.hk/comp2011/web/code.html
//
//  Declaration:
//  I declare that I am not involved in plagiarism
//  I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks.
//
//  Project TA: Peter CHUNG (cspeter@cse.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code blocks in a public discussion forum (e.g., Piazza) may cause plagiarism issues
//  Usually, you will get the quickest response via a direct email.
//
//  Possible usage of the program:
//
//  Method 1: You can display the output on the terminal
//
//  Mac/Linux: ./pa1 < testcase/inputX.txt
//  Windows  :  Get-Content testcase/inputX.txt | ./pa1
//
//  Method 2: You can redirect the output to a text file, and then open the text file for checking
//
//  Mac/Linux: ./pa1 < testcase/inputX.txt > myOutputX.txt
//  Winodws  :  Get-Content testcase/inputX.txt | ./pa1 > myOutputX.txt
//
// =====================================

// === Region: Headers ===
// iostream and cstring are included.
// Do not include extra header files
// =======================
#include <iostream>
#include <cstring>
using namespace std;

// === Region: Constants ===
// Useful constants are defined for this project assignment
// =======================
const int MAX_ROWS = 20;
const int MAX_COLS = 30;
const int MAX_NUM_WARRIORS = 26; // Note: Warriors are named from A..Z
const char CHAR_EMPTY = '.';
const char CHAR_END_INPUT = '!';
const int MAX_DIRECTION_TEXT_LENGTH = 10 + 1; // +1 for the NULL character
const int MAX_ACTION_TEXT_LENGTH = 10 + 1;    // +1 for the NULL character

enum DirectionType
{
    DIRECTION_ERROR = 0,
    DIRECTION_EAST,
    DIRECTION_SOUTH,
    DIRECTION_WEST,
    DIRECTION_NORTH,
    DIRECTION_NORTH_EAST,
    DIRECTION_SOUTH_EAST,
    DIRECTION_SOUTH_WEST,
    DIRECTION_NORTH_WEST
};

enum ActionType
{
    ACTION_ERROR = 0,
    ACTION_MOVE,
    ACTION_FIGHT,
    ACTION_SHOOT
};
enum StatusMoveAction
{
    STATUS_ACTION_MOVE_NOT_IMPLMENTED = 0,
    STATUS_ACTION_MOVE_SUCCESS,
    STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY,
    STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH
};
enum StatusFightAction
{
    STATUS_ACTION_FIGHT_NOT_IMPLEMENTED = 0,
    STATUS_ACTION_FIGHT_SUCCESS,
    STATUS_ACTION_FIGHT_FAIL
};
enum StatusShootAction
{
    STATUS_ACTION_SHOOT_NOT_IMPLEMENTED = 0,
    STATUS_ACTION_SHOOT_SUCCESS,
    STATUS_ACTION_SHOOT_FAIL
};

const char DIRECTION_TEXT_ERROR[] = "wrong direction";
const char DIRECTION_TEXT_EAST[] = "east";
const char DIRECTION_TEXT_WEST[] = "west";
const char DIRECTION_TEXT_SOUTH[] = "south";
const char DIRECTION_TEXT_NORTH[] = "north";
const char DIRECTION_TEXT_NORTHEAST[] = "northeast";
const char DIRECTION_TEXT_NORTHWEST[] = "northwest";
const char DIRECTION_TEXT_SOUTHEAST[] = "southeast";
const char DIRECTION_TEXT_SOUTHWEST[] = "southwest";

const char ACTION_MOVE_TEXT[] = "moves";
const char ACTION_FIGHT_TEXT[] = "fights";
const char ACTION_SHOOT_TEXT[] = "shoots";

int letterToArrayIndex(char letter)
{
    return int(letter - 'A');
}

char indexToLetter(int index)
{
    return char(index + 'A');
}

ActionType convertToActionType(const char actionText[MAX_ACTION_TEXT_LENGTH])
{

    // In this game, only 3 possible values
    if (strcmp(actionText, ACTION_MOVE_TEXT) == 0)
    {
        return ACTION_MOVE;
    }
    else if (strcmp(actionText, ACTION_FIGHT_TEXT) == 0)
    {
        return ACTION_FIGHT;
    }
    else if (strcmp(actionText, ACTION_SHOOT_TEXT) == 0)
    {
        return ACTION_SHOOT;
    }
    return ACTION_ERROR;
}

DirectionType convertDirectionText(const char text[MAX_DIRECTION_TEXT_LENGTH])
{
    if (strcmp(text, DIRECTION_TEXT_EAST) == 0)
    {
        return DIRECTION_EAST;
    }
    if (strcmp(text, DIRECTION_TEXT_SOUTH) == 0)
    {
        return DIRECTION_SOUTH;
    }
    if (strcmp(text, DIRECTION_TEXT_WEST) == 0)
    {
        return DIRECTION_WEST;
    }
    if (strcmp(text, DIRECTION_TEXT_NORTH) == 0)
    {
        return DIRECTION_NORTH;
    }
    if (strcmp(text, DIRECTION_TEXT_NORTHEAST) == 0)
    {
        return DIRECTION_NORTH_EAST;
    }
    if (strcmp(text, DIRECTION_TEXT_NORTHWEST) == 0)
    {
        return DIRECTION_NORTH_WEST;
    }
    if (strcmp(text, DIRECTION_TEXT_SOUTHEAST) == 0)
    {
        return DIRECTION_SOUTH_EAST;
    }
    if (strcmp(text, DIRECTION_TEXT_SOUTHWEST) == 0)
    {
        return DIRECTION_SOUTH_WEST;
    }
    return DIRECTION_ERROR;
}

const char *convertDirectionText(DirectionType direction)
{
    if (direction == DIRECTION_EAST)
        return DIRECTION_TEXT_EAST;
    if (direction == DIRECTION_SOUTH)
        return DIRECTION_TEXT_SOUTH;
    if (direction == DIRECTION_WEST)
        return DIRECTION_TEXT_WEST;
    if (direction == DIRECTION_NORTH)
        return DIRECTION_TEXT_NORTH;
    if (direction == DIRECTION_NORTH_EAST)
        return DIRECTION_TEXT_NORTHEAST;
    if (direction == DIRECTION_NORTH_WEST)
        return DIRECTION_TEXT_NORTHWEST;
    if (direction == DIRECTION_SOUTH_EAST)
        return DIRECTION_TEXT_SOUTHEAST;
    if (direction == DIRECTION_SOUTH_WEST)
        return DIRECTION_TEXT_SOUTHWEST;
    return DIRECTION_TEXT_ERROR;
}

bool isValidMoveDirection(DirectionType d)
{
    return d == DIRECTION_EAST || d == DIRECTION_WEST || d == DIRECTION_SOUTH || d == DIRECTION_NORTH;
}
bool isValidFightDirection(DirectionType d)
{
    return d == DIRECTION_EAST || d == DIRECTION_WEST || d == DIRECTION_SOUTH || d == DIRECTION_NORTH;
}

bool isValidShootDirection(DirectionType d)
{
    return d == DIRECTION_EAST || d == DIRECTION_WEST || d == DIRECTION_SOUTH || d == DIRECTION_NORTH || d == DIRECTION_NORTH_EAST || d == DIRECTION_NORTH_WEST || d == DIRECTION_SOUTH_EAST || d == DIRECTION_SOUTH_WEST;
}

void initializeMap(char map[MAX_ROWS][MAX_COLS], int numRows, int numCols)
{
    int r, c;
    for (r = 0; r < numRows; r++)
        for (c = 0; c < numCols; c++)
            map[r][c] = CHAR_EMPTY;
}

void initializePoints(int healthPoints[MAX_NUM_WARRIORS], int fightPoints[MAX_NUM_WARRIORS], int shootPoints[MAX_NUM_WARRIORS])
{
    for (int i = 0; i < MAX_NUM_WARRIORS; i++)
        healthPoints[i] = fightPoints[i] = shootPoints[i] = 0;
}

void readInputPoints(int healthPoints[MAX_NUM_WARRIORS], int fightPoints[MAX_NUM_WARRIORS], int shootPoints[MAX_NUM_WARRIORS])
{
    int num, hp, fp, sp, i, index;
    char letter;
    initializePoints(healthPoints, fightPoints, shootPoints);
    // Read letters and health points
    cin >> num;
    for (i = 0; i < num; i++)
    {
        cin >> letter >> hp >> fp >> sp;
        index = letterToArrayIndex(letter);
        healthPoints[index] = hp;
        fightPoints[index] = fp;
        shootPoints[index] = sp;
    }
}

void readInputMap(char map[MAX_ROWS][MAX_COLS], int &mapRows, int &mapCols)
{
    int r, c;
    char line[MAX_COLS + 1]; // character array to store each line

    // Read the game map
    cin >> mapRows >> mapCols;
    initializeMap(map, mapRows, mapCols);

    cin.ignore(); // ignore the end line character in this line
    for (r = 0; r < mapRows; r++)
    {
        cin.getline(line, MAX_COLS + 1);
        for (c = 0; c < mapCols; c++)
            map[r][c] = line[c];
    }
}

void displayMap(const char map[MAX_ROWS][MAX_COLS], int mapRows, int mapCols)
{
    int r, c;
    for (r = 0; r < mapRows; r++)
    {
        for (c = 0; c < mapCols; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}

void displayPoints(const int healthPoints[MAX_NUM_WARRIORS],
                   const int fightPoints[MAX_NUM_WARRIORS],
                   const int shootPoints[MAX_NUM_WARRIORS])
{
    int i, hp, fp, sp;
    cout << "== Warrior Letter (HP,FP,SP) ==" << endl;
    for (i = 0; i < MAX_NUM_WARRIORS; i++)
    {
        hp = healthPoints[i];
        if (hp > 0)
        {
            fp = fightPoints[i];
            sp = shootPoints[i];
            cout << indexToLetter(i) << "(" << hp << "," << fp << "," << sp << ")" << endl;
        }
    }
}

// TODO: Implement updateMapForMoveAction
// This function handles the updates based on the movements
// @param map: The 2D array storing the map information
// @param mapRows: The number of rows for this map
// @param mapCols: The number of columns for this map
// @param letter: The warrior letter to be moved
// @param direction: The direction enum, please check DirectionType enum
// @param moveSteps: The number of movement steps
//
// @return The status of move action, please check StatusMoveAction enum
StatusMoveAction updateMapForMoveAction(char map[MAX_ROWS][MAX_COLS], int mapRows, int mapCols,
                                        char letter, DirectionType direction, int moveSteps)
{
int currentRow, currentCol;
bool k= false;
for (int i = 0; i < mapRows; i++)
{
    for (int j = 0; j < mapCols; j++)
    {
        if (map[i][j] == letter)
        {
            currentRow = i ;
            currentCol = j ;
            k= true;
            break;
        }
}
if (k)
{
    break;
}
}
int originalRow = currentRow, originalCol = currentCol;
for (int step = 1; step <= moveSteps; step++)
{
     switch (direction)
    {
        case DIRECTION_EAST:
        currentCol += 1;
        break;
    

        case DIRECTION_SOUTH:
        currentRow +=1;
        break;

        case DIRECTION_WEST:
        currentCol -= 1;
        break;

        case DIRECTION_NORTH:
        currentRow -= 1;
        break;

        default:
        return STATUS_ACTION_MOVE_NOT_IMPLMENTED;

    }
    /*
    Success. The warrior should be moved to the new position.
    Fail, hitting a boundary. The position remains unchanged
    Here is an example to illustrate the boundary checking:*/
    if (currentCol < 0 || currentRow < 0 || currentCol >= mapCols || currentRow >= mapRows)
    {
        return STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY;
    }
    if (map[currentRow][currentCol] != CHAR_EMPTY)
    {
        return STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH;
    }
}
map[originalRow][originalCol] = CHAR_EMPTY;
map[currentRow][currentCol] = letter;
return STATUS_ACTION_MOVE_SUCCESS;

}

// TODO: Implement updateMapAndHealthPointsForFightAction
// This function handles the updates based on the fight action
// @param healthPoints: The 1D array storing the health points of warriors
// @param map: The 2D array storing the map information
// @param mapRows: The number of rows for this map
// @param mapCols: The number of columns for this map
// @param fightPoints: The 1D array storing the fight points of warriors
// @param letter: The warrior letter that triggers the fight action
// @param direction: The direction enum, please check DirectionType enum
//
// We have 3 parameters that are pass-by-reference. They will be returned to the main function:
// @param targetLetter: The target warrior letter
// @param targetOriginalHealthPoint: The original health point of the target warrior
// @param targetUpdatedHealthPoint: The updated health point of the target warrior
//
// @return The status of the fight action, please check StatusFightAction enum
StatusFightAction updateMapAndHealthPointsForFightAction(int healthPoints[MAX_NUM_WARRIORS],
                                                         char map[MAX_ROWS][MAX_COLS],
                                                         int mapRows, int mapCols,
                                                         const int fightPoints[MAX_NUM_WARRIORS],
                                                         char letter,
                                                         DirectionType direction,
                                                         char &targetLetter,
                                                         int &targetOriginalHealthPoint,
                                                         int &targetUpdatedHealthPoint)
{
int currentRow, currentCol;
bool k= false;
for (int i = 0; i < mapRows; i++)
{
    for (int j = 0; j < mapCols; j++)
    {
        if (map[i][j] == letter)
        {
            currentRow = i ;
            currentCol = j ;
            k=true;
            break;
            
        }
}
if (k)
{
    break;
}
}
int originalRow = currentRow, originalCol = currentCol;
switch (direction)
{
    case DIRECTION_EAST:
    currentCol += 1;
    break;


    case DIRECTION_SOUTH:
    currentRow +=1;
    break;

    case DIRECTION_WEST:
    currentCol -= 1;
    break;

    case DIRECTION_NORTH:
    currentRow -= 1;
    break;
    default:
    return STATUS_ACTION_FIGHT_NOT_IMPLEMENTED;
}

targetLetter = map[currentRow][currentCol];
if (targetLetter == CHAR_EMPTY )
{
    return STATUS_ACTION_FIGHT_FAIL;
}
if (currentCol < 0 || currentRow < 0 || currentCol >= mapCols || currentRow >= mapRows)
    {
       return STATUS_ACTION_FIGHT_FAIL;
    }
int targetIndex = letterToArrayIndex(targetLetter);
targetOriginalHealthPoint = healthPoints[targetIndex];
targetUpdatedHealthPoint = targetOriginalHealthPoint - fightPoints[letterToArrayIndex(letter)];

if (targetUpdatedHealthPoint <= 0)
{
    targetUpdatedHealthPoint = 0;
    map[originalRow][originalCol] = CHAR_EMPTY;
    map[currentRow][currentCol] = letter;
}
healthPoints[targetIndex] = targetUpdatedHealthPoint;
return STATUS_ACTION_FIGHT_SUCCESS;

}

// TODO: Implement updateMapAndHealthPointsForShootAction
// This function handles the updates based on the shoot action
// @param healthPoints: The 1D array storing the health points of warriors
// @param map: The 2D array storing the map information
// @param mapRows: The number of rows for this map
// @param mapCols: The number of columns for this map
// @param shootPoints: The 1D array storing the shoot points of warriors
// @param letter: The warrior letter that triggers the shoot action
// @param direction: The direction enum, please check DirectionType enum
//
// We have 3 parameters that are pass-by-reference. They will be returned to the main function:
// @param targetLetter: The target warrior letter
// @param targetOriginalHealthPoint: The original health point of the target warrior
// @param targetUpdatedHealthPoint: The updated health point of the target warrior
//
// @return The status of the shoot action, please check StatusShootAction enum
StatusShootAction updateMapAndHealthPointsForShootAction(int healthPoints[MAX_NUM_WARRIORS],
                                                         char map[MAX_ROWS][MAX_COLS],
                                                         int mapRows, int mapCols,
                                                         const int shootPoints[MAX_NUM_WARRIORS],
                                                         char letter,
                                                         DirectionType direction,
                                                         char &targetLetter,
                                                         int &targetOriginalHealthPoint,
                                                         int &targetUpdatedHealthPoint)
{
int currentRow, currentCol;
bool k= false;
for (int i = 0; i < mapRows; i++)
{
    for (int j = 0; j < mapCols; j++)
    {
        if (map[i][j] == letter)
        {
            currentRow = i ;
            currentCol = j ;
            k= true;
            break;
        }
}
if (k)
{
    break;
}
}

switch (direction)
{
    case DIRECTION_EAST:
    currentCol += 2;
    break;


    case DIRECTION_SOUTH:
    currentRow +=2;
    break;

    case DIRECTION_WEST:
    currentCol -= 2;
    break;

    case DIRECTION_NORTH:
    currentRow -= 2;
    break;

    case DIRECTION_NORTH_EAST:
    currentCol += 1;
    currentRow -= 1;
    break;


    case DIRECTION_SOUTH_WEST:
    currentRow += 1;
    currentCol -= 1;
    break;

    case DIRECTION_NORTH_WEST:
    currentCol -= 1;
    currentRow -= 1;
    break;

    case DIRECTION_SOUTH_EAST:
    currentRow += 1;
    currentCol += 1;
    break;

    default:
    return STATUS_ACTION_SHOOT_NOT_IMPLEMENTED;

}
    
if (currentCol < 0 || currentRow < 0 || currentCol >= mapCols || currentRow >= mapRows)
{
    return STATUS_ACTION_SHOOT_FAIL;
}
targetLetter = map[currentRow][currentCol];
if (targetLetter != CHAR_EMPTY)
{
int targetIndex = letterToArrayIndex(targetLetter);
targetOriginalHealthPoint = healthPoints[targetIndex];
targetUpdatedHealthPoint = targetOriginalHealthPoint - shootPoints[letterToArrayIndex(letter)];
if (targetUpdatedHealthPoint <= 0)
{
targetUpdatedHealthPoint = 0;
map[currentRow][currentCol] = CHAR_EMPTY;
}
healthPoints[targetIndex] = targetUpdatedHealthPoint;
return STATUS_ACTION_SHOOT_SUCCESS;
}
return STATUS_ACTION_SHOOT_FAIL;
}




// The main function
// Given: You should not make any changes
int main()
{
    // Arrays
    char map[MAX_ROWS][MAX_COLS];
    char actionText[MAX_ACTION_TEXT_LENGTH];
    char directionText[MAX_DIRECTION_TEXT_LENGTH];
    int healthPoints[MAX_NUM_WARRIORS];
    int fightPoints[MAX_NUM_WARRIORS];
    int shootPoints[MAX_NUM_WARRIORS];

    // Other variables
    int mapRows, mapCols, moveSteps;
    char letter;
    ActionType action;
    DirectionType direction;
    StatusMoveAction statusMove;
    StatusFightAction statusFight;
    StatusShootAction statusShoot;

    char targetLetter;
    int targetOriginalHealthPoint;
    int targetUpdatedHealthPoint;

    // Start by reading the input
    readInputPoints(healthPoints, fightPoints, shootPoints);
    readInputMap(map, mapRows, mapCols);

    cout << "The initial game information:" << endl;
    displayPoints(healthPoints, fightPoints, shootPoints);
    displayMap(map, mapRows, mapCols);

    // Start of the simulation

    while (true)
    {
        cin >> letter;
        if (letter == CHAR_END_INPUT)
            break; // End of the game

        // read the action text and convert it for further processing
        cin >> actionText >> directionText;
        action = convertToActionType(actionText);
        direction = convertDirectionText(directionText);

        if (action == ACTION_MOVE)
        {
            // need to read the steps if the action is ACTION_MOVE
            cin >> moveSteps;
            if (isValidMoveDirection(direction))
            {
                statusMove = updateMapForMoveAction(map, mapRows, mapCols, letter, direction, moveSteps);
                if (statusMove == STATUS_ACTION_MOVE_NOT_IMPLMENTED)
                {
                    cout << "Error: The move action is not implemented yet" << endl;
                }
                else if (statusMove == STATUS_ACTION_MOVE_SUCCESS)
                {
                    cout << "Success: "
                         << "Warrior " << letter << " moves along the direction " << convertDirectionText(direction) << " by " << moveSteps << " step(s)" << endl;
                    displayMap(map, mapRows, mapCols);
                }
                else if (statusMove == STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY)
                {
                    cout << "Fail: " 
                         << "If " << letter << " moves along the direction " << convertDirectionText(direction) << " by " << moveSteps << " step(s)"
                         << ", it will move outside a boundary. The position remains unchanged" << endl;
                    displayMap(map, mapRows, mapCols);
                }
                else if (statusMove == STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH)
                {
                    cout << "Fail: "
                         << "If " << letter << " moves along the direction " << convertDirectionText(direction) << " by " << moveSteps << " step(s)"
                         << ", it will hit another along the path. The position remains unchanged" << endl;
                    displayMap(map, mapRows, mapCols);
                }
            }
            else
            {
                cout << "Error: The direction " << convertDirectionText(direction) << " is invalid for the move action" << endl;
            }
        }
        else if (action == ACTION_FIGHT)
        {
            if (isValidFightDirection(direction))
            {
                statusFight = updateMapAndHealthPointsForFightAction(healthPoints, map, mapRows, mapCols, fightPoints, letter, direction, targetLetter,
                                                                     targetOriginalHealthPoint, targetUpdatedHealthPoint);
                if (statusFight == STATUS_ACTION_FIGHT_NOT_IMPLEMENTED)
                {
                    cout << "Error: The fight action is not implemented yet" << endl;
                }
                else if (statusFight == STATUS_ACTION_FIGHT_SUCCESS)
                {

                    cout << "Success: "
                         << "Warrior " << letter << " fights " << targetLetter << endl;
                    cout << "Warrior " << targetLetter << " health point is reduced from " << targetOriginalHealthPoint << " to " << targetUpdatedHealthPoint << endl;
                    if (targetUpdatedHealthPoint == 0)
                    {
                        cout << "Warrior " << targetLetter << " is being killed by " << letter << endl;
                        displayMap(map, mapRows, mapCols);
                    }

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
                else if (statusFight == STATUS_ACTION_FIGHT_FAIL)
                {

                    cout << "Fail: "
                         << "Warrior " << letter << " cannot fight any target" << endl;

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
            }
            else
            {
                cout << "Error: The direction " << convertDirectionText(direction) << " is invalid for the fight action" << endl;
            }
        }
        else if (action == ACTION_SHOOT)
        {
            if (isValidShootDirection(direction))
            {
                statusShoot = updateMapAndHealthPointsForShootAction(healthPoints, map, mapRows, mapCols, shootPoints, letter, direction, targetLetter,
                                                                     targetOriginalHealthPoint, targetUpdatedHealthPoint);
                if (statusShoot == STATUS_ACTION_SHOOT_NOT_IMPLEMENTED)
                {
                    cout << "Error: The shoot action is not implemented yet" << endl;
                }
                else if (statusShoot == STATUS_ACTION_SHOOT_SUCCESS)
                {

                    cout << "Success: "
                         << "Warrior " << letter << " shoots " << targetLetter << endl;
                    cout << "Warrior " << targetLetter << " health point is reduced from " << targetOriginalHealthPoint << " to " << targetUpdatedHealthPoint << endl;
                    if (targetUpdatedHealthPoint == 0)
                    {
                        cout << "Warrior " << targetLetter << " is being killed by " << letter << endl;
                        displayMap(map, mapRows, mapCols);
                    }

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
                else if (statusShoot == STATUS_ACTION_SHOOT_FAIL)
                {

                    cout << "Fail: "
                         << "Warrior " << letter << " cannot shoot any target" << endl;

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
            }
            else
            {
                cout << "Error: The direction " << convertDirectionText(direction) << " is invalid for the shoot action" << endl;
            }
        }
    }

    return 0;
}