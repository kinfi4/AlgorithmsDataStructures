# Алгоритм Кнута — Морриса — Пратта (КМП-алгоритм) — эффективный алгоритм,
# осуществляющий поиск подстроки в строке. Время работы алгоритма линейно зависит от объёма входных данных,
# то есть разработать асимптотически более эффективный алгоритм невозможно.


def find_index_of_match(text, template):
    """ Function finds the index of the first appearance of the template in the text """
    p = [0] * len(text)
    j, i = 0, 1

    while i < len(template):
        if text[i] == text[j]:
            p[i] = j + 1
            i += 1
            j += 1
        else:
            if j == 0:
                p[i] = 0
                i += 1
            else:
                j = p[j - 1]

    i, j = 0, 0
    while i < len(text):
        if text[i] == template[j]:
            i += 1
            j += 1
            if j == len(template):
                return i - len(template)
        else:
            if j > 0:
                j = p[j - 1]
            else:
                i += 1

    return -1


print(find_index_of_match('some text', 'text'))  # 5
print(find_index_of_match('lululua', 'lu'))  # 0
print(find_index_of_match('lululua', 'lua'))  # 4

