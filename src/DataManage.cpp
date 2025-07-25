#include "../include/DataManage.h"

DataManage::DataManage()
    : maxHP(0)
    , currentHP(0)
{

}

DataManage::~DataManage()
{

}

DataManage* DataManage::create()
{
    return new DataManage();
}

void DataManage::setMaxHP(typeHP maxHP)
{
    this->maxHP = maxHP;
    this->currentHP = maxHP;
}

typeHP DataManage::getHP()
{
    return this->currentHP;
}

void DataManage::addHP(typeHP currentHP)
{
    if (this->currentHP + currentHP > this->maxHP)
    {
        this->currentHP = this->maxHP;
    }

    if (this->currentHP + currentHP < 0)
    {
        this->currentHP = 0;
    }

    if (this->currentHP + currentHP > 0 && this->currentHP + currentHP < this->maxHP)
    {
        this->currentHP += currentHP;
    }
}