from math import gcd
from random import randint as rand
import matplotlib.pyplot as plt
from tqdm import tqdm as prog
from time import time


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


def test(message: str, key: str):
    decrypt(encrypt(message.encode('utf-8'), key.encode('utf-8')), key.encode('utf-8'))


ax = plt.axes(projection='3d')
ax.set_xlabel('Time, c')
ax.set_ylabel('Length of message')
ax.set_zlabel('Length of key')

for key_len in prog(range(1, 10 ** 5, 1000)):
    for message_len in range(1, 10 ** 4, 1000):
        time_start = time()
        test('a' * message_len, 'b' * key_len)
        time_end = time() - time_start
        ax.scatter3D(time_end, message_len, key_len)

plt.show()
