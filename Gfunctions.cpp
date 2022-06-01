#include "Header-files/Gfunctions.h"
#include "Header-files/Functions.h"

using namespace std;

void getChoice(int& choice,  const string menu_str, const int stream_size)
{
    cout << menu_str;

    cout << "Choice: ";
    cin >> setw(stream_size) >> choice;

    while (cin.fail())
    {
        cout << "\n" << gui::menu_divider();
        cout << "Faulty input!" << "\n";
        cout << "\n" << gui::menu_divider();

        cin.clear();
        cin.ignore(INT_MAX, '\n');

        cout << "ENTER to continue...";
        cin.get();
        cout << "\n" << gui::menu_divider();

        cout << menu_str;

        cout << "Choice: ";
        cin >> setw(stream_size) >> choice;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout << "\n" << gui::menu_divider();
}