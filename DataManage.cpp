#include "DataManage.h"

DataManage::DataManage() : maxHP(0), currentHP(0)
{

}

DataManage::~DataManage()
{

}

DataManage* DataManage::create()
{
    return new DataManage();
}

void DataManage::setHP(float maxHP)
{
    this->maxHP = maxHP;
    this->currentHP = maxHP;
}

float DataManage::getHP()
{
    return this->currentHP;
}