// Kirsten Richards
// 4-29-25
// Using DS: Choose Your Own Adventure Game!

#include <fstream>
#include <sstream>
#include "LinkedList.h"

void introduction() {
    cout << "Welcome to the Castle Adventure!\n";
    cout << "You will navigate through various rooms in the castle, encountering challenges and making decisions that will determine your path.\n";
    cout << "Choose your actions wisely. Let's start your journey!\n\n";
}

int main() {
    LinkedList castleRooms;
    ifstream file("rooms.csv");
    string line;

    // Reading rooms from the CSV file
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string name, description, actionsStr, item;
            vector<string> actions;

            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, actionsStr, ',');
            getline(ss, item);

            stringstream actionStream(actionsStr);
            string action;
            while (getline(actionStream, action, ';')) {
                actions.push_back(action);
            }

            Room newRoom(name, description, actions, item);
            castleRooms.addRoom(newRoom);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    // Introduction
    introduction();

    // Interaction with rooms
    auto current = castleRooms.getHead();
    while (current != nullptr) {
        cout << current->room.toString() << endl;

        // Display actions for the current room
        int actionNum = 1;
        for (const auto& action : current->room.getActions()) {
            cout << actionNum++ << ". " << action << endl;
        }

        // User chooses an action
        int choice;
        cout << "Choose an action (1-" << current->room.getActions().size() << "): ";
        cin >> choice;

        // Process choice
        if (choice < 1 || choice > current->room.getActions().size()) {
            cout << "Invalid choice. Try again.\n";
        } else {
            cout << "You chose: " << current->room.getActions()[choice - 1] << endl;
            if (choice == current->room.getActions().size()) {  // Assumes 'Leave the room' is the last action
                current = current->next;  // Move to next room
            }
        }
    }

    cout << "You have reached the end of your adventure!\n";
    return 0;
}
