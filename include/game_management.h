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
    static bool isCoffeePowerupActive;

public:
    static void initialize();
    static void incrementCount(const std::string& type);
    static void decrementCount(const std::string& type);  // Add this method
    static void resetCounts();
    static void printStats();
    
    // Getters
    static int getNoteCount() { return noteCount; }
    static int getExamCount() { return examCount; }
    static int getCoffeeCount() { return coffeeCount; }
    static int getFreezeCount() { return freezeCount; }
    static void setCoffeePowerupActive(bool active) {
        isCoffeePowerupActive = active;
    }
    static bool getCoffeePowerupActive() {
        return isCoffeePowerupActive;
    }

    static int calculateFinalScore() {
        // Past exam is now worth 40 points (increased from 30)
        // Notes are worth 20 points base
        // Coffee/freeze themselves are worth 0 points
        // Notes and exams collected during coffee powerup get 2x points
        int baseScore = (getNoteCount() * 20) + 
                       (getExamCount() * 40);

        // If items were collected during coffee powerup, they would have been 
        // counted with the bonus in the increment function already
        return baseScore;
    }
};