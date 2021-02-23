from PIL import Image
import numpy as no
import numpy as np
img = Image.open('image1.jpeg').convert('L')
img = img.resize((1500, 1500), Image.NEAREST)
arr = no.array(img)
smp = [[1, 0, -1], [1, 0, -1], [1, 0, -1]]      # vertical for image1
# smp = [[1, 1, 1], [0, 0, 0], [-1, -1, -1]]    # horizontal for image2

result = np.zeros((1498, 1498))
for i in range(0, 1498):
    for j in range(0, 1498):
        result[i][j] = (arr[i][j] * smp[0][0]) + (arr[i][j + 1] * smp[0][1]) + (arr[i][j + 2] * smp[0][2]) + (arr[i + 1][j] * smp[1][0]) + (arr[i + 1][j + 1] * smp[1][1]) + (arr[i + 1][j + 2] * smp[1][2]) + (arr[i + 2][j] * smp[2][0]) + (arr[i + 2][j + 1] * smp[2][1]) + (arr[i + 2][j + 2] * smp[2][2])

img1 = Image.fromarray(result)
img1.show()

