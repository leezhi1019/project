#pragma once
#include <SDL.h>
#include <string>
#include <map>

class GameManagement {
private:
    static int noteCount;
    static int examCount;
    static int coffeeCount;
    static int freezeCount;
    static bool initialized;

public:
    static void initialize();
    static void incrementCount(const std::string& type);
    static void resetCounts();
    static void printStats();
    
    // Getters
    static int getNoteCount() { return noteCount; }
    static int getExamCount() { return examCount; }
    static int getCoffeeCount() { return coffeeCount; }
    static int getFreezeCount() { return freezeCount; }

    static int calculateFinalScore() {
        return (getNoteCount() * 20) + 
               (getExamCount() * 30) + 
               (getCoffeeCount() * 15) + 
               (getFreezeCount() * 10);
    }
};