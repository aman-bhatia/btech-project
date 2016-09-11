from skimage import io, segmentation, color
from skimage.future import graph
import sys

img = io.imread(sys.argv[1])
labels1 = segmentation.slic(img, compactness=30, n_segments=400)
g = graph.rag_mean_color(img, labels1, mode='similarity')
labels2 = graph.cut_normalized(labels1, g)
out2 = color.label2rgb(labels2, img, kind='avg')
io.imshow(out2)
io.show()
