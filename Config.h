#ifndef TWINNAVIGATOR_CONFIG_H
#define TWINNAVIGATOR_CONFIG_H

#include <QString>

class Config {
    QString configPath;
public:
    std::vector<QString> paths[2];
    Config();
};

#endif //TWINNAVIGATOR_CONFIG_H
