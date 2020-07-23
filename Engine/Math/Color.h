#pragma once

#include <windows.h>

namespace AZ {
	struct Color {
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {};
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {};

		float& operator [] (size_t index) {
			switch (index)
			{
			case (1):
				return r;
			case (2):
				return g;
			case (3):
				return b;
			default:
				break;
			}
		}
		const float& operator [] (size_t index) const {
			switch (index)
			{
			case (1):
				return r;
			case (2):
				return g;
			case (3):
				return b;
			default:
				break;
			}
		}


		void Set(float r, float g, float b) { 
			this->r = r; 
			this->g = g; 
			this->b = b;
		}

		Color operator + (const Color& c) const { return {r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return { r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return { r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return { r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return { r + s, g + s, b + s }; }
		Color operator - (float s) const { return { r - s, g - s, b - s }; }
		Color operator * (float s) const { return { r * s, g * s, b * s }; }
		Color operator / (float s) const { return { r / s, g / s, b / s }; }

		Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }

		Color& operator += (float s) { r += s; g += s; b += s; return *this; }
		Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
		Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
		Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

		friend std::istream& operator >> (std::istream& stream, Color& c);

		COLORREF pack888() const;

		operator COLORREF() const { return pack888(); }

		static const Color red;
		static const Color blue;
		static const Color green;
		static const Color yellow;
		static const Color magenta;
		static const Color cyan;
		static const Color white;
	};

	inline COLORREF Color::pack888() const {
		BYTE _r = static_cast<BYTE>(r * 255.0);
		BYTE _g = static_cast<BYTE>(g * 255.0);
		BYTE _b = static_cast<BYTE>(b * 255.0);

		return (_r) | (_g << 8) | (_b << 16);
	}
}
