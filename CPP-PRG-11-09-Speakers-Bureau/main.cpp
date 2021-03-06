//
//  main.cpp
//  CPP-PRG-11-09-Speakers-Bureau
//
//  Created by Keith Smith on 11/8/17.
//  Copyright © 2017 Keith Smith. All rights reserved.
//
//  Write a program that keeps track of a speaker's bureau. The program should use a
//  structure to store the following data about a speaker:
//
//      Name
//      Telephone Number
//      Speaking Topic
//      Fee Required
//
//  The program should use an array of at least 10 structures. It should let the user enter
//  data into the array, change the contents of any element, and display all the data stored
//  in the array. The program should have a menu-driven user interface.
//
//  Input Validation: When the data for a new speaker is entered, be sure the user enters
//  data for all the fields. No negative amounts should be entered for a speaker's fee.

#include <iostream>

using namespace std;

const int INT_ARR_SIZE = 10;

struct StructSpeakerData
{
    string strName;
    string strPhoneNumber;
    string strSpeakingTopic;
    double dblFeeRequired;
};

void manipulateArray(StructSpeakerData *);
int *displayMainMenu();
int *selectElement();
StructSpeakerData *enterSpeakerInfo(StructSpeakerData *, int *);
StructSpeakerData *editSpeakerInfo(StructSpeakerData *, int *);
int *displayEditMenu();
bool *validatePhoneNumber(string *);
void displaySpeakerInfo(StructSpeakerData *, int *);
void displayAllSpeakersInfo(StructSpeakerData *);


int main()
{
    StructSpeakerData *ssdSpeakersArray = nullptr;
    ssdSpeakersArray = new StructSpeakerData[INT_ARR_SIZE];
    
    manipulateArray(ssdSpeakersArray);
    
    return 0;
}

void manipulateArray(StructSpeakerData *ssdSpeakerArr)
{
    int *intArrElement = nullptr;
    intArrElement = new int;
    
    switch(*displayMainMenu())
    {
        case 1:
            intArrElement = selectElement();
            *intArrElement -= 1;
            enterSpeakerInfo(&ssdSpeakerArr[*intArrElement], intArrElement);
            manipulateArray(ssdSpeakerArr);
            break;
        case 2:
            intArrElement = selectElement();
            *intArrElement -= 1;
            editSpeakerInfo(&ssdSpeakerArr[*intArrElement], intArrElement);
            manipulateArray(ssdSpeakerArr);
            break;
        case 3:
            displayAllSpeakersInfo(ssdSpeakerArr);
            manipulateArray(ssdSpeakerArr);
            break;
        case 4:
            cout << "\nYou have exited the program.\n\n";
            break;
        default:
            break;
    }
}


int *displayMainMenu()
{
    int *intChoice = nullptr;
    intChoice = new int;
    
    cout << "\nPlease select from the following menu options:\n";
    cout << "\t1. Enter speaker information.\n";
    cout << "\t2. Edit speaker information.\n";
    cout << "\t3. Display all speaker information.\n";
    cout << "\t4. Exit.\n";
    cout << "Please make your selection: ";
    cin >> *intChoice;
    while(!cin || *intChoice < 1 || *intChoice > 4)
    {
        cout << "Please select from the menu options: ";
        cin.clear();
        cin.ignore();
        cin >> *intChoice;
    }
    
    return intChoice;
}

int *selectElement()
{
    int *intElement = nullptr;
    intElement = new int;
    
    cout << "Please select a speaker's number (1 - " << INT_ARR_SIZE << "): ";
    cin >> *intElement;
    while(!cin || *intElement < 1 || *intElement > INT_ARR_SIZE)
    {
        cout << "Please select an speaker number between 1 and " << INT_ARR_SIZE << ": ";
        cin.clear();
        cin.ignore();
        cin >> *intElement;
    }
    
    return intElement;
}

StructSpeakerData *enterSpeakerInfo(StructSpeakerData *ssdSpeaker, int *intElement)
{
    cout << "Please enter the following information for speaker #" << (*intElement + 1) << ":\n";
    
    cin.ignore();
    cout << "\tName: ";
    getline(cin, ssdSpeaker->strName);
    
    cout << "\tTelephone number: ";
    getline(cin, ssdSpeaker->strPhoneNumber);
    while (ssdSpeaker->strPhoneNumber.length() != 12 || !*validatePhoneNumber(&ssdSpeaker->strPhoneNumber))
    {
        cout << "\tPlease enter a valid phone number\n";
        cout << "\tin the form XXX-XXX-XXXX: ";
        getline(cin, ssdSpeaker->strPhoneNumber);
    }
    
    cout << "\tSpeaking topic: ";
    getline(cin , ssdSpeaker->strSpeakingTopic);
    
    cout << "\tFee required: $";
    cin >> ssdSpeaker->dblFeeRequired;
    while (!cin || ssdSpeaker->dblFeeRequired < 0 || ssdSpeaker->dblFeeRequired > 10000)
    {
        cout << "Please enter a value between $0 and $10,000: $";
        cin.clear();
        cin.ignore();
        cin >> ssdSpeaker->dblFeeRequired;
    }
    
    return ssdSpeaker;
}

StructSpeakerData *editSpeakerInfo(StructSpeakerData *ssdSpeaker, int *intElement)
{
    int *intSelection = nullptr;
    intSelection = new int;
    *intSelection = -1;
    
    cout << "\nPlease edit the following information for speaker #" << (*intElement + 1) << ":\n";
    
    while(*intSelection != 5)
    {
        intSelection = displayEditMenu();
        
        switch(*intSelection)
        {
            case 1:
                cin.clear();
                cin.ignore();
                cout << "\tCurrent name: " << ssdSpeaker->strName << endl;
                cout << "\tName: ";
                getline(cin, ssdSpeaker->strName);
                break;
            case 2:
                cout << "\tCurrent phone number: " << ssdSpeaker->strPhoneNumber << endl;
                cout << "\tNew phone number: ";
                cin.clear();
                cin.ignore();
                getline(cin, ssdSpeaker->strPhoneNumber);
                while (ssdSpeaker->strPhoneNumber.length() != 12 || !*validatePhoneNumber(&ssdSpeaker->strPhoneNumber))
                {
                    cout << "\tPlease enter a valid phone number\n";
                    cout << "\tin the form XXX-XXX-XXXX: ";
                    cin.clear();
                    cin.ignore();
                    getline(cin, ssdSpeaker->strPhoneNumber);
                }
                break;
            case 3:
                cout << "\tCurrent speaking topic: " << ssdSpeaker->strSpeakingTopic << endl;
                cout << "\tNew speaking topic: ";
                cin.clear();
                cin.ignore();
                getline(cin , ssdSpeaker->strSpeakingTopic);
                break;
            case 4:
                cout << "\tCurrent fee: $" << ssdSpeaker->dblFeeRequired << endl;
                cout << "\tFee required: $";
                cin.clear();
                cin.ignore();
                cin >> ssdSpeaker->dblFeeRequired;
                while (!cin || ssdSpeaker->dblFeeRequired < 0 || ssdSpeaker->dblFeeRequired > 10000)
                {
                    cout << "Please enter a value between $0 and $10,000: $";
                    cin.clear();
                    cin.ignore();
                    cin >> ssdSpeaker->dblFeeRequired;
                }
                break;
            case 5:
                break;
            default:
                break;
        }
    }
    
    cout << "\nYou have returned to the main menu.\n";
    
    return ssdSpeaker;
}

int *displayEditMenu()
{
    int *intChoice = nullptr;
    intChoice = new int;
    
    cout << "\nPlease select a menu item to edit:\n";
    cout << "\t1. Name.\n";
    cout << "\t2. Phone number.\n";
    cout << "\t3. Speaking topic.\n";
    cout << "\t4. Fee required.\n";
    cout << "\t5. Exit.\n";
    cout << "Please make your selection: ";
    cin >> *intChoice;
    while(!cin || *intChoice < 1 || *intChoice > 5)
    {
        cout << "Please select from the menu options: ";
        cin.clear();
        cin.ignore();
        cin >> *intChoice;
    }
    
    return intChoice;
}

bool *validatePhoneNumber(string *strPhone)
{
    bool *booIsValid = nullptr;
    booIsValid = new bool;
    *booIsValid = false;
    
    char *chrArr = nullptr;
    chrArr = new char[12];
    
    strcpy(chrArr, strPhone->c_str());
    
    for (int i = 0 ; i < 12 ; i++)
    {
        if (i == 3 || i == 7)
        {
            if (chrArr[i] == '-')
            {
                *booIsValid = true;
            }
            else if (chrArr[i] != '-')
            {
                *booIsValid = false;
                break;
            }
        }
        else if (i != 3 || i != 7)
        {
            if (isdigit(chrArr[i]) == false)
            {
                *booIsValid = false;
                break;
            }
            else if (isdigit(chrArr[i]) == true)
            {
                *booIsValid = true;
            }
        }
    }
    
    return booIsValid;
}

void displaySpeakerInfo(StructSpeakerData *ssdSpeaker, int *intElement)
{
    cout << "\nThis is the information entered for speaker #" << (*intElement + 1) << ":\n";
    
    cout << "\tName: ";
    cout << ssdSpeaker->strName << endl;
    
    cout << "\tTelephone number: ";
    cout << ssdSpeaker->strPhoneNumber << endl;
    
    cout << "\tSpeaking topic: ";
    cout << ssdSpeaker->strSpeakingTopic << endl;
    
    cout << "\tFee required: $";
    cout << ssdSpeaker->dblFeeRequired << endl;
}

void displayAllSpeakersInfo(StructSpeakerData *ssdSpeakers)
{
    int *intIndex = nullptr;
    intIndex = new int;
//    *intIndex = 0;
    
    for (*intIndex = 0 ; *intIndex < INT_ARR_SIZE ; *intIndex += 1)
    {
        displaySpeakerInfo(&ssdSpeakers[*intIndex], intIndex);
    }
}

