from math import gcd
from random import randint as rand


def encrypt(message: bytes, key: bytes):
    random_len = 2 * len(message)
    while gcd(random_len, len(key)) != 1:
        random_len += 1

    shift = len(key) % random_len

    output = []
    for i in range(random_len):
        output.append(rand(0, 255))

    data_index = 0
    key_index = 0
    for i in range(len(message)):
        output[data_index] = message[i] ^ key[key_index]
        data_index = (data_index + shift) % random_len
        key_index = (key_index + 1) % len(key)

    output[data_index] = 0 ^ key[key_index]

    return bytes(output)


def decrypt(message: bytes, key: bytes):
    shift = len(key) % len(message)

    decoded = []
    data_index = 0
    key_index = 0
    i = 0
    while i != len(message):
        byte = message[data_index] ^ key[key_index]
        if byte == 0:
            return bytes(decoded)
        else:
            decoded.append(byte)
        data_index = (data_index + shift) % len(message)
        key_index = (key_index + 1) % len(key)
        i += 1
    else:
        return bytes(decoded)


message = 'Привет, мир!'
print(f'Исходное сообщение: {message}')

key = 'Какой такой мир?'
print(f'Ключ: {key}')

encrypted_message = encrypt(message.encode('utf-8'), key.encode('utf-8'))
print(f'Зашифрованный текст: {encrypted_message}')

decrypted_message = decrypt(encrypted_message, key.encode('utf-8')).decode('utf-8')
print(f'Расшифрованное сообщение: {decrypted_message}')
print()

print(f'Длина исходного текста: {len(message)}')
print(f'Длина зашифрованного текста: {len(encrypted_message)}')
