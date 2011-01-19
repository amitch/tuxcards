/***************************************************************************
                          StringCrypter.cpp  -  description
                             -------------------
    begin                : Fri Jul 18 2003
    copyright            : (C) 2003 by Alexander Theel
    email                : alex.theel@gmx.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "BlowFish.h"
#include "MD5.h"

#include "q3textstream.h"
#include "qstring.h"
#include <iostream>
#include <QLatin1String>

#include "StringCrypter.h"

const int StringCrypter::BUFFER_SIZE = 512;

const char* TUX_ENCRYPT_HEADER = "Fh_enc:BF10";

const int BFISH_BUF_MOD=8;

void StringCrypter::encryptString( const QString& sInputString, const QString& sPassWd,
                                   QByteArray& encryptedData )
{
   if ( sPassWd.isNull() || sPassWd == "" )
   {
      std::cerr<<"TuxCards ERROR: StringCrypter::encryptString: No passwd given for: "
              << sInputString.toStdString()  << std::endl;
      return;
   }

   // calculate hash-value from given password
   CMD5 md5;
   md5.MD5Init();
   md5.MD5Update((unsigned char *)sPassWd.ascii(), sPassWd.length());
   md5.MD5Final();

   CBlowFish fish;
   fish.Initialize( (unsigned char*)sPassWd.ascii(), sPassWd.length() );

   encryptedData.resize(0);
   
   Q3TextStream t(encryptedData, QIODevice::WriteOnly);
    
   // write header string + hash + original file size
   t << TUX_ENCRYPT_HEADER;

   // write password hash value (md5 algorithm)
   unsigned char passWordHashValue[16];
   memset( passWordHashValue, 0, 16 );
   memcpy( passWordHashValue, md5.GetDigestBinary(), 16);
   for ( int i = 0; i < 16; i++ )
   {
      t << (char)passWordHashValue[i];
   }

   // write original file size
   union aInt iSize;
   iSize.theInt = sInputString.length();
   t << (char)iSize.i.byte0 << (char)iSize.i.byte1 << (char)iSize.i.byte2 << (char)iSize.i.byte3 <<"*";
//   std::cout<<"StringCrypter::encryptString: str length: " << sInputString.length() << " Writing length: " << iSize.theInt;


   //NOTE: important => buffer must be multiple of 8 bytes (block cypher)
   unsigned char buf_inout[BUFFER_SIZE];

   int iRead, iEncodedSize, iTotalEncodedSize=0;
   QString sTmp = sInputString;
   QString sLeftPart = sTmp.left( BUFFER_SIZE );
   
   while( sLeftPart.length() > 0 )
   {
      memset( buf_inout, 0, BUFFER_SIZE );
      memcpy( buf_inout, sLeftPart.ascii(), sLeftPart.length() );

      // Encrypt the part
      int encryptPadding=0;
      if (sLeftPart.length() % BFISH_BUF_MOD !=0)
           encryptPadding =  BFISH_BUF_MOD - sLeftPart.length() % BFISH_BUF_MOD;
      
      iEncodedSize = fish.Encode( buf_inout, buf_inout, sLeftPart.length() + encryptPadding);
      iTotalEncodedSize += iEncodedSize;
      t.writeRawBytes( (const char*) buf_inout, iEncodedSize );

      // Remove the copied part
      sTmp = sTmp.mid( BUFFER_SIZE );
      // copy another part from left of buffer
      sLeftPart = sTmp.left( BUFFER_SIZE );
   }
//   std::cout<<" iTotalEncodedSize: " << iTotalEncodedSize << std::endl;
}

// TOFIX additional parameter for output path
int StringCrypter::decryptString( const QByteArray& encryptedData,
                                  const QString& sPassWd, QString& sOutputString )
{
   unsigned char buf_inout[BUFFER_SIZE];
   CBlowFish fish;

	if (encryptedData.size() <= 0)
   		return ERROR_INVALID_ENCRYPTEDDATA;

   // check for header string
   char sHeader[15];
   for ( uint i = 0; i < strlen(TUX_ENCRYPT_HEADER); i++ )
   {
      sHeader[i] = encryptedData[i];
   }


   if( 0 != strncmp(sHeader, TUX_ENCRYPT_HEADER, strlen(TUX_ENCRYPT_HEADER)) )
   {
      // the given string was not compressed with this code
      std::cout<<"Invalid file header (not encrypted with TuxCards)!"<<std::endl;
      return ERROR_INVALID_FILEHEADER;
   }

   // read hash value from file (md5 algorithm)
   unsigned char sHash[16];
   memset( sHash, 0, 16 );
   int offset = strlen(TUX_ENCRYPT_HEADER);
   for ( int i = 0; i < 16; i++ )
   {
      sHash[i] = encryptedData[offset + i];
   }


   // calculate this-password hash value
   CMD5 md5;
   md5.MD5Init();
   md5.MD5Update( (unsigned char *)sPassWd.ascii(), sPassWd.length() );
   md5.MD5Final();

   // compare hash values to quickly validate given password
   if( 0 != memcmp(sHash, md5.GetDigestBinary(), 16) )
   {
      //std::cout<<"Wrong password!"<<std::endl;
      return ERROR_INVALID_PASSWD;
   }

   union aInt iSize;
   iSize.i.byte0 = encryptedData[offset+16+0];
   iSize.i.byte1 = encryptedData[offset+16+1];
   iSize.i.byte2 = encryptedData[offset+16+2];
   iSize.i.byte3 = encryptedData[offset+16+3];


   int iIndexOfAsterisc = offset+16+3+1;
   QByteArray tmpArray( encryptedData.size() - iIndexOfAsterisc - 1 );
   for ( uint i = iIndexOfAsterisc+1; i < encryptedData.size(); i++ )
   {
      tmpArray[i-iIndexOfAsterisc-1] = encryptedData[i];
   }

   fish.Initialize( (unsigned char *)sPassWd.ascii(), sPassWd.length() );

   QByteArray leftArray;
   int bufSize;

   bufSize = StringCrypter::min(tmpArray.size(), BUFFER_SIZE);
   sOutputString = "";
        
   while ( bufSize > 0 )
   {
       // Copy part of unencrypted buffer
      getLeftBytes(leftArray, tmpArray, bufSize );
      memset( buf_inout, 0, BUFFER_SIZE );
      memcpy( buf_inout, leftArray.data(), bufSize);

      // Decrypt the part
      int decryptPadding=0;
      if (bufSize % BFISH_BUF_MOD !=0)
           decryptPadding =  BFISH_BUF_MOD - bufSize % BFISH_BUF_MOD;
      
      fish.Decode( buf_inout, buf_inout, bufSize+decryptPadding);

      // Copy it to output
      if(bufSize < BUFFER_SIZE)
        sOutputString += QString::fromAscii ((const char*) buf_inout, -1);
      else
        sOutputString += QString::fromAscii ((const char*) buf_inout, bufSize);

      bufSize = StringCrypter::min(tmpArray.size(), BUFFER_SIZE);
      // Repeat if needed
   }

   return NO_ERROR;
}

int StringCrypter::min(int num1, int num2)
{
    if (num1 < num2)
        return num1;
    else
        return num2;
}

/**
 * Auxiliary method to retrieve the first 'len' left bytes from a byte array ('source').
 * The result is put into 'dest'.
 * The read bytes are removed from 'source'.
 *
 * The number of bytes copied, can be retrieved via 'dest.size()'.
 */
void StringCrypter::getLeftBytes( QByteArray& dest, QByteArray& source, uint len )
{
   dest.resize(0);

   if ( source.size() < len )
      len = source.size();

   dest.resize(len);
   for ( uint i = 0; i < len; i++ )
   {
      dest[i] = source[i];
   }

   QByteArray tmp( source.size() - len );
   for ( uint i = 0; i < tmp.size(); i++ )
   {
      tmp[i] = source[i + len];
   }

   source.resize(0);
   source.resize(tmp.size());
   for ( uint i = 0; i < tmp.size(); i++ )
   {
      source[i] = tmp[i];
   }
}

