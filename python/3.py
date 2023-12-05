from Crypto.Cipher import DES, DES3, AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import time
import string
import random

def encryption_time(cipher, plaintext, block_size):
    padded_data = pad(plaintext, block_size)
    start_time = time.time()
    cipher.encrypt(padded_data)
    end_time = time.time()
    return end_time - start_time

def random_string(size=1000, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

def main():
    plaintext = random_string()
    plaintext_bytes = plaintext.encode('utf-8')
    results = []

    # DES
    key_des = get_random_bytes(8)
    cipher = DES.new(key_des, DES.MODE_ECB)
    des_time = encryption_time(cipher, plaintext_bytes, 8)
    results.append(("DES", des_time))

    # Triple DES
    key_3des = get_random_bytes(16)
    cipher = DES3.new(key_3des, DES3.MODE_ECB)
    triple_des_time = encryption_time(cipher, plaintext_bytes, 8)
    results.append(("Triple DES", triple_des_time))

    # AES-128
    key_aes128 = get_random_bytes(16)
    cipher = AES.new(key_aes128, AES.MODE_ECB)
    aes128_time = encryption_time(cipher, plaintext_bytes, 16)
    results.append(("AES-128", aes128_time))

    # AES-256
    key_aes256 = get_random_bytes(32)
    cipher = AES.new(key_aes256, AES.MODE_ECB)
    aes256_time = encryption_time(cipher, plaintext_bytes, 16)
    results.append(("AES-256", aes256_time))

    # Sorting the results based on time (efficient first)
    sorted_results = sorted(results, key=lambda x: x[1])

    # Printing the results
    print("Serial No.\tHash Function Name\tProgramming Language\tInput Size (bits)\tOutput Size (bits)\tTotal Time Taken\tPriority")
    print("-" * 200)
    for idx, (name, time_taken) in enumerate(sorted_results, 1):
        print(f"{idx}\t\t{name}\t\t\tPython\t\t\t{len(plaintext_bytes)*8}\t\t\t{len(plaintext_bytes)*8}\t\t\t{time_taken:.6f} seconds\t\t{idx}")

    print("\nAnalysis:")
    print("The table above showcases the efficiency of the four cryptographic hash functions based on their execution times.")
    print(f"The most efficient hash function is {sorted_results[0][0]} with an execution time of {sorted_results[0][1]:.6f} seconds.")
    print(f"The least efficient hash function is {sorted_results[-1][0]} with an execution time of {sorted_results[-1][1]:.6f} seconds.")
    print("The performance difference can be attributed to the different underlying algorithms, key lengths, and operations performed by each hash function.")

if __name__ == "__main__":
    main()
