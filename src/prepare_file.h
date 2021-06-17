#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string initializedocument(string document_name, string title = "Posições Rastreadas dos dados experimentais");
void createtable( string file_name, vector<string>& fields);
void inputentry(string file_name, vector<int>& fields);
