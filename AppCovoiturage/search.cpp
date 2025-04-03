#include "search.h"

// Constructor
Search::Search(int id, int userId, const std::string &depart, const std::string &destination, int seats, double priceLimit, const std::string &searchTime, const std::string &dateTime)
    : id(id), userId(userId), depart(depart), destination(destination), seats(seats), priceLimit(priceLimit), searchTime(searchTime), dateTime(dateTime) {}

// Getters
int Search::getId() const { return id; }
int Search::getUserId() const { return userId; }
std::string Search::getDepart() const { return depart; }
std::string Search::getDestination() const { return destination; }
int Search::getSeats() const { return seats; }
double Search::getPriceLimit() const { return priceLimit; }
std::string Search::getSearchTime() const { return searchTime; }
std::string Search::getDateTime() const { return dateTime; }

Search Search::getSerachById(int SearchId) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return Search(-1, -1, "", "", 0, 0.0, "", "");
    }

    QSqlQuery query;
    query.prepare("SELECT id, user_id, depart, destination, seats, price_limit, search_time, date_time FROM search_history WHERE id = :id");
    query.bindValue(":id", SearchId);

    if (!query.exec() || !query.next()) {
        qWarning() << "Failed to retrieve search record:" << query.lastError().text();
        return Search(-1, -1, "", "", 0, 0.0, "", "");
    }

    return Search(
        query.value("id").toInt(),
        query.value("user_id").isNull() ? -1 : query.value("user_id").toInt(),
        query.value("depart").toString().toStdString(),
        query.value("destination").toString().toStdString(),
        query.value("seats").toInt(),
        query.value("price_limit").toDouble(),
        query.value("search_time").toString().toStdString(),
        query.value("date_time").toString().toStdString()
        );
}
std::vector<Search> Search::getUserSearch(int userId) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return {};
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, depart, destination, seats, price_limit, date_time, search_time FROM search_history WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    std::vector<Search> userSearches;

    if (!query.exec()) {
        qDebug() << "Error fetching search history for user:" << query.lastError().text();
        return userSearches;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        std::string depart = query.value("depart").toString().toStdString();
        std::string destination = query.value("destination").toString().toStdString();
        int seats = query.value("seats").toInt();
        double price_limit = query.value("price_limit").toDouble();
        std::string date_time = query.value("date_time").toString().toStdString();
        std::string search_time = query.value("search_time").toString().toStdString();

        Search search(id, userId, depart, destination, seats, price_limit, date_time, search_time);
        userSearches.push_back(search);
    }

    if (userSearches.empty()) {
        qDebug() << "No search history found for user with ID:" << userId;
    }

    return userSearches;
}
// Setters
void Search::setUserId(int userId) { this->userId = userId; }
void Search::setDepart(const std::string &depart) { this->depart = depart; }
void Search::setDestination(const std::string &destination) { this->destination = destination; }
void Search::setSeats(int seats) { this->seats = seats; }
void Search::setPriceLimit(double priceLimit) { this->priceLimit = priceLimit; }
void Search::setSearchTime(const std::string &searchTime) { this->searchTime = searchTime; }
void Search::setDateTime(const std::string &dateTime) { this->dateTime = dateTime; }



bool Search::isValid(QString* error) const
{
    bool state = true;

    if (priceLimit <= 0) {
        *error += "The price must be greater than 0.\n";
        state = false;
    }

    if (depart.empty() || destination.empty()) {
        if (depart.empty()) {
            *error += "Start cannot be Empty.\n";
            state = false;
        }
        if (destination.empty()) {
            *error += "Destination cannot be Empty.\n";
            state = false;
        }
    } else if (depart == destination) {
        *error += "Start and destination cannot be the same.\n";
        state = false;
    }


    if (seats <= 0) {
        *error += "The number of available seats must be greater than 0.\n";
        state = false;
    }




    return state;
}





bool Search::saveSearchToDB(int &searchId) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO search_history (user_id, depart, destination, seats, price_limit, date_time) "
                  "VALUES (:user_id, :depart, :destination, :seats, :price_limit, :date_time)");

    query.bindValue(":user_id", userId);
    query.bindValue(":depart", QString::fromStdString(depart));
    query.bindValue(":destination", QString::fromStdString(destination));
    query.bindValue(":seats", seats);
    query.bindValue(":price_limit", priceLimit);
    query.bindValue(":date_time", QString::fromStdString(dateTime));

    if (!query.exec()) {
        qWarning() << "Failed to insert search:" << query.lastError().text();
        return false;
    }

    // Retrieve the last inserted ID
    searchId = query.lastInsertId().toInt();


    return true;
}

