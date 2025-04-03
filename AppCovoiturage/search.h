#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Search
{
public:
    // Constructor
    Search(int id, int userId, const std::string &depart, const std::string &destination, int seats, double priceLimit, const std::string &searchTime, const std::string &dateTime);

    // Getters
    int getId() const;
    int getUserId() const;
    std::string getDepart() const;
    std::string getDestination() const;
    int getSeats() const;
    double getPriceLimit() const;
    std::string getSearchTime() const;
    std::string getDateTime() const;

    Search getSerachById(int SearchId);
    static std::vector<Search>getUserSearch(int userId);

    // Setters
    void setUserId(int userId);
    void setDepart(const std::string &depart);
    void setDestination(const std::string &destination);
    void setSeats(int seats);
    void setPriceLimit(double priceLimit);
    void setSearchTime(const std::string &searchTime);
    void setDateTime(const std::string &dateTime);

    bool isValid(QString* error) const;
    bool saveSearchToDB(int &searchId);

private:
    int id;
    int userId;
    std::string depart;
    std::string destination;
    int seats;
    double priceLimit;
    std::string searchTime;
    std::string dateTime;
};

#endif // SEARCH_H
