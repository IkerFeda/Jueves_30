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

// Función para eliminar códigos de escape ANSI del texto
string removeANSIEscapeCodes(const string& input)
{
    string output;
    size_t index = 0;
    while (index < input.size())
    {
        if (input[index] == '\033' && input[index + 1] == '[')
        {
            while (index < input.size() && input[index] != 'm')
            {
                ++index;
            }
            ++index; // avanzar después de 'm'
        }
        else
        {
            output += input[index++];
        }
    }
    return output;
}

void load_script(const string& filename, bool show_script = false)
{
    ifstream file(filename, ios::binary);
    if (!file)
    {
        throw runtime_error("Error de apertura de " + filename);
    }

    string script((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    if (show_script)
    {
        ConsoleBox consoleBox;
        consoleBox.new_text();

        string processed_script = removeANSIEscapeCodes(script); // Eliminar códigos de escape ANSI
        consoleBox.set_text(processed_script); // Mostrar el texto procesado sin códigos de escape
    }
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