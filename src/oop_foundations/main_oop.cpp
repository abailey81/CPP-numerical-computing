#include "player.hpp"
#include "team.hpp"

int main() {
    // Create a few Player objects
    Player p1("Alex Morgan", 13);
    p1.speed = 85;
    p1.stamina = 90;
    p1.jumping = 80;
    p1.shooting = 88;
    p1.passing = 92;
    p1.dribbling = 87;
    p1.tackling = 40;
    p1.marking = 45;
    p1.strength = 60;

    Player p2("Leah Williamson", 6);
    p2.speed = 70;
    p2.stamina = 75;
    p2.jumping = 72;
    p2.shooting = 65;
    p2.passing = 68;
    p2.dribbling = 70;
    p2.tackling = 80;
    p2.marking = 85;
    p2.strength = 90;

    // Create a team and add players
    Team team("The Invincibles", "Red");

    team.addPlayer(p1);
    team.addPlayer(p2);

    // Print player list
    cout << "=== Team: " << team.getName() << " (" << team.getColour() << ") ===" << endl;
    cout << "Players:" << endl;
    team.printPlayerList();

    // Print team ability scores
    cout << endl;
    cout << "Team Physical Ability: " << team.get_physical_ability() << endl;
    cout << "Team Offence Ability:  " << team.get_offence_ability() << endl;
    cout << "Team Defence Ability:  " << team.get_defence_ability() << endl;

    return 0;
}
