#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
const double inf=1e100;
const double eps=1e-6;
int sgn(double d)
{
    if(fabs(d)<eps) return 0;
    if(d>0) return 1;
    return -1;
}
int dcmp(double x,double y)
{
    double d=x-y;
    if(sgn(d)==0) return 0;
    else if(sgn(d)>0) return 1;
    else return -1;
}
struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){};
};
typedef Point Vector;
//运算符重载
Vector operator +(Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator -(Vector A,Vector B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator *(Vector A,double p)
{
    return Vector(A.x*p,A.y*p);
}
Vector operator /(Vector A,double p)
{
    return Vector(A.x/p,A.y/p);
}
bool operator <(Point &a,Point& b)
{
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}
bool operator ==(Point &a,Point &b)
{
    if(dcmp(a.x,b.x)==0&&dcmp(a.y,b.y)==0) return true;
    else return false;
}
double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y+B.y;
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
double Angle(Vector A,Vector B)
{
    return acos(Dot(A,B)/Length(A)/Length(B));
}
double AreaF(Point A,Point B,Point C)
{
    return Cross(B-A,C-A);
}
Vector Rotate(Vector A,double rad)//rad为逆时针旋转的弧度
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A)//向量逆时针旋转90度后的单位法向量
{
    double L=Length(A);
    return Vector(-A.y/L,A.x/L);
}
bool LeftTest(Point a,Point b,Point c)//判断bc是不是ab的逆时针方向，凸包构造使用
{
    return Cross(b-a,c-b)>0;
}
struct Line{
    Point v,p;
    Line(Point v,Point p):v(v),p(p){}
    Point point(double t)//返回P=v+(p-v)/t
    {
        return v+(p-v)*t;
    }
};
//判断点在直线上，直线上取两点与待测点构成向量求叉积

//计算两直线交点,使用时保证v,w不相同
Point GetLineInter(Line A,Line B)
{
    double S1=Cross(Vector(B.p-A.v),Vector(B.v-A.v));
    double S2=Cross(Vector(B.v-A.p),Vector(B.p-A.p));
    //double t=Cross(w,u)/Cross(v,w);
    // return P+v*t;
    return A.v+Vector(A.p-A.v)*(S1/(S1+S2));
}
//点到直线距离
double DistanceToLine(Point P,Line A)
{
    Vector v1=A.p-A.v,v2=P-A.v;
    return fabs(Cross(v1,v2)/Length(v1));
}
//点到线段距离
double DistanceToSegment(Point P,Point A,Point B)
{
    if(A==B) return Length(P-A);
    Vector v1=B-A,v2=P-A,v3=P-B;
    if(dcmp(Dot(v1,v2),0)<0) return Length(v2);
    if(dcmp(Dot(v1,v3),0)>0) return Length(v3);
    return DistanceToLine(P,Line(A,B));
}
//求点在直线上的投影点
Point GetLineProjection(Point P,Line A)
{
    Vector v=A.p-A.v;
    return A.v+v*(Dot(v,P-A.v)/Dot(v,v));
}
//判断点是否在线段上
bool OnSegment(Point P,Point A,Point B)
{
    return dcmp(Cross(A-P,B-P),0)==0&&dcmp(Dot(A-P,B-P),0)<0;
}
//判断两线段是否相交
//不允许在端点处相交
bool SegmentProperIntersectionN(Point A1, Point A2, Point B1, Point B2){
    double c1 = Cross(A2 - A1, B1 - A1), c2 = Cross(A2 - A1, B2 - A1);
    double c3 = Cross(B2 - B1, A1 - B1), c4 = Cross(B2 - B1, A2 - B1);
    return (sgn(c1)*sgn(c2) < 0 && sgn(c3)*sgn(c4) < 0);
}
//允许在端点处相交
bool SegmentProperIntersectionY(Point A1, Point A2, Point B1, Point B2){
    double c1 = Cross(A2-A1, B1-A1), c2 = Cross(A2-A1, B2-A1);
    double c3 = Cross(B2-B1, A1-B1), c4 = Cross(B2-B1, A2-B1);
    //if判断控制是否允许线段在端点处相交，根据需要添加
    if(!sgn(c1) || !sgn(c2) || !sgn(c3) || !sgn(c4)){
        bool f1 = OnSegment(B1, A1, A2);
        bool f2 = OnSegment(B2, A1, A2);
        bool f3 = OnSegment(A1, B1, B2);
        bool f4 = OnSegment(A2, B1, B2);
        bool f = (f1|f2|f3|f4);
        return f;
    }
    return (sgn(c1)*sgn(c2) < 0 && sgn(c3)*sgn(c4) < 0);
}
//求多边形面积
double PolygonArea(Point* p, int n){//p为端点集合，n为端点个数
    double s = 0;
    for(int i = 1; i < n-1; ++i)
        s += Cross(p[i]-p[0], p[i+1]-p[0]);
    return s;
}
//求两个圆相交面积
double AreaOfOverlap(Point c1, double r1, Point c2, double r2){
    double d = Length(c1 - c2);
    if(r1 + r2 < d + eps)
        return 0.0;
    if(d < fabs(r1 - r2) + eps){
        double r = min(r1, r2);
        return pi*r*r;
    }
    double x = (d*d + r1*r1 - r2*r2)/(2.0*d);
    double p = (r1 + r2 + d)/2.0;
    double t1 = acos(x/r1);
    double t2 = acos((d - x)/r2);
    double s1 = r1*r1*t1;
    double s2 = r2*r2*t2;
    double s3 = 2*sqrt(p*(p - r1)*(p - r2)*(p - d));
    return s1 + s2 - s3;
}
int main()
{
    Point x,y;
    double r1,r2;
    cin>>x.x>>x.y>>r1>>y.x>>y.y>>r2;
    cout<<AreaOfOverlap(x,r1,y,r2)<<endl;
}