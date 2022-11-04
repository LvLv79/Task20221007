# 一、kalman_Fan
---
## 1.功能介绍
本套代码用于识别大能量机关的中心点R以及流动条对应的装甲板
并在中心R点处标出当前能量机关的神符扇叶中心点和神符中心的连线与水平方向的角度，在装甲板中心点标出神符击打中心和相机的距离

---
## 2.整体框架
本套代码分为三大部分
第一部分：中心点R识别（class Filter）
第二部分：装甲板识别(class Flow)
第三部分：装甲板坐标标定（class sort）
第四部分：卡尔曼滤波（class kalman）
第五部分：重力补偿（class compensator）
第六部分：信息匹配(class target)

---
## 3.实现方案  
一、**中心点R识别（class Filter）**
通过通道相减法获得蓝色发光区域轮廓
并通过以下判断原理得到中心r型图形
筛选条件如下：
①r型图形没有子轮廓，没有父轮廓，且至少有一个同级轮廓。
②面积范围与最小外接矩形的长宽比

二、**装甲板识别(class Flow)**
与r型图形处理方法相似
筛选条件如下：
①装甲板没有子轮廓和同级轮廓，一定有父轮廓。
②面积范围与最小外接矩形的长宽比。

三、**装甲板坐标标定（class sort）**
找出左下（bl）和右下（br）两个点
1.先算出该点与中心R的距离，bl和br两个点一定为距离最小
2.再算出两点和中心点的向量AR、BR,若AR叉乘BR为负数，则A点为bl,B点为br，反之同理。

四、**卡尔曼滤波（class kalman）**
用匀速直线运动模型 先滤出矫正后的点 再通过保存上一帧得到的数据预测出下一帧的坐标点 装甲板的预测为分别预测xy坐标，神符的预测则为预测装甲板中心点与中心r标中心点连线相对于水平线的角度，再解算出坐标。

五、**重力补偿（class compensator）**
通过抛物线模型，利用求根公式直接解算出补偿角度。分为两种情况：
①装甲板在枪管上：
如图所示
此种情况取负根
②装甲板在枪管下：
如图所示
此种情况取正根
如何判断两种情况：通过set函数。set函数内容为通过装甲板在图像坐标系的点和窗口中心点做比较

六、**信息匹配（class target）**
本套代码中专门定义了target类来做图像绘制，计算距离和偏转角度。
获取目标装甲板与中心二点之间的角度偏转极坐标以及相机与装甲板击打点的距离。
