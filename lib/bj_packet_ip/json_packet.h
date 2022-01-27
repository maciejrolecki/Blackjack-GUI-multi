#ifndef JSON_PACKET_H
#define JSON_PACKET_H
#include "QString"
#include "QByteArray"
#include "QDataStream"
#include "QIODevice"
class json_packet
{
    QString data_;
    QByteArray data_encapsulated;


public:
    json_packet(QString data);
    json_packet()=default;
    void pack_data();
    void un_pack_data();
    void set_data_encap(QByteArray);
    void set_data(QString data);
   inline QByteArray get_data_encapsulated(){return data_encapsulated;}
   inline QString get_data(){return data_;}
    void clear();


};

#endif // JSON_PACKET_H
