from heap import *

def get_character_count(str):
    """
        Returns the count of all characters in a string

        Arguments:
            str (:class:`str`): The input string

        Returns:
            (:class:`dict`): Each key is a character, each value its appearance
                             count.  The key total coresponds to the total number
                             of characters in the string.

        Complexity:
            O(n), where n is the length of the string
    """
    count = {'total': 0}
    for char in str:
        if char in count.keys():
            count[char] += 1
        else:
            count[char] = 1
        count['total'] += 1
    return count

def frequency_from_count(count):
    """
        Returns the frequency of all characters in a string

        Arguments:
            count (:class:`dict`): The count of characters from a string

        Returns:
            (:class:`dict`): The frequency as a dictionary

        Complexity:
            O(n), where n is the length of the string
    """
    return {char: count[char] / count['total'] for char in count.keys() \
            if char != 'total'}

class HuffmanTree:
    def __init__(self, frequency):
        chars = [HufChar(char, freq) for char, freq in frequency.items()]
        self.heap = HufMinHeap()
        for char in chars:
            self.heap.add_element(char)

        print(self.heap.height)

        while self.heap.height > 1:
            left, right = self.heap.pop_min(), self.heap.pop_min()
            new = HufChar(left.char + right.char, left.freq + right.freq)
            new.left = left
            new.right = right
            self.heap.add_element(new)

    def get_codes(self):
        def _get_codes(codes, node, code):
            if node is None:
                return
            if node.left is None and node.right is None:
                codes[node.char] = code
            _get_codes(codes, node.left, code + "0")
            _get_codes(codes, node.right, code + "1")

        codes = {}
        _get_codes(codes, self.heap.pop_min(), "")
        return codes

def string_to_huffman(str):
    """
        This function takes in a string of arbitrary length and returns an 
        optimal huffman code for it.

        Arguments:
            str (:class:`str`): The input string

        Returns:
            (:class:`str`): The string representation of a binary huffman code

        Complexity:
            O(nlogn)
    """
    count = get_character_count(str)
    freq = frequency_from_count(count)
    huff = HuffmanTree(freq)
    return huff.get_codes()

if __name__ == '__main__':
    string = input("enter a string: ")
    print(string_to_huffman(string))
