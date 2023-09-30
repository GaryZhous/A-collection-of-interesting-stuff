#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
using namespace std;

int main() {
    unordered_map<std::string, std::string> companyStatusMap;
    string companyName;
    string companyStatus;
    
    cout << "Enter company information. Type 'quit' to finish.\n";
    
    while(1) {
        cout << "Enter company name: ";
        getline(cin, companyName);
        cin.igonre();
        
        if(companyName == "quit") {
            break;
        }
        
        cout << "Enter company status: ";
        getline(cin, companyStatus);
        cin.ignore();
        
        companyStatusMap[companyName] = companyStatus;
    }
    
    ofstream outFile("company_status.csv");
    if(!outFile.is_open()) {
        cerr << "Unable to open file for writing!\n";
        return 1;
    }
    
    outFile << "Company Name,Application Status\n";
    for(const auto& pair: companyStatusMap) {
        outFile << "\"" << pair.first << "\",\"" << pair.second << "\"\n";
    }
    
    outFile.close();
    cout << "Company information has been written to company_status.csv\n";
    return 0;
}
