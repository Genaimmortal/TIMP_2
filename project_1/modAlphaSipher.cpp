#include "modAlphaCipher.h"
using namespace std;
modAlphaCipher::modAlphaCipher(const string& skey)
{
	for (unsigned i=0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	wstring wskey = towstr(skey);
	key = convert(wskey);
}
string modAlphaCipher::encrypt(const string& open_text)
{
	wstring open_wtext = towstr(open_text);
	vector<int> work = convert(open_wtext);
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
string modAlphaCipher::decrypt(const string& cipher_text)
{
	wstring cipher_wtext = towstr (cipher_text);
	vector<int> work = convert(cipher_wtext);
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
inline vector<int> modAlphaCipher::convert(const wstring& ws)
{
	vector<int> result;
	for(auto wc:ws) {
		result.push_back(alphaNum[wc]);
	}
	return result;
}
inline string modAlphaCipher::convert(const vector<int>& v)
{
	wstring wresult;
	for(auto i:v) 
	{ 
		wresult.push_back(numAlpha[i]);
	}
	string result = fromwstr(wresult);
	return result;
}
wstring modAlphaCipher::towstr(const string& s)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> codec;
	wstring ws = codec.from_bytes(s);
	return ws;
}
string modAlphaCipher::fromwstr(const wstring& ws)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> codec;
	string s = codec.to_bytes(ws);
	return s;
}
