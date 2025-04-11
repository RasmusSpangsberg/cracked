from torchvision import datasets
import matplotlib.pyplot as plt

data = datasets.MNIST("./", train=False, download=False)

print(type(data))

img = data[0][0]
print(type(img))
print(img)


plt.imshow(img, cmap="grey")
plt.show()

