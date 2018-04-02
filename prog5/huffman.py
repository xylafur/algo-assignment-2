
class HuffmanNode:
   def __init__(self, symbols, freq):
      self.symbols = symbols
      self.freq = freq
      self.left = None
      self.right = None

   def is_leaf(self):
      return (self.left is None) and (self.right is None)

   def __lt__(self, other):
      return (self.freq, self.symbols) < (other.freq, other.symbols)
   def __le__(self, other):
      return (self.freq, self.symbols) <= (other.freq, other.symbols)
   def __gt__(self, other):
      return (self.freq, self.symbols) > (other.freq, other.symbols)
   def __ge__(self, other): return (self.freq, self.symbols) >= (other.freq, other.symbols)

   def __str__(self):
      S = '({},{})'.format(self.symbols, self.freq)
      if self.left:
         S = self.left.symbols + '|' + S
      if self.right:
         S = S + '|' + self.right.symbols
      return '[{}]'.format(S)

   def __repr__(self):
      return '"{}"'.format(self.__str__())


def ParentHuffman(L, R):
   H = HuffmanNode('{}{}'.format(L.symbols,R.symbols), L.freq + R.freq)
   H.left, H.right = L, R
   return H

def Huffman(data):
   # record frequency
   freqs = {}
   for i in data:
      if i not in freqs: freqs[i] = 1
      else: freqs[i] += 1

   # create heap
   import heapq
   heap = [HuffmanNode(s, freqs[s]) for s in freqs]
   heapq.heapify(heap)

   while len(heap) > 1:
      heapq.heappush(heap,
         ParentHuffman(heapq.heappop(heap), heapq.heappop(heap)))

   root = heap[0]
   codes = {}

   def recurse(node, code):
      if node.is_leaf():
         codes[node.symbols] = code
         return

      if node.left:
         recurse(node.left, code+'0')
      if node.right:
         recurse(node.right, code+'1')

   recurse(root, '')
   return heap[0], codes, freqs

def Main():
   Data = input("Enter some data: ")
   print('You entered: ', Data)
   root, codes, freqs = Huffman(Data)
   print('Frequencies: ', freqs)
   print('Codes: ', codes)

if __name__=='__main__':
   Main()

