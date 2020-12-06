from PIL import Image
import argparse
import struct


parser = argparse.ArgumentParser()
parser.add_argument('input')
parser.add_argument('output')
args = parser.parse_args()

input_file = args.input
output_file = args.output

image = Image.open(input_file)
image.convert('RGB')
pixels = image.load()

with open(output_file, 'wb') as out:
    width, height = image.size
    out.write(struct.pack('II', width, height))
    for row_index in range(0, image.height):
        row = [ c for col_index in range(width) for c in pixels[col_index, row_index] ]
        bs = struct.pack('B' * len(row), *row)
        out.write(bs)
    out.write(struct.pack('I', 0))

