#include "prepare_file.h"

string initializedocument(string document_name, string title){
	ofstream fout(document_name);

	fout << "UNIVERSIDADE ESTADUAL DE CAMPINAS\n";
	fout << title << "\n\n";
	fout.close();

	return document_name;
}
void createtable( string file_name, vector<string>& fields){
	fstream fout(file_name);
	fout.seekp(0, ios::end);
	for(uint i = 0; i < fields.size()-1; i++){
		fout << fields[i] << " | ";
	}
	fout << fields[fields.size()-1] << "\n";
	fout.close();
}
void inputentry(string file_name, vector<int>& fields){
	fstream fout(file_name);
	fout.seekp(0, ios::end);
	for(uint i = 0; i < fields.size();i++){
		fout << fields[i] << " ";
	}
	fout << '\n';
	fout.close();
}
