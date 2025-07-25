#pragma once

typedef int typeHP;

class DataManage
{
private:
    DataManage();
protected:
    typeHP maxHP;
    typeHP currentHP;
public:
    ~DataManage();

    static DataManage* create();

    //          HP functions

    void setMaxHP(typeHP maxHP);
    typeHP getHP();
    void addHP(typeHP currentHP);
};