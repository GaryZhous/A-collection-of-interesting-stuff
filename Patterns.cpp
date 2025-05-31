#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <random>
/*
  The Tapestry’s interconnections form Patterns. Patterns are the conjoining of the threads of reality. Each is composed of smaller Patterns and each in turn creates greater ones. Patterns bring context to the disparate elements of the Tapestry. They are not intrinsically static and can be altered by external or internal influences. Each Pattern is unique.

  Finally, we’re getting down to the code.

  If I’m reading this correctly, Patterns are the world’s functions, variables and instances. There are no true duplicates, as each Pattern has its own memory allocation, its own unique identifier. Patterns are the Lego bricks of the universe. They can be as simple as a “Hello, world!” application or as complex as the millions of lines that control the space shuttle’s attitude adjustment thrusters.

  A human being is a Pattern, and is composed of a liver Pattern, a heart Pattern, a brain Pattern, and even a useless appendix Pattern, amongst all other kinds of Patterns. Human Patterns form country Patterns, which are on continent Patterns, which exist within a world Pattern. There’s a definite Pattern pecking order, it seems.
*/
//A quote from World of Darkness
class Pattern {
protected:
    std::string id;
    std::unordered_map<std::string, std::shared_ptr<Pattern>> subPatterns;

public:
    Pattern(const std::string& patternId) : id(patternId) {}

    std::string getId() const { return id; }

    void addSubPattern(const std::string& name, std::shared_ptr<Pattern> pattern) {
        subPatterns[name] = pattern;
    }

    std::shared_ptr<Pattern> getSubPattern(const std::string& name) const {
        auto it = subPatterns.find(name);
        if (it != subPatterns.end()) return it->second;
        return nullptr;
    }

    virtual void mutate(const std::string& change) {
        std::cout << "Mutating Pattern [" << id << "] with change: " << change << std::endl;
    }

    virtual void display(int indent = 0) const {
        std::string prefix(indent, ' ');
        std::cout << prefix << "Pattern ID: " << id << std::endl;
        for (const auto& [name, sub] : subPatterns) {
            std::cout << prefix << " SubPattern [" << name << "] ->" << std::endl;
            sub->display(indent + 4);
        }
    }
};

// A more specific Pattern (e.g., an individual human)
class SpecificPattern : public Pattern {
public:
    SpecificPattern(const std::string& specificId) : Pattern(specificId) {}

    void mutate(const std::string& change) override {
        std::cout << "[Specific] Pattern [" << id << "] now exhibits: " << change << std::endl;
    }
};

// Utility function to generate a random ID
std::string generateId() {
    static int count = 0;
    return "Pattern_" + std::to_string(++count);
}

int main() {
    auto humanPattern = std::make_shared<Pattern>("HumanBeing");

    auto heart = std::make_shared<Pattern>("Heart");
    auto brain = std::make_shared<Pattern>("Brain");
    auto appendix = std::make_shared<Pattern>("Appendix");

    humanPattern->addSubPattern("heart", heart);
    humanPattern->addSubPattern("brain", brain);
    humanPattern->addSubPattern("appendix", appendix);

    auto catherine = std::make_shared<SpecificPattern>("CatherineCalvert");
    catherine->addSubPattern("base", humanPattern);

    std::cout << "\n--- Displaying Catherine's Pattern ---\n";
    catherine->display();

    std::cout << "\n--- Mutating General Human Pattern ---\n";
    humanPattern->mutate("Added Gills");

    std::cout << "\n--- Mutating Catherine Specifically ---\n";
    catherine->mutate("Grew Wings");

    return 0;
}
