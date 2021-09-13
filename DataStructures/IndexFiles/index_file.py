from random import choice
from string import ascii_letters


class IndexFile:
    def __init__(self, max_value_size):
        self.max_value_size = max_value_size

    @staticmethod
    def generate_random_token(length=10):
        return ''.join([choice(ascii_letters) for _ in range(length)])


with open('A.txt', 'r') as f:
    pass
