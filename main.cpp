#include <iostream>
#include <string>
#include <map>

bool isSurname(const std::string& surname) {
    if (surname.empty()) {
        return false;
    }
    if (std::all_of(surname.begin(),
                    surname.end(),
                    [](char c) { return !std::isalpha(c); })) {
        return false;
    }
    return true;
}

bool isNumber(const std::string& number) {
    if (number.empty()) {
        return false;
    }
    if (number.length() > 8) {
        return false;
    }
    int count = 0;
    for (char c : number) {
        if (c == '-') {
            ++count;
        }
    }
    if (count != 2) {
        return false;
    }
    if (std::all_of(number.begin(),
                    number.end(),
                    [](char c) { return !std::isdigit(c) && c != ' '; })) {
        return false;
    }
    return true;
}

bool isNew(const std::string& input) {
    int count = 0;
    for (const char c : input) {
        if (c == ' ') {
            ++count;
        }
    }
    if (count > 1) {
        return false;
    }
    size_t spaceIndex = input.find_first_of(' ');
    std::string number = input.substr(0, spaceIndex);
    std::string surname = input.substr(spaceIndex + 1);
    if (!isNumber(number) || !isSurname(surname)) {
        return false;
    }
    return true;
}

void showNumbers(const std::string& name, std::map<std::string, std::string>& phonebook) {
    if (phonebook.empty()) {
        std::cout << "Phonebook is empty." << std::endl;
        return;
    }
    for (const auto& entry : phonebook) {
        if (entry.second == name) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }
}

void showSurname(const std::string& number, const std::map<std::string, std::string>& phonebook) {
    if (phonebook.empty()) {
        std::cout << "Phonebook is empty." << std::endl;
        return;
    }
    for (const auto& entry : phonebook) {
        if (entry.first == number) {
            std::cout << entry.first << ": " << entry.second << std::endl;
            return;
        }
    }
}

int main() {
    std::map<std::string, std::string> phonebook;
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        } else if (isNew(input)) {
            size_t spaceIndex = input.find_first_of(' ');
            std::string number = input.substr(0, spaceIndex);
            std::string name = input.substr(spaceIndex + 1);
            phonebook[number] = name;
            std::cout << "Added: " << name << ", " << number << std::endl;
        } else if (isNumber(input)) {
            showSurname(input, phonebook);
        } else if (isSurname(input)) {
            showNumbers(input, phonebook);
        } else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return 0;
}
