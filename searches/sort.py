"""
Project 2 - Sorting
Author: Carrie Kwong
Class: CS 2420

"""

from random import seed
from random import sample
import time


# Function to find the partition position
def partition(lyst, first, last):
    # Choose the rightmost element as pivot
    pivot = lyst[first]

    # Pointer for greater element
    i = first + 1

    # Traverse through all elements
    # compare each element with pivot
    for j in range(first + 1, last + 1):
        if lyst[j] < pivot:
            # Swapping element at i with element at j
            lyst[i], lyst[j] = lyst[j], lyst[i]

            # If element smaller than pivot is found
            # swap it with the greater element pointed by i
            i += 1

    i -= 1
    # Swap the pivot element with
    # e greater element specified by i
    (lyst[i], lyst[first]) = (lyst[first], lyst[i])

    # Return the position from where partition is done
    return i


def quick_sortHelper(lyst, first, last):
    if first < last:
        pivot = partition(lyst, first, last)
        quick_sortHelper(lyst, first, pivot)
        quick_sortHelper(lyst, pivot + 1, last)


def quicksort(lyst):
    first = 0
    last = len(lyst) - 1
    quick_sortHelper(lyst, first, last)
    return lyst


def mergesort(lyst):
    last = len(lyst)
    # step 1: start
    if last > 1:
        middle = len(lyst) // 2
        left = lyst[:middle]
        right = lyst[middle:]
        mergesort(left)
        mergesort(right)

        i = 0
        compare2 = 0
        compare3 = 0

        while i < len(left) and compare2 < len(right):
            if left[i] <= right[compare2]:
                lyst[compare3] = left[i]
                i += 1
            else:
                lyst[compare3] = right[compare2]
                compare2 += 1
            compare3 += 1

        while i < len(left):
            lyst[compare3] = left[i]
            i += 1
            compare3 += 1

        while compare2 < len(right):
            lyst[compare3] = right[compare2]
            compare2 += 1
            compare3 += 1

    return lyst


def selection_sort(lyst):
    for i in range(len(lyst)):  # for the entirety of the list...
        smallest_number = i
        for j in range(i + 1, len(lyst)):  # compare first index with the next few elements
            if lyst[smallest_number] > lyst[j]:  # swap out smaller element with first index if
                smallest_number = j  # first_index is greater than the smaller element

        lyst[i], lyst[smallest_number] = lyst[smallest_number], lyst[i]

    return lyst


def insertion_sort(lyst):
    """
    This method checks if
    """
    for i in range(1, len(lyst)):
        key = lyst[i]
        j = i - 1
        while j >= 0 and key < lyst[j]:
            lyst[j + 1] = lyst[j]
            j -= 1
        lyst[j + 1] = key

    return lyst


def is_sorted(lyst):
    """
    checks if list is sorted and contains only int
    """
    sorted_list = sorted(lyst)
    if lyst == sorted_list:
        return True

    return False

    # timsort uses sort or sorted method()
    # replace selection_sort with timsort


def random_list():
    data_size = 10000
    seed(0)
    data = sample(range(data_size * 3), k=data_size)
    test = data.copy()  # don’t sort data, sort a copy of data
    return test

    # create large array
    # keep track of time


def main():
    test = random_list()
    print("starting insertion_sort")
    start = time.perf_counter()
    test = insertion_sort(test)
    stop = time.perf_counter()
    print("Selection_sort duration: ", stop - start)

    test = random_list()
    print("starting merge_sort")
    start = time.perf_counter()
    test = mergesort(test)
    stop = time.perf_counter()
    print("Merge_sort duration: ", stop - start)

    test = random_list()
    print("starting quick_sort")
    start = time.perf_counter()
    test = quicksort(test)
    stop = time.perf_counter()
    print("quick_sort duration: ", stop - start)

    test = random_list()
    print("starting selection sort")
    start = time.perf_counter()
    test = selection_sort(test)
    stop = time.perf_counter()
    print("selection_sort duration: ", stop - start)

    test = random_list()
    print("starting insertion sort")
    start = time.perf_counter()
    test = insertion_sort(test)
    stop = time.perf_counter()
    print("insertion_sort duration: ", stop - start)

    test = random_list()
    print("starting is_sorted")
    start = time.perf_counter()
    test = is_sorted(test)
    stop = time.perf_counter()
    print("is_sorted duration: ", stop - start)


if __name__ == "__main__":
    main()
