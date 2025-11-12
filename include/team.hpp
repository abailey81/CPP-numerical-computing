#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include <list>
#include "player.hpp" // Includes Player class

using namespace std;


// Team class definition

// Manages a list of Player objects, storing team name, colour, and utility
// functions for accessing player data and computing team ability ratings.

class Team {
private:
    
    // Private attributes: team identity and players
    
    string name;              // Name of the team
    string colour;            // Team's primary kit colour
    list<Player> playerList;  // Container of Player objects (std::list used here)

public:
    
    // Constructor
    
    // Initializes team with name, colour, and optional player list
    Team(string team_name, string team_colour, list<Player> players = {}) {
        name = team_name;
        colour = team_colour;
        playerList = players;
    }

    
    // Accessor (getter) functions
    string getName() { return name; }
    string getColour() { return colour; }
    list<Player> getPlayerList() { return playerList; }

    
    // Mutator (setter) functions
    void setName(string new_name) { name = new_name; }
    void setColour(string new_colour) { colour = new_colour; }
    void setPlayerList(list<Player> players) { playerList = players; }

    
    // Add a player to the beginning of the list
    
    void addPlayer(Player new_player) {
        playerList.push_front(new_player);
    }

    
    // Print number and name of each player 
    void printPlayerList() {
        for (Player p : playerList) {
            cout << p.number << " : " << p.player_name << endl;
        }
    }

    
    // Return number of players in the team  
    int getNumPlayers() {
        return playerList.size();
    }

    
    // Average team ability functions

    // Compute average physical ability across all players
    int get_physical_ability() {
        if (playerList.empty()) return 0;
        int total = 0;
        for (Player p : playerList) {
            total += p.get_physical_ability();
        }
        return total / playerList.size();
    }

    // Compute average offensive ability
    int get_offence_ability() {
        if (playerList.empty()) return 0;
        int total = 0;
        for (Player p : playerList) {
            total += p.get_offence_ability();
        }
        return total / playerList.size();
    }

    // Compute average defensive ability
    int get_defence_ability() {
        if (playerList.empty()) return 0;
        int total = 0;
        for (Player p : playerList) {
            total += p.get_defence_ability();
        }
        return total / playerList.size();
    }
};

#endif // TEAM_HPP
