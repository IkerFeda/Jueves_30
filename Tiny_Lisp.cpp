#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {}
    void set_text(const string &text) { cout << text << endl; }
};

void load_script(const string& filename, bool show_script = false)
{
    string script;
    ifstream file(filename, ios::binary);
    if (!file)
    {
        throw runtime_error("Error de apertura de " + filename);
    }

    char buf[4001];
    while (file.read(buf, 4000))
    {
        buf[file.gcount()] = '\0';
        script.append(buf);
    }
    file.close();

    if (show_script)
    {
        cout << ColorConsole::fg_blue << ColorConsole::bg_white;
        cout << script << endl;
    }

    ConsoleBox consoleBox;
    consoleBox.new_text();
    consoleBox.set_text(script);
}

int main() {
    string filename;
    cout << "Archivo: ";
    cin >> filename;

    try {
        load_script(filename, true);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const ifstream::failure& e) {
        cerr << "Error de lectura del archivo: " << e.what() << endl;
    } catch (...) {
        cerr << "Error desconocido" << endl;
    }

    return 0;
}