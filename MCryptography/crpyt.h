#ifndef CRPYH
#define CRPYH

#include "Menthol.h"
#include "hex.h"
template<class T> string Template_1(T & t, char* str)
{
	string digest;
	CryptoPP::StringSource(str, true,new CryptoPP::HashFilter(t, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
	return digest;
}

template<class T> string Template_2(char* str)
{
	string digest;
	CryptoPP::StringSource(str, true,new T(new CryptoPP::StringSink(digest)));
	return digest;
}

template<class T> string Template_3(char* str,char* _key)
{
		string recovered;
		string cipher=str;
		char *tmpK= _key;
		CryptoPP::byte key[ T::DEFAULT_KEYLENGTH ];   
		for (int j = 0; j < T::DEFAULT_KEYLENGTH; ++j)
		{
			key[j] = tmpK[j];
		}
		CryptoPP::ECB_Mode<T>::Encryption d;
		d.SetKey((CryptoPP::byte*)key, sizeof(key));

		// The StreamTransformationFilter removes
		//  padding as required.
		CryptoPP::StringSource(cipher, true, 
			new CryptoPP::StreamTransformationFilter(d,
				new CryptoPP::StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource

		string encoded;
		CryptoPP::StringSource(recovered, true,
			new CryptoPP::Base64Encoder(
			new CryptoPP::StringSink(encoded)
			) // HexEncoder
		); // StringSource
		return encoded;
}



template<class T> string Template_4(char* str,char* _key)
{
		string recovered;
		string cipher=str;
		char *tmpK =_key;
		CryptoPP::byte key[T::DEFAULT_KEYLENGTH ];   
		for (int j = 0; j < T::DEFAULT_KEYLENGTH; ++j)
		{
			key[j] = tmpK[j];
		}
		CryptoPP::ECB_Mode<T >::Decryption d;
		d.SetKey((CryptoPP::byte*)key, sizeof(key));


		string decoded;
		CryptoPP::StringSource(cipher, true,
			new CryptoPP::Base64Decoder(
			new CryptoPP::StringSink(decoded)
			) // HexEncoder
		); // StringSource


		CryptoPP::StringSource(decoded, true, 
			new CryptoPP::StreamTransformationFilter(d,
				new CryptoPP::StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource
		return recovered;
}




#endif