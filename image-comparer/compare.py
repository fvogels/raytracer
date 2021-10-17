import wif.reading
import sys


def read_rgb(filename):
    blocks = wif.reading.read_blocks_from_file(filename)
    frames = wif.reading.read_frames(blocks)
    first_frame = next(frames)
    return wif.reading.frame_to_rgb(first_frame)


filename1, filename2 = sys.argv[1:]

image1 = read_rgb(filename1)
image2 = read_rgb(filename2)

