import numpy as np


class FileHandler:
    @staticmethod
    def generate_file_with_numbers(filename, size=1024**3):
        random_numbers = np.random.randint(0, 100000000, size=(size//8,), dtype=np.int64)
        np.savetxt(filename, random_numbers, fmt='%d')
