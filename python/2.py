from Crypto.Cipher import DES, DES3, AES
from Crypto.Random import get_random_bytes
import time
import string
import random

def encryption_time(cipher, plaintext):
    start_time = time.time()
    cipher.encrypt(plaintext)
    end_time = time.time()
    return end_time - start_time

def random_string(size=1000, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

def main():
    plaintext = random_string()
    plaintext_bytes = plaintext.encode('utf-8')

    # DES
    key_des = get_random_bytes(8)
    cipher = DES.new(key_des, DES.MODE_ECB)
    des_time = encryption_time(cipher, plaintext_bytes)

    # Triple DES
    key_3des = get_random_bytes(16)
    cipher = DES3.new(key_3des, DES3.MODE_ECB)
    triple_des_time = encryption_time(cipher, plaintext_bytes)

    # AES-128
    key_aes128 = get_random_bytes(16)
    cipher = AES.new(key_aes128, AES.MODE_ECB)
    aes128_time = encryption_time(cipher, plaintext_bytes)

    # AES-256
    key_aes256 = get_random_bytes(32)
    cipher = AES.new(key_aes256, AES.MODE_ECB)
    aes256_time = encryption_time(cipher, plaintext_bytes)

    # Printing the results
    print("Serial No.\tHash Function Name\tProgramming Language\tInput Size (bits)\tOutput Size (bits)\tTotal Time Taken")
    print("-" * 160)
    print(f"1\t\tDES\t\t\tPython\t\t\t{len(plaintext_bytes)*8}\t\t\t{len(plaintext_bytes)*8}\t\t\t{des_time:.6f} seconds")
    print(f"2\t\tTriple DES\t\tPython\t\t\t{len(plaintext_bytes)*8}\t\t\t{len(plaintext_bytes)*8}\t\t\t{triple_des_time:.6f} seconds")
    print(f"3\t\tAES-128\t\t\tPython\t\t\t{len(plaintext_bytes)*8}\t\t\t{len(plaintext_bytes)*8}\t\t\t{aes128_time:.6f} seconds")
    print(f"4\t\tAES-256\t\t\tPython\t\t\t{len(plaintext_bytes)*8}\t\t\t{len(plaintext_bytes)*8}\t\t\t{aes256_time:.6f} seconds")

if __name__ == "__main__":
    main()
