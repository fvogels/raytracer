import wif.reading
import sys
import os

def read_rgb(filename):
    blocks = wif.reading.read_blocks_from_file(filename)
    frames = wif.reading.read_frames(blocks)
    first_frame = next(frames)
    return wif.reading.frame_to_linear_rgb(first_frame)


def distance(c1, c2):
    return sum(abs(x - y) for x, y in zip(c1, c2))


def measure_distance(rgb1, rgb2):
    return sum(distance(c1, c2) for c1, c2 in zip(rgb1, rgb2))


files = [filename for filename in os.listdir('.') if filename.endswith('.wif')][4:]
reference = read_rgb('multijittered5.wif')


metrics = [measure_distance(reference, read_rgb(file)) for file in files]
max_metric = max(metrics)

for metric, file in zip(metrics, files):
    relative_metric = metric / max_metric
    print(f'{file} {relative_metric}')


# matrix = {}
# max_metric = 0

# for i in range(len(files)):
#     filename1 = files[i]
#     matrix.setdefault(filename1, {})[filename1] = 0
#     for j in range(i + 1, len(files)):
#         print(i, j, file=sys.stderr)
#         filename2 = files[j]
#         matrix.setdefault(filename2, {})[filename2] = 0
#         rgb1 = read_rgb(filename1)
#         rgb2 = read_rgb(filename2)
#         metric = measure_distance(rgb1, rgb2)
#         matrix[filename1][filename2] = metric
#         matrix[filename2][filename1] = metric
#         max_metric = max(max_metric, metric)

# print(",".join(files))

# for file1 in files:
#     print(",".join(str(matrix[file1][file2] / max_metric) for file2 in files))
