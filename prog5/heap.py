"""
    Module for min heap.  Used in the creation of the huffman code
"""

class NotHufChar(Exception):pass
class HufChar:
    """
        Helper class.  Stores a character and its frequency
    """
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left, self.right = None, None

    def __eq__(self, other):
        if isinstance(other, HufChar):
            return self.freq == other.freq
        raise NotHufChar()

    def __lt__(self, other):
        if isinstance(other, HufChar):
            return self.freq < other.freq
        raise NotHufChar()

    def __gt__(self, other):
        if isinstance(other, HufChar):
            return self.freq > other.freq
        raise NotHufChar()

    def __str__(self):
        return "'{}': {}".format(self.char, self.freq)

    def __repr__(self):
        return self.__str__()

def swap(list, ii, jj):
    """
        Helper function, swaps two elements

        Arguments:
            list (:class:`list`): List to swap elements of
            ii (:class:`int`): index 1 of list
            jj (:class:`int`): index 2
    """

    temp = list[ii]
    list[ii] = list[jj]
    list[jj] = temp

class HufMinHeap:
    def __init__(self):
        self.heap = []
        self.height = 0 #we consider no elements height 0

    def __str__(self):
        str = ""
        for char in self.heap:
            str += "{}: {}, ".format(char.char, char.freq)
        return str

    def _heapify(self):
        start_i = self.height // 2
        self.heap
        
        while start_i >= 0:
            right_i, left_i = start_i * 2 + 1, start_i * 2 + 2
            has_right = right_i < self.height
            has_left = left_i < self.height

            if has_right and has_left:
                right = self.heap[right_i]
                left = self.heap[left_i]
                min_val = min(right, left)
                if min_val < self.heap[start_i]:
                    if left < right or left == right:
                        swap(self.heap, start_i, left_i)
                    else:
                        swap(self.heap, start_i, right_i)
            elif has_left:
                left = self.heap[left_i]
                if left < self.heap[start_i]:
                    swap(self.heap, left_i, start_i)
            start_i -= 1


    def add_element(self, elm):
        if not isinstance(elm, HufChar):
            print("This heap only supports Huffman Characters, "
                             "got{}".format(type(elm)))
            raise NotHufChar()

        self.heap.append(elm)
        self.height += 1
        self._heapify()

    def pop_min(self):
        if self.height <= 0:
            return None
        min = self.heap[0]

        self.height -= 1

        if self.height == 0:
            return self.heap.pop()

        if self.height > 0:
            self.heap[0] = self.heap.pop()
            self._heapify()
        return min

    def peek_min(self):
        return self.heap[0]


if __name__ == '__main__':
    ii = HufChar('i', 10)
    jj = HufChar('j', 20)

    heap = HufMinHeap()
    heap.add_element(ii)
    heap.add_element(jj)
    heap.add_element(HufChar('k', 5))
    heap.add_element(HufChar('o', 4))
    heap.add_element(HufChar('a', 25))
    heap.add_element(HufChar('g', 1))
    heap.add_element(HufChar('n', 3))

    while True:
        pop = heap.pop_min()
        if not pop:
            break
        print(pop.freq)
