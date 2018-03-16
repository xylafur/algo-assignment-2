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

class HufMinHeap:
    def __init__(self):
        self.heap = []
        self.height = 0 #we consider no elements height 0

    def _heapify(self):
        pass

    def add_element(self, elm):
        if not isinstance(elm, HufChar):
            raise NotHufChar("This heap only supports Huffman Characters")
        pass

    def pop_min(self):
        min = self.heap[0]
        self.heap[0] = None
        self._heapify()
        return min

    def peek_min(self):
        return self.heap[0]

    
