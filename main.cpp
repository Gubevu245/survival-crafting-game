#include "RecipeSpace.h"
#include <iostream>

using namespace RecipeSpace;
using namespace std;

int main(int argc , char** argv)
{
    // Seed the random number generation
    srand(time(nullptr));

    // Checking the number of arguments
    if(argc != 7)
    {
        cerr << "Please run application with " << argv[0] << " <TotalRows> <TotalCols> "
             << "<ChanceBush> <NumberOfTrees> <Number_Of_Flint> <Number_Turns>" << endl;
        exit(ERR_ARGC);
    }

    // Converting arguments to integer values
    int NumRows = Convert_To_int(argv[1]);
    int NumCols = Convert_To_int(argv[2]);
    int ChanceBush = Convert_To_int(argv[3]);
    int Number_Of_Trees = Convert_To_int(argv[4]);
    int Number_Of_Flint = Convert_To_int(argv[5]);
    int Number_Of_Turns = Convert_To_int(argv[6]);

    // Checking range for the arguments
    Arg_Check(NumRows, ENV_MIN, ENV_MAX);
    Arg_Check(NumCols, ENV_MIN, ENV_MAX);
    Arg_Check(ChanceBush, MIN_PERCENTAGE, MAX_PERCENTAGE);
    Arg_Check(Number_Of_Trees, EQUIPMENT_MIN, EQUIPMENT_MAX);
    Arg_Check(Number_Of_Flint, EQUIPMENT_MIN, EQUIPMENT_MAX);

    // Declaring variables
    TwoDarray arrGame;
    char Input = '\0';
    bool blnContinue = true;
    int intSticks = 0;
    int intFlints = 0;
    int Number_Logs = 0;
    int Number_FireKit = 0;
    int Number_Axes = 0;

    // Allocating memory & Initializing array
    arrGame = AllocMem(NumRows, NumCols);
    IniGame(arrGame, NumRows, NumCols, Number_Of_Trees, Number_Of_Flint, ChanceBush);

    // Clear the screen once before the loop
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    do
    {
        // Anti-flicker cursor repositioning
        cout << "\033[H";

        cout << "Collection Bag : \t\t\t\t Number of turns left : " << Number_Of_Turns << "   " << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Sticks: " << intSticks << "\t\tAxes: " << Number_Axes << endl;
        cout << "Flints: " << intFlints << "\t\tLogs: " << Number_Logs << endl;
        cout << "Firekits: " << Number_FireKit << endl;
        cout << "--------------------------------------------------------" << endl;

        // Print the world
        PrintWorld(arrGame, NumRows, NumCols);

        // Win / Loss Conditions
        if (Number_FireKit >= 1)
        {
            cout << "\nYOU WIN! You built a Firekit and survived the bush!" << endl;
            break;
        }
        if (Number_Of_Turns <= 0)
        {
            cout << "\nGAME OVER! You ran out of turns and froze in the wild." << endl;
            break;
        }

        // Get user input
        cout << "Enter command (or 'x' to quit): ";
        cin >> Input;
        Input = tolower(Input);

        if (Input == 'x')
        {
            blnContinue = false;
        }
        else if (Input == '1')
        {
            // Trigger crafting
            Create_Item(intSticks, intFlints, Number_Axes, Number_Logs, Number_FireKit);
        }
        else
        {
            // Moving the player (also deducts turns)
            MovePlayer(arrGame, NumRows, NumCols, Input, intSticks, intFlints, Number_Of_Turns, Number_Axes, Number_Logs);
        }

    } while(blnContinue);

    // Clean up memory
    DeallocMem(arrGame, NumRows);

    return 0;
}
