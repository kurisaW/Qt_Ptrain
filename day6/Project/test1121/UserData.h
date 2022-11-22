#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData
{
public:
    UserData();
    UserData(QString name, int id);
    ~UserData();

    QString name;
    int id;
};

#endif // USERDATA_H
