from PIL import Image
import heapq
import os
import struct

import cv2
from matplotlib import pyplot as plt

# Define a class for each node in the Huffman tree
class HuffmanNode:
    def __init__(self, frequency, pixel=None):
        self.frequency = frequency
        self.pixel = pixel
        self.left = None
        self.right = None

    # Define comparison operators for sorting the nodes in a heap
    def __lt__(self, other):
        return self.frequency < other.frequency

    def __eq__(self, other):
        if other is None:
            return False
        if not isinstance(other, HuffmanNode):
            return False
        return self.frequency == other.frequency

# Function to calculate the frequency of each pixel in the image
def get_pixel_frequencies(image):
    pixel_freqs = {}
    pixels = image.load()
    width, height = image.size
    for x in range(width):
        for y in range(height):
            pixel = pixels[x, y]
            if pixel not in pixel_freqs:
                pixel_freqs[pixel] = 0
            pixel_freqs[pixel] += 1
    return pixel_freqs

# Function to build the Huffman tree
def build_huffman_tree(pixel_freqs):
    heap = []
    for pixel, frequency in pixel_freqs.items():
        heapq.heappush(heap, HuffmanNode(frequency, pixel))
    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)
        merged_node = HuffmanNode(node1.frequency + node2.frequency)
        merged_node.left = node1
        merged_node.right = node2
        heapq.heappush(heap, merged_node)
    return heap[0]

# Function to generate Huffman codes for each pixel
def generate_huffman_codes(node, prefix="", code={}):
    if node is None:
        return
    if node.pixel is not None:
        code[node.pixel] = prefix
    generate_huffman_codes(node.left, prefix + "0", code)
    generate_huffman_codes(node.right, prefix + "1", code)
    return code

# Function to compress the image
def compress_image(image, huffman_codes):
    compressed_data = ""
    pixels = image.load()
    width, height = image.size
    for x in range(width):
        for y in range(height):
            pixel = pixels[x, y]
            compressed_data += huffman_codes[pixel]
    return compressed_data

# Function to write the compressed data to a file
def write_compressed_data_to_file(file_path, compressed_data, pixel_freqs):
    with open(file_path, "wb") as f:
        # Write the pixel frequencies to the file
        for pixel, frequency in pixel_freqs.items():
            r, g, b = pixel
            f.write(struct.pack("3B", r, g, b))
            f.write(struct.pack("I", frequency))
        # Write the compressed data to the file
        remaining_bits = len(compressed_data) % 8
        if remaining_bits != 0:
            compressed_data += "0" * (8 - remaining_bits)
        bytes_list = [int(compressed_data[i:i+8], 2) for i in range(0, len(compressed_data), 8)]
        f.write(bytes(bytes_list))

# Function to read the pixel frequencies from the compressed file
def read_pixel_frequencies_from_file(file_path):
    pixel_freqs = {}
    with open(file_path, "rb") as f:
        while True:
            pixel_bytes = f.read(3)
            if not pixel_bytes:
                break
            pixel = struct.unpack("3B", pixel_bytes)
            frequency_bytes = f.read(4)
            frequency = struct.unpack("I", frequency_bytes)[0]
            pixel_freqs[pixel] = frequency
    return pixel_freqs

import struct

# Function to decompress the image
def decompress_image(compressed_data, huffman_tree):
    decompressed_data = ""
    node = huffman_tree
    for bit in compressed_data:
        if bit == "0":
            node = node.left
        else:
            node = node.right
        if node.pixel is not None:
            decompressed_data += str(node.pixel)
            node = huffman_tree
    return decompressed_data

# Function to read the compressed data and pixel frequencies from the file
def read_compressed_data_from_file(file_path):
    with open(file_path, "rb") as f:
        # Read the pixel frequencies from the file
        pixel_freqs = {}
        while True:
            pixel_bytes = f.read(3)
            if not pixel_bytes:
                break
            pixel = struct.unpack("3B", pixel_bytes)
            frequency_bytes = f.read(4)
            frequency = struct.unpack("4B", frequency_bytes)[0]
            pixel_freqs[pixel] = frequency
        # Read the compressed data from the file
        compressed_data = ""
        while True:
            byte = f.read(1)
            if not byte:
                break
            bits = bin(ord(byte))[2:].rjust(8, "0")
            compressed_data += bits
    return compressed_data, pixel_freqs

# Function to build the Huffman tree from the pixel frequencies
def build_huffman_tree_from_frequencies(pixel_freqs):
    heap = []
    for pixel, frequency in pixel_freqs.items():
        heapq.heappush(heap, HuffmanNode(frequency, pixel))
    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)
        merged_node = HuffmanNode(node1.frequency + node2.frequency)
        merged_node.left = node1
        merged_node.right = node2
        heapq.heappush(heap, merged_node)
    return heap[0]

# Function to decompress the image from the compressed file
def decompress_image_from_file(file_path,outputpath):
    compressed_data, pixel_freqs = read_compressed_data_from_file(file_path)
    huffman_tree = build_huffman_tree_from_frequencies(pixel_freqs)
    decompressed_data = decompress_image(compressed_data, huffman_tree)
    plt.subplot(1, 2, 2)
    plt.title('Decoded Image')
    plt.imshow(cv2.cvtColor(decompressed_data, cv2.COLOR_BGR2RGB))
    plt.show()
    cv2.imwrite(outputpath, decompressed_data)
    return decompressed_data


def compress_image_to_file(imgfile,file):
    image = Image.open(imgfile)
    pixel_freq = get_pixel_frequencies(image)
    huffman_tree = build_huffman_tree(pixel_freq)
    huffman_codes = generate_huffman_codes(huffman_tree)
    compress_data = compress_image(image,huffman_codes)
    write_compressed_data_to_file(file,compress_data,pixel_freq)


# compress_image_to_file("C:/Users/dpava/Desktop/pa1_photo_id.jpg","compress2.bin")

decompress_image_from_file("compress2.bin","decomp2.jpg")

