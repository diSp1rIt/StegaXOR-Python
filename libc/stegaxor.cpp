#include "stegaxor.h"


static unsigned int gcd(unsigned int a, unsigned int b) { 
	unsigned int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}


StegaXOR::StegaXOR(const string key_file) {
	this->encrypted_index = 0;
	this->decrypted_index = 0;
	this->random_data_length = 0;
	this->shift = 0;
	this->key = new unsigned char [1024];
	this->key_length = 0;

	ifstream fd (key_file);

	if (!fd.is_open()) {
		cout << "[-] Error opening \"" << key_file << "\" to load key." << endl;
		cout << "Generation new key..." << endl;

		ofstream fd_ (key_file, ios_base::trunc);

		if (!fd_.is_open()) {
			cout << "[-] Error creating\"" << key_file << "\"" << endl;
			cout << "Generation new key..." << endl;
			exit(-1);
		}

		for (unsigned short i = 0; i < 1024; i++) {
			char byte = this->gen() % 256;
			this->key[i] = byte;
			fd_.write(&byte, 1);
		}
		fd_.close();
		this->key_length = 1024;
		cout << "Key generated" << endl;
	} else {
		for (int i = 0; i < 1024; i++) {
			char buffer;
			if (fd.eof()) {
				this->key_length = i + 1;
				break;
			} else {
				fd.read(&buffer, 1);
				this->key[i] = buffer;
			}
		}
		if (this->key_length == 0)
			this->key_length = 1024;

		fd.close();
	}	
}


void StegaXOR::encrypt_b2b(const char *input, const unsigned int input_len) {
	for (unsigned int i = input_len * 2; i < input_len * 3; i++) {
    	if (gcd(i, key_length % i) == 1) {
    		this->shift = key_length % i;
    		this->random_data_length = i;
    		break;
    	}
    }

    // cout << "Shift: " << this->shift << endl;
    // cout << "Random length: " << this->random_data_length << endl;

    this->encrypted_bytes = new char [this->random_data_length];

    for (unsigned int i = 0; i < this->random_data_length; i++) {
    	this->encrypted_bytes[i] = this->gen() % 256;
    }

    unsigned int data_index = 0;
    unsigned int key_index = 0;
    
    for (unsigned int i = 0; i < input_len; i++) {
    	this->encrypted_bytes[data_index] = input[i] ^ this->key[key_index];
    	data_index = (data_index + this->shift) % this->random_data_length;
    	key_index = (key_index + 1) % this->key_length;
    }

    this->encrypted_bytes[data_index] = '\0' ^ this->key[key_index];
    this->encrypted_len = this->random_data_length;
}


void StegaXOR::decrypt_b2b(const char *input, const unsigned int input_len) {
	this->shift = this->key_length % input_len; 

	unsigned int i = 0;
	unsigned int data_index = 0;
    unsigned int key_index = 0;

    // cout << "Shift: " << this->shift << endl;
    // cout << "Random length: " << input_len << endl;

    this->decrypted_bytes = new char [input_len];

	while (true) {
    	this->decrypted_bytes[i] = input[data_index] ^ this->key[key_index];
    	data_index = (data_index + this->shift) % input_len;
    	key_index = (key_index + 1) % this->key_length;
    	if (this->decrypted_bytes[i] == '\0') {
	    	this->decrypted_len = i;
	    	break;
	    }
    	if (i == input_len) {
	    	this->decrypted_bytes = new char[1];
	    	this->decrypted_len = 0;
	    	break;
	    }
    	i++;
    }
}


char StegaXOR::get_next_encrypted_byte() {
	if (this->encrypted_index >= this->encrypted_len)
		exit(-2);
	char byte = this->encrypted_bytes[this->encrypted_index];
	this->encrypted_index++;
	return byte;
}


void StegaXOR::update_encrypted_index() {
	this->encrypted_index = 0;
}


char StegaXOR::get_next_decrypted_byte() {
	if (this->decrypted_index >= this->decrypted_len)
		exit(-2);
	char byte = this->decrypted_bytes[this->decrypted_index];
	this->decrypted_index++;
	return byte;
}


void StegaXOR::update_decrypted_index() {
	this->decrypted_index = 0;
}


unsigned int StegaXOR::get_encrypted_len() {
	return this->encrypted_len;
}


unsigned int StegaXOR::get_decrypted_len() {
	return this->decrypted_len;
}


StegaXOR *StegaXOR_new(const char *key_file) {
	return new StegaXOR(string(key_file));
}


void StegaXOR_del(StegaXOR *class_) {
	delete class_;
}


void StegaXOR_encrypt_b2b(StegaXOR *class_, const char *input, const unsigned int input_len) {
	class_->encrypt_b2b(input, input_len);
}


void StegaXOR_decrypt_b2b(StegaXOR *class_, const char *input, const unsigned int input_len) {
	class_->decrypt_b2b(input, input_len);
}


char StegaXOR_get_next_encrypted_byte(StegaXOR *class_) {
	return class_->get_next_encrypted_byte();
}


void StegaXOR_update_encrypted_index(StegaXOR *class_) {
	class_->update_encrypted_index();
}


char StegaXOR_get_next_decrypted_byte(StegaXOR *class_) {
	return class_->get_next_decrypted_byte();
}


void StegaXOR_update_decrypted_index(StegaXOR *class_) {
	class_->update_decrypted_index();
}


unsigned int StegaXOR_get_encrypted_len(StegaXOR *class_) {
	return class_->get_encrypted_len();
}


unsigned int StegaXOR_get_decrypted_len(StegaXOR *class_) {
	return class_->get_decrypted_len();
}
