import tensorflow as tf
from tensorflow.keras import Model 
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import sys
from numpy import asarray
import numpy as np

model = tf.compat.v2.keras.models.load_model('hackathon_binary_model.h5')



image = Image.open(sys.argv[1])
image = image.resize((200,200))
pic = asarray(image)
pic = pic.astype('float32')
pic /= 255.0

pic=np.expand_dims(pic,axis=0)


prediction = model.predict(pic)
print(sys.argv[1])

float_formatter = "{:.2f}".format
np.set_printoptions(formatter={'float_kind':float_formatter})
print(prediction)

 
print()
