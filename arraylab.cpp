#include <iostream>
#include <string>
#include <fstream>
#include <conio.h> 
using namespace std;

class Bag
{
private:
    string colors;
    string* items;  
    int size;          
    int capacity;     

    
    void resize() //doubles the array capacity if its full
    {
        int newCapacity = capacity * 2;
        string* newItems = new string[newCapacity];
        for (int i = 0; i < size; i++) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
        capacity = newCapacity;
    }

public:
    Bag(string name, int initialCapacity = 10)
    {
        colors = name;
        size = 0;
        capacity = initialCapacity;
        items = new string[capacity];
    }

    bool loadFromFile(const string& filename)
    {
        ifstream file(filename);
        string line;
        while (getline(file, line)) //this gathers the data from the text file and increases array size if its full by calling resize function
        {
            if (!line.empty())
            {
                if (size == capacity)
                {
                    resize(); 
                }
                items[size++] = line;
            }
        }
        file.close();
        return true;
    }

    void displayAll() //this displays the items from the text file that were loaded into the array 
    {
        for (int i = 0; i < size; i++)
        {
            cout << items[i] << endl;
        }
    }

    bool startsWith(const string& word, const string& prefix) //this checks wether the word typed starts with the same letter as the data in the text file
    {
        if (prefix.length() > word.length()) return false; // checks the length of the word typed vs the words being searched
        for (size_t i = 0; i < prefix.length(); i++)
        {
            char w = word[i];
            char p = prefix[i];
            if (w >= 'A' && w <= 'Z')  // checks the dinstance from the letter a 
                w = w - 'A' + 'a';
            if (p >= 'A' && p <= 'Z')
                p = p - 'A' + 'a';
            if (w != p) 
                 return false;
        }
        return true;
    }

    void search(const string& query) // this displays the text from the file/array that has letters the match the ones entered
    {
        if (query.length() < 3) //move to main fnction
        {
            displayAll();
            return;
        }

        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (startsWith(items[i], query))
            {
                cout << items[i] << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No matches found." << endl;
        }
    }
};

int main() {
    Bag bag("Available Items");

    if (!bag.loadFromFile("text.txt"))
    {
        return 1;
    }

    string input = "";
    char ch;

    while (true)
    {
        if (_kbhit())
        {
            ch = _getch();

            if (isprint(ch)) //if a letter is entered it gets printed
            {
                input.push_back(ch);
            }

            cout << string(50, '\n');
            cout << "---------------------------------\n";
            cout << "I Search: " << input << " I\n";
            cout << "---------------------------------\n";

            if (input.empty())
            {
                bag.displayAll();
            }
            else
            {
                bag.search(input);
            }

            cout << "---------------------------------\n";
        }
    }
    return 0;
}
