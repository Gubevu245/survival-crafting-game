#ifndef RECIPESPACE_H_INCLUDED
#define RECIPESPACE_H_INCLUDED

#include <iostream>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cassert>

using namespace std;

namespace RecipeSpace
{
    enum enErorrs
    {
        ERR_INVALID = -4,
        ERR_FAIL,
        ERR_CONV,
        ERR_ARGC,
    };

    const int EMPTY = 0;
    const int PLAYER = 1;
    const int BUSHES = 2;
    const int TREES = 3;
    const int FLINT = 4;
    const int PLAYER_TREE = 5;

    const int ENV_MIN = 5;
    const int ENV_MAX = 18;
    const int EQUIPMENT_MIN = 2 ;
    const int EQUIPMENT_MAX = 10;
    const int MIN_PERCENTAGE = 1 ;
    const int MAX_PERCENTAGE = 100;

    const char chFeatures[6] = {'.','P','#','T','O','P'};

    typedef int* OneDarray;
    typedef int** TwoDarray;

    int Convert_To_int(string strNum);
    bool RangeChecking(int Number, int Min, int Max);
    void Arg_Check(int Number, int Min, int Max);
    TwoDarray AllocMem(int Rows, int Cols);
    void IniGame(TwoDarray arrGame, int Rows, int Cols, int NumTrees, int NumFlint, int BushChance);
    void PlaceFeature(TwoDarray arrGame, int Rows, int Cols, int intCount, int Feature);
    int GenRandom(int Lowest, int Highest);
    void PrintWorld(TwoDarray arrGame, int Rows, int Cols);
    void Pause();
    void FindPlayer(TwoDarray arrGame, int Rows, int Cols, int& PRow, int& PCol);
    bool IsInWorld(int Rows, int Cols, int DRow, int DCol);
    void MoveTo_Squares(TwoDarray arrGame, int DRow, int DCol, int Feature, int PRow, int PCol, int& intMaterial);

    // Updated prototypes with correct references
    void MovePlayer(TwoDarray arrGame, int Rows, int Cols, char Input, int& Sticks, int& Flints, int& Num_Turns, int& Axes, int& Logs);
    void Create_Item(int& intSticks, int& intFlints, int& NumAxes, int& NumLogs, int& FireKit);
    void DeallocMem(TwoDarray arrGame, int Rows); // added memory cleanup
}

#endif // RECIPESPACE_H_INCLUDED
