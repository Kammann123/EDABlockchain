#include "cryptoeda.h"

ECDSA<ECP, SHA256>::PrivateKey cryptoeda::
generatePrivateKey(bool& good) {

	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::PrivateKey privateKey;

	/* Creo, inicializo y valido la clave privada nueva */
	privateKey.Initialize(autoSeededRandomPool, ASN1::secp160r1());
	good = privateKey.Validate(autoSeededRandomPool, 3);

	/* Devuelvo resultado */
	return privateKey;
}

vector<byte> cryptoeda::
generateSignature(ECDSA<ECP, SHA256>::PrivateKey& privateKey, string& data, bool& good) {

	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::Signer signer(privateKey);

	/* Creamos, validamos y luego guardamos la firma */
	good = signer.AccessKey().Validate(autoSeededRandomPool, 3);
	size_t siglen = signer.MaxSignatureLength();
	vector<byte> signature(siglen, 0x00);
	siglen = signer.SignMessage(autoSeededRandomPool, (const byte*)data.data(), data.size(), (byte*)signature.data());
	
	/* Devuelvo el resultado */
	return signature;
}

bool cryptoeda::
verifySignature(ECDSA<ECP, SHA256>::PublicKey& publicKey, string& data, vector<byte>& signature) {

	ECDSA<ECP, SHA256>::Verifier verifier(publicKey);

	return  verifier.VerifyMessage((const byte*)data.data(), data.size(), (const byte*)signature.data(), signature.size());
}

string cryptoeda::
hash(string& data) {

	SHA256 hash;
	string digest;

	/* Realizo el hash y guardo en digest */
	StringSource s(data, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	
	/* Devuelvo el resultado */
	return digest;
}

vector<byte> cryptoeda::
getByteArray(ECDSA<ECP, SHA256>::PublicKey publicKey) {

	vector<byte> byteArray(PUBLIC_KEY_CHARS);
	vector<byte> auxiliar(PUBLIC_KEY_CHARS / 2);

	/* Inicializo */
	const ECP::Point& point = publicKey.GetPublicElement();
	byteArray.clear();

	point.x.Encode(auxiliar.data(), point.x.ByteCount());
	byteArray.insert(byteArray.end(), auxiliar.begin(), auxiliar.end());

	point.y.Encode(auxiliar.data(), point.y.ByteCount());
	byteArray.insert(byteArray.end(), auxiliar.begin(), auxiliar.end());

	/* Devuelvo el resultado */
	return byteArray;
}

vector<byte> cryptoeda::
getByteArray(ECDSA<ECP, SHA256>::PrivateKey privateKey) {

	vector<byte> byteArray(PRIVATE_KEY_CHARS);

	/* Inicializo y obtengo key */
	const Integer& privateKeyInteger = privateKey.GetPrivateExponent();

	privateKeyInteger.Encode(byteArray.data(), privateKeyInteger.ByteCount());

	/* Devuelvo el resultado */
	return byteArray;
}

string cryptoeda::
getStringFromBytes(vector<byte>& byteArray) {

	CryptoPP::HexEncoder encoder;
	string output;

	/* Encoder */
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(byteArray.data(), byteArray.size());
	encoder.MessageEnd();

	/* Devuelvo resultado */
	return output;
}