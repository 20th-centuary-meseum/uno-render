from PIL import Image
import numpy as np

img = Image.open(input("경로 입력"))

monoColorList = []
result = []
enterCount = 0
for i in range(16):
    for j in range(16):
        croppedImage = img.crop((j, i, j+1, i+1))
        pixel = np.array(croppedImage)
        if pixel[0][0] < 125:
            monoColorList.append('0')
        elif pixel[0][0] > 125 :
            monoColorList.append('1')
        if len(monoColorList) == 8 and enterCount == 1:
            result.append('0b' + ''.join(monoColorList) + ',\n')
            monoColorList = []
            enterCount = 0
        elif len(monoColorList) == 8 and enterCount == 0 :
            result.append('0b' + ''.join(monoColorList) + ',')
            monoColorList = []
            enterCount = 1
        
print(monoColorList)
print('{' + ' '.join(result) + '}')
