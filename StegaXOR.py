from ctypes import *


class StegaXOR:
	def __init__(self, key_file):
		self.lib = CDLL('./compiled/stegaxor.so')

		self.lib.StegaXOR_new.restype = c_void_p
		self.lib.StegaXOR_new.argtypes = [c_char_p]

		self.lib.StegaXOR_del.argtypes = [c_void_p]

		self.lib.StegaXOR_encrypt_b2b.argtypes = [c_void_p, c_char_p, c_uint]

		self.lib.StegaXOR_decrypt_b2b.argtypes = [c_void_p, c_char_p, c_uint]

		self.lib.StegaXOR_get_next_encrypted_byte.restype = c_char
		self.lib.StegaXOR_get_next_encrypted_byte.argtypes = [c_void_p]

		self.lib.StegaXOR_update_encrypted_index.argtypes = [c_void_p]

		self.lib.StegaXOR_get_next_decrypted_byte.restype = c_char
		self.lib.StegaXOR_get_next_decrypted_byte.argtypes = [c_void_p]

		self.lib.StegaXOR_update_decrypted_index.argtypes = [c_void_p]

		self.lib.StegaXOR_get_encrypted_len.restype = c_uint
		self.lib.StegaXOR_get_encrypted_len.argtypes = [c_void_p]

		self.lib.StegaXOR_get_decrypted_len.restype = c_uint
		self.lib.StegaXOR_get_decrypted_len.argtypes = [c_void_p]

		self.crypt = self.lib.StegaXOR_new(key_file.encode('utf-8'))

	def __del__(self):
		self.lib.StegaXOR_del(self.crypt)

	def encrypt(self, data, data_len):
		result = b''
		self.lib.StegaXOR_encrypt_b2b(self.crypt, data, data_len)
		len_ = self.lib.StegaXOR_get_encrypted_len(self.crypt)
		for _ in range(len_):
			byte = self.lib.StegaXOR_get_next_encrypted_byte(self.crypt)
			result += byte
		self.lib.StegaXOR_update_encrypted_index(self.crypt)

		return result

	def decrypt(self, data, data_len):
		result = b''
		self.lib.StegaXOR_decrypt_b2b(self.crypt, data, data_len)
		len_ = self.lib.StegaXOR_get_decrypted_len(self.crypt)
		for _ in range(len_):
			byte = self.lib.StegaXOR_get_next_decrypted_byte(self.crypt)
			result += byte
		self.lib.StegaXOR_update_decrypted_index(self.crypt)

		return result
