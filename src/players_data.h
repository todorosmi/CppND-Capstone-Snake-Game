#ifndef PLAYERS_DATA_H
#define PLAYERS_DATA_H

#include <iostream>
#include <string>

using::std::string;

class PlayersData {

public:
    void scoreTrack(int score1, int score2);
/*     void writeToScoreFile(string path, string name, float score);
    bool ReadFromScoreFile(string path); */
    void setName1(string name);
    string getName1();
    void setName2(string name);
    string getName2();   

private:
    string _name1;
    string _name2;

};

#endif