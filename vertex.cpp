
/* ----------------------------------------------------------------------------
* ----------------------------------------------------------------------------
*
* 多学科应用模拟的赋能环境
* Enabling Environment for Multi-displinary Application Simulations
*
* 陈建军 中国 浙江大学工程与科学计算研究中心
* 版权所有	  2007年10月15日
* Chen Jianjun  Center for Engineering & Scientific Computation,
* Zhejiang University, P. R. China
* Copyright reserved, Oct. 15, 2007
*
* 联系方式 (For further information, please conctact)
*   电话 (Tel)：+86-571-87953165
*   传真 (Fax)：+86-571-87953167
*   邮箱 (Mail)：chenjj@zju.edu.cn
*
* 文件名称 (File Name)：vector.h
* 初始版本 (Initial Version): V1.0
* 功能介绍 (Function Introduction：
*     定义了一套密度控制机制
*     Define a set of element spacing controlling scheme.
*
*
* -----------------------------修改记录 (Revision Record)------------------------
* 修改者 (Revisor): yhf
* 修改日期 (Revision Date):20190823
* 当前版本 (Current Version):
* 修改介绍 (Revision Introduction):新增了异常处理，新增了一系列的新符号，并按照QVector3D做了名称修改
* ------------------------------------------------------------------------------
* ------------------------------------------------------------------------------*/


#include "vertex.h"
#include <cmath>


/* *********************************************************************************
* 定义三维矢量
* define 3-dimensional vector
* **********************************************************************************/

double& vertex::operator[](const int & index)
{
	if (index > 2) {
		return x;
	}
	if (index == 0)
		return x;
	if (index == 1)
		return y;
	if (index == 2)
		return z;
}

/* 矢量求模 calc. magnitude */
double vertex::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

double vertex::length() const
{
	return magnitude();
}

void vertex::set(double x0, double y0, double z0)
{
	x = x0, y = y0, z = z0;
}

bool vertex::isApproximatelyEqualTo(const vertex v1)
{
	return (abs(x - v1.x) <  (1e-7)) && (abs(y - v1.y) <  (1e-7)) && (abs(z - v1.z) <  (1e-7));
}

/* 矢量求模 calc. magnitude */
double vertex::magnitude2() const
{
	return (x * x + y * y +
		z * z);
}
ostream& operator <<(ostream& out,const  vertex& vec) {
	out <<"("<< vec.x << " " << vec.y << " " << vec.z << ")";
	return out;
}
double vertex::dotProduct(const vertex v1, const vertex v2)
{
	return v1 * v2;
}

vertex vertex::crossProduct(const vertex v1, const vertex v2)
{
	return v1 ^ v2;
}
vertex vertex::normalized() {
	double m = magnitude();
	if (m == 0)
	{
		return vertex(0, 0, 0);
	}
	else {
		return vertex(x / m, y / m, z / m);
	}
}
/* 归一 normalization */
void vertex::normalize()
{
	double m = magnitude();
	if (abs(m) < 1e-10)//修改浮点数等于0为绝对值小于误差 yhf20190823
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	else {
		x = x / m;
		y = y / m;
		z = z / m;
	}
}

/* **********************************
* 重载操作符 overloaded operator
* **********************************/

/* 赋值 assignment */
const vertex& vertex::operator = (const vertex& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

const vertex& vertex::operator = (double v)
{
	x = y = z = v;
	return *this;
}

/* 四则运算 simple mathamatic operator */
vertex vertex::operator + (const vertex& v) const
{

	return vertex(x + v.x, y + v.y, z + v.z);
}

vertex vertex::operator - (const vertex& v) const
{
	return vertex(x - v.x, y - v.y, z - v.z);
}

vertex vertex::operator * (const double& s) const
{
	return vertex(x * s,y*s,z*s);
}
vertex vertex::operator / (const double& s) const
{

	return vertex(x/ s, y/s, z/s);
}


vertex vertex::operator/(const vertex & v) const
{
	if (abs(v.x) < 1e-10)
		return vertex(1.0, 0.0,0.0);
	if (abs(v.y) < 1e-10)
		return vertex(0.0, 1.0, 0.0);
	if (abs(v.z) < 1e-10)
		return vertex(0.0, 0.0, 1.0);
	return  vertex(x / v.x, y / v.y, z / v.z);
}


vertex vertex::getmul(const vertex & v) const
{
	vertex vr;
	vr.x = x * v.x;
	vr.y = y * v.y;
	vr.z = z * v.z;
	return vr;
}

vertex& vertex::operator += (const vertex& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
vertex& vertex::operator -= (const vertex& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vertex& vertex::operator += (double delta)
{
	x += delta;
	y += delta;
	z += delta;
	return *this;
}
vertex& vertex::operator -= (double delta)
{
	x -= delta;
	y -= delta;
	z -= delta;
	return *this;
}


/* 点积 & 叉积 dot & cross */
double vertex::operator * (const vertex& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

vertex vertex::operator ^ (const vertex& v) const
{
	vertex vr;
	vr.x = y * v.z - v.y * z;
	vr.y = v.x * z - x * v.z;
	vr.z = x * v.y - y * v.x;
	return vr;
}

vertex vertex::operator%(const vertex & v) const
{
	vertex vr;
	vr.x = y * v.z - v.y * z;
	vr.y = v.x * z - x * v.z;
	vr.z = x * v.y - y * v.x;
	return vr;
}


vertex operator - (const vertex& v)
{
	vertex vr;
	vr.x = -v.x;
	vr.y = -v.y;
	vr.z = -v.z;
	return vr;
}
vertex operator * (double scale, const vertex& v)
{
	return v * scale;
}

