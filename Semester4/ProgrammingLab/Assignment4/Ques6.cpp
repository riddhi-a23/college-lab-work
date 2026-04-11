#include <iostream>
#include <string>

namespace CricketSystem {

    const int MAX_MATCHES = 100;
    class Cricketer {
    protected:
        std::string name;
        int age;

    public:
        Cricketer(const std::string& n = "Unknown", int a = 0) : name(n), age(a) {}

        virtual ~Cricketer() {}

        void displayProfile() const {
            std::cout << "Name: " << name << ", Age: " << age << "\n";
        }
    };

    class Batsman : virtual public Cricketer {
    protected:
        int runsScored[MAX_MATCHES];
        std::string batOpponents[MAX_MATCHES];
        int batMatchCount;

    public:
        Batsman(const std::string& n = "Unknown", int a = 0) : Cricketer(n, a), batMatchCount(0) {}

        int getMatchesPlayedAsBatsman() const { return batMatchCount; }

        void addBattingRecord(const std::string& country, int runs);
    };

    class Bowler : virtual public Cricketer {
    protected:
        int wicketsTaken[MAX_MATCHES];
        std::string bowlOpponents[MAX_MATCHES];
        int bowlMatchCount;

    public:
        Bowler(const std::string& n = "Unknown", int a = 0) : Cricketer(n, a), bowlMatchCount(0) {}

        int getMatchesPlayedAsBowler() const { return bowlMatchCount; }

        void addBowlingRecord(const std::string& country, int wickets);
    };

    class AllRounder : public Batsman, public Bowler {
    public:
        AllRounder(const std::string& n = "Unknown", int a = 0)
            : Cricketer(n, a), Batsman(n, a), Bowler(n, a) {}

        void insertMatchRecord(const std::string& country, int runs, int wickets) {
            addBattingRecord(country, runs);
            addBowlingRecord(country, wickets);
        }

        double countBattingAverage() const;

        int countTotalWickets() const;

        void displayHighestWickets() const;

        void displayHighestRuns() const;
    };

    void Batsman::addBattingRecord(const std::string& country, int runs) {
        if (batMatchCount < MAX_MATCHES) {
            batOpponents[batMatchCount] = country;
            runsScored[batMatchCount] = runs;
            batMatchCount++;
        } else {
            std::cout << "Max match capacity reached for batting records.\n";
        }
    }

    void Bowler::addBowlingRecord(const std::string& country, int wickets) {
        if (bowlMatchCount < MAX_MATCHES) {
            bowlOpponents[bowlMatchCount] = country;
            wicketsTaken[bowlMatchCount] = wickets;
            bowlMatchCount++;
        } else {
            std::cout << "Max match capacity reached for bowling records.\n";
        }
    }

    double AllRounder::countBattingAverage() const {
        if (batMatchCount == 0) return 0.0;
        int totalRuns = 0;
        for (int i = 0; i < batMatchCount; ++i) {
            totalRuns += runsScored[i];
        }
        return static_cast<double>(totalRuns) / batMatchCount;
    }

    int AllRounder::countTotalWickets() const {
        int totalWickets = 0;
        for (int i = 0; i < bowlMatchCount; ++i) {
            totalWickets += wicketsTaken[i];
        }
        return totalWickets;
    }

    void AllRounder::displayHighestWickets() const {
        if (bowlMatchCount == 0) {
            std::cout << "No bowling records available.\n";
            return;
        }

        int maxWickets = wicketsTaken[0];
        std::string bestCountry = bowlOpponents[0];

        for (int i = 1; i < bowlMatchCount; ++i) {
            if (wicketsTaken[i] > maxWickets) {
                maxWickets = wicketsTaken[i];
                bestCountry = bowlOpponents[i];
            }
        }
        std::cout << "Highest Wickets: " << maxWickets << " against " << bestCountry << "\n";
    }

    void AllRounder::displayHighestRuns() const {
        if (batMatchCount == 0) {
            std::cout << "No batting records available.\n";
            return;
        }

        int maxRuns = runsScored[0];
        std::string bestCountry = batOpponents[0];

        for (int i = 1; i < batMatchCount; ++i) {
            if (runsScored[i] > maxRuns) {
                maxRuns = runsScored[i];
                bestCountry = batOpponents[i];
            }
        }
        std::cout << "Highest Runs: " << maxRuns << " against " << bestCountry << "\n";
    }

} 

using namespace CricketSystem;

int main() {
    std::cout << "=== All-Rounder Profile System ===\n";

    AllRounder player("Riddhi Agarwal", 35);
    player.displayProfile();

    std::cout << "\n--- Inserting Match Records ---\n";
    player.insertMatchRecord("Australia", 104, 2);
    player.insertMatchRecord("England", 45, 5);
    player.insertMatchRecord("India", 130, 1);
    player.insertMatchRecord("Pakistan", 78, 3);
    player.insertMatchRecord("New Zealand", 12, 4);

    std::cout << "Records successfully inserted.\n\n";

    std::cout << "--- Player Statistics ---\n";
    std::cout << "Batting Average: " << player.countBattingAverage() << " runs per match\n";

    std::cout << "Total Wickets Taken: " << player.countTotalWickets() << "\n";

    player.displayHighestWickets();

    player.displayHighestRuns();

    return 0;
}