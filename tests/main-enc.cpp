#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QByteArray>
#include <QStringList>

#include <iostream>

#include "../src/utilities/base64/CBase64Coder.h"

// Converts inputfile(text or binary) to outputfile (text, base 64 encoded)
int EncodeFile(const char* inputFileName, const char* outputFileName)
{
	// Open input file
	// Call encode
	// Write output to file
    int retVal = 0;
    const char* funcName = "EncodeFile";


    std::cout << funcName << ": Encoding " << inputFileName << " to " << outputFileName <<
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
    
    // Convert to base64
    QByteArray	inpByteArray(fileContents.toAscii());

    CBase64Coder b64Coder = CBase64Coder::getInstance();
    QString bufferEncoded;
    b64Coder.encode( bufferEncoded, inpByteArray );

    std::cout << funcName << ": Encoded buffer" << std::endl << bufferEncoded.toStdString() << std::endl;

    std::cout << funcName << ": Direct Encoded buffer" << std::endl << inpByteArray.toBase64().constData() << std::endl;
    
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

int DecodeFile(const char* inputFileName, const char* outputFileName)
{
    int retVal = 0;
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
    

    CBase64Coder b64Coder = CBase64Coder::getInstance();
//    QString bufferDecoded;
    QByteArray	outByteArray;
    b64Coder.decode(outByteArray, fileContents);

    std::cout << funcName << ": Decoded buffer" << outByteArray.data() << std::endl;
    
    // Write file
    QFile outFile(outputFileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
        std::cout << funcName << ": Error opening outputfile" << outputFileName << std::endl;
        return (-1);
    }

    QTextStream outTStream(&outFile);
    outTStream << outByteArray.data(); //bufferDecoded;

    outFile.close();
    inFile.close();

    return (0);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (app.arguments().size() < 3) {
        std::cout << "Usage:\n\t application [-e|-d] inputfile outputfile\n" <<
			"Encodes or decodes a file by default" << app.arguments().size() << std::endl;
        return (-1);
    }

    if (app.arguments().size() > 3) {
    	if (qstricmp(app.arguments().at(1).toAscii(), "-e") == 0) {
    		EncodeFile(app.arguments().at(2).toAscii(), app.arguments().at(3).toAscii());
    	} else if (qstricmp(app.arguments().at(1).toAscii(), "-d") == 0) {
    		DecodeFile(app.arguments().at(2).toAscii(), app.arguments().at(3).toAscii());
    	} else {
            std::cout << "Incorrect option: " << app.arguments().at(1).toStdString()
                 << std::endl;
            return (-1);
    }
            
    }

     return (0);
//    return a.exec();
}

