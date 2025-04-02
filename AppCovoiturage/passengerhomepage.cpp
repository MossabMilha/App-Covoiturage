#include "passengerhomepage.h"
#include "ui_passengerhomepage.h"



#include "start.h"




void PassengerHomePage::on_profilButton_clicked()
{
    // profilewindow profileWindow(this);
    // profileWindow.exec();
}


void PassengerHomePage::on_deconnecterButton_clicked()
{
    this->close();

    QList<QWidget *> allWindows = QApplication::topLevelWidgets();
    for (QWidget *widget : allWindows) {
        if (widget->inherits("MainWindow")) {
            widget->show();
            return;
        }
    }

    start *StartWindow = new start();
    StartWindow->show();
}


void PassengerHomePage::onDateButtonClicked()
{
    ui->calendarWidget->setVisible(true);
}


void PassengerHomePage::onCalendarDateSelected(const QDate &date)
{
    ui->dateEdit->setDate(date);
    ui->calendarWidget->setVisible(false);
}

void PassengerHomePage::displayTheResult() {
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + "/../../../..//Script/sc/output.json";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier de résultats.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isObject()) {
        QMessageBox::critical(this, "Erreur", "Fichier JSON invalide.");
        return;
    }

    QJsonObject jsonObj = doc.object();
    if (!jsonObj.contains("matching_trajects") || !jsonObj["matching_trajects"].isArray()) {
        QMessageBox::critical(this, "Erreur", "Aucun résultat trouvé.");
        return;
    }

    QJsonArray resultsArray = jsonObj["matching_trajects"].toArray();

    // Clear the table before inserting new data
    ui->tableWidgetResults->clearContents();
    ui->tableWidgetResults->setRowCount(0);
    ui->tableWidgetResults->setRowCount(resultsArray.size());
    ui->tableWidgetResults->setColumnCount(5);

    // Set table headers
    QStringList headers = {"ID", "Start Place", "End Place", "Places", "Date"};
    ui->tableWidgetResults->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (const QJsonValue &value : resultsArray) {
        QJsonObject obj = value.toObject();
        int id = obj["id"].toInt();
        QString startPlace = obj["start_place"].toString();
        QString endPlace = obj["end_place"].toString();
        int places = obj["places"].toInt();
        QString date = obj["date"].toString();

        ui->tableWidgetResults->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        ui->tableWidgetResults->setItem(row, 1, new QTableWidgetItem(startPlace));
        ui->tableWidgetResults->setItem(row, 2, new QTableWidgetItem(endPlace));
        ui->tableWidgetResults->setItem(row, 3, new QTableWidgetItem(QString::number(places)));
        ui->tableWidgetResults->setItem(row, 4, new QTableWidgetItem(date));

        row++;
    }

    // Resize columns to fit content
    ui->tableWidgetResults->resizeColumnsToContents();
}


void PassengerHomePage::on_appliquerButton_clicked()
{
    // Récupération des valeurs
    QString depart = ui->comboBoxVilleDepart->currentText();
    QString arrivee = ui->comboBoxVilleArrivee->currentText();
    int places = ui->comboBoxNombrePlaces->currentText().toInt();
    QDate date = ui->dateEdit->date();

    // Vérification des champs
    if (depart.isEmpty() || arrivee.isEmpty() || depart == arrivee || places <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    } else {
        // JSON Construction
        QJsonObject traject;
        traject["start_place"] = depart;
        traject["end_place"] = arrivee;
        traject["date"] = date.toString("yyyy-MM-dd");
        traject["places"] = places;

        QJsonObject root;
        root["traject"] = traject;

        QJsonDocument doc(root);

        // Write to file
        QString currentDir = QCoreApplication::applicationDirPath();
        QString jsonFilePath = currentDir + "/../../../../Script/sc/input.json";
        QFile file(jsonFilePath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'écrire le fichier JSON.");
            return;
        }
        file.write(doc.toJson());
        file.close();

        // Call Python script
        QString pythonExecutable = currentDir + "/../../../../Script/sc/.venv/Scripts/python.exe";
        QString scriptPath = currentDir + "/../../../../Script/sc/script.py";
        QProcess *process = new QProcess(this);
        process->setProgram(pythonExecutable);
        process->setArguments(QStringList() << scriptPath);
        process->setWorkingDirectory(currentDir + "/../../../../Script/sc");

        ui->appliquerButton->setEnabled(false);  // Disable the button before the process starts

        process->start();

        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [=](int exitCode, QProcess::ExitStatus exitStatus) {
                    ui->appliquerButton->setEnabled(true);  // Re-enable the button after process finishes
                    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                        QMessageBox::information(this, "Succès", "Recherche effectuée avec succès !");
                        displayTheResult();
                    } else {
                        QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution du script Python.");
                    }
                });
    }
}

// Gérer le changement de ville de départ
void PassengerHomePage::onVilleChanged() {
    QString ville = ui->comboBoxVilleDepart->currentText();
    qDebug() << "Ville de départ sélectionnée :" << ville;
}

// Gérer le changement de ville d'arrivée
void PassengerHomePage::onVilleArriveeChanged() {
    QString ville = ui->comboBoxVilleArrivee->currentText();
    qDebug() << "Ville d'arrivée sélectionnée :" << ville;
}

// Gérer le changement du nombre de places
void PassengerHomePage::onNombrePlacesChanged() {
    int places = ui->comboBoxNombrePlaces->currentText().toInt();
    qDebug() << "Nombre de places sélectionné :" << places;
}



PassengerHomePage::PassengerHomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PassengerHomePage)
{
    ui->setupUi(this);

    // Cacher le calendrier au démarrage
    ui->calendarWidget->setVisible(false);

    // Connecter le bouton pour afficher le calendrier
    connect(ui->dateButton, &QPushButton::clicked, this, &PassengerHomePage::onDateButtonClicked);
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &PassengerHomePage::onCalendarDateSelected);

    // Ajouter un élément par défaut
    ui->comboBoxVilleDepart->addItem("Départ");
    ui->comboBoxVilleArrivee->addItem("Arrivée");

    // Ajouter les villes dans les ComboBox
    QStringList villes = {"Paris", "Lyon", "Marseille", "Toulouse", "Nice", "Bordeaux", "Nantes", "Strasbourg"};
    ui->comboBoxVilleDepart->addItems(villes);
    ui->comboBoxVilleArrivee->addItems(villes);

    // Configuration des ComboBox pour la ville de départ
    ui->comboBoxVilleDepart->addItems(villes);
    ui->comboBoxVilleDepart->setEditable(true);
    ui->comboBoxVilleDepart->setCurrentIndex(0);
    ui->comboBoxVilleArrivee->setCurrentIndex(0);

    // Configuration des ComboBox pour la ville d'arrivée
    ui->comboBoxVilleArrivee->addItems(villes);
    ui->comboBoxVilleArrivee->setEditable(true);

    // Configuration du ComboBox pour le nombre de places
    for (int i = 1; i <= 7; ++i) {
        ui->comboBoxNombrePlaces->addItem(QString::number(i));
    }

    // Connexion du bouton "Appliquer"
    connect(ui->appliquerButton, &QPushButton::clicked, this, &PassengerHomePage::on_appliquerButton_clicked);

    // Connexion des signaux pour la mise à jour dynamique des valeurs
    connect(ui->comboBoxVilleDepart, &QComboBox::currentIndexChanged, this, &PassengerHomePage::onVilleChanged);
    connect(ui->comboBoxVilleArrivee, &QComboBox::currentIndexChanged, this, &PassengerHomePage::onVilleArriveeChanged);
    connect(ui->comboBoxNombrePlaces, &QComboBox::currentIndexChanged, this, &PassengerHomePage::onNombrePlacesChanged);
}

PassengerHomePage::~PassengerHomePage()
{
    delete ui;
}
