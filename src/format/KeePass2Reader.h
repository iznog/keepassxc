/*
 *  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSX_KEEPASS2READER_H
#define KEEPASSX_KEEPASS2READER_H

#include <QtCore/QCoreApplication>

#include "core/Endian.h"
#include "core/Uuid.h"
#include "keys/CompositeKey.h"

class Database;

class KeePass2Reader
{
    Q_DECLARE_TR_FUNCTIONS(KeePass2Reader);

public:
    Database* readDatabase(QIODevice* device, const CompositeKey& key);
    Database* readDatabase(const QString& filename, const CompositeKey& key);
    bool error();
    QString errorString();

private:
    void raiseError(const QString& str);

    bool readHeaderField();

    void setCipher(const QByteArray& data);
    void setCompressionFlags(const QByteArray& data);
    void setMasterSeed(const QByteArray& data);
    void setTransformSeed(const QByteArray& data);
    void setTansformRounds(const QByteArray& data);
    void setEncryptionIV(const QByteArray& data);
    void setProtectedStreamKey(const QByteArray& data);
    void setStreamStartBytes(const QByteArray& data);
    void setInnerRandomStreamID(const QByteArray& data);

    static const QSysInfo::Endian BYTEORDER;

    QIODevice* m_device;
    bool m_error;
    QString m_errorStr;
    bool m_headerEnd;

    Uuid m_cipher;
    int m_compression;
    QByteArray m_masterSeed;
    QByteArray m_transformSeed;
    quint64 m_transformRounds;
    QByteArray m_encryptionIV;
    QByteArray m_streamStartBytes;
};

#endif // KEEPASSX_KEEPASS2READER_H
