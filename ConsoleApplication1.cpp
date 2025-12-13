#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const string OUTFILENAME = "report.txt";
const int VARIGNORE = 100000;
const int SONG_COUNT = 2;


class grabInput
{
    public:
    
    double bpm()
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
    
    void songLength(double& minutes, double& seconds)
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
    }
    
    void SongName(string& songName)
    {
        cout << "\033[34m" << "What was the name of the last song you listened to?\n" << "\033[0m";
        cin >> (songName);
    }
};

class calculate
{
    public:
        
        double totalBeats(double bpm, double songlengthInSeconds)
        {
            double totalBeats = (bpm / 60.0) * songlengthInSeconds;
            return totalBeats;
        }
        
        double lengthofOneBeat(double bpm)
        {
            double lengthofOneBeat = (60.0) / bpm;
            return lengthofOneBeat;
        }

        double songLengthInSeconds(double minutes, double seconds)
        {
            double songlengthInSeconds = (minutes * 60) + seconds;
            return songlengthInSeconds;
        }
        

};

class practiceTracker
{

    int practicingMinutes[7];
    static const int arraySize = 7;

    void grab()
    {
        cout << "\033[34m" << "How many minutes have you spent practicng every day this week? Enter 7 values" << "\033[0m" << "\n";

        for (int i = 0; i < arraySize; i++)
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

    int computeTotalMinutes() const
    {
        int totalMinutesLocal = 0;
        for (int i = 0; i < arraySize; i++)
        {
            totalMinutesLocal += practicingMinutes[i];
        }
        return totalMinutesLocal;
    }

public:
    int total;

    practiceTracker()
    {
        grab();
        total = computeTotalMinutes();
    }
	
};

class display
{
    public:
        
        void banner()
        {
            cout << "\033[34m" << "------------------------------------------------------------" << endl;
            cout << "                Welcome to the BPM Calculator     " << endl;
            cout << "------------------------------------------------------------" << endl;
            cout << "Hello!!!" << "\033[0m" << endl;
        }

        void editingMenu()
        {
            cout << "\n" << "\033[34m" << "----EDITING MENU----" << endl;
            cout << "0) select active song" << endl;
            cout << "1) edit song name" << endl;
            cout << "2) edit bpm" << endl;
            cout << "3) edit song length" << endl;
            cout << "4) display output (active song)" << endl;
            cout << "5) save output to report.txt (all songs)" << endl;
            cout << "\033[31m" << "6) exit program" << "\033[0m" << endl;
        }

        void output(const string& songName, double minutes, double seconds, double bpm, double totalBeats, double lengthofOneBeat, int totalMinutes)
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

};

struct song
{
    string songName = "";
    double bpm = 0.0;
    double minutes = 0.0;
    double seconds = 0.0;
    double songlengthInSeconds = 0.0;
    double totalBeats = 0.0;
    double lengthofOneBeat = 0.0;
};

void fillSongStruct(song& mySong)
{
    grabInput().SongName(mySong.songName);
    grabInput().songLength(mySong.minutes, mySong.seconds);
	mySong.bpm = grabInput().bpm();
    mySong.songlengthInSeconds = calculate().songLengthInSeconds(mySong.minutes, mySong.seconds);
    mySong.totalBeats = calculate().totalBeats(mySong.bpm, mySong.songlengthInSeconds);
    mySong.lengthofOneBeat = calculate().lengthofOneBeat(mySong.bpm);
}

void fillSongs(song songs[], int count)
{
    for (int i = 0; i < count; ++i) {
        cout << "\nSong entry " << (i + 1) << " of " << count << "\n";
        fillSongStruct(songs[i]);
    }
}

int selectSongIndex(int count)
{
    int selection = -1;
    cout << "\033[34m" << "Select active song (1 - " << count << "): " << "\033[0m";
    while (true) {
        if (!(cin >> selection) || selection < 1 || selection > count) {
            cout << "\033[31m" << "Invalid choice. Enter a number between 1 and " << count << "." << "\033[0m" << endl;
            cin.clear();
            cin.ignore(VARIGNORE, '\n');
        } else {
            break;
        }
    }
    return selection - 1; // zero-based index
}

int main()
{
    int choice{};
    int sentinel = 0;
    int arraySize = 7;
    int practicingMinutes[] = {0, 0, 0, 0, 0, 0 ,0};

    enum menuchoice { SELECT_SONG, EDIT_SONG_NAME, EDIT_BPM, EDIT_SONG_LENGTH, DISPLAY_OUTPUT, SAVE_OUTPUT, EXIT_PROGRAM };

    ofstream outFile;

    display().banner();       //where the program starts running

    song songsArray[SONG_COUNT];
    fillSongs(songsArray, SONG_COUNT);

    int activeIndex = 0;
    cout << "\nDefaulting to active song 1. To change active song use menu option 0.\n";

	practiceTracker myPracticeTracker;


    // Display active song initially
    display().output(songsArray[activeIndex].songName, songsArray[activeIndex].minutes, songsArray[activeIndex].seconds, songsArray[activeIndex].bpm, songsArray[activeIndex].totalBeats, songsArray[activeIndex].lengthofOneBeat, myPracticeTracker.total);
    
    do
    {
        display().editingMenu();
        cin >> choice;

        switch (choice) {
        case SELECT_SONG:
            
            activeIndex = selectSongIndex(SONG_COUNT);
            
            cout << "\033[32m" << "Active song set to: " << (activeIndex + 1) << "\033[0m" << "\n";
            
            break;

        case EDIT_SONG_NAME:
            
            grabInput().SongName(songsArray[activeIndex].songName);
            
            cout << "\n" << "\033[32m" << "The song name has been updated to: " << songsArray[activeIndex].songName << "\n";
            
            break;

        case EDIT_BPM:
            
            songsArray[activeIndex].bpm = grabInput().bpm();
            
            songsArray[activeIndex].lengthofOneBeat = calculate().lengthofOneBeat(songsArray[activeIndex].bpm);
            
            songsArray[activeIndex].totalBeats = calculate().totalBeats(songsArray[activeIndex].bpm, songsArray[activeIndex].songlengthInSeconds);
            
            cout << "\033[32m" << "The bpm has been updated to: " << setprecision(0) << fixed << songsArray[activeIndex].bpm << "BPM" << "\n";
            break;

        case EDIT_SONG_LENGTH:
            
            grabInput().songLength(songsArray[activeIndex].minutes, songsArray[activeIndex].seconds);
            
            songsArray[activeIndex].songlengthInSeconds = calculate().songLengthInSeconds(songsArray[activeIndex].minutes, songsArray[activeIndex].seconds);
            
            songsArray[activeIndex].totalBeats = calculate().totalBeats(songsArray[activeIndex].bpm, songsArray[activeIndex].songlengthInSeconds);
            
            cout << "\n" << "\033[32m" << "The song length has been updated to: " << setprecision(0) << fixed << songsArray[activeIndex].minutes << " minutes and " << songsArray[activeIndex].seconds << " seconds.\n";
            break;

        case DISPLAY_OUTPUT:
            
            display().output(songsArray[activeIndex].songName, songsArray[activeIndex].minutes, songsArray[activeIndex].seconds, songsArray[activeIndex].bpm, songsArray[activeIndex].totalBeats, songsArray[activeIndex].lengthofOneBeat, myPracticeTracker.total);
            
            for (int line = 60; line > 0; line--)
            {
                cout << ".";
            }
            break;

        case SAVE_OUTPUT:
            
            outFile.open(OUTFILENAME);
            
            for (int i = 0; i < SONG_COUNT; ++i) {
                outFile << "Song " << (i + 1) << " Name:" << setw(50) << songsArray[i].songName << "\n";
                outFile << "Minutes in Song:" << setw(44) << songsArray[i].minutes << "\n";
                outFile << "Seconds in Song:" << setw(44) << songsArray[i].seconds << "\n";
                outFile << "BPM:" << setw(56) << songsArray[i].bpm << "\n";
                outFile << "Total Beats in Song:" << setw(40) << setprecision(2) << fixed << songsArray[i].totalBeats << "\n";
                outFile << "Length of One Beat (in seconds):" << setw(28) << setprecision(4) << songsArray[i].lengthofOneBeat << "\n";
                outFile << "\n";
            }
            outFile << "Total Minutes Practiced This Week:" << setw(26) << myPracticeTracker.total << "\n";
            outFile.close();

            cout << "\033[32m" << "Output has been saved to " << OUTFILENAME << "\n";
            break;

        case EXIT_PROGRAM:
            
            cout << "\n" << "\033[32m" << "Exiting program." << endl;
            sentinel = 1;
            
            break;

        default:
            cout << "\n" << "\033[31m" << "Invalid choice. Enter valid input." << endl;
            break;
        }

    } while (sentinel == 0);

    return 0;
}