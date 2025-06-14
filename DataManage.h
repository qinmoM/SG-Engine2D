#pragma once

class DataManage
{
private:
    DataManage();
protected:
    float maxHP;
    float currentHP;
public:
    ~DataManage();

    static DataManage* create();

    void setHP(float maxHP);
    float getHP();
};