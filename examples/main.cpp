#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Component - Base class for both Leaf and Composite
class BagComponent {
public:
    virtual std::unordered_map<std::string, int> getItemQuantities() = 0;
};

// Leaf - Represents a concrete item in the bag
class Item : public BagComponent {
private:
    std::string name;
    int quantity;

public:
    Item(std::string name, int quantity) : name(name), quantity(quantity) {}

    std::unordered_map<std::string, int> getItemQuantities() override {
        std::unordered_map<std::string, int> itemQuantity;
        itemQuantity[name] = quantity;
        return itemQuantity;
    }
};

// Composite - Represents a bag that can hold other bags or items
class Bag : public BagComponent {
private:
    std::string name;
    std::vector<BagComponent*> contents;

public:
    Bag(std::string name) : name(name) {}

    void AddComponent(BagComponent* component) {
        contents.push_back(component);
    }

    std::unordered_map<std::string, int> getItemQuantities() override {
        std::unordered_map<std::string, int> itemQuantities;

        for (auto it = contents.begin(); it != contents.end(); ++it) {
            auto subItemQuantities = (*it)->getItemQuantities();
            for (auto subIt = subItemQuantities.begin(); subIt != subItemQuantities.end(); ++subIt) {
                itemQuantities[subIt->first] += subIt->second;
            }
        }

        return itemQuantities;
    }
};

int main() {
    // Create some items
    Item potion("Health Potion", 5);
    Item sword("Sword", 2);

    // Create bags to hold items and other bags
    Bag smallBag("Small Bag");
    Bag mediumBag("Medium Bag");
    Bag largeBag("Large Bag");

    // Add items to the small bag
    smallBag.AddComponent(&potion);
    smallBag.AddComponent(&sword);

    // Add the small bag to the medium bag
    mediumBag.AddComponent(&smallBag);

    // Add the medium bag and a separate sword to the large bag
    largeBag.AddComponent(&mediumBag);
    largeBag.AddComponent(&sword);

    // Calculate and display the total quantity of each item in the large bag
    auto itemQuantities = largeBag.getItemQuantities();
    
    std::cout << "Total Quantity in Large Bag:\n";
    for (auto it = itemQuantities.begin(); it != itemQuantities.end(); ++it) {
        std::cout << it->second << " " << it->first << std::endl;
    }

    return 0;
}
