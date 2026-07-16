#include "RecipeSpace.h"

namespace RecipeSpace
{
    int Convert_To_int(string strNum)
    {
        int Num;
        stringstream ss {strNum};
        ss >> Num;
        if(ss.fail())
        {
            cerr << "Could not convert " << strNum << " to integer " << endl;
            exit(ERR_CONV);
        }
        return Num;
    }

    bool RangeChecking(int Number, int Min, int Max)
    {
        return(Number >= Min && Number <= Max);
    }

    void Arg_Check(int Number, int Min, int Max)
    {
        if (!RangeChecking(Number, Min, Max))
        {
            cerr << "Please enter a number between " << Min << " and " << Max << " For Number " << Number << endl;
            exit(ERR_FAIL);
        }
    }

    int GenRandom(int Lowest, int Highest)
    {
        assert(Highest >= Lowest);
        int Range = Highest - Lowest + 1;
        return (rand() % Range + Lowest);
    }

    void PlaceFeature(TwoDarray arrGame, int Rows, int Cols, int intCount, int Feature)
    {
        for (int a = 0; a < intCount; a++)
        {
            int Ran_Row = GenRandom(0, Rows - 1);
            int Ran_Col = GenRandom(0, Cols - 1);
            while (arrGame[Ran_Row][Ran_Col] != EMPTY)
            {
                Ran_Row = GenRandom(0, Rows - 1);
                Ran_Col = GenRandom(0, Cols - 1);
            }
            arrGame[Ran_Row][Ran_Col] = Feature;
        }
    }

    // Allocating Memory
    TwoDarray AllocMem(int Rows, int Cols)
    {
        TwoDarray arrGame;
        arrGame = new int*[Rows];
        for(int a = 0; a < Rows; a++)
        {
            arrGame[a] = new int[Cols];
        }
        for(int a = 0; a < Rows; a++)
        {
            for(int c = 0; c < Cols; c++)
            {
                arrGame[a][c] = EMPTY;
            }
        }
        return arrGame;
    }

    void IniGame(TwoDarray arrGame, int Rows, int Cols, int NumTrees, int NumFlint, int BushChance)
    {
        // Placing the player
        int PRow = GenRandom(0, Rows / 2);
        int PCol = GenRandom(0, Cols / 2);
        arrGame[PRow][PCol] = PLAYER;

        // Placing the trees
        PlaceFeature(arrGame, Rows, Cols, NumTrees, TREES);

        // Placing the bushes
        for (int a = 0; a < Rows; a++)
        {
            for(int c = 0; c < Cols; c++)
            {
                if (GenRandom(1, 100) <= BushChance)
                {
                    PlaceFeature(arrGame, Rows, Cols, 1, BUSHES);
                }
            }
        }
        // Placing the flints in the game
        PlaceFeature(arrGame, Rows, Cols, NumFlint, FLINT);
    }

    void Pause()
    {
        cin.ignore(100, '\n');
        cout << "Press any key to continue " << endl;
        cin.get();
    }

    void PrintWorld(TwoDarray arrGame, int Rows, int Cols)
    {
        for (int a = 0; a < Rows; a++)
        {
            for(int c = 0; c < Cols; c++)
            {
                cout << chFeatures[arrGame[a][c]] << " ";
            }
            cout << endl;
        }

        // ADDED HINT HERE
        cout << "\n*** SURVIVAL HINT ***" << endl;
        cout << "1. Collect Sticks (#) and Flints (O)." << endl;
        cout << "2. Press '1' to craft an Axe (Costs 1 Stick, 1 Flint)." << endl;
        cout << "3. Walk into Trees (T) with your Axe to get Logs." << endl;
        cout << "4. Press '1' to craft a Firekit and win! (Costs 2 Sticks, 1 Flint, 3 Logs)." << endl;
        cout << "*********************\n" << endl;

        cout << "--- ACTIONS ---" << endl;
        cout << "1: Craft Item" << endl;
        cout << "w/a/s/d: Move (Up/Left/Down/Right)" << endl;
        cout << "e/q/c/z: Move Diagonally" << endl;
        cout << "x: Quit Game" << endl;
        cout << "---------------" << endl;
    }

    void FindPlayer(TwoDarray arrGame, int Rows, int Cols, int& PRow, int& PCol)
    {
        for(int a = 0; a < Rows; a++)
        {
            for(int c = 0; c < Cols; c++)
            {
                if(arrGame[a][c] == PLAYER || arrGame[a][c] == PLAYER_TREE)
                {
                    PRow = a;
                    PCol = c;
                }
            }
        }
    }

    bool IsInWorld(int Rows, int Cols, int DRow, int DCol)
    {
        return(DRow >= 0 && DRow < Rows && DCol >= 0 && DCol < Cols);
    }

    // Function to move player instead of repeating code
    void MoveTo_Squares(TwoDarray arrGame, int DRow, int DCol, int Feature, int PRow, int PCol, int& intMaterial)
    {
        if (arrGame[DRow][DCol] == Feature)
        {
            intMaterial++;
            arrGame[DRow][DCol] = PLAYER;

            if (arrGame[PRow][PCol] == PLAYER_TREE) {
                arrGame[PRow][PCol] = TREES;
            } else {
                arrGame[PRow][PCol] = EMPTY;
            }
        }
    }

    void MovePlayer(TwoDarray arrGame, int Rows, int Cols, char Input, int& Sticks, int& Flints, int& Num_Turns, int& Axes, int& Logs)
    {
        int PRow = 0;
        int PCol = -1;

        // Finding the player
        FindPlayer(arrGame, Rows, Cols, PRow, PCol);
        if(PCol < 0 || PCol >= Cols || PRow < 0 || PRow >= Rows)
        {
            return;
        }

        int Dest_Row = PRow;
        int Dest_Col = PCol;

        switch(Input)
        {
            case 'w': Dest_Row--; break;
            case 's': Dest_Row++; break;
            case 'd': Dest_Col++; break;
            case 'a': Dest_Col--; break;
            case 'q': Dest_Col--; Dest_Row--; break;
            case 'e': Dest_Col++; Dest_Row--; break;
            case 'z': Dest_Row++; Dest_Col--; break;
            case 'c': Dest_Col++; Dest_Row++; break;
            default: return; // invalid key, don't waste a turn
        }

        if(IsInWorld(Rows, Cols, Dest_Row, Dest_Col))
        {
            // Valid move, deduct a turn
            Num_Turns--;

            // Move player if move to the bush (to get sticks)
            MoveTo_Squares(arrGame, Dest_Row, Dest_Col, BUSHES, PRow, PCol, Sticks);

            // Move player if move to Flint
            MoveTo_Squares(arrGame, Dest_Row, Dest_Col, FLINT, PRow, PCol, Flints);

            // Moving Player to empty space
            if(arrGame[Dest_Row][Dest_Col] == EMPTY)
            {
                arrGame[Dest_Row][Dest_Col] = PLAYER;
                if (arrGame[PRow][PCol] == PLAYER_TREE) arrGame[PRow][PCol] = TREES;
                else arrGame[PRow][PCol] = EMPTY;
            }
            // Moving Player to trees
            else if(arrGame[Dest_Row][Dest_Col] == TREES)
            {
                // If player has an axe, chop it down for a log!
                if (Axes > 0)
                {
                    Logs++;
                    arrGame[Dest_Row][Dest_Col] = PLAYER; // tree is gone
                }
                else
                {
                    // No axe, so just hide in the tree
                    arrGame[Dest_Row][Dest_Col] = PLAYER_TREE;
                }

                // Clean up previous spot
                if (arrGame[PRow][PCol] == PLAYER_TREE) arrGame[PRow][PCol] = TREES;
                else arrGame[PRow][PCol] = EMPTY;
            }
        }
    }

    // Function to handle the creation of items
    void Create_Item(int& intSticks, int& intFlints, int& NumAxes, int& NumLogs, int& FireKit)
    {
        // Try to build firekit first (Win Condition)
        if(intSticks >= 2 && intFlints >= 1 && NumLogs >= 3)
        {
            intSticks -= 2;
            intFlints -= 1;
            NumLogs -= 3;
            FireKit++;
        }
        // If can't build firekit, try to build an axe
        else if(intSticks >= 1 && intFlints >= 1)
        {
            intSticks -= 1;
            intFlints -= 1;
            NumAxes++;
        }
    }

    // Memory cleanup
    void DeallocMem(TwoDarray arrGame, int Rows)
    {
        for (int a = 0; a < Rows; a++)
        {
            delete[] arrGame[a];
        }
        delete[] arrGame;
        arrGame = nullptr;
    }
}
