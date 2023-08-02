#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "Config.h"

Config::Config() {
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    configPath = configDir + '/' + "TwinNavigator/config.json";
    QFile file(configPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Nie można otworzyć pliku JSON.";
        return;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Błąd parsowania pliku JSON: " << parseError.errorString();
        return;
    }
    file.close();
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qDebug() << "Błąd: niepoprawny format JSON lub pusty dokument.";
        return;
    }
    QJsonObject jsonObject = jsonDoc.object();
    for (int i=0; i<=1; i++) {
        QString key = "paths"+QString::number(i);
        if (jsonObject.contains(key) && jsonObject[key].isArray()) {
            QJsonArray pathArray = jsonObject[key].toArray();
            for (const auto& path : pathArray) {
                if (!path.isString())
                    continue;
                paths[i].push_back(path.toString());
            }
        }
    }
}
