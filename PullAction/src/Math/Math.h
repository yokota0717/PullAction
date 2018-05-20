#pragma once
#include <cmath>


namespace Math {
	class Vec;
	struct Box2D;
	struct Circle;
	struct Triangle;
	struct Orval;

	//円周率
	static float PI = 3.141592653589793238462643383279502884197f;
	//角度変換
	float ToDegree(float radian);
	float ToRadian(float degree);
	//重力
	float Gravity(int onemeter);


	//ベクトルクラス
	class Vec {
	public:
		float x, y, z;		//座標

		Vec(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		~Vec();


		//ベクトルを正規化
		Vec Normalize();
		//ベクトルを度数法で回転する
		Vec RotateVecDegree(float deg);
		//ベクトルを弧度法で回転する
		Vec RotateVecRadian(float rad);
		//ベクトルを度数法で回転する、回転中心指定
		void RotateVecDegree(Vec center, float deg);
		//ベクトルを弧度法で回転する、回転中心指定
		void RotateVecRadian(Vec center, float rad);
		//2つのベクトルの内積を返す
		static float GetDotVec(Vec v1, Vec v2) {
			return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
		}
		//2つのベクトルの外積を返す(2次元)
		static float GetCrossVec2(Vec v1, Vec v2) {
			return (v1.x*v2.y) - (v1.y*v2.x);
		}
		//2つのベクトルの外積を返す(3次元)
		Vec GetCrossVec3(Vec v1, Vec v2);
		//ベクトルの長さを得る
		static float GetVecLen(Vec v) {
			return std::powf(v.x*v.x + v.y*v.y + v.z*v.z, 0.5f);
		}
		float GetVecLen() const;
		//正規化されたベクトルを得る
		Vec GetUnitVec(Vec v);
		//ベクトルをn倍する
		Vec VecScale(Vec v, float n);
		//2次元ベクトルの単位法線ベクトルを得る v1×v2 ベクトルの左側の方 (注:数学の座標系)
		Vec GetUnitNormVec2Left(Vec v);
		//2次元ベクトルの単位法線ベクトルを得る v1×v2 ベクトルの右側の方 (注:数学の座標系)
		Vec GetUnitNormVec2Right(Vec v);
		//3次元平面の単位法線ベクトルを得る(注:数学の座標系) v1,v2は平面上に存在するベクトル
		Vec GetUnitNormVec3(Vec v1, Vec v2);

		//当たり判定
		bool Hit(Vec& v) const;
		bool Hit(Box2D& b) const;
		bool Hit(Circle& c) const;
		bool HitBox(Box2D& b) const;

		//オペレータ定義
		Vec& operator = (const Vec& v);
		const Vec operator + (const Vec& v) const;
		const Vec operator - (const Vec& v) const;
		const Vec operator * (const float n) const;
		const Vec operator / (const float n) const;
		Vec& operator += (const Vec& v);
		Vec& operator -= (const Vec& v);
		Vec& operator *= (const float n);
		Vec& operator /= (const float n);

	};




	struct Box2D {				//四角形構造体
		float	x, y, w, h;		//左上の座標、幅、高さ

		Box2D();
		Box2D(float x, float y, float w, float h);
		~Box2D();
		void Offset(Vec v);
		void Offset(float vx, float vy);
		Box2D OffsetCopy(float vx, float vy) const;
		Box2D OffsetCopy(const Vec& v)const;
		bool Hit(const Box2D& b) const;
		bool Hit(const Vec& b) const;
	};

	struct Circle {
		Vec center;		//中心座標
		float r;			//半径

		Circle();
		Circle(float x, float y, float z, float r);
		~Circle();

		void Offset(Vec v);
		void Offset(float vx, float vy, float vz = 0.0f);
		Circle OffsetCopy(float vx, float vy, float vz = 0.0f) const;
		Circle OffsetCopy(const Vec& v)const;
		bool Hit(const Circle& c) const;
		bool Hit(const Vec& v) const;
		bool Hit(const Box2D& b) const;
	};

	struct Triangle {
		Vec v1, v2, v3;		//3頂点

		Triangle(Vec v1, Vec v2, Vec v3);
	};

	struct Orval {
		float x, y;		//中心座標
		float lr, sr;	//長軸、短軸	 long radius,shot radius
		float angle;	//長軸のx軸からの傾き

		Orval(float x, float y, float lr, float sr, float ang);
	};


	struct Rect {
		Vec tl, tr, bl, br;			//4頂点
		Rect(Vec tl, Vec tr, Vec bl, Vec br);
		void Rotate(float rad);
		void Rotate(float rad, Vec center);
	};
}