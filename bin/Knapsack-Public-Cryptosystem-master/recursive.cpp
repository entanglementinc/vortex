#include <iostream>
#include <vector>
#include <string>
#include <numeric>

#define WEIGHT_LIMIT 100

struct Item {
    std::string name;
    float weight;
    float value;

    Item(std::string name, float weight, float value): name(name), weight(weight), value(value) {};
};

std::vector<Item*> knapsack(std::vector<Item>::iterator begin, std::vector<Item>::iterator end, std::vector<Item*> selected) {
    // If there are no more items, return the selected ones
    if (begin == end) {
        return selected;
    } else {
        // Select the current item
        std::vector<Item*> s0 = selected;
        s0.push_back(&(*begin));
        // Continue the recursive function with both the current item selected and not selected
        auto s1 = knapsack(begin+1, end, s0);
        auto s2 = knapsack(begin+1, end, selected);

        // If one of the two selected sets weights too much, return the other
        if (std::accumulate(s1.begin(), s1.end(), 0, [](float total, Item* item){ return total + item->weight; }) > WEIGHT_LIMIT) {
            return s2;
        } else if (std::accumulate(s2.begin(), s2.end(), 0, [](float total, Item* item){ return total + item->weight; }) > WEIGHT_LIMIT) {
            return s1;
        // If both weights are OK, return the one with highest value
        } else if (std::accumulate(s1.begin(), s1.end(), 0, [](float total, Item* item){ return total + item->value; }) >=
                std::accumulate(s2.begin(), s2.end(), 0, [](float total, Item* item){ return total + item->value; })){
            return s1;
        } else {
            return s2;
        }
    }
}

std::vector<Item*> knapsack_better(std::vector<Item>::iterator begin, std::vector<Item>::iterator end, std::vector<Item*> selected) {
    // If there are no more items, return the selected ones
    if (begin == end) {
        return selected;
    } else {
        // Select the current item
        std::vector<Item*> s0 = selected;
        s0.push_back(&(*begin));
        // If the new selection weights too much, just ignore it and continue the recursive function with the current item not selected
        if (std::accumulate(s0.begin(), s0.end(), 0, [](float total, Item* item){ return total + item->weight; }) > WEIGHT_LIMIT) {
            return knapsack_better(begin+1, end, selected);
        } else {
            // Continue the recursive function with both the current item selected and not selected
            auto s1 = knapsack_better(begin+1, end, s0);
            auto s2 = knapsack_better(begin+1, end, selected);
            // None of the selection will weight too much, because the ones that did, where dumped immediately
            // Return the one with the highest value
            if (std::accumulate(s1.begin(), s1.end(), 0, [](float total, Item* item){ return total + item->value; }) >=
                    std::accumulate(s2.begin(), s2.end(), 0, [](float total, Item* item){ return total + item->value; })){
                return s1;
            } else {
                return s2;
            }
        }
    }
}

int main() {
    // Create the items vector
    std::vector<Item> items;
    // Fill it with randomly generated test data
    items.push_back(Item("n0", 2, 9));
    items.push_back(Item("n1", 3, 3));
    items.push_back(Item("n2", 3, 5));
    items.push_back(Item("n3", 1, 7));
    items.push_back(Item("n4", 5, 5));
    items.push_back(Item("n5", 4, 9));
    items.push_back(Item("n6", 3, 8));
    items.push_back(Item("n7", 4, 9));
    items.push_back(Item("n8", 2, 7));
    items.push_back(Item("n9", 4, 3));
    items.push_back(Item("n10", 3, 8));
    items.push_back(Item("n11", 2, 4));
    items.push_back(Item("n12", 3, 8));
    items.push_back(Item("n13", 4, 2));
    items.push_back(Item("n14", 4, 1));
    items.push_back(Item("n15", 5, 0));
    items.push_back(Item("n16", 2, 9));
    items.push_back(Item("n17", 4, 8));
    items.push_back(Item("n18", 1, 4));
    items.push_back(Item("n19", 5, 2));
    items.push_back(Item("n20", 2, 5));
    items.push_back(Item("n21", 5, 6));
    items.push_back(Item("n22", 3, 7));
    items.push_back(Item("n23", 3, 1));
    items.push_back(Item("n24", 5, 1));
    items.push_back(Item("n25", 4, 0));
    items.push_back(Item("n26", 5, 1));
    items.push_back(Item("n27", 4, 5));
    items.push_back(Item("n28", 1, 1));
    items.push_back(Item("n29", 2, 4));
    // items.push_back(Item("n30", 5, 4));
    // items.push_back(Item("n31", 3, 3));
    // items.push_back(Item("n32", 4, 1));
    // items.push_back(Item("n33", 3, 3));
    // items.push_back(Item("n34", 4, 1));
    // items.push_back(Item("n35", 2, 0));
    // items.push_back(Item("n36", 4, 7));
    // items.push_back(Item("n37", 4, 3));
    // items.push_back(Item("n38", 1, 5));
    // items.push_back(Item("n39", 2, 2));
    // items.push_back(Item("n40", 2, 5));
    // items.push_back(Item("n41", 2, 8));
    // items.push_back(Item("n42", 3, 1));
    // items.push_back(Item("n43", 5, 7));
    // items.push_back(Item("n44", 4, 1));
    // items.push_back(Item("n45", 3, 8));
    // items.push_back(Item("n46", 1, 8));
    // items.push_back(Item("n47", 5, 6));
    // items.push_back(Item("n48", 4, 5));
    // items.push_back(Item("n49", 2, 1));
    // items.push_back(Item("n50", 4, 2));
    // items.push_back(Item("n51", 5, 4));
    // items.push_back(Item("n52", 4, 4));
    // items.push_back(Item("n53", 3, 1));
    // items.push_back(Item("n54", 5, 4));
    // items.push_back(Item("n55", 4, 9));
    // items.push_back(Item("n56", 4, 6));
    // items.push_back(Item("n57", 2, 7));
    // items.push_back(Item("n58", 3, 4));
    // items.push_back(Item("n59", 5, 7));
    // items.push_back(Item("n60", 1, 5));
    // items.push_back(Item("n61", 1, 1));
    // items.push_back(Item("n62", 5, 7));
    // items.push_back(Item("n63", 1, 1));
    // items.push_back(Item("n64", 3, 0));
    // items.push_back(Item("n65", 3, 7));
    // items.push_back(Item("n66", 4, 5));
    // items.push_back(Item("n67", 2, 9));
    // items.push_back(Item("n68", 3, 1));
    // items.push_back(Item("n69", 5, 2));
    // items.push_back(Item("n70", 1, 7));
    // items.push_back(Item("n71", 4, 9));
    // items.push_back(Item("n72", 1, 2));
    // items.push_back(Item("n73", 3, 4));
    // items.push_back(Item("n74", 5, 2));
    // items.push_back(Item("n75", 4, 9));
    // items.push_back(Item("n76", 2, 7));
    // items.push_back(Item("n77", 2, 2));
    // items.push_back(Item("n78", 1, 4));
    // items.push_back(Item("n79", 3, 2));
    // items.push_back(Item("n80", 1, 8));
    // items.push_back(Item("n81", 2, 9));
    // items.push_back(Item("n82", 2, 3));
    // items.push_back(Item("n83", 1, 9));
    // items.push_back(Item("n84", 5, 1));
    // items.push_back(Item("n85", 1, 0));
    // items.push_back(Item("n86", 3, 1));
    // items.push_back(Item("n87", 4, 0));
    // items.push_back(Item("n88", 2, 2));
    // items.push_back(Item("n89", 3, 4));
    // items.push_back(Item("n90", 1, 5));
    // items.push_back(Item("n91", 3, 5));
    // items.push_back(Item("n92", 3, 1));
    // items.push_back(Item("n93", 3, 0));
    // items.push_back(Item("n94", 2, 4));
    // items.push_back(Item("n95", 4, 9));
    // items.push_back(Item("n96", 4, 2));
    // items.push_back(Item("n97", 3, 5));
    // items.push_back(Item("n98", 2, 6));
    // items.push_back(Item("n99", 2, 3));

    // Create an empty selected vector
    std::vector<Item*> selected;
    // Start the recursive function
    auto result = knapsack(items.begin(), items.end(), selected);
    //auto result = knapsack_better(items.begin(), items.end(), selected);
    // Print the result
    std::cout << "Items: " << std::accumulate(result.begin(), result.end(), std::string(""), [](std::string total, Item* item){ return total + item->name; }) << std::endl;
    std::cout << "Weight: " << std::accumulate(result.begin(), result.end(), 0, [](float total, Item* item){ return total + item->weight; }) << std::endl;
    std::cout << "Value: " << std::accumulate(result.begin(), result.end(), 0, [](float total, Item* item){ return total + item->value; }) << std::endl;
    return 0;
}
