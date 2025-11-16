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

void displayOutput(string& songName, double& minutes, double& seconds, double& bpm, double& totalBeats, double& lengthofOneBeat)
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

    ofstream outFile;


    banner();


    grabSongName(songName);

    bpm = grabBPM();

    grabSongLength(minutes, seconds);


    songlengthInSeconds = calculateSongLengthInSeconds(minutes, seconds);

    totalBeats = calculateTotalBeats(bpm, songlengthInSeconds);

    lengthofOneBeat = calculateLengthofOneBeat(bpm);


    displayOutput(songName, minutes, seconds, bpm, totalBeats, lengthofOneBeat);



    do
    {
        editingMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            grabSongName(songName);

            cout << "\n" << "\033[32m" << "The song name has been updated to: " << songName << "\n";

            break;

        case 2:
            bpm = grabBPM();

            lengthofOneBeat = calculateLengthofOneBeat(bpm);
            totalBeats = calculateTotalBeats(bpm, songlengthInSeconds);

            cout << "\033[32m" << "The bpm has been updated to: " << setprecision(0) << fixed << bpm << "BPM" << "\n";

            break;

        case 3:
            grabSongLength(minutes, seconds);

            songlengthInSeconds = calculateSongLengthInSeconds(minutes, seconds);
            totalBeats = calculateTotalBeats(bpm, songlengthInSeconds);

            cout << "\n" << "\033[32m" << "The song length has been updated to: " << setprecision(0) << fixed << minutes << " minutes and " << seconds << " seconds.\n";

            break;

        case 4:
            displayOutput(songName, minutes, seconds, bpm, totalBeats, lengthofOneBeat);
            for (int line = 60; line > 0; line--)
            {
                cout << ".";
            }
            break;

        case 5:

            outFile.open(OUTFILENAME);
            outFile << "Song Name:" << setw(50) << songName << "\n";
            outFile << "Minutes in Song:" << setw(44) << minutes << "\n";
            outFile << "Seconds in Song:" << setw(44) << seconds << "\n";
            outFile << "BPM:" << setw(56) << bpm << "\n";
            outFile << "Total Beats in Song:" << setw(40) << setprecision(2) << fixed << totalBeats << "\n";
            outFile << "Length of One Beat (in seconds):" << setw(28) << setprecision(4) << lengthofOneBeat << "\n";
            outFile.close();

            cout << "\033[32m" << "Output has been saved to Report.txt" << "\n";

            break;

        case 6:
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