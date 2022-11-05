B = 12


def get_hash(text: str, q: int) -> int:
    result = 0

    for i in range(len(text)):
        result = (B * result + ord(text[i])) % q

    return result


def search(text: str, pattern: str, q: int):
    pattern_len = len(pattern)
    text_len = len(text)

    if pattern_len > text_len:
        raise ValueError('Invalid pattern or text were specified. Pattern length can not be higher than text length')

    multiplier = 1
    for i in range(1, pattern_len):
        multiplier = (multiplier * B) % q

    pattern_hash = get_hash(pattern, q)
    current_window_hash = get_hash(text[:pattern_len], q)

    for index_symbol in range(text_len - pattern_len + 1):
        if pattern_hash == current_window_hash and text[index_symbol: index_symbol + pattern_len] == pattern:
            print(f'Pattern was found on index: {index_symbol}')

        if index_symbol < text_len - pattern_len:
            current_window_hash = (
                (current_window_hash - ord(text[index_symbol]) * multiplier)
                * B
                + ord(text[index_symbol + pattern_len])
            ) % q

            if current_window_hash < 0:
                current_window_hash += q


txt = "I love Python! Python is good, JS is bad!"
pat = "Python"

q_ = 10
search(txt, pat, q_)
