#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool startsWithPound(string);
vector<string> scanFile(string, bool);

bool autoFillPath = true;

void generateExecutable(string, string);
void generateSecondary(string, ofstream&);
string removeDotH(string);
string removeDotCPP(string);


string addBackSlashes(string);

string removeQuotes(string);
string startingPath;

string getAdditionalDirectories(string);
string getJustEXE(string);


string getDirectoryPath(string);
string directoryPath;

string EXEFile;

vector<string> vAlreadyCalled;
bool alreadyCalled(string);

vector<string> fileNames;
int main(){

	//Update for non testing purposes
	startingPath = "/home/pi/Documents/Actually Programmed Software/MakeFileMAKERprogram/Helper 2/";
	
	string mainDirectory;
	cout << "Please verify that all custom .h .cpp and .o files, (some .o may not exist) are all in the same folder/directory. Press \"Enter\" when finished.\n";
	cin.ignore();
	
	if(autoFillPath == false){
	cout <<"Assuming all files are in the same folder, please enter the folder directory.\n";
	cout <<"This should look something like \"/home/pi/Documents/Actually Programed Software/\n";
	cout <<"Spaces are fine. Do NOT use backslashes. Do not include main.cpp file. Only directory\n\n";
	getline(cin, startingPath);
	}
	
	cout << "Please Enter the name of your main.cpp file. (This should end in .cpp)\n";
	cout << "\t almost all should have \"/home/pi/Documents/Actually Programmed Software/\" in the title\n";
	cout << "\t for testing purposes and ease of use, it will be assumed your default path is\n";
cout << "\t" << startingPath<<endl;	
		cout << "\t (DO NOT ENTER BACKSLASHES).\n";
	getline(cin, EXEFile);
	//EXEFile = startingPath +EXEFile;
	
	//addBackSlashes(EXEFile);
	
	//getline(cin, mainDirectory);
	mainDirectory = startingPath + getAdditionalDirectories(EXEFile);
	EXEFile = getJustEXE(EXEFile);
	
	cout << "Your file is, \"/home/pi/Documents/Actually Programmed Software/" << EXEFile << "\"\n";
	cout << "Your .h directory is, " << mainDirectory << "\"\n";
	
	cin.ignore();
	cout << "Skipped for now. Please enter select the options you would like to add or subtract by typing their value. Type A to turn all on, N to turn all off, and -1 to finish.\n";
	cout << "Processing, please wait.\n";
	cout << "done.\n\n";
	
	
	//=================================
	//Needs to be adjusted;
	fileNames = scanFile(EXEFile, false);
	cout << "File Scanned";
	generateExecutable(EXEFile,startingPath);
	
	
	}

vector<string> scanFile(string fileName, bool displayLine){
	vector<string> veX;
		ifstream file;
	file.open(fileName);
	
	/*
	if(!file.is_open()){
	cout<<"Unable to open the file."<<endl;

	}
	* */
	
	string line;
	int counter = 1;
	while(getline(file, line))
	{
		bool autoTrue = true;
		
		if(displayLine){
			cout<<line<<endl;
			}
	
		if(line.size() > 0){
			if(startsWithPound(line) == true){
			cout<<line<<endl;
			veX.push_back(removeQuotes(line));
			}else{
				autoTrue = false;
			}
		}else{
			autoTrue = false;
		}
		
		if(autoTrue == false){
			//cout<< counter <<". line Or BlankLine"<<endl;
		}
	
	counter++;
	}
	cout << "Out of while loop" <<endl;
    file.close();
   
   cout <<"\nFileClosed\n";
	for(int i = 0; i < veX.size(); i++){
			cout << veX.at(i) <<endl;
	}
	
	return veX;
	
}
	
	string addBackSlashes(string inputString){
		//cout << "Function \'Add Backslashes\' called successfully" <<endl;
		string tempString1 = "";
			for (int i = 0; i < inputString.size(); i++){
					if(inputString.at(i) == ' '){
						tempString1 += '\\';
					}
							//cout << "\t Looping Through \'Add Backslashes\' successfully" <<endl;
					tempString1 += inputString.at(i);
					
				}
				inputString = tempString1;
				//cout << "\t \'Add Backslashes\' finished successfully" <<endl;
				return tempString1;
		}
		
bool startsWithPound(string s){
	if (s.at(0) != '#'){
		return false;
	}
	string r; 
	string INCLUDE = "include ";
	for(int i = 1; i < 9 && s.size() >= 8; i++){
		r += s.at(i);
		}
		
		if(r != INCLUDE){
			return false;
			}
	
	for(int i = 0; i < s.size(); i++){
		if (s.at(i) == '<'){
			return false;
		}
	}
	return true;
				
}

string removeQuotes(string r){
		bool start = false;
		bool end = false;
		string s2;
		
		for(int i =0; i < r.size(); i++){
		
			if(r.at(i) == '"'){
				if(start == false){
					start = true;	
				}else{
					return s2;
				}
				continue;
			}
			
			if(start == true && end == false){
				s2 += r.at(i);
			}
		}
		
		return s2;
	}


//fileName + startingPath
void generateExecutable(string s, string sP){
	string justName = "";
	
	//starting at end working backward, find the highest position of a forward slash
	//^
	//int startPos = -1;
	
	/*
	
	//Get File Name
	for(int i = s.size() -1; i >= 0; i--){
		//cout << "In first loop of generateEx\n";
		if(s.at(i) == '/'){
				startPos = i;
				break;
		}
	}
	
	
	
	//one after start pos b/c sp is /
	startPos++;
	
	
	for(int i = startPos; i < s.size(); i++){
		//if(s.at(i) == '.'){
			//break;
		//}
		justName += s.at(i);
	}
	*/
	justName = s;
	
	//cout << "file name (before removeCPP) is ... "<< justName <<endl; 
	justName = removeDotCPP(justName);
	
	justName = addBackSlashes(justName);
	
	cout << "file name is ... "<< justName <<endl; 
	
	//===Actually Create makefile.
	string mfName = startingPath + "makefile";
	ofstream myFile(mfName);
	
	myFile << justName<<": "<<justName<<".o ";
	for(int i = 0; i < fileNames.size(); i++){
		string tempString = getDirectoryPath(s)+ fileNames.at(i);
			myFile << addBackSlashes(removeDotH(tempString)) <<".o ";
	}
	myFile << endl;
	
	//Just name already has backslashes in it
	myFile << "\tg++ -Wall -g -o "<<justName << " " <<justName<<".o ";
	
	
	for(int i = 0; i < fileNames.size(); i++){
		string tempString = getDirectoryPath(s) + fileNames.at(i);
			myFile << addBackSlashes(removeDotH(tempString))  <<".o ";
	}
	myFile << endl <<endl;
	
	myFile << justName << ".o: " << justName << ".cpp ";
	for(int i = 0; i < fileNames.size(); i++){
		string tempString = getDirectoryPath(s) + fileNames.at(i);
			myFile << addBackSlashes(tempString) << " ";
		}
		myFile <<endl;
		
		//Pretty sure we only need g++ of cpp with main function file
		//myFile << "\tg++ -Wall -c -g "<<justName << ".cpp";
			myFile << "\tg++ -Wall -c -g "<<justName << ".cpp";
		
		myFile << endl <<endl;
		//cout << "========================" <<endl;
			//cout << "\t\tGenerating Executable for " << s <<endl;
			//cout << "========================" <<endl;
		//I believe issue is that the machine can't find code because it doesn't have source.
		//How can we add source?
	string tempString;
	for(int i = 0; i <fileNames.size(); i++){
		tempString = getDirectoryPath(s) + fileNames.at(i);
			if(alreadyCalled(fileNames.at(i)) == false){
				vAlreadyCalled.push_back(fileNames.at(i));
				generateSecondary(tempString, myFile);
			}
	}
	
}
	
string removeDotH(string s){
		int endPoint = -1;
		for (int i = s.size()-1; i >= 0; i--){
				if(s.at(i) == '.'){
				endPoint = i;
				break;	
				}
		}
		//endpoint--;
		if(endPoint == -1){
			return s;
		}
		string s2 = "";
		for(int i = 0; i < endPoint; i++){
				s2 += s.at(i);
		}
		
		//cout <<endl << "Test of remove .h << " << s2 <<endl;
		return s2;
	}	
	
	void generateSecondary(string s, ofstream& myFile){
		myFile << addBackSlashes(removeDotH(s)) <<".o: "<< addBackSlashes(s) << " ";
		
			string s2 = getDirectoryPath(EXEFile) + s;
		cout << "\t\tGenerating Secondary for " << s <<endl;
		
		//Don't use s2 b/c already has path
			vector<string> v2 = scanFile(s, true);
			
			cout << "libraries in this file are: ";
			for(int i = 0; i < v2.size(); i++){
				cout << v2.at(i) <<endl;
				string tempString = getDirectoryPath(EXEFile)+ v2.at(i);
					myFile << addBackSlashes(tempString) << " "; 
			}
			cout <<endl;
			//myFile << endl <<"\t";
			//myFile << "g++ -Wall -g -c "<< s <<".cpp";
			
			myFile <<endl<<endl;
			
			
			//Should probably seperate grab files from generate names.
			for(int i = 0; i <v2.size(); i++){
				string tempString = getDirectoryPath(v2.at(i)) + fileNames.at(i);
				if(alreadyCalled(v2.at(i)) == false){
					vAlreadyCalled.push_back(v2.at(i));
					generateSecondary(tempString, myFile);
				}
			}
			 
	}



string removeDotCPP(string s){
	string returnName ="";
	returnName = s;
	
	//find the last dot
	for(int i = s.size()-1; i >= 0; i--){
		returnName.pop_back();
			if(s.at(i) == '.'){
				//cout << "Found the dot!\n";
				break;	
			}
	}
	//cout << "Exited For loop."<<endl;;
	return returnName;
}

string getDirectoryPath(string fullFileName){
	string tempString = "";
	int startingPos = -1;
	for(int i = fullFileName.size()-1; i >= 0; i--){
		if(fullFileName.at(i) == '/'){
			startingPos = i;
			break;
		}
	}
	for(int i = 0; i <= startingPos; i++){
			tempString += fullFileName.at(i);
	}
	return tempString;
}

bool alreadyCalled(string s){
	for(int i = 0; i < vAlreadyCalled.size(); i++){
			if(s == vAlreadyCalled.at(i)){
				return true;
				}
		}
		return false;
}

string getAdditionalDirectories(string s){
	cout << "starting additional directories\n";
	string s2;
	bool start = false;
	for(int i = s.size()-1; i >= 0; i--){
		if(start == false) {
			if(s.at(i) == '/'){
			s2+= s.at(i);
			start = true;
			}
		}else{
			s2 += s.at(i);
		}
	}
	string s3;
	for(int i = s2.size()-1; i >= 0; i--){
		s3 += s2.at(i);
	}
	
	return s3;
}

string getJustEXE(string s){
cout << "starting just EXE\n";
	string s2;
	int startingPoint;
	for(int i = s.size()-1; i >= 0; i--){
		
			if(s.at(i) == '/'){
			s2+= s.at(i);
			startingPoint = ++i;
			break;
			}
		
	}
	string s3;
	for(int i = startingPoint; i < s2.size(); i++){
		s3 += s2.at(i);
	}
	cout << "finishing just EXE\n";
	return s3;
}
