    #include <iostream>   // Used for standard input/output operations
    #include <fstream>    // Used for file input/output operations
    #include <sstream>    // Used for parsing strings (e.g., parsing leaderboard entries)
    #include <vector>     // Used to manage dynamic arrays (e.g., word lists and leaderboard entries)
    #include <string>     // Used to work with strings
    #include <cstdlib>    // Used for random number generation
    #include <ctime>      // Used to seed the random number generator
    #include <utility>    // Used for pair data structure
    #include <algorithm>  // Used for algorithms (e.g., find, sort)
    #include <cctype>     // Used for character handling functions (e.g., tolower)
    #include <iomanip>    // Used for leaderboard formatting

    using namespace std;

    // File-handling functions 

    // Reads a list of words from a specified file
    vector<string> readWordList(const string& fileName) {
        ifstream file(fileName);
        vector<string> words;
        string word;

        if (file.is_open()) {
            while (getline(file, word)) {
                if (all_of(word.begin(), word.end(), ::isalpha)) {
                    transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert to lowercase
                    words.push_back(word);
                }
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file " << fileName << endl;
        }

        return words;
    }

    // Writes a list of words to a specified file
    void writeWordList(const string& fileName, const vector<string>& words) {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const string& word : words) {
                if (all_of(word.begin(), word.end(), ::isalpha)) {
                    file << word << endl;
                }
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file " << fileName << endl;
        }
    }

    // Saves the leaderboard to a file (name, score)
    void saveLeaderboard(const string& fileName, const vector<pair<string, int>>& leaderboard) {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const auto& entry : leaderboard) {
                file << entry.first << "," << entry.second << endl;
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file " << fileName << endl;
        }
    }

    // Retrieves the leaderboard from a file (name, score)
    vector<pair<string, int>> retrieveLeaderboard(const string& fileName) {
        ifstream file(fileName);
        vector<pair<string, int>> leaderboard;
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string name;
                int score;

                getline(ss, name, ',');
                ss >> score;

                if (!name.empty() && !ss.fail()) {
                    leaderboard.push_back(make_pair(name, score));
                }
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file " << fileName << endl;
        }

        return leaderboard;
    }

    // Initialize predefined word files for each difficulty level
    void initializeWordFiles() {
        vector<string> easyWords = { "fox", "cat", "dog" };
        vector<string> mediumWords = { "orange", "mountain", "planet" };
        vector<string> hardWords = { "palindrome", "dystopia", "mercedes" };

        writeWordList("easy.txt", easyWords);
        writeWordList("medium.txt", mediumWords);
        writeWordList("hard.txt", hardWords);
    }

    // Sort the leaderboard by score in descending order
    void sortLeaderboard(vector<pair<string, int>>& leaderboard) {
        sort(leaderboard.begin(), leaderboard.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
            });
    }

    void displayLeaderboard(vector<pair<string, int>>& leaderboard) {
        sortLeaderboard(leaderboard);
        cout << "\nLeaderboard:\n";
        cout << "-------------------\n";
        cout << left << setw(15) << "Name" << "Score\n";
        cout << "-------------------\n";
        for (const auto& entry : leaderboard) {
            cout << left << setw(15) << entry.first << entry.second << endl;
        }
        cout << "-------------------\n";
    }

    void drawHangman(int wrongGuesses) {
        switch (wrongGuesses) {
        case 0:
            cout << "  +---+" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "     ===" << endl;
            break;
        case 1:
            cout << "  +---+" << endl;
            cout << "  O   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "     ===" << endl;
            break;
        case 2:
            cout << "  +---+" << endl;
            cout << "  O   |" << endl;
            cout << "  |   |" << endl;
            cout << "      |" << endl;
            cout << "     ===" << endl;
            break;
        case 3:
            cout << "  +---+" << endl;
            cout << "  O   |" << endl;
            cout << " /|   |" << endl;
            cout << "      |" << endl;
            cout << "     ===" << endl;
            break;
        case 4:
            cout << "  +---+" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << "      |" << endl;
            cout << "     ===" << endl;
            break;
        case 5:
            cout << "  +---+" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " /    |" << endl;
            cout << "     ===" << endl;
            break;
        case 6:
            cout << "  +---+" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " / \\  |" << endl;
            cout << "     ===" << endl;
            break;
        default:
            cout << "Invalid number of wrong guesses!" << endl;
        }
    }

    int main() {
        srand(time(0));

        initializeWordFiles();

        // Ask for the player's name
        string playerName;
        cout << "Enter your name: ";
        cin >> playerName;

        // Select difficulty
        string difficulty;
        cout << "Select difficulty (easy, medium, hard): ";
        cin >> difficulty;

        // Map difficulty to file name
        string fileName;
        if (difficulty == "easy") {
            fileName = "easy.txt";
        }
        else if (difficulty == "medium") {
            fileName = "medium.txt";
        }
        else if (difficulty == "hard") {
            fileName = "hard.txt";
        }
        else {
            cout << "Invalid difficulty. Defaulting to 'easy'." << endl;
            fileName = "easy.txt";
        }

        // Read words for the selected difficulty
        vector<string> words = readWordList(fileName);
        if (words.empty()) {
            cout << "No words found for this difficulty. Exiting." << endl;
            return 1;
        }

        // Select a random word
        string selectedWord = words[rand() % words.size()];
        string currentDisplay(selectedWord.length(), '_');
        vector<char> guessedLetters;
        int lives = 6;
        int wrongGuesses = 0;

        while (lives > 0 && currentDisplay != selectedWord) {
            drawHangman(wrongGuesses);

            cout << "Current word: ";
            for (char ch : currentDisplay) {
                cout << ch << " ";
            }
            cout << endl;

            cout << "Lives remaining: " << lives << endl;
            cout << "Guessed letters: ";
            for (char letter : guessedLetters) {
                cout << letter << " ";
            }
            cout << endl;

            char guess;
            cout << "Enter your guess: ";
            cin >> guess;
            guess = tolower(guess);

            if (!isalpha(guess)) {
                cout << "Invalid input. Please enter a letter." << endl;
                continue;
            }

            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                cout << "You've already guessed that letter. Try again." << endl;
                continue;
            }

            guessedLetters.push_back(guess);

            bool correctGuess = false;
            for (size_t i = 0; i < selectedWord.length(); ++i) {
                if (selectedWord[i] == guess) {
                    currentDisplay[i] = guess;
                    correctGuess = true;
                }
            }

            if (!correctGuess) {
                --lives;
                ++wrongGuesses;
            }
        }

        // Game over
        if (currentDisplay == selectedWord) {
            cout << "Congratulations, " << playerName << "! You guessed the word: " << selectedWord << endl;
        }
        else {
            drawHangman(wrongGuesses);
            cout << "Game over! The word was: " << selectedWord << endl;
        }

        // Update the leaderboard
        int score = lives * 10;
        vector<pair<string, int>> leaderboard = retrieveLeaderboard("leaderboard.txt");
        leaderboard.push_back(make_pair(playerName, score));
        saveLeaderboard("leaderboard.txt", leaderboard);

        // Display the leaderboard
        displayLeaderboard(leaderboard);

        return 0;
    }
