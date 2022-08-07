#include <unistd.h>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

#include "players_data.h"
#include "game.h"

using::std::string;

void PlayersData::setName1(string name){
    _name1 = name;
}
string PlayersData::getName1(){
    return _name1;
}
void PlayersData::setName2(string name){
    _name2 = name;
}
string PlayersData::getName2(){
    return _name2;
}
//bool PlayersData::ReadFromScoreFile(string path);

void PlayersData::scoreTrack(int score1, int score2){ 
    std::ifstream finput;
    std::ofstream foutput;
    finput.open("../src/data.txt");
    foutput.open ("../src/data.txt", std::ios::app); 
    if (foutput.is_open()) {
        foutput << "\n";
        foutput << _name1 << "      " << score1;
        if(!_name2.empty()){
            foutput << "\n";
            foutput << _name2 << "      " << score2;
        }
    }
    finput.close();
    foutput.close();
    return;
}