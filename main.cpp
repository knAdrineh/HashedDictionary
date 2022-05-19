/*
 Adrineh Khodaverdian
 Professor Biehl
 CS/IS 212
 Lab 6
 */

#include <iostream>
#include <string>
#include "HashedDictionary.h"

#include <fstream>
#include <iomanip>
#include <cmath>


using namespace std;

void printMenu();
void my_function(int& i);
void print_table(HashedDictionary<string, int>);

int main()
{
    HashedDictionary<string, int> table;
    int age; //person age
    string name; //person name
    int choice =-1; //menu choice
    bool found = false; //boolean variable for found file or not
    ifstream inFile; //input file name
    ofstream outFile; //output file name
    string file_name; //user input for file name
    string name_search; //the name for
    double sum = 0;
    double avg  = 0;
    int count = 0;
    double alpha_loader = 1;

    //while loop takes data from file adds it to a table
    while(!found){ //making sure it will ask until it found the file
        try{
            //ask the user to input file name
            cout<< "Enter file name to begin (hint: data.txt) : " ;
            getline(cin,file_name);
            inFile.open(file_name);
            if(!inFile.is_open())
                throw 404;
            while (!inFile.eof()) {
                inFile >> age;
                inFile.ignore();
                getline(inFile,name,'\n');
                table.add(name, age);
                sum+=age;

            }
            inFile.close();
            found = true;
        }
        catch(int err){//throws an exception to avoid crashing incase file not found
            cout << file_name << " couldn't be found" << endl;
            found = false;
        }
    }
    
   
    //user menu choice
    while(choice != 0){
       
        printMenu();
        cout << "Enter choice to continue or 0 to quit : ";
        cin >> choice;
        switch(choice){
            case 0: 
                break;
            case 1: //print hash table
                if(!table.isEmpty()){
                    table.traverse(my_function);
                    //see the efficienty
                    count = table.getNumberOfItems();
                    alpha_loader = (double)count/(double)TABLE_SIZE;
                    avg = sum /count;
                    cout << endl;
                    cout << "Average age is " <<  setw(2) << setprecision(2) <<avg << endl;
                    cout << "Alpha = "  << setw(2) << setprecision(2) << alpha_loader << endl <<endl;
                }
                else{
                    cout << "Table is Empty add items to preview the table " <<endl;
                }
                break;
            case 2: //retrieve hash item
                cin.ignore();
                cout << "Enter name_search to get age or Q to exit" <<endl;
                getline(cin,name_search);
                while(name_search!= "Q" && name_search!= "q" ){
                    if(name_search != "Q" && name_search != "q"){
                        if(table.contains(name_search))
                            cout << name_search << " is " << table.getItem(name_search) << "."<< endl;
                        else
                            cout << "No such name_search exists in the database." <<endl;
                        cout << "Enter name_search to get age or Q to exit" <<endl;
                        getline(cin,name_search);
                    }
                }
                break;
            case 3: //delete item
                cin.ignore();
                if(!table.isEmpty()){
                    cout << "Enter name_search value to delete or Q to exit" <<endl;
                    getline(cin,name_search);
                    while(name_search != "Q" && name_search != "q" ){
                        if( name_search != "Q" && name_search != "q"){
                            if(table.contains(name_search)){
                                sum-=table.getItem(name_search);
                                count-=1;
                                table.remove(name_search);
                                cout <<name_search << " was removed from database." << endl;
                               
                                
                            }
                            else
                                cout << "NO such name search exits " << endl;
                        }
                        cout << "Enter name_search value to delete or Q to exit" <<endl;
                        getline(cin,name_search);
                    }
                }
                else{
                    cout << "Table is empty no elements to delete "<< endl;
                }
              
                break;
            case 4: //read names from file
                inFile.open(file_name);
                cin.ignore();
                while (!inFile.eof()) {
                    inFile >> age;
                    inFile.ignore(); //skipping the space
                    getline(inFile,name,'\n');
                    cout << name << endl;
                }
                inFile.close();
                break;
            case 5: //save names to file
                cin.ignore();
                if(!table.isEmpty()){
                    cout << "Enter fileName to save names to : ";
                    getline(cin,file_name);
                    if(table.save2File(file_name))
                        cout << "Names saved to File" << endl;
                    else
                        cout << "File couldn't be saved" << endl;
                    break;
                case 6: //add item

                    while(name != "Q" && name != "q" ){
                        cin.ignore();
                        cout << "Enter name to Add or Q to exit" <<endl;
                        getline(cin, name);
         
                        if( name != "Q" && name != "q"){
                            cout << "Enter Age : ";
                            cin >> age;
                            table.add(name, age);
                            sum+=age;
                            count+=1;
                        }
                    }
                }
                else{
                    cout << "No data to be saved to the file "  << endl;
                }
                break;
            default: //invalid entry
                cout << "Invalid Entry " << endl;
                break;
        }
    }
    
    
    system("pause");
}

void printMenu(){
    cout << "1 – print hash table\n";
    cout << "2 – retrieve hash item\n";
    cout << "3 – delete item\n";
    cout << "4 – read names from file\n";
    cout << "5 – save names to file\n";
    cout << "6 - add item\n";
    cout << "0 – quit\n";
    
}

void my_function(int& i){
    cout << " "<< i << endl;
}


