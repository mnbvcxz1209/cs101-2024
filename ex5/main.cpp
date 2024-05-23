#include <iostream>
#include <string>
using namespace std;

class myString {
    private:
        string m_str;
    public:
        myString(string s) {
            m_str = s;
        }
};

class ReadClass {
    private:
        string classNames;
        int classCount;
    public:
        ReadClass() : classCount(0) {}

        void readFile(const string& filename) {
            FILE *file = fopen(filename.c_str(), "r");
            if (!file) {
                cerr << "Error: Could not open file " << filename << endl;
                return;
            }

            char line[256];
            while (fgets(line, sizeof(line), file)) {
                string strLine(line);
                size_t pos = strLine.find("class ");
                if (pos != string::npos) {
                    if ((pos == 0 || !isalnum(strLine[pos - 1])) &&
                        (pos + 5 < strLine.size() && !isalnum(strLine[pos + 5]))) {
                        size_t start = pos + 6; 
                        size_t end = strLine.find_first_of(" \n{", start);
                        if (end != string::npos) {
                            string className = strLine.substr(start, end - start);
                            if (!className.empty() && isalpha(className[0])) {
                                classNames += "class " + className + "\n";
                                classCount++;
                            }
                        }
                    }
                }
            }
            fclose(file);
        }

         void showClass() {
            cout << classCount << " class" << " in main.cpp\n";
            cout << classNames;
        }
};

int main() {
    ReadClass rfile;
    rfile.readFile("main.cpp");
    rfile.showClass();
    return 0;
}
