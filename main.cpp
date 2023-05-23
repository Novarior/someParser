#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <istream>
#include <sstream>
#include <time.h>
#include <ctime>
#include <map>

class someitem {
    public:
    someitem() {
        this->name = "";
        this->count = 0;
        this->price = 0;
        this->weight = 0;
        this->id = 0;
    }
    someitem(std::string name, int count, int price, float weight, unsigned int id) {
        this->name = name;
        this->count = count;
        this->price = price;
        this->weight = weight;
        this->id = id;
    }
    virtual ~someitem() {}

    const std::string& getName() const { return  this->name; }
    const int& getCount() const { return this->count; }
    const int& getPrice() const { return this->price; }
    const float& getWeight() const { return this->weight; }
    const unsigned int& getId() const { return this->id; }


    void setCount(int count) { this->count = count; }
    void setPrice(int price) { this->price = price; }
    void setName(std::string name) { this->name = name; }
    void setWeight(float weight) { this->weight = weight; }

    private:
    std::string name;
    int count;
    int price;
    float weight;
    unsigned int id;
};

void saveToFile(std::string filename, std::map<int, someitem*>& items) {
    //open file
    std::ofstream file;
    file.open(filename);
    //check if file is open
    if (!file.is_open()) {
        std::cout << "Error: file not found" << std::endl;
        return;
    }
    //write to json file
    file << "{\n";
    for (int i = 0; i < items.size(); i++) {
        file << "\t\"item" << i << "\": {\n";
        file << "\t\t\"name\": \"" << items[i]->getName() << "\",\n";
        file << "\t\t\"count\": " << items[i]->getCount() << ",\n";
        file << "\t\t\"price\": " << items[i]->getPrice() << ",\n";
        file << "\t\t\"weight\": " << items[i]->getWeight() << ",\n";
        file << "\t\t\"id\": " << items[i]->getId() << "\n";

        if (i == items.size() - 1) {
            file << "\t}\n";
        }
        else {
            file << "\t},\n";
        }
    }
    file << "}";
    //close file
    file.close();
}

void LoadFromFile(std::string filename, std::map<int, someitem*>& items) {
    //open file
    std::ifstream file;
    file.open(filename);
    //check if file is open
    if (!file.is_open()) {
        std::cout << "Error: file not found" << std::endl;
        return;
    }
    //read file
    std::string line;
    std::string name;
    int count;
    int price;
    int i = 0;
    while (std::getline(file, line)) {
        if (line.find("\"name\":") != std::string::npos) {
            name = line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4);
        }
        else if (line.find("\"count\":") != std::string::npos) {
            count = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
        }
        else if (line.find("\"price\":") != std::string::npos) {
            price = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
        }
        else if (line.find("\"weight\":") != std::string::npos) {
            float weight = std::stof(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
            items[i] = new someitem(name, count, price, weight, i);
            i++;
        }
    }
    //close file
    file.close();
}


int main() {
    //clear UNIX console


    //generate 10 items
    std::map<int, someitem*> items;
    for (int i = 0; i < 10; i++)
        items[i] = new someitem("item" + std::to_string(i), rand() % 100, rand() % 100, rand() % 100, i);


    //save items to file using savetoFile function
    saveToFile("items.json", items);

    //clear item and wrtire to consile result
    for (int i = 0; i < 10; i++) {
        delete items[i];
    }
    items.clear();
    std::cout << "Items cleared" << std::endl;

    //load items from file using LoadFromFile function
    LoadFromFile("items.json", items);

    //write to console loaded items
    for (int i = 0; i < 10; i++) {
        std::cout << "Item " << i << '\t'
            << "Name: " << items[i]->getName() << '\t'
            << "Count: " << items[i]->getCount() << '\t'
            << "Price: " << items[i]->getPrice() << '\t'
            << "Weight: " << items[i]->getWeight() << '\t'
            << "Id: " << items[i]->getId() << std::endl;
    }



    //clear items and delete items
    for (int i = 0; i < 10; i++) {
        delete items[i];
    }
    items.clear();

    return 0;
}