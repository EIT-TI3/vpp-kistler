//
// Created by martin on 23.06.23.
//
#include "serializer.h"
#include <QJsonDocument>
#include <QFile>
#include <fstream>


Serializer::Serializer(const IKomponente &root): ik(root) {}

void Serializer::writeToJson(const char *fname) {
    QFile file(fname);

    if(!file.open(QIODevice::ReadWrite)) {
        throw std::fstream::failure("Datei konnte nicht geoeffnet werden.");
    }

    file.resize(0);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(ik.toJson());

    if(!file.write(jsonDoc.toJson())) {
        file.close();
        throw std::fstream::failure("Datei konnte nicht beschrieben werden.");
    }
    file.close();
}

Serializer::~Serializer() = default;

