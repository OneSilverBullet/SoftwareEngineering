## 关于Sketch2Code原理：pix2code论文研究
### 预备知识1：RNN
循环神经网络的主要用途是处理和预测序列数据，在全连接神经网络或卷积神经网络中，网络结果都是从输入层到隐含层再到输出层，层与层之间是全连接或部分连接的，但每层之间的结点是无连接的。考虑这样一个问题，如果要预测句子的下一个单词是什么，一般需要用到当前单词以及前面的单词，因为句子中前后单词并不是独立的，比如，当前单词是“很”，前一个单词是“天空”，那么下一个单词很大概率是“蓝”。循环神经网络的来源就是为了刻画一个序列当前的输出与之前信息的关系。从网络结果上来说，RNN会记忆之前的信息，并利用之前的信息影响后面的输出。也就是说，RNN的隐藏层之间的结点是有连接的，隐藏层的输入不仅包括输入层的输出，还包含上一时刻隐藏层的输出。典型的RNN结构如下图所示，对于RNN来说，一个非常重要的概念就是时刻，RNN会对于每一个时刻的输入结合当前模型的状态给出一个输出，从图中可以看出，RNN的主体结构A的输入除了来自输入层的Xt,还有一个循环的边来提供当前时刻的状态。同时A的状态也会从当前步传递到下一步。
![LSTM](https://img-blog.csdn.net/20181022094701581?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L21lbW9yaWVzX3N1bnNldA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

### 基本想法

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


