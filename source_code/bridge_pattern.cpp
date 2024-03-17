#include <iostream>
#include <memory>
#include <string>

using namespace std;

// World interface (Implementor)
class World {
private:
    string name; // Name of the world
    int difficultyLevel; // Difficulty level of the world

public:
    World(const string& name, int difficulty) : name(name), difficultyLevel(difficulty) {}

    virtual string resolveBattle() = 0;
    virtual string exploreArea() = 0;
    virtual string interactWithEnvironment() = 0;

    string getName() const { return name; }
    int getDifficultyLevel() const { return difficultyLevel; }

    virtual ~World() {}
};

// Concrete Implementor for FantasyWorld
class FantasyWorld : public World {
public:
    FantasyWorld() : World("Fantasy World", 3) {}

    string resolveBattle() override {
        return "fights the dragon!";
    }

    string exploreArea() override {
        return "explores the enchanted forest!";
    }

    string interactWithEnvironment() override {
        return "talks to the village elder.";
    }
};

// Concrete Implementor for SciFiWorld
class SciFiWorld : public World {
public:
    SciFiWorld() : World("Sci-Fi World", 5) {}

    string resolveBattle() override {
        return "engages in a space battle with aliens!";
    }

    string exploreArea() override {
        return "scans the surface of a new planet.";
    }

    string interactWithEnvironment() override {
        return "hacks the mainframe of the spaceship.";
    }
};

// Player abstraction
class Player {
private:
    string playerName;
    int health;

protected:
    unique_ptr<World> world;

public:
    Player(unique_ptr<World> w, const string& name, int health)
        : world(move(w)), playerName(name), health(health) {}

    virtual void fight() {
        cout << playerName << " (" << describeAction(world->resolveBattle()) << ")" << endl;
    }

    virtual void explore() {
        cout << playerName << " (" << describeAction(world->exploreArea()) << ")" << endl;
    }

    virtual void interact() {
        cout << playerName << " (" << describeAction(world->interactWithEnvironment()) << ")" << endl;
    }

    virtual string describeAction(const string& action) = 0;

    virtual ~Player() = default;
};

// Concrete Player class for Male
class Male : public Player {
public:
    using Player::Player;

    string describeAction(const string& action) override {
        return "The male player " + action;
    }
};

// Concrete Player class for Female
class Female : public Player {
public:
    using Player::Player;

    string describeAction(const string& action) override {
        return "The female player " + action;
    }
};

// Client code
int main() {
    unique_ptr<World> fantasyWorld = make_unique<FantasyWorld>();
    unique_ptr<World> sciFiWorld = make_unique<SciFiWorld>();

    Male malePlayer(move(fantasyWorld), "Arthur", 100);
    Female femalePlayer(move(sciFiWorld), "Athena", 100);

    malePlayer.fight();
    malePlayer.explore();
    malePlayer.interact();

    femalePlayer.fight();
    femalePlayer.explore();
    femalePlayer.interact();
}
