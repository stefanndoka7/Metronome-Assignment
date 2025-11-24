#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>


using namespace std;

const string OUTFILENAME = "report.txt";
const int VARIGNORE = 100000;

void banner()
{
    cout << "\033[34m" << "------------------------------------------------------------" << endl;
    cout << "                Welcome to the BPM Calculator     " << endl;
    cout << "------------------------------------------------------------" << endl;
    cout <<  "Hello!!!" << "\033[0m" << endl;
}

double calculateTotalBeats(double bpm, double songlengthInSeconds)
{
    double totalBeats = (bpm / 60.0) * songlengthInSeconds;
    return totalBeats;
}

double calculateLengthofOneBeat(double bpm)
{
    double lengthofOneBeat = (60.0) / bpm;
    return lengthofOneBeat;
}

double calculateSongLengthInSeconds(double minutes, double seconds)
{
    double songlengthInSeconds = (minutes * 60) + seconds;
    return songlengthInSeconds;
}

double grabBPM()
{
    double bpm{};
    cout << "\033[34m" << "Enter the BPM\n" << "\033[0m";
    while (true) {
        if (!(cin >> bpm) || (bpm <= 0))      //input validation for bpm
        {
            cout << "\033[31m" << "User input was invalid. Please try enter a valid input (any number above 0)." << "\033[0m" << endl;
            cin.clear();
            cin.ignore(VARIGNORE, '\n');
        }
        else
            break;
    }
    return bpm;
}

double grabSongLength(double& minutes, double& seconds)
{
    cout << "\033[34m" << "Enter how many minutes long, and then the remaining seconds" << "\033[0m" << "\n";
    while (true) {
        if (!(cin >> minutes >> seconds) || (seconds >= 60 || seconds < 0 || minutes < 0))
        {
            cout << "\033[31m" << "User input was invalid. Please try entering a valid input" << "\n";
            cout << "(minutes can be any whole number, and seconds can be any whole number thats less than 60)" << "\033[0m" << endl;
            cin.clear();
            cin.ignore(VARIGNORE, '\n');
        }
        else
            break;
    }
    return 0;
}

int grabSongName(string& songName)
{
    cout << "\033[34m" << "What was the name of the last song you listened to?\n" << "\033[0m";
    cin >> (songName);
    return 0;
}

int grabMinutesPracticed(int practicingMinutes[], int arraySize)
{
    cout << "\033[34m" << "How many minutes have you spent practicng every day this week? Enter 7 values" << "\033[0m" << "\n";
    for (int i = 0; i < arraySize; i++)
    {
        {
            while (true) {
                if (!(cin >> practicingMinutes[i]) || (practicingMinutes[i] < 0))
                {
                    cout << "\033[31m" << "User input was invalid. Please try enter a valid input (any whole number)." << "\033[0m" << endl;
                    cin.clear();
                    cin.ignore(VARIGNORE, '\n');
                }
                else
                    break;
            }
        }
    }
    return 0;
}

int totalMinutesPracticed(int practicingMinutes[], int arraySize)
{
    int totalMinutes = 0;
    for (int i = 0; i < arraySize; i++)
    {
        totalMinutes += practicingMinutes[i];
    }
    return totalMinutes;
}

void editingMenu()
{
    cout << "\n" << "\033[34m" << "----EDITING MENU----" << endl;
    cout << "1) edit song name" << endl;
    cout << "2) edit bpm" << endl;
    cout << "3) edit song length" << endl;
    cout << "4) display output" << endl;
    cout << "5) save output to report.txt" << endl;
    cout << "\033[31m" << "6) exit program" << "\033[0m" << endl;

}

void displayOutput(string songName, double minutes, double seconds, double bpm, double totalBeats, double lengthofOneBeat, int totalMinutes)
{
    cout << "\033[32m";

    for (int line = 60; line > 0; line--)
    {
        cout << ".";
    }
    cout << "\n" << "----CURRENT SONG INFORMATION----" << endl;
    cout << "Song Name:" << setw(50) << songName << "\n";
    cout << "Minutes in Song:" << setw(44) << setprecision(0) << fixed << minutes << "\n";
    cout << "Seconds in Song:" << setw(44) << seconds << "\n";
    cout << "BPM:" << setw(56) << bpm << "\n";
    cout << "Total Beats in Song:" << setw(40) << setprecision(2) << totalBeats << "\n";
    cout << "Length of One Beat (in seconds):" << setw(28) << setprecision(4) << lengthofOneBeat << "\n";
	cout << "Total Minutes Practiced This Week:" << setw(26) << totalMinutes << "\n";
}



int main()
{
    string songName;    //declaring variables, seperated by whether they are input or output
    double bpm{};
    double minutes{};
    double seconds{};

    double songlengthInSeconds{};
    double totalBeats{};
    double lengthofOneBeat{};

    int choice{};
    int sentinel = 0;
	int arraySize = 7;
	int totalMinutes = 0;

    int practicingMinutes[] = {0, 0, 0, 0, 0, 0 ,0};

	enum menuchoice { EDIT_SONG_NAME = 1, EDIT_BPM, EDIT_SONG_LENGTH, DISPLAY_OUTPUT, SAVE_OUTPUT, EXIT_PROGRAM };

    ofstream outFile;


	banner();       //where the program starts running

    grabSongName(songName);

    bpm = grabBPM();

    grabSongLength(minutes, seconds);

    grabMinutesPracticed(practicingMinutes, arraySize);

	totalMinutes = totalMinutesPracticed(practicingMinutes, arraySize);

    songlengthInSeconds = calculateSongLengthInSeconds(minutes, seconds);

    totalBeats = calculateTotalBeats(bpm, songlengthInSeconds);

    lengthofOneBeat = calculateLengthofOneBeat(bpm);


    displayOutput(songName, minutes, seconds, bpm, totalBeats, lengthofOneBeat, totalMinutes);



    do
    {
        editingMenu();
        cin >> choice;

        switch (choice) {
        case EDIT_SONG_NAME:
            grabSongName(songName);

            cout << "\n" << "\033[32m" << "The song name has been updated to: " << songName << "\n";

            break;

        case EDIT_BPM:
            bpm = grabBPM();

            lengthofOneBeat = calculateLengthofOneBeat(bpm);
            totalBeats = calculateTotalBeats(bpm, songlengthInSeconds);

            cout << "\033[32m" << "The bpm has been updated to: " << setprecision(0) << fixed << bpm << "BPM" << "\n";

            break;

        case EDIT_SONG_LENGTH:
            grabSongLength(minutes, seconds);

            songlengthInSeconds = calculateSongLengthInSeconds(minutes, seconds);
            totalBeats = calculateTotalBeats(bpm, songlengthInSeconds);

            cout << "\n" << "\033[32m" << "The song length has been updated to: " << setprecision(0) << fixed << minutes << " minutes and " << seconds << " seconds.\n";

            break;

        case DISPLAY_OUTPUT:
            displayOutput(songName, minutes, seconds, bpm, totalBeats, lengthofOneBeat, totalMinutes);
            for (int line = 60; line > 0; line--)
            {
                cout << ".";
            }
            break;

        case SAVE_OUTPUT:

            outFile.open(OUTFILENAME);
            outFile << "Song Name:" << setw(50) << songName << "\n";
            outFile << "Minutes in Song:" << setw(44) << minutes << "\n";
            outFile << "Seconds in Song:" << setw(44) << seconds << "\n";
            outFile << "BPM:" << setw(56) << bpm << "\n";
            outFile << "Total Beats in Song:" << setw(40) << setprecision(2) << fixed << totalBeats << "\n";
            outFile << "Length of One Beat (in seconds):" << setw(28) << setprecision(4) << lengthofOneBeat << "\n";
			outFile << "Total Minutes Practiced This Week:" << setw(26) << totalMinutes << "\n";
            outFile.close();

            cout << "\033[32m" << "Output has been saved to report.txt" << "\n";

            break;

        case EXIT_PROGRAM:
            cout << "\n" << "\033[32m" << "Exiting program." << endl;
            sentinel = 1;
            break;

        default:
            cout << "\n" << "\033[31m" << "Invalid choice. Enter valid input (1-6)." << endl;
            break;
        }

    } while (sentinel == 0);

    return 0;

}