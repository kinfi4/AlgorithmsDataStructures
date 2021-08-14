def partition(lst, start, end):
    pivot = lst[start]
    pivot_idx = start

    while True:
        while start <= end and lst[start] <= pivot:
            start += 1

        while start <= end and lst[end] >= pivot:
            end -= 1

        if start <= end:
            lst[start], lst[end] = lst[end], lst[start]
        else:
            break
    
    lst[end], lst[pivot_idx] = lst[pivot_idx], lst[end]
    return end


def quick_sort(lst, start=None, end=None):
    if start is None and end is None:
        start, end = 0, len(lst) - 1

    if start < end:
        p_i = partition(lst, start, end)

        quick_sort(lst, start, p_i - 1)
        quick_sort(lst, p_i + 1, end)
