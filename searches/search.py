import math


def linear_search(array, target_number):
    for i in range(len(array)):
        if array[i] == target_number:
            return True
    return False


def binary_search(array, target_number):
    low_index = 0
    high_index = len(array) - 1
    # take list and divide by 2
    mid = (high_index + low_index) / 2
    mid = math.ceil(mid)
    if len(array) == 0:
        return False
    if array[mid] == target_number:
        return True
    """
    print("--------------------------------------------")
    print("Start: " + str(low_index), "Stop: " + str(high_index), "Mid: " + str(mid))
    print("Array[mid]: " + str(array[mid]))
        print(array)
    """
    if array[mid] > target_number:
        return binary_search(array[: mid], target_number)
    else:
        return binary_search(array[mid + 1:], target_number)


def jump_search(array, target_number):
    size = len(array)
    # Finding block size to be jumped
    jump = int(math.sqrt(size))
    # print(array)
    # print(size)
    prev = 0
    while jump < size and array[jump] <= target_number:
        # print("JUMP BEFORE ADJUSTMENT: " + str(jump))
        prev = jump
        jump += int(math.sqrt(size))
        if prev >= size:
            return False
        # print("jump: " + str(jump))
    # linear search
    for value in array[prev: jump]:
        if value == target_number:
            return True
    return False
