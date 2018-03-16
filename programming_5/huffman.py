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

def build_huffman_tree(freq):
    """
        Arguments:
            count (:class:`dict`): The count of characters from a string

        Returns:
            (:class:`dict`): The frequency as a dictionary

        Complexity:
            O(n), where n is the length of the string
    """
    pass
 
def string_to_huffman(str):
    """
        This function takes in a string of arbitrary length and returns an 
        optimal huffman code for it.

        Arguments:
            str (:class:`str`): The input string

        Returns:
            (:class:`str`): The string representation of a binary huffman code

        Complexity:
    """
    pass

if __name__ == '__main__':
    string = input("enter a string: ")
    count = get_character_count(string)
    freq = frequency_from_count(count)
    print(count)
    print(freq)