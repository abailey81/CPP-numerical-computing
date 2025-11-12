#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

using namespace std;


// Player class definition

// Represents a football player with identity, physical characteristics, skills,
// current position and velocity, and behavior functions for simulation.
class Player {
public:
    // Identity and physical attributes
    string player_name;   // Name of the player
    int number;           // Jersey number
    int height;           // Height in cm
    int weight;           // Weight in kg
    bool left_footed;     // True if player prefers left foot

    // Skill ratings (0–100 scale assumed)
    int speed;
    int stamina;
    int jumping;
    int shooting;
    int passing;
    int dribbling;
    int tackling;
    int marking;
    int strength;

    // 2D Position and Velocity (used for motion simulation)
    float x[2]; // Position on the pitch in meters: x[0] = x, x[1] = y
    float v[2]; // Velocity components: v[0] = vx, v[1] = vy

    // Constructor
    // Sets the name and jersey number; initializes other fields to zero or false
    Player(string name, int num) {
        player_name = name;
        number = num;
        height = 0;
        weight = 0;
        left_footed = false;

        // Initialize all skills to 0
        speed = 0;
        stamina = 0;
        jumping = 0;
        shooting = 0;
        passing = 0;
        dribbling = 0;
        tackling = 0;
        marking = 0;
        strength = 0;

        // Start at origin with no motion
        x[0] = x[1] = 0.0f;
        v[0] = v[1] = 0.0f;
    }

    // Compute average physical ability score
    int get_physical_ability() {
        return (speed + stamina + jumping) / 3;
    }

    // Compute average offensive skill score
    int get_offence_ability() {
        return (shooting + passing + dribbling) / 3;
    }

    // Compute average defensive skill score
    int get_defence_ability() {
        return (marking + tackling + strength) / 3;
    }

    
    // Print all player info in readable format
    void printPlayerInfo() {
        cout << "Player Information" << endl;
        cout << "------------------" << endl;
        cout << "Name: " << player_name << endl;
        cout << "Number: " << number << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Left-footed: " << (left_footed ? "Yes" : "No") << endl;

        cout << "Skills:" << endl;
        cout << "  Speed: " << speed << endl;
        cout << "  Stamina: " << stamina << endl;
        cout << "  Jumping: " << jumping << endl;
        cout << "  Shooting: " << shooting << endl;
        cout << "  Passing: " << passing << endl;
        cout << "  Dribbling: " << dribbling << endl;
        cout << "  Tackling: " << tackling << endl;
        cout << "  Marking: " << marking << endl;
        cout << "  Strength: " << strength << endl;

        cout << "Position: (" << x[0] << ", " << x[1] << ") m" << endl;
        cout << "Velocity: (" << v[0] << ", " << v[1] << ") m/s" << endl;
    }

    // ----------------------
    // Move player forward in time by dt using current velocity
    // ----------------------
    void move() {
        float dt = 0.01f; // fixed small time step in seconds
        x[0] += v[0] * dt; // update x position
        x[1] += v[1] * dt; // update y position
    }

    // ----------------------
    // Update player's velocity vector to a new value
    // ----------------------
    void update_speed(float v_new[2]) {
        v[0] = v_new[0];
        v[1] = v_new[1];
    }
};

#endif // PLAYER_HPP
