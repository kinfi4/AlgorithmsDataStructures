class FileSorted(Exception):
    pass


class Sorter:
    FILE_A = 'A.txt'
    FILE_B = 'B.txt'

    def sort_file(self, filepath):
        iteration = 0
        while True:
            self.distribute_numbers(filepath, 2**iteration)

            try:
                self.merge_into_file(filepath, 2**iteration)
            except FileSorted:
                break

            iteration += 1

    def merge_into_file(self, to_file_path, batch_size):
        with open(self.FILE_A, 'r') as file_a, open(self.FILE_B, 'r') as file_b, open(to_file_path, 'w') as to_file:
            try:
                number_from_a, number_from_b = None, None
                number_from_a = int(next(file_a).strip())
                number_from_b = int(next(file_b).strip())
            except StopIteration:  # that means that one file is empty, and another one have the whole sorted sequence
                self._copy_file_to_file(self.FILE_A if number_from_a is not None else self.FILE_B, to_file)
                raise FileSorted()

            while True:
                from_a_idx, from_b_idx = 0, 0

                while from_a_idx < batch_size and from_b_idx < batch_size:
                    if number_from_a < number_from_b:
                        from_a_idx += 1
                        number_from_a = self._write_char_from_file_to_file(number_from_a, file_a, to_file)
                    else:
                        from_b_idx += 1
                        number_from_b = self._write_char_from_file_to_file(number_from_b, file_b, to_file)

                    if number_from_a is None or number_from_b is None:
                        break

                while from_a_idx < batch_size and number_from_a is not None:
                    from_a_idx += 1
                    number_from_a = self._write_char_from_file_to_file(number_from_a, file_a, to_file)

                while from_b_idx < batch_size and number_from_b is not None:
                    from_b_idx += 1
                    number_from_b = self._write_char_from_file_to_file(number_from_b, file_b, to_file)

                if number_from_a is None or number_from_b is None:
                    break

            while number_from_a is not None:
                number_from_a = self._write_char_from_file_to_file(number_from_a, file_a, to_file)

            while number_from_b is not None:
                number_from_b = self._write_char_from_file_to_file(number_from_b, file_b, to_file)

    def distribute_numbers(self, from_file_path, batch_size):
        direction = self.FILE_B

        with open(self.FILE_A, 'w') as file_a, open(self.FILE_B, 'w') as file_b, open(from_file_path) as from_file:
            for i, element in enumerate(from_file):
                if i % batch_size == 0:
                    direction = self._toggle_direction(direction)

                if direction == self.FILE_A:
                    file_a.write(f'{element}')
                elif direction == self.FILE_B:
                    file_b.write(f'{element}')

    def _toggle_direction(self, current_direction):
        return self.FILE_A if current_direction == self.FILE_B else self.FILE_B

    @staticmethod
    def _copy_file_to_file(from_file_name, to_file):
        with open(from_file_name) as from_file:
            for element in from_file:
                to_file.write(element)

    @staticmethod
    def _write_char_from_file_to_file(number, from_file, to_file):
        """
         Writes incoming number to file, then takes the next(from_file) and returns it.
         If next(from_file) raises StopIteration (its empty) this method returns None
        """
        to_file.write(f'{number}\n')

        try:
            return int(next(from_file).strip())
        except StopIteration:
            return None


# 3
# -5
# 7
# 2
# 1
# 12
# 44
# 0
# 11

# 1
# 3
# 3
# 2
# 5
# 1
# 7
# -9
# 9
# 10
# 11
# 234
# 123
# 23
# 2
# -435
# 23
# 9
# 52
# 421
# 6
# 3
