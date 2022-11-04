# 二 、Armor Detect

## 1.功能介绍
|模块     |功能     |
| ------- | ------ |
|装甲板识别| 检测敌方机器人装甲板位置信息 |
|位置预测| 自瞄时检测移动靶 |
|角度解算| 根据上述位置信息解算目标相对枪管的yaw、pitch角度及距离 |
|相机驱动| 实现相机参数控制及图像采集 |
---
## 2.效果展示
### 装甲板识别
装甲板识别采用基于OpenCV的传统算法实现装甲板位置检测。因为读取的是彩色图，直方图均衡化需要在HSV空间做,同时开操作 (去除一些噪点)，闭操作 (连接一些连通域)。
识别得到装甲板在图像中四个顶点、中心点的坐标信息。 

### 位置预测（class kalman）
用匀速直线运动模型 先滤出矫正后的点 再通过保存上一帧得到的数据预测出下一帧的坐标点 装甲板的预测为分别预测xy坐标，神符的预测则为预测装甲板中心点与中心r标中心点连线相对于水平线的角度，再解算出坐标。

### 角度解算  
角度解算方面使用了P4P算法。 
---
## 3.实现方案  
### 装甲板识别  
装甲板识别使用基于检测目标特征的OpenCV传统方法，实现检测识别的中心思想是找出图像中所有敌方颜色灯条，并使用找出的灯条一一拟合并筛选装甲板。 
主要步骤分为：**图像预处理**、**灯条检测**、**装甲板匹配**、**装甲板数字识别**及最终的**目标装甲板选择**。 
1. **图像预处理** 
为检测灯条，需要进行颜色提取。颜色提取基本思路有BGR、HSV、通道相减法。 
因为读取的是彩色图，直方图均衡化需要在HSV空间做,同时开操作 (去除一些噪点)，闭操作 (连接一些连通域)。

2. **灯条检测** 
灯条检测主要是先对预处理后的二值图找轮廓（findContours），
使用得到的旋转矩形（RotatedRect）构造灯条。

3. **装甲板匹配** 
分析装甲板特征可知，装甲板由两个长度相等互相平行的侧面灯条构成。
我们对检测到的灯条进行两两匹配，解算出中心点，得到灯条在相机面四个角点的坐标（ImagePoints），同时以枪管中心为原点、装甲板长宽构造世界坐标系（ObjectPoints），方便代入PNP解算。

---

### 角度解算  
角度解算部分使用了两种模型解算枪管直指向目标装甲板所需旋转的yaw和pitch角。 
