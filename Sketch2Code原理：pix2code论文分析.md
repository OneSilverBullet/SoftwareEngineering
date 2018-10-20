##关于Sketch2Code原理：pix2code论文研究

###基本想法

从一个GUI屏射图片当中生成对应平台的GUI代码，这种
目标和使用语言去描述对应的图片这种最近比较火热的
深度学习研究有着异曲同工之妙。一般来说，我们可以将
这个任务抽象成三个问题：

1.计算机视觉任务：如何理解给定的图片。

比如对应的object的表示，他们的特点，位置以及样式等等的问题。

2.语言模型任务：如何生成正确的语言。

3.通过利用使用计算机视觉模型的带潜在的变量配合
语言模型来生成正确的语言。

###视觉模型
视觉模型使用的是CNN模型，更确切的说是VGG网络。
作者使用CBB来进行无监督学习，将输入的图片和
固定长度的向量进行映射。
```
image_model = Sequential()
image_model.add(Conv2D(16, (3, 3), padding='valid', activation='relu', input_shape=(256, 256, 3,)))
image_model.add(Conv2D(16, (3,3), activation='relu', padding='same', strides=2))
image_model.add(Conv2D(32, (3,3), activation='relu', padding='same'))
image_model.add(Conv2D(32, (3,3), activation='relu', padding='same', strides=2))
image_model.add(Conv2D(64, (3,3), activation='relu', padding='same'))
image_model.add(Conv2D(64, (3,3), activation='relu', padding='same', strides=2))
image_model.add(Conv2D(128, (3,3), activation='relu', padding='same'))
image_model.add(Flatten())
image_model.add(Dense(1024, activation='relu'))
image_model.add(Dropout(0.3))
image_model.add(Dropout(0.3))
```
这里使用的网络进行训练前，对图片进行如下处理：
* 将图片处理为256*256像素。
* 图片每一个像素都进行normalized在喂给CNN之前。

这篇文章当中使用的卷积核尺寸是，3*3的感受域，
同时其步长为1。


###语言模型

下面的是项目当中使用的DSL：一个简单的专业领域语言。
模型将一张图片转换为DSL格式之后，再进行更加深入的处理。

注意其DSL模型非常简单，便于缩减其搜索空间的同时还可以减少其
词汇量表的大小。通过这种手段，其语言模型可以
在离散输入的情况进行热编码。避免了单词嵌入这种
消耗大量时间空间的运算。
```
, { } small-title text quadruple row btn-inactive btn-orange btn-green btn-red double <START> header btn-active <END> single
```
人类并不是每时每刻都从一片空白的大脑开始他们的思考。在你阅读这篇文章时候，你都是基于自己已经拥有的对先前所见词的理解来推断当前词的真实含义。我们不会将所有的东西都全部丢弃，然后用空白的大脑进行思考。我们的思想拥有持久性。
传统的神经网络并不能做到这点，看起来也像是一种巨大的弊端。
RNN 解决了这个问题。RNN 是包含循环的网络，允许信息的持久化。

LSTM 网络：解决RNN网络长间隔无法识别的问题，可以学习长期特征。


