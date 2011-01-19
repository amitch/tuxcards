// Test program for encryption & decryption
#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QByteArray>
#include <QStringList>

#include <iostream>

#include "../src/utilities/crypt/StringCrypter.h"

// Converts inputfile(text or binary) to outputfile (text, base 64 encoded)
int EncryptFile(const char* password, const char* inputFileName, 
                const char* outputFileName)
{
    const char* funcName = "EncryptFile";

    std::cout << funcName << ": Encrypting " << inputFileName << " to " << outputFileName <<
		std::endl;

    // Read file
    QFile inFile(inputFileName);
    if (!inFile.open(QIODevice::ReadOnly)) {
        std::cout << funcName << ": Error opening inputfile" << outputFileName << std::endl;
        return (-1);
    }
    qint64 fileSize = inFile.size();
    std::cout << funcName << ": Filesize " << fileSize << std::endl;

    QTextStream inStream(&inFile);
    QString fileContents = inStream.readAll();
    
    // Encrypt it
    StringCrypter crypter;

    QByteArray	encByteArray;
    crypter.encryptString(fileContents, QString(password), encByteArray); 
                          
    QString bufferEncoded(encByteArray.toBase64().constData());

    // Write file
    QFile outFile(outputFileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
        std::cout << funcName << ": Error opening outputfile" << outputFileName << std::endl;
        return (-1);
    }

    QTextStream outTStream(&outFile);
    outTStream << bufferEncoded;

    outFile.close();
    inFile.close();

    return (0);

}

int DecryptFile(const char* password, const char* inputFileName, 
                const char* outputFileName)
{
    const char* funcName = "EncodeFile";

    std::cout << funcName << ": Decoding " << inputFileName << " to " << outputFileName <<
		std::endl;

    // Read file
    QFile inFile(inputFileName);
    if (!inFile.open(QIODevice::ReadOnly)) {
        std::cout << funcName << ": Error opening inputfile" << outputFileName << std::endl;
        return (-1);
    }
    qint64 fileSize = inFile.size();
    std::cout << funcName << ": Filesize " << fileSize << std::endl;

    QTextStream inStream(&inFile);
    QString fileContents = inStream.readAll();
    
    QByteArray	outByteArray = QByteArray::fromBase64(fileContents.toAscii());
    
    // Decrypt it
    StringCrypter crypter;
    QString bufferDecrypted;

    crypter.decryptString(outByteArray, QString(password), bufferDecrypted); 

    std::cout << funcName << ": Decrypted & decoded buffer" << bufferDecrypted.toStdString() << std::endl;
    
    // Write file
    QFile outFile(outputFileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
        std::cout << funcName << ": Error opening outputfile" << outputFileName << std::endl;
        return (-1);
    }

    QTextStream outTStream(&outFile);
    outTStream << bufferDecrypted;

    outFile.close();
    inFile.close();

    return (0);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // For debuggign in Qt Creator. Copy 1-encrypted to debug directory.
//    DecryptFile("test", "1-encrypted.txt", "1-decrypted.txt");
//    DecryptFile("tmp", "2-encrypted.txt", "2-decrypted.txt");
//    return (-1);
            
    if (app.arguments().size() <= 4) {
        std::cout << "Usage:\n\t application [-e|-d] password inputfile outputfile\n" <<
			"Encodes or decodes a file by default" << app.arguments().size() << std::endl;
        return (-1);
    }

    if (qstricmp(app.arguments().at(1).toAscii(), "-e") == 0) {
        EncryptFile(app.arguments().at(2).toAscii(), app.arguments().at(3).toAscii(),
                    app.arguments().at(4).toAscii());
    } else if (qstricmp(app.arguments().at(1).toAscii(), "-d") == 0) {
        DecryptFile(app.arguments().at(2).toAscii(), app.arguments().at(3).toAscii(),
                    app.arguments().at(4).toAscii());
//    		DecryptFile("1-encrypted.txt", "1-decrypted.txt");
    } else {
        std::cout << "Incorrect option: " << app.arguments().at(1).toStdString()
             << std::endl;
        return (-1);
    }
    
     return (0);
}

