#ifndef STEGAXOR_LIB_H
#define STEGAXOR_LIB_H

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstring>


using namespace std;


class StegaXOR {
public:
	StegaXOR(const string key_file);
	//~StegaXOR();

	void encrypt_b2b(const char *input, const unsigned int input_len);
	void decrypt_b2b(const char *input, const unsigned int input_len);
	char get_next_encrypted_byte();
	void update_encrypted_index();
	char get_next_decrypted_byte();
	void update_decrypted_index();
	unsigned int get_encrypted_len();
	unsigned int get_decrypted_len();
private:
	char *decrypted_bytes;
	unsigned int decrypted_len;
	char *encrypted_bytes;
	unsigned int encrypted_len;
	unsigned char *key;
	unsigned int key_length;
	unsigned int random_data_length;
	unsigned int shift;
	unsigned int encrypted_index;
	unsigned int decrypted_index;
	random_device gen;
};

#ifdef __cplusplus
extern "C" {
#endif

StegaXOR *StegaXOR_new(const char *key_file);
void StegaXOR_del(StegaXOR *class_);
void StegaXOR_encrypt_b2b(StegaXOR *class_, const char *input, const unsigned int input_len);
void StegaXOR_decrypt_b2b(StegaXOR *class_, const char *input, const unsigned int input_len);
char StegaXOR_get_next_encrypted_byte(StegaXOR *class_);
void StegaXOR_update_encrypted_index(StegaXOR *class_);
char StegaXOR_get_next_decrypted_byte(StegaXOR *class_);
void StegaXOR_update_decrypted_index(StegaXOR *class_);
unsigned int StegaXOR_get_encrypted_len(StegaXOR *class_);
unsigned int StegaXOR_get_decrypted_len(StegaXOR *class_);

#ifdef __cplusplus
}
#endif

#endif