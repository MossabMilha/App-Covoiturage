#include "passengersearchhistory.h"
#include "ui_passengersearchhistory.h"
#include "passengerhomepage.h"

PassengerSearchHistory::PassengerSearchHistory(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PassengerSearchHistory)
    ,m_user(user)
{
    ui->setupUi(this);

    // Récupération de l'historique de recherche de l'utilisateur
    std::vector<Search> UserSearch = Search::getUserSearch(user->getId());
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 🔙 Bouton de retour
    QPushButton* backButton = new QPushButton("← Retour", this);
    backButton->setFixedWidth(100);
    mainLayout->addWidget(backButton, 0, Qt::AlignLeft);

    // ⚡ Connexion du bouton de retour
    connect(backButton, &QPushButton::clicked, this, [=]() {
        PassengerHomePage* homepage = new PassengerHomePage(user);
        homepage->show();
        this->close(); // Fermer la page actuelle
    });

    // 🧾 Zone de scroll
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (auto& search : UserSearch) {
        QWidget* searchWidget = new QWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout(searchWidget);

        QVBoxLayout* detailsLayout = new QVBoxLayout();
        QLabel* routeLabel = new QLabel(
            QString::fromStdString(search.getDepart()) + " ➝ " +
                QString::fromStdString(search.getDestination()), searchWidget
            );

        QLabel* dateTimeLabel = new QLabel(
            QString::fromStdString(search.getDateTime()), searchWidget
            );

        QLabel* searchTimeLabel = new QLabel(
            "Search Time: " + QString::fromStdString(search.getSearchTime()), searchWidget
            );

        detailsLayout->addWidget(routeLabel);
        detailsLayout->addWidget(dateTimeLabel);
        detailsLayout->addWidget(searchTimeLabel);

        QPushButton* researchButton = new QPushButton("Research", searchWidget);
        researchButton->setFixedWidth(100);

        connect(researchButton, &QPushButton::clicked, this, [this, search]() {
            try {
                // 1. Vérification de l'utilisateur
                if (!m_user) {
                    QMessageBox::warning(this, "Error", "User not valid");
                    return;
                }

                // 2. Création de la nouvelle recherche avec les bonnes méthodes
                int searchId = -1;
                Search newSearch(0,
                                 m_user->getId(),
                                 search.getDepart(),
                                 search.getDestination(),
                                 search.getSeats(),       // Méthode correcte
                                 search.getPriceLimit(),  // Méthode correcte
                                 QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toStdString(),
                                 search.getDateTime());

                // 3. Validation et sauvegarde
                QString error;
                if (!newSearch.isValid(&error)) {
                    QMessageBox::warning(this, "Validation Error", error);
                    return;
                }

                if (!newSearch.saveSearchToDB(searchId)) {
                    QMessageBox::warning(this, "Database Error", "Failed to save search");
                    return;
                }

                // 4. Affichage des résultats
                PassengerShowSearchResult* resultPage = new PassengerShowSearchResult(m_user, searchId);
                resultPage->show();
                this->close();
            }
            catch (const std::exception& e) {
                QMessageBox::critical(this, "Exception", e.what());
            }
            catch (...) {
                QMessageBox::critical(this, "Error", "Unknown error occurred");
            }
        });

        hLayout->addLayout(detailsLayout);
        hLayout->addStretch();
        hLayout->addWidget(researchButton, 0, Qt::AlignVCenter);

        searchWidget->setLayout(hLayout);
        layout->addWidget(searchWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    // Ajout de la zone scrollable au layout principal
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

PassengerSearchHistory::~PassengerSearchHistory()
{
    delete ui;
}
