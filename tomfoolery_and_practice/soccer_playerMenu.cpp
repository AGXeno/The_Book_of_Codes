#include <iostream>
#include <vector>
using namespace std;

int main() {
    char input;

    vector <int> playerJersey(5);
    vector <int> playerRating(5);
    unsigned int i;
    int pushback;
    int remove_player;
    int jersey;
    int new_rating;
    int check_rating;
    int index;

    for (i = 0; i < playerJersey.size(); ++i) {
        cout << "Enter player " << i + 1 << "'s jersey number:" << endl;
        cin >> playerJersey.at(i);

        cout << "Enter player " << i + 1 << "'s rating:" << endl;
        cin >> playerRating.at(i);
        cout << endl;
    }

    cout << "ROSTER" << endl;

    for (i = 0; i < playerJersey.size(); ++i) {
        cout << "Player " << i + 1 << " -- Jersey number: "<< playerJersey.at(i) << ", Rating: " << playerRating.at(i);
        cout << endl;
    }

    while (input != 'q') {
        cout << endl;
        cout << "MENU" << endl;
        cout << "a - Add player" << endl;
        cout << "d - Remove player" << endl;
        cout << "u - Update player rating" << endl;
        cout << "r - Output players above a rating" << endl;
        cout << "o - Output roster" << endl;
        cout << "q - Quit" << endl;
        cout << endl;
        cout << "Choose an option:" << endl;
        cin >> input;

        if (input == 'a') {
            cout << "Enter a new player's jersey number: " << endl;
            cin >> pushback;
            playerJersey.push_back(pushback);
            cout << "Enter the player's rating: " << endl;
            cin >> pushback;
            playerRating.push_back(pushback);
        }

        else if (input == 'd') {
            cout << "Enter a jersey number:" << endl;
            cin >> remove_player;
            auto grab_index = find(playerJersey.begin(), playerJersey.end(), remove_player);
            index = distance(playerJersey.begin(), grab_index);
            playerJersey.erase(playerJersey.begin() + index);
            playerRating.erase(playerRating.begin() + index);
            /*
            playerJersey.erase(playerJersey.begin() + (remove_player - 1));
            playerRating.erase(playerRating.begin() + (remove_player - 1));
             */
        }

        else if (input == 'u') {
            cout << "Enter a jersey number: " << endl;
            cin >> jersey;
            cout << "Enter a new rating for the player:" << endl;
            cin >> new_rating;
            /*playerRating.at(jersey - 1) = new_rating; */

            auto grab_index = find(playerJersey.begin(), playerJersey.end(), jersey);
            index = distance(playerJersey.begin(), grab_index);
            playerRating.at(index) = new_rating;
        }

        else if (input == 'r') {
            cout << "Enter a rating: " << endl;
            cin >> check_rating;
            cout << "ABOVE " << check_rating << endl;
            for (i = 0; i < playerRating.size(); ++i) {
                if (playerRating.at(i) > check_rating) {
                    cout << "Player " << i + 1 << " -- Jersey number: " << playerJersey.at(i) << ", Rating: "
                         << playerRating.at(i) << endl;

                }

            }

        }

        else if (input == 'o') {
            cout << "ROSTER" << endl;;
            for (i = 0; i < playerJersey.size(); ++i) {
                cout << "Player " << i + 1 << " -- Jersey number: "<< playerJersey.at(i) << ", Rating: " << playerRating.at(i);
                cout << endl;
            }
        }

    }
    return 0;
}








