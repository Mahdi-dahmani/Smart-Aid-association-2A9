#include "arduino.h"
#include <QtDebug>
#include <QtBluetooth>
Arduino::Arduino()
{
    data ="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}


QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600);
                serial->setDataBits(QSerialPort::Data8);
                serial->setParity(QSerialPort::NoParity);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


QByteArray Arduino::read_from_arduino()
{
   if(serial->isReadable()){
        data=serial->readAll(); //récupérer les données reçues

        return data;
   }
   return  data;
}


int Arduino::write_to_arduino( QByteArray d)
{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
        qDebug() << "done";
    }
    else
        qDebug() << "eruure write to serial!";

}
/* void FenProjet::envoie(char trame)
{
        QByteArray byte; //byte a envoyer
        qint64 bw = 0; //bytes really writen
 
        byte.clear(); // on efface le contenu de byte
        byte.append(trame); // on ajoute "value" a byte
 
        if(arduino != NULL && arduino->isWritable() ){ // on vérifie que le port existe toujours
            bw = arduino->write(byte); // on écrit les byte
            //(bw récupere le nombre de byte écris)
            qDebug() << bw << "byte(s) written | Value sent:" << trame ;
            arduino->flush(); // on attend la fin de la transmission
        }
*/
