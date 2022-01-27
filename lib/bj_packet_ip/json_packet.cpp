#include "json_packet.h"

json_packet::json_packet(QString data):data_(data){}

void json_packet::pack_data()
{
    QDataStream in(&this->data_encapsulated,QIODevice::ReadWrite);
    in<<data_;
}

void json_packet::un_pack_data()
{

    QDataStream in(&this->data_encapsulated,QIODevice::ReadWrite);
    in>>data_;
}
void json_packet::set_data(QString data)
{
    this->data_=std::move(data);
}
void json_packet::set_data_encap(QByteArray array)
{
    this->data_encapsulated=std::move(array);
}

void json_packet::clear(){
    data_.clear();
    data_encapsulated.clear();
}
